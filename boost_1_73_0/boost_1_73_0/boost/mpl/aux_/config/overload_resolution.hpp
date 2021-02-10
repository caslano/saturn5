
#ifndef BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__BORLANDC__, < 0x590) \
        || BOOST_WORKAROUND(__MWERKS__, < 0x3001) \
        )

#   define BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION

#endif

#endif // BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* overload_resolution.hpp
9AKinGxYYwLYotowf3/T6zpdONP8fFCdzEHyGEqslRKVDhOSKYZoVgMHERWbDUY0pELLuhxPF8vJLLysKs2m86Xl2l0XzBIqH1Q4YbWoGg1MM64LItMjDC73x0UZ7pnkyQ4qlYAkGpu4UrDKB2SD3Y4d3lap0G0jeqpjEaCQQgsqsmsDBzA05Q8+QEcIpUP4iWXL+ILUzNEaS4dAS5lZl/d388Vk+rlljChlBT6+sq6q23wR7K+HTaVDpWDTHdUOG+E3+6WUfNiu69c5qhC5whiXJD0vYNQL7H7ix0kyGLh+P0lWKzaI2cC23VUS9yjt9WyaEHdlu1268jzf9l0S+Mx71olnpniJMpF1Ej+yjjdinf4vfwBQSwMECgAAAAgALWdKUtvlN+IEAwAAnwcAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDYzVVQFAAG2SCRg7VVdT9swFH2P1P9w6YS0oYXESZyULkWqgA20aVS0g2djO020NM5sh6779btJCgWxB7Y9TZpUtf6499zjcz+aWmksZ0YeO2lRZQp/vsrNWmlhjp3zxWLWfcGHs0W/OC2W6ACssbmTejvT1Ou9X8Fc6jupXVMI6aRa1uUGbwWzrMfzyCGByCcwRQilix/MFqqC
*/