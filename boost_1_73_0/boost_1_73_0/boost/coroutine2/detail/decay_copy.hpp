
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_DECAY_COPY_H
#define BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
947d1yxN8mScTDLvRmrjTNGf4c1sEnmBqL1/PPi/3KzhUWa4+DDYz0x6T7CPaVDKdjRAob3p/kKlJxPnNDrcje9vgms7bZ6o7vGcPghpyXipqcPRM+y+4g4cEf71gpq504ZfwngSXsSTOF94Id+QrXb2NMrn6RS+hJN5hAoxOEq1Szoqks9uxyCLIggnWYIz4CKF15QCA9QKsuP9B1BLAwQKAAAACAAtZ0pSG6qDVfYFAACQDAAALwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfRlRQUE9SVC4zVVQFAAG2SCRgrVZtb9s2EP7OX3HwPiQpHNlO2qbJumJu4qxeHdvwS7tgGQRaoiw2MimQVBxj3X/fHSk3Tlqg/VAHsSSK99zdc88dHd004NlP+7CI4OC7n9j/x/jB69ZobPQnkbhvG8TxZwh/aHiD1x9w1YIHq8/xAfyQ1WfY91Zx7es13cfxD7i7oSDpq0XGNzHd4kqwrO3Pdbkxcpk72D8/gM7p6Ss4hKN256QJF1xJUcDUCbUQZtmE16lf+T3n9/eRFW+aIBzwInoEOMulBaszt+ZGAN4XMhHKihS4hVTYxMgFPkgFLheQyULA+Wh83R/+0YR1LpO8xtnoCmyuqyKF
*/