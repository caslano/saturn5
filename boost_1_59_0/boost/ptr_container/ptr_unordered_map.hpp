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

#ifndef BOOST_PTR_CONTAINER_PTR_UNORDERED_MAP_HPP
#define BOOST_PTR_CONTAINER_PTR_UNORDERED_MAP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/unordered_map.hpp>
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
        class Hash           = boost::hash<Key>,
        class Pred           = std::equal_to<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< std::pair<const Key,
                           typename ptr_container_detail::void_ptr<T>::type> >
    >
    class ptr_unordered_map : 
        public ptr_map_adapter<T,boost::unordered_map<Key,
            typename ptr_container_detail::void_ptr<T>::type,Hash,Pred,Allocator>,
                               CloneAllocator,false>
    {
        typedef ptr_map_adapter<T,boost::unordered_map<Key,
            typename ptr_container_detail::void_ptr<T>::type,Hash,Pred,Allocator>,
                               CloneAllocator,false>
            base_type;

        typedef ptr_unordered_map<Key,T,Hash,Pred,CloneAllocator,Allocator> this_type;

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
        ptr_unordered_map()
        { }

        explicit ptr_unordered_map( size_type n )
        : base_type( n, ptr_container_detail::unordered_associative_container_tag() )
        { }
        
        ptr_unordered_map( size_type n,
                           const Hash& comp,
                           const Pred& pred   = Pred(),                                         
                           const Allocator& a = Allocator() )
         : base_type( n, comp, pred, a ) 
        { }

        template< typename InputIterator >
        ptr_unordered_map( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }
        
        template< typename InputIterator >
        ptr_unordered_map( InputIterator first, InputIterator last,
                           const Hash& comp,
                           const Pred& pred   = Pred(),
                           const Allocator& a = Allocator() )
         : base_type( first, last, comp, pred, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_unordered_map, 
                                                      base_type, 
                                                      this_type )

        template< class U >
        ptr_unordered_map( const ptr_unordered_map<Key,U>& r ) : base_type( r )
        { }

        ptr_unordered_map& operator=( ptr_unordered_map r )
        {
            this->swap( r );
            return *this;
        }
    };
    


    template
    < 
        class Key, 
        class T, 
        class Hash           = boost::hash<Key>,
        class Pred           = std::equal_to<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< std::pair<const Key,void*> >
    >
    class ptr_unordered_multimap : 
        public ptr_multimap_adapter<T,boost::unordered_multimap<Key,void*,Hash,Pred,Allocator>,
                                    CloneAllocator,false>
    {
        typedef ptr_multimap_adapter<T,boost::unordered_multimap<Key,void*,Hash,Pred,Allocator>,
                                     CloneAllocator,false>
            base_type;

        typedef ptr_unordered_multimap<Key,T,Hash,Pred,CloneAllocator,Allocator> this_type;

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
        ptr_unordered_multimap()
        { }

        explicit ptr_unordered_multimap( size_type n )
        : base_type( n, ptr_container_detail::unordered_associative_container_tag() )
        { }
        
        ptr_unordered_multimap( size_type n,
                                const Hash& comp,
                                const Pred& pred   = Pred(),                                         
                                const Allocator& a = Allocator() )
         : base_type( n, comp, pred, a ) 
        { }

        template< typename InputIterator >
        ptr_unordered_multimap( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }
        
        template< typename InputIterator >
        ptr_unordered_multimap( InputIterator first, InputIterator last,
                                const Hash& comp,
                                const Pred& pred   = Pred(),
                                const Allocator& a = Allocator() )
         : base_type( first, last, comp, pred, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_unordered_multimap, 
                                                      base_type, 
                                                      this_type )

        template< class U >
        ptr_unordered_multimap( const ptr_unordered_multimap<Key,U>& r ) : base_type( r )
        { }

        ptr_unordered_multimap& operator=( ptr_unordered_multimap r )
        {
            this->swap( r );
            return *this;
        }
    };
    
    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< class K, class T, class H, class P, class CA, class A >
    inline ptr_unordered_map<K,T,H,P,CA,A>* 
    new_clone( const ptr_unordered_map<K,T,H,P,CA,A>& r )
    {
        return r.clone().release();
    }

    template< class K, class T, class H, class P, class CA, class A >
    inline ptr_unordered_multimap<K,T,H,P,CA,A>* 
    new_clone( const ptr_unordered_multimap<K,T,H,P,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< class K, class T, class H, class P, class CA, class A >
    inline void swap( ptr_unordered_map<K,T,H,P,CA,A>& l, 
                      ptr_unordered_map<K,T,H,P,CA,A>& r )
    {
        l.swap(r);
    }

    template< class K, class T, class H, class P, class CA, class A >
    inline void swap( ptr_unordered_multimap<K,T,H,P,CA,A>& l, 
                      ptr_unordered_multimap<K,T,H,P,CA,A>& r )
    {
        l.swap(r);
    }


}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_unordered_map.hpp
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
*/