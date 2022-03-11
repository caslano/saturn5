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