
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
}}


/* basic_bind.hpp
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
*/