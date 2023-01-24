// boost lockfree
//
// Copyright (C) 2011, 2016 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_DETAIL_PARAMETER_HPP
#define BOOST_LOCKFREE_DETAIL_PARAMETER_HPP

#include <boost/lockfree/policies.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/parameter/binding.hpp>

#include <boost/mpl/void.hpp>

#include <boost/lockfree/detail/allocator_rebind_helper.hpp>


namespace boost {
namespace lockfree {
namespace detail {

namespace mpl = boost::mpl;

template <typename bound_args, typename tag_type>
struct has_arg
{
    typedef typename parameter::binding<bound_args, tag_type, mpl::void_>::type type;
    static const bool value = mpl::is_not_void_<type>::type::value;
};


template <typename bound_args>
struct extract_capacity
{
    static const bool has_capacity = has_arg<bound_args, tag::capacity>::value;

    typedef typename mpl::if_c<has_capacity,
                               typename has_arg<bound_args, tag::capacity>::type,
                               mpl::size_t< 0 >
                              >::type capacity_t;

    static const std::size_t capacity = capacity_t::value;
};


template <typename bound_args, typename T>
struct extract_allocator
{
    static const bool has_allocator = has_arg<bound_args, tag::allocator>::value;

    typedef typename mpl::if_c<has_allocator,
                               typename has_arg<bound_args, tag::allocator>::type,
                               std::allocator<T>
                              >::type allocator_arg;

    typedef typename detail::allocator_rebind_helper<allocator_arg, T>::type type;
};

template <typename bound_args, bool default_ = false>
struct extract_fixed_sized
{
    static const bool has_fixed_sized = has_arg<bound_args, tag::fixed_sized>::value;

    typedef typename mpl::if_c<has_fixed_sized,
                               typename has_arg<bound_args, tag::fixed_sized>::type,
                               mpl::bool_<default_>
                              >::type type;

    static const bool value = type::value;
};


} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_DETAIL_PARAMETER_HPP */

/* parameter.hpp
ifU2Lk/WdLwRPUE5ZZp8KDvNKNAkUNMMuttonVq1R3u64+tbHo27BSCkJQ8Ga75GF035zfG5vT2f9iA/AQ3gKllYbS9TUQLdO0ZiCGQTGe/g3yW7XDHgUPHlC7z9aVd8HEgF2eF0csfIHtzvWAPiANN8TJ5qekRSeY239lPgJnp5/sZ7t7MtnSKuy/52R4EtAjOKMn52Y2TJCnkVsL05PhbwQQpK8yA7aoB7dHh02SaJSlS/5nFeZIXchQi8ByBsoWVjG0neAvUiyrCMlN3ZN5A7KVo/6CEYKQKd8dhRthA68VoRW3Fb0VpJ9VCrEXWquB2vjdCNUKqRlhCW318hLr0XqAgi5I/3mx7KqXRGz/V531IJcfZ1QdlC30DoVFsU2G9Df6p3G3pxVl3vQok13goMsjSsEzsVyBYHSazUV3WMu354nX2PUIbjgv7cTtttll8Rdxxvlr85jC7ytY+DDh8ctNMHC7xIUk3YPTuJ/SxDS7PdbTfw8YoHS24jUgAXk6QGErkWl8g5Yw5B6iy4JARJxMxieyK9l6WeW8M/jaaU/OKpqAuwVyPK6U6cJUSNbDe84m738aXL+QMNLhq0pLzmtMZLhNgfIzjdX23cvqmq7Iw6Ev9nMUTwG/5cU7FSBxCnx3y2LbDAdcDfjRTWpR4MXdzFbCRxH3HequVILMXM91RzxHHh/moe3bBIdhLtLxJb0+06QCnKVpML
*/