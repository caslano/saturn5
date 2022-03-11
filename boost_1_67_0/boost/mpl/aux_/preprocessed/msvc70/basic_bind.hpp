
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