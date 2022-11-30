//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_PTR_UNORDERED_SET_HPP
#define BOOST_PTR_CONTAINER_PTR_UNORDERED_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/ptr_container/ptr_set_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <boost/unordered_set.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

    template
    < 
        class Key, 
        class Hash           = boost::hash<Key>,
        class Pred           = std::equal_to<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< typename ptr_container_detail::void_ptr<Key>::type >
    >
    class ptr_unordered_set : 
        public ptr_set_adapter< Key, boost::unordered_set<
            typename ptr_container_detail::void_ptr<Key>::type,
            void_ptr_indirect_fun<Hash,Key>,
            void_ptr_indirect_fun<Pred,Key>,Allocator>,
                                CloneAllocator, false >
    {
        typedef ptr_set_adapter< Key, boost::unordered_set<
                           typename ptr_container_detail::void_ptr<Key>::type,
                                 void_ptr_indirect_fun<Hash,Key>,
                                 void_ptr_indirect_fun<Pred,Key>,Allocator>,
                                 CloneAllocator, false >
             base_type;

        typedef ptr_unordered_set<Key,Hash,Pred,CloneAllocator,Allocator> this_type;

    public:
        typedef typename base_type::size_type size_type;

    private:
        using base_type::lower_bound;
        using base_type::upper_bound;
        using base_type::rbegin;
        using base_type::rend;
        using base_type::crbegin;
        using base_type::crend;
        using base_type::key_comp;
        using base_type::value_comp;
        using base_type::front;
        using base_type::back;
        
    public:
        using base_type::begin;
        using base_type::end;
        using base_type::cbegin;
        using base_type::cend;
        using base_type::bucket_count;
        using base_type::max_bucket_count;
        using base_type::bucket_size;
        using base_type::bucket;
        using base_type::load_factor;
        using base_type::max_load_factor;
        using base_type::rehash;
        using base_type::key_eq;
        using base_type::hash_function;
        
    public:
        ptr_unordered_set()
        {}

        explicit ptr_unordered_set( size_type n )
        : base_type( n, ptr_container_detail::unordered_associative_container_tag() )
        { }
        
        ptr_unordered_set( size_type n,
                           const Hash& comp,
                           const Pred& pred   = Pred(),                                         
                           const Allocator& a = Allocator() )
         : base_type( n, comp, pred, a ) 
        { }

        template< typename InputIterator >
        ptr_unordered_set( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< typename InputIterator >
        ptr_unordered_set( InputIterator first, InputIterator last,
                           const Hash& comp,
                           const Pred& pred   = Pred(),
                           const Allocator& a = Allocator() )
         : base_type( first, last, comp, pred, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_unordered_set,
                                                      base_type,
                                                      this_type )
        
        BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( ptr_unordered_set, 
                                                      base_type )
                
    };
        
        
    template
    < 
        class Key, 
        class Hash           = boost::hash<Key>,
        class Pred           = std::equal_to<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<void*>
    >
    class ptr_unordered_multiset : 
          public ptr_multiset_adapter< Key, 
                                boost::unordered_multiset<void*,void_ptr_indirect_fun<Hash,Key>,
                                                                void_ptr_indirect_fun<Pred,Key>,Allocator>,
                                            CloneAllocator, false >
    {
      typedef ptr_multiset_adapter< Key, 
              boost::unordered_multiset<void*,void_ptr_indirect_fun<Hash,Key>,
                                        void_ptr_indirect_fun<Pred,Key>,Allocator>,
                                        CloneAllocator, false >
              base_type;
        typedef ptr_unordered_multiset<Key,Hash,Pred,CloneAllocator,Allocator> this_type;

    public:
        typedef typename base_type::size_type size_type;

    private:
        using base_type::lower_bound;
        using base_type::upper_bound;
        using base_type::rbegin;
        using base_type::rend;
        using base_type::crbegin;
        using base_type::crend;
        using base_type::key_comp;
        using base_type::value_comp;
        using base_type::front;
        using base_type::back;
        
    public:
        using base_type::begin;
        using base_type::end;
        using base_type::cbegin;
        using base_type::cend;
        using base_type::bucket_count;
        using base_type::max_bucket_count;
        using base_type::bucket_size;
        using base_type::bucket;
        using base_type::load_factor;
        using base_type::max_load_factor;
        using base_type::rehash;
        using base_type::key_eq;
        using base_type::hash_function;
        
    public:
        ptr_unordered_multiset()
        { }
        
        explicit ptr_unordered_multiset( size_type n )
         : base_type( n, ptr_container_detail::unordered_associative_container_tag() ) 
        { }

        ptr_unordered_multiset( size_type n,
                                const Hash& comp,
                                const Pred& pred   = Pred(),                                         
                                const Allocator& a = Allocator() )
         : base_type( n, comp, pred, a ) 
        { }

        template< typename InputIterator >
        ptr_unordered_multiset( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< typename InputIterator >
        ptr_unordered_multiset( InputIterator first, InputIterator last,
                                const Hash& comp,
                                const Pred& pred   = Pred(),
                                const Allocator& a = Allocator() )
         : base_type( first, last, comp, pred, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_unordered_multiset, 
                                                      base_type,
                                                      this_type )
         
        BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( ptr_unordered_multiset, 
                                                      base_type )     

    };

    /////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename K, typename H, typename P, typename CA, typename A >
    inline ptr_unordered_set<K,H,P,CA,A>* 
    new_clone( const ptr_unordered_set<K,H,P,CA,A>& r )
    {
        return r.clone().release();
    }

    template< typename K, typename H, typename P, typename CA, typename A >
    inline ptr_unordered_multiset<K,H,P,CA,A>* 
    new_clone( const ptr_unordered_multiset<K,H,P,CA,A>& r )
    {
        return r.clone().release();
    }
    
    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename K, typename H, typename P, typename CA, typename A >
    inline void swap( ptr_unordered_set<K,H,P,CA,A>& l, 
                      ptr_unordered_set<K,H,P,CA,A>& r )
    {
        l.swap(r);
    }

    template< typename K, typename H, typename P, typename CA, typename A >
    inline void swap( ptr_unordered_multiset<K,H,P,CA,A>& l, 
                      ptr_unordered_multiset<K,H,P,CA,A>& r )
    {
        l.swap(r);
    }

}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_unordered_set.hpp
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
*/