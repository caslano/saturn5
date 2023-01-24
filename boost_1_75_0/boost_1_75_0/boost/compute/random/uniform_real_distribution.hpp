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
P/2MfaC1SpX1iMj/lQ3A62NYKZYgYSmGvCX8xpBCDHkf1+HrCM6oFFh/YvH28tNIrtNMuc25Mk5EfvkCrxnEJfX49NnwSIHmFxYn6FvFPt2nxJ6XKVP7XtZoAvfBgunBA9+MExiEVxH/YmgWROsi+TbhvwQfHFgb8gF48JEZVN4JznK+uJwym2dpV6yRyBUOHhD02oNXMusEmu4e1cU4VPJf9TAPMqTE26uHxxyWuG6FfLICT6IhJDOv6K9SSuzJYl8AT9PDshwyHWLW/ec5AOsgw46ccIkczl2MDcQfXU636FPdzNv1M2+V9eF7xK3kzUzKCRA4fR34T/YHIgjhLwWNLmh9mvGJHx6iVwpMe+R0epEv80rOI8BKRAZVtBP+6P74spKS3LtFXrvIiC37ADAsz9MN+Bl8m0SvQIMDHwicLNrrgwePa7H/wyNe/M0kkqbAnK1g/hTvbNHqpALw0Do5WzZfpj2Z8kqEdxT4+0Gmh5Dj4NOaDsDLMwUvMT/ZrcRfCqf7QH8KfRjyUgwpOXkQmvI+HzzgE0i48Pj1/JGgTYHVI8P0A/bEfoUTfXCObt4Hr5c5QjmfHZYQ73xsOQ9NNB3AosiIgIii/sB66VXwjhCsB2ok8WUp5u8xYpgPYAF4S0HP3O2Dh1gxeBwCg0BiQEvl/G7JR9GvkF1ezl4DVugJwIPFp5+1BtBSe+dhdCuJ0kiXqUu6zC9W
*/