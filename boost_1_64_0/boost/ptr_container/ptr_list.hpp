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
4tEX8T7xA3jb9VSX+HMY752eYoorP8HdkREu8eNh8OD/Vfp2mmIOLks+8ZMpirMN8etgl/hmM8YxyRA7PkXdcpf47FlDFO8vxEGPw27+FN4Mn+4SS1ZijGFDfNQJb2Deg3eIe7rEoptxugfnwuOnG2LlTMzpWCGmH4o37SqF2FFgisyDTLHpIbz1auKc4UIhPj7TEJtT8e4A5n7Lk7if8i7muAzj9wmxFWVDyPvmRENMul+I27biPdfnAYvrXaKgr0tENhmi18+4i/6CKfydTPHxJyh3iiGe3mSKm5aZYvDlpljxmRDf7ukSt78Mn/4luC+ZgZg0Qbxu19kl/EHcXcX43sS4Vn4OX+Dthth6sxBfvGYIF9p0xdDPFTinWoDYR+8a4rFjYHPeaogb9nOJLlebYv/X8G441m/zrRhrwCUOf1uI5w4U4tF5pnjoYczpA8QyOMMUaRtglXpKiIvQ5/xSlyguMcUfAKvc0TiHOxS27edw3hYzxPUppnhzo0tcgtPB14aZ4qVxLnH/fYhlchFetwS8lt6FN+pPwh0b4MTkA9D/00Jsv9QlhuJ9t+tuxnz6mqI3yma+YYrFm13ihpG4G/8ayo7G+O53iQu24RwDeND/HVN8NMEQL/xkiJvPMsWjexni4a2YXy/Y/oAfw+eivzqch0xwiZveMsUD2S7xGOZ72h9dYmsv4MRiUxijYfn8DF5bn7nEyee7xF5dTfGXeYbIeNEULzebYti9hlj3M+IonmqKE2HdOuA6+J9jHP374LbqU/jGfK563xAp8xDfZ4VLDFkFm/0C+G4/Z4hC/P3uDLyDGkK8gaghXpzlEgOnwcftaEPc1QmwxRyfn26Kw7A2v57sEodNwP3YGOb0pUt8ssoQFz1miA9AA1fmmOLdD2Gzu02Iqttc4uCIIf50Fu6KVcHmdirwb19TPPeIEJ91RZkg5rjWEAevxusLP8KD/WOXuPYe9IF53jfUFJ/vb4rtxS5ROdQQF0wwRR7gd9/p8Ik4EDgzyBQz3Kb49BdTHLUXPNWmmOLW4w3xj7HA3zl4v/kJQyx4Cy+WArYLygHfz4V4F+V/Bg7PORU4inEsuwAxYCaibfR778v4P9MUW2vw9lbUJS5/0hTfgz7KTjBEOnDnum74/2Mhln4E+M4Er5iK9xKPcomXF+OdqfFCjMaYJ48wxDM1hmh6By9qRVyiVzF8s3NNMXlPnK2uM8Ser+Cdnf1dYtkyQ4z4zhBHgkcMPR9t3GSI/Teb4jLg3Tk/oMy1pli4EngJmr/6TFP8EXjR/yCcuwD3u9aZ4q1BgNcm4FC+IfbqbIobjjXFP68yxJBFhjgU9DO+F/J9pvhqoCn2Qz99q1yi+9Uu8d4WrJsHa/93Uzz5OcZxJGAxCvRwg0vMeEmIDwCHGytwn+4pU3z7rSnuXQ68essQZ98MvAE853QG3k0xhBs87RzAIoI+rwFdTv/SUG+wDMDd7aKBYKe3wHcNtPLYA+gf9HvSvgLwg39XoRB/nYn7ACvAO7GmMeRt+8EQ4w8yxKLHEHMTPOb7UlM88pZLfACYPIu870aa4qzbYY9PBU5ebYgTbkJ/t+O+2eGI/fgm7LR/AazR/8KrcdawGucJH5qiucEQvTHf3LPBK4aC91yOeYDHDcIafnktYpZiXbqDhj+sE+IPL5niBKz3IXgVbtI2rNlXuMu7UYhnrwJvx/+e413i9K+Ak+eBX+0NPg7+eeTbhjCBa9eDL771Kc4pMPZbwbuGgKdN+84UFVibZ/Pw1s0vLlEOuArIj4n3Yz6vmKIf5MNHy/D3PkNUGpAnLtj8l7vED2mm+NOJoBfwhEGr8Q74z6a46mxDXAac7T4AvPM=
*/