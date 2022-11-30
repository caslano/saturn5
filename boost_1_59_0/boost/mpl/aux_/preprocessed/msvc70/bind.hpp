
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