/*!
@file
Forward declares `boost::hana::take_front` and `boost::hana::take_front_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_FRONT_HPP
#define BOOST_HANA_FWD_TAKE_FRONT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first `n` elements of a sequence, or the whole sequence
    //! if the sequence has less than `n` elements.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` `xs` and an `IntegralConstant` `n`, `take_front(xs, n)`
    //! is a new sequence containing the first `n` elements of `xs`, in the
    //! same order. If `length(xs) <= n`, the whole sequence is returned and
    //! no error is triggered.
    //!
    //!
    //! @param xs
    //! The sequence to take the elements from.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to keep in the resulting sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_front.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_front = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_front_impl : take_front_impl<S, when<true>> { };

    struct take_front_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr take_front_t take_front{};
#endif

    //! Equivalent to `take_front`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_front_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto take_front_c = [](auto&& xs) {
        return hana::take_front(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct take_front_c_t;

    template <std::size_t n>
    constexpr take_front_c_t<n> take_front_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_FRONT_HPP

/* take_front.hpp
Kg8vxAMv6Yedd0uHW9zOQmiH0je1da68mG4a3fPUf9tP17d2Jf+JN8xcFZ2HXY9/DGaKtRfrWtbFpTRsfirtH7mtr4UTLAw8G+EKiPdXG1u3r9KmMHLKV7fTx8U2XSLDQrsAcUWHL+n9Wqq0HNmFSIblyGGh94wgl/aeiSDVOEH6I3VnUYgPv9mXKx1OEfwNywJ2cvdnVRqQ4pNOJ5wek9yYuvBVD1w6pQh04h16A773a6UwOX+JLiQX+dIoAfktgh+YL56Fh9+q5OnRa+DNNfjgr42gFyu/fTsMv0kyOue08ZdG9HHwroa/EvaKlC61TZ6JScZN+vCxfebxsVr7BTF5lcq0Xg2Cr+sx82shJ/yVGgHnaKgawvBRVUAsMjAns7nMb1Yrc5l5AX3bQpsOf6jIpCrcjGOddFGwhiNWi8t/SzLS3yFfPhb6lXR4xOL1sst3X8T3GxzgjLSq7AClr33NQcXB7rIW/CmcOdjxwXLKs1Cdwg7lO3x+5gFN0Wq9VqDGLVb+wZggLpcSZxxF/vYWri2tf++20fGWbpM9Ggaq9+v4JzfeOwWfkDC6ysVM+Rx5pgG+n+k65qX4v/J3rPY5S0T/oe1zOo8fbJ9TPvdDl2A0LEwkfuEl5ydqyWlTS84c6p7iqbtodGn6apUHP/SXYWLHL9Xiciq8+lI1QfPDIlJ/qqWeGsS8T1Zwxf038gTaZ2NoklR+kk9vUPLX/VJN16vDuGl54kbGs6nf0ZjjrWzqF3112jq9r0pbC5RYtfju0oSKDqc2F5wZULiUeJWU3o/fPWeYDHuOChv5fvxqD+wmUOpgVfEyCB+lAGGtY7VOdFH/SiYafqVkMoMWmwBdJXLepYYToiNZeFWukkyZgw4lSTyFNehGlDJ6Looln94YlbsntDklMb5moJe+GOOUxkN5hST91jv0q6Z1mxK3hi7qDP0o0bk52h0yGgmmPu7TEh/pB7Nzy58ANS7xGBrkUPY6LJjy+eEe/jjpwyY7bMdksiOR/hSkr6E5SPpzIWXQXmLrTuU8SpAHfZAHffQ8PLRPjU5y6unD9Itmgsio2BItsZAoqcSqFTujJTpfm9txTNVH4ys8gWmiK2r3LedCD9zvBCmrIrJDgwzoZmdAtEDDg2ZwkiH3RIbRjoCNbe9zRiwEBFmuR8sJv5+BbnTFzXqPm21HSAeXxXT0LfNh8jcfLX/KOjn7jas4+6NuXDg/NlyCiYQNuNl//CaIlC/XVbBxtkcJXjE3ND/NgVtoNfhobJV/+Np+/XHfyCVBYVFQJDI5KPY8oUMlkYlBIST01TvRkJFxePZPh28j+AtB0aPDtxM8KihW6vAdBKeHyDh07y+oU1ztVOZOaALTLnBOTdha+z3+5Ybl8OFZGF2lj/HoklaiOI6TeZbmndE0ldAXUx3IZCq9H/6CLNe4J4xyfTUospNp/2JQuJNpPznUpnINhznLZx81BnRn9GqrQa7BPJ0omSc76VMwMfb59aAObxIr6dOeljTHgtY0RyVq+hp8f4u/FJPFkor/6F/zU/+5H+2VHhYorhZT9ttGJUyXfVM3XbYq9djst0Uk192uGxp7OGUtJfwR00xNTjOo0lzpQpoLho1zIMUNSHGSaVyAUoyxObQNA1M8nfnEs7CE0bOi5uQEh7R/KtbQqoO6vR13Co7CYJRsz2b93Oy0uqCw32UYJRP3LaR1KUhP4Yiih7kPSkO0Cfs59ODRlZZ4bp14FUxeEAc6J3HA7DoIG51cELdo7ZJnPJ1kXFt846dyeeo8uqntpwbbC/ub6vpYya5B19+EzJS9MPPCZHthYWi42JAvWwsb0dk/yFrYtbceo7Uwup9yw53yfkqEtFE=
*/