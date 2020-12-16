/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_NESTED_XXX_IF_NOT_PH_HPP
#define BOOST_FLYWEIGHT_DETAIL_NESTED_XXX_IF_NOT_PH_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/flyweight/detail/is_placeholder_expr.hpp>
#include <boost/mpl/if.hpp>

/* nested_##name##_if_not_placeholder_expression<T>::type is T::name unless
 * T is an MPL placeholder expression, in which case it defaults to int.
 */

#define BOOST_FLYWEIGHT_NESTED_XXX_IF_NOT_PLACEHOLDER_EXPRESSION_DEF(name) \
struct nested_##name##_if_not_placeholder_expression_helper                \
{                                                                          \
  typedef int name;                                                        \
};                                                                         \
                                                                           \
template<typename T>                                                       \
struct nested_##name##_if_not_placeholder_expression                       \
{                                                                          \
  typedef typename boost::mpl::if_<                                        \
    boost::flyweights::detail::is_placeholder_expression<T>,               \
    nested_##name##_if_not_placeholder_expression_helper,                  \
    T                                                                      \
  >::type::name type;                                                      \
};

#endif

/* nested_xxx_if_not_ph.hpp
EaC1XNhlVeflhf85dESl5PWJ4pp4stpFK5lPOrk46pS7pT4ewz2WkXUGR8J4zWH6apAJnswwW4ndr8QI3w9lc4peIHn/lUxxCNgGDvj9VwWZtrq/rHEZFGYtTFJlCxnnUW3hxR0NTTG2uSBrDsz2/xdnipb6ua4DShTCBmlfR4l+Ok39xNM7RjsMww3cNIBEjIbXk8E3BK6XvgR8WopPbQKjqJip0YZ30NWA7zYTGrQbmkMvTKbJpotS4hVZoj2UMCrpsnSV4VbYEgS66Eo6VwehpHtYIjiXKYe9h1LuAEEL449lC0XjmjuBiu/OBy+NMs/k/7SfYh/TuI49+5jCfmb7lIdbRWAfk0fgOnTDW4/avb/vUekdX9sevUf6mun9oXsE9C7ua77/e4sd/fWtBKbVa1RS/OO+qv+DVHv8lA3hp3b3SOIH7+5jht/VIoL2eKSPqT1uH2qnPfoTmFa5YQntkUmFCO/iWvba41xvMz+/No+An429TfwsvLl0/w5NjedX3end0l5eN5/oQzWpupkM3D8Jq2wnuTaKgkgxNcikYXu2h82O5egVxfLrKh+N0K4B6KvaxEjvoab24r/mKwQjlbrD6yoywmuqnMruLc/PBHC5mlADpsDg5bqtxxMtxST4M34SVC6Byn2ilJsty72vl0uhcquVctNkuWWiHD9GyYVUIi0P5Fcoeo8suqaCJLE6obxOQXmzLNdXokSRtb/kamIPSfjEKyVtE1vp1RdkSPwTEf9vbXT8D90rJvlTDSPtxT/ux9If8bqrTP5Btg40b/zTXNYbf7k/+UcVsfH/kVwQ6FlaFbHxVzcPg9RNBun8KIi4HvJjh3Z9Bab/ywUych0Q9GM6PqDdfxFJUTVQiqLYKpOYojkt1BfIv67hO9apaEdxNQGebCYAh5kAEyTgrQKwJwJWJsAZssYmJsDqErCxAKyAgEdJOHtW1nh6ohEwRQKeGkyAzOO2/3kC7C0B3yDA2gLQQ1tEaKdbK/E93hK5x3uUNEdDm0mXJ0/JjdNHWRZ7vJykcHu8lkmGPV5mktjj1YXVO5Dp/xaCqCtbtvlUs78pbdkMNV+TJbZsVzID/b+aj0fL72dMT1MkJPGl6F9UWjK8GU5f3g7jnkx+NjmV5GaFvig9az5kya9mCJt6kqahYpDeQSqVF2YWdDXrne5ycr2TLPNJGSlWq8m74AhKXpK5nENl0Ug9TgMuibSVDcHQ0f8DjtljKEETEfQVS0ufg+3Mc8pxTK5SUd0yYfIKNeBQtnZ7Mh/acw0NuqGuUf3qCvgU8roQeQlEXiGISIH+2r5uQp1IQjhp9Ui3CPCtxB7WaPdJ0S7UXvVffZ7r/wPs7moqjfdfGsnxPl2O99tbi/E+sby4ctEDhgvqQL2U4NUGgiv3v8inkBv2PvFor2J0gQM5/DX4yysIS9HXaYq7oaXw/Lca9PP6vfi3oKCckjJ02WOEsBYloDOo/ZLGoSQDUBG8QQ/4V0HXUNGX4nlREhdaQ78NhMDShBTkFFnwKhhfalX5vK6VcTAAGl2yC/Oq/VM3Epo3DlTtn+LtyNtfdSXQyQO5/dN1Nux11nCgBl7V/inOTn0FHPS7btz+yU592Rzohlaq/ZOt+mI4aN1W3P7pWg5V6n3J3V0YpHBFylYtcGPtI/+UzHrd4CMog1be47BRF/pVj9C8eujG0fsluHzI0BqVp7H+4D04rCltBqSxTwQlftUhqlv4PcURnKbf4sykKnELMLEVExFq6Snd4rkRudgxwDWFDn4fgLb8UC8V1QThHlTgkizgYi7NqLbu/1zuxbaZ2v+xtvqfgz7ejPf/YNv939l4NUm7p4bRqUaM/6cS+nOQtjI=
*/