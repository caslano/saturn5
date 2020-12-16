
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
ZWyvkXt8ZtYCeL91xGSe73qR1+/pislaxmp3bS9Pt+M9QV/mmulzZ1PSM8SbEG3Gm9YtM9n2G1Lgnz2f1u9hjs8Ih9SO3NGu3FiX72Ru8ZQonhjF05j0nFF+5fFkdkv75fHUscXzVUPzdy23uagSIj0/h2/ldRujK56TK9j5W4Zpf1sjvc8/VuR3f8HNF+Rt/rERUZ7t619gvRI/+w52vp7nbG3sK/VSG3tLLHuivM+FVhb9+82F5qgDQxt51oEXeV14Y7/zkQU1/40j78WNvM+9FhfA/oKZE2eZlzowJtqz3F8yzn//+w5qnpznbXVgi/pZWMv9YLT3eeBS/McS9Nw5Fc0D188yN6C9HjxgNFhv7DZvT+KkMcEdd8f2t3mZ/+8gF+DVHts3Z+sKag6nzba5um6s7zlXVy/HNc/L/HsPkc8ijziCO+aKwfJ7pOfcSLc18T6vVEnjXz6vlGPbcTGe+fqI8i1123bwZVtkK9t82zxo1j5bG7zE0N3sCPHbzDl1XOMUeu9r5KtPjq++NL766vjqS+Or75CvvjGnrs+S975SvvoU+err4qvPjO8+OesvNvtu3dQ0/tDm8xIaX3b+B4tmtjrHV5+u4PvwVNT3Ji5M9y2xEWmOre1yQ8v4gBu1XkM/6xVrvZae66FrXOEyrXeD1rOOK5ypPg5ZGIvzsQVmYxvMwc6Yi33wQkzAPByK+TgFC/A8LMRkXICFuBCvxEV4NS7B6/AiVHzcs/Md31OK7xnF96zie07xbVV8zyu+FxTfi4qvWPG9pPj+qvheVnzbFN8riu81xbfdOa+B7tnhfsVnnddgmeJbofguU3wrsR1ejuPwCpyFV+I8vApX4J9wI16Nm/A6vA+vx7/ganwO1+CLeANux7W4G9fhXrzROX+S7tfhYMVrnT9ph+J9U/G+pXh3qTxLsAvuVnm+jQPxHXSMV1yq7ffV9q3jFW/Q9m/BOLxV270Nu+Ht2BPvsGwvvrqv7bnG+d+n7b2r7e3X9g5oewdRfR10P8wsY7bn3tchS30d5mMsZmMLzMF2eCEOw0KcjgswBRdiIS7CpbgE1+JS3IQX4zO4DHfhJfghrsA4YvgTnonXYF+8HsfiDTgH1+Jcy7jQpWG6X4VtlY/G/HuP8tFX+eiPDXEAxuAgbI9nYTwmYBIOxjGYiAtwGC7DkXgtjsLrcSzegeNwI56Dj+FUfBynYzGeh3/FC3A/JuP7OBMP4Sz8BtPxJM7GGurDVgszneMN614U1lA+reMN36583oGT8S5Mxk04H+/Hi/Ah/BP+GddjEd6LT+AT+BS+gE/j67gFP8Fn8J+41Tket+4nYRcv9fEfiucjjMVD2AI/xnZ4GDsg23bNn6bt1dL2rPOgNdJ4ytFYAxvrdUWk1Xrdbr2uIW7S6z7QeVGKEXgIW+LHaMaB8fgJTsEjOBf/iXn4KS7Cf+FyPIpX4Ge4Cr/Au7AMN+OX+BQew1fwa3wDv8E38QQqbu7z+I77B8V9UnGHaZ6IStgOK2M8VsEpWBXnYjXMw9NwEVbH5VgDr8CauApr411YBzdjXXwK6+ErWB/fwAb4JjZEXTd1r4dj7eW6+X2Y4sZY/BFb4E94Jv6MXdTXqbsB9sHKqPG9y+/nwDxt3zq+96fa/lFt/zNt/3Nsg19gRyzD7vglDsGvcAQewzF4HKfj1zgTv8EM/NbyeWC14rjTy/ttNR2f6hiLNbAF1sQ2WAs7Ym3sh3UwEeviKKyHkzAcZ2B9TMNIXIhRuAyj8WZsjLdiEyyfp0P3bfAsxWedpyNW5XQGRmIzjME4bI8tsA+2wv7Y2jq+urZ7wEv591W+B2BzHIjxOBiH4hDlLxHTMQkzcTg=
*/