
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_FIXEDSIZE_H
#define BOOST_CONTEXT_FIXEDSIZE_H

#include <cstddef>
#include <cstdlib>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
extern "C" {
#include <sys/mman.h>
}
#endif

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

template< typename traitsT >
class basic_fixedsize_stack {
private:
    std::size_t     size_;

public:
    typedef traitsT traits_type;

    basic_fixedsize_stack( std::size_t size = traits_type::default_size() ) BOOST_NOEXCEPT_OR_NOTHROW :
        size_( size) {
    }

    stack_context allocate() {
#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        void * vp = ::mmap( 0, size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_STACK, -1, 0);
        if ( vp == MAP_FAILED) {
            throw std::bad_alloc();
        }
#else
        void * vp = std::malloc( size_);
        if ( ! vp) {
            throw std::bad_alloc();
        }
#endif
        stack_context sctx;
        sctx.size = size_;
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
#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        ::munmap( vp, sctx.size);
#else
        std::free( vp);
#endif
    }
};

typedef basic_fixedsize_stack< stack_traits >  fixedsize_stack;
# if ! defined(BOOST_USE_SEGMENTED_STACKS)
typedef fixedsize_stack default_stack;
# endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_FIXEDSIZE_H

/* fixedsize_stack.hpp
SOPlp/FzM55BfAPn3+v3jBwv59jz+KzLkz8fz+SxZD5X7NO61Mp7ntrzNzIuQjiak7TKfoHgX5T+B+H9Y9GXCHaTiKUvEf7s5Sw0/mD5sFeIxqsynkFYlp8/nnmNcF4nnDf8e2jteAATOQ3XX/j2uRrf9dsKfTZblNZj/K5C2VwmAZ4j4r7fxLigQ50ziTh/xHhA9Xga57cYB4T0+Zbsk3DdBZ4tg8VL33WgA04PUzX+nzA+6Aljz0bnqW0LAntD+Kc5edYlTc0/loPC7P7JG+e9afUjb1l69Ta1wTuyjREOLquN3yXYvxIs2oNF529Z6Gyy1/YT7IdWbP2W1k3/fA7Z3GbC2+LDY/jseB8T3idZeLvUquNnBPu5pceGN8YxevwPwvnSh8N278f5F+F8ZdmzKcdjz6oTRPh+lVYZeexrAOEMRBxZBvdr1twwwQ8m+Bl9xujG1v4CNIcIW3sPbc/Y0ftoe8aOGGe0jhths39AISOtvyv+3HTER1jcv8OQQINhp1C6skOGna7iTkHzIxWPYxrTU32UDhElvU9VHE7pkt6xDJuMhOJwyzhMu8vKZ9wvVDyO5SqzNPL5p4rHOd0xsKcSHYI2+w5UPG7yXJmv4b0IGtrl5wpOZ1ljLB6OZIO9mdMZFuPxMJTVG5H17K8+60rpzNegShWLo3PD5yHw/HN8xsEYroPZAQxrK0jn369d/2WF2P5kfdZ7H3vQbC/IqdIPbmPZzbaVyjbV5Y83hpIdDPPjmDlYC6eUcMoUDvtbxPH62wqCq6wUvojgyi0/WU2wNT4+ctv8CMLZnm2+n+/sCGO/OfqwIbynjmH1meW9mIRwPC4w9r8dlDdc2H95Jb53j1NjIExVpbJrf186weozhwPcFHVmhx5quYvRUgoH85V9d+bM3wHy5xidBBkpWw8mEmJd0lAQ8Eihk4cXsC8165qPInVZtc0ooyN4z3HWaEt3diLd2RH+K6gx1LZjK/PtAUym3PN58daUu0tevLDBC3vxdiO8XbPjdbloXcbedgecPGs2Q3L5Gj8x7p6E28pnRVt7vXatpHryPgB8DrvPe+hnd7y4V6Uuk891GQQh896Vhe3PujdvTJoK9kbsmDQZ6Ygk1eEyKS5/I/aFQaUICPeaWqdC61YZZjzai3dv6zikb+s3r08xe3fM2a/KbpRJ6/OVt1Jr8oWOTy9g36/SQZ67mGj5qNpKdXl91CTSyX0I9jn+ngWWm/DUeYhV5024jsfe45uIRJK8p4HH9vFEJBnEg/a5nuNo/M/PE1z75v6d1+oEOqEx2l3/BrDTTRzRERflzJHpgVA8E0tj/L01VHSykGNLwfG3tmNlvzJWnkIy21/LjN6L4RyqnD/Fem3C9SPe92IHED0VU8qzSN6y4mKVP62S16goWt64+HvMlxljunO6fl4UPe+c7gzA5zryeBDKQlozNW3kST4rHni8wLgKR/aRcyrFWL0k+1j94EqeO0AeYS1z9v5wLuurmXc3Y+ccsXYz09b0/OfvEO1DK8Wc9kBqR1xX4ZVdIkc7thFv5e48kuSN283L22HMm+A/g/S99T6iUs/HPIGxClZdn8tOz+qr6ubsoOzrU47hdnDXwfjfaQZIBousGCVYqegiPOJJ3tpdumr9SXa64Uozd7I8y5qIDpYD8qb2KPreuWJZXVyWC+ev53EAgzbj8u2nxzbTzeUi77nLjTH/CGfKBB6Q/0SleR8+Wuj4TjgXxnx49SVZ6V1/Adk8Z4nlj/bhGr4zzDfCMoy/bZYwnAvD/Hnhlon6lWeZbzux0jsfuA3wKp8Bz6OPgE76yOX62+lUy5ar3fVT3nbdQutITpfwuL+D5zS9z9OtZ7A=
*/