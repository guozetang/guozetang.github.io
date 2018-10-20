class Solution {
public:
 bool checkInclusion(string s1, string s2) {
 int n1 = s1.size(), n2 = s2.size();
 vector<int> vec1(127), vec2(127);
 for(int i=0; i < n1; ++i) {
 vec1[s1[i]]++;
 vec2[s2[i]]++;
 }
 
 
 if(vec1 == vec2) return true;
 for(int i = n1; i < n2; ++i) {
 --vec2[s2[i-n1]];
 ++vec2[s2[i]];
 if(vec1 == vec2) return true;
 }
 return false;
 
 }
};