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