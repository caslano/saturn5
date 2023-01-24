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

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_CIRCULAR_BUFFER_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_CIRCULAR_BUFFER_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_circular_buffer.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void load(Archive& ar, ptr_circular_buffer<T, CloneAllocator, Allocator>& c, unsigned int version)
{
    typedef ptr_circular_buffer<T, CloneAllocator, Allocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    c.reserve(n);
    
    ptr_container_detail::load_helper(ar, c, n);
}

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_circular_buffer<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_circular_buffer.hpp
qNunpCkv9sa2iHc4Hr2pfvfrqrTmLsNH3rnrZ90zjLyqNP7Uh02zbK/e2xvqNklJ0vG2ws4VhRsysh8JTcyXXJT+2Cfg5iwtN+WHMRb+mZ9Lpy0SbB01Tt/90tnDuVpaLoYPxysZlKwMqEgU2+Ay7ZaroIfjhhX299J7dN1Hnl89vdApZb0Es8BUaU9aCc9Xpe4Kva1fNircmn+/RjSGb+f1xpP+QXQjyTyettRKdeWm07vLFojzWDmlPVm5jO+saPBZx5e/ms8cvOAYE3T/zsndcasvZc4JbHu+5lJTwvrXOytXqr2MUB79TeaBfZtl8/C0cLuh2xNEtALaLG9Uvh7vnnrz7AiNdXHi3TJbP9m89Ev72bU9wS1++02zA45ZCTPjk2+ezbyQ7Nh0s8Rk3cbgx5ovJhUufu8dk+TxuSyqx2VcYvomy3ClgEMn4pace0VfWVtbt2hI89gLPOZdymVubc/XXhqbHytop7t5rqyoSdGyc88XfP769OvQVbrDjUuOXby5IMYp4efcA4e/lURtHTu/+VVGTql/w8eAkDpfxoulM5/ulvfvEr+QKfi0oXHZHc1Aw0VPFMROVy1IDiyTaXYVML4Rufrnj9hzs98Z7ok++URphtiNYOkQnp0bt3nfqJjFs7XbpcS8XvPTeL7Po2OMdopc+Jne7XL52aSFvl931mvFlryUbQ0Ve/vQavl6t4uyf8ccs76T
*/