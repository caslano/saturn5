#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# ifndef CALLER_DWA20021121_HPP
#  define CALLER_DWA20021121_HPP

#  include <boost/python/type_id.hpp>
#  include <boost/python/handle.hpp>

#  include <boost/detail/indirect_traits.hpp>

#  include <boost/python/detail/invoke.hpp>
#  include <boost/python/detail/signature.hpp>
#  include <boost/python/detail/preprocessor.hpp>
#  include <boost/python/detail/type_traits.hpp>

#  include <boost/python/arg_from_python.hpp>
#  include <boost/python/converter/context_result_converter.hpp>
#  include <boost/python/converter/builtin_converters.hpp>

#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/dec.hpp>
#  include <boost/preprocessor/if.hpp>
#  include <boost/preprocessor/iteration/local.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#  include <boost/preprocessor/repetition/repeat.hpp>

#  include <boost/compressed_pair.hpp>

#  include <boost/mpl/apply.hpp>
#  include <boost/mpl/eval_if.hpp>
#  include <boost/mpl/identity.hpp>
#  include <boost/mpl/size.hpp>
#  include <boost/mpl/at.hpp>
#  include <boost/mpl/int.hpp>
#  include <boost/mpl/next.hpp>

namespace boost { namespace python { namespace detail { 

template <int N>
inline PyObject* get(mpl::int_<N>, PyObject* const& args_)
{
    return PyTuple_GET_ITEM(args_,N);
}

inline Py_ssize_t arity(PyObject* const& args_)
{
    return PyTuple_GET_SIZE(args_);
}

// This "result converter" is really just used as
// a dispatch tag to invoke(...), selecting the appropriate
// implementation
typedef int void_result_to_python;

// Given a model of CallPolicies and a C++ result type, this
// metafunction selects the appropriate converter to use for
// converting the result to python.
template <class Policies, class Result>
struct select_result_converter
  : mpl::eval_if<
        is_same<Result,void>
      , mpl::identity<void_result_to_python>
      , mpl::apply1<typename Policies::result_converter,Result>
    >
{
};

template <class ArgPackage, class ResultConverter>
inline ResultConverter create_result_converter(
    ArgPackage const& args_
  , ResultConverter*
  , converter::context_result_converter*
)
{
    return ResultConverter(args_);
}
    
template <class ArgPackage, class ResultConverter>
inline ResultConverter create_result_converter(
    ArgPackage const&
  , ResultConverter*
  , ...
)
{
    return ResultConverter();
}

#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
template <class ResultConverter>
struct converter_target_type 
{
    static PyTypeObject const *get_pytype()
    {
        return create_result_converter((PyObject*)0, (ResultConverter *)0, (ResultConverter *)0).get_pytype();
    }
};

template < >
struct converter_target_type <void_result_to_python >
{
    static PyTypeObject const *get_pytype()
    {
        return 0;
    }
};

// Generation of ret moved from caller_arity<N>::impl::signature to here due to "feature" in MSVC 15.7.2 with /O2
// which left the ret uninitialized and caused segfaults in Python interpreter.
template<class Policies, class Sig> const signature_element* get_ret()
{
    typedef BOOST_DEDUCED_TYPENAME Policies::template extract_return_type<Sig>::type rtype;
    typedef typename select_result_converter<Policies, rtype>::type result_converter;

    static const signature_element ret = {
        (is_void<rtype>::value ? "void" : type_id<rtype>().name())
        , &detail::converter_target_type<result_converter>::get_pytype
        , boost::detail::indirect_traits::is_reference_to_non_const<rtype>::value 
    };

    return &ret;
}

#endif

    
template <unsigned> struct caller_arity;

template <class F, class CallPolicies, class Sig>
struct caller;

#  define BOOST_PYTHON_NEXT(init,name,n)                                                        \
    typedef BOOST_PP_IF(n,typename mpl::next< BOOST_PP_CAT(name,BOOST_PP_DEC(n)) >::type, init) name##n;

#  define BOOST_PYTHON_ARG_CONVERTER(n)                                         \
     BOOST_PYTHON_NEXT(typename mpl::next<first>::type, arg_iter,n)             \
     typedef arg_from_python<BOOST_DEDUCED_TYPENAME arg_iter##n::type> c_t##n;  \
     c_t##n c##n(get(mpl::int_<n>(), inner_args));                              \
     if (!c##n.convertible())                                                   \
          return 0;

#  define BOOST_PP_ITERATION_PARAMS_1                                            \
        (3, (0, BOOST_PYTHON_MAX_ARITY + 1, <boost/python/detail/caller.hpp>))
#  include BOOST_PP_ITERATE()

#  undef BOOST_PYTHON_ARG_CONVERTER
#  undef BOOST_PYTHON_NEXT

// A metafunction returning the base class used for caller<class F,
// class ConverterGenerators, class CallPolicies, class Sig>.
template <class F, class CallPolicies, class Sig>
struct caller_base_select
{
    enum { arity = mpl::size<Sig>::value - 1 };
    typedef typename caller_arity<arity>::template impl<F,CallPolicies,Sig> type;
};

// A function object type which wraps C++ objects as Python callable
// objects.
//
// Template Arguments:
//
//   F -
//      the C++ `function object' that will be called. Might
//      actually be any data for which an appropriate invoke_tag() can
//      be generated. invoke(...) takes care of the actual invocation syntax.
//
//   CallPolicies -
//      The precall, postcall, and what kind of resultconverter to
//      generate for mpl::front<Sig>::type
//
//   Sig -
//      The `intended signature' of the function. An MPL sequence
//      beginning with a result type and continuing with a list of
//      argument types.
template <class F, class CallPolicies, class Sig>
struct caller
    : caller_base_select<F,CallPolicies,Sig>::type
{
    typedef typename caller_base_select<
        F,CallPolicies,Sig
        >::type base;

    typedef PyObject* result_type;
    
    caller(F f, CallPolicies p) : base(f,p) {}

};

}}} // namespace boost::python::detail

# endif // CALLER_DWA20021121_HPP

#else

# define N BOOST_PP_ITERATION()

template <>
struct caller_arity<N>
{
    template <class F, class Policies, class Sig>
    struct impl
    {
        impl(F f, Policies p) : m_data(f,p) {}

