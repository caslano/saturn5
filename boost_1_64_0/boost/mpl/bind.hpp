
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_BIND_HPP_INCLUDED
#define BOOST_MPL_BIND_HPP_INCLUDED

// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/bind_fwd.hpp>
#   include <boost/mpl/placeholders.hpp>
#   include <boost/mpl/next.hpp>
#   include <boost/mpl/protect.hpp>
#   include <boost/mpl/apply_wrap.hpp>
#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/arity_spec.hpp>
#   include <boost/mpl/aux_/type_wrapper.hpp>
#   include <boost/mpl/aux_/yes_no.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/type_traits/is_reference.hpp>
#   endif 
#endif

#include <boost/mpl/aux_/config/bind.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   if defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)
#       define BOOST_MPL_PREPROCESSED_HEADER basic_bind.hpp
#   else
#       define BOOST_MPL_PREPROCESSED_HEADER bind.hpp
#   endif
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/def_params_tail.hpp>
#   include <boost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <boost/mpl/aux_/preprocessor/ext_params.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/add.hpp>
#   include <boost/mpl/aux_/config/dmc_ambiguous_ctps.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/ttp.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/inc.hpp>

namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_APPLY \
    BOOST_PP_CAT(apply_wrap,BOOST_MPL_LIMIT_METAFUNCTION_ARITY) \
    /**/

#   if defined(BOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)
#       define AUX778076_DMC_PARAM() , int dummy_
#   else
#       define AUX778076_DMC_PARAM()
#   endif

#   define AUX778076_BIND_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_BIND_N_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_BIND_N_SPEC_PARAMS(n, param, def) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
    /**/

#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define AUX778076_BIND_NESTED_DEFAULT_PARAMS(param, value) \
    AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    /**/
#else
#   define AUX778076_BIND_NESTED_DEFAULT_PARAMS(param, value) \
    AUX778076_BIND_PARAMS(param) \
    /**/
#endif

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename T, AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg
{
    typedef T type;
};

#   if !defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

template<
      typename T
    , typename Arg
    >
struct replace_unnamed_arg
{
    typedef Arg next;
    typedef T type;
};

template<
      typename Arg
    >
struct replace_unnamed_arg< arg<-1>,Arg >
{
    typedef typename Arg::next next;
    typedef Arg type;
};

#   endif // BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

template<
      BOOST_MPL_AUX_NTTP_DECL(int, N), AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg< arg<N>,AUX778076_BIND_PARAMS(U) >
{
    typedef typename AUX778076_APPLY<mpl::arg<N>, AUX778076_BIND_PARAMS(U)>::type type;
};

#if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, AUX778076_BIND_PARAMS(typename T), AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg< bind<F,AUX778076_BIND_PARAMS(T)>,AUX778076_BIND_PARAMS(U) >
{
    typedef bind<F,AUX778076_BIND_PARAMS(T)> f_;
    typedef typename AUX778076_APPLY<f_, AUX778076_BIND_PARAMS(U)>::type type;
};
#endif

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// agurt, 15/jan/02: it's not a intended to be used as a function class, and 
// MSVC6.5 has problems with 'apply' name here (the code compiles, but doesn't
// work), so I went with the 'result_' here, and in all other similar cases
template< bool >
struct resolve_arg_impl
{
    template< typename T, AUX778076_BIND_PARAMS(typename U) > struct result_
    {
        typedef T type;
    };
};

template<> 
struct resolve_arg_impl<true>
{
    template< typename T, AUX778076_BIND_PARAMS(typename U) > struct result_
    {
        typedef typename AUX778076_APPLY<
              T
            , AUX778076_BIND_PARAMS(U)
            >::type type;
    };
};

// for 'resolve_bind_arg'
template< typename T > struct is_bind_template;

template< 
      typename T, AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg
    : resolve_arg_impl< is_bind_template<T>::value >
            ::template result_< T,AUX778076_BIND_PARAMS(U) >
{
};

#   if !defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

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
struct replace_unnamed_arg_impl< arg<-1> >
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

