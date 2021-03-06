
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
ESdt1/Rw8qN2k8pbIH/snEm8MyMjKWMY1o74Nt5pFlqYb7m9Mi2Ut1JSEpEysC3MZktGSiKKqAg8S3BAoccoecU/zADhgXrhhY80uurtwxxqz3mB7u202AVmr7MVH4K1eh6AWPimgcWmiP7iMpqtyYKnXT/3resa6HVOaLKDyIVQJM8cZJaRvAdQ7PQN/MQ+RvaVweURi6Lgp+PDoRacirJAVapINgbmC4iqIt7CfSQwSO9YubBO7JYdSljbIDY3puhNCwQIjUVYe1MQNCMv0RIXSS4PAspqbAvfHWfXkxmS6RLOWtabHhDPIDYsquNHIgWNFuG10hW1LBMyDTc+3RIRaFPjPBM3l72guHISp9Brxx4rBffaYpIMgRiO/x2r6WQIR28Qt5hBrqhXFSPvEgpi+NsJJvYv/oohvECbHDg1TYBvGSMQU8CzhqLp1SdjJDbBdNFnrkAIwBb5BojvddI9LQhD7KwfAi6llVRIGskQatwrUGmTbUd6KCMy7KuIQ9E1U/khJGKBFg40z/FdOpzfX+fMNXKAJm0SAkUBRX427HHewNoBwKKBIw==
*/