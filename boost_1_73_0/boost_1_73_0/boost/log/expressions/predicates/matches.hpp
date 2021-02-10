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
YmIeOTRfZqrnQxHXekrjKWuqVmDQ9Ehh5tKvGRa2Dh8YHz2eGeRqo7KIzug0cRVHQi94hMLo0lIbY4itnBGOdpN9uz6bNPUNosi07SuRh42iTkK35mdg22DZFxc1YHqbxpz6YW1yamCY4EHlSZV4xsaWzJQB5n6jneWrI78UEuWfUEsDBAoAAAAIAC1nSlIw8mR6kQUAAHcOAAAbAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfbXNncy5jVVQFAAG2SCRgtVZtb9s2EP7uX3F1gcZOZTvpl61NU8xLndZY5gS2gzRYBoGWKIutJAokZTtr+993R0qOlNdt6JRYL+S98bm7hxzs/rirBbvw5OXbn48XPq3GmZKfeWDul/b9b+D+UOsKn085GcCNyje/C0+rfIOOVfFLL2/p3fefcnRFsdFtQJpXPr3iCKqR5pHMr5VYxgY6R13Yf/36Z+jBq71Xex68Z5ngCcwMzxZcLT14G9qRX2K22fQ1f+cBN8CSfmlqHgsNWkZmzRQHfE9EwDPNQ2AaQq4DJRb4ITIwMYdIJByOTs8ux5MPHqxjEcRk5FoWoGNZJCHEbMVB8YCLlbORM2VARqiOxkOhDRosjJBZH31zMFylmmyQe5ZoCWzFRMIW6IgZiI3J9ZvBIChU
*/