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
cD9cAw/Ax+DXcBM8AZ+G0c54AJaHz8PRcCe8Gr4MF8HX4Cn4d+iMt96FSXAvTIMfwovgPtgS7oe94MdwIPwHvBJ+BrPh53Am/AJeBb+Ey+EhuAoeg0/CE3ArPAN3w5/gx9BbHv/DKHgGBuAlXtod2BEmwt4wCQ6GyXA0TIGTYTU4E9aGs2EdeBNMgythA/gn2BBugo3gFngxfBE2g6/AS+D7sCXcB1vDb+Gl8BR00ukM7A3L
*/