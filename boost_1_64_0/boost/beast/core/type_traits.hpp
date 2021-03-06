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
2/io72L9ZxpYuTfuNwKI1dB1FH1Tfp5F8R2L5AcwjC5bFOcO8oLv8dNXqm6LsN7qrwZA1tJrjqzFHMr3yYb3dCh8h3fyp4BxTbyVQ0+DBjSLCPKGs7DPQlZ3PSo/buebZA+MrGRdaRwjnFtiPiKmsHQE8sK8bze0IgXa/JQpvrEmVFFcGhxwBB2Iq8GyCiMN/wW3GUU2ba5tY+xIleiCEPOzAiMYUbePn4p3jimdfFn8K9gxwqAdqlp3cW3/efY/4n5GWZ2VsJ+PbHaYrX82H6fuKcWlRymrzQsag5Op33GelEt83I/UBc5+NyhKUfzw3tJuwrUqnTkIB4kQ5/r4ph5cpHJgbLGv7Is3tvtpfR/3LeSPrO0ylLxbwmwYoS11nSrssS+Yp5HgEToAVJVdvzESXLPvrZBJZdKRmqf1yJ/mrbKmCRLy4TAMZQUnz9hnCGnUvLRbxfiLIyJwhihS3FL4OVDGrqy0hXJZrh+2kfu5+oF030PNnXZo5lHnLHe+Xm6xqFWrlWvH+boWY6AqQWs/qxlrP8mcKnN2NbPBY/XriO3gU/MCANSPeQ==
*/