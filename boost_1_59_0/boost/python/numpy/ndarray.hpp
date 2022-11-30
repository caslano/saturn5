// Copyright Jim Bosch 2010-2012.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_numpy_ndarray_hpp_
#define boost_python_numpy_ndarray_hpp_

/**
 *  @brief Object manager and various utilities for numpy.ndarray.
 */

#include <boost/python.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/python/detail/type_traits.hpp>
#include <boost/python/numpy/numpy_object_mgr_traits.hpp>
#include <boost/python/numpy/dtype.hpp>
#include <boost/python/numpy/config.hpp>

#include <vector>

namespace boost { namespace python { namespace numpy {

/**
 *  @brief A boost.python "object manager" (subclass of object) for numpy.ndarray.
 *
 *  @todo This could have a lot more functionality (like boost::python::numeric::array).
 *        Right now all that exists is what was needed to move raw data between C++ and Python.
 */
 
class BOOST_NUMPY_DECL ndarray : public object
{

  /**
   *  @brief An internal struct that's byte-compatible with PyArrayObject.
   *
   *  This is just a hack to allow inline access to this stuff while hiding numpy/arrayobject.h
   *  from the user.
   */
  struct array_struct 
  {
    PyObject_HEAD
    char * data;
    int nd;
    Py_intptr_t * shape;
    Py_intptr_t * strides;
    PyObject * base;
    PyObject * descr;
    int flags;
    PyObject * weakreflist;
  };
  
  /// @brief Return the held Python object as an array_struct.
  array_struct * get_struct() const { return reinterpret_cast<array_struct*>(this->ptr()); }

public:
  
  /**
   *  @brief Enum to represent (some) of Numpy's internal flags.
   *
   *  These don't match the actual Numpy flag values; we can't get those without including 
   *  numpy/arrayobject.h or copying them directly.  That's very unfortunate.
   *
   *  @todo I'm torn about whether this should be an enum.  It's very convenient to not
   *        make these simple integer values for overloading purposes, but the need to
   *        define every possible combination and custom bitwise operators is ugly.
   */
  enum bitflag 
  {
    NONE=0x0, C_CONTIGUOUS=0x1, F_CONTIGUOUS=0x2, V_CONTIGUOUS=0x1|0x2, 
    ALIGNED=0x4, WRITEABLE=0x8, BEHAVED=0x4|0x8,
    CARRAY_RO=0x1|0x4, CARRAY=0x1|0x4|0x8, CARRAY_MIS=0x1|0x8,
    FARRAY_RO=0x2|0x4, FARRAY=0x2|0x4|0x8, FARRAY_MIS=0x2|0x8,
    UPDATE_ALL=0x1|0x2|0x4, VARRAY=0x1|0x2|0x8, ALL=0x1|0x2|0x4|0x8
  };

  BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(ndarray, object);

  /// @brief Return a view of the scalar with the given dtype.
  ndarray view(dtype const & dt) const;
    
  /// @brief Copy the array, cast to a specified type.
  ndarray astype(dtype const & dt) const;

  /// @brief Copy the scalar (deep for all non-object fields).
  ndarray copy() const;

  /// @brief Return the size of the nth dimension. raises IndexError if k not in [-get_nd() : get_nd()-1 ]
  Py_intptr_t shape(int n) const;

  /// @brief Return the stride of the nth dimension. raises IndexError if k not in [-get_nd() : get_nd()-1]
  Py_intptr_t strides(int n) const;
    
  /**
   *  @brief Return the array's raw data pointer.
   *
   *  This returns char so stride math works properly on it.  It's pretty much
   *  expected that the user will have to reinterpret_cast it.
   */
  char * get_data() const { return get_struct()->data; }

  /// @brief Return the array's data-type descriptor object.
  dtype get_dtype() const;
  
  /// @brief Return the object that owns the array's data, or None if the array owns its own data.
  object get_base() const;
  
  /// @brief Set the object that owns the array's data.  Use with care.
  void set_base(object const & base);
  
  /// @brief Return the shape of the array as an array of integers (length == get_nd()).
  Py_intptr_t const * get_shape() const { return get_struct()->shape; }
  
  /// @brief Return the stride of the array as an array of integers (length == get_nd()).
  Py_intptr_t const * get_strides() const { return get_struct()->strides; }
  
  /// @brief Return the number of array dimensions.
  int get_nd() const { return get_struct()->nd; }
  
  /// @brief Return the array flags.
  bitflag get_flags() const;
  
  /// @brief Reverse the dimensions of the array.
  ndarray transpose() const;
  
  /// @brief Eliminate any unit-sized dimensions.
  ndarray squeeze() const;
  
  /// @brief Equivalent to self.reshape(*shape) in Python.
  ndarray reshape(python::tuple const & shape) const;
  
