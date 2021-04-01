/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_0903)
#define FUSION_BEGIN_IMPL_05062005_0903

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category, typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category, first_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
96PObHj4ntFuWj7kLUlm+aJDdNenyCviGqXbjj8+koR+UD4qfeNZvF+M6MmNzfMf5cw3+Md76VHk7T2EuCg5jgqilx2yAXcMWaxWreToBsZJt+o84Mcu+LlR7Daa2M8NPl3g5OCuoFmqTnH5TMu89IknyURlCWjI3glQ19DXnd0bDfqNUDNVG/ytr7B7k+Lq1yD8noPZ+AWbLZfCB2VTyUZ9X33oVDxJlmrHNEU7UBcyl09S/nFW1bnBUaeXl6z8yEcSm5kzAG37w2lajDNaCtPnftwVUvWspmi506tT7yTu8hqM5iW3WAQtIeoI9/VfAbjL6OlSwpiVTLybhD5yq1OwX5TAs5oM7+JjDWUBbiMBLQZL6rn0tIjjbmLSsGUboIRsm2zclX3Lwe6BvgZIQrQZ52zjJQ0iFUtFKpreNsHi2yFvjU6iRsF0e3s7cSoy1DmPFPSScDuxKw0/SOoRH3z4cRpNv49yRHYXeygcYxfrM18m01nIOPKWzVFC6xOBEmVcOjpWQIuPBQZtuUmHu+k6bEU3PfAtzP7POdAi3FVYhT7KZ70QhRSq9Q==
*/