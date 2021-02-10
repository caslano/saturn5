/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_TAG_OF_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_TAG_OF_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <cstddef>

namespace boost
{
    namespace fusion
    {
        struct po_array_tag;
        struct po_array_iterator_tag;
        struct random_access_traversal_tag;
        struct fusion_sequence_tag;

        namespace traits
        {
#ifdef BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS
            template<typename T, std::size_t N>
            struct tag_of<T[N], void>
            {
                typedef po_array_tag type;
            };

            template<typename T, std::size_t N>
            struct tag_of<T const[N], void>
            {
                typedef po_array_tag type;
            };
#else
            template<typename T, std::size_t N>
            struct tag_of<T[N], void>
            {
                typedef po_array_tag type;
            };

            template<typename T, std::size_t N>
            struct tag_of<T const[N], void>
            {
                typedef po_array_tag type;
            };
#endif
        }
    }

    namespace mpl
    {
        template<typename>
        struct sequence_tag;

        template<typename T, std::size_t N>
        struct sequence_tag<T[N]>
        {
            typedef fusion::po_array_tag type;
        };

        template<typename T, std::size_t N>
        struct sequence_tag<T const[N] >
        {
            typedef fusion::po_array_tag type;
        };
    }
}

#endif

/* tag_of.hpp
yIpGQUJRMqIN00JP6EO0frs4X9OHYLUK4vUFLd5QEF/0/t5F8QmwIRC1IX69bbhGFg2JaisFz+8F/65M9/z1W5qdr+aL5TpdR2ehzfEpjZ48o9/b2sL6pxGNpNjYudMz/+kz/xgC+y3lTB9SzY2dMH4BJg1/yVuKg7PQe+j08jHGaQCJa1G1GI6ouGtyw/9quTa2iUxKte8GY9hH7nwlF/FimUSJ94OoM9nmnF7a4B0Oy1eei5MpyB/mNLYn9KgEQiSA8iCfCUlVX7k0VGuOXrhgJ2EyW0XLdbSIvSXDCFin1RGIVRzwABJrw0QtIL8sot7BZbHEFrD13CtQ1J7mMMiByhIsshR1VTrVoa2mYbUu4FoBwsw2cmiBT7FqKliALjXie1Kpj+1WUwaEWQVkCPdaAL+OqS6q5YQUoITN8canpkboj8Q2qrEHHuQFdrU8UO1i3NH0O4B3Q3UszhgIfJuw43NHsOg0mK/OPC2uauZO+o6QPmjDK1hKqX3Pi2rQTFw/lgJZd2eghdtHldumXYjOjyPxhtsoOcwk6OCh2cMM4wXCxsF8/PTINt5ykRsbo6CNMiXdUe3H3Wvaznx+mJ4lwznYDFc2L+7tmGzdV5IMAN0LKYecECsBHnmXf9+nbWssYkrW9O23m6DE
*/