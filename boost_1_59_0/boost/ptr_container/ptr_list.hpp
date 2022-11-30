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

#ifndef BOOST_PTR_CONTAINER_PTR_LIST_HPP
#define BOOST_PTR_CONTAINER_PTR_LIST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/ptr_sequence_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <list>

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
    class ptr_list : public 
        ptr_sequence_adapter< T, std::list<
            typename ptr_container_detail::void_ptr<T>::type,Allocator>, 
                              CloneAllocator >
    {
        typedef    ptr_sequence_adapter< T, std::list<
            typename ptr_container_detail::void_ptr<T>::type,Allocator>, 
                                         CloneAllocator >
            base_class;

        typedef ptr_list<T,CloneAllocator,Allocator>  this_type;
        typedef BOOST_DEDUCED_TYPENAME boost::remove_nullable<T>::type U;
        
    public:
        BOOST_PTR_CONTAINER_DEFINE_SEQEUENCE_MEMBERS( ptr_list, 
                                                      base_class,
                                                      this_type )

        typedef BOOST_DEDUCED_TYPENAME base_class::value_type value_type;
        
    public:
        using base_class::merge;
        
        void merge( ptr_list& x )                                 
        {
            merge( x, std::less<U>() );
        }

        template< typename Compare > 
        void merge( ptr_list& x, Compare comp )                   
        {
            this->base().merge( x.base(), void_ptr_indirect_fun<Compare,U>( comp ) ); }

        void sort()                                                    
        { 
            sort( std::less<U>() ); 
        };

        template< typename Compare > 
        void sort( Compare comp )                             
        {
            this->base().sort( void_ptr_indirect_fun<Compare,U>( comp ) );
        }

        template< class Pred >
        void erase_if( iterator first, iterator last, Pred pred )
        {
            base_class::erase_if( first, last, pred );
        }
        
        template< class Pred >
        void erase_if( Pred pred )
        {
            this->base().remove_if( BOOST_DEDUCED_TYPENAME base_class:: 
                    BOOST_NESTED_TEMPLATE void_ptr_delete_if<Pred,value_type>
                                    (pred) );
        } 

    }; // class 'ptr_list'

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename T, typename CA, typename A >
    inline ptr_list<T,CA,A>* new_clone( const ptr_list<T,CA,A>& r )
    {
        return r.clone().release();
    }
    
    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, typename CA, typename A >
    inline void swap( ptr_list<T,CA,A>& l, ptr_list<T,CA,A>& r )
    {
        l.swap(r);
    }
}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_list.hpp
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
*/