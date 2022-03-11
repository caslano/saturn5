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