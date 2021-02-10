
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
ZGgc9I58Ob8jn/G/Qr/CF9COoH3pkgBA7y2o83nRw32cdHAAwtztAezHQ5nBsdst6hYA2JuXSuAWFNUIAjhsq2IxLGoQJWWZlBH0Hri9C3tLqSvyj19m0P3yDbrsNcPYbiYp5SI5ZW4CR0s7teYcW8uVhD15ONkJO4ESOGoMEmaWdwy6yJOSGvjyvQtccDIZVDRwc4aCwpyXINbn96nLG6N8Ie9SKk/CNuau1rF2LDLSUMqU0Kn2SpMUL2zv4Vp4JerafxQhD3LqDLLFRZDBxap0Vwd5JilJ5yLPojObON297WaW0mhxZCKdYHMvP+n6dnOT0mw44ep3Pzb3i9tHAbOioiJkFvsZ6FWkWqf0arOoZJiDg9OZa1Hl0u7Owyn0alGoZGqUzxsr4aDl4KCO7kHrvV0XOXgc++UpD3bYETLQTa/sIky5oNNfgv+06TKG7Gpdu485/tVnyr0iQN1dFcm6fINOS3mLg4Pj6/QUs/SJYhHnTBhMex36WKZ8Sa38PuPuusfikbXSb06P6o530TRhbrMNferW+TY5dto8QgGpPLNcnPiD69+eOflyVa7hoRadVo3t/dYqSzOYn7Mkq5yuGsqmPXT3EYxrpEj9YD2EUbfOcnJYb+iCgJ7RwfBD57y1DKTOhC3H4Yhu
*/