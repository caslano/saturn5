/* boost random/sobol.hpp header file
 *
 * Copyright Justinas Vygintas Daugmaudis 2010-2018
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_RANDOM_SOBOL_HPP
#define BOOST_RANDOM_SOBOL_HPP

#include <boost/random/detail/sobol_table.hpp>
#include <boost/random/detail/gray_coded_qrng.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace random {

/** @cond */
namespace qrng_detail {

// sobol_lattice sets up the random-number generator to produce a Sobol
// sequence of at most max dims-dimensional quasi-random vectors.
// Adapted from ACM TOMS algorithm 659, see

// http://doi.acm.org/10.1145/42288.214372

template<typename UIntType, unsigned w, typename SobolTables>
struct sobol_lattice
{
  typedef UIntType value_type;

  BOOST_STATIC_ASSERT(w > 0u);
  BOOST_STATIC_CONSTANT(unsigned, bit_count = w);

private:
  typedef std::vector<value_type> container_type;

public:
  explicit sobol_lattice(std::size_t dimension)
  {
    resize(dimension);
  }

  // default copy c-tor is fine

  void resize(std::size_t dimension)
  {
    dimension_assert("Sobol", dimension, SobolTables::max_dimension);

    // Initialize the bit array
    container_type cj(bit_count * dimension);

    // Initialize direction table in dimension 0
    for (unsigned k = 0; k != bit_count; ++k)
      cj[dimension*k] = static_cast<value_type>(1);

    // Initialize in remaining dimensions.
    for (std::size_t dim = 1; dim < dimension; ++dim)
    {
      const typename SobolTables::value_type poly = SobolTables::polynomial(dim-1);
      if (poly > (std::numeric_limits<value_type>::max)()) {
        boost::throw_exception( std::range_error("sobol: polynomial value outside the given value type range") );
      }
      const unsigned degree = qrng_detail::msb(poly); // integer log2(poly)

      // set initial values of m from table
      for (unsigned k = 0; k != degree; ++k)
        cj[dimension*k + dim] = SobolTables::minit(dim-1, k);

      // Calculate remaining elements for this dimension,
      // as explained in Bratley+Fox, section 2.
      for (unsigned j = degree; j < bit_count; ++j)
      {
        typename SobolTables::value_type p_i = poly;
        const std::size_t bit_offset = dimension*j + dim;

        cj[bit_offset] = cj[dimension*(j-degree) + dim];
        for (unsigned k = 0; k != degree; ++k, p_i >>= 1)
        {
          int rem = degree - k;
          cj[bit_offset] ^= ((p_i & 1) * cj[dimension*(j-rem) + dim]) << rem;
        }
      }
    }

    // Shift columns by appropriate power of 2.
    unsigned p = 1u;
    for (int j = bit_count-1-1; j >= 0; --j, ++p)
    {
      const std::size_t bit_offset = dimension * j;
      for (std::size_t dim = 0; dim != dimension; ++dim)
        cj[bit_offset + dim] <<= p;
    }

    bits.swap(cj);
  }

  typename container_type::const_iterator iter_at(std::size_t n) const
  {
    BOOST_ASSERT(!(n > bits.size()));
    return bits.begin() + n;
  }

private:
  container_type bits;
};

} // namespace qrng_detail

typedef detail::qrng_tables::sobol default_sobol_table;

/** @endcond */

