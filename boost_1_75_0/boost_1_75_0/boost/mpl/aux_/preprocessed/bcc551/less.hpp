
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
g3k+3N01Khg/JwUXQVXnh8ppoef/1NZ5fchzATwLcS+TE4AL9AjUq92TQSudtjuIlhZbBM9HO/tz5jrnsvwwT3WSCdO/+p5anbBtp4skjqlLviRvyOa0bFpv7kjv8bvf33Qcx4/vcbUgQ3ZsfiedIkh7Rl7GzbsCO802Pm4Ybbw1xK4i2MhHfDBEikFZ/nEiUh7O8IPesHCj/kuP3Ya0Id55opL5sEDPo79ZJ/bdD8JOvDpkWyGgA9I+UhYar39g58eucU4Rl1erQnhvkAKEMDZMB9Ln3n4pxYMDOms7lTc+OJBxv8p4nYWiYLk2HTaO9MyL4IM5d2J3em4EpPKQEt9kPOn9IVcAt/W1N4EUkvQqfbDH+8Y/Xlr2EFNh66H27V61KXHbRWsVjspiHmkxJctr5TSmSeFkUlDWBxSLudES10wFunmz4yvSeaHdc6XK9MEywnQ0azScJngtCyW+AAEvT021cC0z7u+9oSEA/rRI8o7EUa2D6bl6uUpTs5o/RzLd0dpufDzvwxjkvVrX5Uw+mpqwJ9XFp/lTeH0CBgSZMBHc9soMKq1A0QCMXt4b2tZPeWnEIUzEwCQlJrz9lU5HjEitcOVM1oOjmSNubwL9IYghZ6Z0VNGkuKq215ubqtCyyEOud69/zjR3JPKSj9MyF3asNWaOcafFui6O0MssZmOi0F2dy6JI3+q6kXRH/xrMKeMxIY8qBPjP
*/