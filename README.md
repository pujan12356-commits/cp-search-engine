# CP Search Engine

A search engine built from scratch in C++ to explore how modern search systems work internally.

The project processes text documents, extracts useful keywords, and builds data structures that allow efficient searching. The goal is to implement the core components of a search engine rather than rely on existing libraries.

## Current Progress

* Document representation
* Text parser
* Tokenization
* Stop-word removal
* Case-insensitive text processing

## Planned Features

* Inverted index
* Keyword search
* TF-IDF ranking
* Query caching
* Spell correction

## Project Structure

```text
documents/
src/
├── Document.h
├── Parser.h
├── InvertedIndex.h
└── main.cpp
```

## Example

Input:

```text
The graph is in the tree and the binary search
```

Output:

```text
graph
tree
binary
search
```

## Motivation

Search engines are a good way to learn about data structures, text processing, indexing, ranking algorithms, and systems design. This project is being built incrementally, with each component implemented from scratch in C++.