//!Instantiations of class template sobol_engine model a \quasi_random_number_generator.
//!The sobol_engine uses the algorithm described in
//! \blockquote
//![Bratley+Fox, TOMS 14, 88 (1988)]
//!and [Antonov+Saleev, USSR Comput. Maths. Math. Phys. 19, 252 (1980)]
//! \endblockquote
//!
//!\attention sobol_engine skips trivial zeroes at the start of the sequence. For example, the beginning
//!of the 2-dimensional Sobol sequence in @c uniform_01 distribution will look like this:
//!\code{.cpp}
//!0.5, 0.5,
//!0.75, 0.25,
//!0.25, 0.75,
//!0.375, 0.375,
//!0.875, 0.875,
//!...
//!\endcode
//!
//!In the following documentation @c X denotes the concrete class of the template
//!sobol_engine returning objects of type @c UIntType, u and v are the values of @c X.
//!
//!Some member functions may throw exceptions of type @c std::range_error. This
//!happens when the quasi-random domain is exhausted and the generator cannot produce
//!any more values. The length of the low discrepancy sequence is given by \f$L=Dimension \times (2^{w} - 1)\f$.
template<typename UIntType, unsigned w, typename SobolTables = default_sobol_table>
class sobol_engine
  : public qrng_detail::gray_coded_qrng<
      qrng_detail::sobol_lattice<UIntType, w, SobolTables>
    >
{
  typedef qrng_detail::sobol_lattice<UIntType, w, SobolTables> lattice_t;
  typedef qrng_detail::gray_coded_qrng<lattice_t> base_t;

public:
  //!Effects: Constructs the default `s`-dimensional Sobol quasi-random number generator.
  //!
  //!Throws: bad_alloc, invalid_argument, range_error.
  explicit sobol_engine(std::size_t s)
    : base_t(s)
  {}

  // default copy c-tor is fine

#ifdef BOOST_RANDOM_DOXYGEN
  //=========================Doxygen needs this!==============================
  typedef UIntType result_type;

  /** @copydoc boost::random::niederreiter_base2_engine::min() */
  static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
  { return (base_t::min)(); }

  /** @copydoc boost::random::niederreiter_base2_engine::max() */
  static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
  { return (base_t::max)(); }

  /** @copydoc boost::random::niederreiter_base2_engine::dimension() */
  std::size_t dimension() const { return base_t::dimension(); }

  /** @copydoc boost::random::niederreiter_base2_engine::seed() */
  void seed()
  {
    base_t::seed();
  }

  /** @copydoc boost::random::niederreiter_base2_engine::seed(UIntType) */
  void seed(UIntType init)
  {
    base_t::seed(init);
  }

  /** @copydoc boost::random::niederreiter_base2_engine::operator()() */
  result_type operator()()
  {
    return base_t::operator()();
  }

  /** @copydoc boost::random::niederreiter_base2_engine::discard(boost::uintmax_t) */
  void discard(boost::uintmax_t z)
  {
    base_t::discard(z);
  }

  /** Returns true if the two generators will produce identical sequences of outputs. */
  BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(sobol_engine, x, y)
  { return static_cast<const base_t&>(x) == y; }

  /** Returns true if the two generators will produce different sequences of outputs. */
  BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(sobol_engine)

  /** Writes the textual representation of the generator to a @c std::ostream. */
  BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, sobol_engine, s)
  { return os << static_cast<const base_t&>(s); }

  /** Reads the textual representation of the generator from a @c std::istream. */
  BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, sobol_engine, s)
  { return is >> static_cast<base_t&>(s); }

#endif // BOOST_RANDOM_DOXYGEN
};

/**
 * @attention This specialization of \sobol_engine supports up to 3667 dimensions.
 *
 * Data on the primitive binary polynomials `a` and the corresponding starting values `m`
 * for Sobol sequences in up to 21201 dimensions was taken from
 *
 *  @blockquote
 *  S. Joe and F. Y. Kuo, Constructing Sobol sequences with better two-dimensional projections,
 *  SIAM J. Sci. Comput. 30, 2635-2654 (2008).
 *  @endblockquote
 *
 * See the original tables up to dimension 21201: https://web.archive.org/web/20170802022909/http://web.maths.unsw.edu.au/~fkuo/sobol/new-joe-kuo-6.21201
 *
 * For practical reasons the default table uses only the subset of binary polynomials `a` < 2<sup>16</sup>.
 *
 * However, it is possible to provide your own table to \sobol_engine should the default one be insufficient.
 */
typedef sobol_engine<boost::uint_least64_t, 64u, default_sobol_table> sobol;

} // namespace random

} // namespace boost

#endif // BOOST_RANDOM_SOBOL_HPP

/* sobol.hpp
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
*/