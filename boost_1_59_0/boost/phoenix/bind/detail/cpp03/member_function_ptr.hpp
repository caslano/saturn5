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
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
*/