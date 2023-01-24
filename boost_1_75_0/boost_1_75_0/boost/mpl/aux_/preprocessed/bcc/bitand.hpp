
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
KybJJ1AmjLXGroLPNUP6Nj0F0WTTyGSyMFbn7QxrMFAOseaEdV9YOclurJP0Vo8AHtbUB7anggjderbyB8jzCd0t1bcQTm9lKxsa7trNkU3ztQo2Narck7DStbKnbW3nlNnmA6iJVagO/xFtNOLPejZMt532DKmUg6EiFH6opLuY357ZkbllhLNNa9ZK9vws44g6oz3CiidQxVhkYr0FgKzsjaTqpK8iJDaEencxVx8b0+c71XlX2s6mM6Ss5ZrDXAZ2OQxYYnonTgID1VqYEt8n2+8J5AN9fSA5tWyWIrWEI7eo8z3QoJ09YoSmPTes3brk+xzokJE91ZPls3VF5a2iR5Sbt1bNOjOaku3MsTItJ9gm7i92vqm0OwiDC0qmbuX0skDdQcnUrTLX1Z040djZGlW90IJ1EetV2hkarsygs1chjLpc25KuDz0lIq0QmiWSsr6ooTp0x0H9HfzWIbRt3sEfBTiIij0d6OnY2rlrVztl3OcOuTe7nbt233QHP1/bedPBNu9Qlt0cuhLYqepT/ITHJmiIuFpr4sarouYzvBWQLfC6Yzv6muHHXnANjY30dCekiJ+AJV6lNHiyfwr6HlfxzAmewGrdvm17pyEGHxCn4myga/PcLlyBMvJ6uFnZ1OFOGKAAhoYf1abOEdV9UAOLJ7k86jLQ7OIu+lCjdqpBhQJTcNsmTn0hg6LVDq+1NAjVEsP+cpn+
*/