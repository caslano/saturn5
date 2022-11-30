/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/wrap_formatter.hpp
 * \author Andrey Semashev
 * \date   24.11.2012
 *
 * The header contains a formatter function wrapper that enables third-party functions to participate in formatting expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_WRAP_FORMATTER_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_WRAP_FORMATTER_HPP_INCLUDED_

#include <string>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/detail/function_traits.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

//! Wrapped formatter stream output terminal
template< typename LeftT, typename FunT >
class wrapped_formatter_output_terminal
{
private:
    //! Self type
    typedef wrapped_formatter_output_terminal< LeftT, FunT > this_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Wrapped function type
    typedef FunT function_type;

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
    //! Wrapped function
    function_type m_fun;

public:
    //! Initializing constructor
    wrapped_formatter_output_terminal(LeftT const& left, function_type const& fun) : m_left(left), m_fun(fun)
    {
    }
    //! Copy constructor
    wrapped_formatter_output_terminal(wrapped_formatter_output_terminal const& that) : m_left(that.m_left), m_fun(that.m_fun)
    {
    }

    //! Invokation operator
    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()), strm);
        return strm;
    }

    //! Invokation operator
    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()), strm);
        return strm;
    }

    BOOST_DELETED_FUNCTION(wrapped_formatter_output_terminal())
};

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_char_type, char_type, false)

template<
    typename FunT,
    bool HasCharTypeV = has_char_type< FunT >::value,
    bool HasSecondArgumentV = boost::log::aux::has_second_argument_type< FunT >::value,
    bool HasArg2V = boost::log::aux::has_arg2_type< FunT >::value
>
struct default_char_type
{
    // Use this char type if all detection fails
    typedef char type;
};

template< typename FunT, bool HasSecondArgumentV, bool HasArg2V >
struct default_char_type< FunT, true, HasSecondArgumentV, HasArg2V >
{
    typedef typename FunT::char_type type;
};

template< typename FunT, bool HasArg2V >
struct default_char_type< FunT, false, true, HasArg2V >
{
    typedef typename remove_cv< typename remove_reference< typename FunT::second_argument_type >::type >::type argument_type;
    typedef typename argument_type::char_type type;
};

template< typename FunT >
struct default_char_type< FunT, false, false, true >
{
    typedef typename remove_cv< typename remove_reference< typename FunT::arg2_type >::type >::type argument_type;
    typedef typename argument_type::char_type type;
};

} // namespace aux

/*!
 * Formatter function wrapper terminal.
 */
template< typename FunT, typename CharT >
class wrapped_formatter_terminal
{
public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Wrapped function type
    typedef FunT function_type;

    //! Formatter result type
    typedef string_type result_type;

private:
    //! Wrapped function
    function_type m_fun;

public:
    //! Initializing construction
    explicit wrapped_formatter_terminal(function_type const& fun) : m_fun(fun)
    {
    }
    //! Copy constructor
    wrapped_formatter_terminal(wrapped_formatter_terminal const& that) : m_fun(that.m_fun)
    {
    }

    //! Returns the wrapped function
    function_type const& get_function() const
    {
        return m_fun;
    }

    //! Invokation operator
    template< typename ContextT >
    result_type operator() (ContextT const& ctx)
    {
        string_type str;
        stream_type strm(str);
        m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()), strm);
        strm.flush();
        return BOOST_LOG_NRVO_RESULT(str);
    }

    //! Invokation operator
    template< typename ContextT >
    result_type operator() (ContextT const& ctx) const
    {
        string_type str;
        stream_type strm(str);
        m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()), strm);
        strm.flush();
        return BOOST_LOG_NRVO_RESULT(str);
    }
};

/*!
 * Wrapped formatter function actor.
 */
template< typename FunT, typename CharT, template< typename > class ActorT = phoenix::actor >
class wrapped_formatter_actor :
    public ActorT< wrapped_formatter_terminal< FunT, CharT > >
{
public:
    //! Character type
    typedef CharT char_type;
    //! Wrapped function type
    typedef FunT function_type;
    //! Base terminal type
    typedef wrapped_formatter_terminal< function_type, char_type > terminal_type;

    //! Base actor type
    typedef ActorT< terminal_type > base_type;

public:
    //! Initializing constructor
    explicit wrapped_formatter_actor(base_type const& act) : base_type(act)
    {
    }

    /*!
     * \returns The wrapped function
     */
    function_type const& get_function() const
    {
        return this->proto_expr_.child0.get_function();
    }
};

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_AUX_OVERLOAD(left_ref, right_ref)\
    template< typename LeftExprT, typename FunT, typename CharT >\
    BOOST_FORCEINLINE phoenix::actor< aux::wrapped_formatter_output_terminal< phoenix::actor< LeftExprT >, FunT > >\
    operator<< (phoenix::actor< LeftExprT > left_ref left, wrapped_formatter_actor< FunT, CharT > right_ref right)\
    {\
        typedef aux::wrapped_formatter_output_terminal< phoenix::actor< LeftExprT >, FunT > terminal_type;\
        phoenix::actor< terminal_type > actor = {{ terminal_type(left, right.get_function()) }};\
        return actor;\
    }

#include <boost/log/detail/generate_overloads.hpp>

#undef BOOST_LOG_AUX_OVERLOAD

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * The function wraps a function object in order it to be able to participate in formatting expressions. The wrapped
 * function object must be compatible with the following signature:
 *
 * <pre>
 * void (record_view const&, basic_formatting_ostream< CharT >&)
 * </pre>
 *
 * where \c CharT is the character type of the formatting expression.
 */
template< typename FunT >
BOOST_FORCEINLINE wrapped_formatter_actor< FunT, typename aux::default_char_type< FunT >::type > wrap_formatter(FunT const& fun)
{
    typedef wrapped_formatter_actor< FunT, typename aux::default_char_type< FunT >::type > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(fun) }};
    return actor_type(act);
}

/*!
 * The function wraps a function object in order it to be able to participate in formatting expressions. The wrapped
 * function object must be compatible with the following signature:
 *
 * <pre>
 * void (record_view const&, basic_formatting_ostream< CharT >&)
 * </pre>
 *
 * where \c CharT is the character type of the formatting expression.
 */
template< typename CharT, typename FunT >
BOOST_FORCEINLINE wrapped_formatter_actor< FunT, CharT > wrap_formatter(FunT const& fun)
{
    typedef wrapped_formatter_actor< FunT, CharT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(fun) }};
    return actor_type(act);
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename LeftT, typename FunT >
struct is_nullary< custom_terminal< boost::log::expressions::aux::wrapped_formatter_output_terminal< LeftT, FunT > > > :
    public mpl::false_
{
};

template< typename FunT, typename CharT >
struct is_nullary< custom_terminal< boost::log::expressions::wrapped_formatter_terminal< FunT, CharT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_WRAP_FORMATTER_HPP_INCLUDED_

/* wrap_formatter.hpp
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
*/