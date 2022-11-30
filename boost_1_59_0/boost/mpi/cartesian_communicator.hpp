//          Copyright Alain Miniussi 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Authors: Alain Miniussi

/** @file cartesian_communicator.hpp
 *
 *  This header defines facilities to support MPI communicators with
 *  cartesian topologies.
 *  If known at compiled time, the dimension of the implied grid 
 *  can be statically enforced, through the templatized communicator 
 *  class. Otherwise, a non template, dynamic, base class is provided.
 *  
 */
#ifndef BOOST_MPI_CARTESIAN_COMMUNICATOR_HPP
#define BOOST_MPI_CARTESIAN_COMMUNICATOR_HPP

#include <boost/mpi/communicator.hpp>

#include <vector>
#include <utility>
#include <iostream>
#include <utility>
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif // BOOST_NO_CXX11_HDR_INITIALIZER_LIST

// Headers required to implement cartesian topologies
#include <boost/shared_array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>

namespace boost { namespace mpi {

/**
 * @brief Specify the size and periodicity of the grid in a single dimension.
 *
 * POD lightweight object.
 */
struct cartesian_dimension {
  /** The size of the grid n this dimension. */
  int size;
  /** Is the grid periodic in this dimension. */
  bool periodic;
  
  cartesian_dimension(int sz = 0, bool p = false) : size(sz), periodic(p) {}
  
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & size & periodic;
  }

};

template <>
struct is_mpi_datatype<cartesian_dimension> : mpl::true_ { };

/**
 * @brief Test if the dimensions values are identical.
 */
inline
bool
operator==(cartesian_dimension const& d1, cartesian_dimension const& d2) {
  return &d1 == &d2 || (d1.size == d2.size && d1.periodic == d2.periodic);
}

/**
 * @brief Test if the dimension values are different.
 */
inline
bool
operator!=(cartesian_dimension const& d1, cartesian_dimension const& d2) {
  return !(d1 == d2);
}

/**
 * @brief Pretty printing of a cartesian dimension (size, periodic)
 */
std::ostream& operator<<(std::ostream& out, cartesian_dimension const& d);

/**
 * @brief Describe the topology of a cartesian grid.
 * 
 * Behave mostly like a sequence of @c cartesian_dimension with the notable 
 * exception that its size is fixed.
 * This is a lightweight object, so that any constructor that could be considered 
 * missing could be replaced with a function (move constructor provided when supported).
 */
class BOOST_MPI_DECL cartesian_topology 
  : private std::vector<cartesian_dimension> {
  friend class cartesian_communicator;
  typedef std::vector<cartesian_dimension> super;
 public:
  /** 
   * Retrieve a specific dimension.
   */
  using super::operator[];
  /** 
   * @brief Topology dimentionality.
   */
  using super::size;
  using super::begin;
  using super::end;
  using super::swap;

#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
  cartesian_topology() = delete;
#endif
#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
  cartesian_topology(cartesian_topology const&) = default;
  cartesian_topology& operator=(cartesian_topology const&) = default;
  // There is apparently no macro for checking the support of move constructor.
  // Assume that defaulted function is close enough.
#if !defined(BOOST_NO_CXX11_DEFAULTED_MOVES)
  cartesian_topology(cartesian_topology&& other) : super(other) {}
  cartesian_topology& operator=(cartesian_topology&& other) { 
    stl().swap(other.stl());
    return *this;
  }
#endif
  ~cartesian_topology() = default;
#endif
  /**
   * @brief Create a N dimension space.
   * Each dimension is initialized as non periodic of size 0.
   */
  cartesian_topology(int ndim) 
    : super(ndim) {}
  
  /**
   * @brief Use the provided dimensions specification as initial values.
   */
  cartesian_topology(std::vector<cartesian_dimension> const& dims) 
    : super(dims) {}

  /**
   * @brief Use dimensions specification provided in the sequence container as initial values.
   * #param dims must be a sequence container.
   */  
  template<class InitArr>
  explicit cartesian_topology(InitArr dims)
    : super(0) {
    BOOST_FOREACH(cartesian_dimension const& d, dims) {
      push_back(d);
    }
  }
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  /**
   * @brief Use dimensions specification provided in the initialization list as initial values.
   * #param dims can be of the form { dim_1, false}, .... {dim_n, true}
   */    
  explicit cartesian_topology(std::initializer_list<cartesian_dimension> dims)
    : super(dims) {}
#endif
  /**
   * @brief Use dimensions specification provided in the array.
   * #param dims can be of the form { dim_1, false}, .... {dim_n, true}
   */    
  template<int NDIM>
  explicit cartesian_topology(cartesian_dimension (&dims)[NDIM])
    : super(dims, dims+NDIM) {}

  /**
   * @brief Use dimensions specification provided in the input ranges
   * The ranges do not need to be the same size. If the sizes are different, 
   * the missing values will be complete with zeros of the dim and assumed non periodic.
   * @param dim_rg     the dimensions, values must convert to integers.
   * @param period_rg  the periodicities, values must convert to booleans.
   * #param dims can be of the form { dim_1, false}, .... {dim_n, true}
   */    
  template<class DimRg, class PerRg>
  cartesian_topology(DimRg const& dim_rg, PerRg const& period_rg) 
    : super(0) {
    BOOST_FOREACH(int d, dim_rg) {
      super::push_back(cartesian_dimension(d));
    }
    super::iterator it = begin();
    BOOST_FOREACH(bool p, period_rg) {
      if (it < end()) {
        it->periodic = p;
      } else {
        push_back(cartesian_dimension(0,p));
      }
      ++it;
    }
  }

  
  /**
   * @brief Iterator based initializer.
   * Will use the first n iterated values. 
   * Both iterators can be single pass.
   * @param dit dimension iterator, value must convert to integer type.
   * @param pit periodicity iterator, value must convert to booleans..
   */
  template<class DimIter, class PerIter>
  cartesian_topology(DimIter dit, PerIter pit, int n) 
    : super(n) {
    for(int i = 0; i < n; ++i) {
      (*this)[i] = cartesian_dimension(*dit++, *pit++);
    }
  }
  
  /**
   * Export as an stl sequence.
   */
  std::vector<cartesian_dimension>& stl() { return *this; }
  /**
   * Export as an stl sequence.
   */
  std::vector<cartesian_dimension> const& stl() const{ return *this; }
  /** 
   * Split the topology in two sequences of sizes and periodicities.
   */
  void split(std::vector<int>& dims, std::vector<bool>& periodics) const;
};

inline
bool
operator==(cartesian_topology const& t1, cartesian_topology const& t2) {
  return t1.stl() == t2.stl();
}

inline
bool
operator!=(cartesian_topology const& t1, cartesian_topology const& t2) {
  return t1.stl() != t2.stl();
}

/**
 * @brief Pretty printing of a cartesian topology
 */
std::ostream& operator<<(std::ostream& out, cartesian_topology const& t);

/**
 * @brief An MPI communicator with a cartesian topology.
 *
 * A @c cartesian_communicator is a communicator whose topology is
 * expressed as a grid. Cartesian communicators have the same
 * functionality as (intra)communicators, but also allow one to query
 * the relationships among processes and the properties of the grid.
 */
class BOOST_MPI_DECL cartesian_communicator : public communicator
{
  friend class communicator;

