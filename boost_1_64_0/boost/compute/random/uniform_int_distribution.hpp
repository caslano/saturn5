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
3eCqMgFV/4b9izi3rvOGGVUFk1wYOeif57Jgg885C1/Etf04ywRvT3rsrZaON1EaJpkO9vYP4V0G5L++3zBmWRlpxeb84HEHunEYs++hMVOFeeNLFQ0E6+bjr+ayEO/CKgH5ywc+1JUd3z/wuBVqhfNukhEkhHcuXxreZcTMPNVysP5sH+8DEdgtHtxjI2FShCyZhUGrQYz9jDmHNYD4HLExeaGlHo1B8+Fpcm+/OML6GNPXkdp7l2y1dt0gbp9fvmDQP80YuKcXSk3K5s682K0evtl9PdsiJGdlafMUCdz5OkF5OC8oqc1okJp563X77Ln5ufni6HlH6zMr2AH7ugKRJsTMHYOBBal7X6cew2l7ZJ090/+Z/8lIkQ3nlb8h2UtUxqokV5vPs0D09ZnxHl/G3yrLnS5Rlv/IvaQw7OMafxn7E3CqKIN9CMRG9pNbMwbuKw2lePyP3O38B2ffdV68Z38ZrV9p6gIxbZqDzOtzwuEgsxAhGsn+c3/T86Zn2T3uvs/v+jLK35KtcNbkJvPm3P7QwBlrRwutzX/k5BcH0+ms4/w2kjNnEagVocq582TQwTx8mVd92cc1b6TmE0GimJ3fYe9DcggZ6xwQaZLj8mKI0/8zVGcWVLgidHVlHur8FapTeW2k520NTjZ7fLf/01wWdLdUseTlcsi+u3NHuIR53mOewLXygvM4tbmZ7Db04P9C/SaZjMwKNT/PGXJ13Ocrfd0sJyPbLYbedU08+Qf1ZbdUUzH4kqZ6wRMR4sr2ZW+5OmGcqQWabWhaJaPO7TGoHTmaXKKNS7fANwXKk778tpOKG5vl1G7JIRLvuk/CVB7GPWueKI2QPQvHOenLBpJanxgxtX3a0JfWQ34mVHdhUQUza7n3TvZw2XMkp2zZ2+tkndq9rF4o+zLU39kkp+N8xAcNAsSFQ/0dLc3BUDa1ud+QoO73zeVhPWemo1319/4g36fwHBGKicJXc0Ts7OCyX0P1aqGloGFOqbS3O8Qpx3NE6ZyLW+bI/uXl2ObvoLplsI6ZElbzeu8S1/0jPIYuJJNEUFOj27J8zGNxu/+ExzAnyzK3qzFc3CvAft+XjSQmbZm2aW54W5JL7fe4hDgaMwbe62mRRJ3lsPAfW6fW3ect9dpVZ68+ABvIV7HPABM2e8lAnsUPGXIn9+WZmvTxzBnd8x2dbPLBmabHR5KNNbwY18k4M3Z5PJ8xcDpJgy2WXy/j9uPGWC139/gnFGmodmW1pmHHB5+RgUtmT723Hsu3yQW6zq/idzayBCf5LB58CdY+Sd/E/aGNKsoV1uhmP5qLk/l+dQU2FMRRtBEtEv8kT3pqCBuxS36Fx9gXEQQVCjjWu8ma4y89ZluyyuHFsoZO7zo+HnPDo37TRHBNW3acNckLDnanj/JzW8gsmBkwD7+G1xV1IYbSEgRRL288Z2tjHn4N8yWqtGYqXs8HIwV8BvPlFvo0O06ec7z7goOOD3yXcPkWYsgwb/o+XMb2COI2Y4wQ3nHqyyzTJbxrgBhVS3nwp0wqeKPXJC+c39PsT8qXboGdLZwfwpwyK25UZLNcm5xfGjitzoI66+/MCV15BvoyVEcmWXMlqU93MOzzs+PjPtAlAf+AYUxlKYq51HXy7tUq1c7B3Bbcjvt9HbfDJh55yek6RxJ5+qKD47Pzg30wvq/j2dxC9XjSpkYWsuuTq0XlVWfYnEt2uH8/o69jW2samJt7pDXh7pMZAD6dc3nI58d9KP38Otu7nCfYbcit8/17471D6OS8BcykOJoxEBevxxQSY6Y0KoHm8Y3HPGZxpjiDfarHZRKLtYW2EOlHZycHdVD21u4aFOx8mMsrLyQvhrAZ08w=
*/