
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
IJNpVGmy2+n2knD+tmP7s0XmV4nubpLfl0semOeLboMXEF/aw7VlurmLZzv7Z0pbr8ShLiLMg8EXvVLXdO8XAZr3C7dnk+pnkToZpKmTsnanxzMtRPtMc0tHwmUm55+D9iK5xFuqSYf6J82HdKh1U+Ky8qKaZ3PdN/I80D8/2igNgQHGaajQpoFHoy9l8X2loULS8KjU14eQ55T1pO1pUP4Qpualqy/b571HvT/Ltfek/p5pDvCsz89zndWsxl+41jI9yTJtSkLC1CnT5qh/Z/KKcnJays9QbNH3jaWTMMV1lzi6IS8SR6lxHOzYfX79jnvnCHoK1+rT1CTx9ZL4eiIvKXlqGJ8136pWdN/j/InE2VvqRxGhFA3yJ1+XdmtXT1teIfwxY1uKCrNab4fUU/42qPVUE79kNq6vxN8HeZVw9Ybx87eyFXkv8Rv/jfRiT2k3z/x4DT2mBUb2qDM9fbbniBd7tPfb6W6edfHno9DkjP+G/Ox0pUL4Hu/rHBCv7u9cXKDnffU68cTq4nHeUOeNS5uGqkDPNLyJbrNeNzeS72V5QvJOG094d8+yquE6qy4etdL6HI/klfuzVZ++7p519tfEW6GPl8rqe/qIt8W6KnboyjCih2f6a7GjWmeHVNJW3DcnWqinzUq8l3jrJ2x9v6txf3Lr+1eN+4Fb37/a2n7g1va7GvcDt77/3Lgf2Hu/+q756vXRH4yfmfX8K8/GZVq7W3a/23b9t97659X+13bSNiZtZnwrqmurx0DFfStrsbZvx9qn8FI4FHaEV8DOcALsAhPgZXARvBymw66wCHaDt8BAuBF2h3fCHnA77Anvhb3gM7A3PAL7wN/BYNgE+8F/wxDYARsHwK5wIAyCg2AkDIXjYBhMgEPgAjgU5sNh8DY4HN4HI+B7cCR8H46CX8BIeAZeAf8FR8NLyaco2B+OgQPhWKjk51mTtItJe1k1EsLvRkRxk7iuD4yV/JwKx8FpcCKcDmfBeDgfzoCL4Uy4As6GN8I5cD1MgLvhXPgcnA+PwwXwI7gQnoaL4Bm4WPJtCewLl8IIuAxOgMvhbHgdLIAr4DpogethCvwxXAUfgmmwCqZDmScrbVtqmxfp18+T3Sj902UwBN4Oh8DNcAS8E14B74LxcAucCcvhCrgVpsFtMANuh/mwAt4IfwQ3wh3wLrgT7oI/hnvhPc61bqXdCl4ldmrXui0jPe3hJimn22EYvANGw82a8raKnkyD8r5f0vsADII/0axNPQJWwjHwEXg1fBROg49DC6yC6+ATsAQ+Be+GT8Pd8Bn4FDwEn4PPwZfh8/ANeBjWwiPwD/AF+BE8Cs/Al6By/7wMw+ErcBh8FU6CP4Nm+HNoga/DVfANyccmk7QnSR4q0p/fDZL+38rzow4OhO9I+Z6E4+Af4CT4nqT7fZgI/wiXww9gCqyHWfAjWAY/lvJtgJXwE/gq/FTS+2d4Cv4FNsPP4Dfwr7AXNn4Oo+Df4DTYBG+BX8H1sBneAb+G98Ez8EH4d+f8Z2krgkcl7dr5z2vbUe4wD/aC+XAUtMJp8Ho4AxbBtfAGuB6ug/fCYrgX3gTvgzfDZ2AJPAyxVcatSJsQDBY7tONWFsm4lUTYGy52zhNHJFyOhNPOE18p9TYVDoWr4FiYDqfDDDgPZkIzzIIrYTbMgms091mTxDPd4D6LkHhGwP5wpMQ3Ck7RzPMONUlbDOwmetrBINEzXDOOxyrXdTHIj1slP9bDTrBUwmGHtF9gn4S7BIaY3Nas1lxf0cL1hXK9TVNf9sv1jxrUl3GSD1fBvnACvBJOlHz/IbTAGGiD18BiGAs3wNlwE5wLd8B5cD+cDx+CZk0+Ws3O/ME=
*/