        PyObject* operator()(PyObject* args_, PyObject*) // eliminate
                                                         // this
                                                         // trailing
                                                         // keyword dict
        {
            typedef typename mpl::begin<Sig>::type first;
            typedef typename first::type result_t;
            typedef typename select_result_converter<Policies, result_t>::type result_converter;
            typedef typename Policies::argument_package argument_package;
            
            argument_package inner_args(args_);

# if N
#  define BOOST_PP_LOCAL_MACRO(i) BOOST_PYTHON_ARG_CONVERTER(i)
#  define BOOST_PP_LOCAL_LIMITS (0, N-1)
#  include BOOST_PP_LOCAL_ITERATE()
# endif 
            // all converters have been checked. Now we can do the
            // precall part of the policy
            if (!m_data.second().precall(inner_args))
                return 0;

            PyObject* result = detail::invoke(
                detail::invoke_tag<result_t,F>()
              , create_result_converter(args_, (result_converter*)0, (result_converter*)0)
              , m_data.first()
                BOOST_PP_ENUM_TRAILING_PARAMS(N, c)
            );
            
            return m_data.second().postcall(inner_args, result);
        }

        static unsigned min_arity() { return N; }
        
        static py_func_sig_info  signature()
        {
            const signature_element * sig = detail::signature<Sig>::elements();
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
            // MSVC 15.7.2, when compiling to /O2 left the static const signature_element ret, 
            // originally defined here, uninitialized. This in turn led to SegFault in Python interpreter.
            // Issue is resolved by moving the generation of ret to separate function in detail namespace (see above).
            const signature_element * ret = detail::get_ret<Policies, Sig>();

            py_func_sig_info res = {sig, ret };
#else
            py_func_sig_info res = {sig, sig };
#endif

            return  res;
        }
     private:
        compressed_pair<F,Policies> m_data;
    };
};



#endif // BOOST_PP_IS_ITERATING 



/* caller.hpp
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
*/