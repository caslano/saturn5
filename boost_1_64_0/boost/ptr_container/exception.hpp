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

#ifndef BOOST_PTR_CONTAINER_EXCEPTION_HPP
#define BOOST_PTR_CONTAINER_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <exception>

namespace boost
{
    class bad_ptr_container_operation : public std::exception
    {
        const char* what_;
    public:
        bad_ptr_container_operation( const char* what ) : what_( what )
        { }
        
        virtual const char* what() const throw()
        {
            return what_;
        }
    };


    
    class bad_index : public bad_ptr_container_operation
    {
    public:
        bad_index( const char* what ) : bad_ptr_container_operation( what )
        { }
    };



    class bad_pointer : public bad_ptr_container_operation
    {
    public:
        bad_pointer() : bad_ptr_container_operation( "Null pointer not allowed in a pointer container!" )
        { }
        
        bad_pointer( const char* text ) : bad_ptr_container_operation( text )
        { }
    };
}

#endif

/* exception.hpp
NN4yvRAhjc6RxEcy4SZhppxB/AX3nnFnhu/hi8AFdCnGOWWE0ir+ldzPN9+qmfuitnSmN8CIYakJAb4PQU/FO3dPA9oOpG6LlAyDJQMVw2Rj1Z2T2ctVtsUy4kWxXYnZRrt6eNJtQdneRR0jdpSjaGH+HOe7IHHmoLgJpEibEyoq3E1RgI+fXzLRbQhJ5pfCXiU0l8Wh7LyWJ9pnP0oo+uLK152f3UKQXcy2hmIfZD8FCOkWCbSg8WaMqgB6NpI/qsKoWQAQKpnidXNGoqflUTArkuarmZtOkoztPzw2Yt+nX+UTrCKDw19FS4ROqPApcrfF/V2/Bn600dn8gwp2iyzf0ujHvjGcNDxnfPemY4/d/YM3+v6N0jcNL3eqsbq6pQmR8aOJO6GKzFavsszcJeIOhiG1IG9hSGvir/mWgHa/BVxwxbxlvULGZDg75dMHmYHngjx/9dVNZ9QD7Qy0SZLDu5xQddp86DG6PQOxI7KjbYJgKyZNnNYNidVGQWN8IHD7Eks0G3aAYU3g9iTuh9pi7kgZa2kJM+qeIzIwU4hT2COvV7fEy9SMPA==
*/