#   endif // BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

// agurt, 10/mar/02: the forward declaration has to appear before any of
// 'is_bind_helper' overloads, otherwise MSVC6.5 issues an ICE on it
template< BOOST_MPL_AUX_NTTP_DECL(int, arity_) > struct bind_chooser;

aux::no_tag is_bind_helper(...);
template< typename T > aux::no_tag is_bind_helper(protect<T>*);

// overload for "main" form
// agurt, 15/mar/02: MSVC 6.5 fails to properly resolve the overload 
// in case if we use 'aux::type_wrapper< bind<...> >' here, and all 
// 'bind' instantiations form a complete type anyway
#if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, AUX778076_BIND_PARAMS(typename T)
    >
aux::yes_tag is_bind_helper(bind<F,AUX778076_BIND_PARAMS(T)>*);
#endif

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
aux::yes_tag is_bind_helper(arg<N>*);

template< bool is_ref_ = true >
struct is_bind_template_impl
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value = false);
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

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/bind.hpp>))
#include BOOST_PP_ITERATE()

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS)
/// if_/eval_if specializations
#   define AUX778076_SPEC_NAME if_
#   define BOOST_PP_ITERATION_PARAMS_1 (3,(3, 3, <boost/mpl/bind.hpp>))
#   include BOOST_PP_ITERATE()

#if !defined(BOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)
#   define AUX778076_SPEC_NAME eval_if
#   define BOOST_PP_ITERATION_PARAMS_1 (3,(3, 3, <boost/mpl/bind.hpp>))
#   include BOOST_PP_ITERATE()
#endif
#endif

// real C++ version is already taken care of
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)

namespace aux {
// apply_count_args
#define AUX778076_COUNT_ARGS_PREFIX bind
#define AUX778076_COUNT_ARGS_DEFAULT na
#define AUX778076_COUNT_ARGS_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#include <boost/mpl/aux_/count_args.hpp>
}

// bind
template<
      typename F, AUX778076_BIND_PARAMS(typename T) AUX778076_DMC_PARAM()
    >
struct bind
    : aux::bind_chooser<
          aux::bind_count_args<AUX778076_BIND_PARAMS(T)>::value
        >::template result_< F,AUX778076_BIND_PARAMS(T) >::type
{
};

BOOST_MPL_AUX_ARITY_SPEC(
      BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)
    , bind
    )

BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(
      BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)
    , bind
    )


#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef AUX778076_BIND_NESTED_DEFAULT_PARAMS
#   undef AUX778076_BIND_N_SPEC_PARAMS
#   undef AUX778076_BIND_N_PARAMS
#   undef AUX778076_BIND_DEFAULT_PARAMS
#   undef AUX778076_BIND_PARAMS
#   undef AUX778076_DMC_PARAM
#   undef AUX778076_APPLY

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_BIND_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

#if defined(AUX778076_SPEC_NAME)

// lazy metafunction specialization
template< template< BOOST_MPL_PP_PARAMS(i_, typename T) > class F, typename Tag >
struct BOOST_PP_CAT(quote,i_);

template< BOOST_MPL_PP_PARAMS(i_, typename T) > struct AUX778076_SPEC_NAME;

template<
      typename Tag AUX778076_BIND_N_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(bind,i_)< 
      BOOST_PP_CAT(quote,i_)<AUX778076_SPEC_NAME,Tag>
    AUX778076_BIND_N_PARAMS(i_,T)
    >
{
    template<
          AUX778076_BIND_NESTED_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
     private:
        typedef mpl::arg<1> n1;
#       define BOOST_PP_ITERATION_PARAMS_2 (3,(1, i_, <boost/mpl/bind.hpp>))
#       include BOOST_PP_ITERATE()

        typedef typename AUX778076_SPEC_NAME<
              typename t1::type
            , BOOST_MPL_PP_EXT_PARAMS(2, BOOST_PP_INC(i_), t)
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

#undef AUX778076_SPEC_NAME

#else // AUX778076_SPEC_NAME

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T) AUX778076_DMC_PARAM()
    >
