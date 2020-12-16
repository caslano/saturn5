/*!
@file
Defines `boost::hana::symmetric_difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SYMMETRIC_DIFFERENCE_HPP
#define BOOST_HANA_SYMMETRIC_DIFFERENCE_HPP

#include <boost/hana/fwd/symmetric_difference.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/difference.hpp>
#include <boost/hana/union.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto symmetric_difference_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using SymmetricDifference = BOOST_HANA_DISPATCH_IF(symmetric_difference_impl<S>,
            true
        );

        return SymmetricDifference::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct symmetric_difference_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys&& ys) {
            return hana::union_(
                hana::difference(xs, ys),
                hana::difference(ys, xs)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SYMMETRIC_DIFFERENCE_HPP

/* symmetric_difference.hpp
uNvg+l3IU8xK4RyvMY0ZmiuJ8LwU0zyhf6Byetb1UvvW9uwYt9raZn0q9QWMzmVedC5VLbWMiH1i/34QvQI78phmYhNWrTY0nwvMxj5ixBzN39n5T5nEBLWdNINWMDbkOL/3b07zKyLvfz2VdStRyU5Yw3b20mmeZzpf0DVBJ5Ae6O6f6O6dz1qUTnlmalP7wc7vN3MboX35ZN4uHswzda0be5fgT72W/WOKsdRMam16a3qUD02HW+PlZ9E9cnSeze3Af5vIVKrtBuNqIvP+Z8u8fyEz2yhu8VSqtyumDfeysXrhfIvtLU0JeJrNtbOVu2TZf6OyhWdOdnwwvll6dg6qAG6DY4V5cziIzjHh/7l+cv7TJn5CvqtU23aMmDPOnRyGVo1vCtpIVOw9zHVA5XDJnNZeVR3/L88Qe0kvVbi2FO3yTHQhcroSi2fuMzablCfpUVfP8TOgAyTs3MvE5/k+9rz0O9/DrsYz+aPh9+OuGs8we9N7zCvkWBA4k18CyikefXuh8Rk5juMc+dojpzk0+4Appf4zNmZ4ANEdCeISTzkUU4LK5o61cvC+atv4Hgkr/Dv7iWNoOKJLkBwSN35UiR/UGNn1XNML0iwAvf93odNRO2ErOsvxhRzFms6ppu2WitmPSH8nuwEdJWJRghyb5wOVIxxTxjQtlw2MHaZ14TrBBwX8Thh5aMncBX4nTK95/z5WtKthXd+JWhg5xws+GsWOforQrxENHvzeoKfEJ4HKqR2rvdO6HSRbB8dc7Fo6HywmxEU5K48uvx8v+sp18P5yJlPYaTDFfZaHdpJ5zMWNqZzzu1YEoKgOtquUznSKu3h+Ua9ifDDCNpU8s17aDxJzcR8q53Z80NqZVjFknfqbHj+6HDc39HXVCBvjGHBGIXd8HbQL6AdTtL9iVptWKu7YGOgKwso0D14O4dSVsSMJmsqKRQy1R0/WRFl3snMVvTwbw/XOPWjcNwmuU8GrmG4s96pXkTfNcdhNINvS2K4phtrlHlPacZS1RgdcqPvtH88A/RqGf/ckKh+lXndjyid6ZgdR+UGpgHsJ8xlGoR0qngaWgGGfizAm+9Ffsc7v5jHTu5Re6LZmPLna7m3N9gIXCoyyJvgqVMat6kpw00jHHrS1PYmBonScM6lg2lsjsTKoZHxzUW083A1Ia1sn+wcPH3vEiJ/lh6is2zjDvfOiDnUeZVgKbrJeUdQ7MK+8sS2XDGSSDBeLMXAQqgoxtnG8sqyVx9Kxb5mTwio9qIR5e47eSt5//yG7hzFwGsL0xodRVj6vfg4xMWYJOX2eK+driB8xiE2+cffNB+2g7fJnWDbmjA/Lj4J5Bnihs0zz6wnN+IkHBIs5ze+X0kRJaDP4M7bxfqEJiNd57cLuGv0XYeyDrwfsmTlO4+crwT5wFFBSz8trEB2/ngVjfdOYluk73dJRN2EaP9U+tvxOeNP0Ve86tnu6dXR4sj/b2znYPnd8v/SB7eLdAOXjbcAnVr3WJJkFOjmP609cLTAZ9FECxmN4N1C8e8GazjuhhGP26Iz1K56wMJAu9AnnZNE2x5q687X3dZiTCcNqPeVFT/49CcLvvpAFP4gi2D5/oLLO51oPyvqeRTaC17OPZ5bHlfZNPtTWm86GuslHgFDDATk3+9lz4rOR18HzC3kta3Wlm5bm5Tg9XZb6IfP7CX89qNqaui1j8M/m35vk8xBcOFDyJ+y4QS/gjT/ucZOcakb5weAVd9BkgZ++4mk2tRWGPhWPm/rOiEG1DUPecpKf4HyYtIF7xytR0ZT0/7ENiNc/kdUNrZe9/i/zhOzcf3YKRn42f7+Xe3y5R4oQvFj1yayJCTGm2AjnnZf3K8o=
*/