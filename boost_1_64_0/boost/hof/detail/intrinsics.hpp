/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    intrinsics.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_INTRINSICS_HPP
#define BOOST_HOF_GUARD_INTRINSICS_HPP

#include <type_traits>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/config.hpp>

// *** clang ***
#if defined(__clang__)
// #define BOOST_HOF_IS_CONSTRUCTIBLE(...) std::is_constructible<__VA_ARGS__>::value
// #define BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(...) std::is_nothrow_constructible<__VA_ARGS__>::value
// #define BOOST_HOF_IS_CONVERTIBLE(...) std::is_convertible<__VA_ARGS__>::value
#define BOOST_HOF_IS_CONSTRUCTIBLE(...) __is_constructible(__VA_ARGS__)
#define BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(...) __is_nothrow_constructible(__VA_ARGS__)
#define BOOST_HOF_IS_CONVERTIBLE(...) __is_convertible_to(__VA_ARGS__)
#define BOOST_HOF_IS_BASE_OF(...) __is_base_of(__VA_ARGS__)
#define BOOST_HOF_IS_CLASS(...) __is_class(__VA_ARGS__)
#define BOOST_HOF_IS_EMPTY(...) __is_empty(__VA_ARGS__)
#define BOOST_HOF_IS_LITERAL(...) __is_literal(__VA_ARGS__)
#define BOOST_HOF_IS_POLYMORPHIC(...) __is_polymorphic(__VA_ARGS__)
#define BOOST_HOF_IS_FINAL(...) __is_final(__VA_ARGS__)
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) __has_nothrow_copy(__VA_ARGS__)
// *** gcc ***
#elif defined(__GNUC__)
#define BOOST_HOF_IS_CONSTRUCTIBLE(...) std::is_constructible<__VA_ARGS__>::value
#define BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(...) std::is_nothrow_constructible<__VA_ARGS__>::value
#define BOOST_HOF_IS_CONVERTIBLE(...) std::is_convertible<__VA_ARGS__>::value
#define BOOST_HOF_IS_BASE_OF(...) __is_base_of(__VA_ARGS__)
#define BOOST_HOF_IS_CLASS(...) __is_class(__VA_ARGS__)
#define BOOST_HOF_IS_EMPTY(...) __is_empty(__VA_ARGS__)
#define BOOST_HOF_IS_LITERAL(...) __is_literal_type(__VA_ARGS__)
#define BOOST_HOF_IS_POLYMORPHIC(...) __is_polymorphic(__VA_ARGS__)
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) __has_nothrow_copy(__VA_ARGS__)
#if __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_IS_FINAL(...) (false)
#else
#define BOOST_HOF_IS_FINAL(...) __is_final(__VA_ARGS__)
#endif
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) __has_nothrow_copy(__VA_ARGS__)
// *** other ***
#else
#define BOOST_HOF_IS_CONSTRUCTIBLE(...) std::is_constructible<__VA_ARGS__>::value
#define BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(...) std::is_nothrow_constructible<__VA_ARGS__>::value
#define BOOST_HOF_IS_CONVERTIBLE(...) std::is_convertible<__VA_ARGS__>::value
#define BOOST_HOF_IS_BASE_OF(...) std::is_base_of<__VA_ARGS__>::value
#define BOOST_HOF_IS_CLASS(...) std::is_class<__VA_ARGS__>::value
#define BOOST_HOF_IS_EMPTY(...) std::is_empty<__VA_ARGS__>::value
#define BOOST_HOF_IS_LITERAL(...) std::is_literal_type<__VA_ARGS__>::value
#define BOOST_HOF_IS_POLYMORPHIC(...) std::is_polymorphic<__VA_ARGS__>::value
#if defined(_MSC_VER)
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) (std::is_nothrow_copy_constructible<__VA_ARGS__>::value || std::is_reference<__VA_ARGS__>::value)
#else
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) std::is_nothrow_copy_constructible<__VA_ARGS__>::value
#endif
#if defined(_MSC_VER)
#define BOOST_HOF_IS_FINAL(...) __is_final(__VA_ARGS__)
#else
#define BOOST_HOF_IS_FINAL(...) (false)
#endif
#endif

#if BOOST_HOF_NO_STD_DEFAULT_CONSTRUCTIBLE
#define BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(...) boost::hof::detail::is_default_constructible_helper<__VA_ARGS__>::value
#else
#define BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE BOOST_HOF_IS_CONSTRUCTIBLE
#endif

#define BOOST_HOF_IS_NOTHROW_MOVE_CONSTRUCTIBLE(...) BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(__VA_ARGS__, __VA_ARGS__ &&)

