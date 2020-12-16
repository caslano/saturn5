
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
n7x+yrPL31r4WtwbN5z4if8+BPt17EPr+4/cTc+2nvlIdHTh78a71YwrbAf3hp1hW9gDtoNxsD1Mhh3gbLgPPBJ2hOmwE5wPO8N82AUWwxh4FuyqcZLd4WoYC2+BPeCjsCd8AfaCr8Le8G3YF34A4+D38hFWyUf4KxwAm5OGeBgBB8JEmAAHw0FwBkyCc+FgmAmHwNRGgfmatFaWfE7WNbLGIlbfk91aWH7XwdLaV4H5orTOVa21rKzrWNX2UX0sP5V5zSrrWlX2PqvbLH4ru3Wp7H1YWoNK60/592dZ15nasW9rNWK3ntQmGDfdn68rsLWjzOtFyQfGGlFwRv3WhvK/LpTvelDB+8iCWffJ7DebhVSv8bQRsVvbyYVs5+/o2bX9aYmc2wznwJo1m6zrNW1xfGZOcIITnOCE/0FojGTv2vZ/YY5n9v9Ot/37mdr+ERoHv1Jt/3PhXr3c4w+8bf9pxKuWv6ftPwdag/+2f8vd6277a7wrw+HM4wFD0/ZfrWsKc2nBB+EPKINNyZvj4S9hjj/A8QeExh/wguEPKO1zYtI5LTZdPSmibMYJy8ZP/nv9AUP5v1LV8ZXyB8Tyd1wd/oBoGAc7wCS4DzwYdoTzfPwAObALdMEYuBh2hctgN3gh7A6vgD3g7bAnvAf2gs/C3vANuC/cAvvAj+QH+F5+gF98/ACRcCBsDRNgNzgIxsJEOBEmwcnyB+TBIdAFh8LFcD94ItwfroDD4blwhOM3cPwGjt8gpH6Difc4fgMnOMEJTnDCvyc0RPs/a25uSNr/A0zt/4n6xk9B9kLGIpPj+Az7o6W3/U+8Rvs/mDmtj9Yxt7hIc4t950bnIO72c0K1ffJPjJF/IgmmYl+l1b6DqufikQ5L8O+bkJ0+cxMTWlnXfYuE35NfWUfVzPvEdo5zjeNopS3nmDBDR8fqtdWK53GH51wMLELydNLsb8CdYRyv90n/Nrg8hP4Dez+Bv3b5rvcH/Fva/fZ+F//+AHv/SvB+gj8MP8HWlrOOOz133bVRD3R8b8B519/69/oJeLb0XuBv87o+NvvExsIxsA8cC5PhODgWjveuz6TnWM+37/pMe8vv0B52gh3gvnAfOAZ2hAfDzvBQ2AWmwxhYBLvCJbA7XANj4Z2wJ3wO9oIvwX01d60P7IIN/WBf2B/GwwEwAcbDJDgQxv1H2v0N1d73aeeHvI3vp33fIG37hmzXh6pN31Dt+QW050912vROcIITnOCE/2hogPY/F4em/39gAO3/ku3e9vUU4v3b2v/pav9P0dpEE+BU7Kuw2udt/0fuyDbGI7SivaHxCEH5AD7y9QEgJh8A/2/2AWisQgFnTOnTunvGcaVpDSBjXXgds2KRN95ttj4B/21A+7Zq8G1z+zasP19E8G1zex9C8G3zUI0pCLZtbu9bCN4nY+9D8O+rGTDVfT5t/G4/jhh38LiLL3/ukC1trv9t17f9/fmCvGv9bvfvE0iWT2AsjIXjYB84HibDA+FYmCKfwGdIhfRNkU+gA39vkb5o6WsPo2AH2A12hL1hJ5gIO8PJsAucAbvBw2F3mAV7wGNgT7gC9oKlsA+8BvaF62EcfBj211yEAfB1mAAr4SDYXGMIIuAQ2BsOhX3gMDgQDocpcAScAEc6PgTHh+D4EALyIVTiP4hY6/gQnOAEJzjBCf+80ADt/9ycee7m/87P/R9kav+PUvv/ELX/JyHT4/jnq5aWtW/nFjIaP4A96LR/mu9Yfe1fVbtd3UhtYvMaz2Xeccf8P+I+2bcd+nxsmje3kFXjM+tc47napih0yCZLfPHyMQxWfImKr9Q3vpyiwkD2DLOJz1jn90G3Pv6eEWf1cWxT/Kc=
*/