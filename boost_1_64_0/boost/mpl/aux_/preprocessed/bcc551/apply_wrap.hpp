
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      int N, typename F
    >
struct apply_wrap_impl0;

template<
      typename F
    >
struct apply_wrap_impl0<
          0
        , F
       
        >
{
    typedef typename F::template apply<
         
/// since the defaults are "lost", we have to pass *something* even for nullary
/// metafunction classes
        na
        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          1
        , F
       
        >
{
    typedef typename F::template apply<
         
        na
        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          2
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          3
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          4
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          5
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap0
    : apply_wrap_impl0<
          ::boost::mpl::aux::arity< F,0 >::value
        , F
       
        >::type
{
};

template<
      int N, typename F, typename T1
    >
struct apply_wrap_impl1;

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          1
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          2
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          3
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          4
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          5
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na, na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap1
    : apply_wrap_impl1<
          ::boost::mpl::aux::arity< F,1 >::value
        , F
        , T1
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2
    >
struct apply_wrap_impl2;

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          2
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          3
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          4
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na, na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          5
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na, na, na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap2
    : apply_wrap_impl2<
          ::boost::mpl::aux::arity< F,2 >::value
        , F
        , T1, T2
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3;

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          3
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          4
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        , na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          5
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        , na, na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap3
    : apply_wrap_impl3<
          ::boost::mpl::aux::arity< F,3 >::value
        , F
        , T1, T2, T3
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4<
          4
        , F
        , T1, T2, T3, T4
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4<
          5
        , F
        , T1, T2, T3, T4
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4

        , na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap4
    : apply_wrap_impl4<
          ::boost::mpl::aux::arity< F,4 >::value
        , F
        , T1, T2, T3, T4
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap_impl5;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap_impl5<
          5
        , F
        , T1, T2, T3, T4, T5
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4, T5

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap5
    : apply_wrap_impl5<
          ::boost::mpl::aux::arity< F,5 >::value
        , F
        , T1, T2, T3, T4, T5
        >::type
{
};

}}


/* apply_wrap.hpp
UX2ZesQSbMEaDGIMQ5IPhrEf9+AwRnASW3EJo5LPceofi3EUd2A7duJe2R9jOIr75DxwRM4D34GpX0mX+Zm3FIekHPguOR/cjz14QOoDPyL5YIeUAz+Is3gQT+Ihye/+dJnPey28B2V+24mFxA9jBR6RcuL7sQ6vwyh2yfHw3XK++B6cwA/hCXyd1B9eL+XHYUz6KuM2ZmO31AO+F334Bjk+3iDtgW+U9sQeaQ+8UcqPN+Ei3izln2I8l/zwTdK+eIvUC94q7YN9Uq94G47g7VIfeIeUE/vReCBdvVnqAT8s+eCdGMC75DxxAGW++xapV+JjOI5vxWl8Gy48cFr/LDS9/ePp8rzsHdaa3qPIc7N3Gnle9S7puOlN/bQeX72FyPjqLUfGV28d0v+9YWQ89fYi46h3DJkneCeRcc07h4xb3gXkvu81PqPHKa9CximvhTyne0uR8cpbg4xL3hgyXnsHkPHQO663s3tn9X4u75IYJp/PSnnIBxkHveXIeOf1IeO4twsZV71DyHjqnUDGU++cXu/yGhN6XuFNQ65wbzZyX/BWIPcDbw0yzntjyDjv7UXGee+YXu/yTur9nd45vb/La/ucHv+96WIv54W8b/LWiAsubxfy/O8dEcdd3hPiLOX4vL5fePOR+4W3GrlfeDuQ+Zt3CBn3vceR+5B3UZziOF/Q9zdvOXKf8gaQ9xveAWSc946LnS7vLHLf8TomJT+XNx95/+YtQ967eauQ+4PXh7yX8XaJZU5vv1jl9A6JdeQnhjlfsdPpXRZ7nd40xjPe23hLkPcx3hrk/Y03LI47vZ3ilNPb98X/zjj+VF96v/6Yelm9Vp8zwDqu0eeMItfkc8aRa/I5U+LqveY5c8R9uIx+TJ3++3Xd823G+RucqvCNTjVKWJDQ41RTtzuVcQfpBIv44Mp24X+83d88DuNEsu1BXfbkVGT8SLa09uRC5LpNLkeu2+Qq5LpPrkOu9+Qwcr0nd+n1ZnIfMs4kDyPjR/JRZJxJnkLGmeR5ZDxJXkbGm+Skh/R4kmwh405yIVJ3yaXiyhLkBXAF8VasQx/G0I8DGMYxbMEpbMBFbEbHDPdhTMXdWIoRlPl6ACuJN+IO3IMdGMU+bMKjM//G62DWTJn5jj7PlEWkvlOSvqvrMyUPqa+UEqTPpFQh9ZXShNRXSgyp75Ruvd6eMoiMuylHxdVn15Qp4g14EhvR9r0nUf4qe5Exq/MvSkLavygPGaeLypBxuqgOGW+LOpDxtqgfGbeLRpDxtmgcGb+LZvT2ZtGSXm8W2b6vz6coFamHonykHopKkPMuqtDp5K/jjqIwUj9FXXo7e1Ev0i+KhpH+UnQMqbeiaaQeiuaReisyHtb9tyhd7CR/cWWhvYsqifvQhy3YiUHswxCOYhincQ8uYBRtP6A/oIW7sRCbJT+MYB3uwhi2Yjf6cQgbcAIbcfYHT6I9nsQi73E4/8RO23lST4m9yHWYOIzUV+IEUl+JJ5D6SlxA2jsxKfE8ae/EdKS9E/OR6zixHGm/xGqkvRKbkPZK7BDHyR9pz8RBpJ0SR5F6TxxH2jNxCum3iXPiav9MXCLegg7zPOqLp2BsQnnv3YB5xMNYhgHcgY3YhLuxE33Yj804giE8jntw1jzvX67f35yTuW2H/TxV9Vq3Kqt3q/BOtxokjBMM25nbc/6uhRRd7y6bknqxu9KR/uwqQerDVY3Uh8uH9GdXVKc7XF063eHqQ+rPNaK1u8aRdnBNI+3mmkPazbWEtJsr6Wm63VwW0s6uYqS9XGU63XRV63SOh4zfrg5k/Hb1iCtLAxOhQeIBlPZowZX2cEl77MJR1odxEv04i4240h4uaY9mlHY=
*/