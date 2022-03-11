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