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