//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TYPE_TRAITS_HPP
#define BOOST_BEAST_TYPE_TRAITS_HPP

#ifndef BOOST_BEAST_DOXYGEN

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/config/pragma_message.hpp>
#include <type_traits.hpp>

BOOST_PRAGMA_MESSAGE("<boost/beast/core/type_traits.hpp> is DEPRECATED and will be removed in a future release.")

namespace boost {
namespace beast {

/** Determine if `T` meets the requirements of <em>CompletionHandler</em>.

    This trait checks whether a type meets the requirements for a completion
    handler, and is also callable with the specified signature.
    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example
    Use with `static_assert`:
    @code
    struct handler
    {
        void operator()(error_code&);
    };
    static_assert(is_completion_handler<handler, void(error_code&)>::value,
        "Not a completion handler");
    @endcode
*/
template<class T, class Signature>
#if BOOST_BEAST_DOXYGEN
using is_completion_handler = __see_below__
#else
using is_completion_handler = std::integral_constant<bool,
    std::is_move_constructible<typename std::decay<T>::type>::value &&
    detail::is_invocable<T, Signature>::value>;
#endif

} // beast
} // boost

#endif

#endif

/* type_traits.hpp
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
*/