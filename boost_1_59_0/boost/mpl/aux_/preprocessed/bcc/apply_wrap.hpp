
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

template< typename F, bool F_has_apply >
struct apply_wrap_impl0_bcb {
    typedef typename F::template apply<na> type;
};

template< typename F >
struct apply_wrap_impl0_bcb< F,true > {
    typedef typename F::apply type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          0
        , F
       
        >
{
    typedef apply_wrap_impl0_bcb< F, aux::has_apply<F>::value >::type type;
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