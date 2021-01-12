/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(segment_type)
    }

    template <class Type>
    struct has_segment_type 
      : mpl::bool_<detail::has_segment_type<Type>::value>
    {};

    template <class Type, bool has_segment_type> 
    struct get_segment_type;

    template <class Type>
    struct get_segment_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_segment_type<Type, true>
    {
        typedef typename Type::segment_type type;
    };

    template <class Type>
    struct segment_type_of
    {
        typedef typename 
            get_segment_type<Type, has_segment_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* segment_type_of.hpp
LoIpoKUZQsM10WXlmtoNawy1+cQhCTCEIzp++2pHwoKotSd5NjhJlPzgCqgTZk8ZsOSX0XU9YtnmMitXRWuBSlnr2yUtotDnUui3RrcID58yPMTJQ9jFQ9zFA5mXjHBxKCQ2POyQKOkYH6dw9kXbyrX+7lKMyAQz2l6ux7af1zBQzR1eTJW3h2dpmSxzpR+CQLaaz9e4Ws3jkh6drk+eXo5ft15RAWfbtUfV3dg9GNoOwkIX
*/