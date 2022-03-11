// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file nonblocking.hpp
 *
 *  This header defines operations for completing non-blocking
 *  communication requests.
 */
#ifndef BOOST_MPI_NONBLOCKING_HPP
#define BOOST_MPI_NONBLOCKING_HPP

#include <boost/mpi/config.hpp>
#include <vector>
#include <iterator> // for std::iterator_traits
#include <boost/optional.hpp>
#include <utility> // for std::pair
#include <algorithm> // for iter_swap, reverse
#include <boost/static_assert.hpp>
#include <boost/mpi/request.hpp>
#include <boost/mpi/status.hpp>
#include <boost/mpi/exception.hpp>

namespace boost { namespace mpi {

/** 
 *  @brief Wait until any non-blocking request has completed.
 *
 *  This routine takes in a set of requests stored in the iterator
 *  range @c [first,last) and waits until any of these requests has
 *  been completed. It provides functionality equivalent to 
 *  @c MPI_Waitany.
 *
 *  @param first The iterator that denotes the beginning of the
 *  sequence of request objects.
 *
 *  @param last The iterator that denotes the end of the sequence of
 *  request objects. This may not be equal to @c first.
 *
 *  @returns A pair containing the status object that corresponds to
 *  the completed operation and the iterator referencing the completed
 *  request.
 */
template<typename ForwardIterator>
std::pair<status, ForwardIterator> 
wait_any(ForwardIterator first, ForwardIterator last)
{
  using std::advance;

  BOOST_ASSERT(first != last);
  
  typedef typename std::iterator_traits<ForwardIterator>::difference_type
    difference_type;

  bool all_trivial_requests = true;
  difference_type n = 0;
  ForwardIterator current = first;
  while (true) {
    // Check if we have found a completed request. If so, return it.
    if (current->active()) {
      optional<status> result = current->test();
      if (bool(result)) {
        return std::make_pair(*result, current);
      }
    }
    
    // Check if this request (and all others before it) are "trivial"
    // requests, e.g., they can be represented with a single
    // MPI_Request.
    // We could probably ignore non trivial request that are inactive,
    // but we can assume that a mix of trivial and non trivial requests
    // is unlikely enough not to care.
    all_trivial_requests = all_trivial_requests && current->trivial();

    // Move to the next request.
    ++n;
    if (++current == last) {
      // We have reached the end of the list. If all requests thus far
      // have been trivial, we can call MPI_Waitany directly, because
      // it may be more efficient than our busy-wait semantics.
      if (all_trivial_requests) {
        std::vector<MPI_Request> requests;
        requests.reserve(n);
        for (current = first; current != last; ++current) {
          requests.push_back(*current->trivial());
        }

        // Let MPI wait until one of these operations completes.
        int index;
        status stat;
        BOOST_MPI_CHECK_RESULT(MPI_Waitany, 
                               (n, &requests[0], &index, &stat.m_status));

        // We don't have a notion of empty requests or status objects,
        // so this is an error.
        if (index == MPI_UNDEFINED)
          boost::throw_exception(exception("MPI_Waitany", MPI_ERR_REQUEST));

        // Find the iterator corresponding to the completed request.
        current = first;
        advance(current, index);
        *current->trivial() = requests[index];
        return std::make_pair(stat, current);
      }

      // There are some nontrivial requests, so we must continue our
      // busy waiting loop.
      n = 0;
      current = first;
      all_trivial_requests = true;
    }
  }

  // We cannot ever get here
  BOOST_ASSERT(false);
}

/** 
 *  @brief Test whether any non-blocking request has completed.
 *
 *  This routine takes in a set of requests stored in the iterator
 *  range @c [first,last) and tests whether any of these requests has
 *  been completed. This routine is similar to @c wait_any, but will
 *  not block waiting for requests to completed. It provides
 *  functionality equivalent to @c MPI_Testany.
 *
 *  @param first The iterator that denotes the beginning of the
 *  sequence of request objects.
 *
 *  @param last The iterator that denotes the end of the sequence of
 *  request objects. 
 *
 *  @returns If any outstanding requests have completed, a pair
 *  containing the status object that corresponds to the completed
 *  operation and the iterator referencing the completed
 *  request. Otherwise, an empty @c optional<>.
 */
template<typename ForwardIterator>
optional<std::pair<status, ForwardIterator> >
test_any(ForwardIterator first, ForwardIterator last)
{
  while (first != last) {
    // Check if we have found a completed request. If so, return it.
    if (optional<status> result = first->test()) {
      return std::make_pair(*result, first);
    }
    ++first;
  }

  // We found nothing
  return optional<std::pair<status, ForwardIterator> >();
}

/** 
 *  @brief Wait until all non-blocking requests have completed.
 *
 *  This routine takes in a set of requests stored in the iterator
 *  range @c [first,last) and waits until all of these requests have
 *  been completed. It provides functionality equivalent to 
 *  @c MPI_Waitall.
 *
 *  @param first The iterator that denotes the beginning of the
 *  sequence of request objects.
 *
 *  @param last The iterator that denotes the end of the sequence of
 *  request objects. 
 *
 *  @param out If provided, an output iterator through which the
 *  status of each request will be emitted. The @c status objects are
 *  emitted in the same order as the requests are retrieved from 
 *  @c [first,last).
 *
 *  @returns If an @p out parameter was provided, the value @c out
 *  after all of the @c status objects have been emitted.
 */
template<typename ForwardIterator, typename OutputIterator>
OutputIterator 
wait_all(ForwardIterator first, ForwardIterator last, OutputIterator out)
{
  typedef typename std::iterator_traits<ForwardIterator>::difference_type
    difference_type;

  using std::distance;

  difference_type num_outstanding_requests = distance(first, last);

  std::vector<status> results(num_outstanding_requests);
  std::vector<bool> completed(num_outstanding_requests);

  while (num_outstanding_requests > 0) {
    bool all_trivial_requests = true;
    difference_type idx = 0;
    for (ForwardIterator current = first; current != last; ++current, ++idx) {
      if (!completed[idx]) {
        if (optional<status> stat = current->test()) {
          // This outstanding request has been completed. We're done.
          results[idx] = *stat;
          completed[idx] = true;
          --num_outstanding_requests;
          all_trivial_requests = false;
        } else {
          // Check if this request (and all others before it) are "trivial"
          // requests, e.g., they can be represented with a single
          // MPI_Request.
          all_trivial_requests = all_trivial_requests && current->trivial();
        }
      }
    }

    // If we have yet to fulfill any requests and all of the requests
    // are trivial (i.e., require only a single MPI_Request to be
    // fulfilled), call MPI_Waitall directly.
    if (all_trivial_requests 
        && num_outstanding_requests == (difference_type)results.size()) {
      std::vector<MPI_Request> requests;
      requests.reserve(num_outstanding_requests);
      for (ForwardIterator current = first; current != last; ++current)
        requests.push_back(*current->trivial());

      // Let MPI wait until all of these operations completes.
      std::vector<MPI_Status> stats(num_outstanding_requests);
      BOOST_MPI_CHECK_RESULT(MPI_Waitall, 
                             (num_outstanding_requests, &requests[0], 
                              &stats[0]));

      for (std::vector<MPI_Status>::iterator i = stats.begin(); 
           i != stats.end(); ++i, ++out) {
        status stat;
        stat.m_status = *i;
        *out = stat;
      }

      return out;
    }

    all_trivial_requests = false;
  }

  return std::copy(results.begin(), results.end(), out);
}

/**
 * \overload
 */
template<typename ForwardIterator>
void
wait_all(ForwardIterator first, ForwardIterator last)
{
  typedef typename std::iterator_traits<ForwardIterator>::difference_type
    difference_type;

  using std::distance;

  difference_type num_outstanding_requests = distance(first, last);

  std::vector<bool> completed(num_outstanding_requests, false);

  while (num_outstanding_requests > 0) {
    bool all_trivial_requests = true;

    difference_type idx = 0;
    for (ForwardIterator current = first; current != last; ++current, ++idx) {
      if (!completed[idx]) {
        if (optional<status> stat = current->test()) {
          // This outstanding request has been completed.
          completed[idx] = true;
          --num_outstanding_requests;
          all_trivial_requests = false;
        } else {
          // Check if this request (and all others before it) are "trivial"
          // requests, e.g., they can be represented with a single
          // MPI_Request.
          all_trivial_requests = all_trivial_requests && current->trivial();
        }
      }
    }

    // If we have yet to fulfill any requests and all of the requests
    // are trivial (i.e., require only a single MPI_Request to be
    // fulfilled), call MPI_Waitall directly.
    if (all_trivial_requests 
        && num_outstanding_requests == (difference_type)completed.size()) {
      std::vector<MPI_Request> requests;
      requests.reserve(num_outstanding_requests);
      for (ForwardIterator current = first; current != last; ++current)
        requests.push_back(*current->trivial());

      // Let MPI wait until all of these operations completes.
      BOOST_MPI_CHECK_RESULT(MPI_Waitall, 
                             (num_outstanding_requests, &requests[0], 
                              MPI_STATUSES_IGNORE));

      // Signal completion
      num_outstanding_requests = 0;
    }
  }
}

/** 
 *  @brief Tests whether all non-blocking requests have completed.
 *
 *  This routine takes in a set of requests stored in the iterator
 *  range @c [first,last) and determines whether all of these requests
 *  have been completed. However, due to limitations of the underlying
 *  MPI implementation, if any of the requests refers to a
 *  non-blocking send or receive of a serialized data type, @c
 *  test_all will always return the equivalent of @c false (i.e., the
 *  requests cannot all be finished at this time). This routine
 *  performs the same functionality as @c wait_all, except that this
 *  routine will not block. This routine provides functionality
 *  equivalent to @c MPI_Testall.
 *
 *  @param first The iterator that denotes the beginning of the
 *  sequence of request objects.
 *
 *  @param last The iterator that denotes the end of the sequence of
 *  request objects. 
 *
 *  @param out If provided and all requests hav been completed, an
 *  output iterator through which the status of each request will be
 *  emitted. The @c status objects are emitted in the same order as
 *  the requests are retrieved from @c [first,last).
 *
 *  @returns If an @p out parameter was provided, the value @c out
 *  after all of the @c status objects have been emitted (if all
 *  requests were completed) or an empty @c optional<>. If no @p out
 *  parameter was provided, returns @c true if all requests have
 *  completed or @c false otherwise.
 */
template<typename ForwardIterator, typename OutputIterator>
optional<OutputIterator>
test_all(ForwardIterator first, ForwardIterator last, OutputIterator out)
{
  std::vector<MPI_Request> requests;
  for (; first != last; ++first) {
    // If we have a non-trivial request, then no requests can be
    // completed.
    if (!first->trivial()) {
      return optional<OutputIterator>();
    }
    requests.push_back(*first->trivial());
  }

  int flag = 0;
  int n = requests.size();
  std::vector<MPI_Status> stats(n);
  BOOST_MPI_CHECK_RESULT(MPI_Testall, (n, &requests[0], &flag, &stats[0]));
  if (flag) {
    for (int i = 0; i < n; ++i, ++out) {
      status stat;
      stat.m_status = stats[i];
      *out = stat;
    }
    return out;
  } else {
    return optional<OutputIterator>();
  }
}

/**
 *  \overload
 */
template<typename ForwardIterator>
bool
test_all(ForwardIterator first, ForwardIterator last)
{
  std::vector<MPI_Request> requests;
  for (; first != last; ++first) {
    // If we have a non-trivial request, then no requests can be
    // completed.
    if (!first->trivial()) {
      return false;
    }
    requests.push_back(*first->trivial());
  }

  int flag = 0;
  int n = requests.size();
  BOOST_MPI_CHECK_RESULT(MPI_Testall, 
                         (n, &requests[0], &flag, MPI_STATUSES_IGNORE));
  return flag != 0;
}

/** 
 *  @brief Wait until some non-blocking requests have completed.
 *
 *  This routine takes in a set of requests stored in the iterator
 *  range @c [first,last) and waits until at least one of the requests
 *  has completed. It then completes all of the requests it can,
 *  partitioning the input sequence into pending requests followed by
 *  completed requests. If an output iterator is provided, @c status
 *  objects will be emitted for each of the completed requests. This
 *  routine provides functionality equivalent to @c MPI_Waitsome.
 *
 *  @param first The iterator that denotes the beginning of the
 *  sequence of request objects.
 *
 *  @param last The iterator that denotes the end of the sequence of
 *  request objects. This may not be equal to @c first.
 *
 *  @param out If provided, the @c status objects corresponding to
 *  completed requests will be emitted through this output iterator.

 *  @returns If the @p out parameter was provided, a pair containing
 *  the output iterator @p out after all of the @c status objects have
 *  been written through it and an iterator referencing the first
 *  completed request. If no @p out parameter was provided, only the
 *  iterator referencing the first completed request will be emitted.
 */
template<typename BidirectionalIterator, typename OutputIterator>
std::pair<OutputIterator, BidirectionalIterator> 
wait_some(BidirectionalIterator first, BidirectionalIterator last,
          OutputIterator out)
{
  using std::advance;

  if (first == last)
    return std::make_pair(out, first);
  
  typedef typename std::iterator_traits<BidirectionalIterator>::difference_type
    difference_type;

  bool all_trivial_requests = true;
  difference_type n = 0;
  BidirectionalIterator current = first;
  BidirectionalIterator start_of_completed = last;
  while (true) {
    // Check if we have found a completed request. 
    if (optional<status> result = current->test()) {
      using std::iter_swap;

      // Emit the resulting status object
      *out++ = *result;

      // We're expanding the set of completed requests
      --start_of_completed;

      if (current == start_of_completed) {
        // If we have hit the end of the list of pending
        // requests. Finish up by fixing the order of the completed
        // set to match the order in which we emitted status objects,
        // then return.
        std::reverse(start_of_completed, last);
        return std::make_pair(out, start_of_completed);
      }

      // Swap the request we just completed with the last request that
      // has not yet been tested.
      iter_swap(current, start_of_completed);

      continue;
    }

    // Check if this request (and all others before it) are "trivial"
    // requests, e.g., they can be represented with a single
    // MPI_Request.
    all_trivial_requests = all_trivial_requests && current->trivial();

    // Move to the next request.
    ++n;
    if (++current == start_of_completed) {
      if (start_of_completed != last) {
        // We have satisfied some requests. Make the order of the
        // completed requests match that of the status objects we've
        // already emitted and we're done.
        std::reverse(start_of_completed, last);
        return std::make_pair(out, start_of_completed);
      }

      // We have reached the end of the list. If all requests thus far
      // have been trivial, we can call MPI_Waitsome directly, because
      // it may be more efficient than our busy-wait semantics.
      if (all_trivial_requests) {
        std::vector<MPI_Request> requests;
        std::vector<int> indices(n);
        std::vector<MPI_Status> stats(n);
        requests.reserve(n);
        for (current = first; current != last; ++current)
          requests.push_back(*current->trivial());

        // Let MPI wait until some of these operations complete.
        int num_completed;
        BOOST_MPI_CHECK_RESULT(MPI_Waitsome, 
                               (n, &requests[0], &num_completed, &indices[0],
                                &stats[0]));

        // Translate the index-based result of MPI_Waitsome into a
        // partitioning on the requests.
        int current_offset = 0;
        current = first;
        for (int index = 0; index < num_completed; ++index, ++out) {
          using std::iter_swap;

          // Move "current" to the request object at this index
          advance(current, indices[index] - current_offset);
          current_offset = indices[index];

          // Emit the status object
          status stat;
          stat.m_status = stats[index];
          *out = stat;

          // Finish up the request and swap it into the "completed
          // requests" partition.
          *current->trivial() = requests[indices[index]];
          --start_of_completed;
          iter_swap(current, start_of_completed);
        }

        // We have satisfied some requests. Make the order of the
        // completed requests match that of the status objects we've
        // already emitted and we're done.
        std::reverse(start_of_completed, last);
        return std::make_pair(out, start_of_completed);
      }

      // There are some nontrivial requests, so we must continue our
      // busy waiting loop.
      n = 0;
      current = first;
    }
  }

  // We cannot ever get here
  BOOST_ASSERT(false);
}

/**
 *  \overload
 */
template<typename BidirectionalIterator>
BidirectionalIterator
wait_some(BidirectionalIterator first, BidirectionalIterator last)
{
  using std::advance;

  if (first == last)
    return first;
  
  typedef typename std::iterator_traits<BidirectionalIterator>::difference_type
    difference_type;

  bool all_trivial_requests = true;
  difference_type n = 0;
  BidirectionalIterator current = first;
  BidirectionalIterator start_of_completed = last;
  while (true) {
    // Check if we have found a completed request. 
    if (optional<status> result = current->test()) {
      using std::iter_swap;

      // We're expanding the set of completed requests
      --start_of_completed;

      // If we have hit the end of the list of pending requests, we're
      // done.
      if (current == start_of_completed)
        return start_of_completed;

      // Swap the request we just completed with the last request that
      // has not yet been tested.
      iter_swap(current, start_of_completed);

      continue;
    }

    // Check if this request (and all others before it) are "trivial"
    // requests, e.g., they can be represented with a single
    // MPI_Request.
    all_trivial_requests = all_trivial_requests && current->trivial();

    // Move to the next request.
    ++n;
    if (++current == start_of_completed) {
        // If we have satisfied some requests, we're done.
      if (start_of_completed != last)
        return start_of_completed;

      // We have reached the end of the list. If all requests thus far
      // have been trivial, we can call MPI_Waitsome directly, because
      // it may be more efficient than our busy-wait semantics.
      if (all_trivial_requests) {
        std::vector<MPI_Request> requests;
        std::vector<int> indices(n);
        requests.reserve(n);
        for (current = first; current != last; ++current)
          requests.push_back(*current->trivial());

        // Let MPI wait until some of these operations complete.
        int num_completed;
        BOOST_MPI_CHECK_RESULT(MPI_Waitsome, 
                               (n, &requests[0], &num_completed, &indices[0],
                                MPI_STATUSES_IGNORE));

        // Translate the index-based result of MPI_Waitsome into a
        // partitioning on the requests.
        int current_offset = 0;
        current = first;
        for (int index = 0; index < num_completed; ++index) {
          using std::iter_swap;

          // Move "current" to the request object at this index
          advance(current, indices[index] - current_offset);
          current_offset = indices[index];

          // Finish up the request and swap it into the "completed
          // requests" partition.
          *current->trivial() = requests[indices[index]];
          --start_of_completed;
          iter_swap(current, start_of_completed);
        }

        // We have satisfied some requests, so we are done.
        return start_of_completed;
      }

      // There are some nontrivial requests, so we must continue our
      // busy waiting loop.
      n = 0;
      current = first;
    }
  }

  // We cannot ever get here
  BOOST_ASSERT(false);
}

/** 
 *  @brief Test whether some non-blocking requests have completed.
 *
 *  This routine takes in a set of requests stored in the iterator
 *  range @c [first,last) and tests to see if any of the requests has
 *  completed. It completes all of the requests it can, partitioning
 *  the input sequence into pending requests followed by completed
 *  requests. If an output iterator is provided, @c status objects
 *  will be emitted for each of the completed requests. This routine
 *  is similar to @c wait_some, but does not wait until any requests
 *  have completed. This routine provides functionality equivalent to
 *  @c MPI_Testsome.
 *
 *  @param first The iterator that denotes the beginning of the
 *  sequence of request objects.
 *
 *  @param last The iterator that denotes the end of the sequence of
 *  request objects. This may not be equal to @c first.
 *
 *  @param out If provided, the @c status objects corresponding to
 *  completed requests will be emitted through this output iterator.

 *  @returns If the @p out parameter was provided, a pair containing
 *  the output iterator @p out after all of the @c status objects have
 *  been written through it and an iterator referencing the first
 *  completed request. If no @p out parameter was provided, only the
 *  iterator referencing the first completed request will be emitted.
 */
template<typename BidirectionalIterator, typename OutputIterator>
std::pair<OutputIterator, BidirectionalIterator> 
test_some(BidirectionalIterator first, BidirectionalIterator last,
          OutputIterator out)
{
  BidirectionalIterator current = first;
  BidirectionalIterator start_of_completed = last;
  while (current != start_of_completed) {
    // Check if we have found a completed request. 
    if (optional<status> result = current->test()) {
      using std::iter_swap;

      // Emit the resulting status object
      *out++ = *result;

      // We're expanding the set of completed requests
      --start_of_completed;

      // Swap the request we just completed with the last request that
      // has not yet been tested.
      iter_swap(current, start_of_completed);

      continue;
    }

    // Move to the next request.
    ++current;
  }

  // Finish up by fixing the order of the completed set to match the
  // order in which we emitted status objects, then return.
  std::reverse(start_of_completed, last);
  return std::make_pair(out, start_of_completed);
}

/**
 *  \overload
 */
template<typename BidirectionalIterator>
BidirectionalIterator
test_some(BidirectionalIterator first, BidirectionalIterator last)
{
  BidirectionalIterator current = first;
  BidirectionalIterator start_of_completed = last;
  while (current != start_of_completed) {
    // Check if we have found a completed request. 
    if (optional<status> result = current->test()) {
      using std::iter_swap;

      // We're expanding the set of completed requests
      --start_of_completed;

      // Swap the request we just completed with the last request that
      // has not yet been tested.
      iter_swap(current, start_of_completed);

      continue;
    }

    // Move to the next request.
    ++current;
  }

  return start_of_completed;
}

} } // end namespace boost::mpi


#endif // BOOST_MPI_NONBLOCKING_HPP

/* nonblocking.hpp
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
*/