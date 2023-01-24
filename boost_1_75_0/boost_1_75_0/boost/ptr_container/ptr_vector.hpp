//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_PTR_VECTOR_HPP
#define BOOST_PTR_CONTAINER_PTR_VECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <vector>
#include <boost/ptr_container/ptr_sequence_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

    template
    < 
        class T, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = void
    >
    class ptr_vector : public 
        ptr_sequence_adapter< T,
            std::vector<
                typename ptr_container_detail::void_ptr<T>::type,
                typename boost::mpl::if_<boost::is_same<Allocator, void>,
                    std::allocator<typename ptr_container_detail::void_ptr<T>::type>, Allocator>::type
            >,
            CloneAllocator >
    {  
        typedef

            ptr_sequence_adapter< T,
                std::vector<
                    typename ptr_container_detail::void_ptr<T>::type,
                    typename boost::mpl::if_<boost::is_same<Allocator, void>,
                        std::allocator<typename ptr_container_detail::void_ptr<T>::type>, Allocator>::type
                >,
                CloneAllocator >

            base_class;

        typedef ptr_vector<T,CloneAllocator,Allocator> this_type;
        
    public:

        BOOST_PTR_CONTAINER_DEFINE_SEQEUENCE_MEMBERS( ptr_vector, 
                                                      base_class,
                                                      this_type )
        
        explicit ptr_vector( size_type n,
                             const allocator_type& alloc = allocator_type() )
          : base_class(alloc)
        {
            this->base().reserve( n );
        }        
    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename T, typename CA, typename A >
    inline ptr_vector<T,CA,A>* new_clone( const ptr_vector<T,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, typename CA, typename A >
    inline void swap( ptr_vector<T,CA,A>& l, ptr_vector<T,CA,A>& r )
    {
        l.swap(r);
    }
    
}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_vector.hpp
+xTXbxYGyV9gBZpU0tTORlXghZWsLzi6btcpKkYq2SSTUqSeoU6fvF2mdgBaq0cRJOEq3p0Bti6Pf6RHfXwysNm+KEIyHGeFq57MkDDQidCoQuVbVZDeC+LIC664QcyddmCrrlScqai7QRAPmt0AhFZonIhB6MKv/XjSDvkHrLQSBtDxEkHoBxKbnQ15r1u++f2LUb9tc8RdX+qrUx+mSyByMRTZ9RGet35XR/KAzxqLlIzrIj0/EgaongcUHGB2PAQ81iDb4CEQ3Ps6RfBAUWRThfdqTadzKFA7q25iD+/jce5GhpLiAYVIVIv9O3U9awWtMp4F/vfJxH9e4PDxPTg1CKpXVy5bVJweozRm2oGlhTfOGfCRg2Hi91y06ozBqYPdNXC0pmcPYX4c+DvgIR+RP9MUD7xIrgiJbnq76XX7eOaf5/Ueoti08OmbZ8xG89ApLmbh9E/BkW+62/IHpODsci5jkhd8I16l9p6clTpVWrN8Q/vZOYEDPDgrIyzPZ+j02vkAQTsSeN6VAgZFfFj2xgk5BG2DFcYxqSVGRywdnAsSo3YpBxvOeXIHsRNrKB2IKokNfhb0PisbsiDA8AYiugzX2x6bOogVDxQVN61kYXNeptz3fTdP0OkHhWWirxjxFqzuvpFboP6ws07tIh3kVlh9r8A953pQJpzlUPmeDxFZttqVR4vHMmGuWdozuRLAKLa4iwilzvhB
*/