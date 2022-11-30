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
                               (n, detail::c_data(requests), &index, &stat.m_status));

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
        if (!current->active()) {
          completed[idx] = true;
          --num_outstanding_requests;
        } else if (optional<status> stat = current->test()) {
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
                             (num_outstanding_requests, detail::c_data(requests), 
                              detail::c_data(stats)));

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
        if (!current->active()) {
          completed[idx] = true;
          --num_outstanding_requests;
        } else if (optional<status> stat = current->test()) {
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
                             (num_outstanding_requests, detail::c_data(requests), 
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
  BOOST_MPI_CHECK_RESULT(MPI_Testall, (n, detail::c_data(requests), &flag, detail::c_data(stats)));
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
                         (n, detail::c_data(requests), &flag, MPI_STATUSES_IGNORE));
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
                               (n, detail::c_data(requests), &num_completed, detail::c_data(indices),
                                detail::c_data(stats)));

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
                               (n, detail::c_data(requests), &num_completed, detail::c_data(indices),
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