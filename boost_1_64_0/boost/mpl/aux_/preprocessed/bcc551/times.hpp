
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
IdeVBXlza+DBrylivwoYqh+F/euQ6cqD/shvenmC+n9b4NN7L9yumN4T8Q6t53G+3RnwWSrf7vJYnG+/9Xg63+4OPDrf7omY5Nu9Hkvn232RJ51v94c+5NsLDHsAzGQZ5eOD8ret37y2lvVwLQBd85BlQft82OrSPnms2unptvSI5UFbetTqwXq/x6wetLE/OB3h49n2R9bx65m9j0OTrSWwhpZ1bC3B3idY40ymxsv6k57ecO/VP2td7Vn+lNbdyhHsM0tsyCxJNn3rlfF+5E+nOL5TP5NgejzoWeblkcX9K8dKK8b0GoG/hgzfRP4W6LqN/R0MY0+V4f4lJR3Xf6Q44vrPBNNx/ZfPESzGkANm56H/x9fdHunP+TrXvxkZ195go4KX+92LG/d5ntXLQ1wG0J+vdHrmQt9Q6XrNxEZaz8lPdWxj6NSmkO5NoOkXug1nU8vqmKsIfTPRMe2Aw9/c6d0ZU99I2wKaLqctofnPGn4ebQWWfMHDszU8PV7ydI8XiEde8oj/Npqpvs220N2LHvVuO+iJlzLda3vH4719XijMXkP6DtBJU237RVpXYyo7Qk+8mCkOLwYPXsyUXzuBJV/MSOPOoScY694l5FxViO0K5r8wOdzdImby25Sbve9LIo6Igb805FzWJgSO1+4hp5qKNblJVrSIrkv3y0NPsN/3Hpqr+S6v8PQ8Ko89Qz5LymMvnyXL45W+JyqPV0VcyuPVEZPyeI3PovJ4rc+j8nidz6PyeH3EpTzeELG4PPYOPCgP2TsWXD/v9lEa2hh5Z0HX50z0eZrMJ5kN3e948DX7OuY/L+Y43X9e7Of09PNif8fj58VcsHAvsAOUrtP4Juiczew9EJrKXvIeJPqJGbwHQwv3unozdL3X1SHQUCR0/aHQpJPC+dnv6ygBZvMSzO7tN8BsqVnvZ/YfH6y0zCsyz3nt8KBlZvk7L8Ll/C5Bxx5Y/LmZX7cU7/ngGECjsBZYrZ63xtcVm0ZjPS903TcbgqbfYYdZbTKT+4EtcmyqNV6dwjagHNZiMJ4qxNoSq01n7cmMtWFoup4vhUbbYHOk6X4jVs+zKO2Hg6EcKZzRQisNDLovCvv1UThl6N6vddx7DKwsvRPSl1ldeiekL/d02avqCF/PrX+F6OhtcF6ujPSKG/s+UrPgOXGUY3QR3eNo0RAQh3OM6NJiEM6xmp3Iaa44zT9L4y2sj/SP9pvaWxrliVXMqhGTs4jGIybvmRrYojBUXFt3XIfMLIuZ66NOOCZdJzRSHgvsxdUe1KvYEzoo/EaSye+O45jzfk9YS6F/B652nPd70M/PKcXMO9EyCndaWBgslV3T8tGly0b4Cxf9xm3FeqXeyGvtxnSjWaVsofBntE/PfEH4x/vc7e/d1rpaR5trXfUDO1pX/cCu1u1ChIlqzYzyULmtiTl6ycaANJwQe8xaDZnDujbmeYbx0HUhoy3B6WlJ9z8x4maErJHz7F3c/6TQI0mgMN4a8257TUZ1xYbxtp6eGQrj5DT3xwAjTz2bVGesvCPiWU39GqF6886UZ7V24UzK0Ee1WvqL7w45FwmPBUbMvBTN8qHWdKM6xfnLY4Gxr2XaHF6LeaPYWLPVnqb4nBJ6qYiLzxqcrvdFvNNueHdk3/s936oqbVuW2ffHdHcKz6JTtQ9NstLCvrWaqT2hPxjqZrxZFSOvU448cV35cE/PDKXhI5q7oV1d2Jy/H036ggLHPT+mvVyW3KNE2j6ueZRlGPfzPHnU1j4Z8Tjtn0p6pJ2cFvG4nXw69Mgjhdcfhzxd76genO57Ue8wNghmDpxB948efFRGn4tY+AWZ4/r5yOd+kFJ6z0hz/AjiML6Q9FA=
*/