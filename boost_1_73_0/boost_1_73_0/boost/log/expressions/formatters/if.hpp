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
fgCR+ZBLf+ZY5YGkEXbFmdHq6UwPMjyRVGKNqJ/2c5Aa1VieGFWhOm0vi/Wja8yUeYbFC0qa0zYBie9HAQ/n2QJzWcAZzWqiuS5gDNyYFiMHeUGqtr/fZOZ/T8XYpgAc9CfOqNc5Hw4u32mb+pL3DYbd3mhy/nOx9Wp4To0F8IvhqNvDxLgc12g4nOBXs3V4Pelf9f/ZG193uj2zAxU06l0OO+c0zwfUD+gJpog9Thckn3FR41Bz1RpuS3WQISIbcnGCfmeuH2DdoHHMWqRzgCOEAtXPfO7TMq+zJ2doPOPVdMrTVGlNgAJgEt0rsmRn1yNnMnrTkzqpoifnQbYJMyG7M6FTQQ2h1x2JtvIZrUXLzAteIsI1bXmCQDmBouEDG4QDGbFGAA4Y1N5Tkyb5CDdAJInGUwHVJPw57EYBPWxJVWLtP6Rg7OWt17Uz7FPSUh7yi1lK/C9PUxxLxlJgw7gmVWR6Wif405lKLqWCXQhqyudShrI1FdlJ5Di+Ip4Xs5CNQv9GacifFvtumcgj5U4ZyONSjV2Fj/W3HbKMzTr4dmnGt9DDrpnGI5VBGUZpKmEXwi12rAKjwFpZMd6WytkiEyKWzD16FApajNEJne6j0w6RJaATprLzK55hfZoyC3TBhy+pXt1kr6+p
*/