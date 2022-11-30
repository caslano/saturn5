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
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
*/