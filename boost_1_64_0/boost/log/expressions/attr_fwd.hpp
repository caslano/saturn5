/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attr_fwd.hpp
 * \author Andrey Semashev
 * \date   21.07.2012
 *
 * The header contains forward declaration of a generic attribute placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_ATTR_FWD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_ATTR_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

template< typename >
struct actor;

} // namespace phoenix

#endif

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * An attribute value extraction terminal
 */
template<
    typename T,
    typename FallbackPolicyT = fallback_to_none,
    typename TagT = void
>
class attribute_terminal;

/*!
 * An attribute value extraction terminal actor
 */
template<
    typename T,
    typename FallbackPolicyT = fallback_to_none,
    typename TagT = void,
    template< typename > class ActorT = phoenix::actor
>
class attribute_actor;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_EXPRESSIONS_ATTR_FWD_HPP_INCLUDED_

/* attr_fwd.hpp
+t5pJ3i+S4oD3oNl/J6g/KB3wFbeCdt07l1FWYn9d8P4lbaF1JmNpZFqHCNtiXnHnhF/o7E7u5a608RjfZ7d4HNyfSRf8xFBz6yZ3+ppdt02meun+evh3a8/CrfAfATYGO02t9C2Prstru1rfoeyPY76jov7RY+VPvLk5U/XZw5/ddtTeUeKQ9sS7Ta9k7dGnN3WGsqm1/Y5cHZbZSjbZtttknZba8AcOGmv1MPDyFv6dyYic6ZMHxB9TMFzpmTOlwv7w1h4KkyAp8E+8HQ4DA6A4+FAmAcHwQvgYHgE5jra1wNH6H2ikXG+NorcpztMhj1hKuwFh8LeMMN/7p2rfR7al1Ov33Tp2l9WoXPUajS+Sthbz9PhKjgEXgwz1X0hvAxeCC+Hy2Ed/38JroVXwGvhXXA9/AH8KnwI3g4fgXfCp+F34LNwK3wBfg++BLfBd+C98CjcDo/BXbAzaX8M9oOPw8HwCTgC7oZZsAGOhQ/AOfBBeB78IbwYPgwvgzvhVfBHcL2EV72ZNi26tMxZ/BOXPXxX9XXIhNN2G+xuCfcXDXdYn9tfNVytaedQpjRcPFKu4d7X5/4B7Aw/0ucV4TJHD37M+Uj4CRwLj8Gz9Xo2/Bfn0yA3oNwBOE+u+9It7QXYxZLudvjzMBomwfYabrP5RqYNIOEC9yV4mvvGw5/DAfAXcAJ8AZ4D98EF8CW4CO6Hl8PX4NXwdfhV+Bu4Cb4B74BvwTvh7+AWeADugG/D5+A7cC/8g+p3t/cbDf5D09kVIYyZS+rCc2EsnAI7whWq76kwB06HNXCWlvO58AZ4HrwFLoDfgudruV+s6boQPgoL4c/gEvhLWApfhUvhX+AX4Ad637/D2fCYnks95P1dhTMt9dAo/EXATJgIz9DyeaaWhzFwEjwL5qj7VHWfru67Ip2wbT5smw/b5v/LbPMFDbFODVKPNCD7EOf+WCcdyUGWIxvuD9vuw0f4CB9tOz6T8f90LZ8s2/+fLGv9J5n1RGifeNYpmi39Jd5lexqN/47/GljF1r4Swhlb1g7OM4n/Xe7HTmvGFjOEv6WPqJXr/5fr+jn+NpdNamP/idrYn4R34W93k3SzwlKZDI8PWAsKZVY7umc739USZovbjRyMYYy7LV/Ea/pjtmaZMfamj3HiHK4zIjbOWWb6t4+I2wRbP5GJr4fp36EEFHrS1ZhkHMzY+1fE7zb3a85h+hhkPLrYQF8T93vdpuuCpXjuLde+7F7ttvfrC5dBJKtWV9SYdL8t/nryHRyhbihS0n0FIVe7Xtv3h+Kv3hWbwnCNy68/MFbCrHClf8rEUefGOtWuz85OHxLBNIdmfkKW+I1y29Hiz3CeV3dvHFfxXCa7VW4H6QMtx3lDpK5VFt0nPrKDKVdmjbIL1V96O9qW+IvMj5sU3SkyJm5o3Olxy6JjIrvHpXv+QpZHR0WmRUdHpsSVxg3m/KK4c3Hpgp+k6AGRCdERkUlxUznrFjc1bmB0RHxsLPeZwP06wT8T93vIX5C1Xbg//Bvkb+kP+StyxOOG1ODmkffTgsaemD7zcslve/ewkyJ+PkTPuK5a5jhmXIQjfq4NqdPeqtNu4q/Y7U2f81TkNVplkwnVI0i33d2R7iAH/RrbkuOx1fnNt0gy7qSl0NidxN6eYuyKauWVy75+8J/Jfcz4BXkuee28a8dlx0fGOv7rlJl6IbkVfcO6VhnvjK//cqu4oVa1jwzT+qJAbf8LEBeZj0Rn8M88U19IFect326T8t1O/M2x1XnEoe8y+WjnnNjYpo8D5wKZ+i63vamfjU4astCBL/30aWd4OrX5WWHLk2qn6Twc80xqJEy8LS/E19R2SIz2vm78ts0=
*/