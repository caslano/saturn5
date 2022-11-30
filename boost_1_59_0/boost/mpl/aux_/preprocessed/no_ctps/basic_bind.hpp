
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
template< bool >
struct resolve_arg_impl
{
    template<
          typename T, typename U1, typename U2, typename U3
        , typename U4, typename U5
        >
    struct result_
    {
        typedef T type;
    };
};

template<>
struct resolve_arg_impl<true>
{
    template<
          typename T, typename U1, typename U2, typename U3
        , typename U4, typename U5
        >
    struct result_
    {
        typedef typename apply_wrap5<
              T
            , U1, U2, U3, U4, U5
            >::type type;
    };
};

template< typename T > struct is_bind_template;

template<
      typename T, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg
    : resolve_arg_impl< is_bind_template<T>::value >
            ::template result_< T,U1,U2,U3,U4,U5 >
{
};

template< int arity_ > struct bind_chooser;

aux::no_tag is_bind_helper(...);
template< typename T > aux::no_tag is_bind_helper(protect<T>*);

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
aux::yes_tag is_bind_helper(bind< F,T1,T2,T3,T4,T5 >*);

template< int N >
aux::yes_tag is_bind_helper(arg<N>*);

template< bool is_ref_  = true >
struct is_bind_template_impl
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value  = false);
    };
};

template<>
struct is_bind_template_impl<false>
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value =
              sizeof(aux::is_bind_helper(static_cast<T*>(0)))
                == sizeof(aux::yes_tag)
            );
    };
};

template< typename T > struct is_bind_template
    : is_bind_template_impl< ::boost::detail::is_reference_impl<T>::value >
        ::template result_<T>
{
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
      typename F
    >
aux::yes_tag
is_bind_helper(bind0<F>*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(1, bind0)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(1, bind0)

namespace aux {

template<>
struct bind_chooser<0>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind0<F> type;
    };
};

} // namespace aux

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
      typename F, typename T1
    >
aux::yes_tag
is_bind_helper(bind1< F,T1 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(2, bind1)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(2, bind1)

namespace aux {

template<>
struct bind_chooser<1>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind1< F,T1 > type;
    };
};

} // namespace aux

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
      typename F, typename T1, typename T2
    >
aux::yes_tag
is_bind_helper(bind2< F,T1,T2 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(3, bind2)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(3, bind2)

namespace aux {

template<>
struct bind_chooser<2>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind2< F,T1,T2 > type;
    };
};

} // namespace aux

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
      typename F, typename T1, typename T2, typename T3
    >
aux::yes_tag
is_bind_helper(bind3< F,T1,T2,T3 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(4, bind3)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(4, bind3)

namespace aux {

template<>
struct bind_chooser<3>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind3< F,T1,T2,T3 > type;
    };
};

} // namespace aux

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
    >
aux::yes_tag
is_bind_helper(bind4< F,T1,T2,T3,T4 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(5, bind4)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(5, bind4)

namespace aux {

template<>
struct bind_chooser<4>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind4< F,T1,T2,T3,T4 > type;
    };
};

} // namespace aux

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
    , typename T5
    >
aux::yes_tag
is_bind_helper(bind5< F,T1,T2,T3,T4,T5 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)

namespace aux {

template<>
struct bind_chooser<5>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind5< F,T1,T2,T3,T4,T5 > type;
    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_bind_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_bind_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    >
struct bind_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_bind_arg<T1>::value + is_bind_arg<T2>::value 
        + is_bind_arg<T3>::value + is_bind_arg<T4>::value 
        + is_bind_arg<T5>::value
        );

};

}

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind
    : aux::bind_chooser<
          aux::bind_count_args< T1,T2,T3,T4,T5 >::value
        >::template result_< F,T1,T2,T3,T4,T5 >::type
{
};

BOOST_MPL_AUX_ARITY_SPEC(
      6
    , bind
    )

BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(
      6
    , bind
    )
}}


/* basic_bind.hpp
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
*/