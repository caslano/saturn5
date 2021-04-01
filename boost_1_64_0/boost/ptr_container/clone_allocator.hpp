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
fuV8y3PlbUq7aLBiENp4ABIuhsockFKnEJhYKs9mP2m4eykVnuo8d83eWuwiEB3t8KYgt1F081KdcE0hYVKHWTMbV6tgrvoBZ7/Z0AqUaoIkX/keJw4S8EeTNtQyVJ5xy45Zu6HXA3lZ2BAivlqFbSKE7ughIPWQtgyTIykkcHhm/yvdzm16WYGsCoNH3sohhumKFzi6AnbfZ7cx41IaW22fvCwQWX8qJhh9As0kAYPYbytpCUFDoz1VWx9mpwN/ixX4ZGmG4I+kcaaMwp7jbMMGt79MlXNMHF34AnqoYvaGCyll6h215xMVPbkpnDNVtRUana+1YDcnFxzxHYTbJJDxGEMmXENd2PRaZ4tE/LVcBoi0S9bURkY4i4gvWTxxBf4gFETqb4i9pqyBxrXw8nJ3nvwktFnwSqrQGYviCl80gkVkII7IjPX4e7uu2xfZfzs1qsDXFA6nxeedtvkwS1vighuR0afxDoijxOZTFmTeYEiZNfa3UoQszAM5WaZnxWAVO2SBsBLxLmQ8bFRvPj4UI7hUh9ysIHukQapAsQ5CLdk9G3GlqMq0+Q==
*/