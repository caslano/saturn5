/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/named_scope.hpp
 * \author Andrey Semashev
 * \date   11.11.2012
 *
 * The header contains a formatter function for named scope attribute values.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_NAMED_SCOPE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_NAMED_SCOPE_HPP_INCLUDED_

#include <string>
#include <iterator>
#include <utility>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/detail/deduce_char_type.hpp>
#include <boost/log/detail/attr_output_terminal.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/string_literal_fwd.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/keywords/delimiter.hpp>
#include <boost/log/keywords/depth.hpp>
#include <boost/log/keywords/iteration.hpp>
#include <boost/log/keywords/empty_marker.hpp>
#include <boost/log/keywords/incomplete_marker.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

//! Scope iteration directions
enum scope_iteration_direction
{
    forward,    //!< Iterate through scopes from outermost to innermost
    reverse     //!< Iterate through scopes from innermost to outermost
};

namespace aux {

#ifdef BOOST_LOG_USE_CHAR
//! Parses the named scope format string and constructs the formatter function
BOOST_LOG_API boost::log::aux::light_function< void (basic_formatting_ostream< char >&, attributes::named_scope::value_type::value_type const&) >
parse_named_scope_format(const char* begin, const char* end);
#endif

#ifdef BOOST_LOG_USE_WCHAR_T
//! Parses the named scope format string and constructs the formatter function
BOOST_LOG_API boost::log::aux::light_function< void (basic_formatting_ostream< wchar_t >&, attributes::named_scope::value_type::value_type const&) >
parse_named_scope_format(const wchar_t* begin, const wchar_t* end);
#endif

//! Parses the named scope format string and constructs the formatter function
template< typename CharT >
inline boost::log::aux::light_function< void (basic_formatting_ostream< CharT >&, attributes::named_scope::value_type::value_type const&) >
parse_named_scope_format(const CharT* format)
{
    return parse_named_scope_format(format, format + std::char_traits< CharT >::length(format));
}

//! Parses the named scope format string and constructs the formatter function
template< typename CharT, typename TraitsT, typename AllocatorT >
inline boost::log::aux::light_function< void (basic_formatting_ostream< CharT >&, attributes::named_scope::value_type::value_type const&) >
parse_named_scope_format(std::basic_string< CharT, TraitsT, AllocatorT > const& format)
{
    const CharT* p = format.c_str();
    return parse_named_scope_format(p, p + format.size());
}

//! Parses the named scope format string and constructs the formatter function
template< typename CharT, typename TraitsT >
inline boost::log::aux::light_function< void (basic_formatting_ostream< CharT >&, attributes::named_scope::value_type::value_type const&) >
parse_named_scope_format(basic_string_literal< CharT, TraitsT > const& format)
{
    const CharT* p = format.c_str();
    return parse_named_scope_format(p, p + format.size());
}

template< typename CharT >
class format_named_scope_impl
{
public:
    //! Function result type
    typedef void result_type;

    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Attribute value type
    typedef attributes::named_scope::value_type value_type;
    //! Named scope formatter
    typedef boost::log::aux::light_function< void (stream_type&, value_type::value_type const&) > element_formatter_type;

private:
    //! Element formatting function
    element_formatter_type m_element_formatter;
    //! Element delimiter
    string_type m_delimiter;
    //! Incomplete list marker
    string_type m_incomplete_marker;
    //! Empty list marker
    string_type m_empty_marker;
    //! Maximum number of elements to output
    value_type::size_type m_depth;
    //! Iteration direction
    scope_iteration_direction m_direction;

public:
    //! Initializing constructor
    format_named_scope_impl
    (
        element_formatter_type const& element_formatter,
        string_type const& delimiter,
        string_type const& incomplete_marker,
        string_type const& empty_marker,
        value_type::size_type depth,
        scope_iteration_direction direction
    ) :
        m_element_formatter(element_formatter),
        m_delimiter(delimiter),
        m_incomplete_marker(incomplete_marker),
        m_empty_marker(empty_marker),
        m_depth(depth),
        m_direction(direction)
    {
    }
    //! Copy constructor
    format_named_scope_impl(format_named_scope_impl const& that) :
        m_element_formatter(that.m_element_formatter),
        m_delimiter(that.m_delimiter),
        m_incomplete_marker(that.m_incomplete_marker),
        m_empty_marker(that.m_empty_marker),
        m_depth(that.m_depth),
        m_direction(that.m_direction)
    {
    }

