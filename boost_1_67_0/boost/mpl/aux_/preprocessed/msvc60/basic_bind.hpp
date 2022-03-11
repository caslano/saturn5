
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