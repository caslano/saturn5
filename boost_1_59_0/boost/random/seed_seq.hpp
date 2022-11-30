/* boost random/seed_seq.hpp header file
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 */

#ifndef BOOST_RANDOM_SEED_SEQ_HPP
#define BOOST_RANDOM_SEED_SEQ_HPP

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

namespace boost {
namespace random {

/**
 * The class @c seed_seq stores a sequence of 32-bit words
 * for seeding a \pseudo_random_number_generator.  These
 * words will be combined to fill the entire state of the
 * generator.
 */
class seed_seq {
public:
    typedef boost::uint_least32_t result_type;

    /** Initializes a seed_seq to hold an empty sequence. */
    seed_seq() {}
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    /** Initializes the sequence from an initializer_list. */
    template<class T>
    seed_seq(const std::initializer_list<T>& il) : v(il.begin(), il.end()) {}
#endif
    /** Initializes the sequence from an iterator range. */
    template<class Iter>
    seed_seq(Iter first, Iter last) : v(first, last) {}
    /** Initializes the sequence from Boost.Range range. */
    template<class Range>
    explicit seed_seq(const Range& range)
      : v(boost::begin(range), boost::end(range)) {}

    /**
     * Fills a range with 32-bit values based on the stored sequence.
     *
     * Requires: Iter must be a Random Access Iterator whose value type
     * is an unsigned integral type at least 32 bits wide.
     */
    template<class Iter>
    void generate(Iter first, Iter last) const
    {
        typedef typename std::iterator_traits<Iter>::value_type value_type;
        std::fill(first, last, static_cast<value_type>(0x8b8b8b8bu));
        std::size_t s = v.size();
        std::size_t n = last - first;
        std::size_t t =
            (n >= 623) ? 11 :
            (n >=  68) ?  7 :
            (n >=  39) ?  5 :
            (n >=   7) ?  3 :
            (n - 1)/2;
        std::size_t p = (n - t) / 2;
        std::size_t q = p + t;
        std::size_t m = (std::max)(s+1, n);
        value_type mask = 0xffffffffu;
        for(std::size_t k = 0; k < m; ++k) {
            value_type r1 = static_cast<value_type>
                (*(first + k%n) ^ *(first + (k+p)%n) ^ *(first + (k+n-1)%n));
            r1 = r1 ^ (r1 >> 27);
            r1 = (r1 * 1664525u) & mask;
            value_type r2 = static_cast<value_type>(r1 +
                ((k == 0) ? s :
                 (k <= s) ? k % n + v[k - 1] :
                 (k % n)));
            *(first + (k+p)%n) = (*(first + (k+p)%n) + r1) & mask;
            *(first + (k+q)%n) = (*(first + (k+q)%n) + r2) & mask;
            *(first + k%n) = r2;
        }
        for(std::size_t k = m; k < m + n; ++k) {
            value_type r3 = static_cast<value_type>
                ((*(first + k%n) + *(first + (k+p)%n) + *(first + (k+n-1)%n))
                & mask);
            r3 = r3 ^ (r3 >> 27);
            r3 = (r3 * 1566083941u) & mask;
            value_type r4 = static_cast<value_type>(r3 - k%n);
            *(first + (k+p)%n) ^= r3;
            *(first + (k+q)%n) ^= r4;
            *(first + k%n) = r4;
        }
    }
    /** Returns the size of the sequence. */
    std::size_t size() const { return v.size(); }
    /** Writes the stored sequence to iter. */
    template<class Iter>
    void param(Iter out) { std::copy(v.begin(), v.end(), out); }
private:
    std::vector<result_type> v;
};

}
}

#endif

/* seed_seq.hpp
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
*/