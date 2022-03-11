/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   parameter_tools.hpp
 * \author Andrey Semashev
 * \date   28.06.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_PARAMETER_TOOLS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_PARAMETER_TOOLS_HPP_INCLUDED_

#include <boost/mpl/or.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/sfinae_tools.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_MAX_PARAMETER_ARGS
//! The maximum number of named arguments that are accepted by constructors and functions
#define BOOST_LOG_MAX_PARAMETER_ARGS 16
#endif

// The macro applies the passed macro with the specified arguments BOOST_LOG_MAX_PARAMETER_ARGS times
#define BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(macro, args)\
    public:\
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_LOG_MAX_PARAMETER_ARGS, macro, args)

#define BOOST_LOG_CTOR_FORWARD_1(n, types)\
    template< typename T0 >\
    explicit BOOST_PP_TUPLE_ELEM(2, 0, types)(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        BOOST_PP_TUPLE_ELEM(2, 1, types)((BOOST_PP_ENUM_PARAMS(n, arg))) {}

#define BOOST_LOG_CTOR_FORWARD_N(n, types)\
    template< BOOST_PP_ENUM_PARAMS(n, typename T) >\
    explicit BOOST_PP_TUPLE_ELEM(2, 0, types)(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& arg)) :\
        BOOST_PP_TUPLE_ELEM(2, 1, types)((BOOST_PP_ENUM_PARAMS(n, arg))) {}

#define BOOST_LOG_CTOR_FORWARD(z, n, types)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_CTOR_FORWARD_1, BOOST_LOG_CTOR_FORWARD_N)(n, types)

// The macro expands to a number of templated constructors that aggregate their named arguments
// into an ArgumentsPack and pass it to the base class constructor.
#define BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_FORWARD(class_type, base_type)\
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(BOOST_LOG_CTOR_FORWARD, (class_type, base_type))

#define BOOST_LOG_CTOR_CALL_1(n, types)\
    template< typename T0 >\
    explicit BOOST_PP_TUPLE_ELEM(2, 0, types)(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy())\
    { BOOST_PP_TUPLE_ELEM(2, 1, types)((BOOST_PP_ENUM_PARAMS(n, arg))); }

#define BOOST_LOG_CTOR_CALL_N(n, types)\
    template< BOOST_PP_ENUM_PARAMS(n, typename T) >\
    explicit BOOST_PP_TUPLE_ELEM(2, 0, types)(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& arg))\
    { BOOST_PP_TUPLE_ELEM(2, 1, types)((BOOST_PP_ENUM_PARAMS(n, arg))); }

#define BOOST_LOG_CTOR_CALL(z, n, types)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_CTOR_CALL_1, BOOST_LOG_CTOR_CALL_N)(n, types)

// The macro expands to a number of templated constructors that aggregate their named arguments
// into an ArgumentsPack and pass it to a function call.
#define BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(class_type, fun)\
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(BOOST_LOG_CTOR_CALL, (class_type, fun))

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// Yeah, not too cute. The empty_arg_list class should really be public.
// https://svn.boost.org/trac/boost/ticket/7247
typedef boost::parameter::aux::empty_arg_list empty_arg_list;

#if !(defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_LOG_NO_CXX11_ARG_PACKS_TO_NON_VARIADIC_ARGS_EXPANSION))

//! The metafunction generates argument pack
template< typename ArgT0, typename... ArgsT >
struct make_arg_list
{
    typedef boost::parameter::aux::arg_list< ArgT0, typename make_arg_list< ArgsT... >::type > type;
};

template< typename ArgT0 >
struct make_arg_list< ArgT0 >
{
    typedef boost::parameter::aux::arg_list< ArgT0 > type;
};

#else

//! The metafunction generates argument pack
template< typename ArgT0, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_DEC(BOOST_LOG_MAX_PARAMETER_ARGS), typename T, = void BOOST_PP_INTERCEPT) >
struct make_arg_list
{
    typedef boost::parameter::aux::arg_list< ArgT0, typename make_arg_list< BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_LOG_MAX_PARAMETER_ARGS), T) >::type > type;
};

template< typename ArgT0 >
struct make_arg_list< ArgT0, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_LOG_MAX_PARAMETER_ARGS), void BOOST_PP_INTERCEPT) >
{
    typedef boost::parameter::aux::arg_list< ArgT0 > type;
};

#endif

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename R >
using enable_if_named_parameters = boost::enable_if_c< boost::mpl::or_< boost::is_base_of< boost::parameter::aux::tagged_argument_base, T >, boost::is_base_of< empty_arg_list, T > >::value, R >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename R >
struct enable_if_named_parameters :
    public boost::enable_if_c< boost::mpl::or_< boost::is_base_of< boost::parameter::aux::tagged_argument_base, T >, boost::is_base_of< empty_arg_list, T > >::value, R >
{
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_PARAMETER_TOOLS_HPP_INCLUDED_

/* parameter_tools.hpp
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
*/