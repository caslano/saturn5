///////////////////////////////////////////////////////////////////////////////
// weighted_covariance.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <complex>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/covariance.hpp> // for numeric::outer_product() and type traits
#include <boost/accumulators/statistics/weighted_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_covariance_impl
    //
    /**
        @brief Weighted Covariance Estimator

        An iterative Monte Carlo estimator for the weighted covariance \f$\mathrm{Cov}(X,X')\f$, where \f$X\f$ is a sample
        and \f$X'\f$ a variate, is given by:

        \f[
            \hat{c}_n = \frac{\bar{w}_n-w_n}{\bar{w}_n} \hat{c}_{n-1} + \frac{w_n}{\bar{w}_n-w_n}(X_n - \hat{\mu}_n)(X_n' - \hat{\mu}_n'),
            \quad n\ge2,\quad\hat{c}_1 = 0,
        \f]

        \f$\hat{\mu}_n\f$ and \f$\hat{\mu}_n'\f$ being the weighted means of the samples and variates and
        \f$\bar{w}_n\f$ the sum of the \f$n\f$ first weights \f$w_i\f$.
    */
    template<typename Sample, typename Weight, typename VariateType, typename VariateTag>
    struct weighted_covariance_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Weight, typename numeric::functional::fdiv<Sample, std::size_t>::result_type>::result_type weighted_sample_type;
        typedef typename numeric::functional::multiplies<Weight, typename numeric::functional::fdiv<VariateType, std::size_t>::result_type>::result_type weighted_variate_type;
        // for boost::result_of
        typedef typename numeric::functional::outer_product<weighted_sample_type, weighted_variate_type>::result_type result_type;

        template<typename Args>
        weighted_covariance_impl(Args const &args)
          : cov_(
                numeric::outer_product(
                    numeric::fdiv(args[sample | Sample()], (std::size_t)1)
                      * numeric::one<Weight>::value
                  , numeric::fdiv(args[parameter::keyword<VariateTag>::get() | VariateType()], (std::size_t)1)
                      * numeric::one<Weight>::value
                )
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if (cnt > 1)
            {
                extractor<tag::weighted_mean_of_variates<VariateType, VariateTag> > const some_weighted_mean_of_variates = {};

                this->cov_ = this->cov_ * (sum_of_weights(args) - args[weight]) / sum_of_weights(args)
                           + numeric::outer_product(
                                 some_weighted_mean_of_variates(args) - args[parameter::keyword<VariateTag>::get()]
                               , weighted_mean(args) - args[sample]
                             ) * args[weight] / (sum_of_weights(args) - args[weight]);
            }
        }

        result_type result(dont_care) const
        {
            return this->cov_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & cov_;
        }

    private:
        result_type cov_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_covariance
//
namespace tag
{
    template<typename VariateType, typename VariateTag>
    struct weighted_covariance
      : depends_on<count, sum_of_weights, weighted_mean, weighted_mean_of_variates<VariateType, VariateTag> >
    {
        typedef accumulators::impl::weighted_covariance_impl<mpl::_1, mpl::_2, VariateType, VariateTag> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_covariance
//
namespace extract
{
    extractor<tag::abstract_covariance> const weighted_covariance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_covariance)
}

using extract::weighted_covariance;

}} // namespace boost::accumulators

#endif

