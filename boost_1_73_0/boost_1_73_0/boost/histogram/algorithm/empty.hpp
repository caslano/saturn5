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
M1IijqEKYpFQxmVBbhmZDnNRCm+jnC9KJootbVZyvcOIEELJosgSmEEIwBNKBLhDRRKKTPPqRVcWymjq0D6xJQ++hiQTeELPuy4N3ed07atIdejDcP5ucjmnD93ZrDuef6LJGXXHn6Dr/XDcx35HsJSRuEszoWA5o2idxpEItcG/7lOm5noNL0OxiBIEcgFrvH/UCj8v09T54Oe59fNRW/N2lSrWYEIGNZE4RZL6wQ1WqQU28JpimSwtnXaJD07IDG3BG0zPFdJ4dDY+uUccBMywfO5nUbLkKH2Ikt/unI9TLJFm4ksRYenY47BD2VpvJge/UIUfk8qLxcLEvq+9pvlk2h/OKrVREsRFyHp1Fpudalx03w/OhqMBndCFfyM0NfzcmJz+7rHsCen1NrTaswgGZZFTtIBN1uTTZRLdWXF0I1A7SD3eFZ/6ExcZuF6zg1GCRMGO4RtKokUivlDroAUHQ84HKOlNLi66476Na+eg5b4bjEbtdqdGbTeI9gpe9O3Bx0FdyFBYYL/I3+DaI0MVyQgRMtK7HA8/evo5AnCo6SJBBTaqq/mux9qsPhQpHokkr5av9Cbd+pnSizf+7Fhodw7ZMhcQzJxQkJLFhvqD0WDO24KN1oSL97whIKxvwigDYXZREjQHWUzr
*/