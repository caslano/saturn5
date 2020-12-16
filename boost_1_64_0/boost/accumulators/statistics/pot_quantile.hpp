///////////////////////////////////////////////////////////////////////////////
// pot_quantile.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_POT_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_POT_QUANTILE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <boost/parameter/keyword.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/peaks_over_threshold.hpp>
#include <boost/accumulators/statistics/weighted_peaks_over_threshold.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // pot_quantile_impl
    //
    /**
        @brief Quantile Estimation based on Peaks over Threshold Method (for both left and right tails)

        Computes an estimate
        \f[
            \hat{q}_{\alpha} = \bar{u} + \frac{\bar{\beta}}{\xi}\left[(1-\alpha)^{-\xi}-1\right]
        \f]
        for a right or left extreme quantile, \f$\bar[u]\f$, \f$\bar{\beta}\f$ and \f$\xi\f$ being the parameters of the
        generalized Pareto distribution that approximates the right tail of the distribution (or the mirrored left tail,
        in case the left tail is used). In the latter case, the result is mirrored back, yielding the correct result.
    */
    template<typename Sample, typename Impl, typename LeftRight>
    struct pot_quantile_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef float_type result_type;

        pot_quantile_impl(dont_care)
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

            extractor<peaks_over_threshold_tag> const some_peaks_over_threshold = {};

            float_type u_bar    = some_peaks_over_threshold(args).template get<0>();
            float_type beta_bar = some_peaks_over_threshold(args).template get<1>();
            float_type xi_hat   = some_peaks_over_threshold(args).template get<2>();

            return this->sign_ * (u_bar + beta_bar/xi_hat * ( std::pow(
                    is_same<LeftRight, left>::value ? args[quantile_probability] : 1. - args[quantile_probability]
                , -xi_hat
              ) - 1.));
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
// tag::pot_quantile<>
// tag::pot_quantile_prob<>
// tag::weighted_pot_quantile<>
// tag::weighted_pot_quantile_prob<>
//
namespace tag
{
    template<typename LeftRight>
    struct pot_quantile
      : depends_on<peaks_over_threshold<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_quantile_impl<mpl::_1, unweighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct pot_quantile_prob
      : depends_on<peaks_over_threshold_prob<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_quantile_impl<mpl::_1, unweighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct weighted_pot_quantile
      : depends_on<weighted_peaks_over_threshold<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_quantile_impl<mpl::_1, weighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct weighted_pot_quantile_prob
      : depends_on<weighted_peaks_over_threshold_prob<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_quantile_impl<mpl::_1, weighted, LeftRight> impl;
    };
}

// pot_quantile<LeftRight>(with_threshold_value) -> pot_quantile<LeftRight>
template<typename LeftRight>
struct as_feature<tag::pot_quantile<LeftRight>(with_threshold_value)>
{
    typedef tag::pot_quantile<LeftRight> type;
};

// pot_quantile<LeftRight>(with_threshold_probability) -> pot_quantile_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::pot_quantile<LeftRight>(with_threshold_probability)>
{
    typedef tag::pot_quantile_prob<LeftRight> type;
};

// weighted_pot_quantile<LeftRight>(with_threshold_value) -> weighted_pot_quantile<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_pot_quantile<LeftRight>(with_threshold_value)>
{
    typedef tag::weighted_pot_quantile<LeftRight> type;
};

// weighted_pot_quantile<LeftRight>(with_threshold_probability) -> weighted_pot_quantile_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_pot_quantile<LeftRight>(with_threshold_probability)>
{
    typedef tag::weighted_pot_quantile_prob<LeftRight> type;
};

// for the purposes of feature-based dependency resolution,
// pot_quantile<LeftRight> and pot_quantile_prob<LeftRight> provide
// the same feature as quantile
template<typename LeftRight>
struct feature_of<tag::pot_quantile<LeftRight> >
  : feature_of<tag::quantile>
{
};

template<typename LeftRight>
struct feature_of<tag::pot_quantile_prob<LeftRight> >
  : feature_of<tag::quantile>
{
};

// So that pot_quantile can be automatically substituted
// with weighted_pot_quantile when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::pot_quantile<LeftRight> >
{
    typedef tag::weighted_pot_quantile<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_pot_quantile<LeftRight> >
  : feature_of<tag::pot_quantile<LeftRight> >
{
};

// So that pot_quantile_prob can be automatically substituted
// with weighted_pot_quantile_prob when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::pot_quantile_prob<LeftRight> >
{
    typedef tag::weighted_pot_quantile_prob<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_pot_quantile_prob<LeftRight> >
  : feature_of<tag::pot_quantile_prob<LeftRight> >
{
};

}} // namespace boost::accumulators

