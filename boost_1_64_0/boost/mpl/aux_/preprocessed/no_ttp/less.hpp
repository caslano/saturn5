
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
j/E5/ATfxk/xGP4dj+NJlOdGy28SzmHZD/Vzo0fJfkShH47B1niNHNdoHITjcCiOx+E4QfYjBq/BSWjFKXI8p+I8nIZLMBaX4XWq55ofknzNkXypn2ueKPlKknxZJF/Jkq8UyVeq5OsGyddMyVea5CtT8jULszEL11YrX79E6CM17WM508bQ7k4oMf51LGExbeK4ca9+v8WqMvouumAE4QJ/x19Tvn6MIv42R5N/Qq70aWzBnWuqmfYT8nm9PbpkH8cp6eeoPs41fjZonKvPI2qc536P7Zq+j0K8SPDlR1IRaWr7QkwUstIfEi59IrFoIzj6Rgr26o+33c7/DhFi+fsC6vWXBLHtpcrfhH2E0wTfmOL+k3D+tw+7xJTejxIVwzYxHpcSivtUMMbVr7IzhvwSHP0rp2NcfSw20iliHwJ4P2Zi6f0t5mtdfS6R6Oh3WYs7CUcJ6j4Y30nej+ddpfyfcIhQRPDUNxPIexdwFfkPn0x8wkJCHmGPpr/m6GRXn80l/vafUrLvJpT3jmMsziesl36cnXiIcHEor9N4Rnk65xohghBPmE/YQthNOJ5u9PEYi7EYi7EYi7EYi7EYi7EYy19juSz9/5msWwn3/yvP93+eBkOz/fn/kgd7b40yvqD4+f7bVPcHdJD++dqEaoRahH3ED3zNOe7+GjYyYUJU2ffe28fzSx8STRH2ZRPWwQ34EunuKbBvlwy5zzsQUMp269LnvfwFe1sSpZhpf33+RftrS1bWn5mXoLiv7FVe52a5+tJkrgBnH2KB2dW3ViTrK/MGONI55eyDSsjOlH6p0473Zks/lcRL1/S1bZcx+y9iHdyFjyv3Z+x2lZN2fsYOZZTVXa86yqay52ukPFzl47ZfOSHEl/K5l/9nyfZOafomT/A6rQ3lkJlh0/bbpsrr07JNm4xTKJRtZjvvN5A0exT3zVcp3l/TGyHu56BZOrqbyLndmHBQ2aHXnGU7g3757JQKzCuhpNNN0sn1kE7hHmc6JGOrUBqO86RA+tUPVGU9fAPfUs4T576UnCfDrPkM054nO/c6zpPKmzdD+mlL1MUAnbp4Ufdccp07Rdp+bfe6J+ejvGcqPhdqF++Tab+cCwOl/JKukH4OOUYtZZ4R026d8ovL4HksqcmWbO+PWUXLzbhP5n/vPplpGfb9KjiTN918qoPfzx+e/HbNH3dcnv7hYJN8h8t3+37NPCFdZZ6QblgLu+M5zK8i39Hy3a3E68nfD6OyhKjurzFjb2yGfbA1hmFH7IvB2B/DMBwjcABG4UAchxGYhoMxG4dgLg7HhTgCb8WRuBIj8S4chXl4Ne7A0bgLx+ArOBb34TX4No7DMzhe9jMGG7BPUzEYp2EkxuIYjMMcjMcbMQHvwkTchNNxJybhMbTghzgDTZRbMlbFdGyPGdgFrdgTs7Ev2jAaczAWZ+N0zMVMnIvz8Ea8DefhOpyPG3CB7E9hFfnNIL8llOPWVzX+8jM5bqfQjF/Jcfsae+NpHIvf4LVYhCn4D1yC3+NmPIsP4Xl8AS/gYfwRP8Kf8TO8iN/gL/gD/oq/4G94FXm6hH74B3ZCMr4wAatiClbDdKyBD2NNfAJrYT7WxfexHh7FBngS/fE0NkHlODTFGtgcO2AL7IqtMBpb40QMwnhsi0uxPa7ADrgGO+Nm7IIfYzc8id3xMwxGP8o9BP2xN/bFPtgfw9GCg3AmRuASHIxrcAhuxqH4KA7DZ3E47sIRKOM+5PcL+yj1Wj3u4xrWq4bR2ADHYWMc74rP7xLP8UdJ/Ksl/miJH4WOz4dgSf+AzufDMo5nXVyOjXAFBuFK7Iy34whcjdfjGrTgnZiO6zAb12MubsCb8G4=
*/