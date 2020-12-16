/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  exclusive_scan.hpp
/// \brief ???
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP
#define BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator exclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, T init, BinaryOperation bOp)
{
    if (first != last)
    {
        T saved = init;
        do
        {
            init = bOp(init, *first);
            *result = saved;
            saved = init;
            ++result;
        } while (++first != last);
    }
    return result;
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator exclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, T init)
{
	typedef typename std::iterator_traits<InputIterator>::value_type VT;
    return boost::algorithm::exclusive_scan(first, last, result, init, std::plus<VT>());
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP

/* exclusive_scan.hpp
IpSqcrub5ppxK+QOsXWb+pB2wOmdkoZwW3Hee+x18VX97Yx+wSA7KhzwEC2PV9Ln/KNDO5GzcPAJV0XwWRuMbBKzvCNLjAU27iFjgf39irAF9psHxQJ7zgp9A+Y/xY45gf3iO0+E7ReVhx/mMzkRPTy0eNXOByrR6rutyS5lgqjTmXWI7gw75R8hACtTDLWGxwbhMVxEZ0fBNH4ucZ9KufBP2s65Xuk0mrbhoLXCDsWNqmewb3ACSau3e/i4c0fd5diCMwUO13nL14uJBN8jEhwuSPBC9LlbfDqxKp7GUJI/qYvjcPpUXLkZRfBAgzLJZwzKwlfCBmU40klC8CGRRgOaGd51cFMgsByGlYXeol9kkFoZL9s87ltxTKKYQc1uWua3Nx2vzcDyJOZLxeP6VgVTXJK3Ko6wTeAj3EsudHKy5dsE2knCpOXeB5KpV87CH7fN+Z7SdQoz4EtZNuNjmDMUx0MaMVURNQ9/hSBanxh7XzAmxteyMQadXw4bg/dlMTESXv5lJ0bptnKa/TZHjffq7lTPz7xPrp/XFfyVuxXAGKvCDuxArfqzVMg0FOcrmG3xfF0Xb3vDAqGlO23KdpJdy12aXcufyVRlJU7mjisX3hc6lhP+0qrV1FmoiB2ovdHfjMpQh0J17CUpqYJcurQ1XpcKd/nyMeGvQfhnuxzlm/pn81xkhE2rFUgUhCGxiOcv6tExgTM39oEkcXQ+nr4YHPbjtv2TVHGBSK5H422lh/ij8SWgpvvwyPi/s5/xT7a9McCMQoR/3TjyElcAUs7yt9jbsN5QXZYtJEEhyFwC4hqLStiLYnj8AwcCHGp/XWo1dssEj3gJAxne80nRj9WAK5xiNDhWGAhN9uoN/kF5DecRwIfWDqSCJXo6ruJN2CUvayxAjxPA3UF2o4BjZRfv0ZW2LcJxCi95nPgrXB/82T/6/uy5v+jbDiX3JV2BKe6tJ+M9DH4IG6rNpUJ36IXibvzydN1xIZEdB/9XRNRx5cn7DJ3fJWTjNOlWNiRQjhUxX7+CxqS3IMLLypLFFdLzsZpPVTrNEvqf2jt4UrDVgHDv9zbtkoreJSzIjOvGkUGs5BvLDFXieqXtxNBCvZoF0ipTHH+FCEX+gPRJ6Y8yBp0JgyECg9fmhGEwtnYaeQiS+drZIDtPAeW0GUKALECWq2AICrG/lnyrqFl3zyvsZWY+K4AvC6unm6hnwz0i6zfIIiaagqxcUgmo40VGjAi1Wxv761rEaD9R9emlD2tCYb0QHthwRlk4l5d5OrhIo2GaikEhtgCN+qXP8pjXJdNAl/BBhJK1h142P0TL2EasZMKAryW1eO3wJ07Q/KDJevnp3DD5Bi42yAnFP0p4iHu6fNfaofG2K09NFmOOhG6kAldkkZCMhFwk5Cq1wPCEN/Ph3x/dwvfHlojPGd/vqH9O/37i5JP4XLj/UHbUq1vzfPaQ7qo3X97r9l4Iw7J8bzfyD15CNh+5V+d7L8iH1OccyWPGq/0SM+2yhvR2yeDRg3aCj2tiwGzavJdR6d0ojajzIX6L8JU2MOrejraqB/LvkTjEb5d50pNLoVfpY95udZflyZtR+kW8hhWwlZI7QxRq46kNK+QFVJXJTIvAPeae7LwOTzF4amS1T9DCXoRBWRU9Wcmw4INUYtUJKKcFPD1DKn+OK0t21yYgusr1pPKOr0uRyhchmaZ6vkhylvVgN8H5vXqi/fTJnJEuYvdYVituFNaVWC/xAeIb91AnqP4K4k7cSedpGfHcO5PMUvnbQly5t1i4Fv/HCPpMbFcCyjdcpI8uFsJMNXJdXidX0VMqrxK5UrEQNztDiSxs4B7TVqoa9mY2jdZ1Np/dxO8=
*/