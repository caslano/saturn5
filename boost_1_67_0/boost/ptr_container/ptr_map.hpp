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