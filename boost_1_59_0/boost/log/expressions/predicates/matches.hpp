/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   matches.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a \c matches predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_MATCHES_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_MATCHES_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * The predicate checks if the attribute value matches a regular expression. The attribute value is assumed to be of a string type.
 */
template< typename T, typename RegexT, typename FallbackPolicyT = fallback_to_none >
class attribute_matches :
    public aux::attribute_predicate< T, typename boost::log::aux::match_traits< RegexT >::compiled_type, matches_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, typename boost::log::aux::match_traits< RegexT >::compiled_type, matches_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param rex The regular expression to match the attribute value against
     */
    attribute_matches(attribute_name const& name, RegexT const& rex) : base_type(name, boost::log::aux::match_traits< RegexT >::compile(rex))
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param rex The regular expression to match the attribute value against
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_matches(attribute_name const& name, RegexT const& rex, U const& arg) : base_type(name, boost::log::aux::match_traits< RegexT >::compile(rex), arg)
    {
    }
};

#if defined(BOOST_MSVC) && BOOST_MSVC == 1925
// MSVC 14.2 has a codegen bug that makes inlined `matches` functions below crash on copy constructing the phoenix::actor on return.
// https://developercommunity.visualstudio.com/content/problem/982738/bad-code-generated-in-boostlogboostregex-test-case.html
#define BOOST_LOG_AUX_FORCEINLINE_MSVC_BUG982738 inline BOOST_NOINLINE
#else
#define BOOST_LOG_AUX_FORCEINLINE_MSVC_BUG982738 BOOST_FORCEINLINE
#endif

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, matches the specified regular expression.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename RegexT >
BOOST_LOG_AUX_FORCEINLINE_MSVC_BUG982738 ActorT< aux::unary_function_terminal< attribute_matches< T, RegexT, FallbackPolicyT > > >
matches(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, RegexT const& rex)
{
    typedef aux::unary_function_terminal< attribute_matches< T, RegexT, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), rex, attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, matches the specified regular expression.
 */
template< typename DescriptorT, template< typename > class ActorT, typename RegexT >
BOOST_LOG_AUX_FORCEINLINE_MSVC_BUG982738 ActorT< aux::unary_function_terminal< attribute_matches< typename DescriptorT::value_type, RegexT > > >
matches(attribute_keyword< DescriptorT, ActorT > const&, RegexT const& rex)
{
    typedef aux::unary_function_terminal< attribute_matches< typename DescriptorT::value_type, RegexT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), rex) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, matches the specified regular expression.
 */
template< typename T, typename RegexT >
BOOST_LOG_AUX_FORCEINLINE_MSVC_BUG982738 phoenix::actor< aux::unary_function_terminal< attribute_matches< T, RegexT > > >
matches(attribute_name const& name, RegexT const& rex)
{
    typedef aux::unary_function_terminal< attribute_matches< T, RegexT > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, rex) }};
    return act;
}

#undef BOOST_LOG_AUX_FORCEINLINE_MSVC_BUG982738

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_MATCHES_HPP_INCLUDED_

/* matches.hpp
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
*/