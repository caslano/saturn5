/*!
@file
Forward declares `boost::hana::zip_shortest_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP
#define BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more with a given function.
    //! @ingroup group-Sequence
    //!
    //! Given a `n`-ary function `f` and `n` sequences `s1, ..., sn`,
    //! `zip_shortest_with` produces a sequence whose `i`-th element is
    //! `f(s1[i], ..., sn[i])`, where `sk[i]` denotes the `i`-th element of
    //! the `k`-th sequence. In other words, `zip_shortest_with` produces a
    //! sequence of the form
    //! @code
    //!     [
    //!         f(s1[0], ..., sn[0]),
    //!         f(s1[1], ..., sn[1]),
    //!         ...
    //!         f(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the shortest sequence. Hence, the returned
    //! sequence stops when the shortest input sequence is exhausted. If you
    //! know that all the sequences you are about to zip have the same length,
    //! you should use `zip_with` instead, since it can be more optimized.
    //! Also note that it is an error to provide no sequence at all, i.e.
    //! `zip_shortest_with` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_shortest_with.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_shortest_with = [](auto&& f, auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_shortest_with_impl : zip_shortest_with_impl<S, when<true>> { };

    struct zip_shortest_with_t {
        template <typename F, typename Xs, typename ...Ys>
        constexpr auto operator()(F&& f, Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_shortest_with_t zip_shortest_with{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP

/* zip_shortest_with.hpp
105bRZkO5kqmtO935cct8j4VqboWpYiAG9Tbj788ouIGrS5RtPq6zYzefM8j0EC0ekmbkBpx8+NMrL00LTsi1o+ATDRdJCn18hke/WKnfQv4Nyn92/NRG3I80iDHoyK4J21G+SlqgBH1M0Q1IKoNjbba2tLobZva0mivSaPzJI3OM2n0mW1o9DoSQFxsMeiyt1rlAoH2PLI/An0lUot19fsj0HPkTa1GRaCLWa9+W3sCtvxd1sCvAmBQu5lkNRpsb0STNzJLZ942S1k40vV4pFr82YzKV69mEezKDk9pWIi3FKXO74hSH0L1LmAVCbbpvVkW7nicaw43c6w/TadnpeLQOTvnJUWjT6NcbBsJ5Pb9Vw5IpO/eJunsXONxsFhw2BZwTz/crIj0GQcg0rO3mR3UXNiGUA/fD6E+ATmKmGJuh1H5FoNUh8Sc1Ux0fSJSz46AuLyZHfkiIR2F4iLpKBFz4YiIs6W3XJzO/R3Qn6HbT/8jtvvCotebJK+89MX0xBpCWJb5B52qHQrRYASuUjJ1RBq/VpWQ7zDdulIx4bnCCXYIJk96QtoXDgrPgavtuzmj2o2vH0S1qeN8nn7YeDzGaYlp1yggKHZDKVW7y9sPrKT4O9zKSo9ZTuZ9fBc/ImehdWC3xRHP4ZQgku0r1Sex7voYvYypfeJCmA4tpHMuUsdlwVAuSWQsb7AC4QMSeS/+ixIMJZE9tU2zmWnGqzRTVZoD9i/XD5idLRsPK8vLTqr02flaDl2vJoUW2iwtJHfuSHusVLY1R57G6ZXk6Ung0zO46QgS/wzHUBn3siLIzjci+SyQQtbCieE88x0+QMSB4FHYgeC1uOclBat01TJTjnzY1gfFM5+Yst+ufMaJXjuWTiAfwJqDFKLHWnUCSWn+xoYPMYi3ItrI97KF8nnpNGUR7B14xDpkSVZ6Ke4RTg+hlVdYhZnjVgkutW6VbJ2bXzCTsQmO9SUrffp4f7LSD4U/OkUdn5eszFs+Pj9IDxVEneLWh9VZTgjKf7nQHR3vgKdbUOQ/oJB8FMJwzxTHsLm6XS/1EBpRTcoOeCMuDESDarz/JMf7J1vlGfm3PbD+lj/JP9F4X7M3PTV7gx/ds0/tg7uHxUD2OADtgfWJlXxEPkyXmlfAJ+bLKwJRujEodagS4Jgsi+bqOQYuhhnl6ODsqecAQoULvrZoqdLQ47JhDMpIEH2ULaZ/RV+X+OMn9PWIMx6lr1fcBvYoOlF2eCGeJmFMLjgYdm5/8x0T3UUT3aqXBggeYx4TeFwNC2y0B+XQXvGGmsoaMFNNdBU7542Dmuht6VNDW783y+/J8vuz/L4sf14bPxo0WK8i9ewBckh6Zx5g4wrs3gcZ5I4IIqjrtD0ZpljCCJi4J41JA1iXJ/RUizp/wW0fIu4v7k0T9xxpEKVrdVjNmXf2i2JK/hbQKwjSPomFHhg/AVv1pHEW5dH5dgKXzGa6SCxH3wibIj9dSpSU6f4KkIfdFgjT3Q/nwkZTssJf9/U2ZbPxQ64Fw3QLd+Ti29VKMNmWXglScvDPf73tSrC/8UZ+awMbr9mNvm9H3/XKNjXeImsMaMMyarRY5fnH62k6E2V560bjFmasOaydrTLUiIXYkSrDZxM6rqC4owpueU0K0eeoKFyKwzwm+7xcaU04ogxSbiXF/+Tw2rp/nuSp/m4P3ICOgLO/drD9HevM3X0qSElDdjwZ963yy2TdkvBx0jkfqKQdpvc1ZK7XnbFam/irMJ4F9wrpycIxYej72BOx4sjYZ+l+N+71cLT7Wrri3dDhfJBzYSp3CJ7wvMvQKOGFKGJOKi9V66NqVVj6zQGvOLeJeOPKx9XVnaINXGedvuY=
*/