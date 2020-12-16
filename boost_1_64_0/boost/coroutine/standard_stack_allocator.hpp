
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#include <cstddef>
#include <cstdlib>
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
struct basic_standard_stack_allocator
{
    typedef traitsT traits_type;

    void allocate( stack_context & ctx, std::size_t size = traits_type::minimum_size() )
    {
        BOOST_ASSERT( traits_type::minimum_size() <= size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= size) );

        void * limit = std::malloc( size);
        if ( ! limit) throw std::bad_alloc();

        ctx.size = size;
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
        std::free( limit);
    }
};

typedef basic_standard_stack_allocator< stack_traits >  standard_stack_allocator;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H

/* standard_stack_allocator.hpp
vrM7mX3JDgh397n2OT73buN/3rzyf//y+//fmxmjrtye3Na9AYxyQW3db9SV27r4PZqSc9jQ0nNgTqvngCvGv/P6WdaBa6Fxa2i9kLjVso6uWw8YulVA3ZSL160CX4huTbCc8yJ9PsE4Ppk3Ope/xU/ii0WdSmcRFlu1Uwk3LzXkI6SeVGeZse7nq7PcsAchdS7ax5bwjKrluY1u58oZV3ywtGLOeFPjytet9qrk6xX3qh7pF3JdzrnKciWPwYzJHw3Y+YqXLXJxj1nVM3BUpfM0lSpd+DvRDP66XSFyONOSt6sYk89V4Coe7/+2X2C7TLq+pgLODFy25V5sPk//9p+VDZ5lifn/XAnzs8FuruVzxnjM75qAEmR9eCHAY7lKyDse1oXWCXkPwvrQOtI+hHU/5nNGMt6XKxiIX44/XrVoRz57az5PUGne0ieV/qCOp8I3c1YF3w8lf9PXqCXF2o1C6xlPpJs82hA6dvnbatbf/nXmmLj2h+D3H7OMuZrvPAnIDheoIAUIZtvzu0nvDNLf+OTzZMnPdmzqJ13XjwfyUJ/Rh8V1d/GEiWat0HeveMw6+kd2TBl4o595vXIb5vq+adbxlZT4XzgZnE2F58AaVfpOZuBLds48oy3rOi6PDbWjf3eZcW7csp5UyZQ963pFzsBb23QFDu6zMocKNcQft6GPXO7Lekz2QqfxvoemlWUicN38lop1G166IowsKgn0J2H5dxkzdiMkfoRmGT82lvpwFRsfSaQ9mV5s95TY8h2FJbCxsSkjxntgAztAJn1Lv3I6RGlcmv5ephL/sMw51/TTAl870vX+4vGW5xzPyLxYEXtY7YOMiE2LN0/UGXWk3KNFHZMnW406eu+6Xuv4abuBn/ZxfdRFn+f0THA5rM4NvmLpJx5gTVJH8wWNhDirs9jmNfks9o5+Qbpsz3eV041T2OUb7nKbu806+p1B+scmvWIOfW/APhrdVYz79pn3BIyi3J+5T115TFkeu3z9QOXrvsJiV16w/0MV+q/4jMCXFa6FxvxfyeOz6Ptr+brUdwj/4b7Mw28MLOq/JvHwhEE3BmTq0SkDl1auf1qiy/V/gO6XIj3VINX/0aSDrkQgjv4F2vo27ClwffRFyyqfC7Y8T/qRJc76jb7SElNtg+IHpqWnxFs+MyJfl58ZOVvpXvmsgogOYFPpumhn3hd6fkR+Dq28nhodUs/yHVUa9eBehb50PlaFfhI+/qDxjpOLjpl83sIQrPq5xENznOc+52yreEazXmOjXuDQb8g8vsTe6qcP8RolWWQy5HtrREvvZswzP4toylctrkM2qME260T781v6tAznIY1Hb9O8EPzmYFPpm4POkrIexhsHrK5FSddMX9JAXzePPYvZm/U9HQJ9BQZY8exKQ2Mc8rysr+meLqjLjbiWVcIy5uibW0E80qYVsZHNeIuvN8dZbPMPxlZc4tWxmsmzy7nfVuYJXJTioes7WH2zUkfr0rnVaIs6lc5HtvDzPsBd41ip2Xc1rjk46qdjCY8jOKeW/nadJcYD5Bb1Zf7IdFcxLUnyJF8bz4fu7Vlu6TxwK67pz534093SO6DbQC+vbWR2zXVtdrkhD/Zsc1ztog1avmOC3rdJ17+f6J/1xX0n0a97Drc79B1+Z4O6Z9jJrvTdti17ozVZMyMHGW7QTlcL0iINWuMqQVpPg/Z72yCtr0HbqAVpQ6AVQ1shgrShRr0jUh+JBu056d4kg3ZNjSAt2WivphqkpRj1XpbuzTBoL7UJ0saUj0+a7/UG7Ywxj67n4zPvD3G6HJ5M/dm9EqcFnqkbJvHYXEsbffAtsASb/mieJKtZ0PWGbGX+C6ZM2qHHp6Q=
*/