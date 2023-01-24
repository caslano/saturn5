/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONVERT_IMPL_10172012_0120)
#define BOOST_FUSION_CONVERT_IMPL_10172012_0120

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::build_tuple_cons<
                        typename result_of::begin<Sequence>::type
                      , typename result_of::end<Sequence>::type
                    >
                build_tuple_cons;

                typedef typename build_tuple_cons::type type;

                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return build_tuple_cons::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
/HXBH8hfy5qIv2B4OCqPcP6CN3XqUOIvArpi/PXMbOQvgh59O/y0/HVfC+cvwm1eVm/wF4Rw/vqyJ/AB2wabtvkF6kvReC75NuduRMePEKxvLLpeYB87HvxLh9kKxZ+wn8PFLnGJYFWoYhWnG7Egdp1s1Uyt/cphq1+/XCKbINWIgc7q6TdEDExGpLEbi80oOeoeaAxWDvPo2AJw0+4uDuWk48FWwSXqk5+2aeDn/M9+lpKqorHINdt6nJYnBUs2BmPJ5qsxm4dPn42AIeowq/KQXGqwOuBWTGBy02hoE37x1TgKkll000jzKDiWQAlNQHLdeR4UFDCwBLyaJDgtYLz8eIiPF2Trf9fFW5r2W/UJxMW4dEMLowbe2XxxG/Z3w7oTYlYaxhLI0ro/4l3KJp4mpsVKPOuoXMBNVgvUl8+lG66rEoih8xyV9/PIPHUJjxyaYIxWVoBlNo3WM/hQJU73PodXQqZxu/5GIPhrHLl3MwIDBzl5CvJ+7PdltlLDP7oKaxX1ws/m6aTFPJ0UDDamE3CmpdnevLkfDNvVos+GRNCoaTcTMPKYZKfdxCQUL/SJeSbB++srWGRm2tv4kbTkM+7VC1BN1YFM+JUrBPOoB57qZc5MH9iMLwFukafmBauMnZ0PnnQqf2WmE+K15OnBSkCDePOQByHkVH6TeS5XK7Gq34BGSl+SSC4QttPGRvOgTV4Tz4alVDov
*/