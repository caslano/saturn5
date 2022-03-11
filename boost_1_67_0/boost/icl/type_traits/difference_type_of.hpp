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