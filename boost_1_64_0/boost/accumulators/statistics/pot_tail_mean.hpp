///////////////////////////////////////////////////////////////////////////////
// pot_tail_mean.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_POT_TAIL_MEAN_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_POT_TAIL_MEAN_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/peaks_over_threshold.hpp>
#include <boost/accumulators/statistics/weighted_peaks_over_threshold.hpp>
#include <boost/accumulators/statistics/pot_quantile.hpp>
#include <boost/accumulators/statistics/tail_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // pot_tail_mean_impl
    //
    /**
        @brief Estimation of the (coherent) tail mean based on the peaks over threshold method (for both left and right tails)

        Computes an estimate for the (coherent) tail mean
        \f[
            \widehat{CTM}_{\alpha} = \hat{q}_{\alpha} - \frac{\bar{\beta}}{\xi-1}(1-\alpha)^{-\xi},
        \f]
        where \f$\bar[u]\f$, \f$\bar{\beta}\f$ and \f$\xi\f$ are the parameters of the
        generalized Pareto distribution that approximates the right tail of the distribution (or the
        mirrored left tail, in case the left tail is used). In the latter case, the result is mirrored
        back, yielding the correct result.
    */
    template<typename Sample, typename Impl, typename LeftRight>
    struct pot_tail_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef float_type result_type;

        pot_tail_mean_impl(dont_care)
          : sign_((is_same<LeftRight, left>::value) ? -1 : 1)
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Impl, weighted>
                  , tag::weighted_peaks_over_threshold<LeftRight>
                  , tag::peaks_over_threshold<LeftRight>
                >::type
            peaks_over_threshold_tag;

            typedef
                typename mpl::if_<
                    is_same<Impl, weighted>
                  , tag::weighted_pot_quantile<LeftRight>
                  , tag::pot_quantile<LeftRight>
                >::type
            pot_quantile_tag;

            extractor<peaks_over_threshold_tag> const some_peaks_over_threshold = {};
            extractor<pot_quantile_tag> const some_pot_quantile = {};

            float_type beta_bar = some_peaks_over_threshold(args).template get<1>();
            float_type xi_hat   = some_peaks_over_threshold(args).template get<2>();

            return some_pot_quantile(args) - this->sign_ * beta_bar/( xi_hat - 1. ) * std::pow(
                is_same<LeftRight, left>::value ? args[quantile_probability] : 1. - args[quantile_probability]
              , -xi_hat);
        }
    
        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sign_;
        }

    private:
        short sign_; // if the fit parameters from the mirrored left tail extreme values are used, mirror back the result
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::pot_tail_mean
// tag::pot_tail_mean_prob
//
namespace tag
{
    template<typename LeftRight>
    struct pot_tail_mean
      : depends_on<peaks_over_threshold<LeftRight>, pot_quantile<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_tail_mean_impl<mpl::_1, unweighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct pot_tail_mean_prob
      : depends_on<peaks_over_threshold_prob<LeftRight>, pot_quantile_prob<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_tail_mean_impl<mpl::_1, unweighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct weighted_pot_tail_mean
      : depends_on<weighted_peaks_over_threshold<LeftRight>, weighted_pot_quantile<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_tail_mean_impl<mpl::_1, weighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct weighted_pot_tail_mean_prob
      : depends_on<weighted_peaks_over_threshold_prob<LeftRight>, weighted_pot_quantile_prob<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_tail_mean_impl<mpl::_1, weighted, LeftRight> impl;
    };
}

// pot_tail_mean<LeftRight>(with_threshold_value) -> pot_tail_mean<LeftRight>
template<typename LeftRight>
struct as_feature<tag::pot_tail_mean<LeftRight>(with_threshold_value)>
{
    typedef tag::pot_tail_mean<LeftRight> type;
};

// pot_tail_mean<LeftRight>(with_threshold_probability) -> pot_tail_mean_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::pot_tail_mean<LeftRight>(with_threshold_probability)>
{
    typedef tag::pot_tail_mean_prob<LeftRight> type;
};

// weighted_pot_tail_mean<LeftRight>(with_threshold_value) -> weighted_pot_tail_mean<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_pot_tail_mean<LeftRight>(with_threshold_value)>
{
    typedef tag::weighted_pot_tail_mean<LeftRight> type;
};

// weighted_pot_tail_mean<LeftRight>(with_threshold_probability) -> weighted_pot_tail_mean_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_pot_tail_mean<LeftRight>(with_threshold_probability)>
{
    typedef tag::weighted_pot_tail_mean_prob<LeftRight> type;
};

// for the purposes of feature-based dependency resolution,
// pot_tail_mean<LeftRight> and pot_tail_mean_prob<LeftRight> provide
// the same feature as tail_mean
template<typename LeftRight>
struct feature_of<tag::pot_tail_mean<LeftRight> >
  : feature_of<tag::tail_mean>
{
};

template<typename LeftRight>
struct feature_of<tag::pot_tail_mean_prob<LeftRight> >
  : feature_of<tag::tail_mean>
{
};

