// Copyright 2019 Henry Schreiner
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ALGORITHM_EMPTY_HPP
#define BOOST_HISTOGRAM_ALGORITHM_EMPTY_HPP

#include <boost/histogram/fwd.hpp>
#include <boost/histogram/indexed.hpp>

namespace boost {
namespace histogram {
namespace algorithm {
/** Check to see if all histogram cells are empty. Use coverage to include or
  exclude the underflow/overflow bins.

  This algorithm has O(N) complexity, where N is the number of cells.

  Returns true if all cells are empty, and false otherwise.
 */
template <class A, class S>
auto empty(const histogram<A, S>& h, coverage cov) {
  using value_type = typename histogram<A, S>::value_type;
  const value_type default_value = value_type();
  for (auto&& ind : indexed(h, cov)) {
    if (*ind != default_value) { return false; }
  }
  return true;
}
} // namespace algorithm
} // namespace histogram
} // namespace boost

#endif

/* empty.hpp
SzBXUUz9snTAM720w8Db1Ost4P3lhfNLwZBRg0zUmCh+c3a9P3d2nn1SbpBmZfwTzTG+s49RE/t9krxHSk6xi2vO4zR54wnc0sY2mN0VoXB4acy9rM+L29M/ERLfJQ4V2xr8BCRT2Soh/u5HQlo843MdrvFZPtjekmX6i/yvYsKGfKSLYF2uJFR5r+LTeE0lr7nEImnFRfaRg5yy9SSXKb8f7TgZGcVjct7UQqkLwoG3a9nY2Yn0JdWvv+jdtF0V2BT9gtboFcilCkZGM8l1RVV/aXDwZB5kz2CJ+/fknHkevXeps5wOeM8wx4TnlSbXCvdKIAG0ARQovg7ZTno0pF/O+smd1D44GlCl7K5SEDraYfEF79HxlGO6GVctUxMO6O9gfhww2sFLMsIgoIcBjPyeCquQv21TAfwlekO6g2u3G3YdzlSgXRnwqNMvums0w/jinU69l6cRxyKBYc4VSV+nW4nZtkzuHvm+G3CMoWecqEWREr5gXLHM7B7uV6AOoOAVp7vCffJ6l9vSVFS+qQwLN7pByUPca7ItZq7fYn8ZT/obpZqDTgMBvx45sU/VFIfFZCx75eg3ADUpHs05QoUQjfIdILw3/ThDVb8OqD78nd2AMZ0fq+UXzd7I76HmGM387uQCuLxwYxLzqdZfcPKgc8xUsZqWTxwDefgYJTMGor5SAHJih/JUp0JSVj/4XTD1Log/gEa8+xhe
*/