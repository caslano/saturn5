/*!
@file
Adapts `boost::fusion::vector` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/ext/boost/fusion/detail/common.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/length.hpp>

#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/tag_of.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion vectors.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion vector is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/vector.cpp
    template <typename ...T>
    struct vector { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace fusion {
        struct vector_tag;
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename ::boost::fusion::traits::tag_of<T>::type,
            ::boost::fusion::traits::tag_of<
                ::boost::fusion::vector<>
            >::type
        >::value
    >> {
        using type = ext::boost::fusion::vector_tag;
    };

    namespace detail {
        template <>
        struct is_fusion_sequence<ext::boost::fusion::vector_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable (the rest is in detail/common.hpp)
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct drop_front_impl<ext::boost::fusion::vector_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::fusion::vector_tag>(
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
    struct make_impl<ext::boost::fusion::vector_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return ::boost::fusion::make_vector(static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP

/* vector.hpp
lbU2e2CvAZL7m2pvL4KHBBlrju6bkpNrzrZY9FftilwLRG4MpSmWHOv4jOz+8fx3tp5bU5rmp+eZE1MsSkl2jjVlAumSjGQrCa2MbLNSl5uRzF9GsYWXbQ4v6sos1Wn65mnjpacBsvk3hFNU6SgpKiLOEvmVvnHWuKKu/uH/dkDNK4v/ZmSqxWDj+0f3rbMNiB0SG903zSN+pfLTEN232sl7QZ2KMCwTLD656v+SAUzMtpIstmbxH5SKHHNKhv6f1uS8fJHrK8gz6xI2k7xMJqNLFW9JFi8BFY18/5mVEt03h46vdET3LUUX/l0jTczPzEpNFtrhk4VQk/+gB796dk0eWsRrcMvdxVXRqY5Kuye6Z/3ghF5F4x3VNmedJ3qMo8ZTRA4+tdCSMqZoQExCTJz36aLaqq7/bg9xsb6nmERsTNzA2IT+MbFFtaXumv++kwH9h4hOjL3WIrVmkcCpHiPk8jOWnzx+7gUvRBzwP4/zv6xXdlHnqNYXnI+JFerv5w+ObK4JxpzJT5aMePL5Ee8xD9L3tg9+QqBrnlC6Yt6HXGet46W6dmsZo9PuYtkuRm1X6Sy2GQ0Yw6iPo17U6cUiylHq+lMX+FykrBvgrSMRVlPr0bzlCZQncWbhImivKdN88xjU5Dw8mrd+sFKvrqSTUh9YJ/zlMMq/Z4ND8Jcm6UMT2xl8o07zl6XIsiuVsomUdW8Oj1XKrO1oQ9nXSlkFZbdQdqtSVinLzEqZU5Zdr5RNlWXzlDKPLFuolM2ibB9lbZR1LGln8IgKpd0yyoL4e2Cwv+zBdgYf3608u1aWzVDK1on1hnCPVOlvC2UuygYqZS9KDvK98ux22d+bStkOuY6+yrOfyTlfqpQdkeMOVsq+lc+WKWUn5RgOOUbvf4dfeAS3CLSZOtVmfPrcjgjcgGu3XWg6z/n0uT11ItVEpq9/nPLMHqGXNpvV6bB5E88+ne3FM54pSh7eWl1bpTzbl3qvy6AdlX576PeHZzkUr7X7+o5r9KysZL7e+v7UZ+tPN86td1LwgRMya6l45bvVLl6R7+t7oPqsb1V+WQyintNHa6nbXlwjbV7FkuJS8YJ0P04MoT3lem+uYmqUeQyjLpnTv/wcMUlbrUuRz/D2BlZU2+t0g1b3YyR1tLaWOJzku/1zSJTPMFajcQZHGOX6CQF4qPaVJucn3vcuyxthjsNjc7iVeWXJ9jpMlTqryxzlPtnlUCfmJLTRajPeia/uy9gm6q0a9co82RcDH4198ahzKlBl4vLry/g/zsmqPlfY3r9+tfztdnKvRY/KGvd5y40embJfxlfTl9NVI2Tswqdp3nKrV2+MUU52/XN5WafWOuzirkjXv5CbbORbY7HaT5XTVouDUGVbSr0+vKzTGyp6a5fPVwl/WOrXz3KfDsoq5Zkp8hmht3U2/zNVsrymSn89PvanNambztoan3xmUM7U7NO4jiPmHSHLr5PlGIDPn81W5eGsq7a7/f3fIutqnNYqe5W/fLHcY49e7O//dr/O+OayVJZhwjZVH+6S5bobVeRwjywvBQJVu7rPOya2rZ9oKM/8k7rSCqcLURS7qfE+84BP3gwfsBcrxDNOV4P/rMKjeXVktYGJer7VXJgP+JEllpjqbbOmqTYSHr3c6PEm27icLqm3Xn16shHG+ht4x1pPvd4J1yWEMShz9o31FG0CBqKlPPxQ7P4Z2c7bj7WkQdzw8Mns2YB6dQ82eetsBC41dr3a2+8/2waOr6/B1+8W77M4Mdmvb07P6Xvhdte68AKO8mqInNuuYMSpdtS7Kz3Wipoal7UUnfbvw4uGjFMyOLTXr3Yo8vW22absQ3JeptBPdrOyUp3DS40=
*/