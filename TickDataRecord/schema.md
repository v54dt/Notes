# Database Schema Design Notes

Recording design ideas and thought processes.

## Idea 1: Time Recording Method for K-bar Data Conversion

### Problem Background
Different products have different market opening times. For example, CDF post-market trading starts at 17:20. When converting tick data to K-bars with different time intervals, the traditional approach requires storing the market opening time for each product in an extra table.

### Solution
Instead of only recording absolute time, calculate and store the offset (time elapsed) from market opening for each data point.

### Benefits
1. **Support for arbitrary time intervals**: Can support various K-bar lengths, such as 59-minute, 33-minute, and other uncommon intervals
2. **Simplified product management**: No need to record market opening times for each product individually
3. **Enhanced flexibility**: The same data structure can be applied to all products and time intervals