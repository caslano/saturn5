/*!
@file
Defines `boost::hana::tap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAP_HPP
#define BOOST_HANA_TAP_HPP

#include <boost/hana/fwd/tap.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename F>
    constexpr auto tap_t<M>::operator()(F&& f) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::tap<M> requires 'M' to be a Monad");
    #endif

        using Tap = BOOST_HANA_DISPATCH_IF(tap_impl<M>,
            hana::Monad<M>::value
        );

        return Tap::apply(static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename M>
        struct tap_helper {
            template <typename F, typename X>
            constexpr auto operator()(F&& f, X&& x) const {
                (void)static_cast<F&&>(f)(x);
                return hana::lift<M>(static_cast<X&&>(x));
            }
        };
    }

    template <typename M, bool condition>
    struct tap_impl<M, when<condition>> : default_ {
        template <typename F>
        static constexpr auto apply(F&& f)
        { return hana::partial(detail::tap_helper<M>{}, static_cast<F&&>(f)); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TAP_HPP

/* tap.hpp
t/33/shqIv87/kvdsFtSv7x7jX5sMtH73v9SD6IYscJed3Pw842t2rtCsULfd4v8PPpdoH/vP56Qn8e0Q7QrkOcPTwo8Lw7RsMB2Blmaib038dzpqYHnGmCI7BC+pY7PMqRPbkmWPB/ngWdCTkXdLZdTB57F7ssP0L6Ce7WNF07iu6zUsvMu+AdeAbSVmMktbNUILhJ4wz/tMdt9SPhb5I343LMLbCIxaK4teBrm3OB4j/TCydnWtz33DWcqxvpdg5BmcMEby0+ymOP8yVT2MX0n1aBlzRaJ7xresRVlaNa3phFtwGAbI9VWszuXeSVeROWfwKVxffBGhVY/BmqIri37iOVE+QfWDwEJlotR4HGFzAz9OkoZY6El0vgkc10hU+e9H5URknktuHaiYgkMA9tzPot3wmFEzMZkm55ikn5lokfZptJVI/8HPVtBD8ZIfDPazLf6nCM8ehruI+7rZ5Ee7WnY75j1kWDFfX6qC65y9k5ncS4H8iK/2z+8cLIfrxs39MoyDKPKtY+jF7fjz8znrp1J3kRn6k70iK1Y/LnwyrBfvHDds592Af85+ssHpWUuj52JfaCxbeVty9bquPBfNYf17uF3BZ3jmr8tU+LOO6bnNx+fb/qNJe8tSZ7QZ4b7oPT8ViNvjGF4BPz+wZuGtTK9hEme0HP4eQ4TyGOv2zmj2ImvuwEEx6BMnBNxDn3RLQINAryvwWS4eCk+f/atls8Xpyd41vRPLW1tg3ONaDnHeQfPdvvnp+m0Og+xzPBveqZ/T6FHsdo0xol+ALymEXIM8OjPjwIAjqhiiAPAHIS2BosKjUn4SqGnZoPva+ebhJewe/riMXMTmC3GiTDNtJDQMnr5xDyB6Bv3tDIXc6VlCA5io2l4ZwGHhN2j5MuC51wqI0MuaS2MaCXktiTWkiQa0XMDhhVmc4rlo53jaRP7hGlsq4SK/gXRjYcfwEk5Rr085znDIKXWw7C19dyJ38gPqR7hmBC205b3rBCCSmS11dWcx9zMX35Q5Nu8PSvXmVbyxpqhZcnbNHbq/u710dSVjXE5e+TeqAtzpUxiUYQRQ2tFw67tkzgR2afw46D52v510Fr4cTHi0Bzuhi5DbAVWzge1CYOxEuMYElVILnoyP5pBVoDoM4DLR1ozHpbnc0bPxa53Siof/caW5kT0Pano+w74k1YEiKIux7rsHwQHytQBFAcjwNcQX9mq9EE0ntumHbDqoSencR3PpjKXWwUlt7UAl5yjq8EYir6BmBeuKuPzet8NXosuYXbspkJWsBLALDTfm+1Gv3z8XgtdDbO8DRHlVagwGhhjzFDMzZGdnNIHxzYQ56iaYHBKoxuuFHvW4UGOHwddsTo4l5S4J7md6Ffz86rwNW3aXlntGQiDZ1X6Xnm2NVSl74PWXWu0ryflY9HkPTwgl3eB0/Jq3snGxRjJJdL8RbTx8Ynt0nTwEtp16WoRIRE9xAjexiEv/dGsa4QUrUb8yt0FwJeFuS3B6VRVESf/Oirfh+uezvB2YOHq7wBAU6Z+2W/jEx9B27V88Fgc9NUTYqauVPUsjzlXebEPs950RnTQRwew/hwlbmJn+yyf5CkZrDQDweeEK7hUlBoq06e4KxrMg9/zT4v342quh7rWIY4Ig1j3n5jHQ9FOyRpn2k52tvSrBm+O6H5etnFD0Db6ABnuapjNFrODnUM4EeQ2ot2Y8suWKVNbo6shSsRdI0Z3x+kUs8+FCxa2xBT3gs5XsPsTPXcxvitMxOU9yrPFZG8jqq7RtWISWAMEHmAQpX4NbvoYPxHW74PJ3vqVosBacNIoq0Qo93B+vsRvPUR7sii/dW9r0wyDZxrY/8fC0bdX0Hc=
*/