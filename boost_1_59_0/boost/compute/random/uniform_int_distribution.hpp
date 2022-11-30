//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP

#include <limits>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/algorithm/transform.hpp>

namespace boost {
namespace compute {

/// \class uniform_int_distribution
/// \brief Produces uniformily distributed random integers
///
/// The following example shows how to setup a uniform int distribution to
/// produce random integers 0 and 1.
///
/// \snippet test/test_uniform_int_distribution.cpp generate
///
template<class IntType = uint_>
class uniform_int_distribution
{
public:
    typedef IntType result_type;

    /// Creates a new uniform distribution producing numbers in the range
    /// [\p a, \p b].
    explicit uniform_int_distribution(IntType a = 0,
                                      IntType b = (std::numeric_limits<IntType>::max)())
        : m_a(a),
          m_b(b)
    {
    }

    /// Destroys the uniform_int_distribution object.
    ~uniform_int_distribution()
    {
    }

    /// Returns the minimum value of the distribution.
    result_type a() const
    {
        return m_a;
    }

    /// Returns the maximum value of the distribution.
    result_type b() const
    {
        return m_b;
    }

    /// Generates uniformily distributed integers and stores
    /// them to the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        size_t size = std::distance(first, last);
        typedef typename Generator::result_type g_result_type;

        vector<g_result_type> tmp(size, queue.get_context());
        vector<g_result_type> tmp2(size, queue.get_context());

        uint_ bound = ((uint_(-1))/(m_b-m_a+1))*(m_b-m_a+1);

        buffer_iterator<g_result_type> tmp2_iter;

        while(size>0)
        {
            generator.generate(tmp.begin(), tmp.begin() + size, queue);
            tmp2_iter = copy_if(tmp.begin(), tmp.begin() + size, tmp2.begin(),
                                _1 <= bound, queue);
            size = std::distance(tmp2_iter, tmp2.end());
        }

        BOOST_COMPUTE_FUNCTION(IntType, scale_random, (const g_result_type x),
        {
            return LO + (x % (HI-LO+1));
        });

        scale_random.define("LO", boost::lexical_cast<std::string>(m_a));
        scale_random.define("HI", boost::lexical_cast<std::string>(m_b));

        transform(tmp2.begin(), tmp2.end(), first, scale_random, queue);
    }

private:
    IntType m_a;
    IntType m_b;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_integral<IntType>::value,
        "Template argument must be integral"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP

/* uniform_int_distribution.hpp
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
*/