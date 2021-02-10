
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
5Cth9FKO0Q5hQAawRv3m8kyVI2Ea93Xjvufc8g6VRrcR3IUhFK5wA75+8w3M0YhaGSTd9hgKvsXK0vD2V7984bnbG5IPTGLoSZKpkhKFrZSMYaeUIuRnFBD+xYsETl8nwOsQJYrt/xDzZSGdjJ4/o31zfNemdYXS9l0TPnApxvMfk9LavdtwCoFJvsPxeYDgWNkS/jkq4M3IYa9xx+1BY924ErSrAUyo3Y7LvEOJKR3OlutsvoqHbfnVMs3oXXjv0M95btkT9NSfUFdFA6004IVFDbZEaKcfSm7gBVHClSmVvSLszee6EnutrBKqHpOWf4sAp4YGZKaMjeEDj4BsnAM3k1eH7fp00DUdPiXper78E5CJELh3r6/pdeAn5oLgOLbJMXyPRj/A9vacXPHeqYM11olr3dLI805N61cl28M2gGgEDw/wyUllqLXSzmlnZjRywH/FjJ4F08vv4B1QSwMECgAAAAgALWdKUoZxn4FyAgAAGgQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDcwVVQFAAG2SCRgbVRtb9owEP5uif9wo0Js1UKgqlQ1yyJ1FLWopSCSdh8r11xIRLAz26Hi3+/s8LIPExGRc8/d82InsUVjBTeYsLiUuaLbBvef
*/