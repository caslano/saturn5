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
VwSm1DfZE/x/uxXCJTAm/8CHBsqlskUz+EYiQeNK/BFTFC8Ta/kbrwT2pQ1NPlCCbbJoEJ8JD231ZcuMH9am0hRGJvb7X14dbzsKNWIzstspdNVBeD70lOiVGFy/GrkLBZ9Jrw3Fsz4joUSTS42+CyK7j3YDdjen8fmfyrDahb1jtovD/6z8U1IkjUo19LPgmR6J3aiK58Adv20JMTkEJnLz/bCwpNKkzZxl2oJohppOybtoJtaTN1FgDe3aq3WFb5pqKNrYnbjYokgOQ+e3azFWjCVWQZzqIjtvcqynUEGam6VMQYCbKlMOnn4slerKhNZJsNCcS+FQt9RyTWLC3M/WKPi3L/2fVX49iOa0+CWHuZh9cotHMktaYnqH3K1+TVZJbwGtpewUAwUZgf3Dr6+bJP9SNrdP9w1bk5xxk7zLj6cepyzYlx1Vxj5Z0ejGrdgNVP1UVMC+clkpM0utHOEmnSISz1fcL2UWOwXTmj4R2Gbl+qOB963UUuwbPD27JjZ+c5GdQbrJJo93z4uTmDOpa+R4Y3tC8z9ZOrfacWRtsaSejjivq4/hWUrJLavVkeEKQFkLu1fDUtQQESUY4096iwz2EQ2NmS8HWoOdxms0n+YTn4olDIEr7F1deRHy7LkSrFmNmgHfLJ3/0Jo43D8TgNXXE53ROKQczjsh9BGKEGyghwnyN2QL+Vx8QZpRTcjV8Mi5/5Iu7kOK
*/