/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONCEPT_EQUIVALENT_HPP_JOFA_090830
#define BOOST_ICL_TYPE_TRAITS_IS_CONCEPT_EQUIVALENT_HPP_JOFA_090830

#include <boost/mpl/and.hpp> 

namespace boost{ namespace icl
{

    template<template<class>class IsConcept, class LeftT, class RightT>
    struct is_concept_equivalent
    {
        typedef is_concept_equivalent<IsConcept, LeftT, RightT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<IsConcept<LeftT>, IsConcept<RightT> >::value)
            );
    };

    template<template<class>class IsConcept, class LeftT, class RightT>
    struct has_same_concept
    {
        typedef has_same_concept<IsConcept, LeftT, RightT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<IsConcept<LeftT>, is_concept_equivalent<IsConcept, LeftT, RightT> >::value)
            );
    };

}} // namespace boost icl

#endif



/* is_concept_equivalent.hpp
rY7NfnDwTmBaktcsWA5710AnD/1PW3x9ns9HGZozgDkcQ0y17gGqsbSOkM92cYFes0gJeZ5EZmsX20KqDTnaNb0hudQrzZAuyRe4fLF/xMz8tsWfuCy9fzJv3jZhxhc1DVcu7N/tTaY0eDRUGEGt83FcE2uwZSpYK1KX11ZwaEfUZwDY0KtlL4Yg5wgxSgPoFwW44iUlMUun8zkOuw/6OCsx5nO4SNcqKgYDv4sBGIkckIo6awSB9qKkro21NybuhQLiRIk3PcJXaUx+TKo8wd/t4Gq0rOTJjSVjeTY8Dr9muiK9iRm+GpeuCujJHu7hFTy75yxi/VWEe9hOGnw8p9sHP6z/5ZzuhIJnEZs1RrO/7OPT5jlhnjf1MwIVxagwg95luWwGr0T+MKUVP4aWywIglTQcZPuIgTkjpzBrzK3044UeC54vMy0TamgpBz1wJBg6va4bk68l1QKEwN3QHLDvHhuPHTo9AmSQhvt6iY5TvjsI4fk912RdoexYcDIzj8QqnRa3f2lBKVPAS7fVrAiC5SnG5Yr4FBlEhIeWVw/XPHhoGHvq9tBuhw==
*/