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