
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
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
*/