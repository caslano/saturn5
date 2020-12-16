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
TfXoAPu7kE1hEmwG9b6674by73HfWXrf2TAWztH7Tkb2qLv56i4CGa3uFmi65MK+MA8OgflwOiyEs2ERzIKL4Dw9PwnvQPI1Xr9R/2OQder/732BdN4HG8NnYXO4H3aCL8Dh8CU4ER6E2fAVeCV8FV4D34TXwdfgrfB1+FN4GP5cr++Eb8DH5Fz1QZm690L3eByC/RB0u8vxF+xFwZOwA/wUdoNZYQE9+6c57w8/hxnwS3g5/ErD8zW8Hf4d3gt9uHsQhsGdMBzuhTXhi7AWPAwj4FEYBWv66wFsBevDTrABHAcT4GSYCFfAJLgaNoU3w+bwNpgMH4ct4AuwDXwfdoAnYUdo+ChvsD3sAnvCVDgAdofDYBpMhz3hZNgLZsI+sAD2g9fA/nAdHABvhYPho3AI/C0cCp+Hw+BHcDj8El4IG5MP42B3OB4OhBPhMDgJjoJT4CQ4FWbAaXAFnAlXwVnwdjgb3gPnwG2QfJN8P2qt59b16IdgI+SglktUBUk9uwh2haO1HF4Mp8BL4Tw4Di6AE2ARnAxXwKnwBjgN3g2nwwdgBnwCZsLXYAE8Cgvhu7AInoCL4Wm4BH4Js2EM4ZwL28F5sAO8DHaDC2AaXAjPh3lavnGja2olDBLP5ki4lu9lWr6vg73gOjgarodz4R6YC3+r8XoKroZ74Y3wB1q/boMvw9vhm/Au+B68G34MN0B/Ob4H1oX3wkZwIzwPboL94GY4HW6FRfABuA4+CG+BP4UPwx3wKPwVPA53ws/gw7Ah8XwENoaPwaFwNxwOf6Ppkm6tmYR9tV2qhQzV/P+ZtnsPwSj4c9gA7oCJ8GHYCP4K9tHzk3CktY4RJqu/NZH+6u8ubYcfhQ3h4+rPbpgEH4PN5VzbZ2s9IJzh0T7/Tbcl/x12hN/AIRAHUl7D4QjogxNhGJyu5idhO2sNHGyh/uv3KeSopeGNcPZv2o8mefQzz6n9P2i89qu7Er+ou4vUnerVk+MddfcurAs/0XQ+CZvCM7AZfB+2hR/A7mreA56AveGHcKiaD4MfwQvlXOu9tbYH9vCo97TV0h9tgqlwH+wFt8KL4QNwKvwJXAp/BpfDn8Or9Xylnq/V8/XwIXizmj8Ed8J98FH4CtwN34K/ge/DPfCk3v80fBiGm9Q72AT+DraAv4cd4TMwBe5Td4fs9RnET+Mpc7CI5I+OI56H8fBF2AS+DJPhQdgbvgIHwENwDvwznAdfg7nwdbgIHoGL4VG4Gv4F3gjfhvfDv8JfwPfgo/AEfAd+Cs/AU/Dv8DNIWWOMR/jg57A+LIMN9dwqh5lnKYevann6k5bDQ5r/g63337CXutP5KDme1Hq/R+vj72Fj+BTsqecnoXhQVlPQQdO3qcQjcHTRctRHy1GGlqN+Wo4GwIlwIMyAg2AWHALnw+EwV8/z9HyJnl8Bh8IVan43HAG3wJGa3hfBJ+FoLWdj4HPwEngYXgo/gdPg53A69EdmBqwBM2AknAjrwUmwGZwM28AMzYcDiLxH1LgfQhoiT2s6zNbvxVwGm8Jc2AouhO3gIi1fN8B0eCOcAtdrutwEZ8HLYQksgKtgIbweFsE1sBjeDpdpeqzQdLhKy10J/x+G18DH4EpNn+vge3C1xucmR/kafJbydUDL14tavl6Cljt5dwNjPNzNVXfzYD04X91lmtZ7BXk/I+7aI+NNfReu7upDmSOAcbChto9xsCVMgG3VvBNsBLvAJvB82BRepOfj4HlwMmwBM2BLmAfbwWthe7gZdoT3w85wL+wKj8JU+BXsARMJa0/YB/aGU2FfmAX7w3w4AC6HA2EpHAR3wPPhUTgMxvoC15vDkbA7vAimwzFwIhwLZ8N0eAU=
*/