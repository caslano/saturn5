
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