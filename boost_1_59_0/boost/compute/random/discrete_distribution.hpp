//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_DISCRETE_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_DISCRETE_DISTRIBUTION_HPP

#include <numeric>

#include <boost/config.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/detail/literal.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// \class discrete_distribution
/// \brief Produces random integers on the interval [0, n), where
/// probability of each integer is given by the weight of the ith
/// integer divided by the sum of all weights.
///
/// The following example shows how to setup a discrete distribution to
/// produce 0 and 1 with equal probability
///
/// \snippet test/test_discrete_distribution.cpp generate
///
template<class IntType = uint_>
class discrete_distribution
{
public:
    typedef IntType result_type;

    /// Creates a new discrete distribution with a single weight p = { 1 }.
    /// This distribution produces only zeroes.
    discrete_distribution()
        : m_probabilities(1, double(1)),
          m_scanned_probabilities(1, double(1))
    {

    }

    /// Creates a new discrete distribution with weights given by
    /// the range [\p first, \p last).
    template<class InputIterator>
    discrete_distribution(InputIterator first, InputIterator last)
        : m_probabilities(first, last),
          m_scanned_probabilities(std::distance(first, last))
    {
        if(first != last) {
            // after this m_scanned_probabilities.back() is a sum of all
            // weights from the range [first, last)
            std::partial_sum(first, last, m_scanned_probabilities.begin());

            std::vector<double>::iterator i = m_probabilities.begin();
            std::vector<double>::iterator j = m_scanned_probabilities.begin();
            for(; i != m_probabilities.end(); ++i, ++j)
            {
                // dividing each weight by sum of all weights to
                // get probabilities
                *i = *i / m_scanned_probabilities.back();
                // dividing each partial sum of weights by sum of
                // all weights to get partial sums of probabilities
                *j = *j / m_scanned_probabilities.back();
            }
        }
        else {
            m_probabilities.push_back(double(1));
            m_scanned_probabilities.push_back(double(1));
        }
    }

    /// Destroys the discrete_distribution object.
    ~discrete_distribution()
    {
    }

    /// Returns the probabilities
    ::std::vector<double> probabilities() const
    {
        return m_probabilities;
    }

    /// Returns the minimum potentially generated value.
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        return result_type(0);
    }

    /// Returns the maximum potentially generated value.
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        size_t type_max = static_cast<size_t>(
            (std::numeric_limits<result_type>::max)()
        );
        if(m_probabilities.size() - 1 > type_max) {
            return (std::numeric_limits<result_type>::max)();
        }
        return static_cast<result_type>(m_probabilities.size() - 1);
    }

    /// Generates uniformly distributed integers and stores
    /// them to the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        std::string source = "inline IntType scale_random(uint x)\n";

        source = source +
            "{\n" +
            "float rno = convert_float(x) / UINT_MAX;\n";
        for(size_t i = 0; i < m_scanned_probabilities.size() - 1; i++)
        {
            source = source +
                "if(rno <= " + detail::make_literal<float>(m_scanned_probabilities[i]) + ")\n" +
                "   return " + detail::make_literal(i) + ";\n";
        }

        source = source +
            "return " + detail::make_literal(m_scanned_probabilities.size() - 1) + ";\n" +
            "}\n";

        BOOST_COMPUTE_FUNCTION(IntType, scale_random, (const uint_ x), {});

        scale_random.set_source(source);
        scale_random.define("IntType", type_name<IntType>());

        generator.generate(first, last, scale_random, queue);
    }

private:
    ::std::vector<double> m_probabilities;
    ::std::vector<double> m_scanned_probabilities;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_integral<IntType>::value,
        "Template argument must be integral"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP

/* discrete_distribution.hpp
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
*/