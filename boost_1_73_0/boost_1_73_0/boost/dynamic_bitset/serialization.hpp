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
tx1MQ6QGUSIC4hdMacRsNRPcQ/MUNJVr1cMYJ0itBJBbwmqyQnNEQ6V1o34dj/NW1hjJuBC5GufbVHiVXj+JaoHerMkGRKNBC2gVdcHIu7AWBSvNiinCzaZd1UxV7s4tNMiLsZCgaF33cKjKqOpCoJD02XKNJDToPdNmUYIrY+2uEus9QUxrD1S2kqM5TAvKFQIT70LLCyqtvE3E1kqfZZvyF0q2870AwdErGPgJBMkAVkQx5cJ1kF5G8xSu/Tj2w3QB0QX44aLHuwrCc+QGQ6sS6H0jqUIvJLB1UzNa7Bn/oZ3ueOklnM3jaTRLs1mUpH/Mo3QCb2FwfAK/txyJffzzAAY1W5nKw4n39sQ7wg3zlVGiNpmi2tQYf0gnhYjJJYT+l4nzHHZ5CMNkdJHOsJzrNZbOFkuiGVLqbQUk4aqk0uIkizCaJUHi/MR4XrcFhVNjuGNh9dGxNnKB+0/9GZoTOKjQSI00eeaLC1iwFkeVVVTIQA0H+bpQo/fW8vkkOYuDWRpEoTMjWA0CjWDceomtgT3K/8ZaWz2ki4kJ65U8ja0xqriayBSVtxhXFyo2q7Ra23ixXf9pqdJdQ37DuGN1jYyqN7CiNlOsBC6ASimkI3L0XiI/rM5jl/o5gDoEGV+j+i2p2c7fZ8E7
*/