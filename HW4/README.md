Hello, this is TA of CSED331.

The grading of your Homework4 has been completed.

The average is 8.83 and the stdandard deviation is 4.16.

Scoring criteria:
Problem 1:\
No definition of a subproblem(-1)\
No recurrence relation(-1)\
No base case(-1)\
Problem 2:\
Time complexity analysis(-1)\
Slower than O(n^3)(-2)\
Problem 3:\
Wrong algorithm (-3)\
Wrong or no time complexity analysis and minor error (-1)\
Problem 4(a):\
Wrong algorithm (-3)\
Similar algorithm but counterexample exists(-2)\
Wrong or no time complexity analysis and minor error (-1)\
Problem 4(b):\
Wrong algorithm (-3)\
Similar algorithm but counterexample exists(-2)\
Wrong or no time complexity analysis and minor error (-1)

김관호 20190650 Homework4 score: 13/15\
Problem 1: 2/2       
Problem 2: 3/3       
Problem 3: 2/4      
-L[i][j] stores the maximum value which can be obtained by selecting 'LEFT' direction whenever we can. (R[i][j] stores similarly) Here, dp[i][j] = max(L[i][j], R[i][j]) means that dp[i][j] store the better solution among 1) selecting 'LEFT' as many as we can, and 2) selecting 'RIGHT' as many as we can. But how can we let dp[i][j] store a zig-zag path(At some rows, we want to go left. But at some other rows, we want to go right)?\
Problem 4(a): 3/3       
Problem 4(b): 3/3       