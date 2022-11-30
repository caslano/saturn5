/*=============================================================================
    Copyright (c) 2005-2006 Joao Abecasis
    Copyright (c) 2006-2007 Tobias Schwinger

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_INVOCATION_INVOKE_PROCEDURE_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/core/enable_if.hpp>

#include <boost/mpl/front.hpp>

#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/functional/invocation/limits.hpp>
#include <boost/fusion/functional/invocation/detail/that_ptr.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        namespace ft = function_types;

        template<
            typename Function, class Sequence,
            int N = result_of::size<Sequence>::value,
            bool MFP = ft::is_member_function_pointer<Function>::value,
            bool RandomAccess = traits::is_random_access<Sequence>::value
            >
        struct invoke_procedure_impl;

        #define  BOOST_PP_FILENAME_1 \
            <boost/fusion/functional/invocation/invoke_procedure.hpp>
        #define  BOOST_PP_ITERATION_LIMITS \
            (0, BOOST_FUSION_INVOKE_PROCEDURE_MAX_ARITY)
        #include BOOST_PP_ITERATE()

    }

    namespace result_of
    {
        template <typename Function, class Sequence, class Enable = void>
        struct invoke_procedure;

        template <typename Function, class Sequence>
        struct invoke_procedure<Function, Sequence,
            typename enable_if_has_type<
                typename detail::invoke_procedure_impl<
                    typename boost::remove_reference<Function>::type,Sequence
                >::result_type
            >::type>
        {
            typedef void type;
        };
    }

    template <typename Function, class Sequence>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::invoke_procedure<Function, Sequence>::type
    invoke_procedure(Function f, Sequence & s)
    {
        detail::invoke_procedure_impl<
                typename boost::remove_reference<Function>::type,Sequence
            >::call(f,s);
    }

    template <typename Function, class Sequence>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::invoke_procedure<Function, Sequence const>::type
    invoke_procedure(Function f, Sequence const & s)
    {
        detail::invoke_procedure_impl<
                typename boost::remove_reference<Function>::type,Sequence const
            >::call(f,s);
    }

}}

#define BOOST_FUSION_FUNCTIONAL_INVOCATION_INVOKE_PROCEDURE_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

#define M(z,j,data) fusion::at_c<j>(s)

        template <typename Function, class Sequence>
        struct invoke_procedure_impl<Function,Sequence,N,false,true>
        {
            typedef void result_type;

#if N > 0

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline void call(Function & f, Sequence & s)
            {
                f(BOOST_PP_ENUM(N,M,~));
            }

#else

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline void call(Function & f, Sequence & /*s*/)
            {
                f();
            }

#endif

        };

#if N > 0
        template <typename Function, class Sequence>
        struct invoke_procedure_impl<Function,Sequence,N,true,true>
        {
            typedef void result_type;

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline void call(Function & f, Sequence & s)
            {
                (that_ptr<typename mpl::front<
                                ft::parameter_types<Function> >::type
                    >::get(fusion::at_c<0>(s))->*f)(BOOST_PP_ENUM_SHIFTED(N,M,~));
            }
        };
#endif

#undef M

#define M(z,j,data)                                                             \
            typedef typename result_of::next< BOOST_PP_CAT(I,BOOST_PP_DEC(j))  \
                >::type I ## j ;                                               \
            I##j i##j = fusion::next(BOOST_PP_CAT(i,BOOST_PP_DEC(j)));

        template <typename Function, class Sequence>
        struct invoke_procedure_impl<Function,Sequence,N,false,false>
        {
            typedef void result_type;

#if N > 0

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline void call(Function & f, Sequence & s)
            {
                typedef typename result_of::begin<Sequence>::type I0;
                I0 i0 = fusion::begin(s);
                BOOST_PP_REPEAT_FROM_TO(1,N,M,~)
                f( BOOST_PP_ENUM_PARAMS(N,*i) );
            }

#else
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline void call(Function & f, Sequence & /*s*/)
            {
                f();
            }

#endif

        };

#if N > 0
        template <typename Function, class Sequence>
        struct invoke_procedure_impl<Function,Sequence,N,true,false>
        {
            typedef void result_type;

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline void call(Function & f, Sequence & s)
            {
                typedef typename result_of::begin<Sequence>::type I0;
                I0 i0 = fusion::begin(s);
                BOOST_PP_REPEAT_FROM_TO(1,N,M,~)

                (that_ptr<typename mpl::front<
                                ft::parameter_types<Function> >::type
                    >::get(*i0)->*f)(BOOST_PP_ENUM_SHIFTED_PARAMS(N,*i));
            }
        };
#endif

#undef M

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif


/* invoke_procedure.hpp
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
*/