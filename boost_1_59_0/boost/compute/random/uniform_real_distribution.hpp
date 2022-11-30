//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP

#include <boost/assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/detail/literal.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// \class uniform_real_distribution
/// \brief Produces uniformly distributed random floating-point numbers.
///
/// The following example shows how to setup a uniform real distribution to
/// produce random \c float values between \c 1 and \c 100.
///
/// \snippet test/test_uniform_real_distribution.cpp generate
///
/// \see default_random_engine, normal_distribution
template<class RealType = float>
class uniform_real_distribution
{
public:
    typedef RealType result_type;

    /// Creates a new uniform distribution producing numbers in the range
    /// [\p a, \p b).
    /// Requires a < b
    uniform_real_distribution(RealType a = 0.f, RealType b = 1.f)
        : m_a(a),
          m_b(b)
    {
        BOOST_ASSERT(a < b);
    }

    /// Destroys the uniform_real_distribution object.
    ~uniform_real_distribution()
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

    /// Generates uniformly distributed floating-point numbers and stores
    /// them to the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        BOOST_COMPUTE_FUNCTION(RealType, scale_random, (const uint_ x),
        {
            return nextafter(LO + (convert_RealType(x) / MAX_RANDOM) * (HI - LO), (RealType) LO);
        });

        scale_random.define("LO", detail::make_literal(m_a));
        scale_random.define("HI", detail::make_literal(m_b));
        scale_random.define("MAX_RANDOM", "UINT_MAX");
        scale_random.define(
            "convert_RealType", std::string("convert_") + type_name<RealType>()
        );
        scale_random.define("RealType", type_name<RealType>());

        generator.generate(
            first, last, scale_random, queue
        );
    }

    /// \internal_ (deprecated)
    template<class OutputIterator, class Generator>
    void fill(OutputIterator first,
              OutputIterator last,
              Generator &g,
              command_queue &queue)
    {
        generate(first, last, g, queue);
    }

private:
    RealType m_a;
    RealType m_b;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_floating_point<RealType>::value,
        "Template argument must be a floating point type"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP

/* uniform_real_distribution.hpp
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
*/