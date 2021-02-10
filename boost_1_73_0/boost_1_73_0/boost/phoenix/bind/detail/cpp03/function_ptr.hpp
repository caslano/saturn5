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
bd7ttPhWbFhMjC8JpUOjHNsA09/uHBzt/J3D6jTARiO/bPA4EyoEnWTk+5PqWnPte+exaEoEbTr2o1jL5LgW6LByd/XJDJdRgU0XcnOUuYGE+9LBSlkvEh+zCcK2zHPSd2RZ0mviNJNEDM+VcCe07WbIxzsxSOk67A3jKAx+56ORYx/PYgbJuK5XBRpTxhNY8vI0PIVUWFDZ58HZwTjACW+vwFU5xhVCThpFhnRwUK0zeZ2OkqJwvfENtsK7jAK8hx13NDYxesFoGisbybIEdx5O8b567AcsxiSSaZLmDAzNP1ZNCWuRUcztvy0fzhzFAwfpFjxbvAsX3jqPu8Iq9ka4zGeyQrP9upK3zhJ5C/kdCEV2hockjSaSNvjMraxJ72l2EI/qPG4MQ0kxCT6HX0qmE4W+sTldBHzYWVVxWp6wEBewYwxzVf//9r69v20bWfT/fApYltdSooftNtmtE6XJJk6b36ZJju30nHti14eWaJvXEqklKTtu4n72Ow8ABMCHKFtum3PL325qkXgMBoPBYF4oDb5lXFWWx0eF4tJXezfE0fF7tXDLtyp1bKAZNeN69JD1l+JYOfXVHKp+6R4zdJQUBUnpUsbpqSBSriRKTkcTacjnBxNRQtahI2Q70j3j5adZkpYjh5TS
*/