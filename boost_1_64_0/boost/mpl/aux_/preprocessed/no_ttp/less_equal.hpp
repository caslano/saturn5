
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
oYc5R/LCm9dJSuXYoDeeUqbjByrNx3KoDeRpH6MdgKgN7u2CWoZ5kkZkUh+i93BdZMwVCN23qmJQAgFEeAGvZxIkr1BgosG73Xw+ADvwFu9avNknG3oc9zRUZ9X1chP5jbLrzpSn1wyYKz+eCq0LDLjvzT2E4bGHriEDGhk2hhihq1lMe80htBvAOYZ4XJt0UPRi4i5CthZ6PneuDyz+2DkuFMdH/K9NacHdwNnsm19yPWWnuK3idsK07HzLb3deoSGnKe4L1fcoNwEdr6/NoaxjOLEV0KhdH3FuwLkHn0cq5/awbwMAOG7TdqnhV+Xlt/LBAs4riD31udXZfAWa92X7ZovneVTo74nyI3mxVQ357IBPRPQOdIZSRv9B43ZXLHpXK/3T5KLkQSHU5KmjiyahVwBWvR+D4Hcl/iSAgbZF6h22Qhs+JjLwYzy1zHd05SlGqXCZe82PyJcESz8MZiNg3cFN7I6H8w83EQaziZF0KpunO2ahAEk4qp4DQknNEreGQjluJiD2E1CpjitA+a3Pf6CnmV0ie8H2Mntl/K1jHX/GuIEb0E+w6w==
*/