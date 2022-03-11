
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