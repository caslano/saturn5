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
b7ZmEW/YBY7FZGGO2H5gJeboSO7/ON8hYp7HnMAkPhFrpWEmYkowFZh9mKefiHybFjkiR+SIHJEjckSOyPGd6f8Xz5PV/05d//8jxxp/++V97GaZH7wKs/dsexAYvGYTtw+5HluqzHdtVNest9oSsxGYLEIsxBjmDAnfvAZbiqx/tE+5T7eSCSeNOeNzMab5RMJxzg/Kum/muUTtV88PMpllnkvEb/hrfolf/T0Dc8XKfEw+f1KHeTvTWkfutdr0GvKSzuB15EmPee0upS8Ztd0/fr8wPXjdrpclQgzglfslmOH4SdtuWreL+4a5blfa9vDX7UrbHv66XeLXuWcdkTKWI37DL0f8mtZu0zqP+cp9LHMdUe49CvWc7+XKTzdmeGO1XsZ4ZYe2rgobO1il7KK0zHwqumE2K+ugF3kq62PJnnck0iwzThlpKd96bJV6YgtmN2EeMcpI8bza6onn1TWXh1VPHDHLkNQTHDfb7rNPWk8cqYN84dcpB1KnGOULv8Y6xawjY5RF4z4f+DXXKZ+lMnd0inVKuPJRvVaayIehnmlhqGdm3ixrQkk9M1lkqLvo8F8rMlSB2Xk2xL9ThsryytX2lKV5ZWV5ufwsLs0tKMouzyvLHDM6vTCkXF2vwtlkdUAWxmLyuUuZWa64Z+3tz2PKfZZ1BuH0RqaGmeVKhxOv16xdbpIp/Lm/K1qRmVNQbpIp/IZfZ+HXKCdfICNfnqKcONse2b9E1n9dLjIi33BIWkK1OymVfnmY4ZKHwfVdfQ+Rh4zKOshDSeh6Zlpl+P0R7lmbPDCJGF5/JKMyPHnIqAxfHjIqw5eHjMr/fHl43ikPokfUxXv69ExC6e1sKPJgv+TqBx494/6Xn97RO6nVsb4/fDC0Xo1ZX+X06Z+Y9abqrh9l1oMKpUdUdz2luuoXmfWaQumD1V3/52PVdki/W+qPLEwjNf/kP5bLfNRK2FTmtbrIvNZZsELmz9bCPvASyHwjFzFPKu6TZF7rArgBzpH5rQKZv1oq81dXif+P4Sbdj8RC4tVQ3dd/3CB6PdtgK5kHbyfz2x1kPnqAzEefC2+Fs+BtMo9XBUtknrxcrlsi8+WrZL78ErGXfJK+BHE15NNsS/QVJJ/mSj59T/KpXPIpS/IpW/IpB050rA2ZK/mUJ/mUL/lUJPlUBrfAcp1P0nbBaw35NETiNUziNVziM1LmO6fBXqLv1C+wX63YTxV9p5lwAsyBE2ExnCL6ThfACvEv+UTdGVqeUiQ+LSU+rSSfWku8+ks+tZV8aif51EHyqb/kUyeJZ2fJpy6ST+mST+eIPPWP7OP6L9nDlflG5h3/PXu41mW+8HTs3+peZ/LwYb7dxiQ+GWv1wSx+MjKfFzkiR+SIHJEjckSOyBE5IkfkiBx1Ob6T+f/CJYuVAsBpmP//m2P+f4dH9jiRud92mIvSec90WeAdPPfmzbt6AZ+Zu6RE5vUmqnfkODi+l92prmkl32ZLGITc0vI537WLvcexx1CBXnPkgHKL0WumNGkW/jtrO05JOk7Y6ffRBUFzmYdF5wE3/V3AHHtfQ2Oa80vz8sxpbgFfUNcUSZoDYZST5unB85i1pPm4cpup7vGwf22f8jJHvn6l3Mf6v0mXPDkg88QNkuo2X3ySPNLfjR/yyfc6kkfXYeamE7PLVR45M6gob1mNORi9Z+MS5X8LJcoMOOZKjGH+RcL16HzW+yhKHmxR7uXIp9cqxgTyYpfMbxAQrFteOOY4VNpHiHysEwE7Qy5qgbkJv2lXBNK+bPLw0ZkLspfm2blgZ8KS8jz1hLrzQX/X3Udd28xqbE6/hO2puT5QmHFPl7hvauL3nMlCXV2Fv7Ln1II=
*/