
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_DISABLE_OVERLOAD_H
#define BOOST_COROUTINES2_DETAIL_DISABLE_OVERLOAD_H

#include <type_traits>

#include <boost/config.hpp>
#include <boost/context/detail/disable_overload.hpp>

#include <boost/coroutine2/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename X, typename Y >
using disable_overload = boost::context::detail::disable_overload< X, Y >;

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_DISABLE_OVERLOAD_H

/* disable_overload.hpp
nN8JMCIR8i7AlNw40BkiIH4qrUPMykmtInQvwAmzsjUMBcELq4HfcVnwBbrjDnLnSnvWaiWVKTCTVqoT20q2VES5Wz3J6hqjWfEN6NKB01BZ0QTa34SVTmVGV6QIF8tqUUibNx/CQocqbWkDVhRFDYemUtiQgoBpzVaTdkKJ0UtHF6uVJW/rXK8ebURaa6CsMgrdIS24L9VIfBMqlQrj93sitl5qlj3l3ynZQ+wpaIVRQaM7hf60AQtupW3Cx/7s3Wg+g4/dyaQ7nF3D6BK6w+sa731/eIHakOjVgLgvjbAYhQG5Kgsp0kfOf2qns2j2Ds7nk8FoPIsvZ+PxaDKDY2h0TuDPSpGsnzegUcgF1R1OouOTqI0L9BQLbjexFY4qjP8oJot403cw7F712FPQm0OUw60AfAZnuLIZpsoThwr1RtPr4Wg87U/ZL1IlRZUKeE1eguDyN8wDJhrXnzrfpzfwLEcpFKiIJ45RdTk38MyWIjn41bu66E3PJ/3xrD8asjFHpjmUWipHGkDZg6qK4pCUIBWnglJp1bJuI74S+CqCvgOClBnJ0uXYIlg89ii7tSwKWAjMG6MOqRYbr1hS1xIf1RZ7u7WyQZhL4Rht6o+Bp6mXQ2giyHRQKnnyxEqFGFXim5kx6uany6jq
*/