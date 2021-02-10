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

#ifndef BOOST_PTR_CONTAINER_CLONE_ALLOCATOR_HPP
#define BOOST_PTR_CONTAINER_CLONE_ALLOCATOR_HPP

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <typeinfo>

namespace boost
{
    /////////////////////////////////////////////////////////////////////////
    // Clonable concept 
    /////////////////////////////////////////////////////////////////////////
    
    template< class T >
    inline T* new_clone( const T& r )
    {
        //
        // @remark: if you get a compile-error here,
        //          it is most likely because you did not
        //          define new_clone( const T& ) in the namespace
        //          of T.
        //
        T* res = new T( r );
        BOOST_ASSERT( typeid(r) == typeid(*res) &&
                      "Default new_clone() sliced object!" );
        return res;
    }


    
    template< class T >
    inline void delete_clone( const T* r )
    {
        checked_delete( r );
    }

    /////////////////////////////////////////////////////////////////////////
    // CloneAllocator concept
    /////////////////////////////////////////////////////////////////////////
    
    struct heap_clone_allocator
    {
        template< class U >
        static U* allocate_clone( const U& r )
        {
            return new_clone( r );
        }

        template< class U >
        static void deallocate_clone( const U* r )
        {
            delete_clone( r );
        }

    };


    
    struct view_clone_allocator
    {
        template< class U >
        static U* allocate_clone( const U& r )
        {
            return const_cast<U*>(&r);
        }

        template< class U >
        static void deallocate_clone( const U* /*r*/ )
        {
            // do nothing
        }
    };

} // namespace 'boost'

#endif


/* clone_allocator.hpp
VAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSj1A4nowOAAAAWwAAJgAJAAAAAAABAAAAAAA0yEAAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9NYWtlZmlsZS5pbmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSeGBhuYgCAABaBQAAKwAJAAAAAAABAAAAAAAN10AAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9jaGtkZWNpbWFscG9pbnQuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIhWWsPwQIAADEGAAAnAAkAAAAAAAEAAAAAAOfZQABjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2Noa2hvc3RuYW1lLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSwrmPJtoHAAC4EQAAIQAJAAAAAAABAAAAAAD23EAAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9maXJzdC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUio9/5+eBgAAahcAACMACQAAAAAAAQAAAAAAGOVAAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTE1Ni5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUrxzknbu
*/