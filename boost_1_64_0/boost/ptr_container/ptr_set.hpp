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
9wLACfC6+aeBNj6GbrwX7Bby/GEQ9qrgYbXvAUfx/02Qh7kNwK2fBXQq7L2wR3PD1nMn4N3rSMgIyPGDkZ49Dfrb32BLOgh8/mvsJdcAj/qYoo8X9iTs9Q4F/84JQW+4EHLpFvCkAvDXc7E/w/+TayzaHwAdwjcTev3j0HlHA6f7YU8IPjotF7rWJUgHPU8tAf4eBrg3oyzW9AzsYSdVgV8fDD4wAXDLh50G+8/qtYDTCdBti7EfqZP7GvB4yKMR2Lf33GiKb4pwLgi4h7FP2I49TxNsJ0dgPgeXgGaB7+cjb/1JwBfsdU/AGjwG/fCbK5De2xQPY1/9cAb2NEcBF84D3Z8JeXAa4AUZUwA5uvRfxJ0JeFTVFccnCSKotYGwhKAQUBFRYhJCBBQlywQC2cwkrNFxkpkkI0lmnJkkROtat7buWquI+1bFfRe0dSlt3fdd61r3DXet1v7ufffNO/MyKHb52q8m4dz93LP8z7n3vbeSPvBnv9+f2H4MuN+D7C4Bn9PuVuK4Jy4lljjYA+Yjx7ABX4BfXA4fIlcQD5HbrFVyif6sHs58VrN+sN4M5vII51u7QLtoX/RkCLL4d2zSGmKEz9jzBZwNPIk9yMc3HMT8+rAVN8ID/H/NHhmez78jNzwMrIJ9e3NvZJzzzrpm9LIEPSb+3/YNeEd/7SoX0U4MSZ2frYHPuRmeOWuxRwXYlr3AUeCXU/GzC54GC5aS5zyUfWZPV6C3/gUZeh/PIS/fg2/8Zgb8INaLUraOPMGX2MUucOrLh+AvT0OGT8cWnA++YOyR0zgfwA5fuxXxB+N3Mt/ht+I3X4V/4z2eJ9CBNddZ/V/EWdGDz+JbfNjGN8CF4OcdyrBD92C7q8hdf0Y8OwWZBpcM6UfWbibuA5tMRwYXfQXP6sHOX4G/O8Ar5KZj/8S3818Z87hpLT4NeRiFP35zR/iqZDUfm7oM3HgY+VXs4T7DyYeCJcatzvJMnEjMeHWWPtscC29/jZ43NBM7vg1+fh//Ol+dryFb5GDu8zDmXHKw8K9lBPtC+4iHPSJn/Ms9iB1ez/QsxG5k4JefGQtvN5Knm0f8MpZYEfr5d4OXsYn998Jr2gYLkOVfk0cB5z1eCI56lDw29QfGE8suIcfP3i/9lPjzT8SkxI0hcOUh2LiTsvB/OfCedW7Ah02Ap7esYf74wDG95PRKWP+d7L/y68dhnzrAVSrfU+nxXBXP9OSwd4pfJyXALK3YYrBUN3JensccatlL/MkDVzH2bHLwyM9TzcShvfhZHzn7hfB7ERjuFHxQCNzM+VgWY78bAyNegh7/nfFqGHcqPI0Rb2PPM7BPt+9I3avxPXuAbYs94Bf8ZAH+qQvcjO//tCjTswac8l4OaxrBHt8O/vra48keAx7bGh6/CY67F7twDfl6MGEvcdLJ2cQW6PTj2L6tMoh1kO0s/Nu7IWRpX+ZcDl5vJ0dWB564mDYvkFuqIhbA92Xsx+/TOI8+Dzn8Fhw/OhPsCl/BOW93YqtUzh7b8loEzH4x+Z2h+IxV2MAbwQOM/QL4eV0FuSJ8Sxt7sCVn9oGD2V/0dsh+5FfYq8pO7PMk9In7BIuQ1cQSbBu25dZ52KswegqGeRafu+XBGZ4D5qCDl3LOe3cG+W8wI/NauRC5/ytjYVN2xba9C6Z8ZBH53SfxgUvJ+z6Ark1HVuBJbAPx1lb4gg9YA+V7EWud8JcMnupjP9mr7al79nnIYTm+k1zOdq3wdQVx3Slg7xZsfj5+aHkG9yXAEtiq3VRMiJ+aj/9dfjY+Gb/zVRDMGuEsopHYh1zWwkvZV/bnNWToemzX/sRbr0Y5m+B8deg92JUtPcRt5LKYy1E=
*/