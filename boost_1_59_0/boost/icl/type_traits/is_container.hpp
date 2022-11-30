/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828
#define BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/element_type_of.hpp> 
#include <boost/icl/type_traits/segment_type_of.hpp> 
#include <boost/icl/type_traits/size_type_of.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
    }

    template <class Type>
    struct is_container 
      : mpl::bool_<
            detail::has_value_type<Type>::value &&
            detail::has_iterator<Type>::value &&
            detail::has_size_type<Type>::value &&
            detail::has_reference<Type>::value>
    {};

    template <class Type>
    struct is_std_set
    {
        typedef is_std_set type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::and_< is_container<Type> 
                              , detail::has_key_type<Type>
                              , boost::is_same< typename key_type_of<Type>::type
                                              , typename value_type_of<Type>::type >
                              , mpl::not_<detail::has_segment_type<Type> >
                              >::value )
        ); 
    };

}} // namespace boost icl

#endif



/* is_container.hpp
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
*/