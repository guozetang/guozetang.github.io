class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
      unordered_map<int, int> numsMap;
      vector<int> result;
      result.reserve(2);
      
      for(int i = 0; i < nums.size(); ++i) {
        numsMap[nums[i]] = i; // Each input would have exactly one solution.
      }
      
      for(int i = 0; i < nums.size(); ++i) {
        const int diff = target - nums[i];
        if(numsMap.find(diff) != numsMap.end() && numsMap[diff] > i) {
          result.emplace_back(i);
          result.emplace_back(numsMap[diff]);
          return result;
        }
      }
      return result; 
    }
};