/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unary_function_terminal.hpp
 * \author Andrey Semashev
 * \date   21.07.2012
 *
 * The header contains attribute value extractor adapter for constructing expression template terminals.
 */

#ifndef BOOST_LOG_DETAIL_UNARY_FUNCTION_TERMINAL_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_UNARY_FUNCTION_TERMINAL_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/copy_cv.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

/*!
 * \brief An adapter for a unary function to be used as a terminal in a Boost.Phoenix expression
 *
 * This class is an adapter between Boost.Phoenix expression invocation protocol and
 * a unary function. It forwards the call to the base function, passing only the first argument
 * from the original call. This allows to embed value extractors in template expressions.
 */
template< typename FunT >
class unary_function_terminal
{
private:
    //! Adopted function type
    typedef FunT function_type;
    //! Self type
    typedef unary_function_terminal< function_type > this_type;

public:
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;

    //! Function result type
    template< typename >
    struct result;

    template< typename ThisT, typename ContextT >
    struct result< ThisT(ContextT) >
    {
        typedef typename remove_cv<
            typename remove_reference< typename phoenix::result_of::env< ContextT >::type >::type
        >::type env_type;
        typedef typename env_type::args_type args_type;
        typedef typename boost::log::aux::copy_cv< ThisT, function_type >::type cv_function_type;

        typedef typename boost::result_of< cv_function_type(typename fusion::result_of::at_c< args_type, 0 >::type) >::type type;
    };

private:
    //! Adopted function
    function_type m_fun;

public:
    //! Default constructor
    BOOST_DEFAULTED_FUNCTION(unary_function_terminal(), {})
    //! Copy constructor
    unary_function_terminal(unary_function_terminal const& that) : m_fun(that.m_fun) {}
    //! Initializing constructor
    template< typename ArgT1 >
    explicit unary_function_terminal(ArgT1 const& arg1) : m_fun(arg1) {}
    //! Initializing constructor
    template< typename ArgT1, typename ArgT2 >
    unary_function_terminal(ArgT1 const& arg1, ArgT2 const& arg2) : m_fun(arg1, arg2) {}
    //! Initializing constructor
    template< typename ArgT1, typename ArgT2, typename ArgT3 >
    unary_function_terminal(ArgT1 const& arg1, ArgT2 const& arg2, ArgT3 const& arg3) : m_fun(arg1, arg2, arg3) {}

    //! The operator forwards the call to the base function
    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type
    operator() (ContextT const& ctx)
    {
        return m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()));
    }

    //! The operator forwards the call to the base function
    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type
    operator() (ContextT const& ctx) const
    {
        return m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()));
    }
};

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename FunT >
struct is_nullary< custom_terminal< boost::log::expressions::aux::unary_function_terminal< FunT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_UNARY_FUNCTION_TERMINAL_HPP_INCLUDED_

/* unary_function_terminal.hpp
fM1K/N8RfuXz1O+hSun/Mm6Tgsf7ZVx+wbcIvlHw7YLvnKfSxTtTLIfqZPxLeEHC8c4Qxs2Q/B6X36fnqb+zUt6kxL8gdHgXgcd7Utpf8PB7j3hXOf68tnnePJaX8OsO/E3JL/xkc/klPx7LidVtq73VXM/wUc3ln6/o8XY1yzORJ02Cx9vDayx51S54+Hvm9hd8VvDXBF8Q/OB8lW/4KEb+RoTuj3X7y++/ELkDv674PU/k0aX5Kt640FUL/qrgV8p89KDgbwrdY/J7Vn4/o+WfyNOvSr3/o+QjKfjex6T8ImdbBL9R5MpW+fuayEX42YR8Wud9/RvA7xf8mQ+r/A1KfPi85P4vvy9XSPnl9zuSvwsi92cl/iX5Db+E+D0lvyfl9zWJjzciufzy+9OSD/jHwm/4R+LyyzwCv0zc/vI7Jb8b5PeMxPuXUl74R8Jf+EPi/i/zSrfQwx8S93/GL2xb6C3kdpnaoPBDQgc/ODz/CF7Pd/Ang7+n5e+dp2V+bla/4ceC+6Okf1XSvybx4WOI+7+kc+4paX89/8l8CL8XLP+k/msFPy35bxB8k+B/TNqlrULx94T//6LnS6H7otQ37pPjN+6Kc/8XfkNCNyz407r95W9S+ukvC99xocf9Sx7/QjdVovIxKeMFd3t43nlR2l/obkv8dsF7Ml+XLxT58L1Sfvn9m5Jug/z+srT7V+Tv38jff9D6j9CV
*/