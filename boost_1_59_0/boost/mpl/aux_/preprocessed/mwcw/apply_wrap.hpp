
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