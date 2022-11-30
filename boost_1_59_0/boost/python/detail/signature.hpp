#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# ifndef SIGNATURE_DWA20021121_HPP
#  define SIGNATURE_DWA20021121_HPP

#  include <boost/python/type_id.hpp>

#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/python/detail/indirect_traits.hpp>
#  include <boost/python/converter/pytype_function.hpp>

#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/iteration/local.hpp>

#  include <boost/mpl/at.hpp>
#  include <boost/mpl/size.hpp>

namespace boost { namespace python { namespace detail { 

struct signature_element
{
    char const* basename;
    converter::pytype_function pytype_f;
    bool lvalue;
};

struct py_func_sig_info
{
    signature_element const *signature;
    signature_element const *ret;
};

template <unsigned> struct signature_arity;

#  define BOOST_PP_ITERATION_PARAMS_1                                            \
        (3, (0, BOOST_PYTHON_MAX_ARITY + 1, <boost/python/detail/signature.hpp>))
#  include BOOST_PP_ITERATE()

// A metafunction returning the base class used for
//
//   signature<class F, class CallPolicies, class Sig>.
//
template <class Sig>
struct signature_base_select
{
    enum { arity = mpl::size<Sig>::value - 1 };
    typedef typename signature_arity<arity>::template impl<Sig> type;
};

template <class Sig>
struct signature
    : signature_base_select<Sig>::type
{
};

}}} // namespace boost::python::detail

# endif // SIGNATURE_DWA20021121_HPP

#else

# define N BOOST_PP_ITERATION()

template <>
struct signature_arity<N>
{
    template <class Sig>
    struct impl
    {
        static signature_element const* elements()
        {
            static signature_element const result[N+2] = {
                
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
# define BOOST_PP_LOCAL_MACRO(i)                                                            \
                {                                                                           \
                  type_id<BOOST_DEDUCED_TYPENAME mpl::at_c<Sig,i>::type>().name()           \
                  , &converter::expected_pytype_for_arg<BOOST_DEDUCED_TYPENAME mpl::at_c<Sig,i>::type>::get_pytype   \
                  , indirect_traits::is_reference_to_non_const<BOOST_DEDUCED_TYPENAME mpl::at_c<Sig,i>::type>::value \
                },
#else
# define BOOST_PP_LOCAL_MACRO(i)                                                            \
                {                                                                           \
                  type_id<BOOST_DEDUCED_TYPENAME mpl::at_c<Sig,i>::type>().name()           \
                  , 0 \
                  , indirect_traits::is_reference_to_non_const<BOOST_DEDUCED_TYPENAME mpl::at_c<Sig,i>::type>::value \
                },
#endif
                
# define BOOST_PP_LOCAL_LIMITS (0, N)
# include BOOST_PP_LOCAL_ITERATE()
                {0,0,0}
            };
            return result;
        }
    };
};

#endif // BOOST_PP_IS_ITERATING 



/* signature.hpp
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
*/