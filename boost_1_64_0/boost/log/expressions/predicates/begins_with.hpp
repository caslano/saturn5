/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   begins_with.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a \c begins_with predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/utility/functional/begins_with.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * The predicate checks if the attribute value begins with a substring. The attribute value is assumed to be of a string type.
 */
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
using attribute_begins_with = aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
class attribute_begins_with :
    public aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value beginning
     */
    attribute_begins_with(attribute_name const& name, SubstringT const& substring) : base_type(name, substring)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value beginning
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_begins_with(attribute_name const& name, SubstringT const& substring, U const& arg) : base_type(name, substring, arg)
    {
    }
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > >
begins_with(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), substring, attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename DescriptorT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_begins_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
begins_with(attribute_keyword< DescriptorT, ActorT > const&, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), substring) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename T, typename SubstringT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
begins_with(attribute_name const& name, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, substring) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_

/* begins_with.hpp
E9dcW1wX19RX1TXEFVf8h+ZrsdutcWfebYeZpmC77Wlpty/kR6fxm8MIzZZGxinBunuf1MdFFLo9jfg39fFBcTsft9a6a9yasVcC6SQepIl4eOrjg3JNnhemE/1ogb0fLrOlta6KCUzVinjrX9mn8fXF6i40Nk8gra31xWM1nZsLo9N5D+kst6WTn8mnj7qkRswzxZfWck/Z9nAkrdXArsMbkd7qI+xreB7XeF5E2W4sik7zHaR5ciDN9Uui37FzahvqzHjYx3g4RnoJI3INE5/W9Bq3nrXA+NNLPEibjsu9bVaf5223Ey36/d8mvXMt6dV+NK60zo2I/8Hcw4t/WLuzxHUW5VVriyt9DHYl3OFBaLweRxy8ebOoOPp5U3leo/V52NbSvJlS1HLeNEbkzf444hXMG8LWvAmP67RO0XGdidsmW1xrl9cvirMcmxKos+o2tBaeQLoSqbPlJdFpnU5aN9rSKoP4+MoF/2F217AJV3lpjLRujEjrgQTSSjyi0srzuMbzIuZ24ztH2xm907UjEEirpE7aZdQ8pcLMkR8St7m2NGs4Ot4zawX2NOPWrHeMc8uAuF0n6+8ZnjlBfDY87bZktK/WOHjb/t4uAc+3Iz5kPfJV/O6IygdsiM1fEpwa6NhI80PXDF8UP1+05QfhWdc3zPrFm3J/TdTaRrFb3+Xe5da1io7wU7k/2tjX+kDO0wNrFeTlZNJYSmqzMgu8fYPkZ9BNQ5fgesaSUN8a4WY9bnq44bTr7amfus7HeYr5ltTyN6Vce5lpu6ww+tG5SbH0oI+e/qxdnzq2vvMfHvRxveOhdd9p+MvlH89oyHz3Ox/1efro6Snb9alj63fb9ZGPnr6zXY87cX3nRPXQY+mJfyi6g3JInU4j3t0c6qXn797mb6nT5u9Vnr97edys0evd+fsqz99Xev6+zvP3NZ6/V3v+bvT8fanqWZcgV+vfN/2DvTMBj6q64vibSchCAoQQQlgN+2KEgAioSNlFjRoBMbgFJGGRLZKgQbGGxYpK26ioaLGl1rrVKlVUVFRUKqioUdHS1mpUrChYEVHRovb3zpy582bmTjIRu31fXr6T/7x7z73vLufu954L6ZlPXTeWtfCoM5/5ehZ1INgEHAS2AAeDLfW9lb53BkeBXcBjwYHgUHAIeBz4I3AYeAr4I/AccDg4FxwJVqh7PWvMeqk50xx11vjneha1GsyIOIvaE1yj378FHA7+Uv2dYtYAJSxRZ6XbwNcUbAdCTkcQcjqB3cAOYJ6+DwRzNX7twWP03ZyV1u+MsYS/u36nl/rTW/3pAx4LHqHplQeO0Pd94F5onfr7gvrbHtqp/h4PXxp4kuZLAZgNTgPbgydr+pwC5oOn6fdPBYfo+1CwEByu7+PA8WABOBG8GDwdXA5OAleAZ4MrwTPBVfq+GjwLXKPvt4HngHeC54L3arjWg1PAh/X9MfA8cIu8a74F1yLAIy359mOVh8vAVD1bng6uAJuBSzU9loG9wOWaj1eAA5QvWB726neejCwPeiY4Adyk5eFpMAvcDPYFnwWHgVvAM8HnwVLwJT3T/DJ4M1gD/gp8A1wLvgbeDm7XM8evg0+o/T6w0swtI/sarnRoTvBspMZ/HpgJzgcHg2UqTxVgIbgQLAMvAS/Q90p9XwRWglXgxZqfl5gz5TrfC3axnOmcrt+fofXATHWXq3OqesaROin8jGOuh682Tj7m5GKemVxp+Hi+jc+/jDj5cuPky4+Tb3icfIV18B3m4ZsSJ19ZnHxVcfJVx8m3Ng6+IcE+OJhjOVP7a22PbgWb6tn/NuBtnnJSo+5vspSTO1RO7wFbgPdp+V0Hdgf/oOX4fnC46gw=
*/