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