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
C3n+V6LV5G6s5oRW/+pYzTEyvmb29vAu6mdv02fg7HPvxemfnVX1DOp2toNU4/PPl/oMW8mDAlnjx7qZ1IFoXt4XILfjzsl+m+RLZK7HilXa7PK+nvEVMud366VLK/Grxh1rnW38+WRpW/SljOe2H78hLp/WJvuKUfEyVmy+F9f3pOQz1Pfc8VLX96Tny34cMvKZjBebT50flEVVflzJl73+5lY+c/U35utqJhrqasyOU5xkOD6B+jHRclH34vrCuhfz9RyyfaN6G+bCi42X8a6N6ljkcwGG74dGhbBN1TkxOPPLkideJnUt/K9qbNa10ga/EcfcFSvKsbfraO7YM+ljVFw8V5BQjZT7dMy+5BtTQspBEnbOl19XDn7qqi4HKZLnnY3KQarke2cpB2n6f8eo2u13lnKQLudFZ6NykCHHqbO+HKjH4iS+UJQx+uSzckxLSz8Gu4K6OKMHh8YGJfTVqOY37CzXGGv9vw3XGJusdTLuuPSDkHXMu+ejbDJOU1Y/P6BxPN6hUUZl9oguXYGRWceyiP7z6nLjqv+s9CNhXUnDZ+W4y1yj2fatbWxoqLpfRoCNXP8LcO3DM+hBGXTwM1cmdBMJ6spC8kt+C77qYfb4G64DqvHP1ce/i8nx72Jy/Luojr/560BzM9eBJJPrgIOZMV/1/clU844MluOkuiZI/ab5utswM9eCGMPYr4MDY7QcQOknZvis1AcTr2HO18Gm8+XaySNQUaW/Bj4qoPu9opGf6TGLDQ2OkTE5X3INTze6hncPNJlvIJ/JfAMm1+97JtfvJybXbxKf7ffMDXMeWzkwMKexvb1MrrnNzeSzTw7XXG8z19x0M9dcT/U1V/8b0Vz3OSVPc7wOm63zNu0LdULG448twPHDnnL8igWbHr+48MiYCP31N/klxzDJ6Bj2CFMfwxSTY5hqcgy5D1Sfe+pjSPl4+TFU90MK+VOOX1Iujt+/cqzaSh+7jKIa3aKMxWeHSdiG+K6E6/K3UxdPbRt/H62HX/tObbQeXXx6aNv6dumk9fFt496N9u65uFYaXxuDZF6I7PNZpMm1nM8k9JV12w15G5J1PUw3k3fmxgRmX7KNCdyuvIxzS5FT3VezrZD4sMy5jyi7xciTj1g/pb+hn5iX4VoeHCx5mPX5Q3xeGUOx5gD5vGos/URnMDsGf2nV2MVD4uJjw0NCNebH3VfPDZDoBLr4SxJ3OuE1Iq4fYYjfJ3t69cFdjv2l12VMToIdYSuhPXnkE5XTsffrIkc+13MaG8955mrmuLuZOe5eZo67Tw7HHVTH3Vp13GXc5ILq415EfdxV4xb7vyHjexJKEewJHckTt2hdnujuGQO5UVDuG7WhA1+QD3aqfEjQqMa9l38HZV43Je4LEndNibsKwZu4k8zHrUyYn+v4403il2uSqq+1t8xtUIegrKhB6ET8aebiD4+T2bU1uU6D5IFqn3dLnCWkjqG4xHnPXJyRcUFZ8cEL47Mxjk/escb8F/Xn/L2dsn7PoCG3V33s36bqjwkdf5nkWyrnd6bm3+Fa+nm+6n6eB3XvZGv97VRG3XlLb1QeX+70911/LPTid6/2+aS+Seqh3PJnntvllRXyrrQy1sFaWB+bowMGoCP2QxcciA3xfWyEc9EVl2ET3IxN8SA2wwxsgZewJV7FVvgTtsZ/oDsWl7mUS6MnlsE2WAfbogO2x87YAftiRwxDbxyKnXA2dsY56IPzsCvuQl/cg354GN/B0+iP57AHypiPUjel1FllH/Oxt+TXZHTGadgLp+MgnIErcCam4my8gMn4Fc7HfNLvqwCuyIrXSuqJpP5IiXeAEq+8I28g/UcdsBk6ogc2Qm90xSA=
*/