// So that pot_tail_mean can be automatically substituted
// with weighted_pot_tail_mean when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::pot_tail_mean<LeftRight> >
{
    typedef tag::weighted_pot_tail_mean<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_pot_tail_mean<LeftRight> >
  : feature_of<tag::pot_tail_mean<LeftRight> >
{
};

// So that pot_tail_mean_prob can be automatically substituted
// with weighted_pot_tail_mean_prob when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::pot_tail_mean_prob<LeftRight> >
{
    typedef tag::weighted_pot_tail_mean_prob<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_pot_tail_mean_prob<LeftRight> >
  : feature_of<tag::pot_tail_mean_prob<LeftRight> >
{
};

}} // namespace boost::accumulators

#endif

/* pot_tail_mean.hpp
1CZV1VWaRYtkn53L2mhW4gqIu/DsdTLd/vw8fa8qbW8O4humR/uIK/UqpD6eKblnIzckYvnXkuLfCFi5n4TvbPgp2PfPOs/+oz/WVyUyHZc+qKfjQRc9gpxMmozHSa7yKKjAyvibqxEj9V2WFjHWZatNWlXbBdaK0lPnHiMrv7OF7UFAJ5bTH1+uX3Co51+WBWLKtVqjVqkxxs9Davi15rKRiZ/GfDrIDip6YY+xAZdNtDo0xA6YUrbw3A5DQkbyKwmko5KIvZo8ZvMtcCCCci2WXNj/ypMy3vhyjgji87+jurWRVoVO8q0RNQmmIbXpMuvU1GsleQQxmORJUz29uazsDSf8XhJ76rL+F3Rzn5WUVjoFYAACqvBhtFc6AcAhJ6oaTXPfu4B6QvfWbdAx6DtQ0RKbtVJzvfl6BMpHZ3rXcox0iLVKbRVbsmkYnrFplPWaYGkpFi0J2nR7M7iCT6gOXcHyZ6SCUTZzNJCSTvtAVE0Ucat6aDLWt9UXk02qHvgXlnP5nD0+OxboE7fkdFBXoLOFr5qPCcQO8wCryajk6eA9vyBU8cHdNciGovqFW33Ktg0han3+ELQpLlmwRN9KUc347dJgJzl7gGSMKOaObDJ/9Qv6LxXWlgp1SzAwlNMAEHxsvH1Qb04DYqe5CqZoOOaxOWyKvAFyO2qk4/3MhgfT7wjAgMZbmb1bIK08n2m9+x9BxS9iHp9p3ad8puIftZotK+Hrt6sNrVr1JxEyiq8tXAUbEwzzjebg/59LVJTX7csz5cOrH2NRmFN9JD9Gq3fpB8gagQl03mkO41ejQzyxtBmsX9xragg+FnOXatKdnH+0ukF+TFBX30kLRRVsKhrwDDbhoV26amzU6NA1iqgwFKHg5RuULz/rUV0++1Fr+XEIVS5f3DDPvAojsxVXOrkq111aUbKCf/XB4EQDR6sLJdmzBzETEDNBOXTMBm+vqVwir+9UxlZVBIJsr3BIeYH75fOMvkHCgtXe5f0Bwnb2NHdSTYfIgeyaPThCPyBbNEiYUH++B+IzM9zO6TUqQb03VA4b2syg2zQzaJVKjyzi5x44XqqGz8py9PUQv3bIFjF2SCuCuhBDwpEf6sjEzep6lvlv8MsE7udn8uxoUTjrgnjNVRsSIjNk2dGctdROIwdWqz6ZJZgcTyNoVLhVJcuj+6zAmiZwTSuNmuAlNkwLm+zDuEwz4nkU/phvk1xQhUzLy54qd+3UzbwhctZ+gq8xgACyg7gN2iKFL2m+9ZDwrSP9/HxrhXoeMinGIojEgsd//VNf0JNVtCGE/u1c/4H+J7Zys5KIy/szdpVkvXyQk0SO7pl6ZJdqxzZOoqDafABYoAcyeQktjx6xKUrGMh1q6FWyLRFZyEw32cTjkVonq/c23lZQMbqGoXNLHzN5AkbdklzajkrXk7m2Qb3HStAYRBTiWGTHTlbH1tRXjojasVBfuwBmjIr/Qjb+PCQlwT8iT338XsP/qpOlqPtw7Nb8Sb+rkpl8s+TL8N7khK69MBqX93uSBl+mLhgsM1M/4QWNPeQWwQqpyxW+KDddvXGQcKnEqVjen+YZDp9OchwSd5HT1Q1/FGXdjlfyN+0aL5SfGfgZKz9ZaUnVMeKPK98gPdrtePdTy7LzgXGTvqO19MrcbYVJNkQjdUI6J5nj1go3KqNpcGrM0LWSkVFETmBD99N15Ed6cj50H5+rSB2eZBXqboQp8CQCxKCkcUz/VcQVbgSeDIvImVq5HOxD2y49xOzPc6OrIBTp2lDqvH4ceSXqEacGlLPFYI7sUdhUP8X1XckRHYxKaWcre95xWZxSn37vFZ2ymq5lorJDvjpJ+s3etcgWTAT7LwU=
*/