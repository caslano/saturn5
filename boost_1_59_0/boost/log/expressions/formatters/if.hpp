/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/if.hpp
 * \author Andrey Semashev
 * \date   17.11.2012
 *
 * The header contains implementation of a conditional formatter.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_IF_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_IF_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

template< typename LeftT, typename CondT, typename ThenT >
class if_output_terminal
{
private:
    //! Self type
    typedef if_output_terminal this_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Result type definition
    template< typename >
    struct result;

    template< typename ThisT, typename ContextT >
    struct result< ThisT(ContextT) >
    {
        typedef typename remove_cv< typename remove_reference< ContextT >::type >::type context_type;
        typedef typename phoenix::evaluator::impl<
            typename LeftT::proto_base_expr&,
            context_type,
            phoenix::unused
        >::result_type type;
    };

private:
    //! Left argument actor
    LeftT m_left;
    //! Condition expression
    CondT m_cond;
    //! Positive branch
    ThenT m_then;

public:
    //! Initializing constructor
    if_output_terminal(LeftT const& left, CondT const& cond, ThenT const& then_) : m_left(left), m_cond(cond), m_then(then_)
    {
    }

    //! Invokation operator
    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        if (phoenix::eval(m_cond, ctx))
            phoenix::eval(m_then, ctx);
        return strm;
    }

    //! Invokation operator
    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        if (phoenix::eval(m_cond, ctx))
            phoenix::eval(m_then, ctx);
        return strm;
    }

    BOOST_DELETED_FUNCTION(if_output_terminal())
};

template< typename LeftT, typename CondT, typename ThenT, typename ElseT >
class if_else_output_terminal
{
private:
    //! Self type
    typedef if_else_output_terminal this_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Result type definition
    template< typename >
    struct result;

    template< typename ThisT, typename ContextT >
    struct result< ThisT(ContextT) >
    {
        typedef typename remove_cv< typename remove_reference< ContextT >::type >::type context_type;
        typedef typename phoenix::evaluator::impl<
            typename LeftT::proto_base_expr&,
            context_type,
            phoenix::unused
        >::result_type type;
    };

private:
    //! Left argument actor
    LeftT m_left;
    //! Condition expression
    CondT m_cond;
    //! Positive branch
    ThenT m_then;
    //! Negative branch
    ElseT m_else;

public:
    //! Initializing constructor
    if_else_output_terminal(LeftT const& left, CondT const& cond, ThenT const& then_, ElseT const& else_) : m_left(left), m_cond(cond), m_then(then_), m_else(else_)
    {
    }

    //! Invokation operator
    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        if (phoenix::eval(m_cond, ctx))
            phoenix::eval(m_then, ctx);
        else
            phoenix::eval(m_else, ctx);
        return strm;
    }

    //! Invokation operator
    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        if (phoenix::eval(m_cond, ctx))
            phoenix::eval(m_then, ctx);
        else
            phoenix::eval(m_else, ctx);
        return strm;
    }

    BOOST_DELETED_FUNCTION(if_else_output_terminal())
};


template< typename CondT, typename ThenT, typename ElseT >
struct if_then_else_gen
{
    CondT m_cond;
    ThenT m_then;
    ElseT m_else;

    if_then_else_gen(CondT const& cond, ThenT const& then_, ElseT const& else_) : m_cond(cond), m_then(then_), m_else(else_)
    {
    }
};

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_AUX_OVERLOAD(left_ref, right_ref)\
    template< typename LeftExprT, typename CondT, typename ThenT, typename ElseT >\
    BOOST_FORCEINLINE phoenix::actor< if_else_output_terminal< phoenix::actor< LeftExprT >, CondT, ThenT, ElseT > >\
    operator<< (phoenix::actor< LeftExprT > left_ref left, if_then_else_gen< CondT, ThenT, ElseT > right_ref right)\
    {\
        typedef if_else_output_terminal< phoenix::actor< LeftExprT >, CondT, ThenT, ElseT > terminal_type;\
        phoenix::actor< terminal_type > actor = {{ terminal_type(left, right.m_cond, right.m_then, right.m_else) }};\
        return actor;\
    }

#include <boost/log/detail/generate_overloads.hpp>

#undef BOOST_LOG_AUX_OVERLOAD

#endif // BOOST_LOG_DOXYGEN_PASS

template< typename CondT, typename ThenT >
struct if_then_gen
{
    struct else_gen
    {
        CondT m_cond;
        ThenT m_then;

        else_gen(CondT const& cond, ThenT const& then_) : m_cond(cond), m_then(then_)
        {
        }

        template< typename ElseT >
        BOOST_FORCEINLINE if_then_else_gen< CondT, ThenT, ElseT > operator[] (ElseT const& el)
        {
            return if_then_else_gen< CondT, ThenT, ElseT >(m_cond, m_then, el);
        }
    }
    else_;

    if_then_gen(CondT const& cond, ThenT const& then_) : else_(cond, then_) {}
};

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_AUX_OVERLOAD(left_ref, right_ref)\
    template< typename LeftExprT, typename CondT, typename ThenT >\
    BOOST_FORCEINLINE phoenix::actor< if_output_terminal< phoenix::actor< LeftExprT >, CondT, ThenT > >\
    operator<< (phoenix::actor< LeftExprT > left_ref left, if_then_gen< CondT, ThenT > right_ref right)\
    {\
        typedef if_output_terminal< phoenix::actor< LeftExprT >, CondT, ThenT > terminal_type;\
        phoenix::actor< terminal_type > actor = {{ terminal_type(left, right.else_.m_cond, right.else_.m_then) }};\
        return actor;\
    }

#include <boost/log/detail/generate_overloads.hpp>

#undef BOOST_LOG_AUX_OVERLOAD

#endif // BOOST_LOG_DOXYGEN_PASS

template< typename CondT >
class if_gen
{
private:
    CondT const& m_cond;

public:
    explicit if_gen(CondT const& cond) : m_cond(cond)
    {
    }

    template< typename ThenT >
    BOOST_FORCEINLINE if_then_gen< CondT, ThenT > operator[] (ThenT const& then_) const
    {
        return if_then_gen< CondT, ThenT >(m_cond, then_);
    }
};

} // namespace aux

/*!
 * The function returns a conditional formatter generator object. The generator provides <tt>operator[]</tt> that can be used
 * to construct the actual formatter. The formatter must participate in a streaming expression.
 *
 * \param cond A filter expression that will be used as the condition
 */
template< typename CondT >
BOOST_FORCEINLINE aux::if_gen< CondT > if_(CondT const& cond)
{
    return aux::if_gen< CondT >(cond);
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename LeftT, typename CondT, typename ThenT >
struct is_nullary< custom_terminal< boost::log::expressions::aux::if_output_terminal< LeftT, CondT, ThenT > > > :
    public mpl::false_
{
};

template< typename LeftT, typename CondT, typename ThenT, typename ElseT >
struct is_nullary< custom_terminal< boost::log::expressions::aux::if_else_output_terminal< LeftT, CondT, ThenT, ElseT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_IF_HPP_INCLUDED_

/* if.hpp
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
*/