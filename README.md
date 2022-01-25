# CSD 319  **Assignment 1** 

​																	Made By  ~  Aryaman Singh Rana 

## Table of Contents

1. [Problem Statement](#Problem-Statement)
2. [Approach and Analysis](#Approach-and-Analysis)
3. [Net Time Complexity](#Net-Time-Complexity--)
4. [Improvement](#Improvement)
5. [Input and Output](#Input-and-Output)
6. [Full Code](#Full-Code)

## Problem Statement

### Input - 

The following integers are to be taken as input - 

 	- l (length of substring)
 	
 	- d (Edit Distance)
 	
 	- indel (Cost of Insertion and Deletion)
 	
 	- sub (Cost of Substitution)

### To execute - 

 Randomly generate 20 strings S1, S2 … S20 of length 600 each using alphabet set Σ.

- For each string i from 1 to 20 -
  -   For each substring **M** in string **Si** (where |M| = L):
      If a neighbour of M occurs in each of the other **19 strings**, then **output M**; (where a string **M’** is considered as a neighbour of M if Edit distance **(M, M’) <= D**).

**Edit Distance** - 
The cost is calculated as follows-
Given two string **X[1…p]** and **Y[1…q]**, the cost to transform string X into Y  in minimum operations is called as the **minimum edit distance of X**.  The transformations performed and its costs are as follows: 

| Cost of      |       |
| :----------- | :---- |
| Insertion    | Indel |
| Deletion     | Indel |
| Substitution | Sub   |


Approach to be applied - **Dynamic Programming**

Create a matrix E[0…p] [0….q].(where E[i,j] represents the number of transformations required to convert X[1...i] to Y[1…j].) 
The following parameters are used - 

* E[i,0] = i for each 0 ≤𝑖≤𝑝.
* E[0,j]=j for each 0 ≤𝑗≤𝑞.
* E[i,j] = minimum of { 𝐸[𝑖−1,𝑗] + 𝑖𝑛𝑑𝑒𝑙 , 𝐸[𝑖,𝑗−1] + 𝑖𝑛𝑑𝑒𝑙 , 𝐸[𝑖−1,𝑗−1] + { 𝑖𝑓 (𝑋[𝑖]=𝑌[𝑗]) then 0 ; else if (𝑋[𝑖]≠𝑌[𝑗]) then sub)

The value at **E[p,q]** will give you the **Edit Distance**.

### Output -

    Array of M - (All substrings which have neighbours in 19 other strings)



---

# Approach and Analysis 

I solved this problem, by coding the following program in **C++** language. (The full code can be found at the end of this PDF.)

I've divided the code into sections for explanation-


| Section   | Description                         |
| :-------- | :---------------------------------- |
| Section 1 | [Global Definition](#Section-1)     |
| Section 2 | [int Main()](#Section-2)            |
| Section 3 | [void fastIO()](#Section-3)         |
| Section 4 | [void solve()](#Section-4)          |
| Section 5 | [void randomStringG() ](#Section-5) |
| Section 6 | [int checkMinDist()](#Section-6)    |

---

### Section 1

Basic definition of global variables and typedefs to be used during the execution of the program.

####    Code-

```cpp
#include <bits/stdc++.h>
#define ll long long int
#define pb push_back
using namespace std;

// using global variables here to store the necessary values
vector<char> seedA = {'A', 'C', 'G', 'T'}; // seed value for generating random string
vector<string> strA;                       // stores the 20 randomly generated string
vector<string> answer;                     // stores the output
int strLength = 600;
```

#### Time Complexity - NIL

---

### Section 2 

The **int main** is used for all input and output related operations.

* srand - is used to make the seed value for random variable as current time. Hence, the chance of same random values being generated is removed.
* freopen - is used to designate input and output files
* fastIO() -
* solve() - is where the main logic exists

####    Code-

```cpp
int main()          // input and output are handled here
{
    srand(time(0));
    freopen("Data.txt", "r", stdin);
    freopen("Out.txt", "w", stdout);

    fastIO();

    int l, d, indel, sub;                   // input
    cin >> l >> d >> indel >> sub;

    solve(l, d, indel, sub);

    for (int i = 0; i < answer.size(); i++) // output
        cout << answer[i] << "\n";

    return 0;
}
```

#### Time Complexity - O(n). (where n = size of answer array)

---

### Section 3 

It is said that in C++, a programmer should use scanf/printf for taking input and output as it takes less time than cin/cout. But by writing the fastIO() code, we achive the same speed while still using cin/cout.

- ios_base::sync_with_stdio(false) - is used to toggle off the synchronization of all the C++ standard streams with their corresponding standard C streams.
- cin.tie(NULL) - is used to make sure output is flushed into the system before taking any more inputs

####    Code-

```cpp
void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}
```

#### Time Complexity - NIL

---

### Section 4 

The **solve** is where the main loop works. 

* First for-loop - is used to generate 20 random strings of length 600 each. Then make substrings of length L and store it in a 2D vector/array.  
* Second for-loop - is used to populate **subString vector** for all possible substring lengths (l-d to l+d). 
* Third for-loop - is  used to populate **fifString vector** with only substrings of  given length (l).  
* Fourth for-loop - It takes the first substring 'M' from S_i and finds if it has neighbours in the rest 19 strings. If yes, then stores it 'M' in the answer array. 
  * A small optimization code where whenever a neighbor of M is not found in any of the S_i, it will break of and not check for neighbor for the rest of S_i. This is a small optimization, but it saves time when the size is high.

####    Code-

```cpp
void solve(int l, int d, int indel, int sub)    // main function where the algorithm works
{

    for (int i = 0; i < 20; i++)                // using the random string generator to create 20 strings of length 600
        randomStringG();

    vector<vector<string>> subString;           // a 2D vector to store the substrings of length l-d to l+d
    vector<vector<string>> fifString;           // a 2D vector to store the substrings of length l only

    for (int i = 0; i < strA.size(); i++)       // populating the strString 2D vector with required substrings of variable length l-d to l+d
    {
        vector<string> temp;

        for (int j = 0; j < strLength - l + 1; j++)
            for(int k = l-d ;k <= l+d ;k++)
                temp.pb(strA[i].substr(j, k));
            
        subString.pb(temp);      
    }

    for (int i = 0; i < strA.size(); i++)       // populating the strString 2D vector with required substrings of length L
    {
        vector<string> temp;
        for (int j = 0; j < strLength - l + 1; j++)
                temp.pb(strA[i].substr(j, l));

        fifString.pb(temp);      
    }

    int a,b,i,j;

    for ( i = 0; i < fifString.size(); i++)         // to iterate through i-th row
    {
        for ( j = 0; j < fifString[i].size(); j++)  // to iterate through the j-th subtring present in i-th row
        {
            int checkCounter = 0;                      // initializing the variable which will count if the neighbour occurs in 19 other strings
                                                       // second double for loop for comparing the main sub-string with 19 other S(i)'s substrings.
            for ( a = 0; a < subString.size(); a++)    // to iterate through a-th row
            {
                if (i != a)
                {   int flag =0;
                    for ( b = 0; b < subString[a].size(); b++) // to iterate through the b-th subtring present in a-th row
                    {
                        if (checkMinDist(fifString[i][j], subString[a][b], indel, sub) <= d) // checking the required minimum distance with given constrain
                        {
                            checkCounter++;
                            flag++;
                            break;
                        }
                    }
                    if(flag == 0)                       // a little logic which helps in boosting the run time
                        break;                          // basically when every a neighbour is not found in any of the 19 strings, it breaks and does not check for the rest of the code.
                }
            }
            if (checkCounter == 19)
                answer.pb(fifString[i][j]);  // pushing the string M into the output vector if we get the neighbours in all 19 strings
        }
    }
}
```

#### Time Complexity - 


| Loop       |       Time Complexity        | Given Value                                                  |
| ---------- | :--------------------------: | :----------------------------------------------------------- |
| for-loop 1 |             O(n)             | n = no. of strings (here 20)                                 |
| for-loop 2 |         O(n x m x l)         | n = no. of strings(here 20), m = no. of sub strings (here 585), l = no. of different lengths of substring(here in between l-d to l+d) |
| for-loop 3 |          O(n  x m)           | n = no. of strings(here 20), m = no. of sub strings (here 585) |
| for-loop 4 | O(n^2  x m1 x m2  x d1 x d2) | n = no. of strings(here 20), m1 = no. of sub strings (here 600 - l), m2 = no. of sub strings of length(in between l-d to l+d), d1 = size of substring(string1), d2 = size of substring(string2) |

Overall complexity of section 4 - **O(n) + O(n x m x l) + O(n x m) + O(n^2  x m1 x m2  x d1 x d2)**  = O(n^2  x m1 x m2  x d1 x d2)

---

### Section 5 

Used to create random strings using the rand function and seed characters.

####    Code-

```cpp
void randomStringG()    // a function to create a random string of length 600
{
    string temp;
    for (int i = 0; i < strLength; i++)
        temp = temp + seedA[rand() % 4];
    strA.pb(temp);
}
```

#### Time Complexity - O(n) where n = size of requires string (here 600)

---

### Section 6 

Used to check for the minimum edit distance using dynamic programming.

####    Code-

```cpp
int checkMinDist(string str1, string str2, int indel, int sub)  // function to check the minimum edit distance
{   
    if(str1 == str2)
        return 0;
    
    int strlen1 = str1.size(), strlen2 = str2.size();

    vector<vector<int>> minDistDP(strlen1 + 1, vector<int>(strlen2 + 1, 0)); // initializing the dp vector here with 0

     // initializing the dp vector
    for (int i = 0; i <= strlen1; i++) // first base condition
        minDistDP[i][0] = i;

    for (int i = 0; i <= strlen2; i++) // second base condition
        minDistDP[0][i] = i;

    for (int i = 1; i <= strlen1; i++)	// filling the dp
    {
        for (int j = 1; j <= strlen2; j++)
        {

            if (str1[i - 1] != str2[j - 1])
                minDistDP[i][j] = min(min(minDistDP[i - 1][j] + indel, minDistDP[i][j - 1] + indel), minDistDP[i - 1][j - 1] + sub);
            else
                minDistDP[i][j] = min(min(minDistDP[i - 1][j] + indel, minDistDP[i][j - 1] + indel), minDistDP[i - 1][j - 1]);
        }
    }

    return minDistDP[strlen1][strlen2];
}
```

#### Time Complexity - O(n x m) where n = size of sub-string 1, m = size of sub-string 2

---

## Net Time Complexity - 

| Section   | Description                    | Description                                                  |
| --------- | ------------------------------ | ------------------------------------------------------------ |
| Section 1 | NIL                            | 0                                                            |
| Section 2 | O(n)                           | 20                                                           |
| Section 3 | NIL                            | 0                                                            |
| Section 4 | O(n^2 x m1 x m2 x str1 x str2) | 20 x 585 x 20 x (variable  number of sub-string length) x (strlen1) x (strlen2) |
| Section 5 | O(n)                           | 600                                                          |
| Section 6 | O(n x m)                       | 15 x m(variable sub-string length)                           |

#### Overall complexity -  **O(n^2 x m1 x m2 x str1 x str2) + O(n x m) + O(n) +O(n)** 

#### 								=   O(n^2 x m1 x m2 x str1 x str2)

---

## Improvement

The first improvement  that can be made to my code is -  Since I've used a **Brute Force Approach**, there are many duplicate values being generated and tested. For example - 

```
In the first string s1, the substrings formed are - 
m1_1 m1_2 m1_3 m1_4 m1_5 .......

m1 will be choosen and be used to test for neighbours against rest of the S array string.
So lets take s5 string -
m5_1 m5_2 m5_3 m5_4 m5_5 .......

Here, at first m1_1 will be compared with m5_1 for neighbourhood, then m1_1 with m5_2, then m1_1 with m5_3, .... and so on. - (1)

Now, after string s1,s2,s3,s4 are checked completely, now comes turn for s5.

Here, m5_1 will be compared with m1_1 for neighbourhood, then m5_1 with m1_2, then m5_1 with m1_3, .... and so on.

From (1), we see that these operations are again repeated, which decrease the efficiency of the program.
```

This is the place where I see that I can significantly improve my codes run time and make it more efficient.
To do this, one can use a better data structure to store the value of valid neighbors of a substring. 

    For example- 
    We store the all values of m1_1 neighbours in a map.
    Assuming that m1_1 is neighbours with m5_2 and m5_3.
    We store this in map with key being m1_1 and value being m5_2 and m5_3 respectively.
    So when the loop reaches to string m5_2, we can just check in the map for m1_1 if it exists there. 
    If yes then we do not check the minimum edit distance(which increase efficiency)
    else we check the minimum edit distance and input the same in the maps.

In this way, we can mitigate finding minimum distance repeatedly for strings. This is one of the optimizations that my code can take(although on the cost of space complexity).


---

## Input and Output

### Test Case 1

Input -
	

	15 5 1 1

Output - 6000 - 7000 Strings

	ATAGAAGGGGTTGTC
	TAGAAGGGGTTGTCA
	AGAAGGGGTTGTCAG
	.
	.
	.
	.
	.
	GACGCTCCGGCGAAC
	ACGCTCCGGCGAACA



### Test Case 2

Input -
	

	15 5 1 2

Output - 0 - 15 Strings

    GGAAACATTGTAGCG
    GAAACATTGTAGCGA
    AAACATTGTAGCGAC
    ACATTGTAGCGACGT
    CATTGTAGCGACGTT
    ATTGTAGCGACGTTC
    TTGTAGCGACGTTCA
    TGTAGCGACGTTCAA
    GTAGCGACGTTCAAT

---

