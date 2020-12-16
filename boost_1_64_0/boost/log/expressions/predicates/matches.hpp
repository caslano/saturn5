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
YCewj5rngXv4/ongx+CpYq71enA/PNjZ0o8aof2okWAncBSYC45WOaCd0T3Msn9d3J8BbcbcfdI0HbPAk8C24Gn6Ph1sDc4Bf6vplw0uBtuAS8Ec8Fp1twbsBN4G5oJ/ADuD28Au4A6wO/gB2AP8B9gT9BO4XmAK2BtMBbuDbcA8sCN4BNhZ33vp+7FgP3AcmA/OA68FfwxeB64HB4GPgIPB58Eh4Kvg0eDb4DHgPvBY8CtwKNjKHzDvDo4C+4CjweHgGPAEcCw4CRwHzlD7ReBE8BrwDHAtWAT+AZwMPgieCdaAZ4Gvg+eCfwWngbvBmSB1gDMLTAXPB7uBs8He4EzwdHAuWALOA+eAFeBi8EJwCXgReCNYCT4ILgIfBS8FnwN/DL4CLgF3gZeDH4M/AV0BuwJMBleArUHXvCv4czAfvBI8CbwKLASvAyeDq8Cp4PXg+eAN4BzwRvBCcDV4HXgzuBa8Bbwd/CV4H/hr8HHwVvAF8DbwZX1/A/yt1g/jgnu0dO/apoj7V++Gz8V7wGTw92AueC/YDVwHDgT/oP4VQWvVvyPVvxSoQP07Vdv/QjAdPA1sDZ4OtgMnge3B8WA+OAEcoOb71L9a9R8ZkPfW0Hr1v7P2F7qCeWAPcD7YCywHe4MrwD7gT8F+4K1gvo4bjwEfUfOX1PxVsD/4LjgA/FzSCjkHh4EJbnsHtgSHg4eD48B+4AngELAAnACOMeMi3YMCjrSMi7I0nbLBFLANmA12AtuAOdpPaqvj0HbgMLAjOEL5tH3VvRLIkqV9HaPt6wlgGngimAOepOOJyeBhYAGYD56i44lTwePVvAgsAs9S/rPB07TfO17HFxO0nzERXKV82j7pGjp1laV9+kDlZBfYCvxI5WWP9tc+Bgfq3TXHgU3AEWAyOEr6VfRjwU/BMnAf+DPlv1H5f6H8t4CfY38n+AX4APgl+Dj4Ffgs+DX4PPhP8BXwILgb/Bak/hV/08AmYAswGWwJ+sFstT9M7buqvcqDrgfTp7PIw2T8F5kHM8BzVB7OBTuDxWBXcCrYFywB+4HTwKH6vg/MNeuuhCHQn5TfWab8hPiq4uSrroOvi4dvbZx86+rgy/XwbYqTr8bDV+sL53vXw1dbB99UD9/eOPmcL+vmY7tzXPcmraeEZh1MdQZChVAltBoawj1KRVDwXqWiJdzng3nwfqW94BzMqqGMU/D3aRLpWOzg6QAeBHcwQZH7DZK2lHt/oOBdTKMx27M30RmK2RDcFkXczTRlafT9TAfAdCqGFdjdBm2D3sQ8D7ODS7FbFri/KReMvsMJXBa6x6mS3yXgBt5roTW8r4e2QwegmYRvyHJ4oW6FuIU6fJoo9z4NB2fyvhy71a5f/N4I3sN7GXbe+6ASmZhZB2ZdrndDgVOgGsyG8r4XrOR9FRS8MyqHyq0CvBOzleBW8E5wOWEKu0Pqctx67pLK30vYXfc/ISy8b4ZWE57g/VJTMB8KVoLV0JRh+Auuwd9d8G7ld4pboWKecwVpx+/h0BB+F0Fb4dP7qBjs8F3eV4MdngndT7WR9xq+Gbyn6iDv6d8iU7hZA43GbBO4H54p/O6FnfcOq277Ep0hK4ifS9idvZc0wK7Kfce+DFrN72pwPbRD77qqwawC/nv4vYffBzBPvJIwu98A94OJw8PvwCrEvATMmUj64XYjVOHa814ILef30GewA2fyfhu4CjfboT3QRt6rXLdQ1lXEH/c7XL/5vR9cuZcwYjeF9x1gNXgQLMTPxBHEBcw9Pex+rai7tWqhg9Am3A7HLGtS6J6ts8EqaC2U+B1x53s7rwq/f2sHlIud9x6u/KtDd3EV8HscaV4F3gblYLYRtN0=
*/