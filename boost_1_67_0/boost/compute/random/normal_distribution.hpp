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