    //! Formatting operator
    result_type operator() (stream_type& strm, value_type const& scopes) const
    {
        if (!scopes.empty())
        {
            if (m_direction == expressions::forward)
                format_forward(strm, scopes);
            else
                format_reverse(strm, scopes);
        }
        else
        {
            strm << m_empty_marker;
        }
    }

private:
    //! The function performs formatting of the extracted scope stack in forward direction
    void format_forward(stream_type& strm, value_type const& scopes) const
    {
        value_type::const_iterator it, end = scopes.end();
        if (m_depth > 0)
        {
            value_type::size_type const scopes_to_iterate = (std::min)(m_depth, scopes.size());
            it = scopes.end();
            std::advance(it, -static_cast< value_type::difference_type >(scopes_to_iterate));
        }
        else
        {
            it = scopes.begin();
        }

        if (it != end)
        {
            if (it != scopes.begin())
                strm << m_incomplete_marker;

            m_element_formatter(strm, *it);
            for (++it; it != end; ++it)
            {
                strm << m_delimiter;
                m_element_formatter(strm, *it);
            }
        }
    }
    //! The function performs formatting of the extracted scope stack in reverse direction
    void format_reverse(stream_type& strm, value_type const& scopes) const
    {
        value_type::const_reverse_iterator it = scopes.rbegin(), end;
        if (m_depth > 0)
        {
            value_type::size_type const scopes_to_iterate = (std::min)(m_depth, scopes.size());
            end = it;
            std::advance(end, static_cast< value_type::difference_type >(scopes_to_iterate));
        }
        else
        {
            end = scopes.rend();
        }

        if (it != end)
        {
            m_element_formatter(strm, *it);
            for (++it; it != end; ++it)
            {
                strm << m_delimiter;
                m_element_formatter(strm, *it);
            }

            if (it != scopes.rend())
                strm << m_incomplete_marker;
        }
    }
};

} // namespace aux

/*!
 * Named scope formatter terminal.
 */
template< typename FallbackPolicyT, typename CharT >
class format_named_scope_terminal
{
public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Attribute value type
    typedef attributes::named_scope::value_type value_type;
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Formatter function
    typedef aux::format_named_scope_impl< char_type > formatter_function_type;

    //! Function result type
    typedef string_type result_type;

private:
    //! Attribute value visitor invoker
    typedef value_visitor_invoker< value_type, fallback_policy > visitor_invoker_type;

private:
    //! Attribute name
    attribute_name m_name;
    //! Formatter function
    formatter_function_type m_formatter;
    //! Attribute value visitor invoker
    visitor_invoker_type m_visitor_invoker;

public:
    //! Initializing constructor
    template< typename FormatT >
    format_named_scope_terminal
    (
        attribute_name const& name,
        fallback_policy const& fallback,
        FormatT const& element_format,
        string_type const& delimiter,
        string_type const& incomplete_marker,
        string_type const& empty_marker,
        value_type::size_type depth,
        scope_iteration_direction direction
    ) :
        m_name(name), m_formatter(aux::parse_named_scope_format(element_format), delimiter, incomplete_marker, empty_marker, depth, direction), m_visitor_invoker(fallback)
    {
    }
    //! Copy constructor
    format_named_scope_terminal(format_named_scope_terminal const& that) :
        m_name(that.m_name), m_formatter(that.m_formatter), m_visitor_invoker(that.m_visitor_invoker)
    {
    }

    //! Returns attribute name
    attribute_name get_name() const
    {
        return m_name;
    }

    //! Returns fallback policy
    fallback_policy const& get_fallback_policy() const
    {
        return m_visitor_invoker.get_fallback_policy();
    }

    //! Retruns formatter function
    formatter_function_type const& get_formatter_function() const
    {
        return m_formatter;
    }

    //! Invokation operator
    template< typename ContextT >
    result_type operator() (ContextT const& ctx)
    {
        string_type str;
        stream_type strm(str);
        m_visitor_invoker(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()), binder1st< formatter_function_type&, stream_type& >(m_formatter, strm));
        strm.flush();
        return BOOST_LOG_NRVO_RESULT(str);
    }

    //! Invokation operator
    template< typename ContextT >
    result_type operator() (ContextT const& ctx) const
    {
        string_type str;
        stream_type strm(str);
        m_visitor_invoker(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()), binder1st< formatter_function_type const&, stream_type& >(m_formatter, strm));
        strm.flush();
        return BOOST_LOG_NRVO_RESULT(str);
    }

    BOOST_DELETED_FUNCTION(format_named_scope_terminal())
};

/*!
 * Named scope formatter actor.
 */
