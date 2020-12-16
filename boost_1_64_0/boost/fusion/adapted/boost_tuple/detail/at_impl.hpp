/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09262006_1920)
#define BOOST_FUSION_AT_IMPL_09262006_1920

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename
                    tuples::element<N::value, Sequence>::type 
                element;
    
                typedef typename 
                    mpl::if_<
                        is_const<Sequence>
                      , typename tuples::access_traits<element>::const_type
                      , typename tuples::access_traits<element>::non_const_type
                    >::type 
                type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return tuples::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
tdEudsaT0Pohv6F4AF5Qb5cCPARv2MRvuq4DtxETT8HQR3bpo+Pwxo/5TVSHn5FqnQN3JviN1po32+U0qdH1P7HLdlKJyxbuEmnR+uFbDfRBn4Uln/Lta82w41a71Ol7wfGkXveCd3/Gbx0ehbc32qVJHX5JWnnHFPRss0s77oODSZnWAMeSEjwMF5MKPA73kFI8DTt/zvp67nAAqcMDcCJpwiNwOanHE3AXqdZ9oe0L3l33hTeTGjwEnyRl+ixcSSr1WfgzqcCliT6QU3oucMkOzu5j1vyaGnbyLnruML2LO8y4bw/928vdxqMtvNM+7jOeht2+5y7p/YFjSYLxMHyTtOHxlF1+Jync2G+XZ8huPAZvaeX+4XKQ7+sQ9zbBs4e5bz9xn/HIz3Z5+ijfj875nRqPcR8YD8Jmko3Lce7gH9wrPAH/Jknd60/6R9bjcoLf1ZO8D+7/iztGCpifhnv/5j7jvlN2eZ6M0fX/scvQDg6pxAMdHZJxhkMq1GGULMPjUDIcEtdn4bRODinFU/DyMx1SpOvAnM4OKcPD8D6LQ0p0DpxrdUih1gyX2hxSrOOwg90hubgBh5I8XQdOJsuoPwKXkziegLtIFZ6CHRwOKccNeAWJ4UH4FIniUfgOCeBxuIP49Vloy3JIEPfBm8lwPARfJEPwGFxHRuq+cD+ZiqdhZ6dDwrovHEBCeABOJBGtGS4n4/RZuNKghs08C792sRduuB1yF4niYejxOMSHB2At6YsnYW8v6+AR2HgWNeC+s6mhC3vpfBg9h3pwfzeHJMkQXLIdcoT4dbw759ODOvEEfK+nQzK1HljZyyGGzu/tEGsfh3TBo7CFlOsc6LuYXuHxHIdc2I+e4EG4ltRpnfCBS+i/OrzJzxnhYXjbAIc06ZpQBjqkAQ/Bz0g9noIdch3SpncADiVpPAgnkxN4BC4novXD/WQ342nY9TKHpHA/HE2SeBjOJevxGPyCNOIpaBnkkATug1eTZq0HxkmL1g8vGOyQYzoOF5N2fXeYP8QhrXgYWoc65BTuh5+TjE9Y83KHnHEF3w4egB+RGjwFA3l8L3gIvkPK8AT86krOQJ+9ivMk1XgMdgjw7eh8uJrU4km4+Gr6qQ5d19BP3A9Hk0I8DBeTYjwOD5JmXK51SC+Sr/PhaFKg8+Fikqfz4V4yBk/DrvncG50PR5McnQ/nkj5aJ1xHsvVd4H5i12dht+v4rvVZOIqY+ix8h9TpfLj2eu4ALjdw1sS+hXMf7pD5xMTj8AeSjafhphvZVx0uLKQePHC3Q54hAVxGOmQEadG9YPAezg5PwmtH890xJwT9YzhHrROe9x/m6TrwKMnAffc6xHkf58ucIIw/zH3QdcbzLUzg/ut8+DRJ4FGYNZH7hvthiMTxMDxJlumaxXzHpAqPwP0khsskxkgET8Auj/A96zpwIynXOY/yHZGpuibcQbo0UD98JMz3i0fhZpJkThJ2mMw3ghuw82N878wJwr3khK45xSFbiTAuJfx2kZS+C/ybpLXmx6mdtOmaMPAE3xEeglESxmNwPwnh8qRDxpNxug5cS3ysn4BfTqVXWvNTDhn8NL3SmuEhEsflGYcMK6UXOg7nTKM/eBLOepY6dB04IkIN6tA1nd9J3A9HkCQegktmcHa4PM83SDI+ZV9YVcY76prw/Jn0Bw/AcbO4e8yRcu7+i9w9PAEfe4l3Z04KdqjgjHADXkCm6r5wBAnrvnA6iWr98ENSrnvBkySkz87h7wsyUveFd5OgPgunk4A+Cz8k4/RZeJIM12df5lni12fheDIEj8AkydZ3hFe+wjeCh2Cc5OBJWBzl9wePw45zeU/cB79+lW8cD8xzyP0=
*/