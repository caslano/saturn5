/*!
@file
Defines `boost::hana::not_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NOT_EQUAL_HPP
#define BOOST_HANA_NOT_EQUAL_HPP

#include <boost/hana/fwd/not_equal.hpp>

#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_to.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto not_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using NotEqual = not_equal_impl<T, U>;
        return NotEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct not_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::equal(static_cast<X&&>(x),
                                          static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct not_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Comparable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_equal(hana::to<C>(static_cast<X&&>(x)),
                                   hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NOT_EQUAL_HPP

/* not_equal.hpp
ohYxD2l7Xdw34T826fQcaKary+sC766qDNwkcGEeqXA6faZOmaZEln7J++znQIiLLyrfbw/4Y7Mae4uYS1vmfNv+FdGXY7sNFyKEvkN0r/HpWQJmF6myOnZBdQFMFO58LAToUptQSRPLibJtw9nL84HAl7fwda7C1dpFbp+u8B6ffKvhkHPN7K/g9XgZOUvuKmxF/VJfNKfUxK1W/QdOhTATPDTfwnznJRokUmhwYigOv9HYilPA8CyCiD13jzw7TMIHLpTup/IbtoYI/k2mfft97QHVjVqXHA4czMWGZhQpZvWrd6vPzOSmbHF/uGT8f6eQLf9VBpMxEqOpA4DswOYVDsURbMxqPys38UHHr3lSGpKjRT6h1L8tY6mxIFqutNvgTR58sxKufO+23kyjTgH1u5WEHhVl8Lzpxs8cmCPtdteSGxOepAmqNHzPIECXDW5u0KbbrJLFvJC0ivSI93a/gYE04Y2aSM1id+GNj/HqFgupVb/27lWHzWjMGY6tHWrifs65mRGg35um65OD1H031BXJq2vBq+MHQtPEpPUr+YX/qq2b3g6+qA==
*/