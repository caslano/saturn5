
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_PROTECTED_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_PROTECTED_STACK_ALLOCATOR_H

extern "C" {
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
}

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#include <cmath>
#include <cstddef>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>
#include <boost/coroutine/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename traitsT >
struct basic_protected_stack_allocator
{
    typedef traitsT traits_type;

    void allocate( stack_context & ctx, std::size_t size = traits_type::minimum_size() )
    {
        BOOST_ASSERT( traits_type::minimum_size() <= size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= size) );

        // page at bottom will be used as guard-page
        const std::size_t pages(
            static_cast< std::size_t >( 
                std::floor(
                    static_cast< float >( size) / traits_type::page_size() ) ) );
        BOOST_ASSERT_MSG( 2 <= pages, "at least two pages must fit into stack (one page is guard-page)");
        const std::size_t size_( pages * traits_type::page_size() );
        BOOST_ASSERT( 0 != size && 0 != size_);
        BOOST_ASSERT( size_ <= size);

        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
#if defined(MAP_ANON)
        void * limit = ::mmap( 0, size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#else
        void * limit = ::mmap( 0, size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
        if ( MAP_FAILED == limit) throw std::bad_alloc();

        // conforming to POSIX.1-2001
#if defined(BOOST_DISABLE_ASSERTS)
        ::mprotect( limit, traits_type::page_size(), PROT_NONE);
#else
        const int result( ::mprotect( limit, traits_type::page_size(), PROT_NONE) );
        BOOST_ASSERT( 0 == result);
#endif

        ctx.size = size_;
        ctx.sp = static_cast< char * >( limit) + ctx.size;
#if defined(BOOST_USE_VALGRIND)
        ctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( ctx.sp, limit);
#endif
    }

    void deallocate( stack_context & ctx)
    {
        BOOST_ASSERT( ctx.sp);
        BOOST_ASSERT( traits_type::minimum_size() <= ctx.size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= ctx.size) );

#if defined(BOOST_USE_VALGRIND)
        VALGRIND_STACK_DEREGISTER( ctx.valgrind_stack_id);
#endif
        void * limit = static_cast< char * >( ctx.sp) - ctx.size;
        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
        ::munmap( limit, ctx.size);
    }
};

typedef basic_protected_stack_allocator< stack_traits > protected_stack_allocator;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_PROTECTED_STACK_ALLOCATOR_H

/* protected_stack_allocator.hpp
xo38Htshun3vTuecmtA5Lrpdh/hzjsT2SOrQP7Zd95iopOjYTjGx0ed81jMmyl85h+M7xMS1Sqyia+f27UznQhG5thiSmpX9Vzb9F4yamJY6ODExJX1YanpKVr2GSQ0Tq5ztxz9+8n/4QB8Hz+jbuFK9cUOaNLiyQaV6nbKC/+uoTahULz0jLWNYxjnGiO8ff8aup38mdYtuF5vULrZDUne/BP5wKjf+nNGNNTvEtIv1a1JUXEJSfHRU77jo09aO7hkXHdUuITB079iYqB4dooOTzvzavUOlej08ZEBqpXrJnOFfBZJ2Cd26d4z6xT3+jQvPXlElqkViz8yMYZmDRlbqmJqWklWp5vjmTWsl9k1NH5IxLqtS19TsrMTY6ISO/eI7dE1sUr9p/Ya/XJ04xouVP+SO/1+9VcMGZy7Xmwb1G17RoGnj+g0SxyRnZlf5j2/SpPGVwU1y5v2/vs2Ykf/CLWBvuVCeMiRAKC+Oyafl1wpoBbUAywv5+Y+fNC41/fSwEwRdv1C5UKT7hV0VoUVqebTCWvCs8Gk7X+CvdtHxAf4npaSfhpFQldzPSvgsKq5/z4QewccNGzX/5QzX//1zhqTknvPv8c/Qwaf55y/7XPwv+lwx95kX5vbZNed26kyfSp/p01+fcv57nPlY/P39e5w97Tz3aP6v3ePMaae1RGWfNwnRWlqkvgXHGjk23d81zjnWyrFNIWtO5xxrnXtepXOOdXCMTAp9rkX+u/bPyEwxAX9l/0v+wv5lcsfVMWfcZ2b6r47/jZ265B7PSsn+5ZqkESkTzvu5a898/u/0PyX5fP5T9bw+3y33ea75i/mIdVzJJvRQBzGYa9OeucdmNz97LC732C09zx5LyD32Tt2zx/rkHjt+zrFEx55wrEf47LHBjv0Uprkizx4blnveF6Gzx0Y7ptwYKnvOsXG51+6POHvsltznvnRO/+bmnrfqnGvvdmxeBE1+zrEHHdvo2JvnHFvh2M+OFT/n2KP+aBj5l315yrHrHat5zrE1uc949Zxj6xx70XlNzjm2Pve5m8859sp57vdGro/vP8d+287zjJ3nud++c8f7b8ZH6rCU8/hXm/Pi0/5c/xqcGlx2xsXOxM8nPv9FEgxJTQn9FRafe9G/FQMjU7OS/zaGO5w3hj/LfVbGqOzUjPSsf+s5GefF6k7ntcUXvzzn72D1kTMYefaU/4Q/xmUOGvW3Y+963vj/KrdPY9KDq05DzZn+HjvbH53JPeU815658mufnf/a4JTTuPK144Ukl3NDuPyXmC+Rc+y58NljQ3KPrQ459q+OPyu9YeIgrpadlZ3JAH85/oRzx3/G5kM9p118bMOk9jFUZUJcTGynpOThKckjzjln+HnOGZaS7UFncf3a85wDw8/4c1ru5+d+9sv9089/rfufPWdUibP8SXlnJmWmDEpLy0g+1+aZzomOi0saNQZ3ZGZmZJ7je2N9ltwoNemvnhMqq05VUW0j6Qp1WzXXndbwVmRYu06xZ6+ArP4b61lPqkOfUs8FIC/0VAdvZS3YGuDL2ergsz1XrS9ziFqFenmp7uo6OONp68At1eYi1G/u364OD7yqqU0P/a3a4rowMOIjQP069Yn+6lzhJ/H8DGuqwXcwqH1W+wA37VPHAt5dmsIptf23huP942pn2+3HaaE2Z52x/DQ4pr6SvEa9y1pY+lD1uR3WenHUfDWUDGsmhw5bb1TL2jDXmoA9ptc8Gvy3VdS4M+3vUjv+/g77iDfy54+tx8QGuXjYd7eowwy2T/QzurNRKAfwQ7gg0J2Vct7nv7htyPsc1omcu7aUUzyvJGsXWaxWeZGfLzv/YufvVYstG9xCLZdwya4=
*/