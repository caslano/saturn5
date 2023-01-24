// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_FUNCTION1_DWA200655_HPP
# define BOOST_DETAIL_FUNCTION1_DWA200655_HPP

# include <boost/concept_check.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/type_traits/add_const.hpp>
# include <boost/mpl/apply.hpp>

namespace boost { namespace detail {

// A utility for creating unary function objects that play nicely with
// boost::result_of and that handle the forwarding problem.
//
// mpl::apply<F, A0>::type is expected to be a stateless function
// object that accepts an argument of type A0&.  It is also expected
// to have a nested ::result_type identical to its return type.
template<typename F>
struct function1
{
    template<typename Signature>
    struct result
    {};

    template<typename This, typename A0>
    struct result<This(A0)>
    {
        // How adding const to arguments handles rvalues.
        //
        // if A0 is     arg0 is       represents actual argument
        // --------     -------       --------------------------
        // T const &    T const       const T lvalue
        // T &          T             non-const T lvalue
        // T const      T const       const T rvalue
        // T            T const       non-const T rvalue
        typedef typename remove_reference<
            typename add_const< A0 >::type
        >::type arg0;

        typedef typename mpl::apply1<F, arg0>::type impl;
        typedef typename impl::result_type type;
    };

    // Handles mutable lvalues
    template<typename A0>
    typename result<function1(A0 &)>::type
    operator ()(A0 &a0) const
    {
        typedef typename result<function1(A0 &)>::impl impl;
        typedef typename result<function1(A0 &)>::type type;
        typedef A0 &arg0;
        BOOST_CONCEPT_ASSERT((UnaryFunction<impl, type, arg0>));
        //boost::function_requires<UnaryFunctionConcept<impl, type, arg0> >();
        return impl()(a0);
    }

    // Handles const lvalues and all rvalues
    template<typename A0>
    typename result<function1(A0 const &)>::type
    operator ()(A0 const &a0) const
    {
        typedef typename result<function1(A0 const &)>::impl impl;
        typedef typename result<function1(A0 const &)>::type type;
        typedef A0 const &arg0;
        BOOST_CONCEPT_ASSERT((UnaryFunction<impl, type, arg0>));
        //boost::function_requires<UnaryFunctionConcept<impl, type, arg0> >();
        return impl()(a0);
    }
};

}} // namespace boost::detail

#endif // BOOST_DETAIL_FUNCTION1_DWA200655_HPP

/* function1.hpp
2rgrc7CuTAPkM2cNrj8FntPgNzlLLbvhF+o3D0iz/Rfqd2cNrj8/a3D9S6FvV2YN3qN/Bp5fgd+mCXrhgFY+prvY/j7mjaVZ+Qv6OScvaMPuLL2gbStaD6E3B/ksUMYJM6A6qdAouUzoxsBlllxCsCRVciVKl0ilJqnUbJeWJLLyE+SjNQ7F3UCoZkBkCkJyzZ5jw4Rfln3gvETZB95R9jGwH7qh7Y9PGDwOL0wY3Afdv6CzhPk64bdqy2C+eGD5myFvsk0v9E5Qy9r8S7pMtsF91QPpp0Hc72CNLemKF3rhV3IyXpj+TbzwAvzeTdYLjRDX2hMv3NY1+Js6YczctsHftBSe/fBba1Pb0fkL6w7zbf6Fdbf9gjbuHVAeg3sJrxdGJOqFLbPihbMVg9vUNN8s9F7QJnO2XkjOPq8P0vQL+iCYb8b8i7fJkT24TXMHlLcX7rdfl9AP72ZB+P8C7/bDcwzendHOBF0M3r1yqVq3Sas/dk4I7xezqRo7Q4TtRL7APBHmD8TNgHs2/FInqu2OwT0T93O4F4OXF75DeFnkvngfNU0cvPYx3cA4LO+piWo7zttS95bL8bY4dP/kTXCw7mdQB8JutMV5tZhP1BiTLW6pFrNXjcmwxa3VYrapMeNscS9oMRsxZk5Fi0xSKDRFnJXs+5WDrYZ49ZwCm8CRGUv7svNva86/nU0iAWXxUlZxPnIqlloeeV6n
*/