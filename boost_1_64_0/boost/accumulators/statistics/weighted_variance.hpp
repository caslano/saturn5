///////////////////////////////////////////////////////////////////////////////
// weighted_variance.hpp
//
//  Copyright 2005 Daniel Egloff, Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_VARIANCE_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_VARIANCE_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>
#include <boost/accumulators/statistics/weighted_moment.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    //! Lazy calculation of variance of weighted samples.
    /*!
        The default implementation of the variance of weighted samples is based on the second moment
        \f$\widehat{m}_n^{(2)}\f$ (weighted_moment<2>) and the mean\f$ \hat{\mu}_n\f$ (weighted_mean):
        \f[
            \hat{\sigma}_n^2 = \widehat{m}_n^{(2)}-\hat{\mu}_n^2,
        \f]
        where \f$n\f$ is the number of samples.
    */
    template<typename Sample, typename Weight, typename MeanFeature>
    struct lazy_weighted_variance_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        lazy_weighted_variance_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<MeanFeature> const some_mean = {};
            result_type tmp = some_mean(args);
            return accumulators::weighted_moment<2>(args) - tmp * tmp;
        }
    };

    //! Iterative calculation of variance of weighted samples.
    /*!
        Iterative calculation of variance of weighted samples:
        \f[
            \hat{\sigma}_n^2 =
                \frac{\bar{w}_n - w_n}{\bar{w}_n}\hat{\sigma}_{n - 1}^2
              + \frac{w_n}{\bar{w}_n - w_n}\left(X_n - \hat{\mu}_n\right)^2
            ,\quad n\ge2,\quad\hat{\sigma}_0^2 = 0.
        \f]
        where \f$\bar{w}_n\f$ is the sum of the \f$n\f$ weights \f$w_i\f$ and \f$\hat{\mu}_n\f$
        the estimate of the mean of the weighted samples. Note that the sample variance is not defined for
        \f$n <= 1\f$.
    */
    template<typename Sample, typename Weight, typename MeanFeature, typename Tag>
    struct weighted_variance_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        template<typename Args>
        weighted_variance_impl(Args const &args)
          : weighted_variance(numeric::fdiv(args[sample | Sample()], numeric::one<Weight>::value))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if(cnt > 1)
            {
                extractor<MeanFeature> const some_mean = {};

                result_type tmp = args[parameter::keyword<Tag>::get()] - some_mean(args);

                this->weighted_variance =
                    numeric::fdiv(this->weighted_variance * (sum_of_weights(args) - args[weight]), sum_of_weights(args))
                  + numeric::fdiv(tmp * tmp * args[weight], sum_of_weights(args) - args[weight] );
            }
        }

        result_type result(dont_care) const
        {
            return this->weighted_variance;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & weighted_variance;
        }

    private:
        result_type weighted_variance;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_variance
// tag::immediate_weighted_variance
//
namespace tag
{
    struct lazy_weighted_variance
      : depends_on<weighted_moment<2>, weighted_mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::lazy_weighted_variance_impl<mpl::_1, mpl::_2, weighted_mean> impl;
    };

    struct weighted_variance
      : depends_on<count, immediate_weighted_mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_variance_impl<mpl::_1, mpl::_2, immediate_weighted_mean, sample> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_variance
// extract::immediate_weighted_variance
//
namespace extract
{
    extractor<tag::lazy_weighted_variance> const lazy_weighted_variance = {};
    extractor<tag::weighted_variance> const weighted_variance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(lazy_weighted_variance)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_variance)
}

using extract::lazy_weighted_variance;
using extract::weighted_variance;

// weighted_variance(lazy) -> lazy_weighted_variance
template<>
struct as_feature<tag::weighted_variance(lazy)>
{
    typedef tag::lazy_weighted_variance type;
};

// weighted_variance(immediate) -> weighted_variance
template<>
struct as_feature<tag::weighted_variance(immediate)>
{
    typedef tag::weighted_variance type;
};

////////////////////////////////////////////////////////////////////////////
//// droppable_accumulator<weighted_variance_impl>
////  need to specialize droppable lazy weighted_variance to cache the result at the
////  point the accumulator is dropped.
///// INTERNAL ONLY
/////
//template<typename Sample, typename Weight, typename MeanFeature>
//struct droppable_accumulator<impl::weighted_variance_impl<Sample, Weight, MeanFeature> >
//  : droppable_accumulator_base<
//        with_cached_result<impl::weighted_variance_impl<Sample, Weight, MeanFeature> >
//    >
//{
//    template<typename Args>
//    droppable_accumulator(Args const &args)
//      : droppable_accumulator::base(args)
//    {
//    }
//};

}} // namespace boost::accumulators

