
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
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
*/