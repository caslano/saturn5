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
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
*/