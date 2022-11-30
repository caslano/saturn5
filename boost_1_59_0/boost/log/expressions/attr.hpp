/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attr.hpp
 * \author Andrey Semashev
 * \date   21.07.2012
 *
 * The header contains implementation of a generic attribute placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_ATTR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_ATTR_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/copy_cv.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/value_extraction.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * An attribute value extraction terminal
 */
template< typename T, typename FallbackPolicyT, typename TagT >
class attribute_terminal
{
private:
    //! Value extractor type
    typedef value_extractor< T, FallbackPolicyT, TagT > value_extractor_type;
    //! Self type
    typedef attribute_terminal< T, FallbackPolicyT, TagT > this_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Attribute tag type
    typedef TagT tag_type;
    //! Attribute value type
    typedef typename value_extractor_type::value_type value_type;
    //! Fallback policy type
    typedef typename value_extractor_type::fallback_policy fallback_policy;

    //! Function result type
    template< typename >
    struct result;

    template< typename ThisT, typename ContextT >
    struct result< ThisT(ContextT) >
    {
        typedef typename remove_cv<
            typename remove_reference< typename phoenix::result_of::env< ContextT >::type >::type
        >::type env_type;
        typedef typename env_type::args_type args_type;
        typedef typename boost::log::aux::copy_cv< ThisT, value_extractor_type >::type cv_value_extractor_type;

        typedef typename boost::result_of< cv_value_extractor_type(attribute_name const&, typename fusion::result_of::at_c< args_type, 0 >::type) >::type type;
    };

private:
    //! Attribute value name
    const attribute_name m_name;
    //! Attribute value extractor
    value_extractor_type m_value_extractor;

public:
    /*!
     * Initializing constructor
     */
    explicit attribute_terminal(attribute_name const& name) : m_name(name)
    {
    }

    /*!
     * Initializing constructor
     */
    template< typename U >
    attribute_terminal(attribute_name const& name, U const& arg) : m_name(name), m_value_extractor(arg)
    {
    }

    /*!
     * \returns Attribute value name
     */
    attribute_name get_name() const
    {
        return m_name;
    }

    /*!
     * \returns Fallback policy
     */
    fallback_policy const& get_fallback_policy() const
    {
        return m_value_extractor.get_fallback_policy();
    }

    /*!
     * The operator extracts attribute value
     */
    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type
    operator() (ContextT const& ctx)
    {
        return m_value_extractor(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()));
    }

    /*!
     * The operator extracts attribute value
     */
    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type
    operator() (ContextT const& ctx) const
    {
        return m_value_extractor(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()));
    }

    BOOST_DELETED_FUNCTION(attribute_terminal())
};

/*!
 * An attribute value extraction terminal actor
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT >
class attribute_actor :
    public ActorT< attribute_terminal< T, FallbackPolicyT, TagT > >
{
public:
    //! Attribute tag type
    typedef TagT tag_type;
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;
    //! Base terminal type
    typedef attribute_terminal< T, fallback_policy, tag_type > terminal_type;
    //! Attribute value type
    typedef typename terminal_type::value_type value_type;

    //! Base actor type
    typedef ActorT< terminal_type > base_type;

public:
    //! Initializing constructor
    explicit attribute_actor(base_type const& act) : base_type(act)
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

    //! Expression with cached attribute name
    typedef attribute_actor< value_type, fallback_to_none, tag_type, ActorT > or_none_result_type;

    //! Generates an expression that extracts the attribute value or a default value
    or_none_result_type or_none() const
    {
        typedef typename or_none_result_type::terminal_type result_terminal;
        typename or_none_result_type::base_type act = {{ result_terminal(get_name()) }};
        return or_none_result_type(act);
    }

    //! Expression with cached attribute name
    typedef attribute_actor< value_type, fallback_to_throw, tag_type, ActorT > or_throw_result_type;

    //! Generates an expression that extracts the attribute value or throws an exception
    or_throw_result_type or_throw() const
    {
        typedef typename or_throw_result_type::terminal_type result_terminal;
        typename or_throw_result_type::base_type act = {{ result_terminal(get_name()) }};
        return or_throw_result_type(act);
    }

    //! Generates an expression that extracts the attribute value or a default value
    template< typename DefaultT >
    attribute_actor< value_type, fallback_to_default< DefaultT >, tag_type, ActorT > or_default(DefaultT const& def_val) const
    {
        typedef attribute_actor< value_type, fallback_to_default< DefaultT >, tag_type, ActorT > or_default_result_type;
        typedef typename or_default_result_type::terminal_type result_terminal;
        typename or_default_result_type::base_type act = {{ result_terminal(get_name(), def_val) }};
        return or_default_result_type(act);
    }
};

/*!
 * The function generates a terminal node in a template expression. The node will extract the value of the attribute
 * with the specified name and type.
 */
template< typename AttributeValueT >
BOOST_FORCEINLINE attribute_actor< AttributeValueT > attr(attribute_name const& name)
{
    typedef attribute_actor< AttributeValueT > result_type;
    typedef typename result_type::terminal_type result_terminal;
    typename result_type::base_type act = {{ result_terminal(name) }};
    return result_type(act);
}

/*!
 * The function generates a terminal node in a template expression. The node will extract the value of the attribute
 * with the specified name and type.
 */
template< typename AttributeValueT, typename TagT >
BOOST_FORCEINLINE attribute_actor< AttributeValueT, fallback_to_none, TagT > attr(attribute_name const& name)
{
    typedef attribute_actor< AttributeValueT, fallback_to_none, TagT > result_type;
    typedef typename result_type::terminal_type result_terminal;
    typename result_type::base_type act = {{ result_terminal(name) }};
    return result_type(act);
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename T, typename FallbackPolicyT, typename TagT >
struct is_nullary< custom_terminal< boost::log::expressions::attribute_terminal< T, FallbackPolicyT, TagT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_)
#include <boost/log/detail/attr_output_impl.hpp>
#endif

#endif // BOOST_LOG_EXPRESSIONS_ATTR_HPP_INCLUDED_

/* attr.hpp
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
*/