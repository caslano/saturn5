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
DAw+vuh40fKIHkjEJVE1VTVdNaN72AT1vKcbPkJAEYc0sHCYPGwIZgOjgOnCEBd0LlNdM8Z+4U+JT1HrRQy7cNnVIIr3PUFBIQqo8STUPugRc2/IVKfzmiJZ1Vf6LhmlBgpIvBqSTwLEvg1aLXl80Pwd9/A7riv/EZma3IUqu0KY2rgHnDmAtB5vzZGulaZj40DxBoFdxJx+zmpub6do3Gc1cf2uiyUXnYBzTy8AwLSsYkHAPqNBvr5iWcUJtw2NoR5dpFoyCBfwhLOMu/pqpYQuz88pE92R80PxfEVofWq9VwWpyKznaZnXT2tg+5OmQcmN+/pyQAsNTDMdP4ojM6mxdG26SAxSr9r31uY5ls5vbtGcB3BWfOMGfcUf1nACWXzi0Ll4Nh1/33pbTqQOPAVNFuyOSfvDWi5W4k1xF5pat7LyQhgF2/nu5/o3dIro3qWAGEaCsF8jY+hEpL0JumjuYly/pKFySKdOguKiDoGhu134CZ2PqJ2WC94eLswq2TOZzvpCXzB24BkuJScIGXeQ11V6PTfcM9kzUaT4JSsBpTEfFFxIkARLfkxFoeYSUEFCmNX6YZ1GKPeKL0IoAJ76GQpwwOzd1xcfMpSqkoH9hKJCKD3Ou9b8+SlbuXTwPqL25qV7mlIvCagX/qzZwXroSLZPZ54JT/ub/vFdUe1d/ahKnjx3qkeAQt09Sv170TTqV1943t/wa0nv
*/