///////////////////////////////////////////////////////////////////////////////
// weighted_kurtosis.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_KURTOSIS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_KURTOSIS_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/weighted_moment.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_kurtosis_impl
    /**
        @brief Kurtosis estimation for weighted samples

        The kurtosis of a sample distribution is defined as the ratio of the 4th central moment and the square of the 2nd central
        moment (the variance) of the samples, minus 3. The term \f$ -3 \f$ is added in order to ensure that the normal distribution
        has zero kurtosis. The kurtosis can also be expressed by the simple moments:

        \f[
            \hat{g}_2 =
                \frac
                {\widehat{m}_n^{(4)}-4\widehat{m}_n^{(3)}\hat{\mu}_n+6\widehat{m}_n^{(2)}\hat{\mu}_n^2-3\hat{\mu}_n^4}
                {\left(\widehat{m}_n^{(2)} - \hat{\mu}_n^{2}\right)^2} - 3,
        \f]

        where \f$ \widehat{m}_n^{(i)} \f$ are the \f$ i \f$-th moment and \f$ \hat{\mu}_n \f$ the mean (first moment) of the
        \f$ n \f$ samples.

        The kurtosis estimator for weighted samples is formally identical to the estimator for unweighted samples, except that
        the weighted counterparts of all measures it depends on are to be taken.
    */
    template<typename Sample, typename Weight>
    struct weighted_kurtosis_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, weighted_sample>::result_type result_type;

        weighted_kurtosis_impl(dont_care)
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::weighted_moment<4>(args)
                        - 4. * accumulators::weighted_moment<3>(args) * weighted_mean(args)
                        + 6. * accumulators::weighted_moment<2>(args) * weighted_mean(args) * weighted_mean(args)
                        - 3. * weighted_mean(args) * weighted_mean(args) * weighted_mean(args) * weighted_mean(args)
                      , ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                        * ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                   ) - 3.;
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_kurtosis
//
namespace tag
{
    struct weighted_kurtosis
      : depends_on<weighted_mean, weighted_moment<2>, weighted_moment<3>, weighted_moment<4> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_kurtosis_impl<mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_kurtosis
//
namespace extract
{
    extractor<tag::weighted_kurtosis> const weighted_kurtosis = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_kurtosis)
}

using extract::weighted_kurtosis;

}} // namespace boost::accumulators

#endif

/* weighted_kurtosis.hpp
Z/06iJS83h+K9To8GxDMruFXPJC0JF+P/iE2Hv1PX0Nmi3kY+7XUQ5fT2CcHs7+tcrxK0bV6R0ZcZM1KHPRiaplB9j5QJ4qy5lp2wqZ2ucMWOLn1eHyLhnANz3E8ZN8PPYIUolctvUMtlAQksqobkERblPjYWIeTIkk4tbI6gewWqtFpI3aGgMvSIePsNxIRTec5eofV4ztcUbvAnRpdRge9NlHq6xQRLVyH7v+dj018cUWA8aPPeSzjyGcZwfMvBWcj20ixOrP+IyNowy7C2hHf+CJmrtwi04GM/mfc8ZA/2jWF/yMTXOIsDz/arDx8eQX444rvkwD/TP4vX14h/VXl4fsqxH+gVXk4cGWF91eUh2smVXjvrJB/8/Lw0aQK9av4vvnP59/u8gr5X1XhfVKF9BXa06hCe0qaV3hfof4ZLSrg77IK+Kn4vsXP5/9xywr1q1D/RpdVwE+F+ixuVaF+gg+z/otZRx/2/5sS1n4tmWbWfh1l87QDdGXOtmuEkwRfSiTBy3XEkT+HFUQTWP/iX2H3usocE/0W9swvPMbfUTYqEaCG8ZarPSPAkMXBjDyDzOfdNoQYrMahXOZ6nWWi3Y5ooLbVEQ0U34tDDHzqdTIZ1+YITyVIoSq+h8STSK+AGSM0w19sz/CvtatDHSgRMokoqNbKUjznXpOq6cemrGpq4pUSXkVFtI6pc/D86yjfxkAWW3TMwDuutzTfWsysMqIqSk1nVVEfYmWiKDIVUy30I4rhA+dkOy7arGvN2iwqagHaSYkujlbhelZjqY0nfmSf53BTHfAyt1brax0MkbAxIhTi/+Gh/xihQ6aq8ldL9742vFOWGT5Rp4ZiMnD7N/EWpeuQI/9Oxm0o0TGxt0Wc9bTmbfF0OMeuuSSRLk6qhx9H+gewGaXXNWuIl6GTCCUaHIBAEAjt7nt5iRB8g60YvsoyU0p8F+nsZeIRKCPYlynG69+bqJa3j1INbd/z3v02oprWpu58+jh3Z+aFLEk+gPmhE6LAMj9BTcOK3hO8N7E02xQ/vjpT2Q1XcvwMqno3qZKWIulCGCTk24I/V8niYSH8DneZHqPuz6mtu/59Em2scLoadWUf1WTCjWjx5LDFoNilywSrry0BrVQK/fWm3jP6+HBwIui2ZxzZOZDv75uQSvZsqbBnywjG0w5R7p5V5e9DX7Xpl8CV7AU2JDMxyslE1a9l2Hv8P1qHN8MgqhyC5vLc9u7N/tzGlL9EISs5KrWViUfmjH9ydyXwTZVJPGlaWkpLgtwKWKUgWMRqFy0WtJFWEkm1eIG7rqJdFbyokGLZ5U6LDY8AKiiu5+7K6npyiRWvlgoth4AgcqkgiL5aUbRKWxCz/5l5eXlJWiiI7JEf5b3veN833zXfzHwz801toAO8Mffw5QkgUBzl33ZzjFqFSLi1UqHvR2PeM51lGAByaUvdmuG8VKLlqlAJ7N+oEJbJiaa2mkG63VMrKdo59X1O9XxrLlgs5CmYx4t5LiGXlHtTsNwt5+vl4gYCY6FfXiSdMlyndjD/Jpy8qxRC73OTC4S6XMh99hY1AR3nylgb7Dvr5dtzyLbl74wBaFp7yQgjo2bMA9Q6Z19uEy7/LWF3kBcFGjs6TmvsAVXtqzUWSNgnGbnRWUGddzddYvVjrV+Zy8lU8rctCKgal+Wwy7IX9Tmsl39K3HcRLy7pHc0eJFO/CU2iEXNy70Yzug68LkDwfpmqE7zoLZF0Tj9UC9Z7RLQz48cx17GszJnyI5G7DlcK+qAOtC78rzE6WtYv4Mu2ClgLDLITm1GWspY46OxL0HmWn0EDX0o0MPAqStD5n1x9vWhaGceNX/T1Y+R3OqRG8DuBlTM=
*/