struct BOOST_PP_CAT(bind,i_)
{
    template<
          AUX778076_BIND_NESTED_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
     private:
#   if !defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

        typedef aux::replace_unnamed_arg< F,mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg<a0,AUX778076_BIND_PARAMS(U)>::type f_;
        ///
#   else
        typedef typename aux::resolve_bind_arg<F,AUX778076_BIND_PARAMS(U)>::type f_;

#   endif // BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#   if i_ > 0
#       define BOOST_PP_ITERATION_PARAMS_2 (3,(1, i_, <boost/mpl/bind.hpp>))
#       include BOOST_PP_ITERATE()
#   endif

     public:

#   define AUX778076_ARG(unused, i_, t) \
    BOOST_PP_COMMA_IF(i_) \
    typename BOOST_PP_CAT(t,BOOST_PP_INC(i_))::type \
/**/

        typedef typename BOOST_PP_CAT(apply_wrap,i_)<
              f_ 
            BOOST_PP_COMMA_IF(i_) BOOST_MPL_PP_REPEAT(i_, AUX778076_ARG, t)
            >::type type;

#   undef AUX778076_ARG
    };
};

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T), AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg<
      BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T)>,AUX778076_BIND_PARAMS(U)
    >
{
    typedef BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T)> f_;
    typedef typename AUX778076_APPLY<f_, AUX778076_BIND_PARAMS(U)>::type type;
};

#else

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    >
aux::yes_tag
is_bind_helper(BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T)>*);

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(BOOST_PP_INC(i_), BOOST_PP_CAT(bind,i_))
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(BOOST_PP_INC(i_), BOOST_PP_CAT(bind,i_))

#   if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    
#if i_ == BOOST_MPL_LIMIT_METAFUNCTION_ARITY
/// primary template (not a specialization!)
template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T) AUX778076_DMC_PARAM()
    >
struct bind
    : BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T) >
{
};
#else
template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T) AUX778076_DMC_PARAM()
    >
struct bind< F AUX778076_BIND_N_SPEC_PARAMS(i_, T, na) >
    : BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T) >
{
};
#endif

#   else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace aux {

template<>
struct bind_chooser<i_>
{
    template<
          typename F, AUX778076_BIND_PARAMS(typename T)
        >
    struct result_
    {
        typedef BOOST_PP_CAT(bind,i_)< F AUX778076_BIND_N_PARAMS(i_,T) > type;
    };
};

} // namespace aux

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // BOOST_MPL_CFG_NO_BIND_TEMPLATE

#endif // AUX778076_SPEC_NAME

#   undef i_

///// iteration, depth == 2

#elif BOOST_PP_ITERATION_DEPTH() == 2

#   define j_ BOOST_PP_FRAME_ITERATION(2)
#   if !defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

        typedef aux::replace_unnamed_arg< BOOST_PP_CAT(T,j_),BOOST_PP_CAT(n,j_) > BOOST_PP_CAT(r,j_);
        typedef typename BOOST_PP_CAT(r,j_)::type BOOST_PP_CAT(a,j_);
        typedef typename BOOST_PP_CAT(r,j_)::next BOOST_PP_CAT(n,BOOST_PP_INC(j_));
        typedef aux::resolve_bind_arg<BOOST_PP_CAT(a,j_), AUX778076_BIND_PARAMS(U)> BOOST_PP_CAT(t,j_);
        ///
#   else
        typedef aux::resolve_bind_arg< BOOST_PP_CAT(T,j_),AUX778076_BIND_PARAMS(U)> BOOST_PP_CAT(t,j_);

