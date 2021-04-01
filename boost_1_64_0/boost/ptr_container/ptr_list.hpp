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
dTlOYR36B9FOm7aS9yVr6M7tfBpV920P78qkcOvXj4Ay2JNN6M/QhJ//FixWwLPWVpv6NeNBXV4p/W6mnl+hoq0kVPwZQ7LW3XLIhOljfhxTc9w00cXn8ksDdwK+k2O9TWIT+Sk3B5bTxtBd77K8fNTmDylKR8PS9HQ349AwC7lCA63BVAzW6I6+BPx8aTAutMwYQbIT9Iu+URRwO5koiBncoggJj8E3i4N61DrrgNnem4fPcpopt9t2AGoweKliSlJeO6+6Ill/k21kopvNWchV3sic+qkVazInp4YAJnSAcxhcexSIYFbiLaP3rEeey6OXc1+XavPHOlj4QQ30asLmRkbH5j2E9acxFnbQmS2vBswdKIylybmSixOkOy7tT90wMS3LS2cjqapKQEFpNAd1/6ckCH7bwpKulqXXz6B3NmYoH4GBnfrxx/HTbLRW8QDoQip9Ffuf1Z/Q3jCquPOu/0Y8C27754ziBUotwx+GlFdkE8bYf3LXuCzlbw9Hn4SvvpPsT4mXVAI7+UWs9jWO/Q6Dirhn8Tj5ue1WJTmxGym54tTCDV1Qag==
*/