#endif

/* weighted_variance.hpp
sm7NxjLdc59dBlZQ3WVxlSlPevR60WjsznrEevJkMdc6gjWAMRw3TqBTQpEtcRy8pi+zxXVy/i3YqQ5Hs7o7UHvh25dONE275/dEFFRzgPPf66SMiSLxHOIob3UHi4Gazxpo+LJhvBwc9DYUjfMprofI+OMpYThP6hKHIOUzzr/NkqFMbsPM2ipND3tp6IuRW5eMse3y3ti1kotDPJqDGwe0H5gkMaOb7JZ0QKKunLOiaotMM4NBqHBsPeltLb3KIPbzeWm3rJGYdFFi+UqKG8Xqv+QvkU9gTIXjYTZM/bHcZky5Zj4zUUOCLhNljw0AiAuZUVvNOSSloq+Jq7etPY4WaPQR3aKR3ko3+WIuzAP4izLzwHz7QdO3seMCGpQHJcs+lJ9KUr17kKExTm69xpS7yklkKOoOrQJHGFmoZ88AN5mNA9LbfsgNI9Vb9LjRbJncAWptCfDwqjFLnz8OyJAUkVkUqaf7OSIfK44MLDD0QZPJlfg9Ymfy7q/EVGcPhKEH6bW6Hf2Hq6UeoFFmLtDcs5U1rVVBG8YCmgrZqcNssjdtq6/tl9w0R6i5V3nfYYshG8WkMdM0ZxOPXQ7UD/w2NXLuXfrJ4y3P1YSRXw50/j1V5M1DystpgfL8L2WBcjLbWxZjbRKAzaW+5vzOkRr+LwXf/CGLgYFRXm6gHM4oRwLlBEJ5axdQtnf+a5Y3mZGnGMjdjFwB8lJCfnwXkBv1v8oo7wVOo7zPPGCt9IDyNrLNIJSrx7VEOQVzZRqtwA6s777wqi70n/JAvP+m2PIJs77whdlk/uRmK5KbLEOEfALp3P4o6aoW/fvm4nb795OxB8i035QuZWr0/5Vt+n9x+/1/oCxfLelSlu3k3/PKFvTx0f3t0sf+MQfIvKmwS5kb5z9XcH7mjIUN46KniEODFWTxHRKr4E4kTSGuPzdFXWzcbN+V+cuY/1viP86Gv7uF3ylz43sdzo0d+1PZfnkL/D2M2arT1QXzw3xe/wgGNO0k8hPwC9obevXt/Sy5wim0j/+F9MNdCWLHbRyI3DTa6If8i9EqtSVuUedw1pawYof+xnmseVFIaIqAJstAs7glmn5AI7MdSvDFfcLsU2+J40Z30ssh8f321lNPTjFabYTXr9XLosKYteZR2eg9M74kItc0rFqvaOv1M1FYHLU+e4NcKBpJehEFpvNmemA9HDvbODM9mMs0W69/OyjfkWBYow9UuAdGceGyrMJ1k8KtvVcK96NDLFxr/d8fdVy+wgOV76vzuHyzfmyW79J7uXz9jPItG3bI5SMWXV6RDq8QC9fPyiTnGsOYh30Ce9ADjP8fWv4KUoyBYl+mT40PJPvw7Kx9Rv3Q0k+Q/UshLVYjo7+l9WqNU7brtIEp2MJbmBrTof1p02hjYd/QwG9j19bmLfRfJref//mUf8kB8ndecljyH9U6/6HGYn0pdYkeTey4BHcPO8QStKj/Ze3X/0Ou/wFyf3LAIeZunf9LzoH5zXz5WV+TmHrbGP/R4PpLUxGQaSWNab3TmcWwf7uU8RvNKSZ0SN4h/HKB92OwkStATjCidQK7/dul7e9XJ3Y6o1j2X4JBW0f76UL9udG2/XQh9tM/KW25ny7Efnp6aVf3019eYvgPCxRa25DI6E36Q2wnRFfjGQ1J+xGH5xEOHmj8X9J6/pxH3WT3ShYf9p3qI14g2CCRVcg5KUQhcqogRHhOcMiN2bR3lLx+YNt2JMcgqJuRzVuOK3DYhUAWrsGrSA4OmeGtuI3jy4x4kQtC2zPTxzp7+mMjWbdzo37uKDldhEVXmspajEefI7rDOUsfNpasr8p28s47MxP4dGDEfv0plaU8xyMddRMOrzA=
*/