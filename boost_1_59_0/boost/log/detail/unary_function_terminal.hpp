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
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
*/