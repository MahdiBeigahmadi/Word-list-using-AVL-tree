#include "Wordlist.h"
int main()
{
    Wordlist wordlist("tiny_shakespeare.txt");


    // Test cases
    /*cout << "Number of different words: " << wordlist.num_different_words() << endl; // Should print: 4
    cout << "Total number of words: " << wordlist.total_words() << endl;             // Should print: 7
    cout << "Most frequent word: " << wordlist.most_frequent() << endl;              // Should print: apple
    cout << "Number of singletons: " << wordlist.num_singletons() << " (" << (wordlist.num_singletons() * 100.0 / wordlist.num_different_words()) << "%)" << endl; // Should print: 2 (50%)
    */
    wordlist.print_words();
    wordlist.print_stats();
    return 0;
}
