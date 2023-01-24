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
xM0WWRx0xcSr5lSfVxgKE8Xypd3xd4g19Vkg1mDq696bCkdRmrS5t8ZZX4ssrImyJGNJ/5pP/8tV61sVarIU0MTa63xhK+0pVZc/LlWXU6ywZLMZVGpLE67OOS/BmA3taE117jsbQ5H/YYqoFcP/bMX2x7rK+Vc27+h1WcQ00gNdfC2cSCI7f+bi5ClBPCb05g+BsU8pnRJBcWsnDIfsJ9qmBVUW8n+pM3SG0x08LKpnD5i4Zb83l79luDe9x0S6a5hm7zAo0V9CFkIjg5qzdhhiQ86YybCzXpP5Byg+wFTjr45NWcmwOecux8jpIM2eonXyQ/LYHrSk826T7HRcYuCdIi6oz6FC3iBDzePWgGSLm4JzGnxWA+ALToqIOPIsy9iNVxFmrT313zwUOsgm1BzQZxlk2lG0SKtZ1DMDC6REFdRrJG2dwCfjCOXXZBfyKpVmqQxtO7gl8MzR7D9blGx9OBM0iCHOVPOmbqIRVGvsPz3/sByTmNiooiOseM4HmrlmQ6JChGKJhgpulMZua+0EUF2bXa2WKJRr1XXwcY0+EvF9xvEJNf3S50HmnlPywF6+jhk6FgfipwpeoK/qS5vuyp6l/6GE4uXMOKWw/qv1jVcF7xWFujyftYFCvPa132IGFhv+wEayahwbTZlao5KPhyp1rx43lIW1v4pXKSnRw2g+nTZFdtai/LNcagCWgG1qN7Fdx+GQRNlc
*/