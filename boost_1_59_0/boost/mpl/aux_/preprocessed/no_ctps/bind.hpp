
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


/* bind.hpp
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
*/