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
Mm98YEqLoY8xmy1+Ux9ezwMsBJ9kLQ/uRJDvk8iHG4j4RURE3WCfzti96/li62Pt4tezxOD9HPLDndJjdk6zULxegvYipi/lu0D4QCXFmv3Kv+HDFpF8xd9A3uVJkOYr/i7SkYq+UT9GWuyvgzRLbIfuyPp/Tt/9Y2KLgv7tTP9V0fY0NoCe2/JbpG9F0pqORH+rPxbjjAgsNl6a+/CvZX3KCRDiRxGvd+0cid/ahdBHWeeNf0LasKrzQh4Xt0S+kmWsbrRJL8I+OfPfHvnLcfRS8PeLMmkcIVbkycQmbpVWQ80ZxnZAl4328JC75yi6lZy9YhYQE0RL3WRIPsWT0oZZVyH+3VSlzvJyFfNUFPWpWNuEY29jUBZOzP+9OpNciiflmViEGzOrqcqpj81Fm2TfNOmfvjJtU5PqOCP/e32WdfnkpG9a23Sd7HWpcH07Nl5W2gT4YFo1OMnsPHUp5izLoih710KWM6u9NNbWbLnNLz2o4D+Mfytkg1GBO2/7KpYbv5h9PJfDGQEHHr3TR5s91SVa1gnjtG0ky3pOUU/0H4xAKK9IaQLZBsvt8adlX7he6F57Hus0HiRTn6zGb73udIpFwIWqe8fQtDlOKcVZGg9dpY/CZ0/LvvFdzbXXIQ9jGFj0Yj7+TFYMmrYIdd11MbEbdV2vnB6YKnMoURcVOlBovS4vJnkuWi9byS1i1wbnCeztVKF/k3v42YWuGO/W9G3/75qIWqe+Z69cTM5Bg5AVb6a+eFPxM/RTX5TvrVGqUoP/H/3vwJiBMfbE9l3o1Ez2lmvdaRyPK/ami+BVnYwhbOMaYj9P+qh1Zmi976b3L1ODc24kxjqflfVRfbAcdqhn3G2gJrzujUOe2IkuF3oMk77jdWP+q54YlUD0vKjQU7OhkX0ruua/6gnbBhLH+aZCT8Vc3/NO1Wqq59/30MYezkfnpS41yLrmQoQBGW0k/8NHdymP7fPyPN+6TjvXsnEjkAOCMcsfnnMPz0tbYeNVpY11MVbIzlfHDcmzhfPQ+WReVbbtxMBBx7pxB3Dyi4PkF4racn0+OKnPYLueqz6owil63GuBJiNp3sKnYcxGoaNixmrhpexACZ3fa7TkEB+Yr1DZx6tm0KJRGiRj4mUsrUaMDsrvAgRf49paMWC9WEfz6sXtGeZnI5jsVO7S0DRWDkJHseroaOmLhr49lN8z0wrbDENo0jMSmDrCne9TuHO0Z0/6RNeu69qOT/pke75s4wMCrt1ZOJv/OdzfpTMO+Jnl+8Nn3hXuFtGXc2dTCWX8NpwRIy3fH47en0DdFk4qEEX6bSgdpeFuMNLzPSMMefcM8jxjocpqu4qQeViX2y+fi00VLjORlnxLY3rxXCTS7khoSRLLiv6lCJOa9aUcWAQWlfRJ8j9Vckcqsfkcv01pd840ZSe0nBtLKv6MBkVTPVIurGpLGCM2+xrqPD6/b3wOIRZGYr/eP2MHCme3lc3tRfoDMr3a3t5MRNq/D430zc2d0f8Wnz8sP6/6nvI/PD+vzeYW4X/E+FxsB4Rbwv+4ccwoAWMCao7tv1g+N5L0zaVI88/aNDu+2tp6ltuUSHv82Ke5tdvP8QrLelqkCbW5HUcRPhe531w55iS2ZdNBnbGfVX6+7bDcOj4b7a07z9qsPKlvgzQwt01oOtPA1JZoWL6JtGBfjJR4h/4seP62m4VvENZ+cof+KMh7tgM08N4dD0ovn49+7+GkJA7nsHuHk+vJ9SHbVsxbAvz7iR8PlWgji1xR50sTDz18oZUEYumo0gcB/8kaflRL+F7+b/ji8TrwpTq+em0dY6FYx9f913ajyqjzDet1ItedgectwBN6GLbbI0JK6uM=
*/