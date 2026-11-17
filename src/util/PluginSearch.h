#pragma once

#include <cstddef>
#include <string>

// On-device ("local") search for plugin catalogs that publish a whole list as
// one static file: a row matches when every whitespace-separated query word
// appears in its title or author. ASCII letters compare case-insensitively;
// other bytes (accented UTF-8) must match exactly. No allocation per row.
namespace pluginsearch {

inline char foldAscii(const char c) { return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c; }

// Case-insensitive (ASCII) substring test of word[0, len) in hay.
inline bool containsFolded(const std::string& hay, const char* word, const size_t len) {
  if (len == 0) return true;
  if (hay.size() < len) return false;
  for (size_t i = 0; i + len <= hay.size(); ++i) {
    size_t j = 0;
    while (j < len && foldAscii(hay[i + j]) == foldAscii(word[j])) ++j;
    if (j == len) return true;
  }
  return false;
}

inline bool matches(const std::string& query, const std::string& title, const std::string& author) {
  size_t i = 0;
  bool anyWord = false;
  while (i < query.size()) {
    while (i < query.size() && (query[i] == ' ' || query[i] == '\t')) ++i;
    const size_t start = i;
    while (i < query.size() && query[i] != ' ' && query[i] != '\t') ++i;
    const size_t len = i - start;
    if (len == 0) continue;
    anyWord = true;
    const char* word = query.data() + start;
    if (!containsFolded(title, word, len) && !containsFolded(author, word, len)) return false;
  }
  return anyWord;
}

}  // namespace pluginsearch
