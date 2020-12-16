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
xDYlb0bg3oTwjg9Yiwqz8GaHWI9eJnkTfvHn0o80A/r0MSwCJS9cLxiGb326Q/gr82eV5BTlHWeN8Dfh+0o9qPuzP25CYH/mb/jMFaJfrPcqnhR/k4DfR9xxqu8Fd0r4dPo1f/B4oOX2e3n3pfRr/uA1pYydayWsPv2Gukv8HS28V2id6gslrAir0yjwm8/8abu5RtBjjp53vit52a624F/ujfIdqZZ3lOjx+3Xhv5V+nXdr+t3xj+5vXgm/jH7Nf0rGOL98uBKqx7g23Pd6A3lJ8tnSTcYk73hjG/mS9XxoqPjn2s3xyN9ZjyHnir/EJx8yZsivre77IyS8q/gzdPwOtuu2KyXco+dwleLvHnoOx3fMEJ6etnO4TITbzuHIkyE8kXpON0H8l9nO6YolPOMHjSsh5nN6TGkr4wTrEOMC6jdgjreafuRJ60D3+Ql0oDeL7vJNT46Zf9mI176rF9trX/HvW//GTufYXmf6Jof5/PXVB58bnD9l/YIvr7z8vrZ3urH+jDSf/ym60fasnj2fHuDu2Hd64rAWdb8XqK661NCRhWyJkz3UbCAeyzokm3Z8X/juEOLZkfglrAFoEeMWUB92GrAjsAjYhc+70b9ERhPR8xX90dXAUuCNwArgOuBM4FbgHOBDwLnAl4DzgHuBlfj/r8AF1IOGzPBMAe9mvrxihcN1IPV37we2pL81/an0d6Y/B/iATpf7zhxTgtN9iOluA7ahP5n+rvT3or8c+DDTTVPcK+V6JJvrETOuop64zOeB5vOJhsSTh0mMt57xYkDljNeD+TmD5ezBcp4JTKMe8hnAfsCBwP7AodRLvph6yZeR/wrqJc8HDmG7DLXk//Bx8n8B8z+G+b+Q+d+huPfGvT8zXhOpb3Gi79wIeC6wL/A84FnAfOBIYAbwQTNd4LNmusC3gWOBB4AXAd8FjgN+ABwP/Bg4Afgp8BLg58BM3pM+kfrXlwG/BmYDjwFzgN8DLwc6zH1bYANgPsu/THH/hntG2UF2BC3B1wLYmuVoAxwH7Mx67Up98DSgGacd6/k04HXUL18L7AC8B5gC3AY8Hfg0MBX4jBmf+RmouHcCjGZ+3KCezM9otse5wAjgecBI+qPo/0L6JfcvgPcxHTM8j+ksonwvZ/++BtiFz7vRvwS4gv37OvbvlUC5gwz4K+BqytMNWp64VraRp4uZ/3GUp/HMbwGohPEmMl49UCbjpTFeN6Ab2Jt2EAOAScCBwGTgcNorpAMn0I7jEuAZwEzTz/ftAh3m+17k++JB2/m+D1Ee0/8J7QH+wXHgU2Bv4GfAsUDIoLznS2Am7SgmA7+ifPwLOA14FFhGO4wZwO+Ac4DfA+cBDcRbBXQAb6B9xk1M7zdAN3AL0AN8HOgFPsVwtjfXLpg7hWjvdRxPbgUmATcCM4C/A44H3kE7h98DzTh3Mr938c64u4FXMd4a4L1sb5SL82/UH8eBllJvPred48DTwATgTsrZn4A9gc8A+wGfY35e4Li1m3fTvUg7i5eApcA/c/x9mfX3F+BC4B5gFfA1yude/t68DtwOfAP4hOhm+Ortb8Dnge8DXwO+yfHlbY4v73A8OQD8DngQaK5V3gNGAd/X4wfngKz34PEjxvDJTxwwjXYxPaSufOVuChxE+5h0YAvKb0tgNrAVMBeYCCwAtqXdTTvgLPItBqYAdwPLJ3u17UM57R/eOIENxJYQdhArkE4ebCHyRuO7AcDk7oF2EdlBthGjg745cBS0EWnsBL0LiijA15FA6aASUBVoC2gP6CgoaYpXDQVlgmaBqqaEbSnCLuzCLuzCLuzCLuzCLuz+V50LVPTj6//j9DynvExMAE7eBqC8ndI=
*/