  /**
   * INTERNAL ONLY
   *
   * Construct a cartesian communicator given a shared pointer to the
   * underlying MPI_Comm (which must have a cartesian topology).
   * This operation is used for "casting" from a communicator to 
   * a cartesian communicator.
   */
  explicit cartesian_communicator(const shared_ptr<MPI_Comm>& comm_ptr)
    : communicator()
  {
    this->comm_ptr = comm_ptr;
    BOOST_ASSERT(has_cartesian_topology());    
  }

public:
  /**
   * Build a new Boost.MPI cartesian communicator based on the MPI
   * communicator @p comm with cartesian topology.
   *
   * @p comm may be any valid MPI communicator. If @p comm is
   * MPI_COMM_NULL, an empty communicator (that cannot be used for
   * communication) is created and the @p kind parameter is
   * ignored. Otherwise, the @p kind parameter determines how the
   * Boost.MPI communicator will be related to @p comm:
   *
   *   - If @p kind is @c comm_duplicate, duplicate @c comm to create
   *   a new communicator. This new communicator will be freed when
   *   the Boost.MPI communicator (and all copies of it) is
   *   destroyed. This option is only permitted if the underlying MPI
   *   implementation supports MPI 2.0; duplication of
   *   intercommunicators is not available in MPI 1.x.
   *
   *   - If @p kind is @c comm_take_ownership, take ownership of @c
   *   comm. It will be freed automatically when all of the Boost.MPI
   *   communicators go out of scope.
   *
   *   - If @p kind is @c comm_attach, this Boost.MPI communicator
   *   will reference the existing MPI communicator @p comm but will
   *   not free @p comm when the Boost.MPI communicator goes out of
   *   scope. This option should only be used when the communicator is
   *   managed by the user.
   */
  cartesian_communicator(const MPI_Comm& comm, comm_create_kind kind)
    : communicator(comm, kind)
  { 
    BOOST_ASSERT(has_cartesian_topology());
  }

