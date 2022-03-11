
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