// Copyright (C) 2007 Trustees of Indiana University

// Authors: Douglas Gregor
//          Andrew Lumsdaine

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file group.hpp
 *
 *  This header defines the @c group class, which allows one to
 *  manipulate and query groups of processes.
 */
#ifndef BOOST_MPI_GROUP_HPP
#define BOOST_MPI_GROUP_HPP

#include <boost/mpi/exception.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>
#include <vector>

namespace boost { namespace mpi {

/**
 * @brief A @c group is a representation of a subset of the processes
 * within a @c communicator.
 *
 * The @c group class allows one to create arbitrary subsets of the
 * processes within a communicator. One can compute the union,
 * intersection, or difference of two groups, or create new groups by
 * specifically including or excluding certain processes. Given a
 * group, one can create a new communicator containing only the
 * processes in that group.
 */
class BOOST_MPI_DECL group
{
public:
  /**
   * @brief Constructs an empty group.
   */
  group() : group_ptr() { }

  /**
   * @brief Constructs a group from an @c MPI_Group.
   *
   * This routine allows one to construct a Boost.MPI @c group from a
   * C @c MPI_Group. The @c group object can (optionally) adopt the @c
   * MPI_Group, after which point the @c group object becomes
   * responsible for freeing the @c MPI_Group when the last copy of @c
   * group disappears.
   *
   * @param in_group The @c MPI_Group used to construct this @c group.
   *
   * @param adopt Whether the @c group should adopt the @c
   * MPI_Group. When true, the @c group object (or one of its copies)
   * will free the group (via @c MPI_Comm_free) when the last copy is
   * destroyed. Otherwise, the user is responsible for calling @c
   * MPI_Group_free.
   */
  group(const MPI_Group& in_group, bool adopt);

  /**
   * @brief Determine the rank of the calling process in the group.
   * 
   * This routine is equivalent to @c MPI_Group_rank.
   *
   * @returns The rank of the calling process in the group, which will
   * be a value in [0, size()). If the calling process is not in the
   * group, returns an empty value.
   */
  optional<int> rank() const;

  /**
   * @brief Determine the number of processes in the group.
   *
   * This routine is equivalent to @c MPI_Group_size.
   *
   * @returns The number of processes in the group.
   */
  int size() const;

  /**
   * @brief Translates the ranks from one group into the ranks of the
   * same processes in another group.
   *
   * This routine translates each of the integer rank values in the
   * iterator range @c [first, last) from the current group into rank
   * values of the corresponding processes in @p to_group. The
   * corresponding rank values are written via the output iterator @c
   * out. When there is no correspondence between a rank in the
   * current group and a rank in @c to_group, the value @c
   * MPI_UNDEFINED is written to the output iterator.
   *
   * @param first Beginning of the iterator range of ranks in the
   * current group.
   *
   * @param last Past the end of the iterator range of ranks in the
   * current group.
   *
   * @param to_group The group that we are translating ranks to.
   *
   * @param out The output iterator to which the translated ranks will
   * be written.
   *
   * @returns the output iterator, which points one step past the last
   * rank written.
   */
  template<typename InputIterator, typename OutputIterator>
  OutputIterator translate_ranks(InputIterator first, InputIterator last,
                                 const group& to_group, OutputIterator out);

  /**
   * @brief Determines whether the group is non-empty.
   *
   * @returns True if the group is not empty, false if it is empty.
   */
  operator bool() const { return (bool)group_ptr; }

  /**
   * @brief Retrieves the underlying @c MPI_Group associated with this
   * group.
   *
   * @returns The @c MPI_Group handle manipulated by this object. If
   * this object represents the empty group, returns @c
   * MPI_GROUP_EMPTY.
   */
  operator MPI_Group() const
  {
    if (group_ptr)
      return *group_ptr;
    else
      return MPI_GROUP_EMPTY;
  }

  /**
   *  @brief Creates a new group including a subset of the processes
   *  in the current group.
   *
   *  This routine creates a new @c group which includes only those
   *  processes in the current group that are listed in the integer
   *  iterator range @c [first, last). Equivalent to @c
   *  MPI_Group_incl.
   *
   *  @c first The beginning of the iterator range of ranks to include.
   *
   *  @c last Past the end of the iterator range of ranks to include.
   *
   *  @returns A new group containing those processes with ranks @c
   *  [first, last) in the current group.
   */
  template<typename InputIterator>
  group include(InputIterator first, InputIterator last);

  /**
   *  @brief Creates a new group from all of the processes in the
   *  current group, exluding a specific subset of the processes.
   *
   *  This routine creates a new @c group which includes all of the
   *  processes in the current group except those whose ranks are
   *  listed in the integer iterator range @c [first,
   *  last). Equivalent to @c MPI_Group_excl.
   *
   *  @c first The beginning of the iterator range of ranks to exclude.
   *
   *  @c last Past the end of the iterator range of ranks to exclude.
   *
   *  @returns A new group containing all of the processes in the
   *  current group except those processes with ranks @c [first, last)
   *  in the current group. 
   */
  template<typename InputIterator>
  group exclude(InputIterator first, InputIterator last);
  

protected:
  /**
   * INTERNAL ONLY
   *
   * Function object that frees an MPI group and deletes the
   * memory associated with it. Intended to be used as a deleter with
   * shared_ptr.
   */
  struct group_free
  {
    void operator()(MPI_Group* comm) const
    {
      int finalized;
      BOOST_MPI_CHECK_RESULT(MPI_Finalized, (&finalized));
      if (!finalized)
        BOOST_MPI_CHECK_RESULT(MPI_Group_free, (comm));
      delete comm;
    }
  };

