/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_10022005_1616)
#define FUSION_AT_10022005_1616

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { 
namespace fusion
{
    struct fusion_sequence_tag;
}

namespace mpl
{
    template <typename Tag>
    struct at_impl;

    template <>
    struct at_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename N>
        struct apply : fusion::result_of::value_at<Sequence, N> {};
    };
}}

#endif


/* at.hpp
nnzj6/y0WFDIGg5TZrfvenMCal9QLnA1rXWQNQAyvkFDy/ofWrd9FuqniYJXmZQa6Aelhn3xDrI8rtjXQi01ZNovuM3G2FJkKIBBtxcX2j3gNuz92H+3Wg0msWpoRUOgN+kBlujR7tShDh0AvgzEDpAX01EgYvlTWtg+/zdowfER55hDSeOAYwWHGI5MlMMXbCnaBGRvUcf4XdKgRRFrAS8DSOe8QXe+S2v5ggmB/JSVwrB5xL136xHtA734XeriUPq8c2wGkmu+SCT1YPeeFcjxM/AnTVMo8Finy+jHn84ds5aaX5yd3vOzSO8K1auChqBKc3VdSf79Ymo9w0wdCz0Aw40GAIQxdrsNP0EkvNlcbKm9O8CtCvQoAeENirtPOrSCZUBoquNd0l2uMFXWbZKMdpbgHdbZCelQ9Yd34f9V4u4PVg44TIjv28garhuNdFW0c4HRTfboZh+VypOlHsTDAJfqsdfZcqUyXVAZmKgCarFl6tCyB5dPFfk6xTwwEzKseP/J4PMOAE73aZU0iUK9T92uDfBTjTvJ93xHqKTVIwrZQugiXBIzaA==
*/