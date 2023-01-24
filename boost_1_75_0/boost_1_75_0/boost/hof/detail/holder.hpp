/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    holder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_HOLDER_H
#define BOOST_HOF_GUARD_HOLDER_H

namespace boost { namespace hof { namespace detail {

template<class... Ts>
struct holder
{
    typedef void type;
};

template<template<class...> class T>
struct template_holder
{
    typedef void type;
};

}}} // namespace boost::hof

#endif

/* holder.hpp
58HYOFmuliHaj2jepe7KxEhmvNEuJg+QLHovI27K5D9T+6CdoZ4GsRuxEPml96u4/7VxM6fmToN0PrkE8MpLqK41bl+F7VEQwUYk16KFyHiLvWtgY9IhS79at3wiw9s1a9EJkGqqDaydmsDVJpy2sJFf/W3mbC0ZDRTLd0WInA4ZHmZpibgR7XGynPPZpkA10IuULeZYoLtZE1Ond94Xnpdy+unBI4dVV9YYi1eGe2YF0xVIBp8S0oxe9XibSqOMRdtTehPW+omHcCtDpLyM17b4fbkpp8bNTP+sKVsxyUbO6IWqRlRni3NAp34nfFdEghchDdWZgzIEcgMfBVWMOIu2eoTXSHSKKwIXWnqRTDElpP5s9kKoYW3QGwHN++yQ9XOMdsuGNYFsRM7Q3clpop1ZXLcNkdO8w2KUgbBHMC6wep+60LYv2mt1wNrFrPSUABsJsmkSrZAwOj+uo5iZuLnfLD+migpOpjmZbpYONNC2oxTQo1lK0cZX2Qxc35eGMxCJ4jDLVwwyAIGF7TUFkCTzzchvUTfW+Mkskel9u1T6aXQAlMFu13tuK3hx9wPEdM8zSlbMQedrYLaR2/EcH0nK1C+B8Z6riqmtt3fct3c1MlDWiJ0OhDRvY2YfnUJy/XqYlrWkFMOqtCKdQebtC+mVT9om3JUyi9jUgV5fv0b++tC4V6uBO95bGKP6EQukVIVk+cgTZN+myGLr
*/