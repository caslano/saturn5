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