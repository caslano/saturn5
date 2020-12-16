/*!
@file
Defines `boost::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_HPP

#include <boost/hana/detail/nested_than_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_than_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(hana::flip(Algorithm{}), static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_HPP

/* nested_than.hpp
burrozLuQN7pThQahGJQdKO6prJW27B7gJvlNGcGcKJ/qMYajm7eh4GfC///fnRe9QjT5bwioUX1+q0IjvrOxeyM86fCpjxOY+8xGntPUB96ku3b35Nnoazv5crpLJTyPcvyZcQ4f57KWky+hBcoz4v4z89mx9IYfpng5hx1MbsLhjZg8zqOhzJ6nZeguf1VPrfTGl/ndHc5OoMxYkXQxia2onyzbnLE3FLhDKYLq1G2b38CgFpuIa/JF3LXU3m1V7NrqteZjDUbXOPhTgrzI74p7MEfK/ERa+U/kX7fYm1ykGiTdyjP29Qmf6Y877I8J9H31tJ7ANfjgGU+/WiyW4tiSFunvwjf2/uuTpYN9fV5ev6rgkHPfV0YVWkNN3bhbyPcY84pcub2AfLztfBit616cwN0n7WB7NqHvrZqiuNOivur0L6jKwG2c2ppvUWTrbNTyBObH0u4bAIxNJY/CvRVZgeXdw2QTdH1+Nitl/7dxoFs3jH+9n/4xoX+ZclErNnUwAKM7DOLrHvnsIUvJVz6Qf89J+Do1gNw9gxAw1XsHcfY6jKi7cuuUVcMXPg/3TrkDX9LW6Nh+R64KbBgchpobfsvVretNnKv2zCCvh1tmd9mWkjCTfs4Ybqvs2F+wzkRj9HEY58N80g1Jlo0HwklXmXEK1GaV/vCxuQeKfcX0RMpeyW4ONqO3/KwZyd2CNk9ue2b8l7IqLBqU72xzmsYqFVf9O7ij0W6ht25H4d0rcMeUhC8AvDp5i5qHmdvtJ4fH2ZnbyP0U9YHr9XacG+wBecSsSY3H0uTfjcN++3p7mKNvhnwim5zpqdTmR0Phf12vDKsP9yOh4lHVam+xWxSgDmya/KJQt7qsF/eSVRWDZMX49B+Hyvmjy9Q/r1p/bAV5d+a8pe7LU5llGtJtyWa2vCG/bifds5W/OuI/0CJ/jjV7Y/D2DjmDlPIvVs0/B5TjaNgwLF3JbXUh4092i483M84mIYTSTwTknDUwKyF7J5pGtWlWf5ObVt7rDWZbEk1JjsSOD1jP1dbDGn1cxRr16NFu86gdt0xrNt1J2qzncPeXbdauusGUd6bRjper3TM7l4p2Eyt49V6PtXz0C5MNzUbee9M6WYPdq4yO+yNp3oxnnYN4yPG025Ul93FWBglfKp7EN1cNha2Mfe0zHqiXM+HkDFjfBB7uXXr0t7gtPEHe3uZvcMjW7MUuyf0JTf/kGN0+WWmy5Dnn25ckcXkb3QpwHycXMDs0b5Cf/PC+Aj9RUkvDeFSPsvSb55U/qYw8xHRviIG2GYhbi/gqaXy5nvtFepl/oS4aMf9SN402aSFlL8lvOGz6ZH8vrQqvzXsld/G+l+70N9XwvgI/SVInmRJe64Wf/pA38jCIFaOS5geFjM5lgg5lobxEXLsT3IcUEqOEbzVUTwOFG3wNTGvHERlpYiutYRNPlH7au1duwrkCbF53tpgdi5lfqu+i42F2o04q7uW7UGvZTrtFfVKU716yC4uo3otJ7ppPv+DG63V8Xzu+qYdt4MZ39iNJRIpTeNeJzIiCzC3gxNZP1wpZO0jWatJ1n6SdSC8wTtbg+nV2ZXeeknAULrZk1dp27Ta3qGz53aADQDI7jav8tVVxVTN50CgCjAJcLY+QtuX86IvF8L4iL48RHVbHd7wW92Ne1eE8+DwiPa/epGciDXG29kSuhjWnBET75P+R2vmdYBPF2+yvg7YLMddgWRQdZc6QffYDmNtNvcznq3PLKk/n7roXSw/587rUKbMz18h7uWFlN9lKO3U0579CN8ao/R9KT4HjQGvMM1B6j8gzjepfx3F1gKbWv8Ufxunn16YsXCM23Z92R7amzebN4k=
*/