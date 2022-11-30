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
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
*/