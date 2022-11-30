// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef PY_FUNCTION_DWA200286_HPP
# define PY_FUNCTION_DWA200286_HPP

# include <boost/python/detail/signature.hpp>
# include <boost/detail/workaround.hpp>
# include <boost/mpl/size.hpp>
# include <memory>

namespace boost { namespace python { namespace objects {

// This type is used as a "generalized Python callback", wrapping the
// function signature:
//
//      PyObject* (PyObject* args, PyObject* keywords)

struct BOOST_PYTHON_DECL py_function_impl_base
{
    virtual ~py_function_impl_base();
    virtual PyObject* operator()(PyObject*, PyObject*) = 0;
    virtual unsigned min_arity() const = 0;
    virtual unsigned max_arity() const;
    virtual python::detail::py_func_sig_info signature() const = 0;
};

template <class Caller>
struct caller_py_function_impl : py_function_impl_base
{
    caller_py_function_impl(Caller const& caller)
        : m_caller(caller)
    {}
    
    PyObject* operator()(PyObject* args, PyObject* kw)
    {
        return m_caller(args, kw);
    }
    
    virtual unsigned min_arity() const
    {
        return m_caller.min_arity();
    }
    
    virtual python::detail::py_func_sig_info signature() const
    {
        return m_caller.signature();
    }

 private:
    Caller m_caller;
};

template <class Caller, class Sig>
struct signature_py_function_impl : py_function_impl_base
{
    signature_py_function_impl(Caller const& caller)
        : m_caller(caller)
    {}
    
    PyObject* operator()(PyObject* args, PyObject* kw)
    {
        return m_caller(args, kw);
    }
    
    virtual unsigned min_arity() const
    {
        return mpl::size<Sig>::value - 1;
    }
    
    virtual python::detail::py_func_sig_info signature() const
    {
        python::detail::signature_element const* sig = python::detail::signature<Sig>::elements();
        python::detail::py_func_sig_info res = {sig, sig};
        return  res;
    }

 private:
    Caller m_caller;
};

template <class Caller, class Sig>
struct full_py_function_impl : py_function_impl_base
{
    full_py_function_impl(Caller const& caller, unsigned min_arity, unsigned max_arity)
      : m_caller(caller)
      , m_min_arity(min_arity)
      , m_max_arity(max_arity > min_arity ? max_arity : min_arity)
    {}
    
    PyObject* operator()(PyObject* args, PyObject* kw)
    {
        return m_caller(args, kw);
    }
    
    virtual unsigned min_arity() const
    {
        return m_min_arity;
    }
    
    virtual unsigned max_arity() const
    {
        return m_max_arity;
    }
    
    virtual python::detail::py_func_sig_info signature() const
    {
        python::detail::signature_element const* sig = python::detail::signature<Sig>::elements();
        python::detail::py_func_sig_info res = {sig, sig};
        return  res;
    }

 private:
    Caller m_caller;
    unsigned m_min_arity;
    unsigned m_max_arity;
};

struct py_function
{
    template <class Caller>
    py_function(Caller const& caller)
        : m_impl(new caller_py_function_impl<Caller>(caller))
    {}

    template <class Caller, class Sig>
    py_function(Caller const& caller, Sig)
      : m_impl(new signature_py_function_impl<Caller, Sig>(caller))
    {}

    template <class Caller, class Sig>
    py_function(Caller const& caller, Sig, int min_arity, int max_arity = 0)
      : m_impl(new full_py_function_impl<Caller, Sig>(caller, min_arity, max_arity))
    {}

    py_function(py_function const& rhs)
#if defined(BOOST_NO_CXX11_SMART_PTR)
      : m_impl(rhs.m_impl)
#else
      : m_impl(std::move(rhs.m_impl))
#endif
    {}

    PyObject* operator()(PyObject* args, PyObject* kw) const
    {
        return (*m_impl)(args, kw);
    }

    unsigned min_arity() const
    {
        return m_impl->min_arity();
    }
    
    unsigned max_arity() const
    {
        return m_impl->max_arity();
    }

    python::detail::signature_element const* signature() const
    {
        return m_impl->signature().signature;
    }

    python::detail::signature_element const& get_return_type() const
    {
        return *m_impl->signature().ret;
    }
    
 private:
#if defined(BOOST_NO_CXX11_SMART_PTR)
    mutable std::auto_ptr<py_function_impl_base> m_impl;
#else
    mutable std::unique_ptr<py_function_impl_base> m_impl;
#endif
};

}}} // namespace boost::python::objects

#endif // PY_FUNCTION_DWA200286_HPP

/* py_function.hpp
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
*/