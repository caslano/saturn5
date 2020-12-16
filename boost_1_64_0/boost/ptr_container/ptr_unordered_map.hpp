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
eXEmcdqx4OJKZA3+3rKRvXgUvDGRM/jfgwVuwsfh59sjYGNs9tPM9d5DwGvMoelKD7lF4qGXsWvE9GedzVkt59tecN/Mr8E/2cQef+KcFWxbSl77KWxELn71bHRhvwco585BD/2cxloOWI/dQgcXch6bRe75mz3RVWzn6m+Q3VHINjhr9Bpk+y7aeIgRaDv9cebbiTy8h9/8nr3F7xYchRywhhPoYwX6NS6PnAwxuB+MdRl9bNga/7sXdglscCs4poh53cY869m7J89nbZ3wGRl7rBvcgDyeAJY6irz1OZzpXnIRYzP/O3qJD8AKj+VmeYoPwk4hf1ucyv0N7PrnYLjXR+Ebjkb3iLOqe+kLTBF/iRhtN870RiH/8GH8ZWDurVgXjiz2HXsymXwKfJ8OrrviEs4a9iTGrcG2ruVOC7yswi6vqCT/xd3Ij8cRH39L3NXGmdFl8G0c55D3gDeIq7b6jHws/BrSTW5zNLZiaAbffOesj7zEVLBoL3jgK/B7/I/oNnp53G34xQzOiH9NHgTeNYLXLhhD7nIivhd5vHwheGEZPnUbfO2J6AB49MGPsCHYqnAzduMO8unT4Tt5wHF/RS/g22G7Mr9ufOmRyN9qj85/D/0L7aBdB/7swme9yRnO2ejSn35LDuNw9Jy1LcVeXwrWXfcV+58gRgNznIa+3HoAecVz4S+YYgoYcutj8LmnEzsxn7NmW7Zq7MXw4TdgXnIHf2du42/FLn6PruTSbwVl440NmWXZsutfwA++zflUJ/Z6C+zh8izO25BRZO7raeQsF+CrOsj/Y3t2vgw5vALsi+3bZ3/42EuMjs9ZegXnDzcz/9XcswJ77PA09pucxmJyFBUvsweHqJcygPEPYLyRYP8jyE1fxZlVNXiWNd8H/m9uwHeBuXbDd9yF7emh7jlTyft62dMPuYuKjb6XM459oOWUgXV9xBTsQc7X+K0QNjuQ6emuIZca59wVecjHXn9KPsizHN85iTgon/OT69gX1j3Zhy7dxF0NxjvgbHTnanTkaWzRE/gleKju4p2OnRoghnkgB9s5DRsTAR99iNysySDfS//ox5ej8IVggOeJYy9A7quQuz/PA/ftQD4niC7Ch53Ay3OOBfsWgvuxo2tOJAYk73303mCEQtr9gjVNI07AHx2EP+8nx1j/lsfT+1UG8RDxWg0+Dv/Ric1evwh7AZ475hHyFeQtN/6ROgvB1hMY73NyLd/hxzPQXeSiBJt6LzqxK/N5XZ1BB9jj98BnXvzJLGz/BnI84PqTvkFWJuKzkMNfoQ8r8dmXvgVO3wF5Z/8m/Rl/VYncYntf3I4cXTb3kL6Ff+Dxjyj33YbsbWPdzS2+lJwkMp9DXLYfMnF5IlPfBZnHvC9sRLfwHdfC80zw3rADwFJd+PuH4S88yN1IXEJer+tT7n5/C45AZ4rfJjfZwB2A4WBV4t7gXGw6/S1EV9rfyeBuDTy+H5mLgdu4M+A7lf/Qn4eYx5VlnOVMBIeQN5zP321zkd952IJmMCBj7oO/LMsG37zOvGvwla+SS2KvXpuD/HMfovqf2DryUbtwZn0TOPDWqdzPAdssRy5/3sYZL3FH+ItM7scSCx+K3jwGPkRu9kLfbgGbPYU/2ws/UkiurwrePkbbshzk6zls0SXc9ziYtlsgayPhyzjmn02eBHs66UD883b0DW7bnpxEG9jyS7B6I/Hx8fPQiXxshQ/b9rFH63se8vDV19jj6zm/UznzUv5+gzxHP/kc8ire9y27MOY18rgjuZO1mHhqGr7wZGKaOdi8E8ixw+fuEDrwa3IL+5C7uYFc/MpMTxDMMX89eH8oOBN6B3L1Jvm+oressS8hj7g=
*/