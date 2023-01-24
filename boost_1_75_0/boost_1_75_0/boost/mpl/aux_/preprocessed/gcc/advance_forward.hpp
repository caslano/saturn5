
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
GNNxsqCJ/KJldf9uxW3l42rGbHDvl5s3KScER2dmktv66uCF9qI1aPTWPr5XaeVACbydLAVGyvbWsH055+pBIIS3B/ENvkeR74TZ4TrQL6fuGI/WDdmGIqXLnLVPpP4cxnzM45cXRBEwi9ND7EsuwuqmdBDYNvFXwu6yqQ02jQJwKcWtuEOhaLEX9/BS3F1atDhFi3uA4u7uWtzdAhR3d5fgFixIsjqzOzs7u5+e33Dmue5zhupaujf9NzC9D8z66R76DD/82kWfSbxRjB7Dh0QA6IFMKpLN9mXQDo33N4ImbtvHL9CFsqkeEYAmvJS/fGDSDniv4mPUvFl6cf4IuOTNv7jdJDrBvkTMv3grRnQCuNLIv3i3lNiOgZnQjhMV147iIruBdHOzxz++JLuBaMhIDzdQfwinjmvXeImb7zJpU9noWgDW1sP2jF54PedwvhsofylD8OYxPTpFTrwcbY25RPKuVOSL59lVdgPVR4cJJjQOPZ4Mq8KxSK5hNM4C+Y/QbjViiKuEEa0p2c1q0XDx4+Pkza+F3Gbue88h1LVjXD0D0yOvRaAHD6ex160H8xlOFV1Ti2ieNc0znJL5ObG5p/NgeaKFogOaYsq/5XR2v+nUWWm74CvgZAXuecG67sQ8gv64tAtWhgBxcSKOHRoFJtyTNtwOgzkZvXt5skgfhF4uFYa7zSzczrgMHcdvGaVv6q2jXlbbRW7M
*/