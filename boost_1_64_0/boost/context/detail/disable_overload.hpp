
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H
#define BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

// http://ericniebler.com/2013/08/07/universal-references-and-the-copy-constructo/
template< typename X, typename Y >
using disable_overload =
    typename std::enable_if<
        ! std::is_base_of<
            X,
            typename std::decay< Y >::type
        >::value
    >::type;

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H

/* disable_overload.hpp
/iC6j7G7jD2Sk5ygj1pA9zwKtZ6bNt3EtJJRT0KhJAeZD0sFWuw5WM86UN0AS9mQGcRl6l00z7pgMql7z+mtvTxJO+CF9ypFeWEUDOrQrBSRhmqQcvz7vtSuDaiXLitr0RkElqUARlfkBzESifhAc0/5meMVQ5RZgZOsSa3+GC6ErHHPAWvBsUOHEX2qwxPh+IYzccRxsVJv/g7wpsfWeXwlAD1E7fm6cjXYlrgJPszqf7yMA6OKLIeFwu3S5gT7KdCLAfviiZOZEM61z3iPei5zNgXk1oxJYj8okus4Rr9vNb+HvIIKa+Jx//xZcYBopCYxhY5zQ4cKwqkztGf4EbIFdIVzpzVrAbcTVdG63MbwwGccetX678h/pLyJb0TfZt4dOrR0teffndbPqDwvofORZztfQmTHIq8OJ1EH36nuDVzQpXwxP/jsdbCm6VLZN/XCbn0yox+BULgwpMpMmgbWm/CA6cku3ph//KzI/sVrFeLJh2ZaoNNh7C9pGSWqzNv3jHWGDBUUQ+Sr0UC5oE0p4wx3FI004XBErMahhF+8FOD0D+9CzD9z7w==
*/