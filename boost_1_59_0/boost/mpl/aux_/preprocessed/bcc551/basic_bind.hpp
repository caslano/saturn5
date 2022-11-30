
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/basic_bind.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      typename T, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg
{
    typedef T type;
};

template<
      int N, typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg< arg<N>, U1, U2, U3, U4, U5 >
{
    typedef typename apply_wrap5<mpl::arg<N>, U1, U2, U3, U4, U5>::type type;
};

} // namespace aux

template<
      typename F
    >
struct bind0
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;

     public:
        typedef typename apply_wrap0<
              f_
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind0<F>, U1, U2, U3, U4, U5
    >
{
    typedef bind0<F> f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(1, bind0)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(1, bind0)

template<
      typename F, typename T1
    >
struct bind1
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;

     public:
        typedef typename apply_wrap1<
              f_
            , typename t1::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename U1, typename U2, typename U3
    , typename U4, typename U5
    >
struct resolve_bind_arg<
      bind1< F,T1 >, U1, U2, U3, U4, U5
    >
{
    typedef bind1< F,T1 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(2, bind1)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(2, bind1)

template<
      typename F, typename T1, typename T2
    >
struct bind2
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;

     public:
        typedef typename apply_wrap2<
              f_
            , typename t1::type, typename t2::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename U1, typename U2
    , typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind2< F,T1,T2 >, U1, U2, U3, U4, U5
    >
{
    typedef bind2< F,T1,T2 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(3, bind2)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(3, bind2)

template<
      typename F, typename T1, typename T2, typename T3
    >
struct bind3
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;

     public:
        typedef typename apply_wrap3<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename U1
    , typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind3< F,T1,T2,T3 >, U1, U2, U3, U4, U5
    >
{
    typedef bind3< F,T1,T2,T3 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(4, bind3)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(4, bind3)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct bind4
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;

     public:
        typedef typename apply_wrap4<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind4< F,T1,T2,T3,T4 >, U1, U2, U3, U4, U5
    >
{
    typedef bind4< F,T1,T2,T3,T4 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(5, bind4)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(5, bind4)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind5
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;
        typedef aux::resolve_bind_arg< T5,U1,U2,U3,U4,U5 > t5;

     public:
        typedef typename apply_wrap5<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type, typename t5::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind5< F,T1,T2,T3,T4,T5 >, U1, U2, U3, U4, U5
    >
{
    typedef bind5< F,T1,T2,T3,T4,T5 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)
}}


/* basic_bind.hpp
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
*/