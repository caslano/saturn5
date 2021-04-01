/*=============================================================================
Copyright (c) 2001-2007 Joel de Guzman

Distributed under the Boost Software License, Version 1.0. (See accompanying 
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/support/iterate.hpp>

namespace boost { namespace phoenix { namespace detail
{
    template <int N>
    struct member_function_ptr_impl
    {
        template <typename RT, typename FP>
        struct impl;
    };

    template <int N, typename RT, typename FP>
    struct member_function_ptr
        : member_function_ptr_impl<N>::template impl<RT, FP>
    {
        typedef typename member_function_ptr_impl<N>::
            template impl<RT, FP> base;
        member_function_ptr(FP fp_)
            : base(fp_) {}
        
        using base::fp;

        bool operator==(member_function_ptr const & rhs) const
        {
            return fp == rhs.fp;
        }

        template <int M, typename RhsRT, typename RhsFP>
        bool operator==(member_function_ptr<M, RhsRT, RhsFP> const &) const
        {
            return false;
        }
    };

    template <>
    struct member_function_ptr_impl<0>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp_)
                : fp(fp_) {}

            template <typename Class>
            RT operator()(Class& obj) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj) ->*fp)();
            }

            template <typename Class>
            RT operator()(Class* obj) const
            {
                return (obj->*fp)();
            }

            FP fp;
        };
    };

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/member_function_ptr.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/member_function_ptr_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_COMPOSITE_LIMIT,                                      \
    <boost/phoenix/bind/detail/cpp03/member_function_ptr.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}} // namespace boost::phoenix::detail

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else

    template <>
    struct member_function_ptr_impl<BOOST_PHOENIX_ITERATION>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp_)
                : fp(fp_) {}

            template <typename Class, BOOST_PHOENIX_typename_A>
            RT operator()(Class& obj, BOOST_PHOENIX_A_ref_a) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(BOOST_PHOENIX_a);
            }

            template <typename Class, BOOST_PHOENIX_typename_A>
            RT operator()(Class* obj, BOOST_PHOENIX_A_ref_a) const
            {
                return (obj->*fp)(BOOST_PHOENIX_a);
            }

            FP fp;
        };
    };

#endif // defined(BOOST_PP_IS_ITERATING)

/* member_function_ptr.hpp
tXyDeSMvxa+zhN4yQnBS/5U2TlCaGZ+nhjfYHTRfg7s/yrAl8MT/3p35EQQgKWVUg+S/1zj8i4F9xXmIp5lhRblnS+/6kN3tXLGiLC8X2W5JFJ3l0TrU/y+7upXcFc1vP6PhrgPD8A3g5a34FhBFqfFKjHcm4D6FDSDecdnmz7EZ/pkjEdq0XiVnWNwGwdvjdGAp9kw4b/FX3zUyCfqvLf21W54cV48jPQ/56ce7a2FoqJ8YehXoBm7Bw9EhXtHWd6C/AJajcaZExwac6xOfcDxMCdT4uLsFnh0ThKOHySS2uQ4Btln9fKRsvD87lWxI2/SIe4NmY6XGgW4C+OVDOBylk4EQ35jPaPbIP06hJqT/OW3xpeAYerkwVCenJOE7S4PHMlBkkY7v2Gc8M5+erZQixX5vjMLRWzndFMnnH7D91vW74BvEgK4xpMPb6nvZV1nrW7doAcIRpJBj4FM5CQ6viPieiyfW+2cfH/Enl7pUQ6T+jKEnpNzwi6jVrO809cD86aROQ0Gee2syGLstZF9xEJInoB6LehpEhHtMDa5S6MPblxI0Cp+3Hw==
*/