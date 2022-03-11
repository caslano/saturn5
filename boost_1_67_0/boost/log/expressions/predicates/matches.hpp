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