
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_TRAMPOLINE_H
#define BOOST_COROUTINES_DETAIL_TRAMPOLINE_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>
#include <boost/cstdint.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/data.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Coro >
void trampoline( context::detail::transfer_t t)
{
    typedef typename Coro::param_type   param_type;

    data_t * data = static_cast< data_t * >( t.data);
    data->from->ctx_ = t.fctx;
    param_type * param(
        static_cast< param_type * >( data->data) );
    BOOST_ASSERT( 0 != param);
    BOOST_ASSERT( 0 != param->data);

    Coro * coro(
        static_cast< Coro * >( param->coro) );
    BOOST_ASSERT( 0 != coro);

    coro->run( param->data);
}

template< typename Coro >
void trampoline_void( context::detail::transfer_t t)
{
    typedef typename Coro::param_type   param_type;

    data_t * data = static_cast< data_t * >( t.data);
    data->from->ctx_ = t.fctx;
    param_type * param(
        static_cast< param_type * >( data->data) );
    BOOST_ASSERT( 0 != param);

    Coro * coro(
        static_cast< Coro * >( param->coro) );
    BOOST_ASSERT( 0 != coro);
    
    coro->run();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_TRAMPOLINE_H

/* trampoline.hpp
irpg4l2oRMZyM6JEOLmqlyVThbulhQV5NhQSFC3LFg5TGVXNEihErVquiYQVsmfaDEpwZaqtC1E9CURZW6C8lhzLoSwYlwkU3oWaZ1TaeCtEV6VV2Ur+Ssu23DMQHFlBz48giHqwJIopF74G8WV4HcNXfzbzJ/EcwgvwJ/MW73Mw+YTeYFhVAr1bSaqQhQRWrUpGsyfFf+hOd7z4Es6vZ+NwGicXwXgUB1cjOIDe/iH8UXPj6/c96JVsaRoPh97BobeHE+YtoURtEkW1aTFe6CaFgNElTPyrkfMCdfEObtD+RllrAZYSkwOaVbSTXNJKaDMoUcuUWrRoPgmnURA5PzGelnVG4cSUb6xYnDm2Uipw/jmrvvkCuwWapESvPGfkQin4jSFlKAyObbVPo+h8FkzjIJw4U4JtIDbKgyAHNBn2eh/zWj3WrCxxd2haNS7/v/U5j9aHu6euKNfNpkZMgeYl3X7Ed0m/1QxVwK9EP1ZGUXlLpaMoz1TjWIsu8buxinU/aSa/1VRuGC4wFVWFEtit7izyYCsT8mU8F/2DwSKf4tbgqWW8RiNacAw2ogWTi/BBtSbYIfKmWUKKZl9Ss8HxpMlxA5n6knCVmz0l0M74lnaLaI8kS7DPctwpm4HXCn/hX49jZ8++TWdh
*/