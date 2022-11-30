/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   function_traits.hpp
 * \author Andrey Semashev
 * \date   30.08.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_FUNCTION_TRAITS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_FUNCTION_TRAITS_HPP_INCLUDED_

#include <boost/mpl/has_xxx.hpp>
#include <boost/log/detail/config.hpp>

#if defined(BOOST_NO_SFINAE) || defined(BOOST_MPL_CFG_NO_HAS_XXX)
#   if !defined(BOOST_LOG_NO_FUNCTION_TRAITS)
#      define BOOST_LOG_NO_FUNCTION_TRAITS
#   endif
#else

#include <boost/mpl/int.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/is_nonmember_callable_builtin.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

    //  A number of traits to deal with functors
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_argument_type, argument_type, false)
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_first_argument_type, first_argument_type, false)
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_second_argument_type, second_argument_type, false)
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_arg1_type, arg1_type, false)
    BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_arg2_type, arg2_type, false)

    namespace has_arity_no_adl {

        typedef char yes_type;
        struct no_type
        {
            char dummy[2];
        };

        template< typename FunT, int ArityV = FunT::arity >
        struct checker
        {
        };

        template< typename FunT >
        yes_type has_arity_impl(FunT const&, checker< FunT >*);
        template< typename FunT >
        no_type has_arity_impl(FunT const&, ...);

    } // namespace has_arity_no_adl

    //! The metafunction detects if the type has an arity static constant member
    template< typename FunT >
    struct has_arity
    {
        static FunT const& get_FunT();

        enum value_t { value = (sizeof(has_arity_no_adl::has_arity_impl(get_FunT(), 0)) == sizeof(has_arity_no_adl::yes_type)) };
        typedef mpl::bool_< value > type;
    };

    //! The metafunction results in an unqualified type with removed reference
    template< typename T >
    struct root_type :
        public remove_cv<
            typename remove_reference<
                T
            >::type
        >
    {
    };

    template<
        typename FunT,
        bool = function_types::is_nonmember_callable_builtin< FunT >::value,
        bool = has_argument_type< FunT >::value,
        bool = has_first_argument_type< FunT >::value,
        bool = has_arg1_type< FunT >::value
    >
    struct first_argument_type_of_impl
    {
    };
    template< typename FunT >
    struct first_argument_type_of_impl< FunT, true, false, false, false >
    {
        typedef typename root_type<
            typename mpl::front<
                typename function_types::parameter_types< FunT >::type
            >::type
        >::type type;
    };
    template< typename FunT, bool HasFirstArgumentV, bool HasArg1V >
    struct first_argument_type_of_impl< FunT, false, true, HasFirstArgumentV, HasArg1V >
    {
        typedef typename root_type<
            typename FunT::argument_type
        >::type type;
    };
    template< typename FunT, bool HasArg1V >
    struct first_argument_type_of_impl< FunT, false, false, true, HasArg1V >
    {
        typedef typename root_type<
            typename FunT::first_argument_type
        >::type type;
    };
    template< typename FunT >
    struct first_argument_type_of_impl< FunT, false, false, false, true >
    {
        typedef typename root_type<
            typename FunT::arg1_type
        >::type type;
    };

    //! The metafunction returns the first argument type of a function
    template< typename FunT >
    struct first_argument_type_of :
        public first_argument_type_of_impl< FunT >
    {
    };


    template<
        typename FunT,
        bool = function_types::is_nonmember_callable_builtin< FunT >::value,
        bool = has_second_argument_type< FunT >::value,
        bool = has_arg2_type< FunT >::value
    >
    struct second_argument_type_of_impl
    {
    };
    template< typename FunT >
    struct second_argument_type_of_impl< FunT, true, false, false >
    {
        typedef typename root_type<
            typename mpl::front<
                typename mpl::pop_front<
                    typename function_types::parameter_types< FunT >::type
                >::type
            >::type
        >::type type;
    };
    template< typename FunT, bool HasArg2V >
    struct second_argument_type_of_impl< FunT, false, true, HasArg2V >
    {
        typedef typename root_type<
            typename FunT::second_argument_type
        >::type type;
    };
    template< typename FunT >
    struct second_argument_type_of_impl< FunT, false, false, true >
    {
        typedef typename root_type<
            typename FunT::arg2_type
        >::type type;
    };

    //! The metafunction returns the second argument type of a function
    template< typename FunT >
    struct second_argument_type_of :
        public second_argument_type_of_impl< FunT >
    {
    };


    template<
        typename FunT,
        bool = function_types::is_nonmember_callable_builtin< FunT >::value,
        bool = has_arity< FunT >::value,
        bool = has_argument_type< FunT >::value,
        bool = has_second_argument_type< FunT >::value
    >
    struct arity_of_impl
    {
    };
    template< typename FunT >
    struct arity_of_impl< FunT, true, false, false, false > :
        public function_types::function_arity< FunT >
    {
    };
    template< typename FunT, bool HasArgumentTypeV, bool HasSecondArgumentTypeV >
    struct arity_of_impl< FunT, false, true, HasArgumentTypeV, HasSecondArgumentTypeV > :
        public mpl::int_< FunT::arity >
    {
    };
    template< typename FunT, bool HasArgumentTypeV >
    struct arity_of_impl< FunT, false, false, HasArgumentTypeV, true > :
        public mpl::int_< 2 >
    {
    };
    template< typename FunT >
    struct arity_of_impl< FunT, false, false, true, false > :
        public mpl::int_< 1 >
    {
    };

    //! The metafunction returns the arity of a function
    template< typename FunT >
    struct arity_of :
        public arity_of_impl< FunT >
    {
    };

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // defined(BOOST_NO_SFINAE) || defined(BOOST_MPL_CFG_NO_HAS_XXX)

#endif // BOOST_LOG_DETAIL_FUNCTION_TRAITS_HPP_INCLUDED_

/* function_traits.hpp
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
*/