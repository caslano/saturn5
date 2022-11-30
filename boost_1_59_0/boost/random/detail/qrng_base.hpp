/* boost random/detail/qrng_base.hpp header file
 *
 * Copyright Justinas Vygintas Daugmaudis 2010-2018
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_RANDOM_DETAIL_QRNG_BASE_HPP
#define BOOST_RANDOM_DETAIL_QRNG_BASE_HPP

#include <stdexcept>
#include <vector>
#include <limits>

#include <istream>
#include <ostream>
#include <sstream>

#include <boost/cstdint.hpp>
#include <boost/random/detail/operators.hpp>

#include <boost/throw_exception.hpp>

#include <boost/type_traits/integral_constant.hpp>

#include <boost/random/detail/disable_warnings.hpp>

//!\file
//!Describes the quasi-random number generator base class template.

namespace boost {
namespace random {

namespace qrng_detail {

// If the seed is a signed integer type, then we need to
// check that the value is positive:
template <typename Integer>
inline void check_seed_sign(const Integer& v, const boost::true_type)
{
  if (v < 0)
  {
    boost::throw_exception( std::range_error("seed must be a positive integer") );
  }
}
template <typename Integer>
inline void check_seed_sign(const Integer&, const boost::false_type) {}

template <typename Integer>
inline void check_seed_sign(const Integer& v)
{
  check_seed_sign(v, integral_constant<bool, std::numeric_limits<Integer>::is_signed>());
}


template<typename DerivedT, typename LatticeT, typename SizeT>
class qrng_base
{
public:
  typedef SizeT size_type;
  typedef typename LatticeT::value_type result_type;

  explicit qrng_base(std::size_t dimension)
    // Guard against invalid dimensions before creating the lattice
    : lattice(prevent_zero_dimension(dimension))
    , quasi_state(dimension)
  {
    derived().seed();
  }

  // default copy c-tor is fine

  // default assignment operator is fine

  //!Returns: The dimension of of the quasi-random domain.
  //!
  //!Throws: nothing.
  std::size_t dimension() const { return quasi_state.size(); }

  //!Returns: Returns a successive element of an s-dimensional
  //!(s = X::dimension()) vector at each invocation. When all elements are
  //!exhausted, X::operator() begins anew with the starting element of a
  //!subsequent s-dimensional vector.
  //!
  //!Throws: range_error.
  result_type operator()()
  {
    return curr_elem != dimension() ? load_cached(): next_state();
  }

  //!Fills a range with quasi-random values.
  template<typename Iter> void generate(Iter first, Iter last)
  {
    for (; first != last; ++first)
      *first = this->operator()();
  }

  //!Effects: Advances *this state as if z consecutive
  //!X::operator() invocations were executed.
  //!
  //!Throws: range_error.
  void discard(boost::uintmax_t z)
  {
    const std::size_t dimension_value = dimension();

    // Compiler knows how to optimize subsequent x / y and x % y
    // statements. In fact, gcc does this even at -O1, so don't
    // be tempted to "optimize" % via subtraction and multiplication.

    boost::uintmax_t vec_n = z / dimension_value;
    std::size_t carry = curr_elem + (z % dimension_value);

    vec_n += carry / dimension_value;
    carry  = carry % dimension_value;

    // Avoid overdiscarding by branchlessly correcting the triple
    // (D, S + 1, 0) to (D, S, D) (see equality operator)
    const bool corr = (!carry) & static_cast<bool>(vec_n);

    // Discards vec_n (with correction) consecutive s-dimensional vectors
    discard_vector(vec_n - static_cast<boost::uintmax_t>(corr));

#ifdef BOOST_MSVC
#pragma warning(push)
// disable unary minus operator applied to an unsigned type,
// result still unsigned.
#pragma warning(disable:4146)
#endif

    // Sets up the proper position of the element-to-read
    // curr_elem = carry + corr*dimension_value
    curr_elem = carry ^ (-static_cast<std::size_t>(corr) & dimension_value);

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
  }

  //!Writes the textual representation of the generator to a @c std::ostream.
  BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, qrng_base, s)
  {
    os << s.dimension() << " " << s.seq_count << " " << s.curr_elem;
    return os;
  }

  //!Reads the textual representation of the generator from a @c std::istream.
  BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, qrng_base, s)
  {
    std::size_t dim;
    size_type seed;
    boost::uintmax_t z;
    if (is >> dim >> std::ws >> seed >> std::ws >> z) // initialize iff success!
    {
      // Check seed sign before resizing the lattice and/or recomputing state
      check_seed_sign(seed);

      if (s.dimension() != prevent_zero_dimension(dim))
      {
        s.lattice.resize(dim);
        s.quasi_state.resize(dim);
      }
      // Fast-forward to the correct state
      s.derived().seed(seed);
      if (z != 0) s.discard(z);
    }
    return is;
  }

  //!Returns true if the two generators will produce identical sequences of outputs.
  BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(qrng_base, x, y)
  {
    const std::size_t dimension_value = x.dimension();

    // Note that two generators with different seq_counts and curr_elems can
    // produce the same sequence because the generator triple
    // (D, S, D) is equivalent to (D, S + 1, 0), where D is dimension, S -- seq_count,
    // and the last one is curr_elem.

    return (dimension_value == y.dimension()) &&
      // |x.seq_count - y.seq_count| <= 1
      !((x.seq_count < y.seq_count ? y.seq_count - x.seq_count : x.seq_count - y.seq_count)
          > static_cast<size_type>(1)) &&
      // Potential overflows don't matter here, since we've already ascertained
      // that sequence counts differ by no more than 1, so if they overflow, they
      // can overflow together.
      (x.seq_count + (x.curr_elem / dimension_value) == y.seq_count + (y.curr_elem / dimension_value)) &&
      (x.curr_elem % dimension_value == y.curr_elem % dimension_value);
  }

  //!Returns true if the two generators will produce different sequences of outputs.
  BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(qrng_base)

protected:
  typedef std::vector<result_type> state_type;
  typedef typename state_type::iterator state_iterator;

  // Getters
  size_type curr_seq() const { return seq_count; }

  state_iterator state_begin() { return quasi_state.begin(); }
  state_iterator state_end() { return quasi_state.end(); }

  // Setters
  void reset_seq(size_type seq)
  {
    seq_count = seq;
    curr_elem = 0u;
  }

private:
  DerivedT& derived() throw()
  {
    return *static_cast<DerivedT * const>(this);
  }

  // Load the result from the saved state.
  result_type load_cached()
  {
    return quasi_state[curr_elem++];
  }

  result_type next_state()
  {
    size_type new_seq = seq_count;
    if (BOOST_LIKELY(++new_seq > seq_count))
    {
      derived().compute_seq(new_seq);
      reset_seq(new_seq);
      return load_cached();
    }
    boost::throw_exception( std::range_error("qrng_base: next_state") );
  }

  // Discards z consecutive s-dimensional vectors,
  // and preserves the position of the element-to-read
  void discard_vector(boost::uintmax_t z)
  {
    const boost::uintmax_t max_z = (std::numeric_limits<size_type>::max)() - seq_count;

    // Don't allow seq_count + z overflows here
    if (max_z < z)
      boost::throw_exception( std::range_error("qrng_base: discard_vector") );

    std::size_t tmp = curr_elem;
    derived().seed(static_cast<size_type>(seq_count + z));
    curr_elem = tmp;
  }

  static std::size_t prevent_zero_dimension(std::size_t dimension)
  {
    if (dimension == 0)
      boost::throw_exception( std::invalid_argument("qrng_base: zero dimension") );
    return dimension;
  }

  // Member variables are so ordered with the intention
  // that the typical memory access pattern would be
  // incremental. Moreover, lattice is put before quasi_state
  // because we want to construct lattice first. Lattices
  // can do some kind of dimension sanity check (as in
  // dimension_assert below), and if that fails then we don't
  // need to do any more work.
private:
  std::size_t curr_elem;
  size_type seq_count;
protected:
  LatticeT lattice;
private:
  state_type quasi_state;
};

inline void dimension_assert(const char* generator, std::size_t dim, std::size_t maxdim)
{
  if (!dim || dim > maxdim)
  {
    std::ostringstream os;
    os << "The " << generator << " quasi-random number generator only supports dimensions in range [1; "
      << maxdim << "], but dimension " << dim << " was supplied.";
    boost::throw_exception( std::invalid_argument(os.str()) );
  }
}

} // namespace qrng_detail

} // namespace random
} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_DETAIL_QRNG_BASE_HPP

/* qrng_base.hpp
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
*/