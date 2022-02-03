#include <bits/stdc++.h>
#define ll long long int
#define pb push_back
using namespace std;

// using global variables here to store the necessary values
vector<char> seedA = {'A', 'C', 'G', 'T'}; // seed value for generating random string
vector<string> strA;                       // stores the 20 randomly generated string
vector<string> answer;                     // stores the output
int strLength = 600;

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

    for (int i = 1; i <= strlen1; i++)
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

void randomStringG()    // a function to create a random string of length 600
{
    string temp;
    for (int i = 0; i < strLength; i++)
        temp = temp + seedA[rand() % 4];
       
    strA.pb(temp);
}

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

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

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

    cout << "Total number of strings found: " << answer.size() << "\n";
    return 0;
}