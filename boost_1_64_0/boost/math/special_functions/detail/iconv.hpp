//  Copyright (c) 2009 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ICONV_HPP
#define BOOST_MATH_ICONV_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/round.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace math { namespace detail{

template <class T, class Policy>
inline int iconv_imp(T v, Policy const&, boost::true_type const&)
{
   return static_cast<int>(v);
}

template <class T, class Policy>
inline int iconv_imp(T v, Policy const& pol, boost::false_type const&)
{
   BOOST_MATH_STD_USING
   return iround(v, pol);
}

template <class T, class Policy>
inline int iconv(T v, Policy const& pol)
{
   typedef typename boost::is_convertible<T, int>::type tag_type;
   return iconv_imp(v, pol, tag_type());
}


}}} // namespaces

#endif // BOOST_MATH_ICONV_HPP


/* iconv.hpp
RMff97E4EHhoBLn5LHLbNVoLeAHKKQbekESo+7ucRluOR3BRUtXkCC8fmvMKtrjkJyWninArUqebjsq19DZ4HSBNbDr3kx6JWedpeddy1XCw8AMT+8IiX5RUlPgHDJRApZ/K0RyEsHbVcdd5hmu5o/v9Ub01xkpH1Wj5Db2JZqWyUzCZ/3MugEqLVHJnV0YrKnic6aXv9aK0qtQKQDaK2zM3+1Cjn41x0MferKGES7JvRC7qqohTw4KWXTXKFb6zEUDhqu7JwW4v9RTMk5kiwHpzRMa+QERVz43Thm+PjL/YivyxSZw6ehRw7NnShYllMcrjEbCqA523pGiZQMThTE54t5pcgyr9EvVYP5MFrK8FXvf7nRxdCfK0xiuMuBbV7HZvrvmNtkdlOkyyltPTHQ/hgo64NXMsbKw8DkXFQWvHSd2CtMTrvWEQssmGT3WZ+ihTKTcs5BxDMNLgg0zquF9MNeNf7pOkmIE2fL80BX658eYU+3eCpDnI63WZ2Igv/lt+e0ijUlJ3e9yLY0r/c3l03tk1a7vBPVURALSlAixNkSxrk4vkbkxUzQ==
*/