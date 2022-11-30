//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_RANDOM_SHUFFLE_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_RANDOM_SHUFFLE_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>
#ifdef BOOST_NO_CXX98_RANDOM_SHUFFLE
#include <cstdlib>
#endif

namespace boost
{
    namespace range
    {

        namespace detail
        {
#ifdef BOOST_NO_CXX98_RANDOM_SHUFFLE

// wrap std::rand as UniformRandomBitGenerator
struct wrap_rand
{
    typedef unsigned int result_type;

    static BOOST_CONSTEXPR result_type (min)()
    {
        return 0;
    }

    static BOOST_CONSTEXPR result_type (max)()
    {
        return RAND_MAX;
    }

    result_type operator()()
    {
        return std::rand();
    }
};

template< class RandomIt >
inline void random_shuffle(RandomIt first, RandomIt last)
{
    std::shuffle(first, last, wrap_rand());
}

// wrap Generator as UniformRandomBitGenerator
template< class Generator >
struct wrap_generator
{
    typedef unsigned int result_type;
    static const int max_arg = ((0u - 1u) >> 2) + 1;
    Generator& g;

    wrap_generator(Generator& gen) : g(gen) {}

    static BOOST_CONSTEXPR result_type (min)()
    {
        return 0;
    }

    static BOOST_CONSTEXPR result_type (max)()
    {
        return max_arg - 1;
    }

    result_type operator()()
    {
        return static_cast<result_type>(g(max_arg));
    }
};

template< class RandomIt, class Generator >
inline void random_shuffle(RandomIt first, RandomIt last, Generator& gen)
{
    std::shuffle(first, last, wrap_generator< Generator >(gen));
}

#else
    
using std::random_shuffle;

#endif  
        } // namespace detail

/// \brief template function random_shuffle
///
/// range-based version of the random_shuffle std algorithm
///
/// \pre RandomAccessRange is a model of the RandomAccessRangeConcept
/// \pre Generator is a model of the UnaryFunctionConcept
template<class RandomAccessRange>
inline RandomAccessRange& random_shuffle(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    detail::random_shuffle(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange>
inline const RandomAccessRange& random_shuffle(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    detail::random_shuffle(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange, class Generator>
inline RandomAccessRange& random_shuffle(RandomAccessRange& rng, Generator& gen)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    detail::random_shuffle(boost::begin(rng), boost::end(rng), gen);
    return rng;
}

/// \overload
template<class RandomAccessRange, class Generator>
inline const RandomAccessRange& random_shuffle(const RandomAccessRange& rng, Generator& gen)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    detail::random_shuffle(boost::begin(rng), boost::end(rng), gen);
    return rng;
}

    } // namespace range
    using range::random_shuffle;
} // namespace boost

#endif // include guard

/* random_shuffle.hpp
++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
*/