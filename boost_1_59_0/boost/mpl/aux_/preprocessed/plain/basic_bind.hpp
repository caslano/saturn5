
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

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg< bind< F,T1,T2,T3,T4,T5 >, U1, U2, U3, U4, U5 >
{
    typedef bind< F,T1,T2,T3,T4,T5 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
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
      typename F
    >
struct bind< F,na,na,na,na,na >
    : bind0<F>
{
};

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
      typename F, typename T1
    >
struct bind< F,T1,na,na,na,na >
    : bind1< F,T1 >
{
};

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
      typename F, typename T1, typename T2
    >
struct bind< F,T1,T2,na,na,na >
    : bind2< F,T1,T2 >
{
};

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
      typename F, typename T1, typename T2, typename T3
    >
struct bind< F,T1,T2,T3,na,na >
    : bind3< F,T1,T2,T3 >
{
};

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
    >
struct bind< F,T1,T2,T3,T4,na >
    : bind4< F,T1,T2,T3,T4 >
{
};

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

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind
    : bind5< F,T1,T2,T3,T4,T5 >
{
};

/// if_/eval_if specializations
template< template< typename T1, typename T2, typename T3 > class F, typename Tag >
struct quote3;

template< typename T1, typename T2, typename T3 > struct if_;

template<
      typename Tag, typename T1, typename T2, typename T3
    >
struct bind3<
      quote3< if_,Tag >
    , T1, T2, T3
    >
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef mpl::arg<1> n1;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef typename if_<
              typename t1::type
            , t2, t3
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

template<
      template< typename T1, typename T2, typename T3 > class F, typename Tag
    >
struct quote3;

template< typename T1, typename T2, typename T3 > struct eval_if;

template<
      typename Tag, typename T1, typename T2, typename T3
    >
struct bind3<
      quote3< eval_if,Tag >
    , T1, T2, T3
    >
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef mpl::arg<1> n1;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef typename eval_if<
              typename t1::type
            , t2, t3
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

}}


/* basic_bind.hpp
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
*/