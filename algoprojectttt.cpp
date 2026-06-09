#include <bits/stdc++.h>
using namespace std;

// Convert text to lowercase
string toLowerCase(string text)
{
    for(char &c : text)
    {
        c = tolower(c);
    }
    return text;
}

// Remove punctuation
string removePunctuation(string text)
{
    string cleaned = "";

    for(char c : text)
    {
        if(isalnum(c) || c == ' ')
        {
            cleaned += c;
        }
    }

    return cleaned;
}

// Read file content
string readFile(string filename)
{
    ifstream file(filename);

    if(!file)
    {
        cout << "Cannot open file: " << filename << endl;
        return "";
    }

    string line;
    string text = ""; 

    while(getline(file, line))
    {
        text += line + " ";
    }

    file.close();

    return text;
}

// Split text into words
vector<string> splitWords(string text)
{
    vector<string> words;

    string word;

    stringstream ss(text);

    while(ss >> word)
    {
        words.push_back(word);
    }

    return words;
}

// Remove stop words
vector<string> removeStopWords(vector<string> words)
{
    vector<string> result;

    vector<string> stopWords =
    {
        "the","is","are","am","was","were",
        "a","an","of","to","in","on",
        "for","with","and","or"
    };

    for(string word : words)
    {
        bool stop = false;

        for(string sw : stopWords)
        {
            if(word == sw)
            {
                stop = true;
                break;
            }
        }

        if(!stop)
        {
            result.push_back(word);
        }
    }

    return result;
}

// Word-by-word LCS
int LCS(vector<string>& a, vector<string>& b)
{
    int n = a.size();
    int m = b.size();

    vector<vector<int>> dp(n + 1,
                           vector<int>(m + 1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(a[i - 1] == b[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] =
                max(dp[i - 1][j],
                    dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

// Similarity calculation
double calculateSimilarity(vector<string>& a,
                           vector<string>& b)
{
    int lcsLength = LCS(a, b);

    if(a.size() + b.size() == 0)
        return 0;

    return (2.0 * lcsLength /
           (a.size() + b.size())) * 100;
}

// Prepare document
vector<string> processDocument(string filename)
{
    string text = readFile(filename);

    text = toLowerCase(text);

    text = removePunctuation(text);

    vector<string> words = splitWords(text);

    words = removeStopWords(words);

    return words;
}

// Compare two files
void compareTwoFiles()
{
    string file1, file2;

    cout << "\nEnter First File: ";
    cin >> file1;

    cout << "Enter Second File: ";
    cin >> file2;

    vector<string> doc1 =
        processDocument(file1);

    vector<string> doc2 =
        processDocument(file2);

    double similarity =
        calculateSimilarity(doc1, doc2);

    cout << "\n===== RESULT =====\n";

    cout << "Similarity: "
         << fixed
         << setprecision(2)
         << similarity
         << "%\n";

    if(similarity > 80)
        cout << "Status: Possible Plagiarism\n";

    else if(similarity > 50)
        cout << "Status: High Similarity\n";

    else if(similarity > 20)
        cout << "Status: Moderate Similarity\n";

    else
        cout << "Status: Low Similarity\n";
}

// Compare one file with many files
void compareMultipleFiles()
{
    string mainFile;

    cout << "\nEnter Main File: ";
    cin >> mainFile;

    vector<string> mainDoc =
        processDocument(mainFile);

    int n;

    cout << "How many files to compare? ";
    cin >> n;

    vector<pair<double,string>> results;

    for(int i = 0; i < n; i++)
    {
        string fileName;

        cout << "Enter File "
             << i + 1
             << ": ";

        cin >> fileName;

        vector<string> otherDoc =
            processDocument(fileName);

        double similarity =
            calculateSimilarity(
                mainDoc,
                otherDoc
            );

        results.push_back(
            {similarity, fileName}
        );
    }

    sort(results.rbegin(),
         results.rend());

    cout << "\n===== RANKING =====\n";

    for(int i = 0;
        i < results.size();
        i++)
    {
        cout << i + 1
             << ". "
             << results[i].second
             << " -> "
             << fixed
             << setprecision(2)
             << results[i].first
             << "%\n";
    }
}

int main()
{
    int choice;

    while(true)
    {
        cout << "\n";
        cout << "===== SMART PLAGIARISM CHECKER =====\n";
        cout << "1. Compare Two Files\n";
        cout << "2. Compare Multiple Files\n";
        cout << "3. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        if(choice == 1)
        {
            compareTwoFiles();
        }
        else if(choice == 2)
        {
            compareMultipleFiles();
        }
        else if(choice == 3)
        {
            cout << "Program Ended.\n";
            break;
        }
        else
        {
            cout << "Invalid Choice.\n";
        }
    }

    return 0;
}