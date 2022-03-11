
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