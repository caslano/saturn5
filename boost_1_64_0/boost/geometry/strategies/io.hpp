// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP

/* io.hpp
K+wCH+4CP9EFPtUFfq4LvNwF3pDwgQz4lS74r+iCf7UL/vUu+D/tAg9udIaHN+z63/P8PNL7Zf4JDee/T30Bw2dkfiMF3/5Chj9H5r8kBb8u4a+V+e/R/DH8Ny9i+HXk4768hX/1xQz/KuA6aHj4Eob/VMJ/k6q/ATiFT8h5+okUfxIefsJP/6kvZfiwB47wMoafkPAZGYdBnum/nOHnZP5SCn71FQxvpOjvl/DwlQx/gYS/VuP3MX8S/g6Z/4E0fQn/rMz/bgr/pxL+C5n/xxT+8KsYPvBJP3/vkfDdDryP8V8t5UvCj8p4/6pPkjbCegbh4zis/Rhs7Y8hEajvcHDo8nwPf17Z8uNkcV8+1SyeXyYzSpqPJ439wSjtCZqMY9iFM2T3R2Shl2CD8Z5vVpvvZ2qz/m0A7LM53lTo/aydc7YWFxejKZj6Pioz8pmC2YjemxVr8x/pSpOJnCG+evO71GuLKb/LA8OLxWo7Ogbbdbl8TPtBGg28USes1MKlYq0cLxUvoBIFb7Uian3YqtMLgegBglA+8CDKlyuL6K1WKB99sPDoRVz0bEVI4xQSc2EtispRWaAJ11O4DAveU37/2AFGOWygzLUrrSg8aWMhLNBruErE+Pko5Ec8wrgRlSw42pdOU2tof1Qj8gvOUwm6XFSypETnL3Fn6jS8RiG/pccoF5VKIfYjOt2o44kNTif9baMmcNp5i26HRCT5qrRON4j1yFO/2keF8kEY+eo0p/+acTEkmW9ebrSs/FjtIlW62QiLdjU6v6F3J2Z+qxEuX6hwb9n5YI72ucSW+ErbIOqFCpqpy5EohwLQutyIzHyQM9KXmiQdYkCblxP+K/WwVm+RuDJJvJJJiUiDkCox4dWxaQW8RtUv0NwohuWabGO4XImXi61SMjCA01aSpkM9JFi1muTTi5+QfSkqXjDKl2LxJq2ocjEiASg2q5dlfrJvVc/GsCMySOBhaUE/5oK0ny0E2bISTRBulyycgtebJHXxUtiuFS9SdcUF6CftF2CJ42eJOF/NgEiJHdpY1R2XzBChD2IiqJrgwNFASFMqv1LGUF0iP0VFSAN27mFTTGoPHQxUs9iUD+doONwmAizExRp7wJci8UouoUcWCtwZBVPepAYTeKQfahFNCLRFw8krXL8YFeJSK+by9QuVKDwf1bT2sNpn4CkXDgLjuUNYPlwpGM9iJfjtuFVfDok1qAt6AyK9BlE8sHSZ9GLcoqrt/ha8F+hRpgLzb+VrTMA8eMui6wroNjOfWlgT/ULtbzYrJGAoFy62If4GPglOsUDvYuM0BiFdV7leKMNhh0mbqkfgh9DoyexQcPYLMlqn8mE7Lhpyg8rkixLl+wfd+rAiSPm28Fhq5LN/BVKfPn79K4BFZ4lmfmshKrYy8CELZC1Adj34JPqkJEsk/4VFadN46TTaC9VKSWioND6QZT9EZdkTcVb/x1GVJhMml4+O7kgffo3EAh1q4AmxKyxcbkW6RvT4QtS6FNEMEkqShNv5FTIbX+lHje9qJBevRWokXq6IM50YgqHgEdY7qCWLbiKcBbKNCqIe5jwDj1Qquoy7JMQRkA7KToWqiWrw23nXD9Qr7DZSFm3SGWzSKEWlTRrg8yDzKqi6QK9mGfSg2Av6oVRtUeggJRgCL1uW0DkftQhJHJkti7mc6ktdLpT5aN1CxRkPJT4WNwreblR5/torA0OT5zVJQlpCE6h8aWNBcYsHTWG0VJKOqONB0BYRXpbPh7IwQS4qjhmP84GwyUZ3GQR5zdCmp0tXeu670I384w4k0KFDUKEDIlle7F96spQ4QDnaUgOqCi7tO/8yrvGh7kR3Fmg6Forq8MCoB2s=
*/