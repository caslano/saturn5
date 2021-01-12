// -----------------------------------------------------------
//
// Copyright (c) 2015 Seth Heeren
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_DYNAMIC_BITSET_SERIALIZATION_HPP
#define BOOST_DYNAMIC_BITSET_SERIALIZATION_HPP

#include "boost/dynamic_bitset/dynamic_bitset.hpp"
#include <boost/core/nvp.hpp>

namespace boost {

    // implementation for optional zero-copy serialization support
    template <typename Block, typename Allocator>
        class dynamic_bitset<Block, Allocator>::serialize_impl
        {
            public:
                template <typename Ar> 
                static void serialize(Ar& ar, dynamic_bitset<Block, Allocator>& bs, unsigned) {
                    ar & boost::make_nvp("m_num_bits", bs.m_num_bits)
                       & boost::make_nvp("m_bits", bs.m_bits);
                }
        };

}

// ADL hook to Boost Serialization library
namespace boost {
    namespace serialization {

        template <typename Ar, typename Block, typename Allocator>
            void serialize(Ar& ar, dynamic_bitset<Block, Allocator>& bs, unsigned version) {
                dynamic_bitset<Block, Allocator>::serialize_impl::serialize(ar, bs, version);
            }

    } // namespace serialization
} // namespace boost

#endif // include guard


/* serialization.hpp
6n5p8/BQv3SIctnR5L/TL6UP/3n6pdOTfv5+6dTh4f3SHMzefqkEs7df2qDmLhH1frNOkn6t9X4bMpAwd0fWe1KZX+Zds80rXpBTUFTpNxK+V+f43qe1XzJuPWGXlBaXFc8qLqzkGwnV1OcDWp+t30aoQX3+o7jZJPXZ0iYIo/p3g+OzRPeb1OkD9C2rm/936vQbP7JOS/0zZRvRv2oZpnrrtCmr438/6c8Kr8MNMXvrcEvM
*/