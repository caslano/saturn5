
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