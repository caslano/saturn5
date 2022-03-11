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