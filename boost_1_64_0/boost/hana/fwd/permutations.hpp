/*!
@file
Forward declares `boost::hana::permutations`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PERMUTATIONS_HPP
#define BOOST_HANA_FWD_PERMUTATIONS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return a sequence of all the permutations of the given sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `permutations(xs)` is a sequence whose elements are
    //! permutations of the original sequence `xs`. The permutations are not
    //! guaranteed to be in any specific order. Also note that the number
    //! of permutations grows very rapidly as the length of the original
    //! sequence increases. The growth rate is `O(length(xs)!)`; with a
    //! sequence `xs` of length only 8, `permutations(xs)` contains over
    //! 40 000 elements!
    //!
    //!
    //! Example
    //! -------
    //! @include example/permutations.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto permutations = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct permutations_impl : permutations_impl<S, when<true>> { };

    struct permutations_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr permutations_t permutations{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PERMUTATIONS_HPP

/* permutations.hpp
90tmlPqLRWk54y5LF8ZufurZEduV9JO7b/YRtDDPNliwWuPevy59u3KXT3tRSUqs1egxotvLK8rU1kpcJ8UwsuutjeOk66q+kV7gsTrnBvOwc3JiRviGUkRwIl+x8MeidYpuzN7gpR6p4s9S8cHpyh2vWOyqVoEX+30q5ZFmyhFpawu7RHy2gYXJNWNSBo6xnrgJIZaBySduWrQ/WnlK2trukfxvc/fNSqcRY9yFfPKsXXzxOwd5pSuvau0Ts+E+MWaGefAZ2v1P2Qpp+H9dY5z3kIE9i6sh+eiCSJIFoGBkuJQD+9Ie2299OXf/7FQiIPh48TckB+Z+wY5J1N8Xy0XijGV9iselrbXseXNZoSVtbT4/JOMhmR6sMMV6RfM7jqTIcDqHJXffnN6gR0NI2LwIsW7EUdSXq2X/fgrxpSLzFnOsjQWmqUBmFK4VSa/y8CA5W/nh3a1p+mxTnzXn73sz2B7b1jmyKJ4OF2P3K+lRNNMm0sZzg9jbygy8Z2xn3IzM/US8ASgj/mSk9BYnI8X2CTnb3yckzz/LbEh8z2rx7mpoqz0nU9mmq6JZegZeYz5l0qWMqi3rgvCDuSWap1SSM0dvn9gCY1Z0bobYBMnvE+uN4bcoIzo3Xayolrr63PT2p5a1Dtb/Q4b/vduvzpuEJ7helYkxpehiPpiohP6e7GfNEyWwMx3d+zCBpmel0AYxOV59Phf/gnEKangJb+IpLhZNN5p7ZXASXLQUNm1KvzhosCO3OG3s1lIxdRLXGbDP1ZbT6NA/zLsjf4Zx4Zq5nJzEg/bbZCMOmzzA/n6RzEOLk5U/rhM576Am1JIsMlOFyYX0RL94fxy5V2RQl4DUgg554hRDC6i6D6D50ohuAXsAzT1hpNo43ku7SRbIG8dvIl3mcrrlZBb6vnI/cYjITdJO7KAqkvAsRZpxKMLczJd23TkIMoyMfjH1EjP8FIRr96hCeH95Jhqm3ZsQdOpSqWgb8P8KTz1eVkQZx8dgfYBgX8Aim8EKur8o1pKHW7bkLiT3i3qveWJkFrmf/FgiVN9gIPQHCoZ/0EfK4zeg4cpFw9Bm02kqtDAjqTJT26Cay8cAsvEKvDSkknmp20YySupF9lJwepmfePz2cfQ3t0RyrANrF1hGhdBButDCzCQcgHQJiB4uyixGv9MrMiNFWVhfxZh6g988XYI3+1j8YsyxqIY8wiBC9dxNDgZMfTrko3y1yS48m75yHKCQYVX7QNXZWB/uPVWSb89CVzFaKHqONVa+J5TJ+rtYlysWy1aYusDCPtrvzabfHtf0c2WvKxZvjDGhHI5ptlOfWi/7fy2Mty+MonsTpSP9JBy0xkfYdp9wANNJ6qOhN6KshTqtZu/XbjbsH7OlQv4aT6ArlP/bvHNo71vAI97X1KafYddKQYVFZIDqbYKapUANMUAttvBWcLmZAPV4b4l5PPUURDGt2LeSY2+PGLELT9IyFVBeuFBwfz9Lwj3VIo+x1eUY78rthp1jPzbrMU+lf9JIv5/SzaZddOnt76I7K7aLrn/8Lrq+8bvojjJ20XXVPHTGGm2bZxe/phvxR7obQa6Qv1sGNi/oN5p8HpxXKr4crhbmLqczNCzaPmSCwBa9hisheWHA4gtPyxKzehm8HcyThz27IqOgtzEjlorp00zbBfZsFVljjBjD1dqZUs8H+PJ8Fj4u8c4CnsdPBmTz1OzTef7q/ccw6A/8yPMox6LW7BJCPJ3p95XCUtasfKUgg/6cpNrPx/9MofWfGbFJDllDi1lOv35MUpJ5/t+dZPbauZLP/1uhzv9bIHe+XsFnmxBlmstRNtuRfMIvF/LCczPC09PFs36WU41FWYZvdVc=
*/