
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "not_equal_to.hpp" header
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

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
ShJnbacp/fU3TnjpXVc63epWupPOQsQO9swzj5+ZoaOYVJRI1jU6YbLl8Nixfc6FJ7vGyHVnxRea3S3dcjZ1xxNEMhUYHeu8s2OVh9+hJRNPTJgy9JjRESyN9l3D6FyYJko46nhEkS4KE6SCUCLtG8kwoQzlDAXkiZXmt4LHsIMhqYhQhuHqzfCRWZpyyTykONowJJjKRALLPGBJub9wjnymJCJoGwqpDAxYuQhfiAp50i4dRGHCUEok2DIBzMkfjUKWKGSaGrPGWq/V6iUPVv2qjlq1OpryHPlhHDM4QQA+ozzxAMvXTEfDt4gKklaMkoc2moRUcMm3ynScpXV9VasYPZ4ocGO6+5S1gYRnZQUqjn5FNCBCMnUTSm5++nT9i1k/bx6zxFdBGzVbFePh4cHUYcH7kBLFDlG50WLirqbuPcY9rIcPz76e9Ia+P8D0uo7Xq76/n1J8GsMW3vh4r6fz2gTOzfE8t+HUAA98+xYPcryc2y4eDPBcr2/neKl/tH28zu1H3GthMofn8B7/hu0Ij9Z47NsZHgGKHEv9foPtFI8meD23Q732sM31ub88X4ybm4pROUkg4aq4KcFIBDfoM8RCWIsLkOD5wkCH36WZcq0vFCz8feGcNNN4pZlGrabBJD5IUjAQJViA
*/