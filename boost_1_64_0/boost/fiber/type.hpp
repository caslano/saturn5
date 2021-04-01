
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
ljO3yHyuWAuPjfYXdxkrGOzY4dFY5OOoSnO2oBNXdz+uN8vZA9atlndxYsdac7ZbLIru/iHNVDlq7nwK5H4MsONfNvwuRphZ2PqpsN3000K5+R/CVR1duvD69TKvXmy6avUEObb6/8YtvzqO8a98Hta0SdjNujDqMmDjrb6MeEc/ZP50nL1elcKIY6KQIa+iQ7a3nvINLpeYP4+rdlQeXg34O0sqHnNBVf+Fxf8psE0QaEJuqFRsCHo3GXnmsXNBzp8zZK4TGIE2qaqhJucQw+ElNd/VKPh6nJUcZxTi+rR7gLZ/HramlWqeggJkCEsFtgfJNFYtUp5xnI4z/qrlU9aKTyqxDLrIRm4B2J1J+o9D0fiGoVpBwmN3yYX4UXU8++CkzTIuhF543QP1IV5o3ww9i2vl3/RUK2+8rjhtVFhUD92BOBouafRVP6/qHYMC6YcfiSc5IVtK+yo4F5SpNZnn6YTpa6hwL0W1K+L3a0bNQuiVDm19vEMj+29Z8VZ0FdcbnbqYUk1dpsMrRYNW97VcrRRDX+sD0kNll8iM+bgH41eIB9qMmFeXDg==
*/