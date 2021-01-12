/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_09172005_0751)
#define FUSION_DISTANCE_IMPL_09172005_0751

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct distance_impl;

        template <>
        struct distance_impl<vector_iterator_tag>
        {
            template <typename First, typename Last>
            struct apply : mpl::minus<typename Last::index, typename First::index>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename mpl::minus<
                    typename Last::index, typename First::index>::type
                call(First const&, Last const&)
                {
                    typedef typename mpl::minus<
                        typename Last::index, typename First::index>::type 
                    result;
                    return result();
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
4l87vxw/zMfx5ToYkeG3Ff2WEZR99E+Nc+ssyy9vYe3y/Pbh1yHUKuylHutaZfvtR0Vk+mXy4vXL9WtWYZftFyvXDxmHIttv8VzXJ9+P+yvrLuNvCCpxMXL9UKNQ5ag1qC2oXajPUDlLgk5/1DTUUtTVqK2ovagDqMRzkZSEGoKahlp67n9Wlt93uf7d8v9mFcyaW1QlAfB7y/87lOoY2WTrVDZZG9qM9jARzidPebmZcxLm
*/