/* weighted_covariance.hpp
SyAqR/MYx4nGyAh9wWRbIXjVkqGa7N+V0bPch9HTeS5Gj0VloCiOmrzi1/NCfO4f7f/vnvAkRizrAp+RlZqJOaiuO/QhOwCdB2+sZ+Y2LuL/NJzjx+qDVqbZ/Z0udWIibsFaYZlb9f2Pkhp9U538/XQhBmxnmbFHaySporyv7zbZM4qrPd2aO73+UTBzachTqfqwLY+EmsJZQlmt9fTj8o/qEJNzjRcH/WGdF6H15yT6xYgF5n2kc5h5N8F7noe/v/2gHJx/ZLTMaeo1LDWWtNbpHSmnN5k8/fxc+b7BLB7/2WFbJEhu4ALkdL/6nRGLxpQB/Ihd1FQ1pD3JaLPKqCbsZY6vokM/0M1zLJZtZhd2IHN1LdnG4xY7pFU/pgi1DtB0/ns5NTuMxLJRdNzvbH3nV7VfJ61pEm5NSSamZ5ZDpQlysmxwf37k1lQbFD6CNasd1W9OpF3kfijFh2h3UPPWcPPE4pmbp44MCrdti2qo2zYs0rZRYWcm1LJz2yM7dfvcd1VuX5/+kfZN7RdtX/N7w+2bn3J27buqV7R91133G7WvkmmcNHDAnVGvtGWwwKVJbSRatSQGI1Rb29cWE5HLAKq5fRFftzh5YFj+LkKtQZAlG6iahTHySfC69jkmTpPDyqC+xTocePzBW7SngxeocLxZ5LXuo4yvN2X8yT3hjAddR0idTqjMJHThsuuMcP4TGLmEVMYoDGSBQMHojI6CUcr4W0hbfA/io3JgEhNYfwp//45ogfdFCjxyLekcbIeogAoFo4CKJeriGpuKG3GNbLpncQfKzvtw7LyPpp33X+Mwzzl8wvR9KiK4vb+cnDITwZu3R9EzUFDlpSHwEkl+qs2fJQQYW3MNWxnysvEjOvzSTByeC+XjjCbQxOIl44q3FkpbegW1eH/qmA9fEcVq47YVsNoY9gy/GWbN8t71/SLrzf63V2nf7w0WEE6WFBBitrWhOI8XxIqRz0ttAbp25tTHFcQ2nktjeslK+dvhepI5M5e/p+/PXtr+rW+4LzOyYRTxCdmSvXgbL5T8xxIdU5pzNardl0CmTrPnfvRjHO4X3eoOfZX8Kc8n86hfVAgsDGBgysxYQF8lAwpMoUYF0yzFU2bHyiUkgXlz8VQ85QkNl2y00nn18XQ+egUe/ScTxt3sWkR5jOvsNeYJVjarh5IjWGlWjbGy+xbBypb7eamGkJ0IcRcm4bWyNNXFy+Ls2QDnyMgruRXFsNGuY+RUynrenXLm5c/aYrVAdk3AnMi2w/puLUkXWERtKLkwktoxxatT9JUcJqUA9i+naDGOaU79sh1nt1V8l6l3lujsSj6MpdaGcq/wZTPK+ATODNQYHYJIxVMIUYipoz/H0W2OadvIlxincK71l9kd01YiQKfUde6G9FT0mgHMhd8x5lB0HccJG5X31bB0XqA9CrRnUM7LqbQYPpyMJqBDCRgEQGoHhPN9ipijuIb1oUeBl4FaUhHXvnF2eYL1fDa1E17CM5xbvVaJvXwx6pM9QyrBQV5/UZnXCi/BWLkc+QRnnye4Q+TILQSJLWirReNlT/GU4zFmDDxjMdVz8wlTPVecEFRv7y89+RZgXR7JPM73CbdWwW0y6lJ1m9wd9fCKFlxypYWwXtuR31cXMQQqjQNuR0J1aEvhXa+rPeC1w0asa3yBN56ofxERtkpHLECOhX3iir62q2sBOhaOio875g/ZHRPrSl7+4jLVjGucG+8PJTgmHj2ONhXvMz7Hy6JSuwrlcC4FfeLUQTymFoyKL0ygWs3R5yksvbW905QJmtAToJNA+8kAKfA4B6LOvVojWjseDLkNKF06BQT8CNCmRBmMLR5Ws7rTIJpGg2jpJRI=
*/