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

const CACHE_TTL_SECONDS = 60;
const MAX_FETCH_ATTEMPTS = 3;

const FETCH_OPTIONS_ = {
    method: 'GET',
    headers: {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
        'Accept': 'application/json, text/plain, */*',
        'Accept-Language': 'en-US,en;q=0.5',
    },
    muteHttpExceptions: true,
};

function fetchJson_(url) {
    const cache = CacheService.getScriptCache();
    const cached = cache.get(url);
    if (cached !== null) {
        return JSON.parse(cached);
    }

    for (let attempt = 0; attempt < MAX_FETCH_ATTEMPTS; attempt++) {
        try {
            const response = UrlFetchApp.fetch(url, FETCH_OPTIONS_);
            if (response.getResponseCode() === 200) {
                const text = response.getContentText('UTF-8');
                cache.put(url, text, CACHE_TTL_SECONDS);
                return JSON.parse(text);
            }
        } catch (e) {
            // network error — fall through to retry
        }
        Utilities.sleep(500 * (attempt + 1));
    }
    return null;
}

function fetchMisQuote_(symbol, prefix) {
    const data = fetchJson_("https://mis.twse.com.tw/stock/api/getStockInfo.jsp?ex_ch=" + prefix + "_" + symbol + ".tw");
    const arr = data && data.msgArray;
    if (!arr || arr.length === 0) return null;
    const q = arr[0];
    if (!q.z || q.z === "-") return null;
    return q;
}

function resolveMisQuote_(symbol) {
    return fetchMisQuote_(symbol, "tse") || fetchMisQuote_(symbol, "otc");
}

function getTWSEStock(symbol = "0050") {
    const q = fetchMisQuote_(symbol, "tse");
    return (q && q.z) || "-";
}

function getTPEXStock(symbol = "00679B") {
    const q = fetchMisQuote_(symbol, "otc");
    return (q && q.z) || "-";
}

function getStockChange(symbol = "2330") {
    const q = resolveMisQuote_(symbol);
    if (!q) return "";
    const z = parseFloat(q.z), y = parseFloat(q.y);
    if (isNaN(z) || isNaN(y)) return "";
    return z - y;
}

function getStockChangePercent(symbol = "2330") {
    const q = resolveMisQuote_(symbol);
    if (!q) return "";
    const z = parseFloat(q.z), y = parseFloat(q.y);
    if (isNaN(z) || isNaN(y) || y === 0) return "";
    return (z - y) / y;
}

function getOTCStock(symbol = "1260") {
    const data = fetchJson_("https://www.tpex.org.tw/www/zh-tw/emerging/latest");
    const rows = data && data.tables && data.tables[0] && data.tables[0].data;
    if (!rows) return "-";
    for (let i = 0; i < rows.length; i++) {
        if (rows[i][0] === symbol) {
            return rows[i][10];
        }
    }
    return "-";
}

function getOTCStockCNYES(symbol = "1260") {
    const data = fetchJson_("https://ws.api.cnyes.com/ws/api/v1/charting/history?resolution=1&symbol=TWG:" + symbol + ":STOCK&quote=1");
    try {
        return data.data.quote["6"] || "";
    } catch (e) {
        return "";
    }
}

function getStockClose(symbol = "1260") {
    const sources = [getTWSEStock, getTPEXStock, getOTCStockCNYES];
    for (const fn of sources) {
        const price = fn(symbol);
        if (price && price !== "-") {
            return price;
        }
    }
    return "";
}
