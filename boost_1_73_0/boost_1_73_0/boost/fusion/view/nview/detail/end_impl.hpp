/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM)
#define BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::end<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif



/* end_impl.hpp
YeMFm4HPIOw3EApQ6FmJfVti9wq2X5leBPWfvhRC24V8Cs0UDHW2Agqttcy9GyGUShgOftdQaL/EHpJYXOjg2NE+EzvZZ8oyzafo6QEatnIsLlHwva/KvcclNsVvYof7TexiCF1IoY0S+gBCSyl0WEK41s9P6QuhHoSZ/hMnAsYk9J9jAjzGQ/qvSfrP+eE6dWas30QlML7r7EvT47EB2aBAMST8GH6lPvYcz/P66PgUU+KS2AhKGQig5/hX4Zc=
*/