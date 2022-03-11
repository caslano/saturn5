
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