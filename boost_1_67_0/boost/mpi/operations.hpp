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