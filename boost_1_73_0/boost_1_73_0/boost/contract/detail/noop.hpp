
#ifndef BOOST_CONTRACT_DETAIL_NOOP_HPP_
#define BOOST_CONTRACT_DETAIL_NOOP_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Following must be expressions, not statements (as used with if.., etc.).

#define BOOST_CONTRACT_DETAIL_NOOP ((void)0)

// Following always compiles but never evaluates cond (so check correct syntax).
#define BOOST_CONTRACT_DETAIL_NOEVAL(cond) \
    (true || (cond) ? BOOST_CONTRACT_DETAIL_NOOP : BOOST_CONTRACT_DETAIL_NOOP)

#endif // #include guard


/* noop.hpp
jLfA44xPap6E4y0Mf0HNBh8VYcDYDgbfgOOzcMTh8Xk44jV+QeSHAwbvMhA5qKPgtpRqO1m1Dai2c1Tb+aptk2q7QrX9XrXdrdoeVW2Pq7ZXVNtrqu0j1fa/qq0R6m8G2bwCOdgqm8L7iU3h2SoKWUXXQayitohVtDr7wEhdr/LCOs+jO4KjIvh7OCHuORI8Hayin3uG8jXP6arndNWzkntOLGITu+DdPoJNrC1kE6tHk7dNbd6MhmXu/T3Vu54=
*/