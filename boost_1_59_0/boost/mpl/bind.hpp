
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
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
*/