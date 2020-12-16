/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOR_EACH_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOR_EACH_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/algorithm/iteration/for_each_fwd.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_for_each_fun
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit segmented_for_each_fun(Fun& f)
          : fun(f)
        {}

        Fun& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef void_ type;
            typedef mpl::true_ continue_type;

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&, Context const&, segmented_for_each_fun const& fun)
            {
                fusion::for_each(seq, fun.fun);
                return void_();
            }
        };
    };

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline void
    for_each(Sequence& seq, F& f, mpl::true_) // segmented implementation
    {
        fusion::segmented_fold_until(seq, void_(), segmented_for_each_fun<F>(f));
    }
}}}

#endif

/* segmented_for_each.hpp
0pITMmQfZnv73okpcZMyZHx37RhUoRhsiUtqWkIi60nf0xadlGVK9Fz7kSenEjVlA5Y4BNm/HzeNQQesGzGpx15dL3l7iVCL8CthMt8p/EqTt+zQMspwqcbUdIqrPf6d2D55NS1dOwalqq9AAzk1B0rc+hGq1+Ne+oQlbolZpMjTcY9tbfd31bHlp7qP7AJvbb+E53gBHfV1M+kr0Hv4kPYxQ/sM7Nd3RCn7J+aH6PbL5V5b2z9hHevm6O2zlH258kPc91HoaUu7jzbtKUofEYmH9JOIGho5oO+YmPDeI3qXrn9GK4P+mf4VtX11Aln3rPF+pYOm5/lQtau2n45vV+f+meo4FVbUHpM2rB/0jVGcSt9/pJUH/WXsfdsqaeOTyvfNuvEZMjS8X+n72VFHGPWzU7f7r6Q9XnFKXWEcF6UjdZniYcuXXQZ9V8Mqa8usWSk7hnEpXbkJNiizBZW1fQ3Hsa7/SaP9lq2vob+vNn0D2U+Y4X5Kd05GGKRvi6/2GKezrtlwv6U/J4N1zsnr6hn3mQ6rYlDuDONUuv6PnpQ7W/4UVdGej5FKuTOMS+nrhwgP6odgW/1QVb8/XdCpZn96f7rdVfX708WeanbN+9PZrpmRMpb/QikLcwnTlHtBaxyUGw3LIPH2Ox4P7lXqyb1KhvW+T+6TpO+Yoyxwu6eOS4CM0/+G5P8rhHvYRtS36rhMS50al8mdaYIHcZH7Jqd7JEc8/KzL4tiUY9yYmtZ8coxLpL7HkftT9X2Y3HNd6aIsYxTWOHUZD5Lx+PNIRH18Aqcr6frOkS7G754wLYUBXC05ncbwv5be927HlpL4aO5hk3TyX8aWkOXkpPyL9j5Sf0wpf5dxWcJc8qae6lyPS53O6e7a9zpcxrg/QcIb4xc4g/3GntbLi2kZiemWbChTPhg/N1j/zax7P6+5h7bnTyVL2WADjrx0pDXKsnndfJFzUMqHZahMVT1gknH4D0ud8xEhm3jt/sGRJ4lKLRCXWap5GpzzQvtM5Nnzg9QpzueKqr4MkVEQP/WxHs8P8G+sW3TGEffkVMfcJitKqjd4hnzknPUZMj4uIcYac+nXqX6OlLHqVc+JMm6x9lkwUJVu17KdqpvmCJ38S1Kf41Le5XuUAc7YKclm1zonJfHuxBS9fFSPzUUfVrN8v4lqDHzNI7KlX69PDWvf155Knv+LvTuBi6KKAzi+CiLdauZJiooKHkR4AaGCgicqKioqBSgoKOIKWNiJZYZlRbeVJZWldpJZaZlRWllZYpaZHVJZ2U1lZWXHb9j/HrMzswchZe18Pu/zTZqd9+bN7Ozu/P/vTQ19JvtV7DBnMsfJtu5XzSzPXBvxnX3dEvu6tvmZFkqd6ZbuU20jgnUH8OKhP9i3YXbaRrL+NlTnu7883+Bl+XzdRimhX6p/tJ8zebn5c9PpUm/Od+drfKq6v3WuEcbvdTl2mYVFer911de0I7I/P8hn6DeUS5X9+clpf2o/trg1Y7nU/K39sp+Hnu2Det48+fyUcymQ9h+mTOff/X5W2my4z+rvLzKH/yLZ7yLKEupsdli935bdrb/Par15NE2n0lZKuPI3S/3SD5rPZfVzCSWwPU7uhY3CpdRV4bQP9i8dnn8WOe9Hjs75aNb5rCjWOUcjdK5P01THlzn52P9DbEsZ1zL8F9qPco3iM1CuJcqnqRz3G1m3hjKVf98m68sxUH3WSZ+prvsV8iyCQBnP4Ielyuf4r/Z+MxcszM/24v3rfL1N1enDCPU9PP1zX3veyhhzozHL9TeW3Nsx4/pjwI3GjBuNiTYaw240VtporLrRGHOjMelGY7qNxuwbjVU3GgNuNIbdaEy30dhz78c=
*/