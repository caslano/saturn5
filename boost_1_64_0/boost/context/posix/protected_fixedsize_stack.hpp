
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H
#define BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

extern "C" {
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
}

#include <cmath>
#include <cstddef>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

template< typename traitsT >
class basic_protected_fixedsize_stack {
private:
    std::size_t     size_;

public:
    typedef traitsT traits_type;

    basic_protected_fixedsize_stack( std::size_t size = traits_type::default_size() ) BOOST_NOEXCEPT_OR_NOTHROW :
        size_( size) {
    }

    stack_context allocate() {
        // calculate how many pages are required
        const std::size_t pages(        
            static_cast< std::size_t >(
                std::ceil(
                    static_cast< float >( size_) / traits_type::page_size() ) ) );
        // add one page at bottom that will be used as guard-page
        const std::size_t size__ = ( pages + 1) * traits_type::page_size();

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_STACK, -1, 0);
#elif defined(MAP_ANON)
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#else
        void * vp = ::mmap( 0, size__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
        if ( MAP_FAILED == vp) throw std::bad_alloc();

        // conforming to POSIX.1-2001
#if defined(BOOST_DISABLE_ASSERTS)
        ::mprotect( vp, traits_type::page_size(), PROT_NONE);
#else
        const int result( ::mprotect( vp, traits_type::page_size(), PROT_NONE) );
        BOOST_ASSERT( 0 == result);
#endif

        stack_context sctx;
        sctx.size = size__;
        sctx.sp = static_cast< char * >( vp) + sctx.size;
#if defined(BOOST_USE_VALGRIND)
        sctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( sctx.sp, vp);
#endif
        return sctx;
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        BOOST_ASSERT( sctx.sp);

#if defined(BOOST_USE_VALGRIND)
        VALGRIND_STACK_DEREGISTER( sctx.valgrind_stack_id);
#endif

        void * vp = static_cast< char * >( sctx.sp) - sctx.size;
        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
        ::munmap( vp, sctx.size);
    }
};

typedef basic_protected_fixedsize_stack< stack_traits > protected_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PROTECTED_FIXEDSIZE_H

/* protected_fixedsize_stack.hpp
jHPQXgl+rsojcQ6O9fo8xEf5JW92DeACgi3dYbkORo9DCn8E/fQLS2HuQvJ0odHxRRJme8B93RBWXX5F/YJZ2/2J0HD507YK95CuNP7Qnhm/EnyPlpXiRGSN6WeEg35Z52XRn/zc2MsK43+uofCs/us3ddBYyQhI16HroK34hbGz6ymM+5opnmW6QeRGnDKD80uxxevAFm82bd0tpdntzK2Q3zUh8bdD/rUtVzu4xcTdCbRuAdteLbZ9t7SXq02+7wnyBPj0lklpMHYvKNS2LfsOht+Vgi7M/tJfmL7IfSqjxK025Xs/2jbjY5sWfs7/T45O1j3DwT3Lw+H9LvWbhcZvlrHvi/ckWtpjrgdMc6OxrmRwt+pD4CMjbuTWk6AWakssTo4Va3Z2TD/vKn0GOq78HjE+7lGjs8fEFh8BW/yzSfOEpHH64TUJCTtfi2GnFww/avsvwt/ug3+2FOOhXdB9yybe9kNeLJX9RmzLsmdV7M/JiPvoXwI7XQO4gMd2+grw1D26yPM1Uxdt/OvGR66V8IHQz35Y7JD9pt6PrGM1DrtxErbNCrNjtg5GDMZrHYIU0IuynbfGe2E8NVVhMq5T3NkebWAjMI71qh1MUBVWm10HeP1hF1LAm1AHGnicAgYrQe2vYB1vMWX/lvFTjxof8Lbpgz5h4t8tzbXvsn+ZeK0F2tYPwJZ5bDIy01//2/E2dv0hyObSuzQY/5GJt3b9ifoziX8xe7+zS8T1932ov0MIhrINpfAao5d8gqEfqNlL/LDwwrhhgltm2hnX30fbroOw4mO4BuKxzOx5pc+VZcbXGdmJcPY5C7PHowhwXspxFmOU8hE6tj0dUwZ+z5x7wjs0VskdSnsZetbPjSvD8s4+EzdB+Dk70XNamgeCsXz2jd6I0gQcpFlqZLJntSZC/EsheaooyzwLdgnowOHY80CVhL8e5mPrltTTnNfKmswJUp0fNdFu5jPWVLe8hibKljfI3J7BaVpZUxOrnd9YS3d5wBzp58tkNkTvbsiYJM2O0XlGvItJ6wnqd1+C4Z703WQd+FwZs87Og/1po9mHhZ6XngZ6djjWpqcLn1Lps4wlPnq/a5TtoSXj3d9rCYFKPJ7sTHS3wX0ds8oGsrZVzbz2LwvePdfx62yutBv4jltd65tTJi6TcRfVNMYo3vlM/zPtL0nO3HNV/aT7YhmsjciY4ACuv7RmUMbfrKs+acPnQd3uK2CcrLeAq8vsu+NIL/ud8gVlembe4stP0xXYtDt7i8qkTwHy6A/7FIstD6YVzsfyqCVY9pvv/ck1zFtq0wgOprNplokdjtH9oTJHU18m4eG0nk40h6dpDkT+4V4DlMcBgoNpbHmsBJ0ivn2Pvolg+OZzNdky7k99Yc/sPTsuDvczrjF1nMpH+iQBX2yXvxpS3n3u28h2CMEHpKuCTF3FdmC79s38ZsXvp5wRv4XCIXWN09i6Fi+TfoHE4RiyTelCuDS9blNTv3Dl2gb19XlU/zVcAetuh5exF2vt6PU9tf/t++axaVoLFyxM06lZuMDQ6PRp8G4UJiIBopL2oVdwP5w9D2/Wk76uwPjl/rQP7SZ6hQPwoZvAP7MEseC9ww3ODzOMsiOwLufnGMaibte0hQzr2BRvYRjbUTHDgn5+gtJGWFaSU/Y+9oBfnurw6Rnn5i7fxaZDJGfoukVufO7f9pbBuB/uekkSHNvHlKl/w6V93ARtC+Nr3RH83aG+Yv3Uuo6+fKu2nYCD9XFbznqm9MJ90lEEy6GbdjkW5OtGQ/K+zDFlQV/7G6KnlXm4H6unuZXiNZxv1uL2GsnjO0+/C702/i7icqcyb0vxPliNj7g5brYthfG8N90=
*/