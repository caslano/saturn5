//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_IS_INVOCABLE_HPP
#define BOOST_BEAST_DETAIL_IS_INVOCABLE_HPP

#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class R, class C, class ...A>
auto
is_invocable_test(C&& c, int, A&& ...a)
    -> decltype(std::is_convertible<
        decltype(c(std::forward<A>(a)...)), R>::value ||
            std::is_same<R, void>::value,
                std::true_type());

template<class R, class C, class ...A>
std::false_type
is_invocable_test(C&& c, long, A&& ...a);

/** Metafunction returns `true` if F callable as R(A...)

    Example:

    @code
    is_invocable<T, void(std::string)>::value
    @endcode
*/
/** @{ */
template<class C, class F>
struct is_invocable : std::false_type
{
};

template<class C, class R, class ...A>
struct is_invocable<C, R(A...)>
    : decltype(is_invocable_test<R>(
        std::declval<C>(), 1, std::declval<A>()...))
{
};
/** @} */

} // detail
} // beast
} // boost

#endif

/* is_invocable.hpp
YRGSFGnqeZMGKcjVlly9WUmTdU2OlmQS+j2wU7HcsR/QOVfkOhX48Ai9e4g/Ryhcon9u40rmD/dz/HgW0dYHPReMqJB2rAadpl8I4XeozJKT1HQugyk/59we8sDE5VUX/TP+Qav1oMwVLI8gzC58JRp/Mt1vmmWEWQlTw8fxuyBd8VrWF3dXq9nQtc3NVUdE7n0P5OOYvpg+ve9NMdHJsV30+ugIskW5WUsxwTh/ETx4MLmyZCspWsLJUWHf8WUympMxwHN9Lxqhl95JV1F/PwoZAdViN6TkR9AL3D3Vpybqe92/2PUXMmKDB8U+McZoNbwuzFsmLOYUtmWceyXZIxFOBr2taLNFy/5CSZG6/mpoojPXRjim5KlqsokeqCbCbiig3MjkL9PdPX2VaQTYlwZ3TLE4eMUaYt86vBSP5yR1dbxCrxoiQ1yeJDczlF5hH4J6CJihEhDBpEGwOrsrt3gf8B/fDAefWtjEKXSFQ10O9kh14Sb2eG4NXkhtXXGD0IHBPntCLyy+Int5PZEnQWwFHwdulwBfGDBiIMTjFn80ssf8S3LE0fOeya0gUTutzFH5V8tVq1VcZIWOI1eUBip9IsR9uSn9W0EQU2PBy2TMcL+gQocdsdDKV8kDWA9zSUw2C2pT65LdDk/qIUbUE0m7y+ASKr60gh+KB3BCOaOIdatFTg93SHFS3mn1jw9JRrU8JBsxM8ohpO7h
*/