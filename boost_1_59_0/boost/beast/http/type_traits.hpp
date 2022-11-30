//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_TYPE_TRAITS_HPP
#define BOOST_BEAST_HTTP_TYPE_TRAITS_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/http/detail/type_traits.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace http {

template<bool, class, class>
class message;

/** Determine if a type meets the <em>Body</em> named requirements.

    This alias template is `std::true_type` if `T` meets
    the requirements, otherwise it is `std::false_type`.

    @tparam T The type to test.

    @par Example
    @code
    template<bool isRequest, class Body, class Fields>
    void check_body(message<isRequest, Body, Fields> const&)
    {
        static_assert(is_body<Body>::value,
            "Body type requirements not met");
    }
    @endcode
*/
template<class T>
#if BOOST_BEAST_DOXYGEN
using is_body = __see_below__;
#else
using is_body = detail::has_value_type<T>;
#endif

/** Determine if a type has a nested <em>BodyWriter</em>.

    This alias template is `std::true_type` when:

    @li `T` has a nested type named `writer`

    @li `writer` meets the requirements of <em>BodyWriter</em>.

    @tparam T The body type to test.

    @par Example
    @code
    template<bool isRequest, class Body, class Fields>
    void check_can_serialize(message<isRequest, Body, Fields> const&)
    {
        static_assert(is_body_writer<Body>::value,
            "Cannot serialize Body, no reader");
    }
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_body_writer = __see_below__;
#else
template<class T, class = void>
struct is_body_writer : std::false_type {};

template<class T>
struct is_body_writer<T, beast::detail::void_t<
    typename T::writer,
    typename T::writer::const_buffers_type,
        decltype(
    std::declval<typename T::writer&>().init(std::declval<error_code&>()),
    std::declval<boost::optional<std::pair<
            typename T::writer::const_buffers_type, bool>>&>() =
            std::declval<typename T::writer>().get(std::declval<error_code&>())
        )>> : std::integral_constant<bool,
    net::is_const_buffer_sequence<
        typename T::writer::const_buffers_type>::value && (
    (std::is_constructible<typename T::writer,
        header<true, detail::fields_model>&,
        typename T::value_type&>::value &&
    std::is_constructible<typename T::writer,
        header<false, detail::fields_model>&,
        typename T::value_type&>::value)
    )
    > {};
#endif

/** Determine if a type has a nested <em>BodyWriter</em>.

    This alias template is `std::true_type` when:

    @li `T` has a nested type named `writer`

    @li `writer` meets the requirements of <em>BodyWriter</em>.

    @tparam T The body type to test.
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_mutable_body_writer = __see_below__;
#else
template<class T, class = void>
struct is_mutable_body_writer : std::false_type {};

template<class T>
struct is_mutable_body_writer<T, beast::detail::void_t<
    typename T::writer,
    typename T::writer::const_buffers_type,
        decltype(
    std::declval<typename T::writer&>().init(std::declval<error_code&>()),
    std::declval<boost::optional<std::pair<
            typename T::writer::const_buffers_type, bool>>&>() =
            std::declval<typename T::writer>().get(std::declval<error_code&>())
        )>> : std::integral_constant<bool,
    net::is_const_buffer_sequence<
        typename T::writer::const_buffers_type>::value && ((
            std::is_constructible<typename T::writer,
                header<true, detail::fields_model>&,
                typename T::value_type&>::value &&
            std::is_constructible<typename T::writer,
                header<false, detail::fields_model>&,
                typename T::value_type&>::value &&
            ! std::is_constructible<typename T::writer,
                header<true, detail::fields_model> const&,
                typename T::value_type const&>::value &&
            ! std::is_constructible<typename T::writer,
                header<false, detail::fields_model> const&,
                typename T::value_type const&>::value
            ))
    >{};
#endif

/** Determine if a type has a nested <em>BodyReader</em>.

    This alias template is `std::true_type` when:

    @li `T` has a nested type named `reader`

    @li `reader` meets the requirements of <em>BodyReader</em>.

    @tparam T The body type to test.

    @par Example
    @code
    template<bool isRequest, class Body, class Fields>
    void check_can_parse(message<isRequest, Body, Fields>&)
    {
        static_assert(is_body_reader<Body>::value,
            "Cannot parse Body, no reader");
    }
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_body_reader = __see_below__;
#else
template<class T, class = void>
struct is_body_reader : std::false_type {};

template<class T>
struct is_body_reader<T, beast::detail::void_t<decltype(
    std::declval<typename T::reader&>().init(
        boost::optional<std::uint64_t>(),
        std::declval<error_code&>()),
    std::declval<std::size_t&>() =
        std::declval<typename T::reader&>().put(
            std::declval<net::const_buffer>(),
            std::declval<error_code&>()),
    std::declval<typename T::reader&>().finish(
        std::declval<error_code&>())
    )>> : std::integral_constant<bool,
        (std::is_constructible<typename T::reader,
            header<true, detail::fields_model>&,
                typename T::value_type&>::value &&
        std::is_constructible<typename T::reader,
            header<false,detail::fields_model>&,
                typename T::value_type&>::value)
        >
{
};
#endif

/** Determine if a type meets the <em>Fields</em> named requirements.

    This alias template is `std::true_type` if `T` meets
    the requirements, otherwise it is `std::false_type`.

    @tparam T The type to test.

    @par Example
    Use with `static_assert`:
    @code
    template<bool isRequest, class Body, class Fields>
    void f(message<isRequest, Body, Fields> const&)
    {
        static_assert(is_fields<Fields>::value,
            "Fields type requirements not met");
    ...
    @endcode

    Use with `std::enable_if` (SFINAE):
    @code
    template<bool isRequest, class Body, class Fields>
    typename std::enable_if<is_fields<Fields>::value>::type
    f(message<isRequest, Body, Fields> const&);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_fields = __see_below__;
#else
template<class T>
using is_fields = typename detail::is_fields_helper<T>::type;
#endif

} // http
} // beast
} // boost

#endif

/* type_traits.hpp
y9REBXGwfI9mA3RvH0g481gcvU4W9DXvfgJpWbJytJB8qRraFii/NkTapvrTfupYH2wkmkXxDiF0XAGTth9qdxaNVGIW1W+jLikO3RNBRkIuHcE6aVC9CYKGll7/KMQKzk0g/AFidP2zNHJVIdfMSpp1CHPfCiWxjUf303CeS+njyqmj4y4FeMMI/hhRD7Hs3b5mMuRONtp0+puymrF/d3VW+vDTCF/mB3geKP45q4rN1SRKq2xStf3HLvz7k3il2dy0XcmHDIs8gl6iIXPTrqx4jwOx92mK6+sT2eIrkBEAIOhP8J+QP6F/wv6E/4n4E/kn6k/0n5g/sX/i/sT/SfiT+CfpT/KflD+pf9L+pP/J+JP5J+tP9p+cP7l/8v7k/yn4U/in6E/xn5I/pX/K/pT/qfhT+afqT/Wfmj+1f+r+1P9p+NP4p+lP85+WP61/2v60/+n40/mn60/3n54/vX/6/vT/Gfgz+Gfoz/CfkT+jf8b+jP+Z+DP5Z+rP9J+ZP7N/5v7M/1n4s/hn6c/yn5U/q3/W/qz/2fiz+ee/P1t/tv/s/Nn9s/dn/8/Bn8M/R3+O/5z8Of1z9uf8z8Wff38u/1z9uf5z8+f2z92f+z8Pfx7/PP15/vPy5/XP25/3Px9/Pv98/fn+8/Pn9w8g09/el9+yyABfYhNBB/t8sKa9mXScYOORe9UwPsRUpp5vZWtcShwuc9EeNXWkK6zxi78ePAbhjzt5F1cc4sMkdBu5ceeuYEl2VoAuZIC4vF1YIt7uGPhvxGNtsWfiqBJp1w2F7XoiZozSlsrzYU+i5ohG5W/9ht2+Ewy5W/Ayu/UwxpsIfmSTmx9ydIb9XQ50LnKf8/7l34J6lA/rb6GNd358zKhVk1XMFPhagdx7kISNLiJzUn05Xo41U7J4Lg9IDlbqlPRy17yaRKmHiUJbMpzYJQJOUCdSsZNRKAtE7k8TDFMKhsVwc3BEQDDQ1pycaCqhkoUvc55Cexd00c5Nlix7R4zEOb2sQfjvLrIZtVo9DIlJm0t32XexJ9TanuuLOHT5a/C0dlXf2OnRU01si/BGxqib/j58HKD6U+ufvMCYLW+Z2HJZK+vuXrinL4uwzlcnvUrDjlo7A74WymZkHBd5xYZiv35e6ve47do5j6O5MvohE88IiQ3fI+Ge4VpJqD5Jzq2XGMOqItIOg6Cjp4rNGBopOyGlhinW0Yhjl4jUzw7fl6KnSZ8JNMHsh5HvSF/zUnnr0SDOcBs/qhO7NbDv1CcNHTKy0mxd8NJAwIyFUnIuNe6eho3psn3GvJa4MCZW6AmydMzeKK7u02E02N8KMHtq4xNEqu6u7rEWugh0E4uVTS4u3pmNWLfM9CoU4aOhF4FdeHTt8XwhPp6LJrsshBVZulUpcS4ygM0lP7B/2mJRN6W8CmYZso2+rC5tZKruMt2xS47g68J/LYFKuJDQTMdqaZdI3GooySrEuZ8xPNoZqY9esqPGdLXisVxJeobxDMtzUewWbltyIFCkk/H+2zF0pYE1bUjHl8Ct5vPXemJDVxP97bR+Qil9xXWr7iGLsmNpSZz7JW7p0XsBfgPNC0/Id69Q7UqTbZa1Gi7fAPVdLNzkXZimQNtgfnoj9j7C0+yf5hQtL+bNW0f8vjDrJf8QrO7eMjlikfTC6F2+vTK7MdRzXpu4tylGNNTKMgcix6y4NL0fL82LwZd9AV/3mR+a+kJznS/liiFISHu8UhqTW8ksBrgsdQP7wD3XFqOk9Zy6acrdLwLBSzoQ8vtYVdoRPnup6hLRv0V45+HkrI9fKJn1QDK0cqspLIe/ZvOcFjAwzJZsTRg7t5yBCS9dT96N6q6S6Dyl8cW+/pxoGDAYHCv9JLWWpu++rMSLWxFtE2VnPMHnTSuJRAeR7fX0Cj6hniIrq0+oczVDrMu6sbDttRCXpvXqFLEIFR2RC+ye0MlOsNPhlBcnZt6qX/T/GPAiSFqlIVYpPkeFPZvgHg+KrfzvVOU9STpgK9I2EqPUCsvMIUt2MaVuW8Pf7jw45s5+uto3ww4QsML+pYe2RDYD15+Ed8q14z8Vla8fktqWZ64UsRhBOQJAfEL1DWsK4m8rn4ZvzQ/HQVtA/NR9SyaI6dBQ0+K6qAi+n7ukcbLqhIlcRKSJKgjq4JuhhhWcLYuYvmpSZ8C0t4rU9pfmOxzFMgj6BCy9kZhYw9aTXLQPl0GCSwZdgX8iy3RYZXhaqiMQYa+hmepeCcz/FaMee9s/ZMaTS7HoquJvOG0cg0c79uERk3+8GRm40u+Ws5IzFsNoquNPFJHysv//hSf3bKBkUbM08OW5ArUIqt6DOdVrasW2v73LxxddlElzET3Z5NC2973dW7SrtSSfEyskdpOMJYnyVfKenb5HNsogjuvTFdTdFDKXOQAGSD+i1fIbanMrrJ4aRL9/H6GC8q6fK48EfE3zN2GiA1pEnDiVzddwU+e2i23iVDE5X9EfTw7vwONiPdOMzV8/Kq+5dt120V1fi9E5wku0Fu2/fUFtCfTIZhrzJG2ZB9ZeiGggv59ty138XBk7NFoTgrPKnj2RGyhKVL5KLuenOi7XlCi/q3K+2o8vDyGjt1n2MeyHzlJvJviASvaCf+V6QjRnbhgVZEcyudAcvnbprC9BA/auDvT3RkUBVfcLgsnTN4Q+MXe76YJKQvLabsJImIPPRuj3jXx7JEy6F5IOR4clrZhpfZup7PIEwAuk/31yb7eZjmIIKQ8PS92Bp+5F5qy5xyfSqr7Yuzmzf2EswFSjsdQHkLlIp/O3vXIdwjLOrqk0JBrbb6e4ftOg8b6yUXX9FouJlw4qMt/H2X40Ko+9HMf6NM7NEdtZMiGDaSV9prtGTFTOwiZaW2v5/rYQ0etq3nziwkoPzVtvKpaoGZ0vmHqf0i9xhNA3IJNibWwet3zF+MSPG/YqtD/nHqvEMrx0W6AiWY6xsWGPf28kgtOHSO5Qwq0IYkxG5VhdEouiezjNgWkOrFVTQpWSeeYtKfI5axoRkyDSAKA1qudhTfJJ6dpIf28fFpgYX5cefUJHuFe64g9LfbWbfUyJ8Q97CqfwinabgxC6592y8a1yMWDdmCj3e1qWH4tpvZznXgHP17vWglvjQttDfnpoTMV2akw6flwbS5tIEs9m0Nn0sPGR2/toiVfqaVjlx27j4j1201Q60ufVWh1U0OmoQFcpIV2Gxlb1paSQDuUkuBn4YPeTt+qJCME271U/OpqzSTo/WvWbl3r065nLso98lqQobDB9K6usWphexCgpzA2DvxYD82cux5xKNYgKP+exb7C8V1Ba41e94tnWbCp+RNCqyMHx/OD1bj+bBNwIM1te8lzAp/OuxxExJqXdCrbsD1XTG2JoQQ75hfoxrK0x0T1xSpJQsj7ptnwXc1qkMcdGZF9plN3waTkK+C8rS2cdBsfaN3J3gLQQIZd6JVMoooLWdosXV4nZlwuFWdv1qsdIaGGKM0vvrkn3OaR5xwcJyco7T/+HBN4X9VUB0OYqEbuq0yuvSpQjbs5XgwXOXix96v0Sj4lWWTRJj1o45APazzs0kHCe7KmUhdV0fyP7bM7UU7+mR6ZQhAL5yF54e/yWeK8Pp8o8HJITR9nWJrQd1rzuIq/RRUr9pMxDe12z8SIfxNe/P/2G0/0L5SqJ4efmEyqLgGktYp40MC9LnPKG0cSfBUx44w7plGh7ZaqLOX7uO7f1ICoIgZl9UWBEHA8DsBOqArqCHM1Pque9oWCZEyUujVYPve+HUO7kBuA+Bn7e2kN0tHcf4JQf4cCKiD2GrVtrTn2JOE3JsL5dIVk4B7FhE8WJ3HQnN+yKhU3Alo3SdQubG+NCcUtNiKdpnj8/bSjDYKVpz2mxty9fNjSn8X2qx78i6fGx4arcmhXrVHPc0dGIJ5yWwg7z39BtK5Vc6zjJmVu77tbLd3yEaC60vCHq1a5Md/pLl/nxvMY6DEhW5SII3sc16DI1qxe664sBsqGB4EiwxZt7iZq3Hd36SAcz1fOSgElxaZoyHVarMO1oSbgZvDHbEa8FBdHqevbtTRnRwTL9Oprl8u3tfJhqRcPRuhh5yoX8KrXapnbzjubESNYOxdQAyfhsdkSs/2yNvfTFb47TBdCShfLsM+GTCR42Jr+Sd7uXse2kxUbQf2ZQ0k0WvSF3tPvdsTfjeM+Qo5yXWvAzU+Oz3ixTzXOshw95NIer6hRoXIwuqgV3C0A1qQ7dG3k50SBuoBHqoiqZvOE6bb/Pmzt6Ce+Ze/8k5OjZFF38Udx0VFVTc0WKlJf5klJfbXQkf/AeWvEi9FXPR7zxotJ5snK7VS6/B7Rd0/pxRE5M5tEvDpbLRTHTgvfyvf6zxuG2IpJnwOgtlFCvkC6f+7Bgzr6HwPYgH9PMJbKRGIojS2OoWi9IaSzWYs9U8vNqdywrGynP1wN79eEzInrvYBi8lL6l9vrPEetKshBVeYobf0cKT9TlEUwyMzwRNwZkauLZJ/eS33dpKipwzlB97JlsqrRNWN5x98wh4Gw5b/0jlmbxftoZxkYJOY0xAIdSX7jkKGFiMppCbLzn2SZ1oxI7IMza24Txmrz600B0IydP/L+QKz7FQyn/uky9WlHSRBorsFPcijBRbK56RkFrIRujNyuH5Pi38POC2pWJVHDn7EsMeLmUgikWqts+3+PZSDR3rr0Gg0z8/r3vgh+NW9RLNeZ/BOPpYW3P353BDUfpg/AVNla3TD7F5wjxM41YwLLI3nzusELchYBTg+TnBOvogortvQ8DQsYnJlNU44QogUc82HkbHnkJLAC+jiHiISzNV/CGwunUzSYHtnxK6EjSKOFbTsX9fdOkr0u/UvUZWiFtX1taivRdQxUqNZsyVchmQWNJBrX2b/9h4VPGFzK3Xp3gWXazlqmZDwcTsaS3jDWsQLg1wgZI6u/eM+B7IIt85iJlNw2lxYwShPCaptGw5XVOETn+69mS+75Ju3EVDR41a5QtJPOtcORYMMJX3e/ACh4lGdAwUJaMycskCbOT9k/c32VoB7Rq2CEJ7PVQMRcetBK4k7D3suczN0P+PTq6PdoSH3xjh2fvXKaV83YIVBQmDByioW2VlU1/uryAtMdPw5NhOiQD2HzqVc+ao/FG5LyH6i1rwebf7kpNa5ZzMOpEpV/qsS6XK8NHvL/o68JKI3awBdtMnuV5BfvkqVD4N9vrh/oit6tFqA6qGOHfkMMj4vp8lSoC4dV2S22KJ7Ur19Ut7IGvtzcbqXdmE/HSX9l2z0/Wb0k219TKyOF/+bFp0XlOwJ7qs9v1beBBYJoiVeJoS92sjPp8yMjFXEMaBYZrXV3F5FGPsE2f5a/lsXF7PD1NW/C4gEbsRJKpvGWqfXhlxazzRCHvst4uNBcSzBxQG3yJw00pHtS6ZAC03KOujlWv4YzpexSxXq7s1dpPLWEiHh23PbnF6zXMnKd+uUh1Su2hcFO5NV1VQdx2TaGmyC+FdU2VkmpU75I+WnwIXtQTLS6zAoyKpLnHBRJXpusnYQiSu7nzGAitIf8eofjIc+7mTO5jxKqu9HyOrI2wxxfHPtRs2K+uGHn3SR3duh//sdcOn1A8d0WPqz9zW51kCH7KbxIeXQPPUnE0kWxk1ryqZGDUblnMpnxM6xcDPzeBgmfLe7iOwGosOTCP6eM9qbdi3yW7PSgnot7t9KQ7yNSYUgwOdgUgbDQxkg6yXsnvgwN7rk8bgdgiOppMp+b9hZMzKgh+8c/+Z63Xi6dqqH/JcibPXsf6mvGXgxzXBn1MDjx8x9/Z2pz84fqC5fpFN00JkPfV9PQRcv/IV3JQqkWRxPOQqCSl2hwupANR3kyyUIct/h4uFzXM+FICWaJmEpOxD476qZyB4j46XsfvlrpPrhMwuSoqLhoX2pczvKPM6H1b3vs/aQ5h882g/8JbLHjcDe65qUpemstxDiPNT+9fU2R0Yxi4Yxmgkxjd+LTM8byYmAtcVvvDBInH6zQxh4kNrt0793I7EZP5TFrscdw9dIpYARW0SQGTkpPtRT95i7mr19l8/pt8rpjq+TUmsdTnMg/XMuK5qaVfaf2yaxMUntFZbzTUWLb5sNPOZOkyWW76pVMRfgKHooRKXGtkVMtHdQn54uvaGHk6RbCJP30Pt/+n8NSz61HZ5zO7WIiyVa2wrG5N76Tw6L6h7qC5W4MzqwuRE7XbPcw3c4qALCJH9VlRpH09ub9S9gtLbnL2KLVetNDLLD+vfvNaHMvID1MQoUaSqcZ1znAE+B9AC37xt0CBjhBQbjyVfJgTSdnXE7Pu2q6BqHv/EUKuGQX+jud/k9UwP2781IOhgdlAGyzIs1wzCrmQD0v+g0cUHkpBSfFHMmSBIreeGHe1OU2CVyaMGQhmRbZfNDGGAB9XzfyB4MJtv+xhiwpkZplEufSD8ZbsB5ij6E9ftyaesxErL+QGwoc0/zhsG2/9CkK6H6twDFBQmrjlso/bo+g6aM/Q2CJ9IYqhJsp9BDar72TeY5LZlQFW6slw/yut2nXPJyhD9rELMj2QMcqz0Qlhx08f8kMvRtF1emFgPasWLPHqRFUakIW3TeBHiW5nDcj4R5mwSwYMETGcTCqbWFsFOCaZB3ykSChgzhyVupma8C/AwKAA0drxrWJj1jf2HBMJwtuWAm+wxS1yrsGV6nR2/HngoW/VCH0FYns/kCN2iU9ASLz2SEcYQjsto1//IWblfO1Jx+9hRIQr7OVZInmexZuxZXZLHwSSObfSObN9vYKFTlgeNo7tTJLscISRN/PakSmpxYxGA6b6SpLJVmFZuZlF9nMRUo3+kGTlTWUDRJRDQnZ9eX1fcpVSVenFIWyTc37OCsmfbNuGY5JhY8/Md/RfJskUVAop2sqMq6z1f6XUc68bUzs01E6+H++ZUpZ7gyhqAKSkqaKiA2AmpVblmZDkEYzRnlwxbNcgEiAJC7ZKFgSlq9lZr3M+JiQlvLWr4koTqZko3bZT9pDuBSkT+rfziNs0laeDl/8upshQw6UWphx40gSyDe7g2WzUmfcyffN70jusrA7lyOaznuroSZ2FBRo/oOpyz5RW5sbOGj2Z7Y0uPndqNnKkU9y3Igq82frKFEoHqOYAOzud4O7VMY0/bV44ZQmAza5gvKYMg38yazW0RejALfTmChfamVrHM3eYBG6aGXC6Za6HpUv7apI7J9l8JA/fPSwtGjbUmlh6rcQeLnyUbIJ1tZHQPGpYeaifslOJyJGx8oivi8Oxy58vR62cH16N3NasAc7PptM7SR2cWYO42AbdU4JcnX/MV7A+wmylko59l0TxA3K/aT69cUMcYsNT+eVma/idFlXk3btikIyrctlEYUXuP3zPZJ0zsQ912UDjfW3w1Ua9u1mqTt3/M/qPWCtmzVBWglJ2K/GWuVgnfdBnXYlkluWHksptF8QPCBDWT58usxEqKkgrX9oOscraL9u1Eet0YPHE0SOKBwA0Hot+uGiDnAh05Up8NVXisNTbf3Lj6Pn9EugEVJXs1OnK8mh3IHqbGxXEF8t5Uq5PPvaTI568tw/ih8nCSnmnuv7s0fx5v/7+iKdEQy12e7d/rXbcuxlTtuW+it1ZJG23HWzcTmIA6Z7k7MLqAzV3aBEF9hybTzEd
*/