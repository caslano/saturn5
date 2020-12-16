//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/udt_builtin_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct udt_builtin_mixture
  : convdetail::get_udt_builtin_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                         ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                       >::type {} ;

} } // namespace boost::numeric

#endif



/* udt_builtin_mixture.hpp
bbFmg1P/syvdvJoFxn91ON1Watb9o0K1022tZkf/2ROTbhvJijO7ffdRnnQLkDmZDUkqlQtrQXmlMjKr+92CrumWiczyP7OSaWsBWV4WN/nqyKR0SyDLyaza36XGYX6WN+ZSc/rDpzd230m3keWNuZT4Zl4fPzMX+ZU38nsvjP53yoG/kR9ZOLNHR3yX0u0uWRZmGcffScbc1axeubfapttrsmzMBtzqORxrXQUjh2b0h+HWKyPSzU2WkVnsgE41060BWQSzX5Ys+wPbJlmxoDWmP8yMq30L85qsnOX/61kj+kMP9aBuur2oSGMRjHtjPxX5FHMivFKoDZ1y+DusyWRhzNpF5YjDmkyWidlfw0+iP3ORZWA24+harBMurcyuI9YdwFpAVpxZhQWBPlh3tbhRN9cVSrdOmrnqb8Na4NFsecFJn6VbD82m3//lVbr1Jgtn9mX+zZZ066/Fbe5Xpkq6JWnW5+8kzImhWr+8/Z8fVmJea/ZDqT37sQ5qbenyd0YH1kGtvgMN7vfFnCALBOdEwzdz/kUBzN1vq2D8yKjMoZ+2SbdUsreYre429nK6XSfLyGzxvNivsB2RZWG2a9iJJ9iOtDKXLduyDNsRWQlmj56tXoF1oirNp+D+oQH9ISp66jBsD1WNbeWNtc9xsDjGnawYsxU7207Fek2WgVnusJKIW6hZ9szrXmC9JnMH21Kf/vBMPR+F/XtVY+6+seg2dTpje6hGayuz/PmjN6ZbdbJ4Zkvsy2thXlcz+qUe/aHq2kw90i2FrGTQ6tIfMnyy5RDGlswatDr0hw21R1zA+JFFMvs9z/GlGCMt7s8F2VFfeHWlsvIyvykzCWsBmZ1Zgw2r62P8yN5iVvjPRreROxmv7/L2weiXRLLszI5M/3IVxpYsjtma6c0xDmPJsjHb3OB4yXSbQRbF7FLbxRbsU7W4ZdvWxabbDs0GdzucJd2+0dpZwN58drqdJ8vCrNm5xD3YH2llrrSvT8E4kOVg9tvqtzE/VQ2lHMw2zsmJ408XWSSziK0/Ya0rT5aT2aRF5Vtin0NmZbb168PTMAc12zQzzzOsdWQ8996VivTGukTG87v1JHkH5q7WzrgjnfZiHMh47ks7db+IcSCLYda0bhjm/CnNjqzMHo11iSyKWecF4Zuw9mht6fVBfH7s/2qG9ln97THbsK/SLLB/XKN0q0wWzeytOxPiMa/JeH1pv7h/wP5IM8epgg2xfyALyb3MgQT0J5mV2fObJ9qjP7Uy3/Y02Jxuu8h4X7f/Mnk/1hDNFi/Lju39MlkEsxL9j+1FX2txg76P/z3dnpHFMctxtuwT9DWtejZmx26ffpluJch4fplqP8R+2k3Gy9x+4XQRzF2yKGbdR77E9jeULJZZzY6xGL8UzS5XzPYbjjG1Mi3ucyWwFpDZmXXd3usUtncy3i+7cgxahO2dLA+zbUNXPMXa6qZ9B7Nrdea5sU27Q8f20JrLC7BNu7X17N2Dt3AsRcbb8m6O5bE47iHj8/r43NxdsbaSZWf2YOeZKVhbySKYHSh6oyn2qWRRzG6/09ybbj6yGGbne/peYA5q+ZWf9Vdj7MfIrMzmxZT8Cf1JloVZxzhPIWzvWn5TD3VFftbaofn5W25Hv7jIeH33Hp+3YxzIeH6tD9DvTIPWhCya2Y5a177E9k7G2/Lt8KvvYHsn42P0y+0ZY3FcR5aVWfYPlrjQ12Qh/Rn3E8bIp9X3Iuv8iZi7Wn3hDTdjfp7X4vb0ePEPjnu0uA4pV1rjvEOLS8p46SjOj+qEjpGz6N2PcE2HzMos4rDjLNYCMl7fDxU+cuB4giyKz5eogm1wrEgWx6z6f7m667Cqli4M4Ic=
*/