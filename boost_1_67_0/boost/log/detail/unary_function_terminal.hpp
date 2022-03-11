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