/*!
@file
Forward declares `boost::hana::sort`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SORT_HPP
#define BOOST_HANA_FWD_SORT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Sort a sequence, optionally based on a custom `predicate`.
    //! @ingroup group-Sequence
    //!
    //! Given a Sequence and an optional predicate (by default `less`), `sort`
    //! returns a new sequence containing the same elements as the original,
    //! except they are ordered in such a way that if `x` comes before `y` in
    //! the sequence, then either `predicate(x, y)` is true, or both
    //! `predicate(x, y)` and `predicate(y, x)` are false.
    //!
    //! Also note that the sort is guaranteed to be stable. Hence, if `x`
    //! comes before `y` in the original sequence and both `predicate(x, y)`
    //! and `predicate(y, x)` are false, then `x` will come before `y` in the
    //! resulting sequence.
    //!
    //! If no predicate is provided, the elements in the sequence must all be
    //! compile-time `Orderable`.
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S(T)`, a boolean `IntegralConstant` `Bool` and a
    //! binary predicate \f$ T \times T \to Bool \f$, `sort` has the following
    //! signatures. For the variant with a provided predicate,
    //! \f[
    //!     \mathtt{sort} : S(T) \times (T \times T \to Bool) \to S(T)
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! `Orderable`. The signature is then
    //! \f[
    //!     \mathtt{sort} : S(T) \to S(T)
    //! \f]
    //!
    //! @param xs
    //! The sequence to sort.
    //!
    //! @param predicate
    //! A function called as `predicate(x, y)` for two elements `x` and `y` of
    //! the sequence, and returning a boolean `IntegralConstant` representing
    //! whether `x` is to be considered _less_ than `y`, i.e. whether `x` should
    //! appear _before_ `y` in the resulting sequence. More specifically,
    //! `predicate` must define a [strict weak ordering][1] on the elements
    //! of the sequence. When the predicate is not specified, this defaults
    //! to `less`. In the current version of the library, the predicate has
    //! to return an `IntegralConstant` holding a value convertible to a `bool`.
    //!
    //!
    //! Syntactic sugar (`sort.by`)
    //! ---------------------------
    //! `sort` can be called in a third way, which provides a nice syntax
    //! especially when working with the `ordering` combinator:
    //! @code
    //!     sort.by(predicate, xs) == sort(xs, predicate)
    //!     sort.by(predicate) == sort(-, predicate)
    //! @endcode
    //!
    //! where `sort(-, predicate)` denotes the partial application of
    //! `sort` to `predicate`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/sort.cpp
    //!
    //! [1]: http://en.wikipedia.org/wiki/Strict_weak_ordering
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto sort = [](auto&& xs[, auto&& predicate]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct sort_impl : sort_impl<S, when<true>> { };

    struct sort_t : detail::nested_by<sort_t> {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr auto operator()(Xs&& xs, Predicate&& pred) const;
    };

    constexpr sort_t sort{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SORT_HPP

/* sort.hpp
ZCm9TvI2j9B1YERAyIEUv2J0to7R0WEjhzyYJIIhRCz06SupWtAS+vQpnj+wQn27DSBOsHBcVSUOK3uXmNU2MymHgY873tG73x8JH2XiSB71vhPHCE0ojzBF0oGwMSj6DNDAkzNtkKuh6DAvJ/TwmnShPSgmXqPX7hb69JE03TtFfvZOn05VNdFnaokXYuCryvB5qTwU+bOouGTpBgXFws7NYGHclIm/HSPSyzAnUXNeTHMD4qk+neYr8cokmqDk7PTC5I7ZSZ/DoF/OkUKEDHIBsXkSLxWJp+orPFfwFzx5iDR4AuJLkzVl5tnNJ4nr8nEaoqiWwx9LOCjAL57H7BXaj1fMopsl99zT/M4HVBbkq/kkhrHG4EvsZ1XXQKQ9uThd/5kl7RfFVCCZ5Xe3B8T28QT//jYimgDt+BB/xjvNjQLT9BSIiHwqWf7cazfUOMRLNjByk6nVsyP3OihkJ4c4aGAhQyZsS1leHC4NeZ6CvOIT4TDY7kFyBRO+RwaaOdAgA5UEoHAGxCsoMyBGGOWI0yyNBCIJU82VYQ9rM6ucOrk9Hk6rEP6k98etpZFECtKlcrqxyYj7wuYKkZn0rmgdETZxErczSfQhXoxUCGNHUAWCePwnOpCb4GjMODIpKe1W6CND2ExRovDy5MJoCMKD1Ol/2y+Zmw1hT/Ma3n1hJU7d2nse738Z2Xk//JyVOHwHwfnomvPlvvgFsP9lO2DtPIYlZKu9QvpdoIXktmRdZX73QChraOf2HFja/o0l0POaAuKrVq1zDais0mMbtVgIar6Jjp6QZ7KogtgQFMPFsm2EXxrdPchas3RiXghx+3SReMYfCH3Y/jM+ieinEYD8CFDKADqLCcm47+uWPU0URSZkt5hhJC9t1AqMms0atW1A5OmfVS8MGyYcv0uRwuyH0Dtk8C2jjldPN0LwMlmCEhAFSSjqPkPbuMeSmgfr49uS3wwLchBzC/cuTjPAl1sBOdFxHvl0kU7oS/SvBP2Bx84VA6gTXjaC+cGldDQE0s0FMoHIxVmMyLMZVi7YT+6H/2UmwzdtZTuRkfMLxF6REefKY9JPNWuQm9nTo2lDyJ7Krp264EC4RTuFoYQYVoukqgyNujya30JPGktI7Ew6NmJjtThew5FtI+kxAiSmDt4sLWUg+UjRVxwwISVJt2pFDuXEJIddlGgOqff8gowvZDvNC7tILMtxfrElGV4StnYK/20yPDts6RT+jWS4B4CUhy0hqnBApI3SScou1Zo5TXzeSTbGNPYpje/FYRlrHdz/IQglPLlp3Z7OGPFQHRJjpUGQbiqHhfRoqZysbVxyLckOJqBlaoZD5YMhHrvWSYhnrbGYadO9dVTcaOM5qSrWD1VysCUCnr2plHb+81U8HymHlX1ByIvd0Gb8+vW2BAFLpELd+V9Ih/t6aGgRb31YjjJycGi43ahWuaFvcAq/sZ05Hnm6+ZvF6cbqD7MpVXEGrwtK/KJkOM+lOjv4daTDzHYLMcjVV9+6Bmx/QPxltD5XLAuIVACS3Hq4YajOqTzfOgzLTLw4kLPI9XB4Cet5A+LwEfrGhQwmiidJoCtQxpiwJVAhrructTRYMeTTAx+r+Y4KsPxlwcQ26BsrkGW5+KTUNYY+T4PDGjlZfhKT5c5LNYn/hCp3dZ8yMUmmm7AYItOAuFb6eBn6SjuDra7Xd/aKgZr+ssodW+xhJqv1iWcu9E/yG8u9pL9iTc4WMjzgVTqJgwwfkgoO13CDYdnloQf16qKyt6K6/2C04iiVSjABQfHQv3QGn3pvRVBczpZNo492Wk4+Qf1xmcdQ0z/0w2Ru81u+QvTgAz1kBlFugy8jcTeIYQJQAvuJuz0=
*/