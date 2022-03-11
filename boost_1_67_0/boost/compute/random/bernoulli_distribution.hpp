//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP

#include <boost/assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/literal.hpp>

namespace boost {
namespace compute {

///
/// \class bernoulli_distribution
/// \brief Produces random boolean values according to the following
/// discrete probability function with parameter p :
/// P(true/p) = p and P(false/p) = (1 - p)
///
/// The following example shows how to setup a bernoulli distribution to
/// produce random boolean values with parameter p = 0.25
///
/// \snippet test/test_bernoulli_distribution.cpp generate
///
template<class RealType = float>
class bernoulli_distribution
{
public:

    /// Creates a new bernoulli distribution
    bernoulli_distribution(RealType p = 0.5f)
        : m_p(p)
    {
    }

    /// Destroys the bernoulli_distribution object
    ~bernoulli_distribution()
    {
    }

    /// Returns the value of the parameter p
    RealType p() const
    {
        return m_p;
    }

    /// Generates bernoulli distributed booleans and stores
    /// them in the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        size_t count = detail::iterator_range_size(first, last);

        vector<uint_> tmp(count, queue.get_context());
        generator.generate(tmp.begin(), tmp.end(), queue);

        BOOST_COMPUTE_FUNCTION(bool, scale_random, (const uint_ x),
        {
            return (convert_RealType(x) / MAX_RANDOM) < PARAM;
        });

        scale_random.define("PARAM", detail::make_literal(m_p));
        scale_random.define("MAX_RANDOM", "UINT_MAX");
        scale_random.define(
            "convert_RealType", std::string("convert_") + type_name<RealType>()
        );

        transform(
            tmp.begin(), tmp.end(), first, scale_random, queue
        );
    }

private:
    RealType m_p;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_floating_point<RealType>::value,
        "Template argument must be a floating point type"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP

/* bernoulli_distribution.hpp
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
*/