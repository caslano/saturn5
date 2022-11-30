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

#ifndef BOOST_PTR_CONTAINER_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_PTR_MAP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <map>
#include <boost/ptr_container/ptr_map_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{
    
    template
    < 
        class Key, 
        class T, 
        class Compare        = std::less<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< std::pair<const Key,typename ptr_container_detail::void_ptr<T>::type> >
    >
    class ptr_map : 
        public ptr_map_adapter<T,std::map<Key,
            typename ptr_container_detail::void_ptr<T>::type,
                               Compare,Allocator>,CloneAllocator>
    {
        typedef ptr_map_adapter<T,std::map<Key,
            typename ptr_container_detail::void_ptr<T>::type,
                                Compare,Allocator>,CloneAllocator>
            base_type;

        typedef ptr_map<Key,T,Compare,CloneAllocator,Allocator> this_type;
        
    public:
        ptr_map()
        { }
        
        explicit ptr_map( const Compare& comp,
                          const Allocator& a  = Allocator() ) 
          : base_type( comp, a ) { }

        template< class InputIterator >
        ptr_map( InputIterator first, InputIterator last )
          : base_type( first, last )
        { }
        
        template< class InputIterator >
        ptr_map( InputIterator first, InputIterator last, 
                 const Compare& comp,
                 const Allocator& a  = Allocator() )
          : base_type( first, last, comp, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_map, base_type, 
                                                      this_type )

        template< class U >
        ptr_map( const ptr_map<Key,U>& r ) : base_type( r )
        { }

        ptr_map& operator=( ptr_map r )
        {
            this->swap( r );
            return *this;
        }
    };
    


    template
    < 
        class Key, 
        class T, 
        class Compare        = std::less<Key>, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< std::pair<const Key,void*> >
    >
    class ptr_multimap : 
        public ptr_multimap_adapter<T,std::multimap<Key,void*,
                                    Compare,Allocator>,CloneAllocator>
    {
        typedef ptr_multimap_adapter<T,std::multimap<Key,void*,
                                     Compare,Allocator>,CloneAllocator>
             base_type;

        typedef ptr_multimap<Key,T,Compare,CloneAllocator,Allocator> this_type;
        
    public:
        ptr_multimap()
        { }
        
        explicit ptr_multimap( const Compare& comp,
                               const Allocator& a  = Allocator() ) 
          : base_type( comp, a ) { }

        template< class InputIterator >
        ptr_multimap( InputIterator first, InputIterator last )
          : base_type( first,  last )
        { }
        
        template< class InputIterator >
        ptr_multimap( InputIterator first, InputIterator last,
                      const Compare& comp,
                      const Allocator& a  = Allocator() )
          : base_type( first, last, comp, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_multimap, 
                                                      base_type,
                                                      this_type )

        template< class U >
        ptr_multimap( const ptr_multimap<Key,U>& r ) : base_type( r )
        { }

        ptr_multimap& operator=( ptr_multimap r )
        {
            this->swap( r );
            return *this;
        }
    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< class K, class T, class C, class CA, class A >
    inline ptr_map<K,T,C,CA,A>* new_clone( const ptr_map<K,T,C,CA,A>& r )
    {
        return r.clone().release();
    }

    template< class K, class T, class C, class CA, class A >
    inline ptr_multimap<K,T,C,CA,A>* new_clone( const ptr_multimap<K,T,C,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename K, typename T, typename C, typename CA, typename A >
    inline void swap( ptr_map<K,T,C,CA,A>& l, ptr_map<K,T,C,CA,A>& r )
    {
        l.swap(r);
    }

    template< typename K, typename T, typename C, typename CA, typename A >
    inline void swap( ptr_multimap<K,T,C,CA,A>& l, ptr_multimap<K,T,C,CA,A>& r )
    {
        l.swap(r);
    }


}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_map.hpp
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
*/