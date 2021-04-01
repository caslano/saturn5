
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
w4iBm9BLgLkgCHy49lLGlUbwb+W6c1xdaaJIRlUZooIpwWEw8dPnwLLo8TPc05TTHOJ9KgvnkhnuHiCYUIr0/Hws2wa2JxFvCklsqzQCzz005kb8EXws0FO4qb18Es0VyakgOwdM7MFODGpSi93MW69u6ma1L27E3FW7iV/IAimLdi81lBYEgMGsc+FBA6Fbdt6UY8J4BqkazQeQi2nDnrpCcikroE7xOzJP/72mmXSKdL5HZXwdVRZ5de0ssasjj1wVNgV/CMh2M1DPaXi2500ipJ3hq7y5P7PzK7p22iHrOTzc/9R7H0n/CfqVTIvWQOKxlr5dULNYk15Fp8Jd6cblBakctapn12ATL8y89wFhEXn+EDmdF5ew+0eDQ5d8vFW/e5904TAHh7QnjocDvVqVnc266SbbywK5cDWNL/sekWXH/oAukOzPoEzDNj7ONJ/Afep7WHrGPRZwkFM+nLKjU5WUiW55vxcdzX19nAny8ahURb9zo5IidmT486MySj7lSFIN2k8VEUIOYVWdMIBv1Zwh65S3QecGHQVRqAVkF5A3DSEf1I3vMA==
*/