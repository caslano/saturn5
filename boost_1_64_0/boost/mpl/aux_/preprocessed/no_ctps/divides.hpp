
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct divides2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides

    : if_<

          is_na<N3>
        , divides2< N1,N2 >
        , divides<
              divides2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct divides2
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, divides2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
iy1fT1du/1b8vyvW/gvG/9cZzP2v1Yn/f9RB/P8V8mud3Sb+P97M/XUs8X/fbP34v1mdZuL/iQ79+P94E/nHEv93Oozj/+M7OfffrhP/fxWdTWE6a6Jus8i5//XkSY9qM/f/PIPYf0u4/qjbsb25/xsM5v6nOY1i/+Nj0hec+59vEPfPdhqPQ83otMaf1vgz2vFnL5f2/XFfPPXrUNefH5876JxzX3165Cmbd/zpHyfOji3m75sdW8w/0dE1MX+no3Mx/yZH52L+LY6uifmnOWOL+Wc7uyfm/yj3oS3F1ljQGgtaY8HuGguu5fiKK6HfIpOQWqQeWYqsKrHGgdZmbZ3d/qX4f1GZt9RT3QU+gGD8f63fBxDIVo3/f9JB/P810tblR4zBxbyujP/vmxQe/79Iif83oV8z7SKT8X9bgb693RX/fx2daQY6o4m9RhP/zyow8iGI4m6K/9fp6hWdXRD/v6og9nj5Ykl7UUS8PF0nXv5GJn/CfEs1MbVZZL++SCdevsFg/kHabAOfiNgR6/yDDPStkfkHB8yOvT7Hzw7Wp7n4f+NsfX+LFMdUDD6W+H/zbGO/SzS6Lf+L5X+J1v8y3KV9//63F96y9bSPts/++B7fkEcSf968/pccpC6/e+L/toLY4v9pBbHF/7MKOhf/ryvo+vj/cMQ2O/Y4PXZx7u/6+QP+OP7s2OL/zbO7J/6fU2r5fCyfj+Xz6S6fT0Up7YAsRVYhcWU874HkIAuQRWWW36crt39p/O+qqZzTJe//Gyzj/zWb3v9H3vv4A7eqH+CzvrbQ/X29zjsAV5FH9vTIMW54fl3pD0jYIdwfcJ3iD/Bih2bidRHvdEvooe8PaO7A7s74BYK602W8/IzU2VPIB+hu7Uh3TW21Lcb3kCXAJBKRhf9zothW4an0j/d86nhP591lyfL+MSlPUdXcSu1f0m5qA5c0rFbvux4brPfAZ2fE5/Pk8+f9wseLjT3b+kw+1Orm2PbrJppxuJ7vZJKMu1+VNnkJ+Zj9fKpeRWdxWaVbbQ+7Cb2ryc/rMdce66jT97R+LDo0WyeIrSvjIvw8Mrb15Rn5eSIqK0Z/z7hgG/UyeB/iDD39Ebpj9Pu0YOzCXvI+xBmx+ylKSSv9MKxO529p8M7KGUZ+l1CxOvXuykWUyb2lvLuyE+VaG14u6ddsW7X1Z7Vq5+eZYeXq1PEUeZ7xn38j+mzdVvp+IOdMAz9QyJzY3z2p1sOCeP13PtbNVPxB4UrlxY+xnW/13vuYsMOm9z6eRX3kxQf2v2pmbO99XDwz/Jy6hs9qHzgq+N7HeIO1R2YZ+8JiqX9N576iM35r/rA9J/W9HHlH63cBnRVVVeWcPnH3FZqvX7n2hPrZW+RXUx74PVHqn6PT/9mulTWO47m6RO4TpD2U9vmM9BWk19pjPQrW9OY8wO9naTbC7aTu1flsPvVapxx/d5NGbYvVfFavbwdIvdRKvSRJW2yPfKHVSyBuUlPukEOBg7z9Ok8Lq5s1UheqLp/o6ie6+iJrtWMuUtc8V8VcT/S61PuxMvf8kE+0xfKJ/md9otcl+fPJuWHs2rsqhtVntLz23Z8XDfnv+UqrXNr3e3yz9flnJD159mHZGauvv/yAJza/r9Q/roEFSHaEL26q+OKmwVQ4HY6Ax8IpcAacDmfBGTBf9alJvsmSr+pTmyA+tYnQDidJujqkVdI9I+m2hbWS7gKx52KYDC+BA2E93AVeCveFl8FJ8HJYDK+AZ8Or4EPwavg4bIDL4DXwKXhtyH65P4fb6NjvFPtdsDcslHQNiE/SvSrpEuFCSfeY2P8EtMNlcAB8Eu4Mn4JDYDOcBpdDL3wG1sLn4BnweXg=
*/