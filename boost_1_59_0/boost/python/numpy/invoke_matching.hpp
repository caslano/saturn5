// Copyright Jim Bosch 2010-2012.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_numpy_invoke_matching_hpp_
#define boost_python_numpy_invoke_matching_hpp_

/**
 *  @brief Template invocation based on dtype matching.
 */

#include <boost/python/numpy/dtype.hpp>
#include <boost/python/numpy/ndarray.hpp>
#include <boost/mpl/integral_c.hpp>

namespace boost { namespace python { namespace numpy {
namespace detail 
{

struct BOOST_NUMPY_DECL add_pointer_meta
{
  template <typename T>
  struct apply 
  {
    typedef typename boost::add_pointer<T>::type type;
  };

};

struct BOOST_NUMPY_DECL dtype_template_match_found {};
struct BOOST_NUMPY_DECL nd_template_match_found {};

template <typename Function>
struct dtype_template_invoker 
{
    
  template <typename T>
  void operator()(T *) const 
  {
    if (dtype::get_builtin<T>() == m_dtype) 
    {
      m_func.Function::template apply<T>();
      throw dtype_template_match_found();
    }
  }

  dtype_template_invoker(dtype const & dtype_, Function func) 
    : m_dtype(dtype_), m_func(func) {}

private:
  dtype const & m_dtype;
  Function m_func;
};

template <typename Function>
struct dtype_template_invoker< boost::reference_wrapper<Function> > 
{
    
  template <typename T>
  void operator()(T *) const 
  {
    if (dtype::get_builtin<T>() == m_dtype) 
    {
      m_func.Function::template apply<T>();
      throw dtype_template_match_found();
    }
  }

  dtype_template_invoker(dtype const & dtype_, Function & func)
    : m_dtype(dtype_), m_func(func) {}

private:
  dtype const & m_dtype;
  Function & m_func;
};

template <typename Function>
struct nd_template_invoker 
{    
  template <int N>
  void operator()(boost::mpl::integral_c<int,N> *) const 
  {
    if (m_nd == N) 
    {
      m_func.Function::template apply<N>();
      throw nd_template_match_found();
    }
  }

  nd_template_invoker(int nd, Function func) : m_nd(nd), m_func(func) {}

private:
  int m_nd;
  Function m_func;
};

template <typename Function>
struct nd_template_invoker< boost::reference_wrapper<Function> > 
{    
  template <int N>
  void operator()(boost::mpl::integral_c<int,N> *) const 
  {
    if (m_nd == N) 
    {
      m_func.Function::template apply<N>();
      throw nd_template_match_found();
    }
  }

  nd_template_invoker(int nd, Function & func) : m_nd(nd), m_func(func) {}

private:
  int m_nd;
  Function & m_func;
};

} // namespace boost::python::numpy::detail

template <typename Sequence, typename Function>
void invoke_matching_nd(int nd, Function f) 
{
  detail::nd_template_invoker<Function> invoker(nd, f);
  try { boost::mpl::for_each< Sequence, detail::add_pointer_meta >(invoker);}
  catch (detail::nd_template_match_found &) { return;}
  PyErr_SetString(PyExc_TypeError, "number of dimensions not found in template list.");
  python::throw_error_already_set();
}

template <typename Sequence, typename Function>
void invoke_matching_dtype(dtype const & dtype_, Function f) 
{
  detail::dtype_template_invoker<Function> invoker(dtype_, f);
  try { boost::mpl::for_each< Sequence, detail::add_pointer_meta >(invoker);}
  catch (detail::dtype_template_match_found &) { return;}
  PyErr_SetString(PyExc_TypeError, "dtype not found in template list.");
  python::throw_error_already_set();
}

namespace detail 
{

template <typename T, typename Function>
struct array_template_invoker_wrapper_2 
{
  template <int N>
  void apply() const { m_func.Function::template apply<T,N>();}
  array_template_invoker_wrapper_2(Function & func) : m_func(func) {}

private:
  Function & m_func;
};

template <typename DimSequence, typename Function>
struct array_template_invoker_wrapper_1 
{
  template <typename T>
  void apply() const { invoke_matching_nd<DimSequence>(m_nd, array_template_invoker_wrapper_2<T,Function>(m_func));}
  array_template_invoker_wrapper_1(int nd, Function & func) : m_nd(nd), m_func(func) {}

private:
  int m_nd;
  Function & m_func;
};

template <typename DimSequence, typename Function>
struct array_template_invoker_wrapper_1< DimSequence, boost::reference_wrapper<Function> >
  : public array_template_invoker_wrapper_1< DimSequence, Function >
{
  array_template_invoker_wrapper_1(int nd, Function & func)
    : array_template_invoker_wrapper_1< DimSequence, Function >(nd, func) {}
};

} // namespace boost::python::numpy::detail

template <typename TypeSequence, typename DimSequence, typename Function>
void invoke_matching_array(ndarray const & array_, Function f) 
{
  detail::array_template_invoker_wrapper_1<DimSequence,Function> wrapper(array_.get_nd(), f);
  invoke_matching_dtype<TypeSequence>(array_.get_dtype(), wrapper);
}

}}} // namespace boost::python::numpy

#endif

/* invoke_matching.hpp
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
*/