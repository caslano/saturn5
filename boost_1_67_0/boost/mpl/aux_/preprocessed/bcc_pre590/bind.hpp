
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bind.hpp" header
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

} // namespace aux

template<
      typename F
    >
struct bind0
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
      typename F, typename T1
    >
struct bind1
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
      typename F, typename T1, typename T2
    >
struct bind2
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
      typename F, typename T1, typename T2, typename T3
    >
struct bind3
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct bind4
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
    , typename T5
    >
struct bind5
{
    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
}}


/* bind.hpp
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
*/