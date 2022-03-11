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