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