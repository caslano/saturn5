
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
MGo5X6J3r51dNbM9sXTUJQGTkNtWZEH7QuYoNLfAmgnLkysTu3bQMttsZhu6PmFnOqvHyaiHP7a9JekSlmQnw8TVEZf1KO79bqlrZVlVJx2ZJLve8e3yJPv5sKJCH1h+okFtT3eh8ZOqKvJjQyRdwxtP7LgGqZnTfaOOSs03R+3l7nPrtew246m/ynMMXcJSOfGnd59JAV/c3pCWHVV3NRswdcx85zgEtoaqI6pR0JuBDdcuLjcuYJTNLAWXHprka2tS8Nd1k8i0BCc7DRg9QfUbrjYBRzvCwPT88ES7GvRHiYHK2Mz8AxVmWluo9BQfc7IEbMniFg3ZSmpvOTXBHnBRj9GOdi2eAbijAm2vGgrTYLM/PGa7SwkAvvKKwpPT830c9kv7/5CPpiZY4ezX8W0uuorVK6t2/fIquaCdNnh2wtSdnS+7JRMcyPoB52dDdfOtEs1p5iZOupXVTcy0m0MhL3PyIfdrUmsrB8Uc+X6C7L1qPudot/PXou2kjqrnD+53yCW4c3ptV8Sji8PxlZLgrEvL2i5v8JnlsvbjkI6X/tyGhXtc4HIuDJfEAfXBSUeYYcRUpO3EUIDOxXxc0vnBKmd3jPeSvhrdDdczFEUkx5t83Pc84ZaXd3TFaGT/6xbPm0lDe8AZP0uL44m+2J4A6rgPVtaZXCvu0x8sVq625VRNHnMhNX70+jyCwYTJQ3eW7Jkfhsz1INTb
*/