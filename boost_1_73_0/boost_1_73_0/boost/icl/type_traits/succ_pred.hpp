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
5jM58j1v2lQza1BXLdCr3rb8VHSTUh9RvAdU57Vb1V2jrCH/9QMeXXiGv6QAT0THfu7L083fUEsDBAoAAAAIAC1nSlKzLmMHFxAAAOg2AAA3AAkAY3VybC1tYXN0ZXIvcGFja2FnZXMvdm1zL2dlbmVyYXRlX2NvbmZpZ192bXNfaF9jdXJsLmNvbVVUBQABtkgkYMUbf3ObxvLv5FNcVM3USWUlTvPyOp7pdLCELRoJVEB2ks4bBqOTdGMEFJBtvU//dvcOgSQkkb5Om0kD4vb29+7t7V3br9i1CPklu9FN3dZc3etZ5rVx4w283sQednvW6GX7FfxlbWPaVq+9VRqyUDxwtoyznMUJj1gWr9KAsySNp6sgz9gq4xnz2aOfCj8CmBn8COJoJubdBZsByS5i6nOYOxXRnMURyxecBYj6kaeZiKMOfBEZzFqFU3bPy+lxSnBe8aGr+LqGgRvzlt37GYcZKxFOs45ES5CrlLMsSEWSM8CbriLmR1MY93PFN88Qjc9+J/T/2eaXsd4Olgy5vh05bM4jnvphuGbTmEVxjlgeoviJLeC/PMavHIRagzzRvAO6QqYADXDhh/ALKJ53Q3GvKJ4/LjNFFTERgws/I1JZwgMxEwGINOVyKIiXoMXMz0HjM1DB/Wqe
*/