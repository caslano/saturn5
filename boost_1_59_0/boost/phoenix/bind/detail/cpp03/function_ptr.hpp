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
    template <int N, typename Dummy = void>
    struct function_ptr_impl
    {
        template <typename RT, typename FP>
        struct impl;
    };

    template <int N, typename RT, typename FP>
    struct function_ptr : function_ptr_impl<N>::template impl<RT, FP>
    {
        typedef typename function_ptr_impl<N>::template impl<RT, FP> base;

        function_ptr(FP fp_)
            : base(fp_) {}
        
        using base::fp;

        bool operator==(function_ptr const & rhs) const
        {
            return fp == rhs.fp;
        }

        template <int M, typename RhsRT, typename RhsFP>
        bool operator==(function_ptr<M, RhsRT, RhsFP> const & /*rhs*/) const
        {
            return false;
        }

    };

    template <typename Dummy>
    struct function_ptr_impl<0, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp_)
                : fp(fp_) {}

            RT operator()() const
            {
                return fp();
            }

            FP fp;
        };
    };

    template <typename Dummy>
    struct function_ptr_impl<1, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp_)
                : fp(fp_) {}

            template <typename A>
            RT operator()(A &a) const
            {
                return fp(a);
            }

            FP fp;
        };
    };

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/function_ptr.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/function_ptr_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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
    (3, (2, BOOST_PHOENIX_COMPOSITE_LIMIT,                                      \
    <boost/phoenix/bind/detail/cpp03/function_ptr.hpp>))
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
#else // defined(BOOST_PP_IS_ITERATING)

    template <typename Dummy>
    struct function_ptr_impl<BOOST_PHOENIX_ITERATION, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp_)
                : fp(fp_) {}

            template <BOOST_PHOENIX_typename_A>
            RT operator()(BOOST_PHOENIX_A_ref_a) const
            {
                return fp(BOOST_PHOENIX_a);
            }

            FP fp;
        };
    };

#endif // defined(BOOST_PP_IS_ITERATING)

/* function_ptr.hpp
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
*/