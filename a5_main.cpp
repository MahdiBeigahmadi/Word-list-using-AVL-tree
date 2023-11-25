
#include "Wordlist.h"
Wordlist lst;

void read_from_terminal(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error loading the file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        size_t start = 0;
        size_t end = line.find(' ');

        while (end != string::npos)
        {
            string word = line.substr(start, end - start);
            if (!word.empty())
            {
                lst.add_word(word);
            }

            start = end + 1;
            end = line.find(' ', start);
        }

        string lastWord = line.substr(start);
        if (!lastWord.empty())
        {
            lst.add_word(lastWord);
        }
    }

    file.close();
    lst.print_stats();
    cout << endl;
    lst.print_words();
    cout << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return EXIT_FAILURE;
    }

   ifstream file(argv[1]);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

    // Open a file to store the output
    ofstream out("output.txt");
    // Redirect cout to write to the output.txt file
    streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    read_from_terminal(argv[1]);

    // Reset cout to its original state
    std::cout.rdbuf(coutbuf);

    file.close();
    out.close(); // Close the output file stream
    return EXIT_SUCCESS;
}