
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "basic_bind.hpp" header
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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