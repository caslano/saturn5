
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
33oKlFwEhxWpDbBl/hMyldlrsZS/n7QQ7lN8SqyyVgiwIJhKKW+nuWUFSJKUWOvnj8ptVcm/l0brpuy1bWQi4mEeaWopMfsPZUK2rklBiH7PLNsM9sE7ut9aK3xzuyX4LsE+22rclZoRFJyEZ+6unbmuz8xqD4SnAFVXM3e5+eddt1HdXoPyXwrgSF1+xb8xk3nu2YjlCqdugWkAXEUIJ3mrpzh12abPfPdWd7Kf7Icf/3yUw/BIsWk2ybbB6FNGym4LIR+6R4MEOfahwUiPzvxE8y0vOp/8pUdU19fqvIZAztDPCqe8+AL2FzsuW2Joqw5TP9E/93JjbDBtaQFrAj+5XbSwX3ihfa4eKBnYn8VjiyLJSWSLTB3Muqz39umk0fan1zPyZGKJjt/naDaMy+6OfpeLYnVNsm0ojgR8e7r1FeyMY7ZkweD2QWRJblXFH0+qQarTOKrBD9ssjLU91Kj4iLUodZa1HUtVgnmlUR1zxWNq9eiVVDigJlDRX7ynaHMays4KCRq6ThbtgJpRWd98lqoJQz7ujfD8+KNa+TX+SoICxw+swszZpmF5ZwoHJbVy/mXwzv7EsYLA06RQLiVmofTxTtkB6lEiq0ruc6vgttIIGNSOH9TI/IvRouPVY1HyrvUryNeMr+JlGE281+mqk6PLrtZcIT/rOIb1MX0e9BiQR+FjQV51U0UKE0/HyPLDI+WkIU0+Bpqj
*/