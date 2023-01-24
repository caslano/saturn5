/*!
@file
Adapts `boost::fusion::list` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/ext/boost/fusion/detail/common.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/length.hpp>

#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/container/generation/make_list.hpp>
#include <boost/fusion/container/list.hpp>
#include <boost/fusion/container/list/convert.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/version.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion lists.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion list is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/list.cpp
    template <typename ...T>
    struct list { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace fusion {
        struct list_tag;
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename ::boost::fusion::traits::tag_of<T>::type,
            ::boost::fusion::traits::tag_of<
                ::boost::fusion::list<>
            >::type
        >::value
    >> {
        using type = ext::boost::fusion::list_tag;
    };

    namespace detail {
        template <>
        struct is_fusion_sequence<ext::boost::fusion::list_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable (the rest is in detail/common.hpp)
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct drop_front_impl<ext::boost::fusion::list_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::fusion::list_tag>(
                hana::at_c<n + i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_front_helper<n>(static_cast<Xs&&>(xs),
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<ext::boost::fusion::list_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return ::boost::fusion::make_list(static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP

/* list.hpp
nSO0P5Zjz2TMEVm7nnwcj+zeTxfxgw+zYg4sVqQ8iI6JZiHf4STbIIfyIF4TvY2w89uc5Dka9bj+tYlCQwCkaT/dNiPbaPtQ9aHSk7RCffoZvGt1jKgbZtZvZJ00WUFhfyZWJzjJjQjCRn7IkHGMyBuh4yYoS0foK0Pzqa3WFZiIaS283IZkDQBKW1xkwn4qbIgr0DArgQn1w90/4oAPsPmLgOOs3wIoFFW1RN+HSbjaywVWFHNmKw9uYesROMZFk9HA681ORGjlhQEzVpYCLh0NmCm+rwlGSuOTKSVxMqUkTqaUxMmU8m2TKfWcyZR6zmS6GWnZSrodlSIdfa+TbUekquM8nj1ZWbcMlsW1Hp5c8om+T0WoyoG6dJmTufaoHOWCAW/coMRYMnU3QANOnCdzPtE58bc6o5w47qP4TsxC1gFzlfn2sIQ3VbNcwAY9jkw47K1fucl7SJs3wpFE+qg+Qk3yPnCTbzBdO0DlQOdaV/06iVqCCNvKLJSpK52Bj19962GeGYulHdNtmc4VleNSywZEN2QCH5lJOuEMXGlvrVTvNqDug1Kbh5eR1JmGcq/FV5uH9iAzUXqM2YGbUfk9yNTCIZnag1AHZEKDSjXdOfV6i/3AxX5vQLxRD04PQGARx3Pcusnsm8zvALpzBD0gLoNSbaZ9++CIoyc6Se0+/ewiNMyiyb29wL+3WJDxwshsekwN4Vkn02Nw
*/