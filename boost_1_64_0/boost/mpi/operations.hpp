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
jc11XjSs1Q68RKQUfDvVFhZ0u58F3rFJaAOeGX7U51xwBZDcd6O4pkgFcIof3mx33LjgKE/GYPt30/ufq8GfAvjsHkQ9jE4+jNLdTgwMpm4Duj1PuOHMR7E8xEYpRd7ug17fXpJ3+/EEMdxWdHQPunw9UIyDfXIaJIixHhj1uR1wqkKuFFKJ5Xnw1kCxXHGkpNWQ9KLX1w0tURxJP6StLYDXn1y+3TpYWZIIKU6qSs0784CwLM27Upt3pWnela55TOGgstJ6zNK6O7V1d5rW3elad2PrkgLNF8BSomr1BzybvuDSLzzPB/oTPwat3xHfau9cDAhvc+rz0UGafmPTxrnBEi/sNknYWnbMcvF2LM7BZju6h111L1KVgOZraaBaAa0DCvDI2usOUu6mLZRV3vskZBESOroPefXMcs0n+RrmMwbauw+5pECvz9yAPoCObg0Oz2s+A1jYp/Lhye5eaLFbc0Ee0FpWN7SqIG7vHvYKxL0CMdZI+MrRJynwYffFSR3DTpHP38tntn0QpQT+wp32Nth2SsJpDJA0K+zfpXC6KxmnQ0k4TXDxNgXhLhNOhwwIhxRO2yw43WfAvMuE0yED8iGF0zYTTvf5TA0ITncRTocEp3hJbJ8PTyXvgxYJp0M6TocUxG0mnO4TiLFG3IexXuICH3ZfnNQxkqB/Hx2Pivsw6kBc4dRCp8Vh/06F053JOB200CkV36Eg3GnC6aAB4aDC6Q4LTnsMmHeacDpoQD6ocLrDhNMeo0CPwulOwumggVPgcT0+fBiqB1oknA7qOB1UEO8w4bTHgLiH6HRQ0Sl1X5zUMdFpj9Bpz3h0CsBsVzjdnozTAQudUvFWBeF2E04HDAgHFE5bLTjdY8C83YTTAQPyAYXTVhNO9/hMDQhOtxNOB3wGsBAlyIePWu2BFgmnAzpOBxTErSac7jEg3kN0OqDolLovTuqY6HSP0Ome8ejUBeE4FU63JeO030KnVLxFQbjNhNN+A8J+hdMWC067DJi3mXDab0Der3DaYsJpl1GgS+F0G+G032cAC1E/fBgcpAtaJJz26zjtVxC3mHDaZUDcRXTar+iUui9O6pjotEvotCsznboBlmaF0uZklPZZyBRLNyn4mk0Y7TPg61MYbbJgtNOAuNmE0T4D7j6F0SYTRjt95gYk7DdhtM9nwNoY6PQF+iiUSh9htE/HaJ+CuMmE0U4D4k6i0j5FpdR9cVLHRKWdQqWdOpU+zg/xLPE34Mka/dD3IXw1XwJE02W12UV20++akdkL7d1/mhkpusKHV5XjEm6bCifyIXQt+ndjKiwz3m/Mhxi8+I7rSPIMznZ7leYGbcdmL3Rg287LfXRodnjNYQIxNAw4GpWi1FPMV4S+4uTeKS2RBD0ljSRDwzocvp85DBqn9F/UgHHjY92aV5QtTHPmUZoL0hC5nNRhl+aKNpfHsIw/YWlrtQM3NC2NLc+jRNUapyU1l8AUmLCU9sDOGUlpDxOt7bmS2huhUv54Snu4N5zSHiZa23MntRfHlKPatJz4THz+Rz9o3/aT/wO2kpPMNWee1Vpz56UYa0UFFluN0nzwHKzwTb76EIP95CQjebXXabWS10KS1Uxe7nBa7GRO9OHNBWXMoi8stQdXag+uND240vXgwh7iYs9iB/HUDtypHbjTdOBO14EbOxgVk5Z8RrBh7tVdGJ5NU8HnJ2yOTWA7eBGKsWUWE9gKJA16fb3C5AgqF7gfXL79wuok0bcfhIyuSHB3MejO0kNRag9FaXooStdDEfaQUMH3vXRp1A4D6kKfzAVABIfxwV8V7N5LB6Gw3OEDIKslvDthexSwPbwHEiwoL05FeXEalBenQ3kxzak=
*/