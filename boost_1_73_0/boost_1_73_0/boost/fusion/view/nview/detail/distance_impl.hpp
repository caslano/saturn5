/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_DISTANCE_IMPL_SEP_23_2009_0328PM)
#define BOOST_FUSION_NVIEW_DISTANCE_IMPL_SEP_23_2009_0328PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<nview_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
              : result_of::distance<typename First::first_type, typename Last::first_type>
            {
                typedef typename result_of::distance<
                    typename First::first_type, typename Last::first_type
                >::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }
            };
        };
    }

}}

#endif

/* distance_impl.hpp
4PCH133JXN4RvkRMYk8zh/H4bTy8uETYpUP00h1EM+va/X6HPlcZwjVgHKs8t0kbviP46/SrMz1rf4fzjSpMHbPoNOdfVUUEX1rVrU6ySYs2KYmjpF9rIOJReI49ZX3NG8KSTEHflGkfvisat/yvsNNmFmMMsEBcLMK62wRB46o2dT0x8OylLIX6C8XIsMxkfqEhy49WmOi5sTLYQdbkCpunW5eHaqLrht50we+N/0F7E0lEFUlNSg+YgjW6WjCOtwnXgndSnP/BIjgCDQA42gKCEyMSdPl0HdCEK6fRaIaMDVSPqzZzMmWeb7JCbA8hOo+dQnpfEc49P0I3zCmnEQW3JjVX+DuqQL/IBHre9q/wfrwZqO34Pxjbtmg8eyYN+sf+n50fsVDTciHSztvNSBv8W7SQeQ1Z7aIG8dFyka2yxW22zxK+vrT+AVBLAwQKAAAACAAtZ0pSGPmah7QPAACNQQAAGQAJAGN1cmwtbWFzdGVyL2xpYi9nZXRpbmZvLmNVVAUAAbZIJGDVW3tz28YR/1+f4qzMuKRCUZKd6TSSo5QmIZsjimAI0IkaezAgcRRRgwCCAySrib97d+8BAiAepKN4WuYh4h67e3v7+O3heHL0dJ8DckQaPxb/z4IP/OUzJlHwb7qIy0db
*/