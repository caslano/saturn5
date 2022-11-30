/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_DIFFERENCE_TYPE_OF_HPP_JOFA_080911
#define BOOST_ICL_TYPE_TRAITS_DIFFERENCE_TYPE_OF_HPP_JOFA_080911

#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/type_traits/is_pointer.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/no_type.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>
#include <boost/icl/type_traits/rep_type_of.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(difference_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_difference_type 
      : mpl::bool_<detail::has_difference_type<Type>::value>
    {};

    //--------------------------------------------------------------------------
    template<class Type> // type_of(T-T)==T
    struct is_subtraction_closed
    {
        typedef is_subtraction_closed type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_numeric<Type>
                             , mpl::and_< has_rep_type<Type>
                                        , mpl::not_<has_difference_type<Type> > 
                                        >
                             >::value)
            );
    };

    //--------------------------------------------------------------------------
    template<class Type>
    struct has_difference
    {
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_subtraction_closed<Type>
                             , is_pointer<Type> 
                             , has_difference_type<Type> >::value) 
            );
    };

    //--------------------------------------------------------------------------
    template <class Type, bool has_difference, bool has_diff_type> 
    struct get_difference_type;

    template <class Type>
    struct get_difference_type<Type, false, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_difference_type<Type*, true, false>
    {
        typedef std::ptrdiff_t type;
    };

    template <class Type>
    struct get_difference_type<Type, true, false>
    {
        typedef Type type;
    };

    template <class Type>
    struct get_difference_type<Type, true, true>
    {
        typedef typename Type::difference_type type;
    };

    //--------------------------------------------------------------------------
    template<class Type> 
    struct difference_type_of
    { 
        typedef typename 
            get_difference_type< Type 
                               , has_difference<Type>::value
                               , has_difference_type<Type>::value
                               >::type type;
    };

}} // namespace boost icl

#endif



/* difference_type_of.hpp
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
*/