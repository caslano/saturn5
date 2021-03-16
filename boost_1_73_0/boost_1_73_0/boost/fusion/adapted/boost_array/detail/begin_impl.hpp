/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_27122005_1117)
#define BOOST_FUSION_BEGIN_IMPL_27122005_1117

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
PopJrnIWxdK7pUGlDY1NJlmmsXogE9jJ8PT9ToY/R1uSXTtwoOlu2pLcDbruTjZWDWMzgS0BVgtsP7BGYHWrKSIwSEv8nmiX8DA3aSmMUmFRiTOYUixZ29q8hDXFzvFQS7M/2X1/VJ2pSs9r6a7i5GQmqT+ZdxW31dG7SkDSEkWWKcCmA1sEbDGwt4E1AIvnygtGvqe4Xbwysz2jkUZa+1jYNbj8QGigWck4RH6lqO4zPGsXbYNTk5+cVmbwm9U=
*/