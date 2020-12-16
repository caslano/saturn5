/*!
@file
Defines `boost::hana::front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FRONT_HPP
#define BOOST_HANA_FRONT_HPP

#include <boost/hana/fwd/front.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) front_t::operator()(Xs&& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using Front = BOOST_HANA_DISPATCH_IF(front_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::front(xs) requires 'xs' to be an Iterable");
    #endif

        return Front::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename It, bool condition>
    struct front_impl<It, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::at_c<0>(static_cast<Xs&&>(xs)); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FRONT_HPP

/* front.hpp
iF5bDmfVXVELuptOyB8g787hM81LZjXc/Dj8naJwPyM+v6QZ/wUHvpOn28R5sOdIjAafbwE37AvIyqVnUvlq9VjXlu4cjGf7ROlV+F2grkLeHg0vNojjCep9GB9GRxd1M943wu9FhgMlfF5rPuhDurwtPjFf+Z6nwPx0uR0vvMm/WLfbFG/aPSl+Snz37oVrfj4QvzT+3F/b1/zYdGd8wPwfl0zanf56Q+WSozfM3/XjhgMNTWXxrfF3J02qbIo31MTjTfve3L21adLu+KTFb6xec2D1T2P3/XOZHWPj8cZZk/Z/vn9fvCy+pqmu+sCaLXmVE1Yf2Lpo68LvL//P1k37l3w7Mj5gdFOvNfvjAzbF46N31cc/urlh64SeTY1f7V5SdOek1Wsqf9160oF4VXxSfEl8zYj4V1s3b/px66/xfWW7t2567YP41jVlk+ONk/ZtnRTfWxlvXLN+zZZeW6sn3XnJBz+sj3/0176mNfF105t+bPp4Ten4Sa9smdQU37emsWbSmuqPSucfGLskXjZh/5I3S/JG/jg6Pvrbd68eeWDrs/ED8TUN+9ZM2rr4r11Nf95xx5KyTbvWbJ3UsCLeuHvvj7tPfjQe3x0/Ip47f8niebXxm2ee8mfDPyH4aHf1HbuXLB47cskPTV8PvyS+48DYb3dtrYvH10yt/KP23Qlb4pNqR44dGx/wXnz11iVrJm34fNLu8+c33bp4/o/r9777T/xW1x6Il73zzr6mWavjB/bFq3fvi2/Yt6Fp/dj4mvp3DuzY/F79zPikhiXH1oyN77nqf1zcDXhy0RwA8ItGGIZhGIb5HoZhGIYwhGEIwxBCCCGEMAxDCEMIYRiGEEIYhhCGEEIIIYSQj194Hh/v8/ye/+l+nXP+59x7+7h7f//od/7p/h9+/B+/+Zfv//rjH//4d/964b98861f/vh3X/+BG37zD0/61t9v+JFLfPSvv/7px7/7x+/8+mN/q/36rdrz179/9Hd///u7H/2Vtz/1ct//de2+f/n4k//+wfc/7u9/Gf3ml+/6S/Dvf9MssswaG2yxS5E6DVp0CZ8jCGZZYIkIm2yTIM0+BxxzRp+ZcwbBPFdlhXWixEmRZY8SR1RpMsSlIJhjmTU22CFJhl0OqVCny5hwSBtZZZNtEqTZ54AaZ4wITWkn61PaNaU9U9ozpT00aTNk+txyxgYZdslT5JAKDboMCJ9HvlhilQjbJNinxhl9RsyH5YgoWUpUadILT97cysN51U+SDLtUaJ1XvQwYEz6feomwSYJ9ypzSYf786iNGnCx7FChRpX3+f02WRdbYoUiLLmNmL6CfLLFKhE22SZBjn2NqnHJG6ILqJ0qcFFlKHFHlhCY9AtfEOZZZY4ddDqnQoMuY8Iw2sE2afQ4oU+OMPqELG3vmuSorRCnRZMj0RdTLIsusscEOGfIUaTAmfFH5YIlVEqQ5oMwxNc7oM+Kqs+YfUVIUKFGlx5C5i6mfNbbIsEuRQyrUmb24+tkmTY59DihTo8OI+Uuolyhx9ihRpUmbYE6dbLDDLnmKHFKhQYsx4UtqA0tE2CbHAWU69Bkxfyk5Z50UVU5o0yO4tLyzRoYKdVp0GTAmPK/PrJLggGNqnNJhxMxl1EeUGNnL6C9Hl1H3ZdR9GXUzJLisrrPMGhvsUqTOmNnL6SerbJNjnzI1zugwYmZB3USJkyJLgRJVTmjSpsfi5dXPGkl2yVPkkDoNuowJX0F7iLBJghxljqlxxojQFeWfq7JOlDgpCpRo0mN4xX/dMOYWBZbZYockGfIc0qDFgPCV5IgFllhlkzQ59jnmlA59RsxfWa6IEidLiSNOaNKmR3AVbWKNJHkqdBk=
*/