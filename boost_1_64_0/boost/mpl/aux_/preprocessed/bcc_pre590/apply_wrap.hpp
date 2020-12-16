
// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "apply_wrap.hpp" header
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
4bhfVueIrsuK2LmO6XLAWmIwW4b2PXU+9Lhs7X7PGEslX6k0qD942LFUy3AeSPj94gLL3RMZ64qdHu/Nf6Flwb2+4/RW8l7fdRx9QHz3+J7RaWYI6thF9m+1D/nFTpN9yC+xmnyiIP37TsenCdznUujmfBLyXSZ/404c7g9E57tB/6HoCJnDvdzqc/Yj34/kby/cK0TncJHXPxZdUoJrrhTm3fMn0M0ZKuT7qfzt3fMqp/tpuVp0L9xroNtzWK6Vv71wrxPdS8v1okdpuUEY7om1vqQvGSrWRLenJrCVALMbHaOVSPTusWm4yWO0GpSu+bmn25WQGE8U1rH7jN7sNP6YiJsQuyVgdBOwXwaMb8T3uZXYqFnvWp2qVfpJ+5WnzaM282tPq001sqZtGsR/4/E8a5tnB3OMGXq8S9rtnraW8uoOqy2f14+9+XiM0NOxf8+6StfcifhdEXeY93v2uJyZe7fW1Rr1e5yOvgT91hsmdm/A5jGjd919YPa7UrPY42RymHt8yKv74cHEUe5mNExMwR/owSvz+P4PgnvfayaZ/Q6Mkm4ORKqrvslDxFYMl2T/X94rWuvIl98rTb93H3E6/Vpp1IvDRUoLSqOoa49GvJrXwB6LWHeqhX7kHxyTMv+jaCal8b0ej7jc608Rk3s94ZiMaT/pNKkDfy60scXlyvyS2viQ2VMB099j/0KsXOkfGFg22j+wUu/D/HTAdJ/vmYDx56JGrd3KiT+b5lNTjZzX6KZ4npkx8XruzkINPXpP55Dl/v3/keRy/3/GXN+fxwLZQ48uW5z4DefWmf0bHndqRCevyqkSWIurPWaYiKflMHsuyXJiG2wZMvlN9TzFeCZCzfyWq9YMp2ufH3AOln+DbxixqVYx37WY1FP0oYrZB40O59NGgRfb5ZimTPviUFw29jzczothr0aN1wJtEnI8B/A5mMLYVHtkBoRbt7ZZyLM8d1sZmo2BGvh2tHnoa7XrGfXrmG8RcI5nw83f2DLgmMJC6dgqZJidgjUF5Nk67UFyOA4vSHvcOoBtPI46pc4u3BZ8SXlBZWjJyKipmkWzpWu3i5m3lmX7iNNDh+buuvNXe3im80m6/w4xd+PnL4qZbjLk2THhyYM4vDjpkTjsxJyOApDw+d2xM5jaHp2u2QW6vy06P1N3Feb2R9pNtMLozVd4iTDS3dpapU+i2dFuybhud5+7PV9fFut2Ngjxl6e5ST7n6R7gPbZKpzBeIZ7kXv57RpyWRBDb67/sXXl8VNUVHlZRUQOiIqVKXXEtmywWlZAECIQkZEFQdEwykzCSzAyZGRZFBUXFioqKSl1xR0FFxa1qXeqClSpVVLS2Yl2qFiu1qFRRe96533t3fTHp8kf7y/x+Jy/vfN+77+73vnM3GwvmhB6kYMgn0USTtCccbODqHqH9dQzVBhVq+OkQiauf25xmh0osGOs7TOpkvsC7DlewjJo2wI9QcUc4jlRxIxw/VTFHOAaouAwHp91AiWFSFGas03bbfv03KOBUlnt6scCoJtGYa46rczAHO3gwT7E/hrjwJrFG6ygHhoDws0MNXJ2jPczAOLGw5adf9wx3cbIZzCEV/hthcNQ9eo82MbXdQ/h/ZnPQ9om1gSOdeHj7d4zNV9s3TptjHRxpWiEDgr/3s8mT7YtHYrdGGRy7nRG8fINntzXinaPdPLQ3wv8FDg6MIkga0W8o/AFe1Os9IaxFFhf2Gw6p4IxROfh+wI6hQT07VuFwxQz9OEWv5sNiVd9ghAN5bLzJyaZmxNF/mGBhyJ94b4mCq/3oiYre7COWKpgZZ8HYq8GR78XaWAWHrVfGFTiTbI61/2yFzRHBRzgqgeOkE54=
*/