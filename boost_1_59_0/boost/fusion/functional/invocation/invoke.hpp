/*=============================================================================
    Copyright (c) 2005-2006 Joao Abecasis
    Copyright (c) 2006-2007 Tobias Schwinger

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_INVOCATION_INVOKE_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/function_types/is_function.hpp>
#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/is_member_pointer.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>

#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
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
            bool CBI = ft::is_callable_builtin<Function>::value,
            bool RandomAccess = traits::is_random_access<Sequence>::value,
            typename Enable = void
            >
        struct invoke_impl;

        template <class Sequence, int N>
        struct invoke_param_types;

        template <typename T, class Sequence>
        struct invoke_data_member;

        template <typename Function, class Sequence, int N, bool RandomAccess>
        struct invoke_fn_ptr;

        template <typename Function, class Sequence, int N, bool RandomAccess>
        struct invoke_mem_fn;

        #define  BOOST_PP_FILENAME_1 <boost/fusion/functional/invocation/invoke.hpp>
        #define  BOOST_PP_ITERATION_LIMITS (0, BOOST_FUSION_INVOKE_MAX_ARITY)
        #include BOOST_PP_ITERATE()

        template <typename F, class Sequence, int N, bool RandomAccess>
        struct invoke_nonmember_builtin
        // use same implementation as for function objects but...
            : invoke_fn_ptr< // ...work around boost::result_of bugs
                typename mpl::eval_if< ft::is_function<F>,
                    boost::add_reference<F>, boost::remove_cv<F> >::type,
                Sequence, N, RandomAccess >
        { };

        template <typename Function, class Sequence, int N, bool RandomAccess, typename Enable>
        struct invoke_impl<Function,Sequence,N,true,RandomAccess,Enable>
            : mpl::if_< ft::is_member_function_pointer<Function>,
                invoke_mem_fn<Function,Sequence,N,RandomAccess>,
                invoke_nonmember_builtin<Function,Sequence,N,RandomAccess>
            >::type
        { };

        template <typename Function, class Sequence, bool RandomAccess, typename Enable>
        struct invoke_impl<Function,Sequence,1,true,RandomAccess,Enable>
            : mpl::eval_if< ft::is_member_pointer<Function>,
                mpl::if_< ft::is_member_function_pointer<Function>,
                    invoke_mem_fn<Function,Sequence,1,RandomAccess>,
                    invoke_data_member<Function, Sequence> >,
                mpl::identity< invoke_nonmember_builtin<
                    Function,Sequence,1,RandomAccess> >
            >::type
        { };

        template <typename T, class C, class Sequence>
        struct invoke_data_member< T C::*, Sequence >
        {
        private:

            typedef typename result_of::front<Sequence>::type that;

            typedef mpl::or_< boost::is_convertible<that,C*>,
                              boost::is_convertible<that,C&>,
                              non_const_pointee<that> > non_const_cond;

            typedef typename mpl::eval_if< non_const_cond,
                mpl::identity<C>, add_const<C> >::type qualified_class;

            typedef typename mpl::eval_if< non_const_cond,
                mpl::identity<T>, add_const<T> >::type qualified_type;

        public:

            typedef typename boost::add_reference<qualified_type>::type
                result_type;

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type call(T C::* f, Sequence & s)
            {
                typename result_of::front<Sequence>::type c = fusion::front(s);
                return that_ptr<qualified_class>::get(c)->*f;
            }
        };
    }

    namespace result_of
    {
        template <typename Function, class Sequence, typename = void>
        struct invoke;

        template <typename Function, class Sequence>
        struct invoke<Function, Sequence,
                      typename enable_if_has_type<
                          typename detail::invoke_impl<
                              typename boost::remove_reference<Function>::type, Sequence
                          >::result_type
                      >::type>
        {
            typedef typename detail::invoke_impl<
                typename boost::remove_reference<Function>::type, Sequence
            >::result_type type;
        };
    }

    template <typename Function, class Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::invoke<Function,Sequence>::type
    invoke(Function f, Sequence & s)
    {
        return detail::invoke_impl<
                typename boost::remove_reference<Function>::type,Sequence
            >::call(f,s);
    }

    template <typename Function, class Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::invoke<Function,Sequence const>::type
    invoke(Function f, Sequence const & s)
    {
        return detail::invoke_impl<
                typename boost::remove_reference<Function>::type,Sequence const
            >::call(f,s);
    }

}}

#define BOOST_FUSION_FUNCTIONAL_INVOCATION_INVOKE_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

#define M(z,j,data) typename result_of::at_c<Sequence,j>::type

        template <typename Function, class Sequence>
        struct invoke_impl<Function,Sequence,N,false,true,
            typename enable_if_has_type<
                typename boost::result_of<Function(BOOST_PP_ENUM(N,M,~)) >::type
              >::type>
        {
        public:

            typedef typename boost::result_of<
                    Function(BOOST_PP_ENUM(N,M,~)) >::type result_type;
#undef M

#if N > 0

            template <typename F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & s)
            {
#define M(z,j,data) fusion::at_c<j>(s)
                return f( BOOST_PP_ENUM(N,M,~) );
            }

#else
            template <typename F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & /*s*/)
            {
                return f();
            }

