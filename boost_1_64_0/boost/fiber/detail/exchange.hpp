
//          Copyright Oliver Kowalke 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_EXCHANGE_H
#define BOOST_FIBER_DETAIL_EXCHANGE_H

#include <algorithm>
#include <utility>

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T, typename U = T >
T exchange( T & t, U && nv) {
    T ov = std::move( t);
    t = std::forward< U >( nv);
    return ov;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_EXCHANGE_H

/* exchange.hpp
SBBzL+lwxSPZNr0kbrjtqPsSCQYNnuqQ/ljuNfCzb9rsZLF9XfNJ0C4w2QsJL0KhwIszjJTv/pL9QOS1kYhwWvJBiHE+VWQWge9Wh8NF2YmIqYixa07bx12LmWg9ar5WoJ3ryJM9bfgkI4uCGSMBHHm7kTXNy7xZS6S6rAgDXbiUNPRJfN5YNMvngm3plbY551ewYe6ndz/IXRmY5P3YzrCdjgRxwQzmX8PPIjhpoLIYseTtZZzWWk7A69jpy0FFTKur3+ywm6WUx/oq1ocCXHdt1cRgLXWeaSBgPOD4p6iCQ77Woz5TD+BLgS3WLuyEy3nri/e0IQK2+B+Pu9waye7EKS6cGXt6Cq0vdeSHSl4wOrT0hawvA/3Alm4J+DLjIdsfnYwQ/IJzu+8A5tk0sDjs19zn73jENQUGoqEyOIKTWyw5+PjaBhjIy/RZKedSMf9TsFrR3VKCyG1qB8N4iwQsKA+PjOPkN0fofO4nzKM770d8/Vdw2E4und/qIk2plBsbb0kVgOuJK1hPmyDZhuOwR33NHMG1iGxIouPYbzMR8WGBGGrIQqUecQ==
*/