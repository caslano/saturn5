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