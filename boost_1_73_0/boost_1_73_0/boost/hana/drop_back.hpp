/*!
@file
Defines `boost::hana::drop_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_BACK_HPP
#define BOOST_HANA_DROP_BACK_HPP

#include <boost/hana/fwd/drop_back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_back_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using DropBack = BOOST_HANA_DISPATCH_IF(drop_back_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::drop_back(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_back(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::drop_back(xs, n) requires 'n' to be non-negative");

        return DropBack::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_back_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_c<1>);
    }
    //! @endcond

    template <typename S, bool condition>
    struct drop_back_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...n>
        static constexpr auto drop_back_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_back_helper(static_cast<Xs&&>(xs),
                                    std::make_index_sequence<(n > len ? 0 : len - n)>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_BACK_HPP

/* drop_back.hpp
urfA8AdoVdRCmUlsJsxtxYjLdCFZQbltKxGaWDkEGcrZYH0ZVvN2s2bFBacCSu12mN2oxvJcEdVVLK8ao4BUrJgkT35q/9y1Or2Ln7rDwi6M3oNBLac2TbRC7PgF/MAElqk1Qzpy10r6VyuBuNLSTwLXHKx1JGGZGAOw1fLP0C94eDLjkzp5WQdP1WZ8PFmm5I0uXsEdzPh4isT2bh6rqa5bOq+1TJz9il2OfoKdFKJRhF0p4tohBsGU5UhSl7X2GURK3XEjidMb7DnlFer18sQCfADHV9F6WSD2EolpBWqhNPfSlIMrgxSb3dqeO2G9C8pXYKZ+r2kiCppkBJvyXWRhXws75/WWjk64QPBy2el0R6NSU83i5af2sN/rv28xZb8RpuD9qXsdhxyMLMSku+QYZiO3d1Yb9Xv1nL+2i0EqsMl9DLnT/X9zsMH/yv9QesAup913l++1+Doz7tyAaCgxZsry6Pj7g0P4d4R7w6+t1tHvavQ9FuA5yNIVeFZFJ4xX3LFxg0lCRtsDV0iwpe1HItHIaX/E+kBdk1HnF/KAbHjWYd8d/3DIRnINsu8Pjg3FiSj0nfmilhrFbsIgLNQf62hKh5XWxjB4KKFB84L+3+n+KUKkit7caHbRXfOwQdEHNGmvNSHSY4sV
*/