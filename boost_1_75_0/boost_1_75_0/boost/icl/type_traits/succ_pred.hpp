/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SUCC_PRED_HPP_JOFA_080913
#define BOOST_ICL_TYPE_TRAITS_SUCC_PRED_HPP_JOFA_080913

#include <boost/icl/type_traits/is_increasing.hpp>

namespace boost{ namespace icl
{
template <class IncrementableT>
inline static IncrementableT succ(IncrementableT x) { return ++x; }

template <class DecrementableT>
inline static DecrementableT pred(DecrementableT x) { return --x; }

namespace detail
{
    template <class DomainT, bool increasing = true>
    struct successor;

    template <class DomainT>
    struct successor<DomainT, true>
    {
        typedef successor type;
        inline static DomainT apply(DomainT value){ return ++value; }
    };

    template <class DomainT>
    struct successor<DomainT, false>
    {
        typedef successor type;
        inline static DomainT apply(DomainT value){ return --value; }
    };

    template <class DomainT, bool increasing = true>
    struct predecessor;

    template <class DomainT>
    struct predecessor<DomainT, true>
    {
        typedef predecessor type;
        inline static DomainT apply(DomainT value){ return --value; }
    };

    template <class DomainT>
    struct predecessor<DomainT, false>
    {
        typedef predecessor type;
        inline static DomainT apply(DomainT value){ return ++value; }
    };
} // namespace detail

//------------------------------------------------------------------------------
template <class DomainT, class Compare>
struct successor
{
    inline static DomainT apply(DomainT value)
    {
        return detail::successor
            <DomainT, is_increasing<DomainT,Compare>::value>::apply(value);
    }
};

template <class DomainT, class Compare>
struct predecessor
{
    inline static DomainT apply(DomainT value)
    {
        return detail::predecessor
            <DomainT, is_increasing<DomainT,Compare>::value>::apply(value);
    }
};

}} // namespace boost icl

#endif



/* succ_pred.hpp
vLfCurdb3ltp3dsj762y7j0h73XJfbh8j/whV4sh495++oIiXXL9KW8/NlDs3ht7gV72AZ1A6oU0CGkC0kVIl56FvoZ0FdJXkL6D1PIc0BukPkiDkD4GYG4ogFJ+nZcFnu2g4hdA+h4Sirnoy7F1ETVmeBHlacT/0/WBXRLwgW0J+MAuDfjALgv4wLbKe8E4ALn98Qng9AtI30L6EXEO+OyDNARpAtLFZ4vhkffq7A2MM5OeWgw6eQf66LLRT+xnuy4rY2tWxh7vnj1WhUN/HwEdjEDZtQAd4PeuHDjbVB3dRr2dTh1fQR3fIc05dTAuXPiwDpNvmLioQBl7nHLwc6AEPnG8fGOUcVWQLKblrLWL2Hfd3EOEcP74ovYb7Rr058Yb8H2P+m7KUKZMhIR1MShbmbJbzdoDFYLBrJfnqG/h2aVBahu26Zz46cakSQPmuLoM7f0M0nVINyCtg7m+/4Ddp+b4+V7dN2mC+/iiQXctgmjxI+Me0ecS8bFBH52C5qZPjXs0ry0VV417NK+hrLg4q5fmtVbr3j2C5ibzHs117da9+wTNTZeNOirCn5vUFoRScwTKSxchzb4ArR4gWbDtV8DvIfVCGoB0FNIUpLd/Fcd1jOfzOAvxg0vGvTYD9o8BnqMv2HXh53sBvhUbq93w/t5AGSGegbpgCI4bAEenUcaYuDljItSHHwEcVyFdh3QDUtdAuC+GAjAu
*/