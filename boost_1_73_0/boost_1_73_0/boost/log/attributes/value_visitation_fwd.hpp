/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_visitation_fwd.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * The header contains forward declaration of convenience tools to apply visitors to an attribute value
 * in the view.
 */

#ifndef BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief The class represents attribute value visitation result
 */
class visitation_result;

/*!
 * \brief Generic attribute value visitor invoker
 */
template< typename T, typename FallbackPolicyT = fallback_to_none >
class value_visitor_invoker;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_

/* value_visitation_fwd.hpp
H6Xm4iSaj+h8zgqd2KYHIZ930E4AV3QlDLl+cnr8y69B73jvh96XcwdeGgN/4g78iTHwv4nGJ3Np7Js0hh4iw3+Eys5cMndMGVKvldQLE8pElKIu5q/B+QSJSwnqWbrzyF+Qw8Z/k7QEr497fbyP1eQaQrutPfrluViljiyG00BCNVrnken7u+cWxkjE18tdA9CeE6vtmH/bqF91BE6F+mtuqhjRlzz6IyDgu0dfPHT8ZNChP2bmGyUBBTpQo8FemEj4xNYO2Qi7cYzUQvMAPvn9m9ikUBafW4pI+Ajb/J1krphkVs871E8WwATKVV/q9M96Su4TeMhmOE11/PfH1Ca6HSCeu5unEdHIEGAN4w2pyTUZw6/TFPL7RstHnUNUT+npHZsXHeKJj6GeXtWpgPfBPR/lHHDY0PYyzgr0B/rqDgsQJoCvG/We673z5/zY2izV3vkMSx4En2ZxCv5eDVJ080XzXXxVrvpbWIQN5x9D9/8RFzvUc4EGUsqAo1p/v3/17jl5C9tPB+BfDrCD7S30L79ksDfFZaFKSvACW09lBS3fjq9+aLRDzAdBoxG26zG0xVg9+HJUMQbc7RQLbhUOXQ+m5AzROKthckf1oPfy4NVBf+3B1DDep1bKDnxt+9T8kjV3q9NbIA+s
*/