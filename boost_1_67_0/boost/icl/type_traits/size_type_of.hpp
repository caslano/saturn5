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