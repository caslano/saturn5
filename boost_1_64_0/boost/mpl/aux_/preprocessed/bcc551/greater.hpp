
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
3RikEkPhMuxxzyLfLaJMx3e78PVGkclwffZQBox5j61k29h+7O6+2hQkP9/qx+BX/wZ2lQAUDVSP0qjSQ/l7cNTqgr0tENkiVFLZDvzsG7kPGettWdjshjt512xqpaGCKnZ5u7o92/4ZCGmhG2GI8wc4UzO8vd5tn4MXUdIxlCYOaU96E6I29nPUcUjL3gfeL1NXqtnIU/eoR1Dr/6R2p++gklSB09GGfcsagrlQ5ODd0FGzBE7RdiDNsYAPAax5DFdNgSL/QfwBHQIRZitzgBlr9cI9XcUaDcfZzHA2Otechu4Sdz1c/d/dCO8IEOgqMCh/D7xGZqCX5Ft4YinQJt+pVWlz6JgL9Jm/k4to7eCsTIUDUhheUGt9s/5QTzTaiM+hLJvLN6yl9i7o2BHQV6PhFf/mY1ERJRHDQtJczUByNxKdRA/AyxdCk44DPoKXwOMtKd80FauC5VnNgD4H7JZOB9SUJNTiec4hJ8955hR3y7ttkQZPAbNcib37K1y1MoHvzyuiDMdQCtn0dDILDtGH5GNU42yymewmOci/DpGjSKDaoYL2R/aYzN5lmWwTO4pKKYHUnxlFeHd4wXu5Bp2SJjaJ8vDQpsoq5nZzhxUPr3CsNxtnG3wZP0X981WUzFa3qjegM++yPtp84EoHPhYoFiEyRTu5CX78FeeAd9LLhZJ9Hvi9yKJKLIZipCQhNF3L+CcfqbA8697E99/3HgcQJLqoUudf+jL+7q22g7I+Zq11A/+/qJKAYTLpxK5r1/5p/YN5KGpiJI8C56nEo+Gw1uGxYD8Bt87mjeEqtuTxPAFnrhvvyRN5fx7AraL++k9Ssc+0sfprRjZ/Tfyv9CQLuL8WvTMbzS3mDuBBDjzaQ+ZR8ziS3HPmBT+fDHBBPDuGwayr+a8pQDL6uibYKdAm0+2Z6DtREosqj/2/d4FDeQ0CQ1gA7vNHtQFQKR4Z3gQkeGuR39VnlLUG3x3P3kf2+w3OLdFaaonaWC0Nc7pbq41OtOZ6b3j0s/UV6KmpacSiOvc0kqHGssCIakCxNOGv8D/wd8EWtvFq4N2NgamjxHSs4BZRNcAJ4RsmQYEtRT9PZTMGWVJnczjmYDGetyJcchP9E0OBfouQy5SH8hTonBmMZ8lAR0dZp4pjwAUeCNY831nnlHYrQY3Eu/3BnNPh+5eCLqFea+yt8d77gcR2VFG8mRTgkuXgnbeETz6WpMHhjFIrqgzI0A8Z2zz1U7D+8lSlreBIjgMerAYDLssaoX+hDxvD5gDDwuF9NgCq9oJnOwuZU5heSq+vN4UD8br+nv4JehBKGHWNl4zuxmvGDPROhfIIXpt7fjfeO6iGhUVxUROdJC+LEdAgS+BvFJM1pIUcZxj0zoeyoFnErGZKs4M5xJxiLsSJDbGqWtxqbw1C594C67lVyK5s66iKA+yJ0JvP7CAkxAy+fD/nTZzk350COMWq28rt645z50IZPkdi29BrDsd3NE7Zg8D+TymqDPbrdixUQE+SDN/3hVkY+G4gBRuImjffegamURGKuA1c/zfteejcKuCUdwJ9I32dcc5c5zH87bLIl1q4fQIMy33o/skt7TXwmnm9kCnOwkkDg0/z5xy4UZ80JT3ATN9DwoOuEvQ1vaR2V19TZ6h56iM1gtamHu1KRwKDb9EHtDiryRz2MnpGpiKhv4c6VgNucydtGGrZde0O1Ec1YHMHfYg+BS7RbT0EPYMcXUqDjMno5/oNbLUyEuG2YOITwQVv8CAkNEy0Ef3Em+KS+FUUkOWlKlvJvtD1F+RV+QKJVyOzBVTaGPMyPK+CQElqtbZeRQfdRdRyxS4H1tUSp2osqs0V1OAyyCCao59oNFw=
*/