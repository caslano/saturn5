
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
D8fBxTAZLofj4S1wAtwAJ8KHYAp8CU6CH8LJ8FM4Bf4Kp0ILeXgubAZTYQuYBrvAdHgGzIB9YCYcBafDKTAXFsOZsn6SBy+F+bACFsA74Gx4D7TC12ER3AOL4bdwDgxW/LVgczgXxsB5sBucD4fBBXAUXAhz4AUwH14IF8CL4Ep4MVwHF8FyuARuhUvhbngJfBcugzVwOTwAV8Cm9AMrYVdYBnvCK+FguAomwqvgBLgGTodrYR5cB8+D18JSeB1cCdfDa+D18F54A3wD3gw/h7fAIPqNCtgA3gpbwttgJ3g77AU3wGx4B5wJ74SL4V3wWrgRPiDrLC/Ae+FOWAl3wfvgR3Az/ApugfVoRw/D1vAR2BY+BjvCJ2BfuA3Gwydd6xwyHpFxSojHOkeEtMM28ETYFvaBzm8MRsFzYHuYBaOhFXaARbCj+/1txhXev702TnXdNrmuRS3XVddy3fq/eD7+vz4XfzTm4Y/0HPxfMf/+b5h7/6vn3c0597rPuZcOZZ4d2YZUI8HDeA97mDnHbh7mYR7mYR7mYR7mYR7mYR7m8V88jsb6f2Zh3hFZ/z9Ltf6/Xtb/n2Aqoil8FG6PZI5ulHsNc/DYkZr1/0g/1i893/dfpXk/Xb/OWsO5EM4VqtaLZd3Vtcac8Cd7dwIfRXXAcTxAkBsChICc4RKRKxwqR8CA3AYIECAqmIQcJBCSJdlAEIoR0QKiolXRgkorKKJovMFSxRsVbbTUoiKmVsUDbUQUVLD9ze5/d2eys2HDobbd+fj8MpuZd82xO++9mXHd4z9ffZ6B+th1z7TuYXZUGHMQq3fyXa4+2/mEVyhQzERLeU9Jn+1NjYPvs/Xcs/hAdf8+26M0ypZOtPRXThoxdcJFI4YbPbbB91X+0Mr/HQkxNfz7R8Opj3Lb9Ny9o1XpI/6hVah/NNQ/WrX+0dGu/tEbP1p+8IYBt2cOffWrm1JuKfzpV9o/Wk3nSp1DIwgdwzzvVEX1r/TAttgTe2AvHIAxOB374HzsiyuxH65Tf+dWPA/fUr/nx9gff8QBGElaA/EcHIQDMRan4BDMxAtwAQ7F23E4bsKRuBVH4Ws4BvfiRViDssRjFI7DLjge43ACTsQEnI0TcRFOwjswEf+IU/AJnIZ/wou9/VI65+LlNv1Skaq3FuqXOhNjsSXGYWtMxDY4C9tiAbZTPUYrHeTcGbhfap9puXIt1yzAcreF+pv+7/qbTtc9H6E+p1Cf08n0OdWPDw/rTognOOJDfU2hKTT9ktPpf/4fr8LM5BLe1QJwcs//axtWv3Eyv8uPjDau+YzIXTEn5+TlzSl0hLnaCEab2gi6V/N/R2C8MU5/lO+aOX7ChIumJBjxHP993eb3akbreneq3sU9CccTd5wvbvKVmp6clpHvagFxJ+FKIzKIa/KppJLmLLK8N54YbN+5ax6/n0AesnMzvW0JXKsz79fWoOcgWca7e9/TfQdpZ+v92+Y2iNa65n5SZX5UZS4fbVPmoMtbs/HysZ57HE6u/EcqlPdAhbaLcnNbi8pvfhbZIWt9WJ+Lpa+q51X2Z1T26IusZfdt6uDK/kL8L1f2m45T9j4VxuN3Vdk7YwLHYckIV9l1gCenOfNzgm5nUxkt7Stpc9NVPr1nOn+Ww/Q+aXR9lgPe90n/GKkymvbnvDl6l7za0lR3rmd8fezKM+NlI6zvrM2q6d9+lcj2TRlnaU8aM37khCq9s3ZSO/+2q0M29xpMZblim7R0m0GV2q44B1juM1jf2HyfgbXdzmlzn0ES66/3z0uV319L2SttQ1tfPXBbk33bWuA2KPs2tMBtI/ZtL6euTcm+be3UtZXZtxFVvc2qqm1u9m1ZVW8=
*/