  /**
   *  @brief If the array contains only a single element, return it as an array scalar; otherwise return
   *         the array.
   *
   *  @internal This is simply a call to PyArray_Return();
   */
  object scalarize() const;
};

/**
 *  @brief Construct a new array with the given shape and data type, with data initialized to zero.
 */
BOOST_NUMPY_DECL ndarray zeros(python::tuple const & shape, dtype const & dt);
BOOST_NUMPY_DECL ndarray zeros(int nd, Py_intptr_t const * shape, dtype const & dt);

/**
 *  @brief Construct a new array with the given shape and data type, with data left uninitialized.
 */
BOOST_NUMPY_DECL ndarray empty(python::tuple const & shape, dtype const & dt);
BOOST_NUMPY_DECL ndarray empty(int nd, Py_intptr_t const * shape, dtype const & dt);

/**
 *  @brief Construct a new array from an arbitrary Python sequence.
 *
 *  @todo This does't seem to handle ndarray subtypes the same way that "numpy.array" does in Python.
 */
BOOST_NUMPY_DECL ndarray array(object const & obj);
BOOST_NUMPY_DECL ndarray array(object const & obj, dtype const & dt);

namespace detail 
{

BOOST_NUMPY_DECL ndarray from_data_impl(void * data,
					dtype const & dt,
					std::vector<Py_intptr_t> const & shape,
					std::vector<Py_intptr_t> const & strides,
					object const & owner,
					bool writeable);

template <typename Container>
ndarray from_data_impl(void * data,
		       dtype const & dt,
		       Container shape,
		       Container strides,
		       object const & owner,
		       bool writeable,
		       typename boost::enable_if< boost::python::detail::is_integral<typename Container::value_type> >::type * enabled = NULL)
{
  std::vector<Py_intptr_t> shape_(shape.begin(),shape.end());
  std::vector<Py_intptr_t> strides_(strides.begin(), strides.end());
  return from_data_impl(data, dt, shape_, strides_, owner, writeable);    
}

BOOST_NUMPY_DECL ndarray from_data_impl(void * data,
					dtype const & dt,
					object const & shape,
					object const & strides,
					object const & owner,
					bool writeable);

} // namespace boost::python::numpy::detail

/**
 *  @brief Construct a new ndarray object from a raw pointer.
 *
 *  @param[in] data    Raw pointer to the first element of the array.
 *  @param[in] dt      Data type descriptor.  Often retrieved with dtype::get_builtin().
 *  @param[in] shape   Shape of the array as STL container of integers; must have begin() and end().
 *  @param[in] strides Shape of the array as STL container of integers; must have begin() and end().
 *  @param[in] owner   An arbitray Python object that owns that data pointer.  The array object will
 *                     keep a reference to the object, and decrement it's reference count when the
 *                     array goes out of scope.  Pass None at your own peril.
 *
 *  @todo Should probably take ranges of iterators rather than actual container objects.
 */
template <typename Container>
inline ndarray from_data(void * data,
			 dtype const & dt,
			 Container shape,
			 Container strides,
			 python::object const & owner)
{
  return numpy::detail::from_data_impl(data, dt, shape, strides, owner, true);
}    

/**
 *  @brief Construct a new ndarray object from a raw pointer.
 *
 *  @param[in] data    Raw pointer to the first element of the array.
 *  @param[in] dt      Data type descriptor.  Often retrieved with dtype::get_builtin().
 *  @param[in] shape   Shape of the array as STL container of integers; must have begin() and end().
 *  @param[in] strides Shape of the array as STL container of integers; must have begin() and end().
 *  @param[in] owner   An arbitray Python object that owns that data pointer.  The array object will
 *                     keep a reference to the object, and decrement it's reference count when the
 *                     array goes out of scope.  Pass None at your own peril.
 *
 *  This overload takes a const void pointer and sets the "writeable" flag of the array to false.
 *
 *  @todo Should probably take ranges of iterators rather than actual container objects.
 */
template <typename Container>
inline ndarray from_data(void const * data,
			 dtype const & dt,
			 Container shape,
			 Container strides,
			 python::object const & owner)
{
  return numpy::detail::from_data_impl(const_cast<void*>(data), dt, shape, strides, owner, false);
}    

/**
 *  @brief Transform an arbitrary object into a numpy array with the given requirements.
 *
 *  @param[in] obj     An arbitrary python object to convert.  Arrays that meet the requirements
 *                     will be passed through directly.
 *  @param[in] dt      Data type descriptor.  Often retrieved with dtype::get_builtin().
 *  @param[in] nd_min  Minimum number of dimensions.
 *  @param[in] nd_max  Maximum number of dimensions.
 *  @param[in] flags   Bitwise OR of flags specifying additional requirements.
 */
BOOST_NUMPY_DECL ndarray from_object(object const & obj,
				     dtype const & dt,
				     int nd_min,
				     int nd_max,
				     ndarray::bitflag flags=ndarray::NONE);

BOOST_NUMPY_DECL inline ndarray from_object(object const & obj,
					    dtype const & dt,
					    int nd,
					    ndarray::bitflag flags=ndarray::NONE)
{
  return from_object(obj, dt, nd, nd, flags);
}

BOOST_NUMPY_DECL inline ndarray from_object(object const & obj,
					    dtype const & dt,
					    ndarray::bitflag flags=ndarray::NONE)
{
  return from_object(obj, dt, 0, 0, flags);
}

BOOST_NUMPY_DECL ndarray from_object(object const & obj,
				     int nd_min,
				     int nd_max,
				     ndarray::bitflag flags=ndarray::NONE);

BOOST_NUMPY_DECL inline ndarray from_object(object const & obj,
					    int nd,
					    ndarray::bitflag flags=ndarray::NONE)
{
  return from_object(obj, nd, nd, flags);
}

BOOST_NUMPY_DECL inline ndarray from_object(object const & obj,
					    ndarray::bitflag flags=ndarray::NONE)
{
  return from_object(obj, 0, 0, flags);
}

BOOST_NUMPY_DECL inline ndarray::bitflag operator|(ndarray::bitflag a,
						   ndarray::bitflag b)
{
  return ndarray::bitflag(int(a) | int(b));
}

BOOST_NUMPY_DECL inline ndarray::bitflag operator&(ndarray::bitflag a,
						   ndarray::bitflag b)
{
  return ndarray::bitflag(int(a) & int(b));
}

} // namespace boost::python::numpy

namespace converter 
{

NUMPY_OBJECT_MANAGER_TRAITS(numpy::ndarray);

}}} // namespace boost::python::converter

#endif

/* ndarray.hpp
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
*/