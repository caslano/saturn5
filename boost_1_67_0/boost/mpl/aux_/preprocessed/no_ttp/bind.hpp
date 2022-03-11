
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

}}


/* bind.hpp
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
*/