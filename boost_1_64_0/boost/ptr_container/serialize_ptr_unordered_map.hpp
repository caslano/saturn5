//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_UNORDERED_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_UNORDERED_PTR_MAP_HPP

#include <boost/ptr_container/detail/serialize_ptr_map_adapter.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_map<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_multimap<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_unordered_map.hpp
R0Hu1G7qgMKnh9bdJbcA9uOcwgZU/DvtWID3lflWTpNKnfahWqE+BD5f7UweKzySli/hSJmiqJx+6n1UBSz0jGTRwLAiyNr3qQ6v385iICDxxHL6CoV/I1yyfZPKKmPcCPrL3Vw5s/hFqsZBgwDNOTf+MLaypDxbbAveymdVMYXJUzqhndzojb04ps6GaZhhaZidalSw3pThIgo/6l452BONP4js9rZvI/jexnKH+lJu7w4sQ1vozqqctjdcHl/QehSQhWo9VGzny7go5IiIGS0awQkP6MYKyB9Z7jPPSaAOJsLVh+G7nAv2+EcTghxpXOxND97pxjOCntIsBydLTnDNgLK2wO9Qq/GRfyf2Ft8ZSemBanCp7ExIMt42p5qNUcHq4xdPp77L5x7qbaVs0N3TkTE0ZC5CZ19QF9gUqN4nNXwjkUznyyjiUhlYUjai707mTkAo2y68xwCgVhPsdFHsekT457ik+TaFvyAG2DTRXi6e+9qpTAT2GbyTf6g59t5Tc+rh9C8Hd3qTLleDxwm3KBcy4lomhJ3/AQpT5nnJgzJWcpuzfBk2ZA==
*/