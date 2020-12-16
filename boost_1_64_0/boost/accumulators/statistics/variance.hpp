///////////////////////////////////////////////////////////////////////////////
// variance.hpp
//
//  Copyright 2005 Daniel Egloff, Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_VARIANCE_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_VARIANCE_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    //! Lazy calculation of variance.
    /*!
        Default sample variance implementation based on the second moment \f$ M_n^{(2)} \f$ moment<2>, mean and count.
        \f[
            \sigma_n^2 = M_n^{(2)} - \mu_n^2.
        \f]
        where
        \f[
            \mu_n = \frac{1}{n} \sum_{i = 1}^n x_i.
        \f]
        is the estimate of the sample mean and \f$n\f$ is the number of samples.
    */
    template<typename Sample, typename MeanFeature>
    struct lazy_variance_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        lazy_variance_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<MeanFeature> mean;
            result_type tmp = mean(args);
            return accumulators::moment<2>(args) - tmp * tmp;
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

    //! Iterative calculation of variance.
    /*!
        Iterative calculation of sample variance \f$\sigma_n^2\f$ according to the formula
        \f[
            \sigma_n^2 = \frac{1}{n} \sum_{i = 1}^n (x_i - \mu_n)^2 = \frac{n-1}{n} \sigma_{n-1}^2 + \frac{1}{n-1}(x_n - \mu_n)^2.
        \f]
        where
        \f[
            \mu_n = \frac{1}{n} \sum_{i = 1}^n x_i.
        \f]
        is the estimate of the sample mean and \f$n\f$ is the number of samples.

        Note that the sample variance is not defined for \f$n <= 1\f$.

        A simplification can be obtained by the approximate recursion
        \f[
            \sigma_n^2 \approx \frac{n-1}{n} \sigma_{n-1}^2 + \frac{1}{n}(x_n - \mu_n)^2.
        \f]
        because the difference
        \f[
            \left(\frac{1}{n-1} - \frac{1}{n}\right)(x_n - \mu_n)^2 = \frac{1}{n(n-1)}(x_n - \mu_n)^2.
        \f]
        converges to zero as \f$n \rightarrow \infty\f$. However, for small \f$ n \f$ the difference
        can be non-negligible.
    */
    template<typename Sample, typename MeanFeature, typename Tag>
    struct variance_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        template<typename Args>
        variance_impl(Args const &args)
          : variance(numeric::fdiv(args[sample | Sample()], numeric::one<std::size_t>::value))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if(cnt > 1)
            {
                extractor<MeanFeature> mean;
                result_type tmp = args[parameter::keyword<Tag>::get()] - mean(args);
                this->variance =
                    numeric::fdiv(this->variance * (cnt - 1), cnt)
                  + numeric::fdiv(tmp * tmp, cnt - 1);
            }
        }

        result_type result(dont_care) const
        {
            return this->variance;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & variance;
        }

    private:
        result_type variance;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::variance
// tag::immediate_variance
//
namespace tag
{
    struct lazy_variance
      : depends_on<moment<2>, mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::lazy_variance_impl<mpl::_1, mean> impl;
    };

    struct variance
      : depends_on<count, immediate_mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::variance_impl<mpl::_1, mean, sample> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::lazy_variance
// extract::variance
//
namespace extract
{
    extractor<tag::lazy_variance> const lazy_variance = {};
    extractor<tag::variance> const variance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(lazy_variance)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(variance)
}

using extract::lazy_variance;
using extract::variance;

// variance(lazy) -> lazy_variance
template<>
struct as_feature<tag::variance(lazy)>
{
    typedef tag::lazy_variance type;
};

// variance(immediate) -> variance
template<>
struct as_feature<tag::variance(immediate)>
{
    typedef tag::variance type;
};

// for the purposes of feature-based dependency resolution,
// immediate_variance provides the same feature as variance
template<>
struct feature_of<tag::lazy_variance>
  : feature_of<tag::variance>
{
};

// So that variance can be automatically substituted with
// weighted_variance when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::variance>
{
    typedef tag::weighted_variance type;
};

// for the purposes of feature-based dependency resolution,
// weighted_variance provides the same feature as variance
template<>
struct feature_of<tag::weighted_variance>
  : feature_of<tag::variance>
{
};

// So that immediate_variance can be automatically substituted with
// immediate_weighted_variance when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::lazy_variance>
{
    typedef tag::lazy_weighted_variance type;
};

// for the purposes of feature-based dependency resolution,
// immediate_weighted_variance provides the same feature as immediate_variance
template<>
struct feature_of<tag::lazy_weighted_variance>
  : feature_of<tag::lazy_variance>
{
};

