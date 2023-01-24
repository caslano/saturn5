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
5aEBad0VMtr7cNa3ZBK7ArtHftI93TgzH6bTKU9x+/NscOeYytUap5jyOaePaB/1qhVrl6F7mUdyjU0fLaLLTpjT2NSMQ3C5hAoSGCxTeEOkmK3WiI7reZTWyTm4yTUtgLUglfm45JeUpUmHErKDMTie8KSXnj7nKbxF9kNsoLMzeI+tKliQOoqaXXDwQHDbxc42knGd5urdqGvV1lN02uYj5x8J4RS9Cy/w3OSqTr/tpVdzQcp2RyiODGgadqC3T4dP0SKs/BUb3C76XoPJ3qO7/eVbQau8Ng72YToVdGe8bEVnVcuFBcVY1r9jBDO3F4IdvdZ4NOyUABwxzMJmn4t3L0L94K06/V5gkWqV4X7FNCE+rpnUYA6YEV9AS1W5oOhYagjNK1VgKAfcUVoV4Fe5qeeDkNd8aXJ0en7UxvrH9zOroa1SFrA5qaMSXLemfJ/H0MFdA3JBWk1VvVaHWGtwfYWhgljo+HCNVZ5FGt79gLCD2X4xaNQjE8EdxGG31iP6ki4j17nI6Ify263mNJ9VD+PjlKVX8BT/cP6a3kOLYr/ez6zHhdGevjbQWJzyWmeqVo4GoyZPQ8XrWHNOluUBPN3CSrxkbEPKAkmGDwkpzr66PyAYY0u4mty4qlY1dRztBlFWPq1fbU5+XS6sdoTTDSp+xWjggn1PgW9mhPPwdZRzFTKMCO41lpu2gileT2sBYbUR43xkKiw6
*/