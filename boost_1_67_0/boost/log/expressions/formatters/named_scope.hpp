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