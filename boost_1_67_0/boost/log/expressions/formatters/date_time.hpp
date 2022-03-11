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