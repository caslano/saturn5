/* boost random/nierderreiter_base2.hpp header file
 *
 * Copyright Justinas Vygintas Daugmaudis 2010-2018
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_RANDOM_NIEDERREITER_BASE2_HPP
#define BOOST_RANDOM_NIEDERREITER_BASE2_HPP

#include <boost/random/detail/niederreiter_base2_table.hpp>
#include <boost/random/detail/gray_coded_qrng.hpp>

#include <boost/dynamic_bitset.hpp>

namespace boost {
namespace random {

/** @cond */
namespace qrng_detail {
namespace nb2 {

// Return the base 2 logarithm for a given bitset v
template <typename DynamicBitset>
inline typename DynamicBitset::size_type
bitset_log2(const DynamicBitset& v)
{
  if (v.none())
    boost::throw_exception( std::invalid_argument("bitset_log2") );

  typename DynamicBitset::size_type hibit = v.size() - 1;
  while (!v.test(hibit))
    --hibit;
  return hibit;
}


// Multiply polynomials over Z_2.
template <typename PolynomialT, typename DynamicBitset>
inline void modulo2_multiply(PolynomialT P, DynamicBitset& v, DynamicBitset& pt)
{
  pt.reset(); // pt == 0
  for (; P; P >>= 1, v <<= 1)
    if (P & 1) pt ^= v;
  pt.swap(v);
}


// Calculate the values of the constants V(J,R) as
// described in BFN section 3.3.
//
// pb = polynomial defined in section 2.3 of BFN.
template <typename DynamicBitset>
inline void calculate_v(const DynamicBitset& pb,
  typename DynamicBitset::size_type kj,
  typename DynamicBitset::size_type pb_degree,
  DynamicBitset& v)
{
  typedef typename DynamicBitset::size_type size_type;

  // Now choose values of V in accordance with
  // the conditions in section 3.3.
  size_type r = 0;
  for ( ; r != kj; ++r)
    v.reset(r);

  // Quoting from BFN: "Our program currently sets each K_q
  // equal to eq. This has the effect of setting all unrestricted
  // values of v to 1."
  for ( ; r < pb_degree; ++r)
    v.set(r);

  // Calculate the remaining V's using the recursion of section 2.3,
  // remembering that the B's have the opposite sign.
  for ( ; r != v.size(); ++r)
  {
    bool term = false;
    for (typename DynamicBitset::size_type k = 0; k < pb_degree; ++k)
    {
      term ^= pb.test(k) & v[r + k - pb_degree];
    }
    v[r] = term;
  }
}

} // namespace nb2

template<typename UIntType, unsigned w, typename Nb2Table>
struct niederreiter_base2_lattice
{
  typedef UIntType value_type;

  BOOST_STATIC_ASSERT(w > 0u);
  BOOST_STATIC_CONSTANT(unsigned, bit_count = w);

private:
  typedef std::vector<value_type> container_type;

public:
  explicit niederreiter_base2_lattice(std::size_t dimension)
  {
    resize(dimension);
  }

