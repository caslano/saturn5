/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09272006_0725)
#define BOOST_FUSION_IS_VIEW_IMPL_09272006_0725

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
EGRMFTaSNtfvw6liDlapudSlY9mbJc4F1wdIZyFvBhtfoHS2ubi0QX0CEdnBdPFyFElxQzbzCezTRqSqA8Ecf/0/E8wuLphdnRTMvaK4YC7RJ7JYout8RhdRFTiFLc8VVLWwbI4SVaqZKtWPKhDLBNMvvCdRisWnOFWnOFWYnVS2BGHbW3Snv8aM8eReMWMgaYEzvm9qkBlDzPnnGd+YZzIMEXBSPEXwSeOvCDFpjOAyvd5v0vge/R8EEfZbWUQTaFbDmL0kqLBfFdGBsP8Pi2i+DkTBJbJRqKwXWoLXP9GGMBeF3gUf2kFo9Gsn6pb2IVE3FT+NK97PhVJuxP8uXHH3AKLubJFrW3inRF0oVajTizqTPLvl+9PKs5UnQJ5lfC/k2fITJM+sZnlmPZ0809fSeEb2zHo/bdj931kteM3TFa54bF9+R+dWK6D9+3hatXK2e8NcssgTHhzSw9XOtJc4qFS4+WrHBEmkOiMBgH1kJF08nHMqDp/9+FOyCIjeGW0UclKj57GT9DzE339mT/b4gT3og/PbxK+z+acbedL1/NMP+fNN+vRlHv0sfz51EoPL6eHliRfDk/L9vFWUUNVKkf/miabjs069lj9d/JmJz63qFTxdMitKXcPaD3DaiYoz6dGbHhI9YugRBslLKPmxv0Xho3Uy0vRfw1upwF1/03MrPneom/4mAj76mwhYdQozXkmPF+nxDD0e
*/