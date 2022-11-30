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
#include <boost/mpi/detail/antiques.hpp>
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
                          detail::c_data(in_array),
                          (MPI_Group)to_group,
                          detail::c_data(out_array)));

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
                         ((MPI_Group)*this, ranks.size(), detail::c_data(ranks), &result));
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
                         ((MPI_Group)*this, ranks.size(), detail::c_data(ranks), &result));
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
+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
*/