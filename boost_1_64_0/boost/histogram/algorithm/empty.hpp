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
+pKIVwbQptsl7k+6Hs3CpPgHkcwqZ85tzSxWf3ws7KIlXN6bR98JQhHVH6h1brNGo1FbeaihJCtSyrTUwBmzP4edoblIDaZomCS2AgXR6acVkNiym0uMkVUGE+FwJjGMT4V+9aQLiT3NGnnF2o3ALHswCe4ZOtnlpp1x+pIlU2LDSfmx4YppseExcfnXx9W3Y3JMOHwRbeytYYh6INMWY5Ja5d0U4RLfwQauCinv3lTYobw7AHinNK0MH9MbIRpNqEb/BmpTYBzBkj2+0n1yb1uY8HwxqqeIx84ca3MioYXH9RksK/J9F9ihb6znrW99evTSads/yjOzv+SQOko/3e/86d+fHpvO7SM+uXu7CMjwUpqmnmsfXtjbnhzUSXgpInC6M/BShHq2M/BSxOxBnwAv5EnrGB6cvqPv+dOXlbSFF8Xvs3cML3tTz4/bh5cd29/ATsLLLspOdQZedpF7pjPwsotBAz8JXuDwUzuEB6d/7xPSJxa3hRfF/yq5Y3g5m9460z68sK7nD+gkvJxiSEtn4OUUttOdgZdTHEn7JHjhjnOfDuHB6d5PSLcXtYUXxX8jqX140VULkTxZZzGnS285vktYSzXMJf7AIGB9lkskRcxcknBY6D2YRwM9nv8l8hBFj1GLMs5v146qY79mwjWU70mtjdbQWcUV+hMWfyzRWfrB8vH0vX0MxVAPmNqvoIbeOykbanGLJ7gjSvvKMUmf3TDh5KBxXx+mOSq97EdM+nTsseS9UNtrRPpTxBjeeFO1FhjmpFaH1yYR+5fA7B/9svAvxNsQIoeb9WVUVTdQUw+Kw8gmAT9douhi3tTx8s5E/gUCd393Hgz7+Pj09yuZxY/q/OZeBkuWyN1bVO+i6Kp+ZBLkolMe70JX9+N+SKw/31SAtdwn5l6uw3+dccDpLyZj3w0SVlzjDXvI8NWw7mdOgbN8D5MfZOXnVPiGFAMQlLM2hk4UxEyI14vogERx6ajExECm0AVuYNCNNLE9TsiJ3VvhFtow/X5H52/XSHq51Czn27DfmozTAWbeMI/N2Qek96AhTZA95Q5EsWLv6hLJ4hSa6AjwGKLZSQqdrEMIjB/kc4o38zCCQoUyfEu/QOYTP5wmAeaoosd+2FOPeK2frMxKWavZKu+0AZ+14mgBGX7BRHI2mOtxZWJkkgHPy8GUuRtNVpTAr+A8JWcf3GeJnw00YDUg0Kj4bysHwFYSwPYfP2ZcR6NxVZSJwRiZW0zNgM8jsSNTviSNHMC1K+tz9jW//sIX+JHykzcvkTaYtHqfRgzg51Ucs4/iLLJ2TNSlOywX/bataiW5gfgWae/eHh19oU6FfZvi1p2MZrMZSS+ufQxdGEIGh4uds6i3sDuwZidCmULtZchbMrwJXum0hhcJ5335I4JRiuF3rfCURrrDlNYuTJfbEGjIp7gL3N6n6ZnxsfznkbTY8I/i0tfE6cueSWtjD8TnIWbc+aTV9cNj+lBLYJMIW6bh3gR1zb09nZR4g6SLgZYEP/mN47i9HxgF+iDniFtlzmmRnD4+zTVau2LmOiuXkJ+o9zCpyolYr9756oZv93HS4eV4bwQXcNAt3uW1nhZftTxPGRDX38cUd6UYd2LhUL2UxqEuQC3UhmuUfqZd36leszc8eQlRVNKawzp3qWl6ZRauLNWoTAcY04IlifqCrHyn0dql05Apg5//EXBvLXeZpXeetJpQ1j8Kl3UBEiLNLx8+ZriYc9z+W9BsDxKoM48xktrzGv3ZmnUSNem44xUzvqvMyBVoUdanOqquQgT61B3TVtkz0GJxVJHBpbxRUA/7e3bohBVkoRpnZhp2p2jKZyZPjknsuOIV3c59MeK4Z9w=
*/