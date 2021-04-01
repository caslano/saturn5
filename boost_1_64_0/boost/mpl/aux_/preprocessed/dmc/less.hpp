
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
iHRKSEZei6wQYRqcHEKw9vyXWyiaaLnRExsm8/SVs2bQ32SwdDduXbUbsA9qBc0FuFEUc8mL8b379InJQFdVyAAUi62Z0PBWp0kBvwZYsxBwWzk8RnbhBCLnnQ8UP6C0Ny1/qUWRF3CuzKEwYoItzChs3nsygdD610pMdgVYpSREekXS6kCO6FPz+e8JFxewvu/A7Hz+YQeaz6YrTMMVtcoeumEu5fEPLh6gZ4CKk8HxVyv2RE18DFY7B21qMXDK20AqWhsHAKJkh5o+wcdkEytNWweXGKmD6tUnOp4RCiZcPPhThB/REBLOnemQUc9Zs3/uyLuxvVA8YUvbopOLZXNHyzHXGwo9zbEbU0O3a2H0+zsLzo7fQcZb7y9G2kq9E6+1h9e1wVSBuJOpcLHBb33BU70E3+aj0n25SgodwPFqc4dlRJHtRl14D1OQVattCXapYxQAa2X3b/dMe1VwuMIcnSUKGmrbVHN7xwSs4HqLPjtgh/NSDlU7y0v+n7gPFRdWFV+VfFfhLqJLXcPEYsaRrcWZvvh0p4Vdtf1eWjSGIReLB9R1HIJw6Q==
*/