
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
8DRcD/8B74b/hFvhD3A7/Ak+KvNjXlMAP4CNYSN0NxG/B8FI2BReCpvB4bA5jIMt4CzYEs6GrWAqbAsXwvPh9TAYroXt4C4YAnfD9vAg7ADfgeHwXRgh9VPdWN6P5L1J8c9se5wH+Z0R/4TBUBgOO8EI2BV2hD1hJxgLO8MhMAqOg9FwMuwKr4LdYDq8CF4HfyN+vRjeAnvADbAn3AJ7wadgb/gsjIGfwT7wS9gXno/N/WAojIV9YX94GRwAp8FLoBkOglfCwXARHAIL4aWwGA6DN8Lh8C44Am6Cl8HtcBR8BcbBt+BoWA3HwONwLGyM7+LheXAcjITj4UVwAhwKJ8JRcDK8HE6BuXAqXAwvh8UwAS6DZngznA7XwhnwPpgIH4JJ8Ek4Ez4Lk+FeOBu+CufAQ3Au/BDOg8fhVbAWpsAfYSpsyu9RGjwPzoeRMB12hllwFFwA58JsmApzYAFcCJfDRXADzIVbYB4shwVwB7TAl+Bi+B4shIehDX4Ei+BX8Gr4DSyG/4RLoPIhcCk8H14LL4IlcDi8Dk6D10MzLJX7AHUv7628z8p94GLlfRMq2wvSzithKPyTtPOXpJ2/DGPhK3AQ3AcnwP0wAb4K8+Br8EZ4QNrzG3ArfBNWwLfgflgFX4MH4TH4NvwKHhJ734XKPeo9GAHfh53hB7AH/BD2gkfgIHgUxsOPYCr8GM6Hn8DFsBpa4afwBvgZXAs/hw/BY3AHPA6fgl/AZ+GXsBJ+BQ/Ar6Xd/xm65hEec8eZqEHU8wNfVp2XKue1q+e8Uh/zK/fxvErVeake53VRnVetss/7efIuA1rWfR7vIr7lF3vcN/vM9Zx3spHMw0Tqmm+ZnMe8Oeg517KE4+XI3rwgn+dd/ppzLsuQM7sbPueyofMtGzLXUuZZ1jnH8hB+Po2E5jM/EUlCLEgZshM5igQVMN8SSUZKkR3IIeRMQWC8VmALbIEtsAW2/48tCMn/xfr/rfznXEQ03VZsHwJw9mMA8rDWuVaL8j7uZBu4E64j7/IqR39aYsqMcdNTbAUp/GvmuBmTxs9OGZuUbPKpb23A2/q+tbX2vsjFrm+5ZexTMldfWZn0VYZIX1gMVloKcnPSl7jXBrFxTk6eEvae86QPri/n5WWwlsAC1TrcHMsvYN0Ik7svrZ9ynnWBdq0/+a4QijRBQpD16Kh6W3zgLnmiYz0veoh8mNMgZXaVMUTKXIFWyUJjx16xI1zs6IBsIG2N3o5k+zLwLFHgy9wKDzs039GzPGwYKuMJysWGLcidpAt+x8CGdGVpkCKLP2ufiA2aMQzbRGeM6OwlOqsNdNbfJ1i/voggifeNtEEmiL6oQwb6cvJzbCbf11wx0rdSEo4XfWOQuziv1EgfXU++rEelvl7Qp6nD1k317fl3ij+N9NGe/V0PSdOOpL98PlTbsK6pfv0j2jIfEYxtOJdteYzYENNMv/7q3Uo9e7NBbioNac/OazuKSsvOLFaW1tCsWc/aGhr/VDTT19Fm8jJ7s83KMnJ+rKPs6Z8f+Dhqheq1NAYajAn4HGdZ3nX22yUPir3UubSF7/11Fe2061pYQ/TrWtTCqsbe+5nG2+dQjfi+x8VJfy+5eceEOREnz1t9vf/9Z5/a83np7eQ/b8/tdOLn9eXxH3Z78hTfYtooxys+nx39u9SHWt7U6kCjsL8/+Azf9lopxx+evTT5ZLO19y/b1r76wAO37f3PWx/iIbudKx68+93j+2Jjl+9LLM5Z88BJ//sL/e2H89Zf+IndHlvHVX9bPv33c27qNWtL8MAWfMAz7pc9d+tM9OumHL/ZFPyudd6Bg2fmrD3x25pP4/3vF8yy53P7oC6D8j63PmM=
*/