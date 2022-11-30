// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef NULLARY_FUNCTION_ADAPTOR_DWA2003824_HPP
# define NULLARY_FUNCTION_ADAPTOR_DWA2003824_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/preprocessor/iteration/local.hpp>
# include <boost/preprocessor/facilities/intercept.hpp>
# include <boost/preprocessor/repetition/enum_params.hpp>
# include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace boost { namespace python { namespace detail { 

// nullary_function_adaptor -- a class template which ignores its
// arguments and calls a nullary function instead.  Used for building
// error-reporting functions, c.f. pure_virtual
template <class NullaryFunction>
struct nullary_function_adaptor
{
    nullary_function_adaptor(NullaryFunction fn)
      : m_fn(fn)
    {}

    void operator()() const { m_fn(); }

# define BOOST_PP_LOCAL_MACRO(i)                                            \
    template <BOOST_PP_ENUM_PARAMS_Z(1, i, class A)>                        \
    void operator()(                                                        \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(1, i, A, const& BOOST_PP_INTERCEPT)   \
    ) const                                                                 \
    {                                                                       \
        m_fn();                                                             \
    }

# define BOOST_PP_LOCAL_LIMITS (1, BOOST_PYTHON_MAX_ARITY)
# include BOOST_PP_LOCAL_ITERATE()
    
 private:
    NullaryFunction m_fn;
};

}}} // namespace boost::python::detail

#endif // NULLARY_FUNCTION_ADAPTOR_DWA2003824_HPP

/* nullary_function_adaptor.hpp
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
*/