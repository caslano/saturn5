/* boost random/faure.hpp header file
 *
 * Copyright Justinas Vygintas Daugmaudis 2010-2018
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_RANDOM_FAURE_HPP
#define BOOST_RANDOM_FAURE_HPP

#include <boost/random/detail/qrng_base.hpp>

#include <cmath>
#include <vector>
#include <algorithm>

#include <boost/assert.hpp>

namespace boost {
namespace random {

/** @cond */
namespace detail {

namespace qrng_tables {

// There is no particular reason why 187 first primes were chosen
// to be put into this table. The only reason was, perhaps, that
// the number of dimensions for Faure generator would be around
// the same order of magnitude as the number of dimensions supported
// by the Sobol qrng.
struct primes
{
  typedef unsigned short value_type;

  BOOST_STATIC_CONSTANT(int, number_of_primes = 187);

  // A function that returns lower bound prime for a given n
  static value_type lower_bound(std::size_t n)
  {
    static const value_type prim_a[number_of_primes] = {
      2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
      59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
      127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
      191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
      257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
      331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
      401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
      467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557,
      563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619,
      631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
      709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787,
      797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
      877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953,
      967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031,
      1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093,
      1097, 1103, 1109, 1117 };

    qrng_detail::dimension_assert("Faure", n, prim_a[number_of_primes - 1]);

    return *std::lower_bound(prim_a, prim_a + number_of_primes, n);
  }
};

} // namespace qrng_tables
} // namespace detail

namespace qrng_detail {
namespace fr {

// Returns the integer part of the logarithm base Base of arg.
// In erroneous situations, e.g., integer_log(base, 0) the function
// returns 0 and does not report the error. This is the intended
// behavior.
template <typename T>
inline T integer_log(T base, T arg)
{
  T ilog = T();
  while (base <= arg)
  {
    arg /= base; ++ilog;
  }
  return ilog;
}

// Perform exponentiation by squaring (potential for code reuse in multiprecision::powm)
template <typename T>
inline T integer_pow(T base, T e)
{
  T result = static_cast<T>(1);
  while (e)
  {
    if (e & static_cast<T>(1))
      result *= base;
    e >>= 1;
    base *= base;
  }
  return result;
}

} // namespace fr

// Computes a table of binomial coefficients modulo qs.
template<typename RealType, typename SeqSizeT, typename PrimeTable>
struct binomial_coefficients
{
  typedef RealType value_type;
  typedef SeqSizeT size_type;

  // Binomial values modulo qs_base will never be bigger than qs_base.
  // We can choose an appropriate integer type to hold modulo values and
  // shave off memory footprint.
  typedef typename PrimeTable::value_type packed_uint_t;

  // default copy c-tor is fine

  explicit binomial_coefficients(std::size_t dimension)
  {
    resize(dimension);
  }

  void resize(std::size_t dimension)
  {
    qs_base = PrimeTable::lower_bound(dimension);

    // Throw away previously computed coefficients.
    // This will trigger recomputation on next update
    coeff.clear();
  }

  template <typename Iterator>
  void update(size_type seq, Iterator first, Iterator last)
  {
    if (first != last)
    {
      const size_type ilog = fr::integer_log(static_cast<size_type>(qs_base), seq);
      const size_type hisum = ilog + 1;
      if (coeff.size() != size_hint(hisum)) {
        ytemp.resize(static_cast<std::size_t>(hisum)); // cast safe because log is small
        compute_coefficients(hisum);
        qs_pow = fr::integer_pow(static_cast<size_type>(qs_base), ilog);
      }

      *first = compute_recip(seq, ytemp.rbegin());

      // Find other components using the Faure method.
      ++first;
      for ( ; first != last; ++first)
      {
        *first = RealType();
        RealType r = static_cast<RealType>(1);

        for (size_type i = 0; i != hisum; ++i)
        {
          RealType ztemp = ytemp[static_cast<std::size_t>(i)] * upper_element(i, i, hisum);
          for (size_type j = i + 1; j != hisum; ++j)
            ztemp += ytemp[static_cast<std::size_t>(j)] * upper_element(i, j, hisum);

          // Sum ( J <= I <= HISUM ) ( old ytemp(i) * binom(i,j) ) mod QS.
          ytemp[static_cast<std::size_t>(i)] = std::fmod(ztemp, static_cast<RealType>(qs_base));
          r *= static_cast<RealType>(qs_base);
          *first += ytemp[static_cast<std::size_t>(i)] / r;
        }
      }
    }
  }

private:
  inline static size_type size_hint(size_type n)
  {
    return n * (n + 1) / 2;
  }

  packed_uint_t& upper_element(size_type i, size_type j, size_type dim)
  {
    BOOST_ASSERT( i < dim );
    BOOST_ASSERT( j < dim );
    BOOST_ASSERT( i <= j );
    return coeff[static_cast<std::size_t>((i * (2 * dim - i + 1)) / 2 + j - i)];
  }

  template<typename Iterator>
  RealType compute_recip(size_type seq, Iterator out) const
  {
    // Here we do
    //   Sum ( 0 <= J <= HISUM ) YTEMP(J) * QS**J
    //   Sum ( 0 <= J <= HISUM ) YTEMP(J) / QS**(J+1)
    // in one go
    RealType r = RealType();
    size_type m, k = qs_pow;
    for( ; k != 0; ++out, seq = m, k /= qs_base )
    {
      m  = seq % k;
      RealType v  = static_cast<RealType>((seq - m) / k); // RealType <- size type
      r += v;
      r /= static_cast<RealType>(qs_base);
      *out = v; // saves double dereference
    }
    return r;
  }

