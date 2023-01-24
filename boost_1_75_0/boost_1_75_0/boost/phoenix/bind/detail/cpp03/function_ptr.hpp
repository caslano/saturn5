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
4995jq0NPi9+agg+PPyum21qCpY+sS79eXSYyhxKsoRCdfC8JEuRTD8NIvvQLKEVQtxXrxtuQHcQODLrdTaEqkfVhKqGXqbqEKkokNxSmAdPNcUb/xHvCp8Y2/rDZKH1Z6EVc+rRMl8eKfKSWvQdlpmbgYDd3urlFtDJwEhAv0fxV6qy4JDVV0PY7c4/h5QkDyJQ4+kOLklAK4nuU7kupCzAL5u1Y74KLzm8pF1ZIJ0BzloX/0qKWKfYV552pc/OwAnqiQCL5/Og2p2FAu77vOZPvEA97g+PKz7CKOhr4K2s4wK+rSLMx2suM96nTODMW+ntdTe6NivnZ+NyXlmadCMIiKe70ToGTgefGpYFiF2vQJ6bkw8Zn8w8j2h33N5ek4znVGl9TkA+wzCGyoeYj+SUGyG9Oczsz8w4CGC8aE2HH4g/BdSe+6Iy/EH/x12JLqMpsbboJoUoZyIfwq+9rm+erGPcPRBtqG3w5ZB4QXK9S73svTqBU73Ngyscc947NZV1sZ6tf+gEZQXa9bobwjg2Fo6NdEOY4Xvk+1LWw6wiPEBC9v7JVLy+Genhqf0OjreKZza+4owTndpqkOSzhqYnxcVbF+Swhjaee4kgYNsSHsF9rE7f4h3NC0onaPA0r0PDYydwuNh+v2og2XZcbQoL69KfcakmdZpxfc6iBAgs3OzFcTu2ojETTBDe6bTsxhAwFTo9CLDgNspt
*/