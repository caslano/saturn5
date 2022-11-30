/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/date_time.hpp
 * \author Andrey Semashev
 * \date   16.09.2012
 *
 * The header contains a formatter function for date and time attribute values.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_DATE_TIME_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_DATE_TIME_HPP_INCLUDED_

#include <string>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/date_time_fmt_gen_traits_fwd.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/detail/attr_output_terminal.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Date and time formatter terminal.
 */
template< typename T, typename FallbackPolicyT, typename CharT >
class format_date_time_terminal
{
public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Attribute value type
    typedef T value_type;
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;

    //! Formatter function
    typedef boost::log::aux::light_function< void (stream_type&, value_type const&) > formatter_function_type;

    //! Function result type
    typedef string_type result_type;

private:
    //! Formatter generator traits
    typedef aux::date_time_formatter_generator_traits< value_type, char_type > formatter_generator;
    //! Attribute value visitor invoker
    typedef value_visitor_invoker< value_type, fallback_policy > visitor_invoker_type;

private:
    //! Attribute name
    attribute_name m_name;
    //! Formattr function
    formatter_function_type m_formatter;
    //! Attribute value visitor invoker
    visitor_invoker_type m_visitor_invoker;

public:
    //! Initializing constructor
    format_date_time_terminal(attribute_name const& name, fallback_policy const& fallback, string_type const& format) :
        m_name(name), m_formatter(formatter_generator::parse(format)), m_visitor_invoker(fallback)
    {
    }
    //! Copy constructor
    format_date_time_terminal(format_date_time_terminal const& that) :
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

    BOOST_DELETED_FUNCTION(format_date_time_terminal())
};

/*!
 * Date and time formatter actor.
 */
template< typename T, typename FallbackPolicyT, typename CharT, template< typename > class ActorT = phoenix::actor >
class format_date_time_actor :
    public ActorT< format_date_time_terminal< T, FallbackPolicyT, CharT > >
{
public:
    //! Attribute value type
    typedef T value_type;
    //! Character type
    typedef CharT char_type;
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;
    //! Base terminal type
    typedef format_date_time_terminal< value_type, fallback_policy, char_type > terminal_type;
    //! Formatter function
    typedef typename terminal_type::formatter_function_type formatter_function_type;

    //! Base actor type
    typedef ActorT< terminal_type > base_type;

public:
    //! Initializing constructor
    explicit format_date_time_actor(base_type const& act) : base_type(act)
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
    template< typename LeftExprT, typename T, typename FallbackPolicyT, typename CharT >\
    BOOST_FORCEINLINE phoenix::actor< aux::attribute_output_terminal< phoenix::actor< LeftExprT >, T, FallbackPolicyT, typename format_date_time_actor< T, FallbackPolicyT, CharT >::formatter_function_type > >\
    operator<< (phoenix::actor< LeftExprT > left_ref left, format_date_time_actor< T, FallbackPolicyT, CharT > right_ref right)\
    {\
        typedef aux::attribute_output_terminal< phoenix::actor< LeftExprT >, T, FallbackPolicyT, typename format_date_time_actor< T, FallbackPolicyT, CharT >::formatter_function_type > terminal_type;\
        phoenix::actor< terminal_type > actor = {{ terminal_type(left, right.get_name(), right.get_formatter_function(), right.get_fallback_policy()) }};\
        return actor;\
    }

#include <boost/log/detail/generate_overloads.hpp>

#undef BOOST_LOG_AUX_OVERLOAD

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param name Attribute name
 * \param format Format string
 */
template< typename AttributeValueT, typename CharT >
BOOST_FORCEINLINE format_date_time_actor< AttributeValueT, fallback_to_none, CharT > format_date_time(attribute_name const& name, const CharT* format)
{
    typedef format_date_time_actor< AttributeValueT, fallback_to_none, CharT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(name, fallback_to_none(), format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param name Attribute name
 * \param format Format string
 */
template< typename AttributeValueT, typename CharT >
BOOST_FORCEINLINE format_date_time_actor< AttributeValueT, fallback_to_none, CharT > format_date_time(attribute_name const& name, std::basic_string< CharT > const& format)
{
    typedef format_date_time_actor< AttributeValueT, fallback_to_none, CharT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(name, fallback_to_none(), format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param keyword Attribute keyword
 * \param format Format string
 */
template< typename DescriptorT, template< typename > class ActorT, typename CharT >
BOOST_FORCEINLINE format_date_time_actor< typename DescriptorT::value_type, fallback_to_none, CharT, ActorT >
format_date_time(attribute_keyword< DescriptorT, ActorT > const& keyword, const CharT* format)
{
    typedef format_date_time_actor< typename DescriptorT::value_type, fallback_to_none, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(keyword.get_name(), fallback_to_none(), format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param keyword Attribute keyword
 * \param format Format string
 */
template< typename DescriptorT, template< typename > class ActorT, typename CharT >
BOOST_FORCEINLINE format_date_time_actor< typename DescriptorT::value_type, fallback_to_none, CharT, ActorT >
format_date_time(attribute_keyword< DescriptorT, ActorT > const& keyword, std::basic_string< CharT > const& format)
{
    typedef format_date_time_actor< typename DescriptorT::value_type, fallback_to_none, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(keyword.get_name(), fallback_to_none(), format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param placeholder Attribute placeholder
 * \param format Format string
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename CharT >
BOOST_FORCEINLINE format_date_time_actor< T, FallbackPolicyT, CharT, ActorT >
format_date_time(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& placeholder, const CharT* format)
{
    typedef format_date_time_actor< T, FallbackPolicyT, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(placeholder.get_name(), placeholder.get_fallback_policy(), format) }};
    return actor_type(act);
}

/*!
 * The function generates a manipulator node in a template expression. The manipulator must participate in a formatting
 * expression (stream output or \c format placeholder filler).
 *
 * \param placeholder Attribute placeholder
 * \param format Format string
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename CharT >
BOOST_FORCEINLINE format_date_time_actor< T, FallbackPolicyT, CharT, ActorT >
format_date_time(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& placeholder, std::basic_string< CharT > const& format)
{
    typedef format_date_time_actor< T, FallbackPolicyT, CharT, ActorT > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(placeholder.get_name(), placeholder.get_fallback_policy(), format) }};
    return actor_type(act);
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename T, typename FallbackPolicyT, typename CharT >
struct is_nullary< custom_terminal< boost::log::expressions::format_date_time_terminal< T, FallbackPolicyT, CharT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_DATE_TIME_HPP_INCLUDED_

/* date_time.hpp
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
*/