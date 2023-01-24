
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "plus.hpp" header
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
6TRd1E/BUDF+4CZfKgok8f4JBZCgDCg8JdBFnONx696jVKkvwi/hzW2J83+MWwrziSJgStbB55ch/vVwv0Q4OhABqvFRhca+fcSJQqGKL8CxWcWT8utaRQC98VEdQkS26/IrKChqVyoNnvYFuHGjstqe/Lipnn8BI4wdePIL5PdqiaaiOFR9AL27SpyqzydzoVrNjRXQ+Jwsbwi4rYxxBSIjlZ4Uf2uCPB6+No3/MX6a3NiNpVuDIomtRIH+huUvz9RE5f5nM53pv7vTZCy9bP4C5C6nhubO9Io0qAV1q1IPusgSTpdZX3xOormuu5M7pjARv43Ou8wloq5+7VSFaTFxv+bW9uXZE1e157iAL8IkMjI/NU+Zv/z8oOcY/Yz4gx5TwPsCJdwvKZH6V7JM/iOyRb9K9h9s9yekVtVdcIzCriq7spbd7PYfQmAhsPGxztsDzHPU1cAOU7eYGNFtDxtHkOUkbYaNoTaVBQHyaXhkREW2wzP+qRRqPuQCbfbdGVw3TJoUH3swe3cufB0ERynyk2yRoWPiPPvxoqpSE8uvSNHCz2tcl970/OjDld/1wdpK03UaCHIevvk4vvL1+neIURMdPoksIZPB4QRLNDNzksqLsHgfDxxkZH7l6wNnLJjXUOSKN7K/n/vkbC3xJP+S4yYJZnpw0b/gwiaG60JZSTMSbjyPIn/PX52bfvdHeppoEsNKyQa2TwFS
*/