/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
6jGH30I/PAUT4E+wCayv9VRd2EnUWt7NWadQ3a2ALFJ3X9f8/DZMhO9ovn4X1oHvwYbwfdgF7oW94SdwLDwAp8DPYD48BJ+Ah+FW+BV8DR6Bb8JvNL9tMmeNkke0nCUj69Rf7B+T9HsX+uEemAjfh9XgB/BC+BFsDT+GXaHfuWMRiwHYASbD7jAVjoVV4FRYFRbCWvBaWBsugQ3hLbA5XAUnwq74LxM6/p4SPD8U1tH4jEPS
*/