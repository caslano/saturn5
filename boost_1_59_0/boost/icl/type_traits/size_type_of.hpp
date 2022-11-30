/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SIZE_TYPE_OF_HPP_JOFA_080911
#define BOOST_ICL_TYPE_TRAITS_SIZE_TYPE_OF_HPP_JOFA_080911

#include <boost/mpl/has_xxx.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>

namespace boost{ namespace icl
{

    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(size_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_size_type 
      : mpl::bool_<detail::has_size_type<Type>::value>
    {};

    //--------------------------------------------------------------------------
    template <class Type, bool has_size, bool has_diff, bool has_rep> 
    struct get_size_type;

    template <class Type> 
    struct get_size_type<Type, false, false, false>
    { 
        typedef std::size_t type; 
    };

    template <class Type, bool has_diff, bool has_rep> 
    struct get_size_type<Type, true, has_diff, has_rep>
    { 
        typedef typename Type::size_type type; 
    };

    template <class Type, bool has_rep> 
    struct get_size_type<Type, false, true, has_rep>
    { 
        typedef typename Type::difference_type type; 
    };

    template <class Type> 
    struct get_size_type<Type, false, false, true>
    { 
        typedef Type type; 
    };

    //--------------------------------------------------------------------------
    template<class Type> 
    struct size_type_of
    { 
        typedef typename 
            get_size_type< Type
                         , has_size_type<Type>::value
                         , has_difference_type<Type>::value
                         , has_rep_type<Type>::value  
                         >::type type;
    };

}} // namespace boost icl

#endif



/* size_type_of.hpp
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
*/