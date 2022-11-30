
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