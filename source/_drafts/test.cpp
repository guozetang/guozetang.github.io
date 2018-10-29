class Solution {
public:
    int maxProfit(vector<int>& prices) {
      if(prices.empty()) return 0;
      int preMin = prices[0], curMax = 0, maxPrice=0;
      for(int i = 0; i < prices.size(); ++i) {
        if (prices[i] > curMax){
          curMax = prices[i];
          maxPrice = max(maxPrice, curMax - preMin);
        }
        
        if (prices[i] < preMin) {
          curMax = 0;
          preMin = prices[i];
        }
      }
      return maxPrice;
    }
};