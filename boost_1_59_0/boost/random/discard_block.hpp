/* boost random/discard_block.hpp header file
 *
 * Copyright Jens Maurer 2002
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-03-02  created
 */

#ifndef BOOST_RANDOM_DISCARD_BLOCK_HPP
#define BOOST_RANDOM_DISCARD_BLOCK_HPP

#include <iostream>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/seed_impl.hpp>


namespace boost {
namespace random {

/**
 * The class template \discard_block_engine is a model of
 * \pseudo_random_number_generator.  It modifies
 * another generator by discarding parts of its output.
 * Out of every block of @c p results, the first @c r
 * will be returned and the rest discarded.
 *
 * Requires: 0 < p <= r
 */
template<class UniformRandomNumberGenerator, std::size_t p, std::size_t r>
class discard_block_engine
{
    typedef typename detail::seed_type<
        typename UniformRandomNumberGenerator::result_type>::type seed_type;
public:
    typedef UniformRandomNumberGenerator base_type;
    typedef typename base_type::result_type result_type;

    BOOST_STATIC_CONSTANT(std::size_t, block_size = p);
    BOOST_STATIC_CONSTANT(std::size_t, used_block = r);

    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    BOOST_STATIC_CONSTANT(std::size_t, total_block = p);
    BOOST_STATIC_CONSTANT(std::size_t, returned_block = r);

    BOOST_STATIC_ASSERT(total_block >= returned_block);

    /** Uses the default seed for the base generator. */
    discard_block_engine() : _rng(), _n(0) { }
    /** Constructs a new \discard_block_engine with a copy of rng. */
    explicit discard_block_engine(const base_type & rng) : _rng(rng), _n(0) { }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    /** Constructs a new \discard_block_engine with rng. */
    explicit discard_block_engine(base_type && rng) : _rng(rng), _n(0) { }
#endif

    /**
     * Creates a new \discard_block_engine and seeds the underlying
     * generator with @c value
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(discard_block_engine,
                                               seed_type, value)
    { _rng.seed(value); _n = 0; }
    
    /**
     * Creates a new \discard_block_engine and seeds the underlying
     * generator with @c seq
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(discard_block_engine, SeedSeq, seq)
    { _rng.seed(seq); _n = 0; }
    
    /**
     * Creates a new \discard_block_engine and seeds the underlying
     * generator with first and last.
     */
    template<class It> discard_block_engine(It& first, It last)
      : _rng(first, last), _n(0) { }
    
    /** default seeds the underlying generator. */
    void seed() { _rng.seed(); _n = 0; }
    /** Seeds the underlying generator with s. */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(discard_block_engine, seed_type, s)
    { _rng.seed(s); _n = 0; }
    /** Seeds the underlying generator with seq. */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(discard_block_engine, SeedSeq, seq)
    { _rng.seed(seq); _n = 0; }
    /** Seeds the underlying generator with first and last. */
    template<class It> void seed(It& first, It last)
    { _rng.seed(first, last); _n = 0; }

    /** Returns the underlying engine. */
    const base_type& base() const { return _rng; }

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        if(_n >= returned_block) {
            // discard values of random number generator
            // Don't use discard, since we still need to
            // be somewhat compatible with TR1.
            // _rng.discard(total_block - _n);
            for(std::size_t i = 0; i < total_block - _n; ++i) {
                _rng();
            }
            _n = 0;
        }
        ++_n;
        return _rng();
    }

    void discard(boost::uintmax_t z)
    {
        for(boost::uintmax_t j = 0; j < z; ++j) {
            (*this)();
        }
    }

    template<class It>
    void generate(It first, It last)
    { detail::generate(*this, first, last); }

    /**
     * Returns the smallest value that the generator can produce.
     * This is the same as the minimum of the underlying generator.
     */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return (base_type::min)(); }
    /**
     * Returns the largest value that the generator can produce.
     * This is the same as the maximum of the underlying generator.
     */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return (base_type::max)(); }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /** Writes a \discard_block_engine to a @c std::ostream. */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os,
               const discard_block_engine& s)
    {
        os << s._rng << ' ' << s._n;
        return os;
    }

    /** Reads a \discard_block_engine from a @c std::istream. */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is, discard_block_engine& s)
    {
        is >> s._rng >> std::ws >> s._n;
        return is;
    }
#endif

    /** Returns true if the two generators will produce identical sequences. */
    friend bool operator==(const discard_block_engine& x,
                           const discard_block_engine& y)
    { return x._rng == y._rng && x._n == y._n; }
    /** Returns true if the two generators will produce different sequences. */
    friend bool operator!=(const discard_block_engine& x,
                           const discard_block_engine& y)
    { return !(x == y); }

private:
    base_type _rng;
    std::size_t _n;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class URNG, std::size_t p, std::size_t r>
const bool discard_block_engine<URNG, p, r>::has_fixed_range;
template<class URNG, std::size_t p, std::size_t r>
const std::size_t discard_block_engine<URNG, p, r>::total_block;
template<class URNG, std::size_t p, std::size_t r>
const std::size_t discard_block_engine<URNG, p, r>::returned_block;
template<class URNG, std::size_t p, std::size_t r>
const std::size_t discard_block_engine<URNG, p, r>::block_size;
template<class URNG, std::size_t p, std::size_t r>
const std::size_t discard_block_engine<URNG, p, r>::used_block;
#endif

/// \cond \show_deprecated

template<class URNG, int p, int r>
class discard_block : public discard_block_engine<URNG, p, r>
{
    typedef discard_block_engine<URNG, p, r> base_t;
public:
    typedef typename base_t::result_type result_type;
    discard_block() {}
    template<class T>
    discard_block(T& arg) : base_t(arg) {}
    template<class T>
    discard_block(const T& arg) : base_t(arg) {}
    template<class It>
    discard_block(It& first, It last) : base_t(first, last) {}
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return (this->base().min)(); }
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return (this->base().max)(); }
};

/// \endcond

namespace detail {

    template<class Engine>
    struct generator_bits;
    
    template<class URNG, std::size_t p, std::size_t r>
    struct generator_bits<discard_block_engine<URNG, p, r> > {
        static std::size_t value() { return generator_bits<URNG>::value(); }
    };

    template<class URNG, int p, int r>
    struct generator_bits<discard_block<URNG, p, r> > {
        static std::size_t value() { return generator_bits<URNG>::value(); }
    };

}

} // namespace random

} // namespace boost

#endif // BOOST_RANDOM_DISCARD_BLOCK_HPP

/* discard_block.hpp
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
*/