template< typename FallbackPolicyT, typename CharT, template< typename > class ActorT = phoenix::actor >
class format_named_scope_actor :
    public ActorT< format_named_scope_terminal< FallbackPolicyT, CharT > >
{
public:
    //! Character type
    typedef CharT char_type;
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;
    //! Base terminal type
    typedef format_named_scope_terminal< fallback_policy, char_type > terminal_type;
    //! Attribute value type
    typedef typename terminal_type::value_type value_type;
    //! Formatter function
    typedef typename terminal_type::formatter_function_type formatter_function_type;

    //! Base actor type
    typedef ActorT< terminal_type > base_type;

public:
    //! Initializing constructor
    explicit format_named_scope_actor(base_type const& act) : base_type(act)
    {
    }

    /*!
     * \returns The attribute name
     */
    attribute_name get_name() const
    {
        return this->proto_expr_.child0.get_name();
    }

    /*!
     * \returns Fallback policy
     */
    fallback_policy const& get_fallback_policy() const
    {
        return this->proto_expr_.child0.get_fallback_policy();
    }

    /*!
     * \returns Formatter function
     */
    formatter_function_type const& get_formatter_function() const
    {
        return this->proto_expr_.child0.get_formatter_function();
    }
};

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_AUX_OVERLOAD(left_ref, right_ref)\
    template< typename LeftExprT, typename FallbackPolicyT, typename CharT >\
    BOOST_FORCEINLINE phoenix::actor< aux::attribute_output_terminal< phoenix::actor< LeftExprT >, attributes::named_scope::value_type, FallbackPolicyT, typename format_named_scope_actor< FallbackPolicyT, CharT >::formatter_function_type > >\
    operator<< (phoenix::actor< LeftExprT > left_ref left, format_named_scope_actor< FallbackPolicyT, CharT > right_ref right)\
    {\
        typedef aux::attribute_output_terminal< phoenix::actor< LeftExprT >, attributes::named_scope::value_type, FallbackPolicyT, typename format_named_scope_actor< FallbackPolicyT, CharT >::formatter_function_type > terminal_type;\
        phoenix::actor< terminal_type > actor = {{ terminal_type(left, right.get_name(), right.get_formatter_function(), right.get_fallback_policy()) }};\
        return actor;\
    }

#include <boost/log/detail/generate_overloads.hpp>

#undef BOOST_LOG_AUX_OVERLOAD

#endif // BOOST_LOG_DOXYGEN_PASS

namespace aux {

//! Auxiliary traits to acquire default formatter parameters depending on the character type
template< typename CharT >
struct default_named_scope_params;

#ifdef BOOST_LOG_USE_CHAR
template< >
struct default_named_scope_params< char >
{
    static const char* forward_delimiter() { return "->"; }
    static const char* reverse_delimiter() { return "<-"; }
    static const char* incomplete_marker() { return "..."; }
    static const char* empty_marker() { return ""; }
};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
template< >
struct default_named_scope_params< wchar_t >
{
    static const wchar_t* forward_delimiter() { return L"->"; }
    static const wchar_t* reverse_delimiter() { return L"<-"; }
    static const wchar_t* incomplete_marker() { return L"..."; }
    static const wchar_t* empty_marker() { return L""; }
};
#endif

template< typename CharT, template< typename > class ActorT, typename FallbackPolicyT, typename ArgsT >
BOOST_FORCEINLINE format_named_scope_actor< FallbackPolicyT, CharT, ActorT > format_named_scope(attribute_name const& name, FallbackPolicyT const& fallback, ArgsT const& args)
{
    typedef format_named_scope_actor< FallbackPolicyT, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typedef default_named_scope_params< CharT > default_params;
    scope_iteration_direction dir = args[keywords::iteration | expressions::forward];
    const CharT* default_delimiter = (dir == expressions::forward ? default_params::forward_delimiter() : default_params::reverse_delimiter());
    typename actor_type::base_type act =
    {{
         terminal_type
         (
             name,
             fallback,
             args[keywords::format],
             args[keywords::delimiter | default_delimiter],
             args[keywords::incomplete_marker | default_params::incomplete_marker()],
             args[keywords::empty_marker | default_params::empty_marker()],
             args[keywords::depth | static_cast< attributes::named_scope::value_type::size_type >(0)],
             dir
         )
    }};
    return actor_type(act);
}

} // namespace aux

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param name Attribute name
 * \param element_format Format string for a single named scope
 */
