/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_SUPPORT_DEDUCE_HPP_INCLUDED)
#define BOOST_FUSION_SUPPORT_DEDUCE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/ref.hpp>

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <functional>
#endif

namespace boost { namespace fusion { namespace traits
{
    template <typename T> struct deduce;

    //----- ---- --- -- - -  -   -

    // Non-references pass unchanged

    template <typename T>
    struct deduce
    {
        typedef T type; 
    };

    template <typename T>
    struct deduce<T const>
    {
        typedef T type;
    };

    template <typename T>
    struct deduce<T volatile>
    {
        typedef T type;
    };

    template <typename T>
    struct deduce<T const volatile>
    {
        typedef T type;
    };

    // Keep references on mutable LValues

    template <typename T>
    struct deduce<T &>
    {
        typedef T & type;
    };

    template <typename T>
    struct deduce<T volatile&>
    {
        typedef T volatile& type;
    };

    // Store away potential RValues

    template <typename T>
    struct deduce<T const&>
    {
        typedef T type;
    };

    template <typename T>
    struct deduce<T const volatile&>
    {
        typedef T type;
    };

    // Unwrap Boost.RefS (referencee cv is deduced)

    template <typename T>
    struct deduce<reference_wrapper<T> & >
    {
        typedef T& type;
    };

    template <typename T>
    struct deduce<reference_wrapper<T> const & >
    {
        typedef T& type;
    };

    // Also unwrap C++11 std::ref if available (referencee cv is deduced)
#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
    template <typename T>
    struct deduce<std::reference_wrapper<T> &>
    {
        typedef T& type;
    };

    template <typename T>
    struct deduce<std::reference_wrapper<T> const &>
    {
        typedef T& type;
    };
#endif

    // Keep references on arrays, even if const

    template <typename T, int N>
    struct deduce<T(&)[N]>
    {
        typedef T(&type)[N];
    };

    template <typename T, int N>
    struct deduce<volatile T(&)[N]>
    {
        typedef volatile T(&type)[N]; 
    };

    template <typename T, int N>
    struct deduce<const T(&)[N]>
    {
        typedef const T(&type)[N];
    };

    template <typename T, int N>
    struct deduce<const volatile T(&)[N]>
    {
        typedef const volatile T(&type)[N];
    };

}}}

#endif


/* deduce.hpp
kPdp2LKHYQE5NNWzlQ+lR2d4hJPjr8f4wubkOMa50JIUZp70kuxDjNO88XwvxdNTz9FZDPIQqrejmpfSwZnCPwpL4L2SGWlHOYRDTi6zcskvUsOXhEIqwnBysxiNf8R4LGVWBpJnU8OVplY5SrEmWMpIrrcclbAepmA4k+fSeSasvTS6x9oET3blAkeQF8oZiLWQSixZSHiU3lfuW5JktVVcfZKbzCXZy/F7pV+9nmTBRazEM0zl4Q1qRzFCZoyVyWURLDeEnVW9VNKV8b4altJ5YiwcKRW4GCfJbcsmzHbtiUMaKq5Y+mCc0S5IPZZm9SaR+xhYitpqFuI+cFJuuM0xav6cbJPcnPxFYtfTpsEfjmZfbw6juRi0BjOMZi0shZMuxt1ofjW5neNuMJ0OxvMFJpcYjBeB7OdofM6jlyxmQU+VJcfiFnJVKUn5TvPzVhJFbakzVeeE0zC97QjLs727pXgMPMNWFPG5av5Iw+mlLgx+R8DOF2DpayA8+vvgMAQbmpQUrUh7hJd+9Kf/nrQ7/JcqFUqZrLM2Mj/qR8HgbTxTJHRddd7RFMEwJmqT5h8Wku4H/3/gLvwFUEsDBAoAAAAIAC1nSlLoaRzdiQMAAF0HAAAhAAkAY3VybC1tYXN0ZXIvbGliL2Zp
*/