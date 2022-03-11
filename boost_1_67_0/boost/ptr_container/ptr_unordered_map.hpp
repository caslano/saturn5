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