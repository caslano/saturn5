#ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED
#define BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mpl_common.hpp>
#include <tuple>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<std::tuple<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

/* mpl_tuple.hpp
isBzb6X4SjTtWk30DOj71sE5nvrSJyjs4VrPgH52q/Hf6/TfeE3tm5WIgcnFYiDG4q77ZkdSeUy2jLGLqDHGvlzgHQieqM3iI228nm/drMdrCSJJTxWlVvV6KdE3xkbt0Z+TXH7/wxi+/5PmtRdTuDeJdywaLUvQX9PaOqTzen7gvWfy/ucxPJe+HcL9Y6jeMuejfx5LHbN1mbhbHy4Cx5bNY3hseWkMjQdaX6z3o023d7sPeQBeNkCv47+FcGSMnIMuCBE7rY8IzGDGmOU9SvLekXDMcXti/HCK6JXB40fCWJTxSPykjqXzi5eEYL7+iabRe7L7cJ/b5yD6OX62vBjeLpf3ukCoh1k5tvN+eL4pQN43vmys/2b8fWhQY0LDVusTrEv1MVZtpXW0LscNOd+djfE4H/Pd3KD5rof6WfktttvFYNdqMTj592KwqfGob7G1Ix4vlQHNw7+HxXpI3GXVBsp+np6b7HxmMlzdZ2lc/xhnXP+AMHZc5/OJ6rVOYStFErQjSr9BTNZ3yLCO8QyRZxzPJ5dAWDnO3vkNBf+ONr8mOrxDrNSW2VLlvvNQUWiTe3qm3lbRe4Z8rt7jKD4l0f+dWrt83pfqaCeCjX8HP23jZPtDHRVrWPSo+9fQr2C+EgGdi/CqOhVp8B+Kn8g0ypf0r6ZeerpZj9TUM7c90E+Aeaegr8DUYYZ65ranXB9gbeCieTzdu22j
*/