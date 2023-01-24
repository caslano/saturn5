
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

template<> struct less_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< integral_c_tag,na >
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
l8M8lfg/8JfnHrHO0i9KeMydlLz2sxw/8tG3dghMqEReuE02Ufnp85UZexmSLjkxfJlSRrZ1+PWqsRJbjjU/1jqYKe4U5a2wmOmMYjzCFd/gzLB/FtZA8k3kiHWwVcpLcz+OC2ruzDOPt1EAXknMfU9Jmk1MkkOshRVg8adMztnq5qIYgv/nlxN3zVZeZSF0keENxUgBtx8L5AGuCjhgYm5HhfgRnTotZH+lk+EmXbXBEHMzYt1OZtTvD/tLNwfuf0IY9VwmVOnZJo+UdCwMg4EEDqty0UuLGzMbuDHnOJ1rAzEXhkrrH4QrDZyU5mTBVHo+M+d1+E3HdpbEWpAWh79wdpddbYZ3HMexQUuRAgWKFy/QwnCHFgoUd3d3gjsEKcWluDsEl6LBC8Wd4O4QXIIFQubbk+3sbO/gPvez7/mf6/eJ/Oxj5zW5GHfWms1tN4GbqSVBfPu9q6+iyJf6Xbb3apws88/22zM8LLSAzuDIXJONrsh1UXU/plvckxV+AuoTahyMvs6Cs66u3BonpYJWW/uZXB90sogC89C2ghVuvZjRtRkIZK2hBNTejiURWmFqQzKWqZK0zhvudmXiVNNajjByoWOJOmviZeOqFWaMwuQc8P79U6Hyy1ZEhSQB5h2csKQoMzYj2/hi3tWKqv6mzBaKL9lu56/D38jje8/ovDpj5QFpKqmJa7+NURjWZYZU3uqspf8ei0bO
*/