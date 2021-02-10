/*!
@file
Forward declares `boost::hana::min`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MIN_HPP
#define BOOST_HANA_FWD_MIN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the smallest of its arguments according to the `less` ordering.
    //! @ingroup group-Orderable
    //!
    //!
    //! @todo
    //! We can't specify the signature right now, because the tag of the
    //! returned object depends on whether `x < y` or not. If we wanted to be
    //! mathematically correct, we should probably ask that `if_(cond, x, y)`
    //! returns a common data type of `x` and `y`, and then the behavior
    //! of `min` would follow naturally. However, I'm unsure whether this
    //! is desirable because that's a big requirement.
    //!
    //!
    //! Example
    //! -------
    //! @include example/min.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto min = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct min_impl : min_impl<T, U, when<true>> { };

    struct min_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr min_t min{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MIN_HPP

/* min.hpp
Y3VybC5wYy5pblVUBQABtkgkYK1TW0/bMBR+z684KjywKbSMp1HBlK7cqlVNlQQQElLkxCeNJyfObKe0Av77jlOgTNvEC67a41rf5fizvfP544a3A++OtPumNKg6wlyrn5jbf4PT9BE2HyLdUX3HYgBbxmP6Cd5lPMJex0ifPY7dPE3fsblzjbmfgSPepW5KK94O8caqWWuxKC3sjT/Bl6Ojr7APhweHBz6cslqghNhinaFe+HDMu5WgZKtV3+A3H9ACk/1OKCmFAaMKe880As2lyLE2yIEZ4GhyLTL6I2qwJUIhJMI4nN9OZhc+3JciL0ljrVowpWolh5ItETTmKJYbiYZpC6ogNmlzYSzptVaouk/WCBZ1ZUjCmTNpFLAlE5JlZMMslNY2ZjgY5K2W1PmAq9wM8pet90tbPe/iljqo2BpUY8EqaA364HA+VIqLwlWKghabNpPClP62FTKq+UBpMCglSRFNoNm0jBA/J+M7FDTUrbCuGFUb53RfquoPIEVIIkWra7KhCAjDFQXsQ1tz1B222/SLw3OaXbT/OZJtrxxUTZ1AbxTDJO5BxowwPtxMksvwKoGbURSNZskthOcwmt2S1o/J7JTOW5CTBlw1Gg05axBVIwXyzvDjhvfa/eY2VMpQWlpldKBr
*/