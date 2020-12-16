
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
OAol/L8K2bwMndAqpkL9lra4Cie2GGMrdK8h70gGUoTsRRqR0JgLLTXGuAtJd4bGXoD4WM3+iezbB48i+lgMJ7Q0W80xGeK3YhdOhKGxGXK2muMz1Gw1x2g4upVjYW0Ddvj/WaSK3/F3tcZtmAgDsRtq7uIYfA3GcLirLY7D4bvaYjmc4v/dattiOsQ/wDpEyKhaY3yHktr2Yzw0N2CD4w7VQvadgoF4D93u1sV8OGiM+zBd+xv/z4Vj2O+GOfjQzL4dd6tjQRy6uy0eRMbB8DEhHJ/kGMSNzlyojxFRze8WfjdAfayIOo49+kl+r6ScYSO/VbEjjj0QYyt+xJh7rGNInEHHMZh9T/uxJHbf0xZPooH/7+e4UzB2W2tsiVFQFV8iLyvGkbUtsjgTPo4/zf93wOn8PgRzYTM8gwRiT6TcS/nADKiKQVHDfjfcDc/mciw8gWgxKbptx+ddMYbYFCnb0cG+Bv4/d3tbjIoS/k+cCmK5kI/t6GZfPdTHrGjeboxbkXQfZfMs5w5ZjdQiB5BmpPth9iOrkW3IIeQkEv8cMS4QN7IbOYycQlKeZz9SguxAGpGTSPwL7EfcyB7kKHIGGXWE+obUIPXIa0ivF7GJ5CJuZBdyCDmBdP8BMTSQXKQa2Y80IWeR4T8ktgZShexBjiCnkZSjrDOG5CFVSB3ScDQaSyO6/W9vH9X8/+JNXTP//1otPniyNv9/fWl5QanPG5hvzt9uTqBv1P+3pSuXOGetzMl0Zs1bNS9rhcQAGE4uAzGP6dNl43gu8d6wHnrR3XQ8UfuuHQziWlRaXNzOHBf5nn1+3PWvkZahr671Lo9H9437/mAMABnXLPsYm0Ou2sbIXsM+rxY8QL7Jx8NrU1BY1HpMkmH8unFeV6noaeG3FluVuL2GeR8SX5b+wJi4FvYnkf9xcO0v8VmOO8lxb3EcIZa1b/HBY3M5tgi+qDv2VCC29IZyv93Twd+tE/dJb5j/1izl/U1EYs85fNqLz6/ayntFzrLl85xzcnIDw7RtjCMIjHX4IIn8+ar8Y4Z3+nWyDTDG782W5vxy8WGs+JD3usKHdse4Ku0b8nxYEce/Uqu/Snv+yd6FLo+vQzZni83pijj+G7BZH8ZmSX5peSRjW8SuYTx+g8LuRuw2hrFb6fG4GHtOteyY7UVie/L56nJuat+2FmY+opjaqjKvV9ivwn6ztX3/kJfOlvkYxXz+TdhtCWtXyzaaOml7n8L2zan882sr2xKsxOnr8HUVsD38QnUdj7W2XVnun0TiKupomQfO9W6xPURsDxbbaVa2x3fu+grYjVfM5b8Fu9lWdrWmpBPXVsDuNoXdzdjNs7Zb4ipch+H25/yFO8fdFfH5b8Wuux27/gu6qGN5DtiuUdj+BLarw9uWCt4x24G2rFtPte268LZ1cfo7Zj9wvjdb2N9jZb8T92p9mZ/pqW7D663tShNOPbcxxyzcfbrsIrPtDzmu0dI2z3cVng7ZDMYFsrDZFN5m69TVDpZ14By7e/FPyJjaau1+ZW27yslqMPkdsKsYPxys6y29lGWAI9Z+uLUpzT651Drgj74cSnqb7d+u3Ucs7SNay9ZBu8FYGQq7d2A3LZxdeVTp6H0kGAOoj9n2FmynW9mWACL+y8zG3Ntwtl9T2K7Bdka7tj1l3k7mO/didV3LtrTNDIa2x4YO2Q7GALpY3abmWdr2j6i2FdctnN3MWLPdO7Hrbseus7CgQ3aD71kyB74n7wT+7+7wLuxWK+2Wlpf62o910If366oTWnoHDaHJfvC9+h/89voqPC7de/UN+FOFUYdu7mk9++TBTN6R9fFRYuKySJjFMVdr45l+i13d+3Z+PPo=
*/