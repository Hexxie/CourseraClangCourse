#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

bool operator==(const Region& lhs, const Region& rhs){
    return tie(lhs.names, lhs.parent_std_name, lhs.population, lhs.std_name) ==
        tie(rhs.names, rhs.parent_std_name, rhs.population, rhs.std_name);
}

/**
 * @brief Return max number of repetitions
 *
 * @param regions base with region
 * @return int max nr of region repetition
 */
int FindMaxRepetitionCount(const vector<Region>& regions)
{
    vector<int>nr_repetitions;
    int max_repetitions = 0;
    int repetition = 0;

    if(regions.size() == 0)
    {
        return 0;
    }

    //Create a vector with repetitions for each member
    for(int i = 0; i < regions.size(); i++)
    {
        repetition = 0;
        for(int j = i; j < regions.size(); j++)
        {
            if(regions[i] == regions[j])
            {
                repetition++;
            }
        }
        nr_repetitions.push_back(repetition);
    }

    //Find max nr of repetitions in the vector with repetitions
    for(auto item : nr_repetitions)
    {
        if(item > max_repetitions)
        {
            max_repetitions = item;
        }
    }

    return max_repetitions;
}

int main()
{
cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;

  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;

  return 0;
}