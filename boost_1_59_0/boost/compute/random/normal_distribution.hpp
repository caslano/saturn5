//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_NORMAL_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_NORMAL_DISTRIBUTION_HPP

#include <limits>

#include <boost/assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/type_traits/make_vector_type.hpp>

namespace boost {
namespace compute {

/// \class normal_distribution
/// \brief Produces random, normally-distributed floating-point numbers.
///
/// The following example shows how to setup a normal distribution to
/// produce random \c float values centered at \c 5:
///
/// \snippet test/test_normal_distribution.cpp generate
///
/// \see default_random_engine, uniform_real_distribution
template<class RealType = float>
class normal_distribution
{
public:
    typedef RealType result_type;

    /// Creates a new normal distribution producing numbers with the given
    /// \p mean and \p stddev.
    normal_distribution(RealType mean = 0.f, RealType stddev = 1.f)
        : m_mean(mean),
          m_stddev(stddev)
    {
    }

    /// Destroys the normal distribution object.
    ~normal_distribution()
    {
    }

    /// Returns the mean value of the distribution.
    result_type mean() const
    {
        return m_mean;
    }

    /// Returns the standard-deviation of the distribution.
    result_type stddev() const
    {
        return m_stddev;
    }

    /// Returns the minimum value of the distribution.
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        return -std::numeric_limits<RealType>::infinity();
    }

    /// Returns the maximum value of the distribution.
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        return std::numeric_limits<RealType>::infinity();
    }

    /// Generates normally-distributed floating-point numbers and stores
    /// them to the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        typedef typename make_vector_type<RealType, 2>::type RealType2;

        size_t count = detail::iterator_range_size(first, last);

        vector<uint_> tmp(count, queue.get_context());
        generator.generate(tmp.begin(), tmp.end(), queue);

        BOOST_COMPUTE_FUNCTION(RealType2, box_muller, (const uint2_ x),
        {
            const RealType one = 1;
            const RealType two = 2;

            // Use nextafter to push values down into [0,1) range; without this, floating point rounding can
            // lead to have x1 = 1, but that would lead to taking the log of 0, which would result in negative
            // infinities; by pushing the values off 1 towards 0, we ensure this won't happen.
            const RealType x1 = nextafter(x.x / (RealType) UINT_MAX, (RealType) 0);
            const RealType x2 = x.y / (RealType) UINT_MAX;

            const RealType rho = sqrt(-two * log(one-x1));

            const RealType z1 = rho * cos(two * M_PI_F * x2);
            const RealType z2 = rho * sin(two * M_PI_F * x2);

            return (RealType2)(MEAN, MEAN) + (RealType2)(z1, z2) * (RealType2)(STDDEV, STDDEV);
        });

        box_muller.define("MEAN", boost::lexical_cast<std::string>(m_mean));
        box_muller.define("STDDEV", boost::lexical_cast<std::string>(m_stddev));
        box_muller.define("RealType", type_name<RealType>());
        box_muller.define("RealType2", type_name<RealType2>());

        transform(
            make_buffer_iterator<uint2_>(tmp.get_buffer(), 0),
            make_buffer_iterator<uint2_>(tmp.get_buffer(), count / 2),
            make_buffer_iterator<RealType2>(first.get_buffer(), 0),
            box_muller,
            queue
        );
    }

private:
    RealType m_mean;
    RealType m_stddev;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_floating_point<RealType>::value,
        "Template argument must be a floating point type"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_NORMAL_DISTRIBUTION_HPP

/* normal_distribution.hpp
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
*/