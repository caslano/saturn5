
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
/PVsf7iajnKNdFe4WRU+IRSai8XG6VZMEqVQ/jz7ED1/fwg31MayADoKpJ9QRWD77Dcq2BIg04UVo4xlbGuVwdi25xHQkhrMUXSnbEldxoD2AALtcVPJpyGS6hqfC0crhHAUD+lb9FC9nEO1EC4up3NAHtdO5hH3HB5SVIagCVBC6Oux6kprESU9qsJikrJ6AWiOqZWZ8kg6uIlLB5NsFEBkE9aBXbo6RAdW+QBWCEb57Fw4mx/ik7ioId+bhfETDCji5RrW8kUYVxpuOuFAM9km9PwzuZ5/gjL0WdJkSGgejpZAT8wEPX/gIa7m13gJymwrXeO9bkClcGdoFd74IILar3zADmXggePoyHicTfNjd2PQ9052z7j85sEsJ9zCc5ZoOQXN8SxnwI0853bKmcFyimAhC5Qda2MIRBMU1yju34EN/NgdfAk2abK9N+5oO5Nw5zcR/GqBWhgBb1Mm+C1iWy8ftl4Gbr0i3HpZ2uaB/ZYBq0aLYIRR72Q/mxZA5N6y7SD1/lpVYrrhDr5zaEFvvEMPHUKkqwVnBB32p7kBRhuVJ5TqbuYba82VpOgA4M+4rGTGZaWqwexpd215UOyuNx4kGclL/GldRc8biCUYVkqvg/nz8lXiHCdiaoff9JWearW98p45KzjRypFcaVBm6KyOUKwtSYJi6YjVL8va3nVxWvXqP31olRNQH3AFqILBzu25/IQJ1jie
*/