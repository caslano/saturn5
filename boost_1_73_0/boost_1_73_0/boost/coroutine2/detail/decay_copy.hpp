
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
Iq+WKsgphZ9ZFfpBDYdjxQVaVvmdMUF+QbepICdlSyboqXlpYnCvUaOSQfj3MfyN7MtvJS2wZEo2fLLmsi2Xr580/66CqkFv80dyFViOHx98x86LNl0/c//q9PDqP5Xx35grsPzi4S3PHt6/+LMVhbuHTR6INyhtJvrywtufe25xSejQvdc8fnTiFTX8kQ0FlkcvVT4+cUnNqz999829EUvkZcZmW5B+/X13vvbnvRUVa/YGumI3//IYmArRtx8=
*/