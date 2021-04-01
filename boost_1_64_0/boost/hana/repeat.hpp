/*!
@file
Defines `boost::hana::repeat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPEAT_HPP
#define BOOST_HANA_REPEAT_HPP

#include <boost/hana/fwd/repeat.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename I, bool condition>
    struct repeat_impl<I, when<condition>> : default_ {
        template <typename F, std::size_t ...i>
        static constexpr void repeat_helper(F&& f, std::index_sequence<i...>) {
            using Swallow = std::size_t[];
            (void)Swallow{0, ((void)f(), i)...};
        }

        template <typename N, typename F>
        static constexpr auto apply(N const&, F&& f) {
            static_assert(N::value >= 0, "hana::repeat(n, f) requires 'n' to be non-negative");
            constexpr std::size_t n = N::value;
            repeat_helper(static_cast<F&&>(f), std::make_index_sequence<n>{});
        }
    };

    //! @cond
    template <typename N, typename F>
    constexpr void repeat_t::operator()(N const& n, F&& f) const {
        using I = typename hana::tag_of<N>::type;
        using Repeat = BOOST_HANA_DISPATCH_IF(repeat_impl<I>,
            hana::IntegralConstant<I>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::IntegralConstant<I>::value,
        "hana::repeat(n, f) requires 'n' to be an IntegralConstant");
    #endif

        return Repeat::apply(n, static_cast<F&&>(f));
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPEAT_HPP

/* repeat.hpp
PVyxvSRX2tpNFvTHtTUunZTh7S9SRaGgdZeQ2/XsS02hfHgzVYdJOsXjsyJqAhoLLOoxu4PmQ8+kCikwmJe/4xKtzd6KI4uajYAMcGPttFwUW8y+Q9sVH1XSe1gp8m/sOgUV3XiLaJ6LMsLylp+ljgtFydh059JQof8Epiwh1Z91U1sU7XplX2dcsjSOkWJyXunWD/rUkF5E4CgIm25llkn12mjKe2Ir7EzknWKQW+M3jO6P+uv7hS+lWRHoPy+tUrznvNRSLePI+xGIibPx+z/fvoWlPf52045rx3R86QUTaC/uHa/VgekslwVdIvPc737RXLphZHQpz8JzHsvowfPDTXzCFtD1+afy/PiYZzR3WIriDaP+nlTDsdjMeqZT2RC8Ck1v/7Jb/FlcnqZ+EL+soD7S1HJt/Q5yHYmM5JA+GR7S+xAxLlsYGhKWWnv+cHW4ZYUVQj4RIdGU0in5humtQ2IWMXrKnKCzPmzDgZ3qeXW0fPfnFF/2YhacDnOSjHEfRDz8ABgVzvTO5ktzCOlZYf/VUNQ4wLxj7VUFSRVuFpacAzxMzAGk9w==
*/