
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