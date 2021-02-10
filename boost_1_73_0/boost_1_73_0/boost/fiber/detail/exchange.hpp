
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
1Pkc/GZiXvjJJJ5G6TQMLFPy/na64CVWJ+dNg9OONXdaS1jzyzSNkv4SDjRcPe5JKtZUuJYVEawsgZazRmnNIQ6arq6PtPJYQ7SAtJTQZ9+2ZEXxqG/T4WBo8iW1zEDgYkVMc+MAEE/JcyHp2pYL7bO3kqa77ci/th2wL/zYNg1k+8EnG5PTMUiLksuJuWfBseX0Pcw8wVy/UtqaQu1SFBx7B0ip74Js91wgU1bPlGtoRKbTcBLOEmuup9oGZf6UKmPjf/Guo5lvuU1p9fUyQvv9STVZw9QIK8PKkd48gL8s+Hex9cZjkXHBi+6GF70n2FDUzflqbKOnF+FGI08cmHxfj9Tqmvhxih5y7ONGuS1d/Tc4ihPRupj/B9rr2tT79VDERV6S3OBEsuVZLqjqwfiyVw+ct1pVfTH2vec1JU3X7o7+ttySmTJ7n73pzPswnU3TheUVRf9/rR8nxiD203kcwGdvNvetmCqc1tLk52fhFbAS0lmi+0/ulO0Mp/PgKghvgiw07aotUbgODlFrQM/TLPyYXfvXYbzQx3rWUthgl7FGdmXJcl0hqChpQbYkp7147cT3wZslIY60D/GzLIM9OjtAsp4v/u50D/5kDO6O/wFQSwMECgAAAAgALWdKUjvfnt38BAAAWgsA
*/