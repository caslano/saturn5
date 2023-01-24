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
mMkVTM6US65psPjrKkD3WIopzJ3I4oUY54+v8a0JvZUC3GEmt/75T4/Epg75ZTA+vPAYzS/E3QDSyNi8d1G2p4sjAqQ7wfav/95J58QGJ/ckwODJJsDHbJDeHAP8SAV4evNzXe+MAdcyC2N8xESpjXQTa8NfOj2SAuObHKcX4hyxGPtzajpcqAps9dCeZIob8M5ZkNvXZFP8Mr9wdx7w5GLoPh+eZHA+9Bk8aQ7mzdde4nD7MpRnaTnuOKWNDhx/gJJPoAQbYLp+87P1UW0x1s7e5ewi0DIUArg4C+a1i6Iprtq/0OV01DuYvgRcAmyb5ZdXMBx3jMnaoNAC3rj9OSEbBjOWMd3pTu6nK7jPD1zlIuyPvDUY/sBwKx8n5WyNQMWOwNacv8yQSR9MhZh0CXIE3ypxLsLewJy+gfKzCFz/BT69CONrywsU76Tl9MJoDzvxwNUtwNw8/16GM9c5fEAI9LRK0Jv+/7X3PvBVH9ed6E/SBSQQIIEAgWW42HIsx7IjY9mWU7kW5uIIW4CCLlzZkc0FLiDZF3QNAouE1MpWTbUbtqVdmtIt2+ptSUv3o+zTvtJX+qq+Ki1t1ZZ2Sat26eeRVn2lW/qWfEr7obvqliTvfM+c+c3M789FJE7S9z6+fA6698yZM//PnJk5c+Y5ix3jz7wIGZjeIEcPjGtmO5jfrOjcc/Soff6AsNxO9KOj7wj9013H9zH+
*/