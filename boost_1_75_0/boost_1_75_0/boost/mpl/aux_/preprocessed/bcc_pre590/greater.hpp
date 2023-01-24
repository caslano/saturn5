
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater.hpp" header
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
jaqk4rniT+zR3YeK+zzncTMtu05f/Q1beZU0xzBJP4thXv4pTmD+PCTModbhfEUQV6Nv9yL2g/tFuEhg1uMFNvD7VpyK1B62VarntT1C84K5mQ7nj/QX9qP3T4sS7uHgco2493x/jrxtsSt26a288YYvtB0TGtr+FBPSjjhFc73wJhwS/cX09j6UI2gWwfv2Pmr7D9fyB4xI/2H7P8+3snp7i46nQE/2LuUX34CCZu9kk5KZPhkJHHmMfvL04BAwKZnXM4jSPcYb3DL2UvKLVvle/rN8Lppklfu37x1dV+zdMzM10kDZttX2IP0Js38cPKNnestEgaFEbShZy2O/JBL0R8rqZYZY3RughzFTzPGAmbzSMQbYybX9D5pN33Pu8CkLZt81zRAFdzomdikL0Z+jyrauoqVz2lRtF5GxZ0+AA3KI4BOOBeZmsEOh8Dc2D7SmYSDadUkDBAQ89oFzg564/xSEgvqoai5ziUuPcW5JwI/j3tuwR+ELIyCkxxv0nOsd+DTd5Qy/EYfDWep773+oiT3/4giEeu+WHe47rzra9HYutnppT29jHAvzgBZN5z2xc+mjXh5sS57K6y2/KBUBYy17R1aUljyWoPaZNxkx1p2+vktQNDLQ+yAPM73Z2WYhUUGqMeXd5DV+xU5+dxK3uhHjT0sPwslsyC8UKflIRNfvkBr92UnZ+z817GCVmOKL4c7skEFZRbBJ
*/