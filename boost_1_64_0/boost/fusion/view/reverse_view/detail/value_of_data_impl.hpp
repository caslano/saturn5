/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
h5YxYkvR6PlWtABa2hhpvz+4nEGYc4kJ5rG4YZO3nBemW2qCvcxWZos3C4NlJpjIbOPEGhWE+dFeKNIyv8p3kOrzmaAEi+ue6+crwtxou5j1aNpgBNW+wgQ/MWu/bCjVYF9pgrLM/mqXm/L0oGViRr8XieZDm8AsxZi4yTQuq6Lj6Lt6aO5kRu9NQ/OireVWxVWNalhtgnzMhh4/mZ/i0J4xu+35/THN3xo8xyRLdv75M55jkiW7Z4UWz4yfY7rRjMz4fRuvRpuBnzVyWavenwMtDzN+T9WN5ozYsmTXVSG0ehFbjjZn1aEG1OY6EzRnFrukvrwGQivMbGW6tuWEhdGqMPvvjPnyHHO9epwXrTSzVGn6uChPtLLMTAUy0bjYN6jHedDyM+v5nWEW1YDGa+/RoV5zYbqN0bW/X7jmDbWJxmsYNP7wfpo/NF57kZi0J4TZNqnHudB4DRcmvnlCeaLx2s+vnXNAGGxWj3Oi8dr3n5qahmpA47WXis2wi8YajdeecVGjP6jNLdE1HHSUzkLzh8Zrf3T8y/fCwhpx9q3RNViqpqhFeaLx2lN06pJVWFAjzuaPrn1IhpFrqQY0XvuBLLkq0Vij8drvmjKR2bZF1/DHs+Uemj+0KrzNXk0/CwtoxMH26Bqq/WfzTcoTjdfe9tTZscJ8GnFhNF574torJamGX0xwkY/LplOraR52mGAIs7R5T12jsUarwCxv4qF21OZOPB4xm5a/dyeqYZcJejLbujbN78JCaNUVae22Tacx8+yJ7q/z1ph7lAtayhhp3xj7jaJ5+DXyWV3EKk4K2mlc9tM+GS16n6w7gPtdsmT3y9HU4twacX4NC6Mdj9hPaBd2xNYkO2iCDszO731/g/o7hMdGZvTeGDQvWi9mzQa+akFzFMDPG5n9vKDuVRpPtKqppK1M8DyiGk6aYCGLy7zVOp1yOYWfDfL+6uVLSXGn8VyKWef3991UH9pSZvOf5TcJC5yJjpt525tLGJzFz32ZLZubPTPFoSUwc81u/gvF/Y73oZnx+9ButE0x0nacThdpc3dsMCiPtz5ld+y0LDOGCdNdwM8YYqR96PfhJcVditw3jVjFifWKCPNdNkEzZpPOO15Qm1dMMIlZ7VTmHsICaHtipWVbE39dmPumfIZgBdrZ3C0ukd0xwZOU0sYnTVxOeT4yQSGQtqlp6iTK5XG01XLfry/MmcxaziqaVpgXrS+zHzsoDmG2J7gfVKR51/T5jcblD3lOhMbOiTBPtHhmdN6DpvuPepwDTS3OoxHn14gLo+WN1LASLZzx2gRhrmcmOAjSum5qOJ7G7Dl+/s6sQKbqFBdAG8zsfqcmFajNFybwxkj79urlWTRmr3BuWS6f/ZPSCIM3JpgC0o5/XPSA6kPLyIyuZdCCaFZm3uXeOcLgLR5XmBV7cSiHMDtaYWafV7xbJ8yN9oBZroEPpgvzvsN5YMbnIYAWz4zPA7zHfTIz2iej2dASmNF+F82lEedBU8vFr9FmGE0tT/sHvK5K8dVWoe1MMziVMPiCx9tYaUX//uEM5Qlm6ArS3COuZRYWQvuH2UJL+UNUe4wZcinMdpVsRGMda4ZtLG6qu+Z/aY5SmOEDs04PSwap9pRmyBAjbcCLN9mEOeLMsITF/T37yU5hujRmyE2WbNtEiydLtm1qxPk1LKRhurRmSGDG58+pYV40tTyDaIMiY70are93G52UZ3ozdANpe7au2STMniHa5uoNLSgOzciMr88gWh9mt6be19N6yYjzx0x3pNZuYb5MOC5kyfataL2ZzRxrmERt6sxgYUbfxUfzoH3DLFePY2upBrRyirQC+/Wbad6zqOfiRotnxsfaj+Y=
*/