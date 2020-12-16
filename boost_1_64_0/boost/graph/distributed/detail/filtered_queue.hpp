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
vgou179lb6PmLtf/9f5G40g/exzR17l+c5+j7S7Xv3Wvo6Lzfv9+R4ddrn96z6Pf2u/I53b95p5HDdGJte/RCLfrP7L30Ty36/92/6NV/+QeSKvcrj+0D9JLbtcf3gvpZ8LY+yGhE+f6n94TqafeF2lxxN5IA0jzJNw83N24l3Bf4Pzx9LW4P//+/Pvz78+/P//+/Pvz7//jz4Ub82/b/0+Wvv1L9gAM7i9WJ7PUPn/ISu3zJzJ7nz9b5hRZ//49G9syl8gG9OzPysQMLXMbWS5SWx5nyxshNnHEi7xv/x7IymhZgsgGEdaD//T7HzVJ4fuG3uNnqN7/6Hhwbo7mTRw5drtMVdIl+av7/GjdDmZubKM7gv5+Zm3UUfF7VPRePvb6hO/k+FTrEZWn5+SG42xq1m5VF50+Zt3LveuC/jYSZ4PQvHBGpPbahfPXh+aFO5Tb2G9tKHFc6nzJcjBfwMFcgDjbXj12/AtyZ5BXLArqeAoJM0nCHLK6WD3lXK+mK/5kqZuxEVpLdK50voJ1sJL7M2TotWSDRWew807Svs6xWa8xY2b6nchJpR2uiIyE5t43h3kSrpezxJ4YZq5ysRxf7GhD+nyOQr3/ETZJpXx+trqp+cw5aMd8qQBzklYG5zLrtluo91LgG43EcRGlNRpZhF3+kYXT8nVamsAeojfKebr50OOkvLtYus71+VvY+cL+WJGOqzUcL3F1lny1EHu0XNf6+Dmwnhy/3GnXz/Rp+bnTphcVFU4txoy8rh+Tzw7qPAnbMNimQ+3P6TXz94tMO7pR0tlOl59OJ6Wjy0nS21DKZ+T0MXqNwwgY0U7yZtrtRNrWJOLdJuesqhxcgUm4TFyOHGMnFzlW29mEo21x3XEDcTMsl5yvUabEm6/t/oXWoUiYiRG20gfZ9aHb1E+Sl02l2xJxtON4P4ljqNNew6ovZ36laHu5o0Wnu3OZFSdt45400TNrHRbJOTzRx3RZJsn5VqqMUm3ObQXbWuSaC1knotehFEg4d9TxRjpNqbCWHG+Drcz4KJ0zdRzjiWOC6CREHW+s45jA8cpyfIBqpK+tHBW9jiMAy6Ejttl0uqqLv5uqyKRc7CbJHhz7KLez5Pv3FWJTyJkrSzFjre+QMMcJ00zWd1xxXan1aVqHuVs63rnrgzFqvVJxtYvXcSXN9Zu4SuiMRqc5Oqw8eb6kPZ9L8VfC38K25yPuGdyduJbIW2nXGnc2rk2EjZO2/G6HwzaOyNrzuwOuI66T6Nmuc4S/S8Ra0KLT20bpSJTku6XsidDHsoydlC1SD9q+yB1mzb1Z6/+OLTNr/ffZMrPW/1lbZtb6P2ZkmETRsvtsmVn/v8GWnWVshNgyY5/gZltm7BOcXGdkkuYyyNYi02vTxM+1EmU3IGN9absBW05jN2BbabsB0j/RZyGTPitqLc2ARD3/PASOUYfozvnOqYJTbadPnszi+tC9U/fFyOmL7TU0WtcZ2jNC5NKvIhun987gnl1Cj8Nm7bzFdcemLeOLZ4V0+5bQzUQ3C93p0JL+Nayfy1Itfc2XCJOt05Et8UsGRF4LprCKvQ/6/NZhsAwQFT/6ErVZw2bCNLTDSNtVv7FmygMpM8qeMtMyP6R8kFE+2i5Dpll3Y8qC+AOSD9KFvHS+iUvyky3hSLNZw2PC2HkpUe/VfEr+PDrB8bguJOLYncqud7klx6x3reuJqndnnB6/mfVT0Xpk+58qN2ecbtv22iPmwMRacxN7DdAQWTO07dUH3vypfNfZz7abuve5Jk8vibUGKNZan1hrnmKtbYq19ijWmqdYa4/++FqoGGuPYq4lqiprdFZ8vHbG9heHnbGn7eKDF16+5blYa5I=
*/