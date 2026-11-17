#include <gtest/gtest.h>

#include "PluginSearch.h"

using pluginsearch::matches;

TEST(PluginSearch, MatchesTitleOrAuthorCaseInsensitively) {
  EXPECT_TRUE(matches("bones", "City of Bones", "Cassandra Clare"));
  EXPECT_TRUE(matches("CLARE", "City of Bones", "Cassandra Clare"));
  EXPECT_TRUE(matches("city clare", "City of Bones", "Cassandra Clare"));
}

TEST(PluginSearch, EveryWordMustMatch) {
  EXPECT_FALSE(matches("city stephen", "City of Bones", "Cassandra Clare"));
  EXPECT_FALSE(matches("glass", "City of Bones", "Cassandra Clare"));
}

TEST(PluginSearch, ExtraSpacesAndEmptyQuery) {
  EXPECT_TRUE(matches("  city   bones ", "City of Bones", ""));
  EXPECT_FALSE(matches("", "City of Bones", ""));
  EXPECT_FALSE(matches("   ", "City of Bones", ""));
}

TEST(PluginSearch, Utf8BytesMatchExactly) {
  EXPECT_TRUE(matches("café", "Café Society", ""));
  EXPECT_TRUE(matches("CAFé", "Café Society", ""));  // ASCII part folds, é must match
  EXPECT_FALSE(matches("cafe", "Café Society", ""));
}

TEST(PluginSearch, SeriesInAuthorSubtitle) {
  EXPECT_TRUE(matches("mortal", "City of Bones", "Cassandra Clare · The Mortal Instruments #1"));
}
