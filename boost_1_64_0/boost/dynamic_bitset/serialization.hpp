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
ab9fKLnEjw+3eDfKZgezCkmkEVCXvLTRR9+2RHpcJSOXtIcctiDVCNjNAGD/fgWk0mXIsJTVv62UcYpisXXFC1I4BJMTm/lHjf6xo1eUxLh44/F+6+FKU67KQhqQcSM928g27DzG8umiqj0rCUoiYdPvnMY1flwHDUMCv1MWsS6ZzWCaJY1PL2lsu3HBTmGIAWZFxxl3LuUilQuoC4pCv100BGUpIfkKRThoihbA6C+LZUCNwrM2ui5vzETuAupaOdjgYNjOQ61JMqsaC0j3KbOqE5L1NKKwEyMxj2A1eqBG5kLqXYavb2yp05zIyKRU1RHrdCRTp34IShsp6nPTKCQEKFnmELA//vB7Uomdl7orUHDD0wTH2NZHiHpLZHlyVSaga/ChOdnQXGMvjLk8w5Zone/y0xugWT4HZFygz+3BbFJWABVkHy2YEoP40Lg/awYNnaGy72wJe6mrEcIcP9sIzQtRXzg60s968/8d/b+7tIJ/rzUfNPmAXE/K5StwHL+tjtbe57gQIwPD9MluahJ9tbzDt/KOP1fqE+0Qta2zyTjhhu7QIUnR/g==
*/