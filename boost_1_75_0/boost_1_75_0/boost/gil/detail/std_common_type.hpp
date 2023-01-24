//
// Copyright Louis Dionne 2013-2017
//
// Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_DETAIL_STD_COMMON_TYPE_HPP
#define BOOST_GIL_DETAIL_STD_COMMON_TYPE_HPP

#include <type_traits>
#include <utility>

namespace boost { namespace gil { namespace detail {

// Defines a SFINAE-friendly version of `std::common_type`.
//
// Based on boost/hana/detail/std_common_type.hpp
// Equivalent to `std::common_type`, except it is SFINAE-friendly and
// does not support custom specializations.

template <typename T, typename U, typename = void>
struct std_common_type {};

template <typename T, typename U>
struct std_common_type
<
    T, U,
    decltype((void)(true ? std::declval<T>() : std::declval<U>()))
>
{
    using type = typename std::decay
        <
            decltype(true ? std::declval<T>() : std::declval<U>())
        >::type;
};

}}} // namespace boost::gil::detail

#endif

/* std_common_type.hpp
JnlD7c4iJuGyJF59Y2zB8Mly+NtZhUoQKUAAY3g2lZvDkDvOhZDkJKkmFQT7HBiZcna1elid54QCsIGfnn549X662kQq27v342tsB+NJsxO6G2IoBK91WCHLqAwAOLdL9QQ5mDqP7x6fEUCxryvNt1qCkKN0gZ5B+qEqTs5hss7zTdBPp+bUA+sScP79M6+bqQMsWyqvXjZEYi92++4HkbYZvUERIADZe3J5rAdmAWLqwJbNDpHmP+/WMEO1psf0bAebzkJvaTJlzOXurVdd3g0aupDDshiq28zp9bXB9zvn6CQSBaB01xIEun61vpxR439eLFKuUXECXVOEIWK8iUq/dSUOpmAvfFXSdmtryiOiYnTx0vQYq2FG5O1X519/UleIlsVLQW4sKDZ1zicCs22V99tN00ifW0/QvlaezQ1yKZnsO6TDyV968YNubRo9fTztlC5exTMt8HVJB5gE7IT0sX9UYl2jwQ42/PZr+NPhmF61Wa/n8EZaA+S8CbBf3z40qKtfKDX29uTefe0Am9FiDasH5bUrn6C/HJvOSP3M6dJmHPO0p9zqOFEExdX1lImKnH0INTWKcD+KwJc8bzEmbPdnu+5wWAaf//bU3dGqiCbOn1yvPcJdM7BTtR4owLyN49IEYxqtDAvojqWEC3mbSRmVVDu6qjOm5MRxyhZOu3+uqLfcrAvy7rIXBEjQK7pNjevTku7aO8x4
*/