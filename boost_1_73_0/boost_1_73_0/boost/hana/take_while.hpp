/*!
@file
Defines `boost::hana::take_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAKE_WHILE_HPP
#define BOOST_HANA_TAKE_WHILE_HPP

#include <boost/hana/fwd/take_while.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/first_unsatisfied_index.hpp>
#include <boost/hana/take_front.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto take_while_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using TakeWhile = BOOST_HANA_DISPATCH_IF(take_while_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::take_while(xs, pred) requires 'xs' to be a Sequence");
    #endif

        return TakeWhile::apply(static_cast<Xs&&>(xs),
                                static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct take_while_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using FirstUnsatisfied = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::first_unsatisfied_index<Pred&&>{})
            );
            return hana::take_front(static_cast<Xs&&>(xs), FirstUnsatisfied{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TAKE_WHILE_HPP

/* take_while.hpp
TtFpCS0I1LupOjyb3OtFj3aDW7Ru021xPIujeBiptvbN8JLOEh3LeVXiAUHsLwJyd1p6mIte28WVR0icWtf0xxQfZP80SFYL776FDiI/B7PnR08O24/RS+r5FXqrPEYPJP5K8HJ5x8zJHQ8vR+PuKayU4Wjc+JdQmd2kmYUPub9Z8qIzHPc6SH2dXt+S3UzXlQgYKLAzb0FT08j2A5tZEqm9xvMVkwBsXm+SmRDZBH/6pDR7hnGJiux54fQ6wuz0UjFBfzvY4h3OejXfk3NR8mPIbSwZLC9Wti0yRBGzjpNMsNXSLK8JndHeHEIGjS/2glSZ+sBFIhCFfH+m6t1eRwuh4ZZhhZSQHIrgMaZOiXuTEKL+S4sz2f/+4GlbX6/HjzhmzDCzF00MNygrEvkaLR9F61q0+WcQnlNNUPkLQVmeLAq1sYB5hEmgU7BsKpTI0JTwHiEFK4KCsP+S6w6G3bnG0F4InF3Uad/l0DcqYLwpiFIZoCE0Hc2z+lq6ZUAsO1KwC/Ia8lK88UfXSfG3nA5FJeADOcgkk1Z6zeAQrYhSEUG4er3Bx4Ktoq8vl6s/eLXBMSOK/uyIhap39h624O4QJD/jCSaI4sM8HXKzy76fKjgXDCfxp7DdJirbEgk1fPAZcMQlP7xBoG+6
*/