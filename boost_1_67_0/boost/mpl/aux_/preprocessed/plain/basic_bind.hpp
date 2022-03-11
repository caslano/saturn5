
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