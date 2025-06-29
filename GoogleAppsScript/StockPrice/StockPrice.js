/**
 * DISCLAIMER AND USAGE WARNINGS
 * =============================
 * 
 * 1. DO NOT USE IN PRODUCTION
 *    This code is for educational and testing purposes only.
 *    It is not suitable for production environments without proper
 *    error handling, monitoring, and security considerations.
 * 
 * 2. FAIR USAGE OF APIs
 *    - Respect API rate limits and terms of service
 *    - Do not overwhelm servers with excessive requests
 *    - Consider implementing longer delays between requests
 *    - Use appropriate caching to minimize API calls
 *    - Be mindful of the data provider's resources
 *    - Check and comply with the API provider's usage policies
 * 
 * 3. ADDITIONAL CONSIDERATIONS
 *    - This code may impact your Google Apps Script quota
 *    - Monitor your usage to avoid exceeding daily limits
 *    - Test thoroughly in a development environment first
 *    - Consider the legal and ethical implications of data usage
 * 
 * USE AT YOUR OWN RISK
 * The authors are not responsible for any damages, service disruptions,
 * or policy violations that may result from using this code.
 */

function getTWSEStock(symbol = "0050") {
    const url = "https://mis.twse.com.tw/stock/api/getStockInfo.jsp?ex_ch=" + "tse_" + symbol + ".tw";
    const options = {
        'contentType': 'application/xml; charset=utf-8',
        'method': 'GET',
        'headers': {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.5',
            'Accept-Encoding': 'gzip, deflate',
            'Connection': 'keep-alive',
            'Upgrade-Insecure-Requests': '1'
        },
        'muteHttpExceptions': true
    };
    var response = UrlFetchApp.fetch(url, options);
    var responseCode = response.getResponseCode()

    while (responseCode !== 200) {
        Utilities.sleep(2000);
        response = UrlFetchApp.fetch(url, options);
        responseCode = response.getResponseCode()
    }

    var json = response.getContentText("UTF-8");
    var data = JSON.parse(json);
    return data["msgArray"][0]["z"];
};

function getTPEXStock(symbol = "00679B") {
    const url = "https://mis.twse.com.tw/stock/api/getStockInfo.jsp?ex_ch=" + "otc_" + symbol + ".tw";
    const options = {
        'contentType': 'application/xml; charset=utf-8',
        'method': 'GET',
        'headers': {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.5',
            'Accept-Encoding': 'gzip, deflate',
            'Connection': 'keep-alive',
            'Upgrade-Insecure-Requests': '1'
        },
        'muteHttpExceptions': true

    };
    var response = UrlFetchApp.fetch(url, options);
    var responseCode = response.getResponseCode()

    while (responseCode !== 200) {
        Utilities.sleep(2000);
        response = UrlFetchApp.fetch(url, options);
        responseCode = response.getResponseCode()
    }

    var json = response.getContentText("UTF-8");
    var data = JSON.parse(json);
    return data["msgArray"][0]["z"];
};

function getOTCStock(symbol = "1260") {
    const url = "https://www.tpex.org.tw/www/zh-tw/emerging/latest";
    const options = {
        'contentType': 'application/xml; charset=utf-8',
        'method': 'GET',
        'headers': {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.5',
            'Accept-Encoding': 'gzip, deflate',
            'Connection': 'keep-alive',
            'Upgrade-Insecure-Requests': '1'
        },
        'muteHttpExceptions': true

    };
    var response = UrlFetchApp.fetch(url, options);
    var responseCode = response.getResponseCode()
    while (responseCode !== 200) {
        Utilities.sleep(2000);
        response = UrlFetchApp.fetch(url, options);
        responseCode = response.getResponseCode()
    }

    var json = response.getContentText("UTF-8");
    var data = JSON.parse(json)['tables'][0]['data'];
    for (var i = 0; i < data.length; i++) {
        if (data[i][0] === symbol) {
            return data[i][10];
        }
    }
    return "-";
};


function getOTCStockCNYES(symbol = "1260") {
    var url = "https://ws.api.cnyes.com/ws/api/v1/charting/history?resolution=1&symbol=TWG:" + symbol + ":STOCK&quote=1";
    const options = {
        'contentType': 'application/xml; charset=utf-8',
        'method': 'GET',
        'headers': {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.5',
            'Accept-Encoding': 'gzip, deflate',
            'Connection': 'keep-alive',
            'Upgrade-Insecure-Requests': '1'
        },
        'muteHttpExceptions': true

    };
    var response = UrlFetchApp.fetch(url, options);
    var responseCode = response.getResponseCode()

    while (responseCode !== 200) {
        Utilities.sleep(2000);
        response = UrlFetchApp.fetch(url, options);
        responseCode = response.getResponseCode()
    }

    var json = response.getContentText("UTF-8");
    var data = JSON.parse(json);

    try {
        var result = data["data"]["quote"]["6"];
        return result;
    } catch {
        return "n.a";
    }
}

function getStockClose(symbol = "1260") {
    var twse_stock = getTWSEStock(symbol);
    if (twse_stock !== "-") {
        return twse_stock;
    }

    var tpex_stock = getTPEXStock(symbol);
    if (tpex_stock !== "-") {
        return tpex_stock;
    }

    // var otc_stock = getOTCStock(symbol);
    var otc_stock = getOTCStockCNYES(symbol);
    if (otc_stock !== "-") {
        return otc_stock;
    }

    return "n.a";
};
