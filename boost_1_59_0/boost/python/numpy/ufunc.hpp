// Copyright Jim Bosch 2010-2012.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_numpy_ufunc_hpp_
#define boost_python_numpy_ufunc_hpp_

/**
 *  @brief Utilities to create ufunc-like broadcasting functions out of C++ functors.
 */

#include <boost/python.hpp>
#include <boost/python/numpy/numpy_object_mgr_traits.hpp>
#include <boost/python/numpy/dtype.hpp>
#include <boost/python/numpy/ndarray.hpp>
#include <boost/python/numpy/config.hpp>

namespace boost { namespace python { namespace numpy {

/**
 *  @brief A boost.python "object manager" (subclass of object) for PyArray_MultiIter.
 *
 *  multi_iter is a Python object, but a very low-level one.  It should generally only be used
 *  in loops of the form:
 *  @code
 *  while (iter.not_done()) {
 *      ...
 *      iter.next();
 *  }
 *  @endcode
 *
 *  @todo I can't tell if this type is exposed in Python anywhere; if it is, we should use that name.
 *        It's more dangerous than most object managers, however - maybe it actually belongs in
 *        a detail namespace?
 */
class BOOST_NUMPY_DECL multi_iter : public object
{
public:

  BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(multi_iter, object);

  /// @brief Increment the iterator.
  void next();

  /// @brief Check if the iterator is at its end.
  bool not_done() const;

  /// @brief Return a pointer to the element of the nth broadcasted array.
  char * get_data(int n) const;

  /// @brief Return the number of dimensions of the broadcasted array expression.
  int get_nd() const;
    
  /// @brief Return the shape of the broadcasted array expression as an array of integers.
  Py_intptr_t const * get_shape() const;

  /// @brief Return the shape of the broadcasted array expression in the nth dimension.
  Py_intptr_t shape(int n) const;
    
};

/// @brief Construct a multi_iter over a single sequence or scalar object.
BOOST_NUMPY_DECL multi_iter make_multi_iter(object const & a1);

/// @brief Construct a multi_iter by broadcasting two objects.
BOOST_NUMPY_DECL multi_iter make_multi_iter(object const & a1, object const & a2);

/// @brief Construct a multi_iter by broadcasting three objects.
BOOST_NUMPY_DECL multi_iter make_multi_iter(object const & a1, object const & a2, object const & a3);

/**
 *  @brief Helps wrap a C++ functor taking a single scalar argument as a broadcasting ufunc-like
 *         Python object.
 *
 *  Typical usage looks like this:
 *  @code
 *  struct TimesPI 
 *  {
 *    typedef double argument_type;
 *    typedef double result_type;
 *    double operator()(double input) const { return input * M_PI; }
 *  };
 *  
 *  BOOST_PYTHON_MODULE(example)
 *  {
 *    class_< TimesPI >("TimesPI")
 *      .def("__call__", unary_ufunc<TimesPI>::make());
 *  }
 *  @endcode
 *  
 */
template <typename TUnaryFunctor, 
          typename TArgument=typename TUnaryFunctor::argument_type,
          typename TResult=typename TUnaryFunctor::result_type>
struct unary_ufunc 
{

  /**
   *  @brief A C++ function with object arguments that broadcasts its arguments before
   *         passing them to the underlying C++ functor.
   */
  static object call(TUnaryFunctor & self, object const & input, object const & output)
  {
    dtype in_dtype = dtype::get_builtin<TArgument>();
    dtype out_dtype = dtype::get_builtin<TResult>();
    ndarray in_array = from_object(input, in_dtype, ndarray::ALIGNED);
    ndarray out_array = ! output.is_none() ?
      from_object(output, out_dtype, ndarray::ALIGNED | ndarray::WRITEABLE)
      : zeros(in_array.get_nd(), in_array.get_shape(), out_dtype);
    multi_iter iter = make_multi_iter(in_array, out_array);
    while (iter.not_done()) 
    {
      TArgument * argument = reinterpret_cast<TArgument*>(iter.get_data(0));
      TResult * result = reinterpret_cast<TResult*>(iter.get_data(1));
      *result = self(*argument);
      iter.next();
    } 
    return out_array.scalarize();
  }

  /**
   *  @brief Construct a boost.python function object from call() with reasonable keyword names.
   *
   *  Users will often want to specify their own keyword names with the same signature, but this
   *  is a convenient shortcut.
   */
  static object make()
  {
    return make_function(call, default_call_policies(), (arg("input"), arg("output")=object()));
  }
};

/**
 *  @brief Helps wrap a C++ functor taking a pair of scalar arguments as a broadcasting ufunc-like
 *         Python object.
 *
 *  Typical usage looks like this:
 *  @code
 *  struct CosSum 
 *  {
 *    typedef double first_argument_type;
 *    typedef double second_argument_type;
 *    typedef double result_type;
 *    double operator()(double input1, double input2) const { return std::cos(input1 + input2); }
 *  };
 *  
 *  BOOST_PYTHON_MODULE(example) 
 *  {
 *    class_< CosSum >("CosSum")
 *      .def("__call__", binary_ufunc<CosSum>::make());
 *  }
 *  @endcode
 *  
 */
template <typename TBinaryFunctor, 
          typename TArgument1=typename TBinaryFunctor::first_argument_type,
          typename TArgument2=typename TBinaryFunctor::second_argument_type,
          typename TResult=typename TBinaryFunctor::result_type>
struct binary_ufunc 
{

  static object
  call(TBinaryFunctor & self, object const & input1, object const & input2,
       object const & output)
  {
    dtype in1_dtype = dtype::get_builtin<TArgument1>();
    dtype in2_dtype = dtype::get_builtin<TArgument2>();
    dtype out_dtype = dtype::get_builtin<TResult>();
    ndarray in1_array = from_object(input1, in1_dtype, ndarray::ALIGNED);
    ndarray in2_array = from_object(input2, in2_dtype, ndarray::ALIGNED);
    multi_iter iter = make_multi_iter(in1_array, in2_array);
    ndarray out_array = !output.is_none()
      ? from_object(output, out_dtype, ndarray::ALIGNED | ndarray::WRITEABLE)
      : zeros(iter.get_nd(), iter.get_shape(), out_dtype);
    iter = make_multi_iter(in1_array, in2_array, out_array);
    while (iter.not_done()) 
    {
      TArgument1 * argument1 = reinterpret_cast<TArgument1*>(iter.get_data(0));
      TArgument2 * argument2 = reinterpret_cast<TArgument2*>(iter.get_data(1));
      TResult * result = reinterpret_cast<TResult*>(iter.get_data(2));
      *result = self(*argument1, *argument2);
      iter.next();
    } 
    return out_array.scalarize();
  }

  static object make()
  {
    return make_function(call, default_call_policies(),
			    (arg("input1"), arg("input2"), arg("output")=object()));
  }

};

} // namespace boost::python::numpy

namespace converter 
{

NUMPY_OBJECT_MANAGER_TRAITS(numpy::multi_iter);

}}} // namespace boost::python::converter

#endif

/* ufunc.hpp
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
*/