  /**
   *  Create a new communicator whose topology is described by the
   *  given cartesian. The indices of the vertices in the cartesian will be
   *  assumed to be the ranks of the processes within the
   *  communicator. There may be fewer vertices in the cartesian than
   *  there are processes in the communicator; in this case, the
   *  resulting communicator will be a NULL communicator.
   *
   *  @param comm The communicator that the new, cartesian communicator
   *  will be based on. 
   * 
   *  @param dims the cartesian dimension of the new communicator. The size indicate 
   *  the number of dimension. Some dimensions be set to zero, in which case
   *  the corresponding dimension value is left to the system.
   *  
   *  @param reorder Whether MPI is permitted to re-order the process
   *  ranks within the returned communicator, to better optimize
   *  communication. If false, the ranks of each process in the
   *  returned process will match precisely the rank of that process
   *  within the original communicator.
   */
  cartesian_communicator(const communicator&       comm,
                         const cartesian_topology& dims,
                         bool                      reorder = false);
  
  /**
   * Create a new cartesian communicator whose topology is a subset of
   * an existing cartesian cimmunicator.
   * @param comm the original communicator.
   * @param keep and array containiing the dimension to keep from the existing 
   * communicator.
   */
  cartesian_communicator(const cartesian_communicator& comm,
                         const std::vector<int>&       keep );
    
  using communicator::rank;

  /** 
   * Retrive the number of dimension of the underlying toppology.
   */
  int ndims() const;
  
  /**
   * Return the rank of the process at the given coordinates.
   * @param coords the coordinates. the size must match the communicator's topology.
   */
  int rank(const std::vector<int>& coords) const;
  /**
   * Return the rank of the source and target destination process through a shift.
   * @param dim the dimension in which the shift takes place. 0 <= dim <= ndim().
   * @param disp the shift displacement, can be positive (upward) or negative (downward).
   */
  std::pair<int, int> shifted_ranks(int dim, int disp) const;
  /**
   * Provides the coordinates of the process with the given rank.
   * @param rk the ranks in this communicator.
   * @returns the coordinates.
   */
  std::vector<int> coordinates(int rk) const;
  /**
   * Retrieve the topology and coordinates of this process in the grid.
   *
   */
  void topology( cartesian_topology&  dims, std::vector<int>& coords ) const;
  /**
   * Retrieve the topology of the grid.
   *
   */
  cartesian_topology topology() const;
};

/**
 * Given en number of processes, and a partially filled sequence 
 * of dimension, try to complete the dimension sequence.
 * @param nb_proc the numer of mpi processes.fill a sequence of dimension.
 * @param dims a sequence of positive or null dimensions. Non zero dimension 
 *  will be left untouched.
 */
std::vector<int>& cartesian_dimensions(int nb_proc, std::vector<int>&  dims);

} } // end namespace boost::mpi

#endif // BOOST_MPI_CARTESIAN_COMMUNICATOR_HPP

/* cartesian_communicator.hpp
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
*/