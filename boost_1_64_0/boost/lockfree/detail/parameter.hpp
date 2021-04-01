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
i87Awsqo4gn1YEK35h1lTRAjlU25ZrCpEG3EE1B+bn1f3HlT87JL/phNCHh4y1FnEilddKHtWdMaxbXeb6X7g3BteYxdjXHXA7bIuREla5/tUOlcUZvAiU8s5aStyCYGl5Bihx02+ds5Z/8GK4InYeEqU7901aVscAyG55vDpodrc/0S8+TbxjwbpabPlWFQNoqhs5mTNmiU5H2HPTSAR2YshXd26JGB60ijorB6AToreFHiWeyTdTEAaA2jH6gYrhFBt9OA6ZM1pY4u/h/cu6xFFVLN1XJn9oIL9jumdqEDyzntSicoS4Ic3wyd7cCjhtlqCUgCoAAjYVlGmkcrYSv/mIqJ59JFIfVXjEiJd2+25O97YWjlpAKOMSz2vHBCYbW5Z1P6Fe7/pdYyhyiNI9A24Rd2woGVlsK+IQsBIf51PjbhaUscEkQztwMmMrJdTjr1C362Pavo3+4bv0FvoVCz4LlEGTh/TFSEpuoWjscSgXx10DjhZe2nImKBPaNoriuRL/e40a3ceCdIjNHQ81g6fcMC4JoopcqGyUwwkPgg1637CrzSR9diNQ==
*/