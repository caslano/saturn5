
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_POOLED_pooled_fixedsize_H
#define BOOST_CONTEXT_POOLED_pooled_fixedsize_H

#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/pool/pool.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
extern "C" {
#include <sys/mman.h>
#include <stdlib.h>
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

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
namespace detail {
template< typename traitsT >
struct map_stack_allocator {
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    static char * malloc( const size_type bytes) {
        void * block;
        if ( ::posix_memalign( &block, traitsT::page_size(), bytes) != 0) {
            return 0;
        }
        if ( mmap( block, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED | MAP_STACK, -1, 0) == MAP_FAILED) {
            std::free( block);
            return 0;
        }
        return reinterpret_cast< char * >( block);
    }
    static void free( char * const block) {
        std::free( block);
    }
};
}
#endif

template< typename traitsT >
class basic_pooled_fixedsize_stack {
private:
    class storage {
    private:
        std::atomic< std::size_t >                                  use_count_;
        std::size_t                                                 stack_size_;
#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        boost::pool< detail::map_stack_allocator< traitsT > >       storage_;
#else
        boost::pool< boost::default_user_allocator_malloc_free >    storage_;
#endif

    public:
        storage( std::size_t stack_size, std::size_t next_size, std::size_t max_size) :
                use_count_( 0),
                stack_size_( stack_size),
                storage_( stack_size, next_size, max_size) {
            BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= stack_size_) );
        }

        stack_context allocate() {
            void * vp = storage_.malloc();
            if ( ! vp) {
                throw std::bad_alloc();
            }
            stack_context sctx;
            sctx.size = stack_size_;
            sctx.sp = static_cast< char * >( vp) + sctx.size;
#if defined(BOOST_USE_VALGRIND)
            sctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( sctx.sp, vp);
#endif
            return sctx;
        }

        void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
            BOOST_ASSERT( sctx.sp);
            BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= sctx.size) );

#if defined(BOOST_USE_VALGRIND)
            VALGRIND_STACK_DEREGISTER( sctx.valgrind_stack_id);
#endif
            void * vp = static_cast< char * >( sctx.sp) - sctx.size;
            storage_.free( vp);
        }

        friend void intrusive_ptr_add_ref( storage * s) noexcept {
            ++s->use_count_;
        }

        friend void intrusive_ptr_release( storage * s) noexcept {
            if ( 0 == --s->use_count_) {
                delete s;
            }
        }
    };

    intrusive_ptr< storage >    storage_;

public:
    typedef traitsT traits_type;

    basic_pooled_fixedsize_stack( std::size_t stack_size = traits_type::default_size(),
                           std::size_t next_size = 32,
                           std::size_t max_size = 0) BOOST_NOEXCEPT_OR_NOTHROW :
        storage_( new storage( stack_size, next_size, max_size) ) {
    }

    stack_context allocate() {
        return storage_->allocate();
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        storage_->deallocate( sctx);
    }
};

typedef basic_pooled_fixedsize_stack< stack_traits >  pooled_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_POOLED_pooled_fixedsize_H

/* pooled_fixedsize_stack.hpp
naTOMVZvMbBi5jHPmetoD03iTGM3QepUGjBz7w9pmNnYEkyml0kyMs3Is5fp5Pj2RqbKw5P4PkSyIzSltlYler8PEW6aj4nSxpfuM2ECmQelP6pho0kQezy5zKW9BMuLhKMur9hO5rsXHfFkT2skFc8kQ5HGsDqmBCYfkvLbGi1ckvEPyUin+ox0MhJunCnpRRPIu+Qn5skP7uv5rkiSfIzfd20Hvmtpgb5rVI73oMvIb00lv3WCx2/NboAD4+rmBprq5rm2b6UB7T7OF/C6OaSRI4/0Yznpx3ivv413R0PLeC/BSci3csHYFvgOlc+6OTmL7/X7XeFzZTlkxzPjPcForAXLVLQ5fwjbrQRQa1yo7FOzlB2YB1/hhOlgLt+bms/vs6znL5jR1tpgNwEnSxtdYfnZ0y2/fwb52TPz2nIoHusIRHvi4Yz5dIhMM+vmVwofv0qMkc624opzquCy4opziZfV+cZq5M9oGQZy4kkhnTnfqvcFVr3XUFkX5u1f5h/e1NAWaHR7BfFM5VxslXOJVc6lVM5lBk7xZubLhYyutGR0VRVcloyuJnrXEOwYT8xzQjwmfNUQjHdw7QDq4lqpi33UrTbHPCbGa4xCj1Lf1mflK+qejXcd8pBUaO737Tf8hz7resTPuD5ro6wn8NwYbk56+TZJec9mKtDfqTa9UbTpTaJNb7ba9JYquKw2vZXa9LaqPs8VS2SSiXjKrYhMM7zcLnj5QZV3THsHPL+ZZd/dncTDDwl+hUfWVIRca2adsztExD93AY1SOmeXMc0eLnPOLp7VQXPMZh1IJpWkdR9TKZ65W7TnhALlkF1/MZzDL74hmnl09fceYaf3CDneZ9n5/dSG91K8+mOS3wNVed4DFOH/8T2JKRPvmZeHLV4eIV4eIl4eJV5+yv2mtEWUf11KH10jfUWCgx3Xjn4m7ajAeC6r7hZog/i+Q9T5CVHnp6w6/5zq/CTV+Wmq8zMCf4XAf9bC/yXhn074zxH+ryw4oO9dU0NwvxHlXCzKeUHY/ouW7f+uSl3WXg2it6nv/jdL9yt6X97bYfH/B4v/V6i8VzVcX+NLq9H86exzXhMyeF3I4E+WDN6ogsuSwZ+Jpzd5rJY/fpQOGLnKmkN8vS34ekfw9ReLr3er4LL4+ivx9V7WPq0nKr8DOIS+g8V97fvSdvroN7PXt66+vmH+/MDMhvn1rY0tbY3NTYzuzzE+40Ohlx+Kum+29GIL1fXvpP8fUV0/FnPNK8X9Kgv/M8L/lPA/J/wvBM4Vloy/rOL3POasg38S3r8E3gtWWV9TWZfosmCijvZOVLs40M4FnR+LEwTYczc0tbUegeLMlena1MBqrx8dUI3j/Ux3t+nLBmFaMtIdTEd7Izqd45uS6sLim8k54pvBiG/KelSfl5bgd918FuaQankW5szG+W0wnmpsavOEL3Yy62ABa1wAp2F2g3tiuj+H37VIeZnvViY7g7HoCbjsU9djG6yXno+LxVPu2aTbVkvb0bN9rQ2zuAZugv1uHvpi73eJSU+2q843njAC8YvI2FVZtfW90mpvWRVUVqWGs7/jh5ecB68m+Jrqgs6rtwKXLOnE54hq/3mZXPb21drmdqCyR/phMSaTc9OjCHbHLLCKnoTdiWDHEGw7tf9wLLczYn/P9DvY/pgeCaXNWYGjq1W7q+3khMDnMUP6cEx3EdxvPe0sdGb0N5jXy93vWvsAvEnm3Px87Ujf3Pe3I6f723Ec0WOfsBvWT5Vr1kgPwWcdLKu03VFuOnbeg3zCHtInYH1kRYx+vyb87+uW/92b2nkvRUvZNbXzd4X/PYpwatmHoZ5HYzA35e43moj4QR1BRDiGSLk=
*/