  void compute_coefficients(const size_type n)
  {
    // Resize and initialize to zero
    coeff.resize(static_cast<std::size_t>(size_hint(n)));
    std::fill(coeff.begin(), coeff.end(), packed_uint_t());

    // The first row and the diagonal is assigned to 1
    upper_element(0, 0, n) = 1;
    for (size_type i = 1; i < n; ++i)
    {
      upper_element(0, i, n) = 1;
      upper_element(i, i, n) = 1;
    }

    // Computes binomial coefficients MOD qs_base
    for (size_type i = 1; i < n; ++i)
    {
      for (size_type j = i + 1; j < n; ++j)
      {
        upper_element(i, j, n) = ( upper_element(i, j-1, n) +
                                   upper_element(i-1, j-1, n) ) % qs_base;
      }
    }
  }

private:
  packed_uint_t qs_base;

  // here we cache precomputed data; note that binomial coefficients have
  // to be recomputed iff the integer part of the logarithm of seq changes,
  // which happens relatively rarely.
  std::vector<packed_uint_t> coeff; // packed upper (!) triangular matrix
  std::vector<RealType> ytemp;
  size_type qs_pow;
};

} // namespace qrng_detail

typedef detail::qrng_tables::primes default_faure_prime_table;

/** @endcond */

//!Instantiations of class template faure_engine model a \quasi_random_number_generator.
//!The faure_engine uses the algorithm described in
//! \blockquote
//!Henri Faure,
//!Discrepance de suites associees a un systeme de numeration (en dimension s),
//!Acta Arithmetica,
//!Volume 41, 1982, pages 337-351.
//! \endblockquote
//
//! \blockquote
//!Bennett Fox,
//!Algorithm 647:
//!Implementation and Relative Efficiency of Quasirandom
//!Sequence Generators,
//!ACM Transactions on Mathematical Software,
//!Volume 12, Number 4, December 1986, pages 362-376.
//! \endblockquote
//!
//!In the following documentation @c X denotes the concrete class of the template
//!faure_engine returning objects of type @c RealType, u and v are the values of @c X.
//!
//!Some member functions may throw exceptions of type @c std::bad_alloc.
template<typename RealType, typename SeqSizeT, typename PrimeTable = default_faure_prime_table>
class faure_engine
  : public qrng_detail::qrng_base<
      faure_engine<RealType, SeqSizeT, PrimeTable>
    , qrng_detail::binomial_coefficients<RealType, SeqSizeT, PrimeTable>
    , SeqSizeT
    >
{
  typedef faure_engine<RealType, SeqSizeT, PrimeTable> self_t;

  typedef qrng_detail::binomial_coefficients<RealType, SeqSizeT, PrimeTable> lattice_t;
  typedef qrng_detail::qrng_base<self_t, lattice_t, SeqSizeT> base_t;

  friend class qrng_detail::qrng_base<self_t, lattice_t, SeqSizeT>;

public:
  typedef RealType result_type;

  /** @copydoc boost::random::niederreiter_base2_engine::min() */
  static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
  { return static_cast<result_type>(0); }

  /** @copydoc boost::random::niederreiter_base2_engine::max() */
  static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
  { return static_cast<result_type>(1); }

  //!Effects: Constructs the `s`-dimensional default Faure quasi-random number generator.
  //!
  //!Throws: bad_alloc, invalid_argument.
  explicit faure_engine(std::size_t s)
    : base_t(s) // initialize the binomial table here
  {}

  /** @copydetails boost::random::niederreiter_base2_engine::seed(UIntType)
   * Throws: bad_alloc.
   */
  void seed(SeqSizeT init = 0)
  {
    compute_seq(init);
    base_t::reset_seq(init);
  }

#ifdef BOOST_RANDOM_DOXYGEN
  //=========================Doxygen needs this!==============================

  /** @copydoc boost::random::niederreiter_base2_engine::dimension() */
  std::size_t dimension() const { return base_t::dimension(); }

  /** @copydoc boost::random::niederreiter_base2_engine::operator()() */
  result_type operator()()
  {
    return base_t::operator()();
  }

  /** @copydoc boost::random::niederreiter_base2_engine::discard(boost::uintmax_t)
   * Throws: bad_alloc.
   */
  void discard(boost::uintmax_t z)
  {
    base_t::discard(z);
  }

  /** Returns true if the two generators will produce identical sequences of outputs. */
  BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(faure_engine, x, y)
  { return static_cast<const base_t&>(x) == y; }

  /** Returns true if the two generators will produce different sequences of outputs. */
  BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(faure_engine)

  /** Writes the textual representation of the generator to a @c std::ostream. */
  BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, faure_engine, s)
  { return os << static_cast<const base_t&>(s); }

  /** Reads the textual representation of the generator from a @c std::istream. */
  BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, faure_engine, s)
  { return is >> static_cast<base_t&>(s); }

#endif // BOOST_RANDOM_DOXYGEN

private:
/** @cond hide_private_members */
  void compute_seq(SeqSizeT seq)
  {
    qrng_detail::check_seed_sign(seq);
    this->lattice.update(seq, this->state_begin(), this->state_end());
  }
/** @endcond */
};

/**
 * @attention This specialization of \faure_engine supports up to 1117 dimensions.
 *
 * However, it is possible to provide your own prime table to \faure_engine should the default one be insufficient.
 */
typedef faure_engine<double, boost::uint_least64_t, default_faure_prime_table> faure;

} // namespace random

} // namespace boost

#endif // BOOST_RANDOM_FAURE_HPP

/* faure.hpp
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
*/