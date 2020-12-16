//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/targa/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// TARGA Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , targa_tag
                     >
{
public:

    using format_tag_t = targa_tag;

public:

    writer_backend( const Device&                        io_dev
                  , const image_write_info< targa_tag >& info
                  )
    : _io_dev( io_dev )
    , _info( info )
    {}

public:

    Device _io_dev;

    image_write_info< targa_tag > _info;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* writer_backend.hpp
iC8BKwz4jd+lKgGIxnVPdBcAaeDtBqqLv2AqsUSxABSxwQ3XlzaRX3eiwdvzXNr/LgKim69dPSwF/7AfHGA472VGApoGfgLU6XNeJtA0dvd+j4fkhz78NRnCDQ9BP34mCwRXvSyzi835qwNolwrtVNBWp7L45Isuo32nPFnCoWravYl/9Z+yTENLNXGW17H4WlSH85xRazh6hk4h29oqF5Hk9qt2BFXh6ntlEw+PdIbErhGycbgOg4vp8KJQb80/HMAXZVKCODGVfsUmxV+fGFAUHOEsSQ3A7vAnNtymOh88GsTMRiY1H8NN3maKmiCtJjdG/Om2uD+Cra/x44MlzxKaM6gB1V0Mnw6FrB1Lbrh/EK6itEVt+L3fAaxX5h2VKbmEGOCphr1noKeGbmfudreaVRMUH08QYmlN0PU5M+dWDw+25NI1kYRPsKUAYZnYbwQVtXRqEMVf2e6r++mpvvXBh9TFFmWRA5RU2XjMxASFKBW/CVHIZaZdqxOdJCWotddbuHLHQIbE2+bhxeIwvG4FCmxPj1uXDYb4E/SaqWKyio86dpgPhVGZesTUxL0iHU2/kBy9RbIDpI1epDcIqf1uQToAJHzf2HrZbxxB0jtTILW9jW/yRJ8pwbr3TaAhvQ3S9aJzXrqkb7MW7CL2ahtKZXwjTRT0XrLgb7QWPiblX3PEqx5ZC+bLqYe5DpqpwvE5jpK7A4D5ex9mATDTjO3BBqB73RgO38hLvVLxUyS9w8r5Iovq0C1PTr5szxTwvcdj44MMWZij084wffGyKSFW7t1ntFi5t8Krb+UOa0KqkZouK/dxsnLvWsd8m4TeCwT1AIql4tKKZ4ZT8fpSHQtUV5M9yfWpazb+1rtmYqM5DavnT/GJ+NiHkJPolk2jBfSnSIDvCC/8sM1q31cMXGA8wBhIFVi9OojCmHB7JtzGqIfeBAkBpJxHhYf2yZyGBNUwie6e3cXML7f4Nl7P/+jxsCp6wxTzLqx61Bh585Gmpk3zyfWLGHOkDW5jbL4HcQew7X9w1Ee15U2RNp5qbA+qVn0Ix3Cxc/pjroqFqnIaVdEngpRBIPYuYcPFLBb9soQqCAbMoUXzNUkGsKMWy2X2y4SiHWKkWCDRB2nheUljrIVP8nmcX72//4kKm8gnTwd7i4bskMBiMOdWwVTGYbX/rHpkyYdv4rR0yJuqAmmKgrwqQDyhSnYZHmiYGItlNZsLq1MPMfZmMNjkzlfGR7nDGC7V9lRzte+6U4xxfgd5ItxuoOId0jfvZY6daqD9DxCNTkZa/VbpVPx7snFLMUQWvnnBfZFsVJJt6lNBkPoio3CVVDyBMLLDQraupXRHTZOPLzkta+Rx1H/kLOCDO328pBxSENm4G84kMlVVljTiAkZNL+X9q1ZP88nWKUJ4BsTJNOzNjeaZn2/IGEx3IJmKpLKvFEvZi/tpzqsm3dOte2TMWoJcVKWmO6i3pVsSGtOw6AAdsCIPZo1q/GTWhEwyxlY0kBqHEohqdzpn228qrcoRU31qWG14vTsQbl8X9SK+1snqKYdEtw8aYuAebggXjZxP3k6lNporPB5dXvqG6l3FBwokYLk41BOEBqCyoRyG+x9wMxn1XZDvCcSxld1q30a4RVeQMC5eR5zrBM6Jvi2U6/ixWlrLlVuJap/7xBzBdcRUxg7hxnwZiZ74iKv4+kHqXZlBFrNuxa5wPfgbqQ7q4g8++bUJvkR67GNfeyttnOzsBaS01z0WC4WpcyyWGxFG/8FiuRMhG+EBhAKEEoRnEF5BWIewDeEwgkI4jxCK/GkItyPcjZCLcA3gNyHkIf4Ewk6EeoSjCG6EcwhBsy2W9gh9EW5CKED54/A=
*/