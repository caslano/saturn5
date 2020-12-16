/*!
@file
Defines `boost::hana::slice` and `boost::hana::slice_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SLICE_HPP
#define BOOST_HANA_SLICE_HPP

#include <boost/hana/fwd/slice.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Indices>
    constexpr auto slice_t::operator()(Xs&& xs, Indices&& indices) const {
        using S = typename hana::tag_of<Xs>::type;
        using Slice = BOOST_HANA_DISPATCH_IF(slice_impl<S>,
            hana::Sequence<S>::value &&
            hana::Foldable<Indices>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::slice(xs, indices) requires 'xs' to be a Sequence");

        static_assert(hana::Foldable<Indices>::value,
        "hana::slice(xs, indices) requires 'indices' to be Foldable");
    #endif

        return Slice::apply(static_cast<Xs&&>(xs), static_cast<Indices&&>(indices));
    }
    //! @endcond

    namespace detail {
        template <typename Xs>
        struct take_arbitrary {
            Xs& xs;
            using S = typename hana::tag_of<Xs>::type;

            template <typename ...N>
            constexpr auto operator()(N const& ...) const {
                return hana::make<S>(hana::at_c<N::value>(xs)...);
            }
        };
    }

    template <typename S, bool condition>
    struct slice_impl<S, when<condition>> : default_ {
        template <std::size_t from, typename Xs, std::size_t ...i>
        static constexpr auto from_offset(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(hana::at_c<from + i>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename T, T from, T to>
        static constexpr auto apply(Xs&& xs, hana::range<T, from, to> const&) {
            return slice_impl::from_offset<from>(
                static_cast<Xs&&>(xs), std::make_index_sequence<to - from>{}
            );
        }

        //! @todo
        //! Since we have the right to specify the same index more than once,
        //! we can't move from the elements of the source sequence even if it
        //! is a temporary object: we could end up double-moving. Perhaps it
        //! would be possible to determine the indices from which we can move
        //! without incurring a too large compile-time penalty?
        template <typename Xs, typename Indices>
        static constexpr auto apply(Xs const& xs, Indices const& indices) {
            return hana::unpack(indices, detail::take_arbitrary<Xs const>{xs});
        }
    };

    template <std::size_t from, std::size_t to>
    struct slice_c_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const {
            return hana::slice(static_cast<Xs&&>(xs),
                               hana::range_c<std::size_t, from, to>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SLICE_HPP

/* slice.hpp
aOOxjmfxUB6uR5a0L9F8WYR/g/v5zm5wkcD7wEu9vbhPlsr1Iab09IgAW9ZZZ6K0tWZGSi+Mk+iTYddhSQ7bChwtyS0/zQN2EO8mrNxY55WX4yqyHmai5TLZpe+UaU/Opk0XaGBjTLSPibReDpvBehCBIZYzwt1d5nkS8jwUbhx3/x3Tts1njreX59HGtW03eJLTY2rEiP7IZVKP28z3qLsX8iTrO+G5NP5sebNygFdZ/M5+gXvUhoNWx+/pl9dYHk93bYh1+TWULe8rwXqH2JUrE2xpxJB8W5HXsZNWa1GxW03nyy0oXd0wZ3hvROPG3Ku3ot47Mid5meZ5bamM8wavBZeNZiodDRBTwyc6tJk3opKV78a6gDxafm7xsFve4ha3uGWw/SyrndzLnxb1+nZwDdea3S/Ve2uVda1JvV0wFzU1fhIgH50PqHEivjziT3D8ptJvgntntWw6Jg8jDk2UhClikl/jVr5DZ3jncJMfpLvqRlpexy/K5rJbFGXxC0K+25RlcCSd393coSwDrTkmKOgyb/3jVD6DkpA4k+RJtbFsbb0KTSF32Bv0OcK0rHT5fuY+uTwFdsHnCaMYE7Rum6xv0rEXMPZ1Y2zvWBM4koYIEkrbaE7TExKnspVzmBf/bROfQlUFoGnLgoFtlj7cPInij8KAiHgdvy7mg2DetF7Itvnv7m7GeFqW4gRverXlcbY5xu27+M3fCtaA8DvH9KlbR5qUh2Lz6H732zwdf183/N4/PMq/z4XfO7sPCb8x3gq++yvlOrfvi/kMfn1BfI649Sbbf95cnoFrrmzrhGdpxtLMPjr46q2Gr8/LYY4GcGH0N6eybme9q21InR+DaHFTIecVVtRdhQumxrlhYD5w7IKLeuE6u4b4dEU9xltVO9OwaZ7jgzrbcRI92kKdMqbnmm3Ap1nCak1lcPTjeXM5Z1XjhdK6hsNV/saXC4pZXtgK4ixSOecb1TZ1rW0Euqa44Oh7+7Wi7ZY57+vB9DZ/LKHe+WjdIhot6AUN3kMUcjgbbNvwRtboV76XLNJzp/RTk8/zbynXytY1teCDYwkJBR2X4j92ycIXW8KCOqXyHKGyRATelUa0PXMnO9m1LX0uYHHZgpG8b2jYg4K70dYhw3vni/64wK2KYwCDOAYHwned16tLLadDveYmsXzMXwRL1hjBGGGw4uIWb58R2+pWgCM16qIgIhbtot/rW8rvSPWVHFpJ03vFwYgGE9xPCrvwhfHOczLeumpgjGo9FzY1QMYCMhOABnQVxJYr2gZTx9te951iScz9cd2lkwkbdprtE9d5XKkXdHYQsh/6RTmxq2iiznPwb0U7BKs7VTlvXeYHbW6BOfNe7q0Te07lxWDQfB8V9SmvzXrPWyf2RymttoP7r9d2mBPU7uaLthimFLfSel6sW1sHQfN7eHxJ8Hrq+XvexfdSyAmBSfXQ+bmdLMy0fTAKPgI6huYSlEPiEQo5mrVBu1eiYehbeHZz0P9zImNQurKd6IiMPMtghUm3GqQtuFYU+7FnbSu7Rnd6WZ9QYtm1eNb81DVyHHrMbxuP+vE52mkw+Hx8jjaaRtrIMp5N73jVpXmg4j796WuciZeB58vXwZ56RSyHTZXkCfrYBWlZ3Fix7GEXgzK6VpAz7dUuiWXAGIrDJjfPFXjjQqesmLODctLapXnFQKMbk4qtYm6J2wVxeTDJXt8WchWrnfdN14nlSm/8RTXfeIeS19Ub/jDm0Z/oeSsir5Xn5/Lkqvjg+688MK+5//jB4vkNKFM0RAdi5r5Xn0DaMH8zaeznjH5Lryv6JtjQ9No2qmbnDkOAe+hRvPCHfgA/WeeihsFwjL7wpklsMq8=
*/