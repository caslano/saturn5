/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_0128)
#define FUSION_END_IMPL_07162005_0128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::concat_last_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.concat_last();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
xvWaSdwdNf2NRpdbX34BcabdvInwW1xYQdhThB19MQbT64fINkcE2BPuwwLXDeCntF9O9Tz6IC9rX28z+exsWDM9vtLIY7vgLP/PMXoesfnB0nou4cRu8hhvR5TWpk1QjnuNxMlNVpb35ws70ydzGf0FnbU3dCv685NdG2KwVt8vNJjRB+t4vl8ksd3DeybdFxucPIXAZb1EYOQBB96Hv9TgTIi2yftbSI+jN99Zeh8xtrL5
*/