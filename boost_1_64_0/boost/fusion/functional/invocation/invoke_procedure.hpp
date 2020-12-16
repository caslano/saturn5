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
bIIr0A0/wdZ4Ed3xGnriz9gGn2E7LEykXvgmtscq2AGrYUdsip3QA33QB7tiKPriYHwbZ6If7sZuuB/fxRPYCy9iH/wRtfgAA7CYjO1cCkOwOYZiFPbFOOyHkzAMP8ZwXIj9cQMOwL0YgUcwEj/FaHyGMfgcY3GgjPU8HONxPybgERyE13AwKj8KQzABh+JQHIbv4UicgKNwMo7GOTgGF+N4TMMJ+DVOxHv4Pj7CD1EZC3UStsGPMBo/xmE4HcfhDJyAs3A1zsYNOAcP4Vz8FOfhI5yPz3Ah5uNavggLYgoWw8VYAlOxLK7CKrgaa+Ma9MK16I/rsCeux0TcgNMwDRfgRlyOm3ElbsONuB234w78HHeihnK9CwvgbiyE+7A5pmNLPIg+eAj98TAG4BHsh0cxHDMwCs/jVPw7TsfPcR5ewBX4JabhV7gHL+F+/Bp1c3VbSR2d1N1x3unO9bpy3vVS+gNjb2yFWmyHQdgFg/EdDME+GIVRGI3TMAbnYByuwATcioNwFw7BTzERP8OheAWH4TUcjo9xJP6Oo1C5Lk3AkjgRK+MH6IgfYiOchF3xI3wH1+MneAhP4mH8HY9hIfb5OLbCM9gPz2IEnsOP8Dwuwi8wFS9gGl7CU/g1XsbLeAe/wV/wClqTl1exON5AV/wOQ/EWjsTbuBi/x5V4B1fhj3gM7+IpvI8P8AGW4zz6Ge3wITbHR9gaH2MQ/oL98JEV5xM+xg/wF1yDTzANlbEVd2I+/Abz43W0wgKcTwXQFgtiVbRBL3wNO6EtRmARHIhFMQ6L4TAsjiuwBKbjm/gNlsLrWA7vYnl8hJVQGTvODpthZXTDKuiPVbEn2mMi1sZhWA9TsD4uwQa4EpvjEWyBGdgST6Mbfomt8Rq64230wKfoiW9wXrTFctgOK6IX6vpZ55f6TKnnVM6fbko/a1QWbxl7thPWxs7ohCHohX0xAvthHEbiWIzCVIzGDTgQ92AsPsR4LECkCVgEB2MFHILVMRFdcCg2wmHojSOwG76HAZiE0TgKB+NoTMJx+BGOxyU4AbfgRDyC7+NV/ABv4iS8jx+hhn2fjCVwCr6FU7EhTsOmOBPdcS52wXk4EBfgKFyIybgIF2EKfoaL8Qtcgt/gUryKy9CD82I5euFK7Iqr8F1cjUG4BifhWpyKabgaN+Ie3IRf4Ga8jFtQebDdiqVxG1bET9AOt+No3IETcBfOwD24EPfhUjyAG/AgbsNDeBsP4108go/xKD7BDFTq7o5hLzyJwXgKE/E0DsMzOALPYgp+hkvwPK7Gz3ErfoH78AKewK/wDF6Ucsz1TOp4OXdlDHx/o/nFV+vu96QtFq5FD9yEPXALjsCtOBa340zcgfNxF67D3bgV9+Ah3ItHcB9ewv14Aw/hAzyM1iTqCFbBo9gSM9ADj6MPfop98CQm4CkciqdxPJ7BZXgWV+FnuAbP4Qk8j2fxC7SSfv82+CVWwa/QES9iE7yELfEbTMMruAuvooZycw0L4LdYGa9jK7yBa/A7TMNbuBXv4B68i4fxJzyN9/ALfIA/4s/4AB9jIeU6jq/jE/TEp9gen6EP/ord8DfU4j8wEMnTpHAsgAOxICZiIZyNNrgSX8NVaIsZWBivYhH8AYviQ3wDH2MJ1FCuSmIhLIXVsTS+i29hbyyDWiyHC7A8LsJKuBHtcAdWxv1YBTOwKh7Hangaq+MXWBOvoz3ex9r4COvIfU5Sfn0duCZWrtOdlOsoKssVa8o3XsVmeA098DvsgbdxBH6PY/FHnIl3cT7ew3V4H7fiAzyEP+MRfIiX8DHewKf4AJ/J2Lq/YhX8DVviP9ADn2MCkqe68pwPZ2B+XIpWuAatMQ0=
*/