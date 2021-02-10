
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_TYPE_H
#define BOOST_FIBERS_TYPE_H

#include <atomic>
#include <chrono>
#include <exception>
#include <functional>
#include <map>
#include <memory>
#include <type_traits>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/apply.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/parent_from_member.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive/set.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/data.hpp>
#include <boost/fiber/detail/decay_copy.hpp>
#include <boost/fiber/detail/fss.hpp>
#include <boost/fiber/detail/spinlock.hpp>
#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/fixedsize_stack.hpp>
#include <boost/fiber/properties.hpp>
#include <boost/fiber/segmented_stack.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class type {
    none               = 0,
    main_context       = 1 << 1,
    dispatcher_context = 1 << 2,
    worker_context     = 1 << 3,
    pinned_context     = main_context | dispatcher_context
};

inline
constexpr type
operator&( type l, type r) {
    return static_cast< type >(
            static_cast< unsigned int >( l) & static_cast< unsigned int >( r) );
}

inline
constexpr type
operator|( type l, type r) {
    return static_cast< type >(
            static_cast< unsigned int >( l) | static_cast< unsigned int >( r) );
}

inline
constexpr type
operator^( type l, type r) {
    return static_cast< type >(
            static_cast< unsigned int >( l) ^ static_cast< unsigned int >( r) );
}

inline
constexpr type
operator~( type l) {
    return static_cast< type >( ~static_cast< unsigned int >( l) );
}

inline
type &
operator&=( type & l, type r) {
    l = l & r;
    return l;
}

inline
type &
operator|=( type & l, type r) {
    l = l | r;
    return l;
}

inline
type &
operator^=( type & l, type r) {
    l = l ^ r;
    return l;
}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_TYPE_H

/* type.hpp
H0d3uiJPM5/dkXc0GbrIcWtn/yn67KMHj/0gfORgz/EGR/6jB4YOfs1sDvwfUEsDBAoAAAAIAC1nSlIrTka3IAQAANIIAAA6AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9YWV9TRVJWSUNFX05BTUUuM1VUBQABtkgkYK1UbW+jRhD+zq8Y0S92xOFL01OaJj2Vc0hD4wACnJwlS2gNS9gesGh3iR01/e+dBdzU12svHw4L77I788zbM2OvTTj6Zo9hazj46pP2b4oPrnulUPDfaaa+rJCmzzD8UHGN6ytMzeBF6zmdwqu0nmHSa6WjrQu9T9NXmFtrJ/XfTCuvU73Fk0Fz1J/z9kmwh1LBZD6F47OzH+ENfP/2+NSCS9IwWkGsaLOh4sGCi7w/+aUku50t6XsLqAJS2QeASckkSF6oLREUcF+xjDaS5kAk5FRmgm3wgzWgSgoFqyjMg3Dl+b9asC1ZVo44T7wDWfKuyqEkjxQEzSh7HGBaIhTwAhEQP2dSIWanGG9sNE9BUVHLEUY7QSrJgTwSVpENmiMKSqVa+dNslnWiwkhmOc/kLNunwi5V/VlUK/SmJk/AWwWKQyepBVregprnrNArpggP225TMVlaL26hwSaf
*/