/*!
@file
Defines `boost::hana::Applicative`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_APPLICATIVE_HPP
#define BOOST_HANA_CONCEPT_APPLICATIVE_HPP

#include <boost/hana/fwd/concept/applicative.hpp>

#include <boost/hana/ap.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename A>
    struct Applicative
        : hana::integral_constant<bool,
            !is_default<ap_impl<typename tag_of<A>::type>>::value &&
            !is_default<lift_impl<typename tag_of<A>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_APPLICATIVE_HPP

/* applicative.hpp
uD4TbbdrdeXPY36/Hf/+Tvn7VfN7w8Zfx+8RHvfySv/q/oFkduoUVgpxov8lYddr+fePO3XC73adzO+3j9t1kr/LOhl7mXr75Cb/3lO2FCEOlBtB029F9O6A4rvWuxZEYdiefS3m0etJiNI5VP7Z4/9f24/Q/ccP6BsaL0bTHq+72VJiTO3RtEcyjY6TbfU72764vrVSYeFsZAfCXU8a5bK5uaakRK0YnBdS46YerXDnw8DnvPKV50/Rfyl5PzEN3kf30DeBvqnrwNfjGvdRxqGPJUjxQt7ftOxDiRJ29snHEM6Xc9x93jHj3NPjb/xK8buWF+PPa34f2vg/4PdYvo6ccOQRv4fl8aETtjyK36U8Srysv8TL+ku8rL/E2/WXb0EJOYT8CVUusV/GfhVYdXxSnQ8vatwda9100dar2LuC7up8FcumMf/EPiKk6VMDg/vvA2u9NKg1fbsAffnIqEwqUa+gdA3j1rcerq+ku/UdmvX8E7yO6eJpHVK2nrIxCNG3BbXoqu2gmo80b6tEm6PfiSVNre32FgWM9SLru35wz9jTdjtOBw+NdjlOSldNq7sL5tseiDbTAjkgPOWtJMwbqY7TjImC4fUupD4UA/FCjcuHcDXaSpC1RsBTM7rsE+P5yiqx3eTNsd2kaLbkFbKIKdpbY1p2uYL9OtNqRItIC4XFHGi8T6+Dpm42hQFNfxssU98ZdlWbC0XyMyhmchqvxturhi5rC7Rlvn1IL2qAbsNFokejhuHi/TmVpfrLzJbVbneT9fuHCU+VqhbmqT5a32OK6DI/Hde/ksuoUlEpwRdsme8H1Tea8fPMOZLWjbnx+0OcOd/ySGDdPR/OkEcfRZid93Kpl2n81UcTfvf72tQr9Tpy8jG7/+5EtJ6hzffkt+F9LmwR1/YB6+9hxVn+W49VON1M/M5+xvS7UUvS1iL3ncPRqspV5Wqp3eFlrSIbxC5scdKGs76rekT4Jz+C8Luqh/ZvlPqNg0HWlSWF7m2iZGG4GxZ3RIVBVgNLMDLC196+S1piJRNdtb8hJc6SG9xfQ3Nri378g9jvj9vrcz/uov7KnvBosgmQsihXV0rKLYHr8XijR5aWsyuLudQxfUe5GLikNHiKZSb6/BurOf7/XH5paaFo/FUmHlZ0WVI01x9Pv1c36FxdMDaDZ+HeJOueU4Rsf/nRoPtnJDHv9+0Bzj1vwX72F4XZ5TnKyFKP2pvdxViYfcpXE306z+TKxdyi8urEW1FCTsI387Zc5SP/Ts3I9/BEjvTEOpzNaFebUy+Zju+uSsLORb6XyqW3bGjbNk09/QvaeZum3MHLiDkVtOBJj3KVIj9r1C5ZOa9tr9HY4deT2lbvtV+wNXgBCcYLaKxeMBq2N+kO9gWbp15w6gXT+H7u0VzWWLBbOH2G7z+02/KHdGNsChf2yGlZvgsOFz5typ7dbdmRPzlKx/tFj4rHhCA8XqZeU6JeYUbJY/LTG7uuF10VaG4yflLUS1i/lhH3IOi2xSHVM/W/w5j3hgsMV/9/7N0PfE1lGAfw9947s5g1EiM0QizW3TB/Ui1JElqSpKVhY2N/bruzxJIkVNLSKkm1WJKWJElaWlqSJAn51yxJSFpIS1LPOee9z33v6v621T23T5+P26d213fnve9z3vec8573nvOcjnwvq9VdPu+NlTY/Xd34Msenq83O97wo5XvMfhJxjMrfVJpB5XosU/6mJjN0nCfvr8v/9YxFub/xoPL36symyxP+zpVrnlYp7vVMij4v2tUP1L/HM7gprmWGqsvgWVzeDmaqy8jzJc5HoJh6tsbPJFL972ejUzj3ocff6sWMd9lmDzNqwfedKqbM6qZzrow=
*/