#endif

/* pot_quantile.hpp
1yXXS1UbuCpvnnsXartcPTfDOrJ7jG0koIn3AOlTUA1Hnkreca3U5zGw2273Gi7UR7pj000HGSImSELl5N8hr+8D6pJQjVje2odbYNitpcHayFe+fqLa+qbp+vZJfat+Z9oPMdTq6dXVlzm/dvX5pD42ET6bJpK4ZP1A11ci9WVKfU/j3cYzamCoQmZcZjERB2F8FE5TaykcwQ/7YccsZ5iVOT+B+/+4bs+UmUyWJ9Mf9hbwAOQWJ+GvWNvUNTi0GTwpkIiujQJRxHsPcCbi8RF8g5spffoIoeqa0h/UxLIARFJNfp4ZM3LteN2jTOLrocnzxpDAWzV7zkq8MpQ4fTQSr1W/PGsltgklplHJFJUVKhkeSlxJieeoJ0Mlv5bnEh2ROB+JuIrASgcy6HjKGyAysW7GGL5lKWlbQDNftGhFj+d3IdHVu2r+VJED9fyT0P/MxfyQvvJrEXrab20CN9RuIH/l71Tj98lcvZmbI/c9VP2NQ0T5bqQnWlnk5nRQBoL9xRgB3jvFqtG3ygUeC2eyh5g3Ex/y3f4iprSuDKN3GhLkXt8VfIywiviOzBiWtK2soDv8OlwTrDM1nQblykbqhCCPsSdPIkaEkHiG8Ff5/BDCTOFjGjO4EiVlF7azJJjJJMz0I8z0FnzcdIsdH4PALmuLaDOeMJHRx46MuZWQUbBeI2OuIGNIln1W9Z4iyAh/2ULGGXt6hInfcgjoQ1V9fchUtYnDtx8VaSqh4li6dmmA0yJtCh3R2n1D9SmXXbq2yHOvwqbQVM2arClYJpSe5VngKDyPiSP2Kind+AEXio7cL09kt849Hp7dNPd4JP2vjtjzJvlPSXvE+Zy9ppVJXCeKawx8X+6GzfBsVj1Mosu/PwnSrhtKvmFeAsqCqgnXHViPZHUv1m7gPXnTn0bqJimq5+wqSuwemPighkTDgu1dvIenlmd3YNhU0VVyS1Y6JFTHq5O4jmFiCt40BIfZMHi4SOxEaPd3ml1uUANS9k1T7y8R0jDrJv6LC001lT+VWNq23sQIDQoWukCmzvm91sHczslD0kjo3JGPLDkXUPMybXgYaGtjA7QxQIwyuuY72033Kb20MuV9Io9cDyglI7lKMSgsVXoiNqvnbxR2aBjVSBPw7VlcI4/GDTQaD2LAABZJHZE3PfVwdkO2v4W0wF04ZnGFOEDbKxz6JC+JBsWibo+sLEuLvUkE5ueC2zIkSQtFgT2Sb6Uw/eHLV5lTv914zb/hZ9GbON5eeKWFzldprBn2F3O54Vh/Amd9l6Gwnb50DAh1ThscTlfx5dGw7YkvVeAXAkMmFS5x58o0dIxp58obOoKG4k02u/Ui6X8PJrNbfW5WR+/HnLgMhdNnXs3caiARAXC1aSrxocrrAjzS+5CrZkf2y4uExGSEg0/4q2k1dBNL3WOaF4zQi2SNUKyfebXx/bB12ksbxmvCPO29bRo2Bkmjv5P/wH9F8T0bAfpKMY+CMhnSWbzPUwpbstzkH/o9d//2vIwTRwuPA0G+JjSZnvwdR9fFmp5ZpyQibebFrH3FxjFV7zxbJ7FpaQs8iR94Uj8ce5Gp3IVO8WqKGPQP9q4ELspqizMgiiLMuCC4pFimuD0ttEDUZhB1UFDMXMpMyyVTM4shNa00sqSRsvXZq/ds331Z71VIVioZZu4+U9PKJesiWaZors37n3Pu980HMyhkb3/z+8HM3c8999xz7z333HPshEB0a5f6YJZAOxYAlnwv2zhPQzdsN4PPYUuYf43tyGtuEsjqZ40NE9UbmF+oPh1adTZ32A4Y8hdudpAY/x/ye59+9QyBfTWB/cb8s0DGM+soDdf1KMDus9z53ROl5bAvdMM=
*/