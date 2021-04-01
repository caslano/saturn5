
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_EXCHANGE_H
#define BOOST_CONTEXT_DETAIL_EXCHANGE_H

#include <algorithm>
#include <utility>

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
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

#endif // BOOST_CONTEXT_DETAIL_EXCHANGE_H

/* exchange.hpp
QcNUrFHXruGeNgY1MbTSnDJqA62hwD9FJaQMmMfQoNdiRqJddL7TFAuB+bvk6zOBqU1J7irYHSJH1owhbj93gtiMF1RyJRQB53FG1hsmrvMNrK+FxfTQG0mKuso9VxkZ1nDBS0R/98tJu6GV6qc21P/V+YEEujOmMDqRGJELVtbh2CdNn6nnbEXDR2KmwkSM1Xc8fSbReG6qm2Jca/Ox1+CzJdsuKwGaLCVs9vHzHxRKL9Nzyr2bWk8av7s9Ne79J5+v5Yd79ragpwfJ1GQme//fQPTGGqyM6ZoF6kjSBrF0buIU0ZIGFaE8HWggViMZlUUwhkXf3leW0s8dgFbzLmrwAXV3MgJ3sKQ2X9StUXabzimOIiXet8Pqd3TiYu4F3pp7izQyv0MnfuMEzj2h6TyFVX0c/is/XD2YiJpFjasRRq47clhj6otzzEVJ2q1+dSTIfDzaufw7G0rjQx5CoW+RQEsolnPYotvEjFbxnFf6VxAEvpyBUbckqGb/J6IxbX3ebpcyJfA74YFc1034OuvopfUMCXU04P6BQfVPXBbr08m2CEO0obMS3g==
*/