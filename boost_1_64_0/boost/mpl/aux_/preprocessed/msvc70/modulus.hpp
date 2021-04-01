
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct modulus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus
    : aux::msvc_eti_base< typename apply_wrap2<
          modulus_impl<
              typename modulus_tag<N1>::type
            , typename modulus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct modulus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 % n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::modulus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* modulus.hpp
zdEtXkSHJ5HSnf3NE5lK1lf2s3df14RbP+v+1NroeQegTk5+We7gAQ+SAUiyaeFnwUKYQsjJwe5k1ypDmhX/uy2HWmStGfq+vlRLtUFk7ypwfw3nND4pWrplpRWJ6zkuFK1SGxdtncAeoVzglRsuTZDKw5MtKWJS6oOCv9+27KHsY75OZSKoLxbqnC5ggooyqLmbBYrcnGYveYPQQw/MGyx/f9zawgzhyGYQuR9gnrx4eVk8KO3M6jcBjijLLnRnAhx1aX62QBGrDyi3wQGEeJLwXlGMm2uHG0KrkWI5NTiVc3Yvb5zc0oHxDlOs+LqB1mvxBuOYFXLy48oaNqgjHgNAy01tHlFK93vttGs9C6HG60fn6lIFrKPo6DfVVODZryIGbvLHjWGoEDgt2XpOMiLkAjQ2uXIel8spqfWRKz0qCzdsGc3YVmtKXWe3mm8dx0MHJ9JUqTKrQKsVMh4PFBGykIPVFKoVej3fRPiPERhCCfrhqx5wyY3R8dViXEl1WR5BXazXmQZ3I+vY8vgtoTHkZlE6/RmDxb32YEl6v21R0bKPpTJHMj6Q4A==
*/