#   endif
#   undef j_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* bind.hpp
+JQyPhd78LmG+V8r+ERdfJCv3T7xKT1gfHz6Ywj8j8TXdWlyEpk3s8/MbHBfs+m1ESJlFlwhWtCgc3ApexXuh2nyDXb72FcZ+Zy2sENXnruc8DGR844KupL2tUSMz/6ikvadrs1rAJO3vztdkfM3mjNeZh3rygD2S0G/Xmsd53zMR8HbnIIjidujilhHz/mnAcyVsTNsDdOiWAHi2PQOHcAKsF96mAaOYTxv8TRwHuH5YX3L/Pw2lx8h34v1beXnY74sP5/Azr/VHn6+3uh/qFqjiPlY0qsulpq7h4PozH0wzgkaZCQNPVSY7Q6263+pDr49rTcc+Jcq/Gc+2vNl3ODa1v6e1pOe/pnL/E+rQ8RmXxc97TYeWXs7mF3Y1pYP97V8wbPa8hzrebflAP7ih19Ts932juTxeIOnvfNZ/v+wZX6/0G0s8g1Fvpb4/cgD5vdG/yOh2mB2DffEHM/KuFj6ftMHWmm0lVhFodlDYMYKV6YtkbspwjRMr3eZsYKa44DqGd/QSldd01x94KdqffadvuSqNIVZK/o5Qda1u8A8nxM/mrzOKDWneB/DZi7jktMGTNzzX5+Cnp7Nv2A8CwaA84vsvz7r7o5hNxCtbAWe10qbpWaKwbJJi1Itx3+l+u2azXBodv0TsE+4SvYloNTD/AAmHoyfBTsm9r6mYu9rKqeOwXok1SqE+wPq+9NdbRpnhxNsGs4uDcT9rb/a86WCwLr3f38i61lpjlgMvKc+smmNlF33/Z7td9brQsDDzg/up1SgjTjPLkD/8BGAsoIyLx23odEjn2f/ljWtjx4lCWxr6SiJ+l+XjlV/7iZzLXkajQfxvyrlJY83vp5+SSzcb0UvBmApQofi3gRo3WycnSnG2UuQCTxrA3J8BY9Rd/6TxG1mtXMh7T08WYehtmiuvQO2CWfR7xEdIV/yrc0yqe+uw6Rm+/Jl4pSGq3soCAePSNinQ2mOfRrec8Hdxl8tB/5qOXSNTrQgAexEARsdj3Ts9r3wxtclJbjtJwkaM21aOtmFC6Fwlx74TgfDW4n5/zHTc6nsd66U/x7wRVez5b/l8t+d8t9ars6NU+87wLBB/tuK/xKOOmzGf4vOJ0dnfhKbH6Jp9LJ+QglEO/Dfp4Wmn7yn6+q1IeMj1J3l0zLHXmGnwEyQUTeVMrTC7iOz4V1Yku2ye6ruweTqbnaq6xgiMOvZ27esqz1qI7OnpZUFS2MFuUhLr/trR8Ena2GWBoi/W09crKwoX8nxvn7h1DBLazhSaqh7kooLlxWfI4LzuBzgoQuB6OU+euFVwZXNG2iqVYZYflspckDqK8aBp+x6KobbfXbCt+nZXWKd+O2nZTsRPtDm7yV2XnHGnA7kOsQ3SBTaDHFiqKIuAEHhd7WxguUAk5H1aMlyyjW8KELnn37nNGGcNuHCP0sTPu7AdiP39paAdLDs7ERSOSDwNuttlAev2EZ3YZM/XIOZnbusd5xvBds21QbJIK3f6q13nW+F26oiVUyFKXZMvzdaf0ose7l+242Is4e4l1A3bkkLC7vYRel8GKY0hDztTITm3U4b87WN8/4kbczqwG3a6DmmY7hjANwxklqyeXhJU1bFbGq1GWqHYajl0FCjyxfUrWxxPAum5t5OQmXJ4ljJmgXla6rpvuWrQlsWldKUaMcVzKHE3FRJvIYS0zmxhBIHBCRxLiWmceLxFeVrxl9Fk/+GVH7NodcIvy4MghfQg5xqWBgruKGy8IZYFZesvJX/jd16DT+jghjqBtq7KvEc43mC19ASd4SkFmyMFWzEh8Yt45YwCtroTk6jY4uuJABMpXCsih+hV9VzQDw8EUh6upW/TLGX7EKnCUiuVK4=
*/