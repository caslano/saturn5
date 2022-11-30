// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_FILTERED_QUEUE_HPP
#define BOOST_FILTERED_QUEUE_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <algorithm>

namespace boost {

/** Queue adaptor that filters elements pushed into the queue
 * according to some predicate.
 */
template<typename Buffer, typename Predicate>
class filtered_queue
{
 public:
  typedef Buffer                      buffer_type;
  typedef Predicate                   predicate_type;
  typedef typename Buffer::value_type value_type;
  typedef typename Buffer::size_type  size_type;

  /**
   * Constructs a new filtered queue with an initial buffer and a
   * predicate.
   *
   * @param buffer the initial buffer
   * @param pred the predicate
   */
  explicit
  filtered_queue(const buffer_type& buffer = buffer_type(),
                 const predicate_type& pred = predicate_type())
    : buffer(buffer), pred(pred) {}

  /** Push a value into the queue.
   *
   *  If the predicate returns @c true for @p x, pushes @p x into the
   *  buffer.
   */
  void push(const value_type& x)  { if (pred(x)) buffer.push(x); }

  /** Pop the front element off the buffer.
   *
   * @pre @c !empty()
   */
  void pop()                      { buffer.pop(); }

  /** Retrieve the front (top) element in the buffer.
   *
   * @pre @c !empty()
   */
  value_type& top()               { return buffer.top(); }

  /**
   * \overload
   */
  const value_type& top() const   { return buffer.top(); }

  /** Determine the number of elements in the buffer. */
  size_type size() const          { return buffer.size(); }

  /** Determine if the buffer is empty. */
  bool empty() const              { return buffer.empty(); }

  /** Get a reference to the underlying buffer. */
  buffer_type& base()             { return buffer; }
  const buffer_type& base() const { return buffer; }

  /** Swap the contents of this with @p other. */
  void swap(filtered_queue& other)
  {
    using std::swap;
    swap(buffer, other.buffer);
    swap(pred, other.pred);
  }

 private:
  buffer_type buffer;
  predicate_type pred;
};

/** Create a filtered queue. */
template<typename Buffer, typename Predicate>
inline filtered_queue<Buffer, Predicate>
make_filtered_queue(const Buffer& buffer, const Predicate& pred)
{ return filtered_queue<Buffer, Predicate>(buffer, pred); }

/** Swap a filtered_queue. */
template<typename Buffer, typename Predicate>
inline void
swap(filtered_queue<Buffer, Predicate>& x,
     filtered_queue<Buffer, Predicate>& y)
{
  x.swap(y);
}

} // end namespace boost

#endif // BOOST_FILTERED_QUEUE_HPP

/* filtered_queue.hpp
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
*/