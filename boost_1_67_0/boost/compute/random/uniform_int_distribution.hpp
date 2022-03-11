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