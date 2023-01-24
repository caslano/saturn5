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
ZY/0tltsLE48LTHHnhT3yLSzJMU9f6fkxG12EpN9jznyG/BrXjruTNDsJv6pNruMQ7PlvL1wPw7ut6Q7j+xvQI8k/Ix8sqfixsSF0aOzBquYYcZbyrSwKBILZ17mKn8GHV0+L0IjE9Pb0pFlFPQ4Pc0SzDdxXCZQgya5GSvDxDQyPoKiRlYsFTPAxUzw5yHYR31gUzUrDc2MI1XNXM3E4msiG1AsgMyXB1+zK5zVusLZFmIBekC0iqA327TxWkonGkOaZRMPtWKmcJTPvc9qZwONQqNoSKpzlXcMtwAGWp2LT+u0tLpWOZiZw8pgqX4bxCJbvXcSvfv8ZzDVOTBUfLnieHFLKjL7m9ibH0Kp5boRnAY1CvVviEO4A+o8bINqrxU1Uz1Ksm7PDdGH6iKGguVE4HZG3y+KIjP6flkcnuH/CsyT30bDEn8FkTrV3HUr6vo+0XXGx9j3GHi3hPuGdMmnotpT35ngYMyqOD61rZJhO3GFBPLE1bUi2UF+H55l9f2jKDKr77HicPF6FrgnJ0SDA+54Nia1EDQq3mZownKSV8PBro54UqOapH5LUcfizcnRljQuJGxNhJCnalzltK3FnjCfr8IS0RVNHKz0Vhhshx4JO6eWUZJqNLCID/nf3/UYPMoQg4RukvvHmASlEhUWpdQEsIq2+PK9+GUcibRDjAsZyfZ35EhsVpH/dddPOezfL3ynkZkCsMKR
*/