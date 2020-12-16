
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
l0UaGYqmjs110vAQLr8yScy1kYTLIgePouadZjo5bGzGcmCrRKFDwsUSsLilFc10EphMuHKUYeI+PJpwMe8t9vu8Zjren9rMgfdBDe+9ipqoR8f7P3oceD9Ww/s0nv97dLxf5HHgfUjDe54PXObR8b6fx4H3JYRL3/ube3S8/zrJgfdhwqXv9y8k6Xj/aJID7yMa3nOc4oYkHe9/nOTA+0LCpbfcnZN0vE9LcuD9DA3vWyhqPkjU8X5zogPvizS89ypqKhN1vC9LdOB9PuHSW4MLE3W8PyPRgffFhEtvB/Ym6Hj/SQLzPgf2RCxWl4XSLRvIxdixex88zqPHbHE+/1humKgn/JHSd/575cNhq/05I0En+dYJDpIvQaYxIrNDsM2tE/sbbr3YaU2LEZlnhfe4tevfbgeZl2KDGZHZZb7ErRN4wK0XOK3dMCLzSPO4ddLe5XLScnZms3n5jUvH7DUup2FmZzb7xdNcOmb/xOXA7AI7sz0c/3Np438uB2YX25nN4fi/1nk1zH4TUrXMLrIzmwNNKwCkPrNvhVQts/Mde/alAFKf2X0gVcvsQjuzWaE1A5D6zN591KtndtjObPZwXwSQ+sxeC6laZofszE5XRESO6ph9NaTqzYid2TwH7HZUx+yTjjowO2hndjNFxOff6Zj9FqQ6u7Ec5c5+9+LRVmVy13c6ls+E1Dg+7AxsPKMzxz7yv9Mx/ixIdXZgKcrN6Mwzvv3f6tj/GaTGmVeMRhIYnbnHr/lWJ4SlkOo8qaAoN6MzR0Ou/FYnijxIjTfXs4uCA1Deb3Wi2HMkrihG2kXB2n3jEZ0oHjkSVxQhuyhYx193RCeKkUfiiqLEURQdAVAT/zsSVxT5dlFwyPWtwzpRbDgcVxSFdlGwVzvzsE4UEw7HFUXQLgpe+znrsE4UWYfjiqLALgqeV3x2SCeK1yE1XoTKLgoOxS49pBPFzYfiiiJsFwXPLvIAULP/8VBcUYy1i4Jtwp6DOlF8DKlxY+B7+5dOto6Hxw7qhHAXpGrDsiOx2YzIbICLDurYPxRSnWPgjMjM+HYAoln/hFRtWDaCDWZE5pXPtw/oWF4Fqc4xcEZkVkHzD+iYfcMBB2aX2JnNC899D+iY3QVSnWPgjMjc1/d+o2P2J984MLvczux0RcTj3+iYvQxSnWPgjMis9a/9RsfsYd84MLvQzuw0RUTWNzpmJ0CqcwycEZldy3f265i9cb8Ds8famc3ezoL9OmaX7ndgdsjO7DSe/+/XMbvrfgdml9qZzcpk3z4dsz/d58DsAjuzecHhiX06Zi/f58DsYkdm/3SfjtkFkOq8eMwLarXTJ99s9XBa79Ox/Lu9XsfFY/bpGZ1ppedlANTsf4NUh8VjXslkdGbPvmyvjv3XQKrD4jFvIWd0Zl3eZa9OCJmQ6rCOz0vIjM7s5X+wRyeKzXviimKGXRTc+xfu0Yli6p64osi3i4IjF3326ETReY+3MVsqCJ05cPSPr3WieP/ruKIYaRcFx67v+1onivlfxxVF0C4KNq4FX+tEce7X3sZsqSB05ujdd7t1ovhid1xRFNtFkczrnwCoWf/cHVcU5XZRsAW4ZrdOFEN2exuz54vQmcPXmbt1oji8K64oQnZR8KmGzbt0onhiV1xRlNhFwXu+pu7SiWL0rvrOJm8y4g135gD2mbt0Mmizy9u4DXcenv9+pZ3/fsXMt+8/DfH+U4uLf+9XOq7P+6q+i8+77LR7w0d8pWN3X8KTo9llGdaf20j5SsfnfTsd+TxSf1TipZ06Pj+505HPhfpNxzfv1PF57E5HPo9mPlsUTa+dOj532unI5yLmsyVA/Y8vdXx+/0tHPo9lPlt2sDw=
*/