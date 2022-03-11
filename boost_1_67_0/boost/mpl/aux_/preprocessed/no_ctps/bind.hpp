
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