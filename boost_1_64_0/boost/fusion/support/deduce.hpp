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
oNB6rmb1JgpfTf8d2BKMXoh0ojDG2Gd6XrX6YARqhbD75uXwkivzNZNRWPAguNlvXnQd2jgCVgfyjQE5dSDt6LSlDTco7WEzLQ138+67H6SRzTfxkXnH/YhpyO5dx+wBQ/M3YNbe4iBi0MAK7cIOaRowmf03bMFg/+XYTyG9leWO/lBDH91C0/c82JJ41eqWgNWxo/39JqiQbZpX9sRhOG0bX/xWBntmfu4xS4FM6lMkZjfemfi4Lro1sZmStya4RXjzFz55kesCWls5gtEp2Paau41Lw5Ig7+soHVK1tH8S2mhnvGppu7d1aKYZMLbVo/e78bWKslSZMtoRM/hIDJSvDxQvzfU5zI92AA2XL7h37esDjT2tJzUYo91Is/Trlm5SawAom1engd7Y4qPSBHOpurnoWdQunou8CqqbHX7DDFEan/BrA+9AqoeWth20bwkGFkcPrrat7jhtMCiENDH3Hea3fSwmiP5nZwzGV7LhWF3Z18NsrSP/rfZTGu7dnPpfRswkxZot7+oBisPtm9P/o4M+Zrhl22d1Fum6Lm1Ad4My2VkfyxbbHdj16LBxZQ8hvTWixLYF2i2Qptue5IB+8W+JmMYTcvuufHMbpjQsw2cpxsx4toyrtyL0rpxIB1tTQjczHNLfROlNEdx5/LO36eg42nB+Wrwt0PT49kRSzwMW95sOR0QNgTgPjQ4Drj8v7lzAee4PPt3kZOfC9dt5mG4CRszfCSY6Je2ch2VZvH0PY3LCNYbQ/TnzxB0cuuGtun09mT8qlmU8E0lS3ugE4s4fX/XHsbfuXh4YHFG472wPnbl2fRoxdvxQKLbjg2c6LCqXPfn6i8FQha6lLxyg9L5t6u4spXe2qSj/tzB0ooy19XnbLZHels2MeKyQY49+4lYGS5WRdm3QdDumJ7bfmVtTDPgj24Fx397NbYGyxVnfj96GYhsHmGZT6MbieRPFTewTjLV+W4sdu2Uc2/S+SDB+eu4a8ezDBusr+VAOXnp7xLRT2NrYzGJ2PNzjDhpDpA7b4cQdNW3yhZR7//qvBkdaHmnvvhPQuj0dXI5vrTkxru+MNKpEd2RZ3QUxRFnu7sdWjgDGm+9wK4i4X0zE4VYQcet3BdzN2Fv+YSIOEyT269t309i959C/eHR/fhzdHTFkP6kfpT60S2cyhuxjsW3vMRkL5bL758kYd7+L7faMe07EemvBXybjtMxjWq+910QMtknVnb97c3adFlma3vCUPfVwZ87+yuC/X6K6e8R4QPDHDL6bonBs/5PiDAy3L3p4YppgS0Gx9ALWxmqZsTgYfRbgvmFFjKcYx/542z7ATF6/7Vv/Z5C7qDoW0Moi0u6F9bjUW9hOS4NnicMuz6NlKIsoTXIGcOswD/14A5bc6SSKC14V3n1QyzaD7wtcvoplPAiCKJfMaVi8x8U3qi+Zct4x5KoSYZ0nNuJC/94oJWWLWFYVPFa8u4jjVbQU1WD5WS323qwRPs5kmYZKxLFzRwLMT+GyVrzltO29S9s7yUSSFklkszz1NGWyQ58Rc64PzuM8jIIqiCvWucarun65dtGp/6MyaIAgjRjRGyt8w0nbtwoyCWhTjDhL+OnFrugc74F7fVnHaaqyqOPCwXy65xviJsIXsCwvBU+ky9c0Wr9/rvT6J5ZpllU14XsKP5WJp1Fb84trA6cd6kAVKpUB+PY4gQpnxP7GzeNRSQ2CLCKpsVZVi3GJXWzJIlmUWRllGjwEF97rmyO817k/+pgCHuKHN1V5GknR5TBcafYqff5/ox+KZ7rvbPI6yyWMY82N/Up9TLn4UrveS0MRNBUyKifMY71rA/UcN0Z2ospYJDxnrl5upcMuuOk=
*/