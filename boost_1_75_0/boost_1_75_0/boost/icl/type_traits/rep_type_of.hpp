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
qub8l7F9cBK22JAqlaVZajr75ODy9Brsb438VEqKn1jemGWhr0oaQX3jpfZf2WNLGy9zpkrqXLJYV3S9dJ0k/MwXNz7mzxYcOjnskNo2XuNjC2cj+O+l0FuRk0QQOtBN/0kTgcOaYKBJv1xPjchUBz6ePVcuNG79IYE/lXRbMzrV75wRzyK1DMxofL+/+9AH72w93P77a2aR/fGh86ZKBvOEYst5WMVfUNGUZ7nrcx8vm2YrRSQoGfCFUyz419v9hVg31vF9oHCVp+iktnJbG/OcWteYBnaJ6VBvdUSzzc9DatuMn+/uV5fH5gsKUxVDB85Nn1IwHoTco42cZYcj9AuiYFOKozJo5u2yGwtxQPfGNSahn/JTgsRh3tqDMVQ6ofoV0f5DYkXKemid9AsaccJljjujLNGK9Av5vvHDfJE3O8IjGdrZdUzabPcHHOWB4f1Lf2v03TfAafYc3jUvHBRNvoeSRDRtOVE14VWfyQEswsmgrzuqLlS+lJuNCNZT7wt1nkXVku5QeNNP2VbG7QmWYHR/x9YyX2mvi/v9LfDlRqTQOWtMd4Om7VQE9ELlA6wgfrH3kv+Gd9qkcKvyjPJsgkiHX/3EYBvHhn65gtrCL/+hSZrpKXrM8y5LFV0wmd0JNohEEWxhCQcdQavTAo1HL221sUMXjfivaH4Yj05VvhPueb4yRoPF62e6MyTrenTZkl7M0R10iKfv
*/