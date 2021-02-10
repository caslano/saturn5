/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1340)
#define FUSION_CONVERT_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/convert_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_map
        {
            typedef typename
                detail::as_map<
                    result_of::size<Sequence>::value
                  , is_base_of<
                        associative_tag
                      , typename traits::category_of<Sequence>::type>::value
                >
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence>::type
    as_map(Sequence& seq)
    {
        typedef typename result_of::as_map<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence const>::type
    as_map(Sequence const& seq)
    {
        typedef typename result_of::as_map<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
GKzm74PLzSdRmYbJM3c8cGd1s1/Hc3ezf7eZxnZ+EDJjYtmMGAbADFOPYx2HBSpEK9n0jbdQ7fySijZZmGaRlmha7gAQZ+sv4ikaG4MIb9aVsZfeYh1MPER4igL7xnKccOD6T+8PDnu1Pm6yK3Ar9V1X5VdzeyWOYd2YsmJWK/gPVaSerGkTCKiKG1qWeIj5LlmWC7t+ABvsy8zVohCgjoNMS9P+Rvudo8b5y0sDlRozIJo19DMf52jQm5L8XnyIh3kkwazebpe/xl3CtYvvcfgbscuiBi+/MvSS7bNkKr0Vp5Kmk4rFLdtg8bNUxZTVCJNHDHhbHDOfdG9YOS8nd7+D6gOvqS88gNIqnH2d47+KdMtqVRlNyzXBAgYUowGFNAdKdpUM6HcWskCr0fbnsUAiPZcHpUyYejPRNvoqIbi42rzsb64kCCeHn/5VYpAStVwI0qZ/VAQ2kRWriAHy4U8XgjkcKA8TJXGWnAisqAZ2V5p9pczgnz37y+NGMgdNFujDuhO5u925XEW9fau+MMypVQX85rRKVKppecE5RBYnap1twgb61DcXnoDnywJ+cwIWFRdcQVgnwlZAm8IX5dy4PSMTUJN/xXEPQgXQlxmP0uFaogqHyDKWl04puCwvoSU18/gDJUTiKRgY
*/