/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNMENT_CONSTANT_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNMENT_CONSTANT_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t N>
struct is_alignment_constant
    : integral_constant<bool, (N > 0) && ((N & (N - 1)) == 0)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* is_alignment_constant.hpp
C4EQNHusSRKqHS0/rqqNBW9f11bbjb1+PnUttM1SjEb32zlG/p4AAwpAhUeC1bHCVVySibFiY/EG5I9QHKmJRvvqavyC7/usE9vjynNsh7PrnczeGlbsoMsr8G6mkQExRpud2D7RKdHO9jjVVNdRftxFO3oky1cOdkCy5cbrv+AHuUNFdZCcX+ruVIYUC7mZp8YcpO2BMloMlojSV9Abf8F3nnoLD+k+dmZVo0Q2h9HsA6z9CwZ4BPUiIgKdj+am7oJHNUwmfsnuXG402jAEeo4qoJ/vBArDJPMaUC7yY1IV6WJzjUbfc4WGSkbfTJ6lrojWoMWPIX5ma9NeBXis0sMrx9B0PNzxPgkWmE7YhdVvg/HUy+TGlZCgMyc7xObgAxCvNACiAJ4bBqrSCdvwwkkxlSyln2FSYyUO2Vv4gBW0uFw+P5PL07V3wKKXR3FExkPGRlPnsyudDEWtsoucxRLTuCgw1loooHKyK5wMj1tlP3YWexhZ8HQMTpZRccW0B6bzWuxozx3oc/e3dxZw8gPfwgzIaJvF0GtmYU5lVHIx/Q0uP1pX8/p9e80x21mPgtQX0ertNWxLkBwKSWSsw98F+PTP0MXIFxqhLd+BmBR4k6EyejUAU4fJsDNFnx5czZSFyqTyNCukykNlAgl+huIwZPJDPfGh4vTPkEZd6ggPxoRn5UFrt0YA4QhI7RWBF8oRj87Dax9CSP4i
*/