/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_predicate.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a generic predicate in template expressions.
 */

#ifndef BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/functional/save_result.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

/*!
 * The predicate checks if the attribute value satisfies a predicate.
 */
template< typename T, typename ArgT, typename PredicateT, typename FallbackPolicyT = fallback_to_none >
class attribute_predicate
{
public:
    //! Function result_type
    typedef bool result_type;
    //! Expected attribute value type
    typedef T value_type;
    //! Predicate type
    typedef PredicateT predicate_type;
    //! Argument type for the predicate
    typedef ArgT argument_type;
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;

private:
    //! Argument for the predicate
    const argument_type m_arg;
    //! Attribute value name
    const attribute_name m_name;
    //! Visitor invoker
    value_visitor_invoker< value_type, fallback_policy > m_visitor_invoker;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param pred_arg The predicate argument
     */
    attribute_predicate(attribute_name const& name, argument_type const& pred_arg) : m_arg(pred_arg), m_name(name)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param pred_arg The predicate argument
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_predicate(attribute_name const& name, argument_type const& pred_arg, U const& arg) : m_arg(pred_arg), m_name(name), m_visitor_invoker(arg)
    {
    }

    /*!
     * Checking operator
     *
     * \param arg A set of attribute values or a log record
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    template< typename ArgumentT >
    result_type operator() (ArgumentT const& arg) const
    {
        typedef binder2nd< predicate_type, argument_type const& > visitor_type;

        bool res = false;
        m_visitor_invoker(m_name, arg, boost::log::save_result(visitor_type(predicate_type(), m_arg), res));
        return res;
    }
};

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_

/* attribute_predicate.hpp
jJHw/XLzp6cVOr7zag9/0hd+UC5vfmRqePu7l/bweaESvmf+1EFZBYW+8DGW8DFl4eV9604u3zMc31DHvFUa6Yluar4/2yXGV8bfIb/aDFdjLea7pF9JOp6z2ChLkPds4/TdFm991fDXl+X9FuoFd60XdffAk+Ku5Vf3GEg5cTfLKe+XHJD80O9TDJtt1QWhZW3p0d8B+xHGuEXaVDtKakFhfk76tHwps5zEZeBEbzWc25X4+r6xab8kHX/fO/Wx4lebKyHMqY3NuPLOmcTNzsyBfjtm0eLfhMvK5dDm9nMXBdhECxe/VuInlaU2AMUmtfglndVejr+9vPFrWOqhiu39c8qr7VQkupTBZq+medjp75E/k8Rv6b66L7gy9ercrIzUnKLphtTF00lS71c617nEs73jfYT8naXvme9VedOuIWnb87jTIY8Xe23/2POYl5vny+Nb1c6cx2EBecyMrXgeSdsxj2vDT8/jdsozKSCPRQXTKpTHSZb+FyJjRl5hfnm2dwLKc/gc6txSHtN2AefDTc5nu06XRpxexhcoY569jFenZRcxFFSsvxA3wMZQVsbMcsqZF1DOo+dQTkvfsttokPOprSmdY47oxdbGBxmPBngf9veVU2eYis8vxHOeX2zlM8NZyo6tTuq8FOWQ9z3IZEPmhET0hZHWOaFJheeE1beUzQlnmRd6/SvzgnecX36L8zh/rJI+J6Xrg/e8Z2lDuW+QepU1RerkrJyM1ClFOem+/hOGv8u77iBsvI6910v43UZP/p2BPI041ruEc1nni1nTc9Kmyzyl88AdEma1fFM5C3Hqd5qO5OfKJBz02vDbVflA/JOMuvp9uUvkgSPOZan38BtlvlHdZYwQPUTa+BgnSaZu5tahjaPjrWOntJM/zEjClHjDeIZZrgF7mJn+dCIvPi2dePQwb3liyuRO5Rnmm17W68jbHjW0PbQP6Bykdat9wJDy8cxFjN1uSacqvkTH43k+7AVbpZDHP1n6wNTs3Mlp2dm5uVcW5Ul6/vaTE/i+Jfjr77/H3yz2wl1x2i9iRK/mak9uDpnfkXYZbUvLtcnBeXWtxTm6SbtNz80owkbblKx81i1yrp2ca5GkvVHyMkjC5WcWWtYDv4h/J/S4wPNKnG5SuxnZ2RqnFmwoceJdDYlz2vlzMmf67Yzs5vz3StgnJVyILG6mDZaAI3LS8jTNWHi/hFsiXw8XN7QnxK0UlyyJ307Ok56fmVaILTqJb74bny1h2zrFlXK08eUxk9W/1Oc+8laFfuXWfuXvSynuc3unWvqQti9uki7nwk3OJX3K196MIzE+fZrqP6l+lepDU3z6ggD/RQH6vaq30/CrAuK/r3o31Q+oPjLRp38dEP54QPqhpfb4VUvt8WuV2uM3CvBvafoHrIeq6kLQTV3BfnAkYTbfYrmGrsjNwnZN4BjqeA0Qz7wGhqfId7Gy6IEFedlZhYaOlbFwl4Tr6G5OrJcR/R6Pxn/cNmZqmua1a7BGTcsvNMfMzrd5/WfTF6Ya/uv35K1et8PGRYykTyD+byyFS9hQVzXTZkTulCkFmWbe4uAeOV8bd0NWJS8g/nstw2LDMl7P3VvSW2S4uTYb8FZZAfTnYark4T5XCyOcq+iwWcYccV9m+c6T3g9omm/L+W8ivWhLmTNzMsy5xmXEyHn/Tpnr8Gz9iNPCVdNw8yXcNYSrbXjtKXRjzFxFuL/7viUw3PstEXdodCi2ikMwsG6/x9D8xEoaTez3GDruxItfnXLzJesCPW9sVfO8r3BeTtpcTup0zhslnUaO57xF/Go7ltH8nomOIfdaxpFIqx2uCsxJ8TonDZexw9aP5Zp6XtqRZ/oa+PQ=
*/