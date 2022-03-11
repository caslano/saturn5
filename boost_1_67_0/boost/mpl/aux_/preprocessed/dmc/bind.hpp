
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
      typename F, int dummy_
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
      typename F, int dummy_
    >
struct bind< F,na,na,na,na,na >
    : bind0<F>
{
};

template<
      typename F, typename T1, int dummy_
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
      typename F, typename T1, int dummy_
    >
struct bind< F,T1,na,na,na,na >
    : bind1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2, int dummy_
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
      typename F, typename T1, typename T2, int dummy_
    >
struct bind< F,T1,T2,na,na,na >
    : bind2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, int dummy_
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
      typename F, typename T1, typename T2, typename T3, int dummy_
    >
struct bind< F,T1,T2,T3,na,na >
    : bind3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , int dummy_
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
    , int dummy_
    >
struct bind< F,T1,T2,T3,T4,na >
    : bind4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, int dummy_
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
    , typename T5, int dummy_
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

}}


/* bind.hpp
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
*/