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