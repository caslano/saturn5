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