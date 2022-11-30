
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bind.hpp" header
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

template< typename T >
struct replace_unnamed_arg_impl
{
    template< typename Arg > struct result_
    {
        typedef Arg next;
        typedef T type;
    };
};

template<>
struct replace_unnamed_arg_impl< arg< -1 > >
{
    template< typename Arg > struct result_
    {
        typedef typename next<Arg>::type next;
        typedef Arg type;
    };
};

template< typename T, typename Arg >
struct replace_unnamed_arg
    : replace_unnamed_arg_impl<T>::template result_<Arg>
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
    , typename T5
    >
aux::yes_tag
is_bind_helper(bind5< F,T1,T2,T3,T4,T5 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)
}}


/* bind.hpp
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
*/