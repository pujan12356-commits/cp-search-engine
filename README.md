# CPP Search Engine

This is a simple search engine built in C++ to understand how search engines work internally. Instead of using existing search libraries, I implemented the main components myself, including indexing, ranking, caching, and typo correction.

The project indexes a collection of text documents and allows users to search them through a command-line interface.

## Features

* Document loading from text files
* Tokenization and stop-word removal
* Inverted index for fast searching
* TF-IDF based ranking
* Boolean queries (AND / OR)
* LRU cache for repeated searches
* Spell correction using Edit Distance
* Interactive command-line search interface

## How it Works

### Document Loading

The engine reads text files from the documents folder and stores them as Document objects.

### Parsing

Documents are converted into tokens by:

* Converting text to lowercase
* Removing punctuation
* Removing common stop words

### Inverted Index

An inverted index maps each word to the documents containing that word.

Example:

graph -> [2]

dfs -> [2]

dp -> [1]

This allows queries to be answered without scanning every document.

### Boolean Search

The search engine supports:

graph AND dfs

graph OR dp

AND queries are handled using set intersection, while OR queries use set union.

### TF-IDF Ranking

For single-word searches, matching documents are ranked using TF-IDF scores so that more relevant documents appear first.

### LRU Cache

Recently searched queries are stored in an LRU cache. If the same query is searched again, the result can be returned directly from cache.

### Spell Correction

If a query does not match any indexed term, the engine suggests the closest word using Levenshtein Edit Distance.

Example:

grahp → graph

## Technologies Used

* C++
* STL

  * vector
  * list
  * unordered_map
  * set
* File I/O
* Dynamic Programming
* Hashing
* Information Retrieval concepts

## Example Queries

graph

graph AND dfs

graph OR dp

grahp

## What I Learned

While building this project, I learned how search engines organize and retrieve information efficiently. I also got hands-on experience with hash maps, caching, dynamic programming, file handling, and designing a multi-component C++ project from scratch.

## Future Improvements

- Generate the vocabulary automatically from the inverted index instead of maintaining a manual vocabulary list for spell correction.
- Support case-insensitive queries by applying the same normalization pipeline to both documents and user queries.
- Add phrase search support to allow queries such as "dynamic programming" or "binary search".
- Experiment with more advanced ranking algorithms such as BM25 and compare them with TF-IDF.
- Build a simple web interface on top of the search engine to make document searching more user-friendly.
