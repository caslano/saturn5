/*!
@file
Defines `boost::hana::fuse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUSE_HPP
#define BOOST_HANA_FUSE_HPP

#include <boost/hana/fwd/fuse.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct fused {
            F f;
            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) const&
            { return hana::unpack(static_cast<Xs&&>(xs), f); }

            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) &
            { return hana::unpack(static_cast<Xs&&>(xs), f); }

            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) &&
            { return hana::unpack(static_cast<Xs&&>(xs), static_cast<F&&>(f)); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto fuse_t::operator()(F&& f) const {
        return detail::fused<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUSE_HPP

/* fuse.hpp
l1XS5NinzBkdQs/Sb1aIEmOPAke0n/WvL63nWGODLfLUadFlzOyz1cUmCdLkOOCYMzqMmHmOOokRJ0uBElXa9Jh+rhyzRZIMRQ6p06DFmPCeNrDKNmn2KXNMhz4jQs8z1qwTI0WWPY5oMmT6+frOBlsk2SVPkQZdBoRfIN9E2CRBjjI1zugQ2lc3VyVKnCx7HFHlhCZDpl9orrPGFhnyFDmkQpeFF+k7EdLkOKBMjVNGzL9Y7lknSowUWfYoUOKEJj2CvHawQZIMh7ToMvsS9bNKhG0S5NjngFP6jJh/qf6zTpQYcVLsUaDKCW16DFl8mVyQZJcihzQYEC5oB6tE2CZBmhwHlDnmjA6hl8sHcbKUqNJmyPQrzAEWWWOLDHkOadBiQPiVcsECETbZJs0BZWqc0WfmQC5YJ0qKAlWaB/96wHORDbbIUKdBiy4Dxsy+2vxjk20S7FOmxikjQq9RL1dlnRgp9ihQ4ogqvdf86werOZZZI0meIhXqNGjRZUD4tXLAKhG2SbNPjTM69BkRep08cFWixMhSoMQRVZq0GTL9erlhiwy75KnQoMWY1ZKcsE2aA2qc0mfEzBvUz1WJEifFHkdUOaFJj+CNcsIaW+ywS54GA8JvMiYssUqEbRKkybHPATVOOaPDiFBZu7gqK6TYo0SVJkOCN8sFiyyzQZI8Rep0GTAm/BZtYpUI26TZ54AyHUJvVT/zrBMjRZYSJzRpMyQ41AY22CHDLkUOadCiy5jw28wRVtkmzQFljjmjQ5+Zt2sH68RJsccRVU7oMWT6HcaGRbbIkOeQOg1adBkwJnxkrFgiQoIcZc7o0Cf0Tu3gqqywTpQYcVLsUaDEEW2GzL1Lm1hmjQ12yJDnkBZjwu/WFiJssk2OfU7pMyJ0rD2sECXFHiWa9Biy+B51vkd9JClSeY9cvEed75ELBoxZeq86SbBPjTP6hN6n76wQJUaKLHsUOKHJkLmKfrJDkgy75ClSp8WA8PvNBSLkOKbPzAfUyQoxsuxxRJUTekx/UD9ZZosdkmQockiFOg1adBkQrpqLLBEhTY4yNU45o8OImQ9pD+vEiLNHiSonDAk+rF0ssswWSTLkKVKhToMxsx/RDjZJkGOfMsec0WHEfE1uWGGdOCkKHNGkx5Dpj2oHy2yw9VE5YpfiR+WHCvWPyg0Dwh/THpZYZZNtchxzSoc+oY9rB1H2KFDihB7Dj//rwYc5Flljgx3yFKlQp0WXAeFPGBuWSJAmR5lTOvQJfVI+uCpxspQ4os2Q4FPqZ5kdMuQpUqFBizHhE/WyRIQ0OQ445owOfUaEPm1ecFVSZD8tD5+WB0pUadIj+IwcsMwGO+Qp0qBF+LNyzwLbJMixT5lTOvQZMXMq/8SIk6VAj+Bz+s0iy2yRZJcKdRp0CX/eWLNNghwHHFOjQ+gLcs0KUWLESZFljxJNhl/418Mu0yyzxhY7JMlwSIMWXcaEv6j/LLHKJglyX5QDanToM2L+S9pDlBhZ9qhyQpM2PYYEX9YmFlkmSZ4KDVosNdVNhE3S5NjnmFM69Bkx8xXtYJ0ocUpUadJmSPBVdTPHImvskCRDkUMq1GnRZUD4a9rFKhE2SbPPMad0CJ1pD/NEiZFijxJHVGnTY8j017WJRZZZY4cMuxxSp8GA2W9oA9skyHHAGSNmvql+osSIkyJLiSpNegyZbqmbDXZIskuRQxq0GDP7LecGkW+p+1ty8C31U6bGGR36hL5tbrBOjDhZChxRpc2Q6e/IAYsss0GSPA26hNvqJ8Im26TJsU+ZYzqMCH1XHlj5rrrZ+646OaH5XXUTfE+dLLPGBlvssMshFRq0GDAm/H3zgQibJEiT44BjTpk=
*/