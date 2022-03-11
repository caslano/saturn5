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

#ifndef BOOST_PTR_CONTAINER_PTR_SET_HPP
#define BOOST_PTR_CONTAINER_PTR_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/ptr_container/ptr_set_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <set>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

    template
    < 
        class Key, 
        class Compare        = std::less<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<typename ptr_container_detail::void_ptr<Key>::type>
    >
    class ptr_set : 
        public ptr_set_adapter< Key, std::set<
            typename ptr_container_detail::void_ptr<Key>::type,
            void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                CloneAllocator, true >
    {
        typedef ptr_set_adapter< Key, std::set<
            typename ptr_container_detail::void_ptr<Key>::type,
            void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                 CloneAllocator, true >
             base_type;

        typedef ptr_set<Key,Compare,CloneAllocator,Allocator> this_type;
        
    public:
        ptr_set()
        { }
        
        explicit ptr_set( const Compare& comp,
                          const Allocator& a = Allocator() ) 
         : base_type( comp, a ) 
        { }

        template< typename InputIterator >
        ptr_set( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< typename InputIterator >
        ptr_set( InputIterator first, InputIterator last, 
                 const Compare& comp,
                 const Allocator& a = Allocator() ) 
         : base_type( first, last, comp, a )
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_set,
                                                      base_type,
                                                      this_type )
        
        BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( ptr_set, base_type )
                
    };
        
        
        
    template
    < 
        class Key, 
        class Compare        = std::less<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<void*>
    >
    class ptr_multiset : 
        public ptr_multiset_adapter< Key,
                                     std::multiset<void*,void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                     CloneAllocator, true >
    {
        typedef ptr_multiset_adapter< Key,
                                      std::multiset<void*,void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                      CloneAllocator, true >
              base_type;
        typedef ptr_multiset<Key,Compare,CloneAllocator,Allocator> this_type;
        
    public:
        ptr_multiset()
        { }
        
        explicit ptr_multiset( const Compare& comp,
                               const Allocator& a    = Allocator() )
         : base_type( comp, a ) 
        { }

        template< typename InputIterator >
        ptr_multiset( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< typename InputIterator >
        ptr_multiset( InputIterator first, InputIterator last,
                      const Compare& comp,
                      const Allocator& a  = Allocator() )
         : base_type( first, last, comp, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_multiset, 
                                                      base_type,
                                                      this_type )
        
        BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( ptr_multiset, 
                                                      base_type )     

    };

    /////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename K, typename C, typename CA, typename A >
    inline ptr_set<K,C,CA,A>* new_clone( const ptr_set<K,C,CA,A>& r )
    {
        return r.clone().release();
    }

    template< typename K, typename C, typename CA, typename A >
    inline ptr_multiset<K,C,CA,A>* new_clone( const ptr_multiset<K,C,CA,A>& r )
    {
        return r.clone().release();
    }
    
    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename K, typename C, typename CA, typename A >
    inline void swap( ptr_set<K,C,CA,A>& l, ptr_set<K,C,CA,A>& r )
    {
        l.swap(r);
    }

    template< typename K, typename C, typename CA, typename A >
    inline void swap( ptr_multiset<K,C,CA,A>& l, ptr_multiset<K,C,CA,A>& r )
    {
        l.swap(r);
    }

}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_set.hpp
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
*/