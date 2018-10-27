class Solution {
 public:
  int scoreOfParentheses(string S) {
    int res = 0;
    std::stack<char> par_stack;
    bool flag = false;
    for (int i = 0; i < S.size(); ++i) {
      if (S[i] == '(') {
        par_stack.push(S[i]);
        flag = true;
      } else if (flag == true) {
        flag = false;
        if (par_stack.size() == 1)
          res++;
        else
          res += 1 * pow(2, par_stack.size() - 1);
        par_stack.pop();
      } else
        par_stack.pop();
    }

    return res;
  }
};
