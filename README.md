# WordSearchEngine

This project has the objective of creating and comparing various implementations of a program that reads and analyses text files, and then allows the user to search for instances of a word that might exist in those text files.

### wts.out
This implementation is the most basic one, in which the user inputs a word and the program individually checks every word of every text file. This becomes quite troublesome when the user is planning on searching several words, which means the program must iterate over each text file multiple times.

### wts2.out
This implementation fixes the above problem, initially it uses the following data structures:
```
typedef struct{
	int fileIdx;
	int line;
	long offset;
} Occurence;

typedef struct{
	char *word;
	int count;
	Occurence *occur;
} Word;

typedef struct{
	Word *words;
	int used;
	int allocated;
} Index;
```
To store words in an array of dynamic size, each word has to it associated an array of occurences of dynamic size.
With this system in place the search for a word boils down to iteration over each word in the array of words until one that matches the word value is found, this way we only analyse the text files once for various searches. While this works a lot better than the previous implementation there are still some serious optimizations we can do.

### wts3.out
This implementation focuses on shortening the search time by ordering the word array alphabetically and using the C standard library functions qsort and bsearch to sort and find words respectively.

### wts4.out
This implementation uses the concept of _binary tree_ to shorten greatly the search for words.

### wts5.out
This implementation uses a mix of the concept of _hash table_ and _linked list_ to allow for a better and more efficient search engine.
