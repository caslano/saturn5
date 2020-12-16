/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_in_range.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of an \c is_in_range predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_IS_IN_RANGE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_IS_IN_RANGE_HPP_INCLUDED_

#include <utility>
#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/in_range.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * The predicate checks if the attribute value contains a substring. The attribute value is assumed to be of a string type.
 */
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename BoundaryT, typename FallbackPolicyT = fallback_to_none >
using attribute_is_in_range = aux::attribute_predicate< T, std::pair< BoundaryT, BoundaryT >, in_range_fun, FallbackPolicyT >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename BoundaryT, typename FallbackPolicyT = fallback_to_none >
class attribute_is_in_range :
    public aux::attribute_predicate< T, std::pair< BoundaryT, BoundaryT >, in_range_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, std::pair< BoundaryT, BoundaryT >, in_range_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param boundaries The expected attribute value boundaries
     */
    attribute_is_in_range(attribute_name const& name, std::pair< BoundaryT, BoundaryT > const& boundaries) : base_type(name, boundaries)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param boundaries The expected attribute value boundaries
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_is_in_range(attribute_name const& name, std::pair< BoundaryT, BoundaryT > const& boundaries, U const& arg) : base_type(name, boundaries, arg)
    {
    }
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value
 * is in the specified range. The range must be half-open, that is the predicate will be equivalent to <tt>least <= attr < most</tt>.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename BoundaryT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_is_in_range< T, typename boost::log::aux::make_embedded_string_type< BoundaryT >::type, FallbackPolicyT > > >
is_in_range(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, BoundaryT const& least, BoundaryT const& most)
{
    typedef typename boost::log::aux::make_embedded_string_type< BoundaryT >::type boundary_type;
    typedef aux::unary_function_terminal< attribute_is_in_range< T, boundary_type, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), std::pair< boundary_type, boundary_type >(least, most), attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value
 * is in the specified range. The range must be half-open, that is the predicate will be equivalent to <tt>least <= attr < most</tt>.
 */
template< typename DescriptorT, template< typename > class ActorT, typename BoundaryT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_is_in_range< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< BoundaryT >::type > > >
is_in_range(attribute_keyword< DescriptorT, ActorT > const&, BoundaryT const& least, BoundaryT const& most)
{
    typedef typename boost::log::aux::make_embedded_string_type< BoundaryT >::type boundary_type;
    typedef aux::unary_function_terminal< attribute_is_in_range< typename DescriptorT::value_type, boundary_type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), std::pair< boundary_type, boundary_type >(least, most)) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value
 * is in the specified range. The range must be half-open, that is the predicate will be equivalent to <tt>least <= attr < most</tt>.
 */
template< typename T, typename BoundaryT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< attribute_is_in_range< T, typename boost::log::aux::make_embedded_string_type< BoundaryT >::type > > >
is_in_range(attribute_name const& name, BoundaryT const& least, BoundaryT const& most)
{
    typedef typename boost::log::aux::make_embedded_string_type< BoundaryT >::type boundary_type;
    typedef aux::unary_function_terminal< attribute_is_in_range< T, boundary_type > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, std::pair< boundary_type, boundary_type >(least, most)) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_IS_IN_RANGE_HPP_INCLUDED_

/* is_in_range.hpp
59W89I9vftozlt7Shuv3tOszjaWHtOH6TO16VGPrS82U9F9+xy9ef39Lfv6SLRMqZ/309j3cuybmFe2u/HzJaTefeXmfM36ZMTB1J2aSbucPabP5kw4f7nxtyB3tTz23y+LY+l6/3uCanzD64THFg79d0frWvIvfrzh2YWy9t3Y9trH1rtr1tMbWx2rXh9twvb2x9PN+4c6RQTxy9qkX7ru4Z0A8v7fr71z3vL/n97v6G3DeC/2WtatavjfVbQ/097uO7KE05p+Gfss85yYwG7pPfxdCD+rvadAG/f0139gHrjY6grCDNuk4eaXG5QG9o+4hsC34MDgQfAQcDG4BjwY3gjPBx8HZaj4HfBJcBj4FVoNPgzeq/WpwM3g7+EfwfvBZ8GG13wfeGdQRA/xcw5cJrdHwbYPPxZfAZPBl8DCwBuwMvgN2Vd25fcDXwL7g6+Dx4BvgicpXAO4ATwf/DE4B3wQXg2+Dl4O14JXKfzX4N/Bn+r4PHGL0p1D/angToTwN7/EJgfCOA9uDJ4AdwRPBfWAltFfdz1T36dAcdT9D8+N8zY/ZYH9wjuZLBTgInAeOAueDJ6j5ieAFYBG4AJwGloMzwApzZ6Hq2NCx96aIOwsv0u8vAlPAi8F08FLwcLBKw7FU5WMZOAT8MXisvu8DtxrdDaJLwMjtRv3OW/7Ad94B24LvggPB98DB4Ofg0eD74Ezw7+BsNZ8DfgBWgLvAy8GPwJXgbvA2cA94l/LfDX4MPg5+Aj4H7gVr1P4VcB/4NvgZuBvcD+5V+30iNzy14fHJEfkMPLfB1xy8U+NzF9hB33P1PR+8W+P1O/B48H7wHPABjd96cCH4ILgcfAhcAW7Q+G0Er1f/fgNuAp8AnwI3g8+Az4KPgK+q/Vtqv1PtPwQfBj/R931gdfDMOLhW49cCIgzybIEvAXwBzAC3abxeBHuDL2m+1YBjwFfAAvBV8CzwNXCaursA/BP4c3CHxucv4E3gdvBX8q7lzadnjfUc9Sawm0eX/NnwpYNTwTzwPE3naeBxYAl4MlgKjgeng+eDM8H54K9UjmaD1eAcDcdclZv54P1gGfgweIHKzwLwRbACfA28EHwdvAT8AFwMfgpeCv4T/DGYQpgvA9PBa8EccDbYF7wRHAauBseCN4EF4K/AQnA5eAa4AjwLvAqcAV4NzgLXgMvBW8Cr1N0+B35Hz3sC0zRfm0OLNV9/qfXrWi3vvwabg7dq/fMbsBN4L5gL3g72Bu/QeuAusBC8B5wM/h48R/mLwbvB8/R9X+A7CGJ4eyTrOxqeK7T+uUq/f7V+Z6XWNzdre/RzrdeqwdlqPhe8FlwEXgdWqflS8HoQcm4AbwJvBO8AV4N/ADEjf+HXcO41Z+CQGZW79tBODWc30jcR7AVmgr3BbPA4sC/4Iy0Pw1UOR4DDwMPB08E88GzwCHC2mi8CjwSXggPBn4KDwWfUv23q36vq32tgX/Afav+l2n+j9t+qe84ViH0ROBw8FxwBFoNDwFJ91/6Cnksi7y39hQPw+cGDYDvwG3AA+C04CGQiVOLtA8eACeBpYBPwPDAJvBhsBl4BtgCvVncrwabgNWr/S7W/Ve33iczoGRegleZLlqdv9hCDMdEJBTYFHwO7gk+Ap4BPg7PBZ8CLwM3gInALWA1uBW8EnwN/q+YPgC+CG8GXwC3gK+B74KvgLvBN8EPwT2Cij/oLbAb+FcwEsZfwE3A9u8B8sYa/I7Rfw/+O6w7cBbrmH2n4d4NHg/vAAvAzcCL4JVgGfg0uB/8JrgAPgr8Bv9F4MMgjHoDWY0ngFjAZfAFM1/YvQ9u9LPArsA2YQDjbgS3B9mArsAPYFswF24MdwW4=
*/