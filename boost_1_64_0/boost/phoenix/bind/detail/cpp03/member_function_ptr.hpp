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
U76JNvaoJUMeUaDyjXI6uQ8HS2OuDO+8n+SbKeVThXStYKYh2hMhLPGlfZ5qvZbBNlnyKcRzrcYdt3CY2qC2pWwy7+JusnDFcgOGJraLd7i4ExLXk66VYdl6MJmocxncSQuX8VRMQuyS7ag5uFMWLovt0FwjhaWWi7vZwtXTqQZW8pjp8w7uUzauhD3NDPpe0cXdYuEqasFaaaST9YyDO23jSl6ukC1hq9TFnbFw1TTM2UIxldzh4m61cB7mE6wvsFzpc3BnbZyH6FuNLEzcnIO7zc43X2lUa4V8MrPDwd1u4Wr5XANDbiFZ8hzcObu8mELSHnZLsm45fmbrQalQLHleOdnXcHDnLVy5mkoVqtkUTGwHd4eFa+S9bK6KJXcq6+AuOPWXyVZhGiSzbr1ctOVDvDQM2eVk5qkObs7m1yjA3Emnkjm3Pf5u4UqpRtbLYM72djq4S3Y5GoVsuYGt9VK/g7vLzjfjVTPVBkKBuuVIHLVw1Tzu+2fQL11+S21cJluslj3os1uOZYQj+Yq1YjHtYZxz811u4TBk5ApVtQJ1x4MVFi6XzVZK2TqGTRe30ikHVqCpMvqRK99qmx/0pVrJwSYvOrg1Fg6bzplyEfW3w9XnLgtXLOdy+VqxlNxRIVwP4dZKXB1L9hr2erA+GRqbbKstxskOFg9UqC2UplemwTYzHHzL6VwNAza5gNPdX1q4mnRVmc7DU/u5TDaLY4m9aunjx0DCXxwtU3bmXGyPTIdBrVJsZGtYFiaHkYbOMfRbAzPTZt3dejylv9FKj7iE6XQdWuclzXl+KG1Sy3zUlrmerpRrNfCYmHTW+k66E1ae6FheOVXPYSRDYSNSJnVZbzlq78N4VRj+qVwalWseNAqn57KeO2qfj8HILhRqGOGdjYAbJp+td3BSOu2cmzZfK1dwTmenpbdMnLTL3uycS8OkS6VRXistTelO2i6ZFnWLzuR5GRwyIUBTaz/shc3mBjTVM6e9/Rl22iI2Quo1WMkUJEw8QmHS6jba+ma7jaqFejabx56X1sVJrJ33wQmG2qhH67FMV01Wy5lsKpup8roZo7zOS6fZTWlorV0v4tSyXMTTG/5uOfZCWhOjWkSdZkymqWMuz8HqrAZqP4zaFCcRJs2Ndj6lCqJX1nK6Nuw0ug4PW/WAvZJCDVuISBVEm1TqovwhhviMgOvwJpkWhhMsXWxjYhU6ZfwQUInhOJ2ferPdp7F4VfszXnIUer4P+hLsyeiL/qZP63xvp/TUL6s4wivUi2kkh5bgVr9d0sR2E1PUrp98vVpHUhibbX9bfRChWrWqsK/Gs+0yFnNF1FC+7g8C7MITjkX6ZtcvoFqDN0PN7ssmzrMpo06/8i32/nCuVsUuPMYCp09N7u3gehBey6PBQLdr71ucvgFdqKRLGeSvNHz/BK7RQAB1Th46I6++xTlTzMPuxH8wfkUeYbV9LZmC33grdBbVkbxg3BQ97IEU8qUIXiraLDRGXYew6/Ko5IGhoVosFxrFnOl0jvuAKY9Ofwrp5bgKr4ZsLpUq+W0Il7cxCBAMFkZxFQuOD4/fCnVmSKFch1vtIfISMj5eNy+JxeD2LIDCj/C2uwssPQbo8utcEYshfiLW9jLCAoCaJBjn590rgk5srtW2KH7GT3twL/ST/aSqf5RvwA0UlTcqUg/RGx4Gd+piBE5tbvpgxn0iAkfejD7wOsLdEoWbmVAYw6svRjaKL2t47bJwg4gmPjpEIc2nNeZLVn4oG+4T0P1Ng7nVwuDiXQTm2xLjy6FBjLndwsAfMILPTyzM/kjMjXbc3GrRvC/HmHN/djDQzjHMqBLzEpePedGGMb8I85mEo2hzcHq/aY8=
*/