#endif

        };

        template <typename Function, class Sequence>
        struct invoke_fn_ptr<Function,Sequence,N,true>
        {
        public:

            typedef typename ft::result_type<Function>::type result_type;

#if N > 0

            template <typename F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & s)
            {
#define M(z,j,data) fusion::at_c<j>(s)
                return f( BOOST_PP_ENUM(N,M,~) );
            }

#else
            template <typename F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & /*s*/)
            {
                return f();
            }

#endif

        };


#if N > 0
        template <typename Function, class Sequence>
        struct invoke_mem_fn<Function,Sequence,N,true>
        {
        public:

            typedef typename ft::result_type<Function>::type result_type;

            template <typename F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & s)
            {
                return (that_ptr<typename mpl::front<
                                ft::parameter_types<Function> >::type
                    >::get(fusion::at_c<0>(s))->*f)(BOOST_PP_ENUM_SHIFTED(N,M,~));
            }
        };
#endif

#undef M

#define M(z,j,data)                                                             \
            typename seq::I##j i##j =                                          \
                fusion::next(BOOST_PP_CAT(i,BOOST_PP_DEC(j)));

        template <typename Function, class Sequence>
        struct invoke_impl<Function,Sequence,N,false,false,
            typename enable_if_has_type<
#define L(z,j,data) typename invoke_param_types<Sequence,N>::BOOST_PP_CAT(T, j)
                typename boost::result_of<Function(BOOST_PP_ENUM(N,L,~))>::type
              >::type>
#undef L
        {
        private:
            typedef invoke_param_types<Sequence,N> seq;
        public:

            typedef typename boost::result_of<
                Function(BOOST_PP_ENUM_PARAMS(N,typename seq::T))
                >::type result_type;

#if N > 0

            template <typename F>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & s)
            {
                typename seq::I0 i0 = fusion::begin(s);
                BOOST_PP_REPEAT_FROM_TO(1,N,M,~)
                return f( BOOST_PP_ENUM_PARAMS(N,*i) );
            }

#else

            template <typename F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & /*s*/)
            {
                return f();
            }

#endif

        };

        template <typename Function, class Sequence>
        struct invoke_fn_ptr<Function,Sequence,N,false>
        {
        private:
            typedef invoke_param_types<Sequence,N> seq;
        public:

            typedef typename ft::result_type<Function>::type result_type;

#if N > 0

            template <typename F>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & s)
            {
                typename seq::I0 i0 = fusion::begin(s);
                BOOST_PP_REPEAT_FROM_TO(1,N,M,~)
                return f( BOOST_PP_ENUM_PARAMS(N,*i) );
            }

#else

            template <typename F>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & /*s*/)
            {
                return f();
            }

#endif

        };

#if N > 0
        template <typename Function, class Sequence>
        struct invoke_mem_fn<Function,Sequence,N,false>
        {
        private:
            typedef invoke_param_types<Sequence,N> seq;
        public:

            typedef typename ft::result_type<Function>::type result_type;

            template <typename F>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static inline result_type
            call(F & f, Sequence & s)
            {
                typename seq::I0 i0 = fusion::begin(s);
                BOOST_PP_REPEAT_FROM_TO(1,N,M,~)

                return (that_ptr< typename mpl::front<
                                      ft::parameter_types<Function> >::type
                    >::get(*i0)->*f)(BOOST_PP_ENUM_SHIFTED_PARAMS(N,*i));
            }
        };
#endif

#undef M

        template <class Sequence> struct invoke_param_types<Sequence,N>
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


/* invoke.hpp
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
*/