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