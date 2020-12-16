/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    join.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_DETAIL_JOIN_H
#define BOOST_HOF_GUARD_FUNCTION_DETAIL_JOIN_H

#include <boost/hof/detail/holder.hpp>

namespace boost { namespace hof { namespace detail {

template<class... Ts>
struct join_args
{};

template<template <class...> class T, class Args, class=void>
struct join_impl
{};

template<template <class...> class T, class... Args>
struct join_impl<T, join_args<Args...>, typename holder<
    T<Args...>
>::type>
{ typedef T<Args...> type; };

template<template <class...> class T, class... Args>
struct join
: join_impl<T, join_args<Args...>>
{};

}}} // namespace boost::hof

#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_JOIN(c, ...) typename boost::hof::detail::join<c, __VA_ARGS__>::type
#else
#define BOOST_HOF_JOIN(c, ...) c<__VA_ARGS__>

#endif

#endif

/* join.hpp
tsUmlooti02DoPkA89z5yv3o3Pnn6H70rJ+mbAv/J2OJxf5BwOL//CYL/peYTnd9f6xd21ibzWFbeaM+jaQZEbDbgl9ixoFazRl6T+2EPEfc4iG8I3ishDlpqVVG9Ffjo6EWEYhSwQTlizsWSeULNJFk05OlPDKlJCBlQ4a9Hz0nkjovwbCnfLtTTz7mqXDofViBTc/0iXWdqV9ONnpxol2w3zHPamfwAhLe2O6gzPp6/ePtLvq1ukoXrURSLe11iWuvS8vtyVYK0Z5sefu5tzfBbG9bJ9XeYGrvMm5vYEJ73UNHVYMdkK8DfmUFnZSllc1b23fqU832LzTbH07tj0CLjmCu0X638PTVxxqygh2rD67qsdNBMmjtdlKbgAB1Y7fsRrihrPFc29+W+g+0n9XK9tFaKkSNGGPKRYN5B9EkPLGlTT4QbmDN7mOF5XCHcaxQdwRJaV0u8LPU14nrO9qRB9CoxoiuucPT9eMN43C4BPOPNezWR2DcsC9bURgcCEHUSp/4bJFxKFWk48iqG0mik58WGnG6PJxbpehrfGR3T9+/QqN/8Xm08k+a6VcN8bSsX1Wfyf6/5kt53Gy6TnJ9dROjoT+c8pNmfru626KRgdtOQJ8E3CU6pNuFXolG+oA67QZ1+vY8pXYSdHY8EXHVVbQPATZT2DuLtn4dHg2ZQr8uptPRX/uemTJeq5Vvjh+VcAeVrGxm436Piy3Z5MGLqxOS2DmhaPs1Xeucn9vwydlfN6zGW9jLHUmvKzoOZRfqnJhhoE0fHvO4HPrF2o9VM9EVbvFWETCvn8Ri0sWBIuYUaI+bkdDVFRdfj3w74qJm1XqgHXg95631pJP1YOmln557622Stn/UXtu7497QAUeth4SchtV6nPhTUOtJxZ8ptZ4MAkkxwxDwy9PcSV1hhu4GqYllxF6g7W8Ol6/NkCjpBEjY9pymKP4pbL0/8roS+2OIaU82L+6Txan1kdrP4uHxgofMnsbDo55i3lAxMNLKayZbyalmtnK5/ss/Wi6AaSyBe28w9MtOtKxfxrYnDq6ikwAeNtd0qXO+zGuqoc7Ja6qxbry5pKJYt2fDtlm/pNDdmBhWe03tryH0CIIUQt34KG2qFPwlmMptlZpNkxo6wFF1qcT0yck1tbn+BFWJFuGv/HU+TV33QYKJKoQSUBSyZ0XtI10hOAoamozGYkNVEIu4ruYYNtXBSO/QqfZrnOEXI93rPMdJqOK6WFZX+EB4anp47+ZW0gr1ZE+oMTNyhxRjbpTWys4Fx1W7JLm+PU2gVzyPXsmuN7YIf1ujZT6cFvj/eI7UJ4TYUpRPNfyN9JPg17OZCmPo0T062IR8Btqkv25iOdYa1gBpKgJf4k0iVbXr5F57d7rSjGzbZmH9DXqskumGcAo/j9CdrHCYyE3w4NsDnXpzuKK+uubW92a9DanY2Afi+emDDCfnuRfG5eojc611+oC+D4ShZnHbtYrycYEP9t8WyHGOcurpMI5Udq2SFvx92VzuSjk5MfwLpHMkbr+tXN1hb5eh9nO2mcryw8c95WQtLtgn+mQ9y6vMxPSIdSAlGBHJo7k1n7gGNIAzar8yzQEc3o9w1qFqWuXobe9CAyagViiYzK+/gO9emLkgkQnRFd/hL1ebspOdUc41SB2yeceLym1oXE8/5gH+0BcoSVUwc379xVwHx3VGnDOIerM4DlBr7aXe7P5NmyXXZ7YVMs+WEGQWpZiQ+fNIhgwOkwEQeg66YNuRV5xxsiRNjVwsl/U0WtZSj8pY2odzzKW9tG5KexTXF+Io7E7kDOgOeuE7noknVB8fjv0oxTwgfcYJmZAv/rh89RqunwpZKsNZ0MZt0bY=
*/