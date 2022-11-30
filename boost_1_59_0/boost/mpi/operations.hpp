// Copyright (C) 2004 The Trustees of Indiana University.
// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

/** @file operations.hpp
 *
 *  This header provides a mapping from function objects to @c MPI_Op
 *  constants used in MPI collective operations. It also provides
 *  several new function object types not present in the standard @c
 *  <functional> header that have direct mappings to @c MPI_Op.
 */
#ifndef BOOST_MPI_IS_MPI_OP_HPP
#define BOOST_MPI_IS_MPI_OP_HPP

#include <boost/mpi/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/core/uncaught_exceptions.hpp>
#include <functional>

namespace boost { namespace mpi {

template<typename Op, typename T> struct is_mpi_op;

/**
 * @brief Determine if a function object type is commutative.
 *
 * This trait determines if an operation @c Op is commutative when
 * applied to values of type @c T. Parallel operations such as @c
 * reduce and @c prefix_sum can be implemented more efficiently with
 * commutative operations. To mark an operation as commutative, users
 * should specialize @c is_commutative and derive from the class @c
 * mpl::true_.
 */
template<typename Op, typename T>
struct is_commutative : public mpl::false_ { };

/**************************************************************************
 * Function objects for MPI operations not in <functional> header         *
 **************************************************************************/

/**
 *  @brief Compute the maximum of two values.
 *
 *  This binary function object computes the maximum of the two values
 *  it is given. When used with MPI and a type @c T that has an
 *  associated, built-in MPI data type, translates to @c MPI_MAX.
 */
template<typename T>
struct maximum
{
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef T result_type;
  /** @returns the maximum of x and y. */
  const T& operator()(const T& x, const T& y) const
  {
    return x < y? y : x;
  }
};

/**
 *  @brief Compute the minimum of two values.
 *
 *  This binary function object computes the minimum of the two values
 *  it is given. When used with MPI and a type @c T that has an
 *  associated, built-in MPI data type, translates to @c MPI_MIN.
 */
template<typename T>
struct minimum
{
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef T result_type;
  /** @returns the minimum of x and y. */
  const T& operator()(const T& x, const T& y) const
  {
    return x < y? x : y;
  }
};


/**
 *  @brief Compute the bitwise AND of two integral values.
 *
 *  This binary function object computes the bitwise AND of the two
 *  values it is given. When used with MPI and a type @c T that has an
 *  associated, built-in MPI data type, translates to @c MPI_BAND.
 */
template<typename T>
struct bitwise_and
{
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef T result_type;
  /** @returns @c x & y. */
  T operator()(const T& x, const T& y) const
  {
    return x & y;
  }
};

/**
 *  @brief Compute the bitwise OR of two integral values.
 *
 *  This binary function object computes the bitwise OR of the two
 *  values it is given. When used with MPI and a type @c T that has an
 *  associated, built-in MPI data type, translates to @c MPI_BOR.
 */
template<typename T>
struct bitwise_or
{
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef T result_type;
  /** @returns the @c x | y. */
  T operator()(const T& x, const T& y) const
  {
    return x | y;
  }
};

/**
 *  @brief Compute the logical exclusive OR of two integral values.
 *
 *  This binary function object computes the logical exclusive of the
 *  two values it is given. When used with MPI and a type @c T that has
 *  an associated, built-in MPI data type, translates to @c MPI_LXOR.
 */
template<typename T>
struct logical_xor
{
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef T result_type;
  /** @returns the logical exclusive OR of x and y. */
  T operator()(const T& x, const T& y) const
  {
    return (x || y) && !(x && y);
  }
};

/**
 *  @brief Compute the bitwise exclusive OR of two integral values.
 *
 *  This binary function object computes the bitwise exclusive OR of
 *  the two values it is given. When used with MPI and a type @c T that
 *  has an associated, built-in MPI data type, translates to @c
 *  MPI_BXOR.
 */
template<typename T>
struct bitwise_xor
{
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef T result_type;
  /** @returns @c x ^ y. */
  T operator()(const T& x, const T& y) const
  {
    return x ^ y;
  }
};

/**************************************************************************
 * MPI_Op queries                                                         *
 **************************************************************************/

/**
 *  @brief Determine if a function object has an associated @c MPI_Op.
 *
 *  This trait determines if a function object type @c Op, when used
 *  with argument type @c T, has an associated @c MPI_Op. If so, @c
 *  is_mpi_op<Op,T> will derive from @c mpl::false_ and will
 *  contain a static member function @c op that takes no arguments but
 *  returns the associated @c MPI_Op value. For instance, @c
 *  is_mpi_op<std::plus<int>,int>::op() returns @c MPI_SUM.
 *
 *  Users may specialize @c is_mpi_op for any other class templates
 *  that map onto operations that have @c MPI_Op equivalences, such as
 *  bitwise OR, logical and, or maximum. However, users are encouraged
 *  to use the standard function objects in the @c functional and @c
 *  boost/mpi/operations.hpp headers whenever possible. For
 *  function objects that are class templates with a single template
 *  parameter, it may be easier to specialize @c is_builtin_mpi_op.
 */
template<typename Op, typename T>
struct is_mpi_op : public mpl::false_ { };

/// INTERNAL ONLY
template<typename T>
struct is_mpi_op<maximum<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_floating_point_datatype<T> >
{
  static MPI_Op op() { return MPI_MAX; }
};

/// INTERNAL ONLY
template<typename T>
struct is_mpi_op<minimum<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_floating_point_datatype<T> >
{
  static MPI_Op op() { return MPI_MIN; }
};

/// INTERNAL ONLY
template<typename T>
 struct is_mpi_op<std::plus<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_floating_point_datatype<T>,
                           is_mpi_complex_datatype<T> >
{
  static MPI_Op op() { return MPI_SUM; }
};

/// INTERNAL ONLY
template<typename T>
 struct is_mpi_op<std::multiplies<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_floating_point_datatype<T>,
                           is_mpi_complex_datatype<T> >
{
  static MPI_Op op() { return MPI_PROD; }
};

/// INTERNAL ONLY
template<typename T>
 struct is_mpi_op<std::logical_and<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_logical_datatype<T> >
{
  static MPI_Op op() { return MPI_LAND; }
};

/// INTERNAL ONLY
template<typename T>
 struct is_mpi_op<std::logical_or<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_logical_datatype<T> >
{
  static MPI_Op op() { return MPI_LOR; }
};

/// INTERNAL ONLY
template<typename T>
 struct is_mpi_op<logical_xor<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_logical_datatype<T> >
{
  static MPI_Op op() { return MPI_LXOR; }
};

/// INTERNAL ONLY
template<typename T>
 struct is_mpi_op<bitwise_and<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_byte_datatype<T> >
{
  static MPI_Op op() { return MPI_BAND; }
};

/// INTERNAL ONLY
template<typename T>
 struct is_mpi_op<bitwise_or<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_byte_datatype<T> >
{
  static MPI_Op op() { return MPI_BOR; }
};

/// INTERNAL ONLY
template<typename T>
 struct is_mpi_op<bitwise_xor<T>, T>
  : public boost::mpl::or_<is_mpi_integer_datatype<T>,
                           is_mpi_byte_datatype<T> >
{
  static MPI_Op op() { return MPI_BXOR; }
};

namespace detail {
  // A helper class used to create user-defined MPI_Ops
  template<typename Op, typename T>
  class user_op
  {
  public:
    user_op()
    {
      BOOST_MPI_CHECK_RESULT(MPI_Op_create,
                             (&user_op<Op, T>::perform,
                              is_commutative<Op, T>::value,
                              &mpi_op));
    }

    ~user_op()
    {
      if (boost::core::uncaught_exceptions() > 0) {
        // Ignore failure cases: there are obviously other problems
        // already, and we don't want to cause program termination if
        // MPI_Op_free fails.
        MPI_Op_free(&mpi_op);
      } else {
        BOOST_MPI_CHECK_RESULT(MPI_Op_free, (&mpi_op));
      }
    }

    MPI_Op& get_mpi_op()
    {
      return mpi_op;
    }

  private:
    MPI_Op mpi_op;

    static void BOOST_MPI_CALLING_CONVENTION perform(void* vinvec, void* voutvec, int* plen, MPI_Datatype*)
    {
      T* invec = static_cast<T*>(vinvec);
      T* outvec = static_cast<T*>(voutvec);
      Op op;
      std::transform(invec, invec + *plen, outvec, outvec, op);
    }
  };

} // end namespace detail

} } // end namespace boost::mpi

#endif // BOOST_MPI_GET_MPI_OP_HPP

/* operations.hpp
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
*/