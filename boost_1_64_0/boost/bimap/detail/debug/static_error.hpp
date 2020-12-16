// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/debug/static_error.hpp
/// \brief Formatted compile time error

#ifndef BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP
#define BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>

// Easier way to call BOOST_MPL_ASSERT_MSG in class scope to generate
// a static error.
/*===========================================================================*/
#define BOOST_BIMAP_STATIC_ERROR(MESSAGE,VARIABLES)                           \
        BOOST_MPL_ASSERT_MSG(false,                                           \
                             BOOST_PP_CAT(BIMAP_STATIC_ERROR__,MESSAGE),      \
                             VARIABLES)
/*===========================================================================*/



#endif // BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP

/* static_error.hpp
h3BfD1egb1ODDFIG/Cah/LJL12LWDY7AfDNubDmm8W+S1/B+7NZgtgseRr2L2Wb08YXEpxYZnaigrNOemO2FhbW4hdNhQ7mnqzBba8k/zXvTkoGK3fZC8hu1k/gcRq0grkHZqIdrsYMpdYSH+oLfhXAdbr7Az3R+tzkLlUdY/B7C7wmonfw+gArKUs1YzH1RQXmqE/jd+O14I1d1Pfq1uNuC2oR+F+yJfUNZq1Mx24nbfaippGO/334J9ZH4lGG/GpWHfhPcgdqvMllfxH4O5sl9cePncOSnwm7ot8NIslr3Yf4c7Dnck9layO8ylH2O1Ar0nWDPeuivp3A1aghm67HbjLof/ST078JauPZN4of5YfT7YbelATmv8Zchaxf7/iOOLuf1kMp6nYTfXZh1G+nJfK2C61FbUfdzr5aYrVgaKgd2fwRZsDuWevJg310akAm7ijzPWIY/VE/MJ8BIMmLrMa/EfAvu1/qJehEVSXascw7pwf1e3K5Dv53fbUh7G8wbvxPv7ENfwO/k5cQZNV3lzBbxeyOshLbM2a2YbcHsML93wD3o98OUFZjxOw/aMmmL0BfCKtiyiLyCQRm121YQV8z2wKmwVmXWJq/EHb+3oNahH4F+H++++BubOJ1QQ1ATULWo9aitqN0o5ybsUUWoOag1qM2o51DvouJvxh5ViJqKqkdtQG1D7ULtRzVejxvUiPUxebixK3bFrtj1/3D9u+X/lddMrZ81c5Z/VbJfAOC/LP8vJ9sxcvK6NdUxgkT6kcrLOjJvWCrrFkaMHF+q95bY6Dp5PTvLWwul7nsZWQQXi740Udc167k13hqccrEvStQ1Nup/wJFk0Kmb4WaNYY3omQpnZsDv74yOsuaEA8/L6irLPbkPj0wPnDuuZ09pOLcnnOJu8m2Nb6drYIltud98hqyB3aDrhwZLmBWLy2d5exY+nOl3d4WvLTMqwbWFPeUej/kqnGasCxqZOlbGQPRe/FMZTKpfl2iFvWCJJevoolI9A07DyGsQxmajX6zx07xd4oWxVeyzTBgFDcLYYvSvWus+KWEY9FNo+UnHzzYr7svdvzqD4w+K3x9kiZypigW6Z4I0e3spSFu+tfZtvvhvET/ezfXl6tq37ZJvTkI857z/jZHIXN9dzk7fS86DcX92mmpd8I/Apem6qjxxf7l7BeUZrAcfUx7Ad6XzobpjVZOYZcSdyWzLKeJOy5dZlzRNz/clrFYJp/mukTjXyb3qF1brnt40dGfMkvX1KvOLsV4J9z7fKMw8P6SfgkrXfcLPSbir3XM4UXiYm2jWhF0nYe005/8tLgucEZiucV4l9oN9zXDzKeYBd8F4T7HuR3lPzEOvz4H4+9DI7PmF5HNBXFA21ffEP/sDtOx9Er+nEi5hBs5KA4HmmXTvkzDPMnufXymTsnfS9Vk8W8JY7nuUFVCfu9nqzjxDDeLa14SbND2Qn1kazg8lrk0SxmF2HTN4ufFtTLrGiNv1PvS4tcPG3qQrTer0OsJuJ+6/kxCaJu/eV+m9g2naP0v3Y2tcdksar3aydO3zUHG/wVeEnw+pjRm+puo2Qjqp6xSJKdsN4vcTya95hLVE0vnbuA6uz33Tt9bIQyuROCS4AXfBetuWervc7eZbb575uwPPtHmfOryT7P0ag+R+9/pKuWfwnfRXCetB32TC1/0YmmetVB5MUJ8i95G9x7MCfoJ1pULCnZiw1MdzZD8jeZ6MqDjxs1rtNS+sZ2h7aegzNFP0N8ZN07KoNPFoKfHIwc/74uZ3CSHPGGFmaZg7JF5/jJvCfqoWPGPXuDN9wXfEMinH95iv8JnyWC9xfEGfxWD5TaV8sDfP3um+lrjxP3s=
*/