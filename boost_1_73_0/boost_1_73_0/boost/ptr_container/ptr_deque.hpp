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

#ifndef BOOST_PTR_CONTAINER_PTR_DEQUE_HPP
#define BOOST_PTR_CONTAINER_PTR_DEQUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <deque>
#include <boost/ptr_container/ptr_sequence_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>

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
        class Allocator      = std::allocator<typename ptr_container_detail::void_ptr<T>::type>
    >
    class ptr_deque : public 
        ptr_sequence_adapter< T, std::deque<
            typename ptr_container_detail::void_ptr<T>::type,Allocator>,
                              CloneAllocator >
    {
         typedef   ptr_sequence_adapter< T, std::deque<
             typename ptr_container_detail::void_ptr<T>::type,Allocator>,     
                                         CloneAllocator >
          base_class;

         typedef ptr_deque<T,CloneAllocator,Allocator> this_type; 
         
    public:

      BOOST_PTR_CONTAINER_DEFINE_SEQEUENCE_MEMBERS( ptr_deque,
                                                    base_class,
                                                    this_type )
    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability
    
    template< typename T, typename CA, typename A >
    inline ptr_deque<T,CA,A>* new_clone( const ptr_deque<T,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, typename CA, typename A >
    inline void swap( ptr_deque<T,CA,A>& l, ptr_deque<T,CA,A>& r )
    {
        l.swap(r);
    }
}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_deque.hpp
AgAACgAAAAgALWdKUhMI/eV+BgAA6BAAACMACQAAAAAAAQAAAAAAmYpBAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU0MS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkiZA7zsAgAAXAYAACMACQAAAAAAAQAAAAAAYZFBAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU1MC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgdaKke2AgAAOgYAACMACQAAAAAAAQAAAAAAl5RBAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU1MS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnrv2IYRBAAAhAkAACMACQAAAAAAAQAAAAAAl5dBAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU1Mi5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlmF9XKeBAAAdAsAACMACQAAAAAAAQAAAAAA8ptBAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU1My5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnj7HLE+BAAAYgoAACMACQAAAAAAAQAAAAAA2qBB
*/