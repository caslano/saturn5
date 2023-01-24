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
4J24he2RjsIW6t7WSjLgNeG7zEZzm0A6cIw84W4zid5ka6pG8eR3Qz8FGq3GxFVeZ2eveT8i8Qf+TYpFhknAmCcYPXzS0V+cbDlvxF+Z8P86VSTOl/n+DfspH0fN+uirO3J6HMK0B86T4iY2y/Vv3RkiXmJEPjHyHg+oJZ/ROO5X0jkHxLVCYP5hnHgsM7PibAMQLzrTbzh/DOGtJtk33ziO6lEn1wd4aKLkMojf+NBpZ0Jnbdq+LlFT0GbiGF3+uS+hO3O3BzA1uPA0mMRhDjHeQWHj+1FBI34eiJe47Kzz7s3bKaKz4Q3jvfFDD1Kno8WOoK2mkZFpdg5v9eL64vLy8uLc2sFu/8+a/Xgf/cmjIlIXGGYnklvh+OiAck4W4zURLgvTtEtvcbZxKK2t7e3l7o6umhoC5RfEDQ6CEw7jmEoL/bE+3rse87N6HZTYmO79xQ2kh2vc1S3BWYfVKyFBaJDl+9Fyy5fe00vv+xyqhMHN1XbzIe1L9xrHyQb5fnfxB4YJjsbVaSICH4L7L7SYHiVvQzxvzou27nR+I9ttvHQVJXDvErH7LfiBxlNDs/FawcviH7ik52k5ExxCgsZi4XQr2KzZtE+pyWECpUdRFch4lHVcNeyp7Kkq98cRTuzWveUjrudZv2o4hXlGrEVCPQ6xaWpXa1ixfQJtYswu7YFzi6433qLhT+kjJfYrRYCiCjiboLqEhKm8
*/