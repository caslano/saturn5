/*!
@file
Forward declares `boost::hana::zip_shortest`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_SHORTEST_HPP
#define BOOST_HANA_FWD_ZIP_SHORTEST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more.
    //! @ingroup group-Sequence
    //!
    //! Given `n` sequences `s1, ..., sn`, `zip_shortest` produces a sequence
    //! whose `i`-th element is a tuple of `(s1[i], ..., sn[i])`, where `sk[i]`
    //! denotes the `i`-th element of the `k`-th sequence. In other words,
    //! `zip_shortest` produces a sequence of the form
    //! @code
    //!     [
    //!         make_tuple(s1[0], ..., sn[0]),
    //!         make_tuple(s1[1], ..., sn[1]),
    //!         ...
    //!         make_tuple(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the shortest sequence. Hence, the returned
    //! sequence stops when the shortest input sequence is exhausted. If you
    //! know that all the sequences you are about to zip have the same length,
    //! you should use `zip` instead, since it can be more optimized. Also
    //! note that it is an error to provide no sequence at all, i.e.
    //! `zip_shortest` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_shortest.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_shortest = [](auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_shortest_impl : zip_shortest_impl<S, when<true>> { };

    struct zip_shortest_t {
        template <typename Xs, typename ...Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_shortest_t zip_shortest{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
P4XcfPr7jt16KmnfirMaoHCRVlOvs7tPaXOWcKwZgC0gc0iIdcwhwW/QcUm0gIQFZpLbRIZmTUvo4ExWGh+eybUhAVojD97e1cnlC9IkJGxhWv3tdGyEZoAKHaO1AQNFadG4rSRrbv0KfU3GGyXWVnVYHGcWQxu37Z7TSOPfxF2nVsdgOhGIiIJ/krFsbb3YfPZ8+/nLF00sJl4+La+SR+XVXD1yacoWabGclk0JF5X97QfWyUbyAxdVL8Ek4rIrapcBKhy+Lt+KvSwwzlMNbcCPZkw+ZL0yUBGGXRooOxwuDNP7Cg3EjNhiQzETuIBgTBo8MBxzmAO2+jtCMqC0AX/vNYIwz0AEcQ1RxJ3vyJA7D3NMfoEMLdpO4Qou3vXene3/0k1gcZVeLUaXd+OwRuiqhxACDlT4IOpAnjK1fuNAqNOi6ldDsgNbS/l8s5Xy+WUrVWAABQCVeePIv2gFS/xrRdGkv64JIPxCli0t/l2kAoRTlmHCjNUsIW1IkI942K5Xr+iq6H81jzZqnofe/7X6kL2/bQMAd5QWHU+wVXme44HdCnFkqBWOklYfHmLpKNVXT0uSigkC8FzVo0s36tfaqhgYgaEsplTB2gFFT+s+IqhpGxokLW1h46ek1WCNdHQN7vx+71+3M9FW
*/