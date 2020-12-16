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

#ifndef BOOST_PTR_CONTAINER_PTR_DEQUE_HPP
#define BOOST_PTR_CONTAINER_PTR_DEQUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <deque>
#include <boost/ptr_container/ptr_sequence_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{
    
    template
    < 
        class T, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<typename ptr_container_detail::void_ptr<T>::type>
    >
    class ptr_deque : public 
        ptr_sequence_adapter< T, std::deque<
            typename ptr_container_detail::void_ptr<T>::type,Allocator>,
                              CloneAllocator >
    {
         typedef   ptr_sequence_adapter< T, std::deque<
             typename ptr_container_detail::void_ptr<T>::type,Allocator>,     
                                         CloneAllocator >
          base_class;

         typedef ptr_deque<T,CloneAllocator,Allocator> this_type; 
         
    public:

      BOOST_PTR_CONTAINER_DEFINE_SEQEUENCE_MEMBERS( ptr_deque,
                                                    base_class,
                                                    this_type )
    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability
    
    template< typename T, typename CA, typename A >
    inline ptr_deque<T,CA,A>* new_clone( const ptr_deque<T,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, typename CA, typename A >
    inline void swap( ptr_deque<T,CA,A>& l, ptr_deque<T,CA,A>& r )
    {
        l.swap(r);
    }
}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_deque.hpp
x04Mjp2zbdt8F/xPqJbwi0xV81IcrqzWodUI2on7EHRlMDB2HmuubISNUs+i8y1+1tZQAw8pQd/yrUn+jXVrVt9DyY69B+u/uwOOwkYlT7rUvPekeY901BkSh1KKuhJfRBt7Z9t7q70ZLHtkJ/Pn9GybF8pyafiV/LknjZPaSvDCXtmsnGDlqO34PiZG7fXGL+OtKm8Uy2Nt0P7HqZ4+xvbvjRJwYXsjLUPbG7E+GH/+kPZGeyFd7oMystkK0N5oH6Rp/FX0QVqdP1Lnkxe6KK0vL3eo2Cktk6XNC8CRPmB998um6J6SJ9N32N/is9N6iv4EyyX24NS+a0A233f1NAZSOZ2fS1zrDn4+iPIlDnZvA9emt48HtIuuJK66Ga5mEv7XJvlfR3D8gdtEjBem6LyQ0lMlP030w/LUnJq0wX2d8A/OZjSa9jvKB8m/8iimjiGk/ONxW31VjTXyfoEfl+hKE+f1+9K68Rw5j0LyZR/Kxpr6G3C+eZewDdHdKg7X6hpys94Wl2vdneQayaS0NmTSMDb+DBvWoYametwuKVOWymJoJxqgnUuQvwyD6SxpepDfo4QFx5D0JBY2/IZz+P0Ge0qcjx6ZlexTf0C2Ja9WD7Lllfz+vJf9PTnhGxprlP7DQXm/OlBDMV8SKVDt4rFeeCm5F+iCVOv+5Khs5sWGS9zyiXI/nJub5N8ovfrQegF6AyLhqyqLxRoXNiI+t8/f1ERvBqh0pXyG6gN2ummlz48FrbQcNq6cbGoNORL/aCQ8ifpu08+wsQE6EfeF03O4P94Y9Dk2u3V/vIOQNz9g96/oifSDcVw/+A3957U1D+dGeLLCqfgcxrcxhwkOc4ifNU/kc+hw33EcqJGxAWjdA4skzUzGupq0rpOy7VmFamL1Aba4O6fbNrMDmc13lBwf3Xv7pBfNk72fExX0ZocWMyo329ZfDsX/5AulWsvHt+xH0h2Ph+XJtn55rKhCKitpkpedlm398thYRaxP2Re/hzSDyo7OsufAx/R9Gqur3bUqy6Z+ZZ76pbrU7+EsP4vud/E5eNm4DA4ntF3F8iQ+8X5n0dwP13yu5mjl5mp8LIXxMf6dyXw9Gg1+dycAHJsfrGb3IkykVc+rb0qO+420Jh7zH9/h+mpeJlWV8YfravhbHGg/2KisbLxsd9XvIj0dcwHji9j9pMlv1m+67CMSa+B1MpAWZGX2UWXs7z74rq/1Y7R2Wj+khZobQzzezQCkhQP2PaYhskygIcjfDBlKaRDSqtyRgP8wq15OvK10SX9WnzDoWPcrewKsPkb3U+L3IgrKvMzHo2qnVJKZKnYLxShosG7NxB0OfZG6YK08v2yU/p5E//5s3V+yjbrkw9n+8uRDQrJ8mpqXrzYYtnwLKE3K83o/kuhbym/cwLV9waqT91ohvPofjPqUjYNCLmhprcZzIqiVknNM/Famnkp7rwDprY5tdWBdZFvzqa2NSffhSvzVdbARcJqie7lltXT/KtLm3TDS4+gyT2XIu7hhXqheu7fT3W5TZUdYf2nq/llZbZnSh/z15FjJ6Eg+veGvRutwbA1Wy7p5FGsrmKTz0czlO5ocIHoy3TMcyfXV+P0tuqXMddQUuh8X1/MWcj2P+qSgZPGbQKxbLQc9O/u0TisqRVSi0nyPz6dqs29avwa1fiy2Nb75/aIo3S8KET9uovLsfQ2lH+K1gBryx1U0GGbzSWl7HM77498AAxVnjMaPIW6rdSXhpOLydvw2de+wONi4MBDmd+Ao3yXvH+r5fP0Iv9SFdr73oPQiWxNWe9oEzlI+Xq/RSvCYB4QwZbUexKtYrKggKQYCtoYOffehdNlc8l3FIoi4gMwU9r0=
*/