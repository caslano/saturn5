
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