// Copyright Jim Bosch 2010-2012.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_numpy_dtype_hpp_
#define boost_python_numpy_dtype_hpp_

/**
 *  @file boost/python/numpy/dtype.hpp
 *  @brief Object manager for Python's numpy.dtype class.
 */

#include <boost/python.hpp>
#include <boost/python/numpy/config.hpp>
#include <boost/python/numpy/numpy_object_mgr_traits.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/python/detail/type_traits.hpp>

namespace boost { namespace python { namespace numpy {

/**
 *  @brief A boost.python "object manager" (subclass of object) for numpy.dtype.
 *
 *  @todo This could have a lot more interesting accessors.
 */
class BOOST_NUMPY_DECL dtype : public object {
  static python::detail::new_reference convert(object::object_cref arg, bool align);
public:

  /// @brief Convert an arbitrary Python object to a data-type descriptor object.
  template <typename T>
  explicit dtype(T arg, bool align=false) : object(convert(arg, align)) {}

  /**
   *  @brief Get the built-in numpy dtype associated with the given scalar template type.
   *
   *  This is perhaps the most useful part of the numpy API: it returns the dtype object
   *  corresponding to a built-in C++ type.  This should work for any integer or floating point
   *  type supported by numpy, and will also work for std::complex if 
   *  sizeof(std::complex<T>) == 2*sizeof(T).
   *
   *  It can also be useful for users to add explicit specializations for POD structs
   *  that return field-based dtypes.
   */
  template <typename T> static dtype get_builtin();

  /// @brief Return the size of the data type in bytes.
  int get_itemsize() const;

  /**
   *  @brief Compare two dtypes for equivalence.
   *
   *  This is more permissive than equality tests.  For instance, if long and int are the same
   *  size, the dtypes corresponding to each will be equivalent, but not equal.
   */
  friend BOOST_NUMPY_DECL bool equivalent(dtype const & a, dtype const & b);

  /**
   *  @brief Register from-Python converters for NumPy's built-in array scalar types.
   *
   *  This is usually called automatically by initialize(), and shouldn't be called twice
   *  (doing so just adds unused converters to the Boost.Python registry).
   */
  static void register_scalar_converters();

  BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(dtype, object);

};

BOOST_NUMPY_DECL bool equivalent(dtype const & a, dtype const & b);

namespace detail
{

template <int bits, bool isUnsigned> dtype get_int_dtype();

template <int bits> dtype get_float_dtype();

template <int bits> dtype get_complex_dtype();

template <typename T, bool isInt=boost::is_integral<T>::value>
struct builtin_dtype;

template <typename T>
struct builtin_dtype<T,true> {
  static dtype get() { return get_int_dtype< 8*sizeof(T), boost::is_unsigned<T>::value >(); }
};

template <>
struct BOOST_NUMPY_DECL builtin_dtype<bool,true> {
  static dtype get();
};

template <typename T>
struct builtin_dtype<T,false> {
  static dtype get() { return get_float_dtype< 8*sizeof(T) >(); }
};

template <typename T>
struct builtin_dtype< std::complex<T>, false > {
  static dtype get() { return get_complex_dtype< 16*sizeof(T) >(); }  
};

} // namespace detail

template <typename T>
inline dtype dtype::get_builtin() { return detail::builtin_dtype<T>::get(); }

} // namespace boost::python::numpy

namespace converter {
NUMPY_OBJECT_MANAGER_TRAITS(numpy::dtype);
}}} // namespace boost::python::converter

#endif

/* dtype.hpp
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
*/