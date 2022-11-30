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
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
*/