////////////////////////////////////////////////////////////////////////////
//// droppable_accumulator<variance_impl>
////  need to specialize droppable lazy variance to cache the result at the
////  point the accumulator is dropped.
///// INTERNAL ONLY
/////
//template<typename Sample, typename MeanFeature>
//struct droppable_accumulator<impl::variance_impl<Sample, MeanFeature> >
//  : droppable_accumulator_base<
//        with_cached_result<impl::variance_impl<Sample, MeanFeature> >
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

/* variance.hpp
6nwr3qusmzT/k0g1TJHiKFLbmzl8723R8GN4VhdR4tma7rKpuOU+zf8IuG2k5n8EJI3S/I+AorECXE1A79ECNCVgmZ7O6hNQcrsAdgJCGjg2iVjJOM3/AaBmuaaa5VHNJnbn8L6m8AcofDDCVSdd+l8pp4/+LMDzBOR2FmAOAQN1gVMJGKOBsQRcoEsfJqVfbSrFRaXYpPSGpvBkCv8+C4nnaoJOppy669IvI6CmHo2NCFijmWU8ASc1EEIMNUdX/4CfSym51cSL8KwmZ3H4B6bwPRQ+lEpvrJG9gHKqo4GXCDiuq/I4Ae93EWA6ATdhmgsffR7rP1vXJf///P9z1h/t//JPIt9/kSHU2CyPRD8NNMhjMm/aG2RuETK/BM9qSiYipetI+yfQdDBMi8gThAeaUtCz6pnJ4XZTeDyFd6ScLtWJ/0I59Zyop0jJ6XCvaAp6VnGS02em8O8o/EcfcQ09v/alnC7TQBYBDg2kEfCN5qfXEtBfl345AbF67r+IgKF/jA7KuAm/9qCsWh/17R/Fc9IDdmh+Dxh/stG5fbTPuBwbvEFvirrIJdespARaBobZAqPsjgSro26MI6FLgqOuN8GRkNbYUTe1MeDWgFsDTgWcegABWQcQknWuyiXt/0PqJ2vbB3rWEf8fVwK7p7mPUe63O/V9xXL/66nv+5T7r6v0X6pR98rQsNEKfEjuJ/Shin+7pU4Moe3bdoI2e6B1YJQt0MfOaDibuw3M9yNWvv+t8v3BkeuaTnFfauS6r6rv58T7eAEr3Wdd2R9GRFXy4h9E0c02XD7ePqgDLNiBBdro8iaov6dE9g/uZ/N/qMzkSNsO9RIECPaoxJZLcKyiikVv1RSqNRjIIzjUoyWpKkgzYmwHrIo78U5wbHKIoDfb0pmetrLz8FAP2Xlw+MlUiY3MxWcjiC+ivDhnj61m/f6bv49oca/rFLaVaYa6VHaedGr6GRzOxJIRNvHyj7KnkjuDF6RBRTfz8b4D+FNrWLlhhUKIsJLVmOwJQzkgqzijuz3QEP9eo3trUsKeRxE+XBIbNhIcqRN2SfRmZ3VQC6/XGxvG2rMhx5/DB9YzZv/DFyQfJHsh2eUx7XDsht7ptPwpJ+JEtHM4058yjH3BrA+BHzYsQkvs5MHqQmoVOSny0gGiheT6I6ZdDTmSzkH34EH1xuqFLPk6kUJ8/ANMPB2WTNBXbfaQq8r6dKdRWx23bVZXX/Uyqb5ywh4/DYcamMV2h8hMvEAZDSnLmTkRC9j2kWz7S7YWU7YGsqX4xT2qyt4L/x/UHFexY9L34psYXl+zvR3QziZwU4MZ6J2sOnzgxL14BGHndSwJoL1LjMHnSFqCXIPkcuTTaQ//+A4x2tTUuCkRhDQKaWmnzl04hm09unVQnmuipsdjUdeeiEJVH4cI1A6peKpbfdizygprA5KSG3lX1kUIz2+P5wgOhgoOTnQDDroRDuLUlCqz4sOiaOdVRAEt3YtrsLOlMp0N/sjBgHp2Alsn1vSXnXTk3wHzdt3onPrMpCpnagXxVwj1hgYkbPpP/Wj956CIPzNv6M6Wp/J/Osg83l65GlDFwdYP3OiU/nn33hseWmG7Wz/Rj789yOYB3uTozEOsrcocwSPGSfdfdhUKKSLiyBoq9HGZejtC0BHU12DDXbIngb55eOISm2ZFhTCaggXpYXo+dBX2EBNqOOpaHQndIEpAnEi4CaJEWuMwVeMfjaVqjU+Eb0b0qB4QF9N47o4hk8i93DuRD0Blp3ZQL62pRSRPp6QQvxuT1XC14o7oudV7qOwHUDYLI+Xq7S78WNhu50zw27qtouNjLlp/Taa0/lNz693qnZurygr18hmpLck=
*/