#ifndef BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>

namespace boost
{
namespace mp11
{

// mp_map_find
namespace detail
{

template<class M, class K> struct mp_map_find_impl;

template<template<class...> class M, class... T, class K> struct mp_map_find_impl<M<T...>, K>
{
    using U = mp_inherit<mp_identity<T>...>;

    template<template<class...> class L, class... U> static mp_identity<L<K, U...>> f( mp_identity<L<K, U...>>* );
    static mp_identity<void> f( ... );

    using V = decltype( f((U*)0) );

    using type = typename V::type;
};

} // namespace detail

template<class M, class K> using mp_map_find = typename detail::mp_map_find_impl<M, K>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED

/* mp_map_find.hpp
baJpGzXaQLd2lo3ttt2W1a7Qd8yb/3eS4KK0ta3bBmfmX+9f7/rvvZ88zDrxedKbgMEeYr6tAY0NivTNtU59QfFALyHb0JB+1A+8Aai+7iWG4RT4criXvzxArMJkgPlsfP0mMQll8DoaXx8m9qAQHliH+zDGDYB45lUPUDDze2Phe6Ph+LMsmsQBzaGiJdXZWxnuaiwCxVTn5mjVXckhFHz9LkgpeTzc5Uf/6d6WUBPo15oaej2gmWoYjcqn1mnWtdizi1fE0NG4O7l/zS9lAqBEc9u0Oda+P6W+QSooMrD3faSt7G7ecvyaaahOfY6iyFmQn6zVrLnW6Dl0ECJNFToK8RQErGGArGh4LarRImtbAstAH7QhvIqp9SoKup3CiM7hJ0BJuCG8mhNWg9Z2Q3iND18wNM4mIqOQ1SHldecI90tJFa3lgRHKKWIteAvYNjNJ5UlNkRhSDaW4sshnwli0rTOG39dGjRXJ3wCMAFByAssRfdVWKTDt1S1Va0Fb8xVFarsBLJG/QtA6a4aOWyyM70lcnr+3RB6ZCwqBMSsVYbjXJyuqj5Jbwo9UW4/foRq4ATIk92Vxqw/PKACGR+ZYy7Us8wiG+FyU7CxSoLZE1s61SvbxeKSZydRMvBoFbwtqSnFDfXurLMNJPRoH9hKNAqVByIYNco3LOxTgv/XaNfpUjWurra9qNa4ljWaG1rVy8yan466G2arXa7EVHtoDtRYavNQtFlH1No7U2jgLMiUfAiUA6SDTG8I9vODS921riONp30ic8a22Rz6dmqZRt7FgH0dx8BorgVGBHJoJbh/Jl7Bf8ArJFrSeYtBSo1WrW6ANRD0ly/FohRuVMMvc4nM5LXLk0oZpspigQuo3d+eXqs9RBF4Am+YG7DsuwHgpnEmAMa8wW7XwiGqh62XFTRyYOJFIuEzvWhb/f/2w4ggKGX8yO2AQntu/w0aOlqfuU4BAaEKs7y5jRdeMgKCOSDfY/xB+NUg4ParZ1p90tACqIb7h+Wc+4Rs+rj/nfpw3V8N5pq2AZO8TUbN8+3GaczpXvITmnVWR9UCzT3tUaPaJAVvBcupjisRf5WS/hLKPc7KHIIWPRr31pbrMdXgsDBYg26YMj0YMat5iM1YmSkL6T/mBRvrjGumffU8u6T+W3ymocDzxdT+7CNSPsfU0YzjZrgOzfAmyEAPc3qYU+G8stGHoIsZhk7xmKec6fiU804VnlKxPZdeFImySOYxwGR5qHmZtXkv+C7bbQsInuDdEO9xKrFMcxiYfMVXMAhiES7ubt/oANaBypAdxDfzb0AN46eekC86UPI4mUxbQBRjFeqB4mZLFeM5MDgifAUTF+tGJdzvKZW48Rd9JSbtfTFGaUxkAQnNzndLv3iqlpwro+B3xGGrDb6NZZo0wH/SlyZarF/A1sTNLXoGqU0QsLOobBbImlmuSGxw6mwm8qDAmqtWh76Tns4bfaUNSsngdsQswAGgxIwNg0AA8oAYgnOFOTlipBoAwaEq1tu8yNQCzvPoASOnMl9UACLmn0mkk94e0qAEIZ+nQLx2tyrLvFJ0KUNV/klm1yI0skziQfLgy3pLFd/YH+Nq7Bgf46qgC+D6PAvh0p/TJOwW4YXkeAPuS0wmk0chSoFuIDD2p2MfqQNFWrP96DoGJKwJDy/yFjUrr6Wvg53D8k9OwXfsh/k4j/h7zuC6PiaZA9DFehc5//ahC56s9Cp03AH5e+JDg53tBcqENdtmDtrqPdSY1rAAnO5T1jygFuOh/xEp+/R2iAOfFsprfbdUM/ZuYUmCj2vlrFaq9+mZ6ZiUTLY7P8xe5gC26mHScoPdgLbccnTevLRAtN35qaTFIp1E=
*/