
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_TRAMPOLINE_PUSH_H
#define BOOST_COROUTINES_DETAIL_TRAMPOLINE_PUSH_H

#include <cstddef>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>
#include <boost/cstdint.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/move/move.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/data.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/parameters.hpp>
#include <boost/coroutine/detail/setup.hpp>
#include <boost/coroutine/detail/setup.hpp>
#include <boost/coroutine/exceptions.hpp>
#include <boost/coroutine/flags.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Coro >
void trampoline_push( context::detail::transfer_t t)
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
void trampoline_push_void( context::detail::transfer_t t)
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

#endif // BOOST_COROUTINES_DETAIL_TRAMPOLINE_PUSH_H

/* trampoline_push.hpp
/ZvzY2MZGBLD9NtsmDKIpoydaP5w2/1L5ZbXwYoj+GoADbAIXtBSv6lOV5Z0bj46hK8OrmbO+VIeuHrvOFrEfS4fb5xH5FNqNjH97LnRl5EXiiV6v94Yc9WAP6TzD9jQN0HMNLa34F72EYdJe4xTXnJ1JgySE81sTlNbX5tS0f17hU/vWy9ujudlWXtpFHwPkzyflrqunrqEWv9TntFkK50RrInw2zgaKOVd89pWzvIgPRRgfbD2JE4ffgE+8MfGakYrI2nGoO5SPnS6Dt7tNn47W85xjT7Snavpo2vZ9fLRtPFyfoULShxX87Bu+4k+7LgGHsD/mM/xy1xa1ZyvZMsljfEXfGsF26OPO2d5GM7BfBrg6fW0U7p82/wW6MNv3PcUfhkGq8Zt4Wv0xrRWbNlXH8Nhe3ojfJcf38Fvb3yNP/jdG/a8fR6sFzSBye3l6T3gKrsNd95w2HTVH4zTvB18zNysgAnXiI/L2FqtfuvlsNccdSiAd1pG+O++4u4b5Jl0U7P55qQbvsJFJ+LlTnj25jvDoXK0XUV8dKP4CjfGS+ofu4I9TsY99lbzVdAcVmETnNheXjhhHy0Th7Pz05L+/uolfQ7yrT1463UcsxmGrjcGeDhmNEyRF1XJNr84IliTKJ7Jj3HvycX6/ydjUle9kgYqOJv2GUvT04KvPkRjGP9D4vLH/PKdpfjUM2Nm0BjZcgX1jwvM97dy5XHyjQ7f8pXSMHCBWAreT2OrjXLqtL4R6qOR9By9mxChJgoj8eUr9gxOuC6oeeM3vP7ow+7dh2YcgA/WwCtzW6Ut3BADVQrBDTg4sBJtqL1zj3yJnpizFH4F33NfRS5zqWdN8j7wevtcxEqhObBCDD0/lKaJMZ4txiJ/79SQP9M5P37nvp3U4/Op+8TQaPp65Fljc//S37BpEePKj5cvgc0/q+PfBTt249oRMLQ8W5vXm0bQD3R39kw6MBImPQPzg/dS1VeiaMmmX5kztYyELuYwS322tdy5KS2+wP5UmJT2ZSRRrX56gm3F5NXq2Lc0CxkvXo6w7hDsa4GlBW83ng3GFQ8X4GWRgvoBC0pHiSt+1VzOnKm2GpeX9pX7b6Wfw+vF4SwY3Urtu0+kd/bNlzm4id7ZeyDnO/an0Jj3wPkksf6VPOPYPn0yv61g1OTxnvOp3CEJj1Zy/Jh1W3qwoPrrGn3sizM+D2pr1/PBmTQXf757nWtq0tOx4okP9J3n+TTWQ1vFIu5tIC5PDLFGSHdEGuvQYF0Vhu5z/50/mPO68tfpuAMvJDRli+C9d3X0P8KuFfbbXOD8t39Do9AYz8LoTam07498aA//uIjugb31P4LLJdV83pW369ct1rtrLpLbyfHCd/J5dacxYr8NjuglJ0ilRU80pEuewpPT2KwLX/yd+JJjT4Vp2x+GUzDrlgg1nzAM6arusKFhGNRzrBC8FFMT8oSWRvz8cx6HfuYrwb/sm3MaqRK6Y2ZwhEYI5S8T4RqHQpdqFMSxuFBeUaqu1CIxY1RKelbGmMzklJxfs9LqDR6TmjakXsP6Des3GFpvbFajBg2bnflsfNMm9bKGD8pMGVIvMyUtZVBWSu4ZoY5n7zkkZWxi7nV9ohITMjLSshK7x/u1YZP6DRvUb3RF8Mng1PTEzhlZ2f2aNkkcryWn1Y/uFx061ij3PvXrJ/pf7nNze5OYnDlhVHZG4qCUrKAlJQ9Orp9sPIP/9+NJzPBxUlb2oOzU5PqjhgwOFQrnPKNezP/wKZX+p3f7xTyp6clpY4ak/I9vnnvX0NfHj/1ii/M84dzp+icf/6vdzT37zGkdevSMjo2P75bUOz46qV3Pnt1iYrs62iG+R1LfmNg=
*/