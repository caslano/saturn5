/*!
@file
Defines `boost::hana::zip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_HPP
#define BOOST_HANA_ZIP_HPP

#include <boost/hana/fwd/zip.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_with(hana::make_tuple, static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_HPP

/* zip.hpp
Dmq9HJX+1NG4Lx5PdcKt8ZYYWm/lp355c+oXfQN6y84MjOphQ9N1xX52ZATKvQrGwRtQSjVLruD0xnmNXsGzZRzq5yDOp4810IaAlOpBocVaJVEwAz0EJ/JB0gS2johqAsdGa5rArD3IonGD3NePo4TXxg11U6ZgFFvcLtfJHCdgnpWwZFNtn1ibg2JZqbYB3+xk/VPQ0t6unilxRyOflWembJESvJNXlivmLe4lkUW6z7zDEeTYrwFkBchVvdegLrRBq40nNQcf14zWorgc9rRcBQztTaiZ6jhsbyUrj0U9o1Tsw50eCUqpFlFPcezOcrSID36Kwi2apR0tTtDGJ+lOKCP44TkX/hWlrYp9kSN/VMduX1Mxmodv6hEM3hncim1hK3oFQ7FnZQ56NgXUdvaejWoknwnrrPjgbmTFGG4Bc798RkA1CYjyX/14Vw957gSImCG3GG3NVT/np744u9Ay6tb2Nbq1UGPc4FELX7qeQ6uAdBjzXE95Nu/XbespPRgPYXfXaCRrDAzY4WKnqNc61HdA8oPbCEvFHfBHMNojMldE+cdfoStcG748Fj5iPxocozpeVXPQpl2/+T5uZVIbWc1MXBol+epnUPx+0Kd/jHR58eURfXrhMNSnXZ76q3FtGNXpiaNInV4o/ndbYce4Pd0Aa8hKloUI4wbxO3e0T9F06LHid29hrxYiOjRtgvVYFvB4JSZmEXlE
*/