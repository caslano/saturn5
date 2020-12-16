
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
9zt9RCfzuRifhujf6X+irWV6n7yt+PeprnuFnNRquQ6+xX6h7gp93YWBXIPhaK0fWufWWs8qUK9z+HO0Nuefcm04lItFpVGkz/lM+XtQ85Nr6rH9Gq3Nv+eQd+5l0h/XYfspY1uvb3Mw14+003Pew1X5pDK5W/mu5elwXuTIgd73UHlXlc+iYHs+4+aY5f5M9EKuz7j4NMf1aSP9nI3fOK5t67VzSeQGmj4t11noLAj8uIzmiayR9/iFcv6LsQP4rMKnjKcknZkg3WkLJBcmvuDv0cFr6zdHeO8d+7TaermXyPXicwx5R+mP4S/8lzzkOYZhQ92HEMQx/FGHY/ggOrhjcI8jxTbRH8MRrbknPuw+huDPwTVBzG8Q/bW0DwW2z3eyiC+l9pi056DaoP2hrfnc2/7xdbmOjmwd+DG4z0F1Ha+jeQZa/Mb4Ly3TjC3KQQT+vfs5iHFFd1tiRJt/sfTnXKwJbakoc4/vqb+X/jXl7rbwHTPX5OvPv2jy9c8PWwzadwztczzibp/qOxdE+z6IPrj2ub9PE0SLP0Xal4Y1pX1hG9ztC77v8G3QNl07dN8bdb/tO1bfb8fRrhJvu8bX5bxW19N5dTTVjyuH8Yf9UXf76vYdoC/M5wjJ2GxRM99nUpk/sdblW371sqYFcj3V97hypC2kuZMdk2jYCfx9t6tNct+Uc13TQNc9xVPeSfnBlHtGVf6AvrwmV2bf42oO5Ffph5+wcM5BxqPeeSTSGdk5WbOyc2yBPZclbdQ+l4WrficcckOU8+N5jtffM2uezX5+VMbRWtsadD5JfY17/83euYBHUV0BODVREQMECCGQIOH9ECRYqqCIQYiCBIgQ2lDRJJBAgCQseWBEkPCQlwhRQEBQg6IiokZFDYoaLVgUiqGCRYs2WmqxpjZYsFTp45/N2dmZnTv7SFbbfs1+3/n+7Oaee869c+fOzH2c2dzSOf6c/GDiyR05A0r7VB366h/39GgcD/9Pj4ePcY6H94zLOu/s3n37Iz+MjNq65sHZNGLn78cXZ65+vO1fXzzZZvKn+5e80fuHGyeP3+Eeh07wGJcdZNivkSzpfiLpjPs1npRx2R0wFj4FO8Od8DL4NOwPn5H8ipEyya9Y8guHOZLfPZLfahgJS2EXeC/sAdfCeFmnPhA+BEfAMjhG1qNPlfXo+bIOvRA+LvazQ+SZHI4W+03hJLGf9SPW08Op8CI4DbaB2TAGToe94Ax4BcyBg2EuvB7mwVFwFtTnGcReU0U9X2kcn5d0rb0cj2qkStLVSrp28IikGyz1d43U37WwPUyAneB1sB8cBgfARHgNvB6OhDfAKXAELIY3wrkwCc6Do+G9cAxcC5PhengT3AHHwZ1wAnwF/hS+JePrB2Aq/A2cCD+Bk+Cf4C2wBt6qx2+VZ1+wRsppjN+aIsdpAuyk2YHdNDvwUpgKb4AT4Xj4c3grnAQL4C1wOUyD98B06IpHWSl2o8WuMR5lvtgtkPZRCJvBIhgF50g+pUi15LNE8jHGgQ0TvSbSvi6CvWFTGA8vhgNgOBwGm8GxsDmcAFvAiTACZsCW0DlXDItgazgftoElMEr3C3nG3q8+4le8+NVf/Lpc/Pqx+DVA/PqJ+HWF+HWl+DVQ/Bokfl0lfl0tfl0jfg1x+8Vzob1fL0m7fkXmf16FveEewz6dAfB1OAy+AcfCSjgBvgknwrdgBvwFnAb3wiK4D86Hv4QlcD90+VXrxa/j4le1+PWp+PWZ+PV78euE+PUH8etz8euP4tdJ8esL8etP4teX4tefxa+vjPOX5TJP56W/KEaqJN3cEGt/206OdyxsDTvAtvAS2BF2lPMqDibATnA47AJTYFc=
*/