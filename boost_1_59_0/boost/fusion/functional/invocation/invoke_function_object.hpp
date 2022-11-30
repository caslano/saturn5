/*=============================================================================
    Copyright (c) 2005-2006 Joao Abecasis
    Copyright (c) 2006-2007 Tobias Schwinger

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_INVOCATION_INVOKE_FUNCTION_OBJECT_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/functional/invocation/limits.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        template<
            class Function, class Sequence,
            int N = result_of::size<Sequence>::value,
            bool RandomAccess = traits::is_random_access<Sequence>::value,
            typename Enable = void
            >
        struct invoke_function_object_impl;

        template <class Sequence, int N>
        struct invoke_function_object_param_types;

        #define  BOOST_PP_FILENAME_1 \
            <boost/fusion/functional/invocation/invoke_function_object.hpp>
        #define  BOOST_PP_ITERATION_LIMITS \
            (0, BOOST_FUSION_INVOKE_FUNCTION_OBJECT_MAX_ARITY)
        #include BOOST_PP_ITERATE()
    }

    namespace result_of
    {
        template <class Function, class Sequence, class Enable = void>
        struct invoke_function_object;

        template <class Function, class Sequence>
        struct invoke_function_object<Function, Sequence,
            typename enable_if_has_type<
                typename detail::invoke_function_object_impl<
                    typename boost::remove_reference<Function>::type, Sequence
                >::result_type
            >::type>
        {
            typedef typename detail::invoke_function_object_impl<
                typename boost::remove_reference<Function>::type, Sequence
                >::result_type type;
        };
    }

    template <class Function, class Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::invoke_function_object<Function,Sequence>::type
    invoke_function_object(Function f, Sequence & s)
    {
        return detail::invoke_function_object_impl<
                typename boost::remove_reference<Function>::type,Sequence
            >::call(f,s);
    }

    template <class Function, class Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::invoke_function_object<Function,Sequence const>::type
    invoke_function_object(Function f, Sequence const & s)
    {
        return detail::invoke_function_object_impl<
                typename boost::remove_reference<Function>::type,Sequence const
            >::call(f,s);
    }

}}

#define BOOST_FUSION_FUNCTIONAL_INVOCATION_INVOKE_FUNCTION_OBJECT_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

#define M(z,j,data)                                                             \
        typename result_of::at_c<Sequence,j>::type

        template <class Function, class Sequence>
        struct invoke_function_object_impl<Function,Sequence,N,true,
            typename enable_if_has_type<
                typename boost::result_of<Function (BOOST_PP_ENUM(N,M,~)) >::type
            >::type>
        {
        public:

            typedef typename boost::result_of<
                Function (BOOST_PP_ENUM(N,M,~)) >::type result_type;
#undef M

#if N > 0

            template <class F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & s)
            {
#define M(z,j,data) fusion::at_c<j>(s)
                return f( BOOST_PP_ENUM(N,M,~) );
#undef M
            }

#else

            template <class F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & /*s*/)
            {
                return f();
            }

#endif

        };

#define M(z,j,data)                                                             \
            typename invoke_function_object_param_types<Sequence,N>::T ## j

        template <class Function, class Sequence>
        struct invoke_function_object_impl<Function,Sequence,N,false,
            typename enable_if_has_type<
                typename boost::result_of<Function (BOOST_PP_ENUM(N,M,~)) >::type
            >::type>
#undef M
        {
        private:
            typedef invoke_function_object_param_types<Sequence,N> seq;
        public:
            typedef typename boost::result_of<
                Function (BOOST_PP_ENUM_PARAMS(N,typename seq::T))
                >::type result_type;

#if N > 0

            template <class F>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & s)
            {
                typename seq::I0 i0 = fusion::begin(s);
#define M(z,j,data)                                                             \
            typename seq::I##j i##j =                                          \
                fusion::next(BOOST_PP_CAT(i,BOOST_PP_DEC(j)));
                BOOST_PP_REPEAT_FROM_TO(1,N,M,~)
#undef M
                return f( BOOST_PP_ENUM_PARAMS(N,*i) );
            }

#else

            template <class F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & /*s*/)
            {
                return f();
            }

#endif

        };

        template <class Sequence>
        struct invoke_function_object_param_types<Sequence,N>
        {
#if N > 0
            typedef typename result_of::begin<Sequence>::type I0;
            typedef typename result_of::deref<I0>::type T0;

#define M(z,i,data)                                                             \
            typedef typename result_of::next<                                  \
                BOOST_PP_CAT(I,BOOST_PP_DEC(i))>::type I##i;                   \
            typedef typename result_of::deref<I##i>::type T##i;

            BOOST_PP_REPEAT_FROM_TO(1,N,M,~)
#undef M
#endif
        };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif


/* invoke_function_object.hpp
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
*/