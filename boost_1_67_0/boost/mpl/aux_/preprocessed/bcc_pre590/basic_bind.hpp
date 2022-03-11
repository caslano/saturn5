
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