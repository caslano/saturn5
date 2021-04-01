/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<struct_iterator_tag>
      : deref_impl<struct_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
NobjO5StF/htklJ7mt3JNGfWp5LO6ZWiNYhE8+kK1J7a3WWRnpP+6tIzzCHrRt0KDJyVlCyyMNS/QPBuHd6cG0xLK2atPJ73L2Pt3PeiiHsNX2YnEkQBpeEQP6l9axuXG5y76UXp49tQeT/ZuSixze7i/bwriXVGzxMZMmDauMiwMjAUSwHl5SUjIcFs10SRQntJ1L5tBna90qES9oPh1bRODLDIDxQU9zS7Mgqbbn8Zk4cHv0k5I0tqqVW46VvHmY5TT7oM6NRYCUf7u6X/ZcK0Tr4Ist+9508pmlgvjnBpfavP32Lewjcb36z51PHZodUZMxk9QIqlJ2WvjV4XmB2+46df+kPkKlqBuhLqQBNtzSZSE2HDKq8+oxPb/4oLPcW8FzEV+pnQ4KZLZj1BjcmdErlc+dBzN11o83v67I+wPxgiJnd11xDhwVZzLQmNDZXD4Gln6dh04NhSVsJbxDOlrsSK4gJaTWAq2Y6XC/YVHKCyKOyKNQUPk/NNFeRrwJQqEezmGVuK1PH9QglqfFW6aMAfuCJwoDh5pfeGnHpSguX4IUjZ/PVUlw==
*/