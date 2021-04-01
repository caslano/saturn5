/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09242011_1744)
#define BOOST_FUSION_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <utility>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                typedef typename std::tuple_element<N::value, seq_type>::type element;

                typedef typename
                    mpl::if_<
                        is_const<Sequence>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return std::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
slPK7gCzGRlU2eg2xeOK5HpI94/ep/720EtjdFc2qpbo+siD+rUlvoRcgX8+cZ08xTtn4a87O2/sCoq3NznwZHU+VOHYQfitHTs7V/GyqllhA2cQ+mJFo8+/fJFE/SYkW0vUq1z1ccapzoRqx/kcSSqEz5MpEwITVOPHudRYhZ26B+draY3RNwRUA0t+hLbaYR9clxM9WINS7sC4B+Q0HWNngQ00y8tjV3yPQywXKUeaJxe/XlVwl3SrNRvC1jwwmOXA7WVm0AaDgyCciGuKGHYKISOnnPvIGSYGCM7jBIkXODSj+tTOvTEXhl9IDiZEolRVFod81meRiOZR9LOzFi1Zumi7O0ikbMouWM7pk+CIsh5RuzPT27s19nAOcO1Z0IxOMcamEb99+4TSIWIoOaXGi4FH9p55lh/y5op9DWSIyJqXTpQ2o3QQb9ADPAl/unF9xk+QGusxoF4UWx7HCmnUZ/IQ71rgIn1v73Uv+ofU91QcE23Wm1ICXcGEp2iXgkWNP1qoKWYYL+QJ+ineHzjkHStXorvkFvVm8WfIvcasDAwOL6ktjP7H/g==
*/