  /**
   * The underlying MPI group. This is a shared pointer, so the actual
   * MPI group which will be shared among all related instances of the
   * @c group class. When there are no more such instances, the group
   * will be automatically freed.
   */
  shared_ptr<MPI_Group> group_ptr;
};

/**
 * @brief Determines whether two process groups are identical.
 *
 * Equivalent to calling @c MPI_Group_compare and checking whether the
 * result is @c MPI_IDENT.
 *
 * @returns True when the two process groups contain the same
 * processes in the same order.
 */
BOOST_MPI_DECL bool operator==(const group& g1, const group& g2);

/**
 * @brief Determines whether two process groups are not identical.
 *
 * Equivalent to calling @c MPI_Group_compare and checking whether the
 * result is not @c MPI_IDENT.
 *
 * @returns False when the two process groups contain the same
 * processes in the same order.
 */
inline bool operator!=(const group& g1, const group& g2)
{ 
  return !(g1 == g2);
}

/**
 * @brief Computes the union of two process groups.
 *
 * This routine returns a new @c group that contains all processes
 * that are either in group @c g1 or in group @c g2 (or both). The
 * processes that are in @c g1 will be first in the resulting group,
 * followed by the processes from @c g2 (but not also in @c
 * g1). Equivalent to @c MPI_Group_union.
 */
BOOST_MPI_DECL group operator|(const group& g1, const group& g2);

/**
 * @brief Computes the intersection of two process groups.
 *
 * This routine returns a new @c group that contains all processes
 * that are in group @c g1 and in group @c g2, ordered in the same way
 * as @c g1. Equivalent to @c MPI_Group_intersection.
 */
BOOST_MPI_DECL group operator&(const group& g1, const group& g2);

/**
 * @brief Computes the difference between two process groups.
 *
 * This routine returns a new @c group that contains all processes
 * that are in group @c g1 but not in group @c g2, ordered in the same way
 * as @c g1. Equivalent to @c MPI_Group_difference.
 */
BOOST_MPI_DECL group operator-(const group& g1, const group& g2);

/************************************************************************
 * Implementation details                                               *
 ************************************************************************/
template<typename InputIterator, typename OutputIterator>
OutputIterator 
group::translate_ranks(InputIterator first, InputIterator last,
                       const group& to_group, OutputIterator out)
{
  std::vector<int> in_array(first, last);
  if (in_array.empty())
    return out;

  std::vector<int> out_array(in_array.size());
  BOOST_MPI_CHECK_RESULT(MPI_Group_translate_ranks,
                         ((MPI_Group)*this,
                          in_array.size(),
                          &in_array[0],
                          (MPI_Group)to_group,
                          &out_array[0]));

  for (std::vector<int>::size_type i = 0, n = out_array.size(); i < n; ++i)
    *out++ = out_array[i];
  return out;
}

/**
 * INTERNAL ONLY
 * 
 * Specialization of translate_ranks that handles the one case where
 * we can avoid any memory allocation or copying.
 */
template<> 
BOOST_MPI_DECL int*
group::translate_ranks(int* first, int* last, const group& to_group, int* out);

template<typename InputIterator>
group group::include(InputIterator first, InputIterator last)
{
  if (first == last)
    return group();

  std::vector<int> ranks(first, last);
  MPI_Group result;
  BOOST_MPI_CHECK_RESULT(MPI_Group_incl,
                         ((MPI_Group)*this, ranks.size(), &ranks[0], &result));
  return group(result, /*adopt=*/true);
}

/**
 * INTERNAL ONLY
 * 
 * Specialization of group::include that handles the one case where we
 * can avoid any memory allocation or copying before creating the
 * group.
 */
template<> BOOST_MPI_DECL group group::include(int* first, int* last);

template<typename InputIterator>
group group::exclude(InputIterator first, InputIterator last)
{
  if (first == last)
    return group();

  std::vector<int> ranks(first, last);
  MPI_Group result;
  BOOST_MPI_CHECK_RESULT(MPI_Group_excl,
                         ((MPI_Group)*this, ranks.size(), &ranks[0], &result));
  return group(result, /*adopt=*/true);
}

/**
 * INTERNAL ONLY
 * 
 * Specialization of group::exclude that handles the one case where we
 * can avoid any memory allocation or copying before creating the
 * group.
 */
template<> BOOST_MPI_DECL group group::exclude(int* first, int* last);

} } // end namespace boost::mpi

#endif // BOOST_MPI_GROUP_HPP

/* group.hpp
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
*/