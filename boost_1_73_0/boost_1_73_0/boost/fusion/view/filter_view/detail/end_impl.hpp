/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_0906)
#define FUSION_END_IMPL_05062005_0906

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category,last_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
b5q7ZeBJ+UdhOrwZQy6Zz8hfwshBmgtS7Asn7EQl67Uqg6OihEicu0CGwy6Og1tI5jOtmWmpvjCLFPq9iedpPI2wMUAxhmGxIcXn6q8wixg6D3EBJi0mPGT9Gj6+iFCMNKV5RJnEpJzLOwGIsWad5ciTg34eRMWQTlP1F17AFcFInQkWV5p4ClYJKZIDxLkCKsSyVfD6AD9ioOEMERcr6eg7AbHS9/Du052Huzs7TEbRBUoFGwUhxg/NdXzptRrS7kThNHjckJT+speaE7ATb7mI8E1UACfQla6U9YyUPSabYXPB1NWKXfmOBFyR7yjtEIDd3CofAiDMjvoIwSK+n7W7B5gHihQnR6fnfQRmhRqrE6FWYEEOwBpB336Bv+/DpiVc2pdNRtf4eBpjDBxwAMhWkTIzBYCnTG4KwRK60ldebcNCRbbLj9yFMqq8UGzBRigmEiAB2xz2lqDgPWHzEMo1OgwOtRMFplBU2Oyh5VUcEEAWz/QQlExAoeRy0jfuwXXxrSXbLeoKL6npyA6cKR3Gmd8VCfWwsvAinmAeKbUoO1VzRQVbDZ3+lju7urf31JSxU5NuoV920NWInni5kPcg/YQZ1vXyLC8VK12nlf5T9Fowzr7z+YlO2ul5ZNPjJ0/2zGPnnrS/YNpJ
*/