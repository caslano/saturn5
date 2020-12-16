/*!
@file
Defines `boost::hana::for_each`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FOR_EACH_HPP
#define BOOST_HANA_FOR_EACH_HPP

#include <boost/hana/fwd/for_each.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr void for_each_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ForEach = BOOST_HANA_DISPATCH_IF(for_each_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::for_each(xs, f) requires 'xs' to be Foldable");
    #endif

        return ForEach::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename F>
        struct on_each {
            F f;
            template <typename ...Xs>
            constexpr void operator()(Xs&& ...xs) const {
                using Swallow = int[];
                (void)Swallow{0, ((void)(*f)(static_cast<Xs&&>(xs)), 0)...};
            }
        };
    }

    template <typename T, bool condition>
    struct for_each_impl<T, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr void apply(Xs&& xs, F&& f) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            hana::unpack(static_cast<Xs&&>(xs),
                         detail::on_each<decltype(&f)>{&f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FOR_EACH_HPP

/* for_each.hpp
Cy7Bf0fQ2VfTpRn0zRr1v4G/TsRP+uazr4Lr59LFflemHK9v+ZuOnIlv5He/DHn3mOstpTP5q278bCFeT1K/9YPhODyNWtcqOVrczhdf61Wz76S3o9an9UOKxGvENfo8B6uHD+XBJvOxwzyK28IT7Ttaaj1vNP2Dz2pq4GaVPNwt36vgTSu4cRrf9J043IdXlsLr5nz3SHz2iX6APN1+qnlPwyNnJ9KF4kffVo0zT/3094fCOzyU36hvRJ8X/CI/vnLeRLh2o3oeiJ+XwoHn6K216nkeHTmKHszTJwv3V15Mx8nv0vOC9zPuwYv/3x+q7u7nC393HKSvcpzzmtR9f8/R2Tx5zhyvF56uv8GXVZTKuxvcd24iXcUPPmi+IvT4A3jvOHHt7HprPCc/W3OJ9ZLD6VHr6yX1fM00cbuATv6Tn+Mjp3T3XMPohfvl+yPm+UV5/Yd+xww+MKpPj7/7pdNHnm+a9anKH+TdHPlkvNPkV5f3wnx13Yfd73n3r4Qb4e97XWUevja+vnBuIP5dDd/X4d9H/d2FDjiUrh5gnWWD+eQfFg7HK9FI8Hn5mHI0P34cXKAP8vL5jQ76r+Ld8xx1+7znGyoP+erM0/jUkfRFO7w/J6xj8zITvj6EX+r5nAXw4xR86P1Fh4Y6EG8P0cc423Mk45u36LDiKD7gr/jfhm/p7Rzxel28l8rTbdYH1/NXN/D17a1z0I3J5r38Gc+zl7+037X9LfI3ildbyrPsaPB+Er9h/ayoCB7Iv8oW8u+h0B/Chb3yeHEETyUaB/0/Xj0M1n/drx53iV8p/XUnP7gryldZHxjMl+Woz5/gZgqfzDcWP+v9oeH3wcunw/ig5p5jvH7GFHXxhHzsTY/Mto7Ot84+Ap9/z9+fAzfbu+9JcOZ5ON0TLp0UCY6fmo8tnvcrcaUPyr+mI+jCWQfjvQPOsy83/DdisPn/Rj9CP23lDvO40j6/vvznAuc9Ix5p4q0P3zhePltXyDwejxrfDD51lX5lpfFHM9XH6+axbcz+BnVAl9S1kp/GM3e7PKYLK7rI8y58+qV8RoL9RRX8nvWmbOuYmY/xD63FoZRuhQdzL8E3d8HFT/Defvr/GDzfW7883zoSvk6iw+ro4Mn1dPkv8HwJvU0fZ8DhLDqokV5Kh5NJ8Dw3IRoc+ZJYR3rT6yvpwuyF+lEHWe9s5nkeNx+n06Ph77+0t246iE9fhv//zR/8xudm8VdvybOT6F59mU5l9NON6vgL402X752MW58ypbf1oql45Tbrx3/SSxcZlzwp66GOToF3m/iBO/HYHPmRpV6t8xbtkL93qYcG+ndnYvD+43TWcrrEfuPSZvjwXPz3TfB+Zc9wP6M+0yR+Zix9XJQIB/gJ+Vu+Wx7MgWd4YMpr9HsJHxL2TdR1zcF0eBv6nr8f0YinLuMXt+DduOtW0XPz6a6djtvw1O94cJJ14CY40lO9XET/Hc1/r+Yrb+Oz6uFgGl/fh244Hh/ofy4PfxfoHn4cLtW8ih8S4OYevrw33k3VJ7iUjvpOXXQIji35qil8UG5mAt8NB8Qntk5dvY136KbJ++V5Y9T/xwjjGryfdim8fkF9Z9EdF7mefk/BOuuo11rXnWD+x9Ah9HzxDfxAOF8v0Tvnq6tj8CDfWLQZDsO56t/5Kbq5dr883BEJzj+VLlkd+izPMVkevS3vrvY5PF/7XBgvnzsBfnxt3perf338UvvgM1LVWW98K3+66Fsu+0KcU+Slfl7x2+ZNf6mwuXzsps5nGm9/fU46eOoA/lc9Vc4K1+HC/YTidh69tw/fH2KfYyF996p6c98tx/AJFfx0O/h0htdHwcHr3e8G86zPnzdSv74=
*/