  void resize(std::size_t dimension)
  {
    typedef boost::dynamic_bitset<> bitset_type;

    dimension_assert("Niederreiter base 2", dimension, Nb2Table::max_dimension);

    // Initialize the bit array
    container_type cj(bit_count * dimension);

    // Reserve temporary space for lattice computation
    bitset_type v, pb, tmp;

    // Compute Niedderreiter base 2 lattice
    for (std::size_t dim = 0; dim != dimension; ++dim)
    {
      const typename Nb2Table::value_type poly = Nb2Table::polynomial(dim);
      if (poly > (std::numeric_limits<value_type>::max)()) {
        boost::throw_exception( std::range_error("niederreiter_base2: polynomial value outside the given value type range") );
      }

      const unsigned degree = qrng_detail::msb(poly); // integer log2(poly)
      const unsigned space_required = degree * ((bit_count / degree) + 1); // ~ degree + bit_count

      v.resize(degree + bit_count - 1);

      // For each dimension, we need to calculate powers of an
      // appropriate irreducible polynomial, see Niederreiter
      // page 65, just below equation (19).
      // Copy the appropriate irreducible polynomial into PX,
      // and its degree into E. Set polynomial B = PX ** 0 = 1.
      // M is the degree of B. Subsequently B will hold higher
      // powers of PX.
      pb.resize(space_required); tmp.resize(space_required);

      typename bitset_type::size_type kj, pb_degree = 0;
      pb.reset(); // pb == 0
      pb.set(pb_degree); // set the proper bit for the pb_degree

      value_type j = high_bit_mask_t<bit_count - 1>::high_bit;
      do
      {
        // Now choose a value of Kj as defined in section 3.3.
        // We must have 0 <= Kj < E*J = M.
        // The limit condition on Kj does not seem to be very relevant
        // in this program.
        kj = pb_degree;

        // Now multiply B by PX so B becomes PX**J.
        // In section 2.3, the values of Bi are defined with a minus sign :
        // don't forget this if you use them later!
        nb2::modulo2_multiply(poly, pb, tmp);
        pb_degree += degree;
        if (pb_degree >= pb.size()) {
          // Note that it is quite possible for kj to become bigger than
          // the new computed value of pb_degree.
          pb_degree = nb2::bitset_log2(pb);
        }

        // If U = 0, we need to set B to the next power of PX
        // and recalculate V.
        nb2::calculate_v(pb, kj, pb_degree, v);

        // Niederreiter (page 56, after equation (7), defines two
        // variables Q and U.  We do not need Q explicitly, but we
        // do need U.

        // Advance Niederreiter's state variables.
        for (unsigned u = 0; j && u != degree; ++u, j >>= 1)
        {
          // Now C is obtained from V. Niederreiter
          // obtains A from V (page 65, near the bottom), and then gets
          // C from A (page 56, equation (7)).  However this can be done
          // in one step.  Here CI(J,R) corresponds to
          // Niederreiter's C(I,J,R), whose values we pack into array
          // CJ so that CJ(I,R) holds all the values of C(I,J,R) for J from 1 to NBITS.
          for (unsigned r = 0; r != bit_count; ++r) {
            value_type& num = cj[dimension * r + dim];
            // set the jth bit in num
            num = (num & ~j) | (-v[r + u] & j);
          }
        }
      } while (j != 0);
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

typedef detail::qrng_tables::niederreiter_base2 default_niederreiter_base2_table;

/** @endcond */

//!Instantiations of class template niederreiter_base2_engine model a \quasi_random_number_generator.
//!The niederreiter_base2_engine uses the algorithm described in
//! \blockquote
//!Bratley, Fox, Niederreiter, ACM Trans. Model. Comp. Sim. 2, 195 (1992).
//! \endblockquote
//!
//!\attention niederreiter_base2_engine skips trivial zeroes at the start of the sequence. For example,
//!the beginning of the 2-dimensional Niederreiter base 2 sequence in @c uniform_01 distribution will look
//!like this:
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
//!niederreiter_base2_engine returning objects of type @c UIntType, u and v are the values of @c X.
//!
//!Some member functions may throw exceptions of type std::range_error. This
//!happens when the quasi-random domain is exhausted and the generator cannot produce
//!any more values. The length of the low discrepancy sequence is given by
//! \f$L=Dimension \times (2^{w} - 1)\f$.
template<typename UIntType, unsigned w, typename Nb2Table = default_niederreiter_base2_table>
class niederreiter_base2_engine
  : public qrng_detail::gray_coded_qrng<
      qrng_detail::niederreiter_base2_lattice<UIntType, w, Nb2Table>
    >
{
  typedef qrng_detail::niederreiter_base2_lattice<UIntType, w, Nb2Table> lattice_t;
  typedef qrng_detail::gray_coded_qrng<lattice_t> base_t;

public:
  //!Effects: Constructs the default `s`-dimensional Niederreiter base 2 quasi-random number generator.
  //!
  //!Throws: bad_alloc, invalid_argument, range_error.
  explicit niederreiter_base2_engine(std::size_t s)
    : base_t(s) // initialize lattice here
  {}

#ifdef BOOST_RANDOM_DOXYGEN
  //=========================Doxygen needs this!==============================
  typedef UIntType result_type;

  //!Returns: Tight lower bound on the set of values returned by operator().
  //!
  //!Throws: nothing.
  static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
  { return (base_t::min)(); }

  //!Returns: Tight upper bound on the set of values returned by operator().
  //!
  //!Throws: nothing.
  static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
  { return (base_t::max)(); }

  //!Returns: The dimension of of the quasi-random domain.
  //!
  //!Throws: nothing.
  std::size_t dimension() const { return base_t::dimension(); }

  //!Effects: Resets the quasi-random number generator state to
  //!the one given by the default construction. Equivalent to u.seed(0).
  //!
  //!\brief Throws: nothing.
  void seed()
  {
    base_t::seed();
  }

  //!Effects: Effectively sets the quasi-random number generator state to the `init`-th
  //!vector in the `s`-dimensional quasi-random domain, where `s` == X::dimension().
  //!\code
  //!X u, v;
  //!for(int i = 0; i < N; ++i)
  //!    for( std::size_t j = 0; j < u.dimension(); ++j )
  //!        u();
  //!v.seed(N);
  //!assert(u() == v());
  //!\endcode
  //!
  //!\brief Throws: range_error.
  void seed(UIntType init)
  {
    base_t::seed(init);
  }

  //!Returns: Returns a successive element of an `s`-dimensional
  //!(s = X::dimension()) vector at each invocation. When all elements are
  //!exhausted, X::operator() begins anew with the starting element of a
  //!subsequent `s`-dimensional vector.
  //!
  //!Throws: range_error.
  result_type operator()()
  {
    return base_t::operator()();
  }

  //!Effects: Advances *this state as if `z` consecutive
  //!X::operator() invocations were executed.
  //!\code
  //!X u = v;
  //!for(int i = 0; i < N; ++i)
  //!    u();
  //!v.discard(N);
  //!assert(u() == v());
  //!\endcode
  //!
  //!Throws: range_error.
  void discard(boost::uintmax_t z)
  {
    base_t::discard(z);
  }

  //!Returns true if the two generators will produce identical sequences of outputs.
  BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(niederreiter_base2_engine, x, y)
  { return static_cast<const base_t&>(x) == y; }

  //!Returns true if the two generators will produce different sequences of outputs.
  BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(niederreiter_base2_engine)

  //!Writes the textual representation of the generator to a @c std::ostream.
  BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, niederreiter_base2_engine, s)
  { return os << static_cast<const base_t&>(s); }

  //!Reads the textual representation of the generator from a @c std::istream.
  BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, niederreiter_base2_engine, s)
  { return is >> static_cast<base_t&>(s); }

#endif // BOOST_RANDOM_DOXYGEN
};


/**
 * @attention This specialization of \niederreiter_base2_engine supports up to 4720 dimensions.
 *
 * Binary irreducible polynomials (primes in the ring `GF(2)[X]`, evaluated at `X=2`) were generated
 * while condition `max(prime)` < 2<sup>16</sup> was satisfied.
 *
 * There are exactly 4720 such primes, which yields a Niederreiter base 2 table for 4720 dimensions.
 *
 * However, it is possible to provide your own table to \niederreiter_base2_engine should the default one be insufficient.
 */
typedef niederreiter_base2_engine<boost::uint_least64_t, 64u, default_niederreiter_base2_table> niederreiter_base2;

} // namespace random

} // namespace boost

#endif // BOOST_RANDOM_NIEDERREITER_BASE2_HPP

/* niederreiter_base2.hpp
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
*/