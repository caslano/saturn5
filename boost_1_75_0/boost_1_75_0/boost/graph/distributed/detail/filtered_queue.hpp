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
X9RakcTwco0uw2BhGmfOnd5/6eXv/sUpz7yKeRUvvXb+PdfA/oHBv3nvqQsD+wcHXc9cOvuubb6nPFIId6JcUl567dyPTv/QtVeNhrXxmGvPWDhkKK5z//TKDy6EL+w6GzzzlGtdt6/P5dcxjHFN/6zryRemzk/ed/a/LscgQwtPcAk9yqh2SOnxde3q923ZVlvbO6KNy9zW2tqAGlbynyifyNwmKsfMhwHD3NgKw9zYmkse76a+ztOwsql5Y2vQv88TjxnaqFRUrmFuTQpKN+Qk/3rmwDccW2e/m+ZTfWZuuyC3nIJ3wbmsQ67J/+34k1fEdNMHwBu/8Nbf+XPNYOr1p4PpzerrehpsLe6MxuC8kfTN4vfwWChUIfYwvnfl5Temonxuf/nD7JU55ZEGJjeZjB1P7j+9Y6HxqNxOepSxkKqLh+gOXYtn7pBB+VqztVbWq+3o7Bzo8e3s7u1DarBHUaUKr92K+3btgPTnQZmdi4Yvdr/6uVevZmj4yRdmcWy+Rwr98Qa59car1tf5G66zr6e8UQiVZOZnn2yuTrMXqb6uq8FSfeLJ09Xr4m1dou01O7umn3BBdbLPpKxni/i5xYFziwPnE6dIkzjDJG4qZw2VVnlqvXJxCsovlImTUjIwyGdiPEXouwhnJz6mpVZdJpBrbE5xCkuGihx1y6wypzXnyrS5lIu2pRavFKezUoynCnmuo2q0KhM6
*/