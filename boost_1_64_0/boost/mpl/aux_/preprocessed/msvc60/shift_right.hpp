
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_right_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_right_impl<
              typename shift_right_tag<N1>::type
            , typename shift_right_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
opZoWUiOQCKTKCM2EDVEHeFXxHJEMlFMVBI7iTrCfx4/I8YQmUQxsYrYSOwi9hEtL2AeIokoIdYS24nPCb/5PpbexBhiFlFOVBHvEYeIoAXkICQyiXJiLVG9wHyGy5zMyZzMyZzMyZzMyZzMyZzMyZz+udMxeP4/PTs3lftW6h//P6Ln/5Xnsnu2tdife23ifL/OAeV+nYZ7ZUaOrX9KxfP7FfXueef2FNv9D0FNjK6DG92fYHT92uj6u9H9FZ7fJ6B//4PRdXOj+xOMr8u/V399//sHQz+Ov7D5952bRD7mPSqEzmwYt1C2hWwj3ybacQs7Sr6sTtgZ/TGZeZzPrdrHrCkjchzzJhnkSmrvcD5UciMZ50NyyIOUQqwmOEfJuUmjXEdyHtHh/GFdjOQvcjNnkf3cn+45Pzmnp81HVOkiD1GknJOznovbZZ6fMidzMidzMidzMidzMidz+t9Pf/n3/4ERMDAiK//I8/93U/LZ8f1+XTTfI+vztw2MSC0ozE+dUTQno7CgPlfcj/x8/lCHn+dnTS/InVPAKtafQ+D7qe2Zn2Q5hzBKziHEEiM68N214RzC6MTE1Jzc6Zmp9tJoUkHj5xLcyTmuf67A82cH9M8hHL176T095+AXpbyfeuW8tZk1cx6P7PrSkurXX4syfEbA+BmN+nL2bb2qdNSnP4XvLrm424YfKm83eubC8JkOyTku21S2dbRDzvEpci5iKnbDs/EkPAeH47kYi6nYi/pTSrmvhDC6F6ySnzXcD3bs8z5vL/U5rNzPn7OcQ/5nzn8c/bzP7uR8/rfnem652DzfYk7mZE7mZE7mZE7mZE7/vOmYfP/ni3NRYc4Rf/9XvrufqLr+Xy7f3Z+QnApbCN9QnmGLq//uTm6O+EmTxjH2QEZE0Zxsd3JmcP0flaQJLGTLqVBI8Dony5o7SXJ3UKgtp0Khd/1r5rHnughqeK9wdp59rLdCGeNOmeeAvC5SlnLI5xcn4/TdK+u2nmjButWM1qwbxUfQNPfX7RNpt2rdpN32NuXRbgq1tfuQQ7tlPaRPpN0O4/mdL+PUzUSl3VWnObW7qHBGdH27/Y5Cu+saaXdrVX+f58Z6pEgSjrZNWQ9sjcq+VTJGux6sg7Jz1a9HkBvr8VftW5/Le/lZhZaOsq7BLEsDB0VkzOLRSId9UF7vc+iTOvU+KflB/NimyZQ9j9f3j7XnB9nDvEX8e5aMZVgrr3Ny6/tSk6c0zEdybMp+0QyPpz+Dzqzvz/TZeamFufXd6f6+rGxvTsg19KXsI5QwkFNTmnEKlVXpKP2m7RPJf0I5vWnfAl6X1rdH+kq7Ppr9Y52P871HJ4TSpnGa3G0c+bj9ycN7j9Lz7DmCWlEmx09N3b2aOdfdhvkqneqe4VEO1jvY2WY0UnelTt3tmK9mnDVH0tFZ75Y6dQc2d667A/NZxlvrPjrrLXX/Jflu9M9RGuXB8fxc6tHKj+NpHhz9c9Oe58fx9FzzPy0PzkX126vfaU0ntRnT7KpufVK2FPQ5/a5jk+9mnUU+++AT8jx1W1wjO31beZ66I7bDThiM/hiGnXEMdsFxGIDZGIj52BWXYDcswyC8CnvgGgzG27An3o29sApDsBpDcQueaHu+XT7P4L06z7f3lfb2xw44AAMxHE/ECByGgzAOI3E8DpZ2D8HZGIVLMVraORTvxJNxPQ6T9uy2yOcU+fxCe+gbcsRKezZIex6Q9jwo7dmIEbhJ6t+Cs3ArLsDHcBE+jpfjE7gCn8L78Wnpnx34Fj6DH+BzeACfx/a05wUMwV3YH1/EKHwJh+IreA6+ipn4Os7EN2T9EppYP780fK7pTSj9GCefo8fI+p2J7XE=
*/