namespace boost { namespace hof { namespace detail {

template<class T, class=void>
struct is_default_constructible_check
: std::false_type
{};

template<class T>
struct is_default_constructible_check<T, typename holder<
    decltype(T())
>::type>
: std::true_type
{};

template<class T>
struct is_default_constructible_helper
: std::conditional<(std::is_reference<T>::value), 
    std::false_type,
    is_default_constructible_check<T>
>::type
{};

template<class T, class... Xs>
struct is_constructible
: std::is_constructible<T, Xs...>
{};

template<class T>
struct is_constructible<T>
: is_default_constructible_helper<T>
{};

}

}} // namespace boost::hof

#endif

/* intrinsics.hpp
K+wbHBMY134t3JHcYE7Q9sdGmrSHB5qcMNCiWs1YWnJm1Gjv2EOAQhO0Pu32uBGDTVLTSLX+NjbAyBLt9XgQrLiGQXD4rCB4TjsTCCpKaeQFkQLtV+YFuyXuOFl3xtJjuHRuCOimTYfFVrH1Fqn7mkRN0+nBOF94Y3YW+mbIhb0CAu+659NdZxWO+P/n3/5p2rEq8b2x/VYL/68ikf835bZE/s3G25T877LTytNTujW/+KimRfmoKaq+pqVmfdZ08WiL5VG/Vf/hlgT5qinW9D8uV+mqfEw+KvUOC99WlVf+32qs6fV3r27Z32DGGvT951fH+RscRjGNV5/N3+A44Osa1Sx+Wh3nbzAzUKh51/DlfJfczY9ff1qXg6+sNOnd35EuB29ZoVwOHlhtuBxk/kxr/Q4mE+wiI+rfWd1qBCO4NOZx8G+64qwWGh4HB640lc+uMWQYmSyVR35xBwdKeKB8u6qx7v8Sj5XhwpfWTxcnGDwJTJPACagCX//SGa1gTvfKx8QjL/0LP+i94n/edNr1zrPecHtL673pr0GL/0s9ISxNKZnsDGZmwCw99hbxSrDuwffWBwdStWGV9JT/YIQ0PbaNF346092HBByGja/XRvBy59jzAh21SVzmacSy1PJiWUgaxmglybxerEk8HxA29n/ACg+Vjv2/riV4IN26/5ep/a3S4+Qfb2+2f3dgTPHhdxLCyv8HVpr4Glas2odXaKvX8j68Uy61nGtPuw+LdEWKvU3RF0qEWG7QKyR14inEGpSLH1NlePXX574f5fdPWIiH8Zu9sQDxmAOJGJ9GPRb3Vykjtjle2gy1A2pnOcVlcyRzB/vrJT4GU8Fo3BjnzXOBpd+3LJDm0ZYH5siUpSpl9oIz4Qldr5J7Z0xghqXchWcs99Y0+Vx4D7aThQd0JBAE8a3d088woXOezsP9lxkxqt/O/O9A/Hv5QZqR6uwdNvls3sHTRmqDmNHgcjWjxT7Qn2g+M8C2ZV9iWnQEKRBei8WKkRMfHUGW2WbHcPga5q2rzl5PNChhn4HBF4n+XF8upumJMmBVZH6DNQsJr1q5hPCq7WcXOo378OqQSqaLzP1kTRfXVrZ4vtx9c+L5MqY8MfwV3UL/tOSftdwin+S32H9bdhr/qFcDvzY4KVlMo/MrqqDYMU/KDezB1vWxnM+RUlKdEGL9IFNsPtjXlPIpNUQBc8VHLKiSoeQnwh4mZUKUs5RfoKAAHeEjxx1xU0w63qRKkJN8rkDm1x75AZyzkzNTvw/x6tWl3+RVB2yutmutYVBi0Y1yK6GabPLvHrBRIbpzyR82GUAYhW0eOur0qm4OEEPWyQ70DnsGkgAtRVL/qaSUCYFvkrz3DEWNzzEVUjz/edlothgPgSYMTMo09cDY/GLbDYazJnPg0+Gv6TX21/RPdNzSwscfsPHJm6vF3vmO+Y0JPvRgMRPPT7K+/cPrGIZnUBei05WVNT41bEJl8I2Hw7ETaP5Lld/DIdYb8OAiOmt+yhnSSUGJ7UngDruUocWn9TeWmlgTERUZP0LF56m6soy61iySs9a1JlqpzGHeiDiuR7RfIuE/hZQDO+Nl5xMpspFIPyanB1OLIRB3iYxye4u1HWupJxfLWlkxR1LjX5V5cEpEl5jI0k1Als6VmXqaD7OuSsV9sgHYAEoxPG6GJ8X5sc8iE9iKCUASFj5RsVBiDPvB/so7Iq5ZYsJur40N4NsldhYWkPVUvAsJv7Fc1K2w01KxC1RuLwzOTIFAlOgEilDN7p2LL84w7JROAkuoAiEopnHBTBy+S+uKeB9ll8Lf1mijumA2N0NJRkuv30A13jyLq182nEsH7AZ4/zKIb0jUlkU=
*/