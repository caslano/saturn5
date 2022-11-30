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
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
*/