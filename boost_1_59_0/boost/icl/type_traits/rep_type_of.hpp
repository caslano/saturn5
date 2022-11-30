/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_REP_TYPE_OF_HPP_JOFA_110329
#define BOOST_ICL_TYPE_TRAITS_REP_TYPE_OF_HPP_JOFA_110329

#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(rep)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_rep_type
      : mpl::bool_<detail::has_rep<Type>::value>
    {};

    template <class Rep, class Type>
    struct represents // Rep represents Type;  Type is_wrapper_of Rep
      : mpl::bool_<detail::has_rep<Type>::value>
    {
        typedef represents type;
        BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_< has_rep_type<Type>
                              , boost::is_same<typename Type::rep, Rep> >::value)
            );
    };

    //--------------------------------------------------------------------------
    template <class Type, bool has_rep>
    struct get_rep_type;

    template <class Type>
    struct get_rep_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_rep_type<Type, true>
    {
        typedef typename Type::rep type;
    };

    //--------------------------------------------------------------------------
    template<class Type>
    struct rep_type_of
    {
        typedef typename
            get_rep_type<Type, has_rep_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif

/* rep_type_of.hpp
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
*/