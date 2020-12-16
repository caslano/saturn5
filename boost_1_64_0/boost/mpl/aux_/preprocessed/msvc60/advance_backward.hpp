
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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
DXwPtuAF7H04Au6HRfADeC/8ENbCWvg1/Bh+Cw9AyuTw/WYeaNj3a7W38FakBtE+wj6+XPlwLf23/n23hEPCRlvvE6w9gv3uDbwa2YiYfa+xhj/Vy/daciC8Qf9rLCI/K/5Vs2/V16/q60e18qEG7jd1+UxXoWclsg3ZgxxGWn3CPr5IMpKNlH8S8pWGjtAROkJH6AgdoSN0hI7QETpCx3/K8a/w/w8aMvS4+P8HGHNsn3P4/0nS6f9fb+H/L9Y3rRyX//9PLr/2oEEu/z/fYn8x/+5q4p5u8u8O5u/mAfr/hxO20qTvz/X/Dz2G//9h5fsgMpJw1aZ8g/X/Dw3Q/z/KKN+f6/P5Kf7/oT/T/+/dPqrd+tCs/g3tYycNoIdF+8jW55Ob0fskeAM02kfqNpO+zvYRwNoQx2ofms8cgP8/k3NjH5W6x9HB5COON+yd5+ULLvD18e8Kt257NdWmMh2HtjfZwsc/mnBVT5ny+Qk+/qEB+vjj5OO/TT7+m+Eoo5zm/NX2g9krzV/bt/nx8R/1qFPVscnnf6QBn7/Zjx+l+dpTWYA6Bo6FY9Bn/3ZHmZx3ej9+/M3mZ04A/WloEH78bcQdaPLjV6qMrv64RufzdV6h8wU6f1TnadpzbaPOsbP6q/z+stlWC5utVZx5Ol+p82KluVnnc/Tv63Seoz3b0jlP6k4exbacguzcLFd9bVG4LJ2vcqU7wNkne9DOapvh12vNN/cd9X2ynHCrO7jHHrjDRmDclzH67Nfrw1aZ2gRh3WMV4ghQ2ZM4jfb1aX375CHp93/ZaWCz1865+b5ffuzB8RpjEOyYAX++/kKHHfI2b6p+YPPUUQsbrZ53cevS3S4fvd4xYDHS3OwzNs0bHSof3zDYAw6HA+AImAxHwjR4BpwDR8EceCZ0zwdUPu2Uj9lnN10+uzQYCWeY5mdWK97DimeenxmleO0ULxqeAtvDYTAGToAd4CzYEebBTvBiGAsrYGe4HnaBW2BX+CCMq9dfz37SstA/RXpMkb1SoezLM9q/fRMVPln2HSf7jpd9z5Z9J8i+E2Xfc2TfScrn0TA9W/XMlW3CtiifMzWvczSMhmNgV5gEE+BYOBAmw2FwHJwKx8N0eDZcCCfClXASvAaeC7+HKTCfzKfDJTANroIz4PVwJqyEv4LXot9seAO0QdUzz1H/9dxd9u2hej5F9Xyq6rmn6jlB9dxL9dxb9dxH9dxX9dxP9dxf9Xyau571nIXtlbe5nodrL6MRsB0cCYnHdT0f9dzkIA756e9v5Vv+TvoTkHm8QL7XJnAQbA7PhC3gZHginA1bQcczANrhyfBCGAEvhW3hGhgJq2AUfBq2gy/BaPgmbA/fhzHwU9gVfmPa86gbbIvO8bAb7A4d81/hQJgAh8FecBLsDdNgH3jBP9m7F7goijiA4yRYmqiIiIioKJaoqKCY+AhFUVERVDAxUUDuQOQZoOIjH6nZg8zKytLM0syMitJKywwFH6kZJhWWGaWVKRUVFRVZv737cywHJChR1s7nM37Zde9uZ3Zvb/8zs7vohlHYC+PQHWehBy7E3rI/eOLD2Ffqb4el/BbLbzT1wLaX+2xJH74DlmJ7qT9XsMKReLXsp9dgjNn1z3dJPa7FJpgh9fmGjIU5KvV4AVsg72moxx5oh+exFdo1MNbju9gaS9ABX2Yd2+ApdERlbEVb3IdOuLQhxxfMwPY482pjvT+Azjj+GmO9z8NO6NXIWO8R2Bk7NGZ/Rz+8Hq++1rg9eqErfo1d0b6JcXvkYXf8Hd3wdWv2d+mz7olPNjVun8Pojnc2M26fl7A3JjU3bp+52BcXohfmY3/8GgfgszYc77FhC4736Ig=
*/