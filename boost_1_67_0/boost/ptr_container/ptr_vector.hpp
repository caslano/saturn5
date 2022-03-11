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