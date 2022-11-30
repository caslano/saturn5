
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bind.hpp" header
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
      typename T
    , typename Arg
    >
struct replace_unnamed_arg
{
    typedef Arg next;
    typedef T type;
};

template<
      typename Arg
    >
struct replace_unnamed_arg< arg< -1 >, Arg >
{
    typedef typename Arg::next next;
    typedef Arg type;
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
        typedef aux::replace_unnamed_arg< T4,n4 > r4;
        typedef typename r4::type a4;
        typedef typename r4::next n5;
        typedef aux::resolve_bind_arg< a4,U1,U2,U3,U4,U5 > t4;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
        typedef aux::replace_unnamed_arg< T4,n4 > r4;
        typedef typename r4::type a4;
        typedef typename r4::next n5;
        typedef aux::resolve_bind_arg< a4,U1,U2,U3,U4,U5 > t4;
        ///
        typedef aux::replace_unnamed_arg< T5,n5 > r5;
        typedef typename r5::type a5;
        typedef typename r5::next n6;
        typedef aux::resolve_bind_arg< a5,U1,U2,U3,U4,U5 > t5;
        ///
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
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
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
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
        typedef typename eval_if<
              typename t1::type
            , t2, t3
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

}}


/* bind.hpp
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
*/