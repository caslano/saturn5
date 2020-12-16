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
+jc8TpYrIbxlnehwKJvnSGs8PitJG3h2NJHu/XsfRmMLUd/jcW65930I2xWcr72elQPyxbS7Omw8br3UtmEzg/Hu67oZssslMTllw4b1BOt6aL/LOdDg4hSpc+5kvLRhE9vw535VX9e2VkXyMl2zVvE5wLa2cL9rkFlLa0MQ9n+QGTYzeIP0IXyea57hSXnSIpVh+vW8++4gewmF1jbQO8sOGxrIDnPnQ9iGwbwLPsWp0wfz9m3w3/0wtgE5Y7QQnfR7R+eHBxcb37cH97hEeHHJFiEmLmxM72Kszhiwb7sggyimP1M+r+Z86+KNbS1+96THPo6zFmfBGGJ3MraNmbkc5LSgQfqk6HUcMKiwrtfvNK8wX5RG1KpItXljvrsHPp2pLlaw/5UPzqIfxraS2FZ+pktwr+3nnO2/ZLElw1l06E+eqJWGpX70WoiWXXjt2PlVICwlTAsqjVZTj27NcWi2GLBC3DeEM0TFEk0wcdibN5jBD/cj6HvvKRU0rli3n7qDz473+wju25y41Dys5cMdCqtyJkdxhshHhlimkYvsTFjJW5mvkRn2J9QOS7Q2skhr/ns7zls8Y+S3+qa+rq3MeS7ZpfrepCKeMPuOpGVv6ssKTmzijid2x2/S7Ydxu94cuLu9dXVQuwG4v4e4C3VBMSOmty4L9024qwx9X4wWkln+f8h8AGP+UeR7rVVRQdHKC/qhtcz368tyQ3wlldLH/11mnJeH9PUFIhwPtmSzCL3FY6tDlGW/gXsLaoeq80VmxiX7P+TfTcuYDzLZIhQzuvy/MkGck76+LaOzVc6JSfO/vDG+yeay357LQlxJ2cIcJ7pxAUIrFsfX+xPmM0xS79xKfTCX3WfL/jDwJaMyVYZvflE2+cBu97HhPEOpFjTGjb6fMxoMFTmINfAxfF+kzEo/57m5PGmOjtsnZ/vD9wNxB+Ici6p28fXc82jf3n7mLANwH/b1RCJZECzI3HPvLfcC+Jb0GM4IT1lzydlm/oan8NqQrfN1tPTLlsABfDsxt1FTvkTZc+/O+UP48r37xsfw9065opgiNqXhjIP7VHjFrC+o6uPnzXWDDrvH3MzSFFF8IFk/GeJDHIOvMW57MIw6VlC37Y82tz/1mC3etDjF1/mZbNhZ5if4QeD2F8qYtsb2BJfnL8Q6hH/OGPBBbuZAniDAXjvtPKW+PFn2EHj3+HF8RlLM06I5ngNH2Mf2oR8fc1y0c4DPZDlSbU1MW2fPhTB7cKaEbx2qg5HipFU5l3Hi1/13I8/JM3psISK3d2aFzTH1QFKcH3bgi94FW6Tb4INLx9r/4k0Ia4g2krIS6aa8EGIPcX9p4A6MyZhY2uBu2V1nP2rQ9fbYQCwrLfNkAr1t995tf2nvjxCfJEXKRFnalPXk8nm3mzPXXAHMP8wZolSpeAOc3Zu057ll/iHOQowVuraVbvbvVcswsgNpx7ZvLT4Fu6D/+wTij962TDYF+MG20d1RHvMJzF+yji33yn/n337Cwg9+8qguSliyzPPMyPMu6oOAw7PzGgO/64UdyLU6tMHLaaL8hz6YLQVdH4ANb2iDDpIp7xxuA/QEtOEbQxs459kYav97Gzb74VdDG4wsxlKdcRvgBdzOMv/+hnCSaN4e1Bg6fFi2m+fq0TnsDS8BvfEnMS+nQngtA+aFmQ/r9KEIp0jFGJ3VSNs0HFOeqZGXDLwicyZK0gPvIu9t8H9HOEsEs4EH5Ubi6VX45WG1wILMT4C3lgN35C2dNh/mHOhVwM72LoSTLTGtVkLYkfspO09p6pUNG8qXEJ6TIr1lLhjCD3fr7xv1wFcnyEse+7jHbG1gvz1wK18KM5vUAqg7O/DA60U=
*/