template< typename CharT >
BOOST_FORCEINLINE format_named_scope_actor< fallback_to_none, CharT > format_named_scope(attribute_name const& name, const CharT* element_format)
{
    typedef format_named_scope_actor< fallback_to_none, CharT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(name, fallback_to_none(), element_format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param name Attribute name
 * \param element_format Format string for a single named scope
 */
template< typename CharT >
BOOST_FORCEINLINE format_named_scope_actor< fallback_to_none, CharT > format_named_scope(attribute_name const& name, std::basic_string< CharT > const& element_format)
{
    typedef format_named_scope_actor< fallback_to_none, CharT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(name, fallback_to_none(), element_format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param keyword Attribute keyword
 * \param element_format Format string for a single named scope
 */
template< typename DescriptorT, template< typename > class ActorT, typename CharT >
BOOST_FORCEINLINE format_named_scope_actor< fallback_to_none, CharT, ActorT >
format_named_scope(attribute_keyword< DescriptorT, ActorT > const& keyword, const CharT* element_format)
{
    BOOST_STATIC_ASSERT_MSG((is_same< typename DescriptorT::value_type, attributes::named_scope::value_type >::value),\
        "Boost.Log: Named scope formatter only accepts attribute values of type attributes::named_scope::value_type.");

    typedef format_named_scope_actor< fallback_to_none, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(keyword.get_name(), fallback_to_none(), element_format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param keyword Attribute keyword
 * \param element_format Format string for a single named scope
 */
template< typename DescriptorT, template< typename > class ActorT, typename CharT >
BOOST_FORCEINLINE format_named_scope_actor< fallback_to_none, CharT, ActorT >
format_named_scope(attribute_keyword< DescriptorT, ActorT > const& keyword, std::basic_string< CharT > const& element_format)
{
    BOOST_STATIC_ASSERT_MSG((is_same< typename DescriptorT::value_type, attributes::named_scope::value_type >::value),\
        "Boost.Log: Named scope formatter only accepts attribute values of type attributes::named_scope::value_type.");

    typedef format_named_scope_actor< fallback_to_none, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(keyword.get_name(), fallback_to_none(), element_format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param placeholder Attribute placeholder
 * \param element_format Format string for a single named scope
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename CharT >
BOOST_FORCEINLINE format_named_scope_actor< FallbackPolicyT, CharT, ActorT >
format_named_scope(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& placeholder, const CharT* element_format)
{
    BOOST_STATIC_ASSERT_MSG((is_same< T, attributes::named_scope::value_type >::value),\
        "Boost.Log: Named scope formatter only accepts attribute values of type attributes::named_scope::value_type.");

    typedef format_named_scope_actor< FallbackPolicyT, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(placeholder.get_name(), placeholder.get_fallback_policy(), element_format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param placeholder Attribute placeholder
 * \param element_format Format string for a single named scope
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename CharT >
BOOST_FORCEINLINE format_named_scope_actor< FallbackPolicyT, CharT, ActorT >
format_named_scope(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& placeholder, std::basic_string< CharT > const& element_format)
{
    BOOST_STATIC_ASSERT_MSG((is_same< T, attributes::named_scope::value_type >::value),\
        "Boost.Log: Named scope formatter only accepts attribute values of type attributes::named_scope::value_type.");

    typedef format_named_scope_actor< FallbackPolicyT, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(placeholder.get_name(), placeholder.get_fallback_policy(), element_format) }};
    return actor_type(act);
}

#if !defined(BOOST_LOG_DOXYGEN_PASS)

#   define BOOST_PP_FILENAME_1 <boost/log/detail/named_scope_fmt_pp.hpp>
#   define BOOST_PP_ITERATION_LIMITS (1, 6)
#   include BOOST_PP_ITERATE()

#else // BOOST_LOG_DOXYGEN_PASS

/*!
 * Formatter generator. Construct the named scope formatter with the specified formatting parameters.
 *
 * \param name Attribute name
 * \param args An set of named parameters. Supported parameters:
 *             \li \c format - A format string for named scopes. The string can contain "%n", "%f" and "%l" placeholders for the scope name, file and line number, respectively. This parameter is mandatory.
 *             \li \c delimiter - A string that is used to delimit the formatted scope names. Default: "->" or "<-", depending on the iteration direction.
 *             \li \c incomplete_marker - A string that is used to indicate that the list was printed incomplete because of depth limitation. Default: "...".
 *             \li \c empty_marker - A string that is output in case if the scope list is empty. Default: "", i.e. nothing is output.
 *             \li \c iteration - Iteration direction, see \c scope_iteration_direction enumeration. Default: forward.
 *             \li \c depth - Iteration depth. Default: unlimited.
 */
template< typename... ArgsT >
unspecified format_named_scope(attribute_name const& name, ArgsT... const& args);

/*! \overload */
template< typename DescriptorT, template< typename > class ActorT, typename... ArgsT >
unspecified format_named_scope(attribute_keyword< DescriptorT, ActorT > const& keyword, ArgsT... const& args);

/*! \overload */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename... ArgsT >
unspecified format_named_scope(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& placeholder, ArgsT... const& args);

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename FallbackPolicyT, typename CharT >
struct is_nullary< custom_terminal< boost::log::expressions::format_named_scope_terminal< FallbackPolicyT, CharT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_NAMED_SCOPE_HPP_INCLUDED_

/* named_scope.hpp
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
*/