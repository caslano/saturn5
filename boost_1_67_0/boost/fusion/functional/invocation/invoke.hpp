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