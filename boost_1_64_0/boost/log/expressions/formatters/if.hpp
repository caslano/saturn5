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
PLE7VVW9uMauT2/cmvHd4hqvvcEb5X6d041YaDw5qgPp1/r9R3GT77j9yIwsSZCzIDj+yzwtc1rmeLfEc7JSUmLWxVh2r/4gYec4MkZsT74iC2WuMDMrJ0v7Fb13CAkbI2b5ZZDo9l+xx4n4O8xx4vcLj3ycaGzqGR1qmMw1LTP5bbNQHZPzt/R8d0R/tVNfmlN17DgJudyd7xWF17mE5ntFkfO9eZSatd7hNv56p24Trg8N4i9T7P48Qz3blROsD32YF7rTR60Tej83NzR+pU6kS9/THqfOEc4hi1odx8Y5h5T8tJV97HllUXh9qNPz3RF90MR8R46btQ+6AbnCtdMQUR/inVfiL2JeicdY+moJ1AV1G3OOuaWo9T6oqGOoD9pFGGvygn3QyCPugwo6hvqgnVyYmBesc+eH+iC915infdDIxPqgw52rNhcdeR8kc1Upy9h90F8i6lxeR1Pnwmzg7dc6R7M0tvCudHWLO5o6J8apNVUmQeS9m2bcuFes9Y8wErM57YZXqOF5+8mBBOgeA9RTf+SvuG2MiGNNIJvUbmv0PPAr4j7bFlcNy+dpV4sq6hfZ24q69dSPxOrAteI/PW5bWK9G1wGtFxJHKd8NHe1j4hFqb3CQBtwb2YubrYG8OydyUVHtv3jHxDIP3ea6x3cnwrbkH+HFv86obqPtTcbRL+9peW1P8mKf5sUfI/Jih1sJdF7gQ65ErhrGP8WReUHbaiEvThT3w3in5dvygvDiX8/DbUw7X8VwmtzvR7+bG9nfGvuK2eJmGXUQW+mI27eNotxndgysz6VmZiUPzkzxzBBzvXkvfZvuMfP2a0jrv+tiyiWONbXFxTHWU4vD98blI8nue0/LxSyimbYdXSabxK2brhRbmRBWYn2Rp81J3L9bbG9fEzvZ4741Mu5iMz92/Le1Ev+trcd/Qkvxf87EP9zG/LjOAc/rtE3chtzXk7LT+Ecsss2psrULrYcZnVw/lbSLJFsaCDP+eXNzcfzz5qDbPDN2MetExu78W+LmFrGTW47YbEB5n6nz5oY6T1vsLOk7l/j5vesrzH/jt7e85zDmsmovV9/xmjZtU8OIk9i40Pf8hIjz+eY8vNyru5i5hxxnICkltJNOWu6RC2LR5W7s428SPxPk3TDK/n4g3JbXxfLgU+Kmp4RjqxMmDB2Dkfe6vnV47w/7ulPEO0N/iGUpIvmGDCefcks0n8IXlSLzyJYX+I2/HeSWxN8O1K133cesOZbKvdG8G1LN2s8V6l77fl03UjtkR/hObq1Oe/v/4m7RY5R3CXOjyWOz+BK7/y9pcXxCWPGvx2wsSWAuVJLQWCb8HXOY6wvPyDPZix3xLqrsHp2Pb+KmWfMxfEEhdl7ubjkvCS/+NYbmBPKyObG8bHWM3Mp8XfIyq7N9bWZUD7OWrHqsiGtjrHNkXjJWbCEvp4v7k2ONFQkv/jl6987x5yVuWxxXNsj9gbgtiDmuHCRu6sPGlYuoYw/RTyy0jSvzjv648tXDnP9+vrN9jWWo2uQ7EZFz5DXc7PCWKya7uBw5xzXztxfEbXtbeRKO97dDotcm3uwcvv6e3EXd63iiorTVeh9jzqw2ZDXdv4t432epkQguy/1iZI1bn8P1T84656xp5nt1HmlYLbaqmF038HarD9nD7C3+YtTpQJpatcFepGngGaTBPEPS0Vf3++fkBs4HmfPwdnq/pqtIAy5EriW88uh0SbFmS5qiy2W8uM9uNd/duIzVuMwY6J7P1vNURoUSN/N7nd3VTtxw1b8chnyOf+Za4kbqgz/XqT/MEjv/O7p5Fjv/Cb/133Cq1PRa+hnjv8iMI8g5E0SoD1ko7o4nz32ttmc=
*/