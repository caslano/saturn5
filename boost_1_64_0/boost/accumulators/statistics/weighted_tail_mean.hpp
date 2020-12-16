///////////////////////////////////////////////////////////////////////////////
// weighted_tail_mean.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_MEAN_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_MEAN_HPP_DE_01_01_2006

#include <numeric>
#include <vector>
#include <limits>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_mean.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{

    ///////////////////////////////////////////////////////////////////////////////
    // coherent_weighted_tail_mean_impl
    //
    // TODO

    ///////////////////////////////////////////////////////////////////////////////
    // non_coherent_weighted_tail_mean_impl
    //
    /**
        @brief Estimation of the (non-coherent) weighted tail mean based on order statistics (for both left and right tails)



        An estimation of the non-coherent, weighted tail mean \f$\widehat{NCTM}_{n,\alpha}(X)\f$ is given by the weighted mean
        of the

        \f[
            \lambda = \inf\left\{ l \left| \frac{1}{\bar{w}_n}\sum_{i=1}^{l} w_i \geq \alpha \right. \right\}
        \f]

        smallest samples (left tail) or the weighted mean of the

        \f[
            n + 1 - \rho = n + 1 - \sup\left\{ r \left| \frac{1}{\bar{w}_n}\sum_{i=r}^{n} w_i \geq (1 - \alpha) \right. \right\}
        \f]

        largest samples (right tail) above a quantile \f$\hat{q}_{\alpha}\f$ of level \f$\alpha\f$, \f$n\f$ being the total number of sample
        and \f$\bar{w}_n\f$ the sum of all \f$n\f$ weights:

        \f[
            \widehat{NCTM}_{n,\alpha}^{\mathrm{left}}(X) = \frac{\sum_{i=1}^{\lambda} w_i X_{i:n}}{\sum_{i=1}^{\lambda} w_i},
        \f]

        \f[
            \widehat{NCTM}_{n,\alpha}^{\mathrm{right}}(X) = \frac{\sum_{i=\rho}^n w_i X_{i:n}}{\sum_{i=\rho}^n w_i}.
        \f]

        @param quantile_probability
    */
    template<typename Sample, typename Weight, typename LeftRight>
    struct non_coherent_weighted_tail_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<Weight, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type result_type;

        non_coherent_weighted_tail_mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            float_type threshold = sum_of_weights(args)
                             * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] );

            std::size_t n = 0;
            Weight sum = Weight(0);

            while (sum < threshold)
            {
                if (n < static_cast<std::size_t>(tail_weights(args).size()))
                {
                    sum += *(tail_weights(args).begin() + n);
                    n++;
                }
                else
                {
                    if (std::numeric_limits<result_type>::has_quiet_NaN)
                    {
                        return std::numeric_limits<result_type>::quiet_NaN();
                    }
                    else
                    {
                        std::ostringstream msg;
                        msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                        boost::throw_exception(std::runtime_error(msg.str()));
                        return result_type(0);
                    }
                }
            }

            return numeric::fdiv(
                std::inner_product(
                    tail(args).begin()
                  , tail(args).begin() + n
                  , tail_weights(args).begin()
                  , weighted_sample(0)
                )
              , sum
            );
        }
    };

} // namespace impl


///////////////////////////////////////////////////////////////////////////////
// tag::non_coherent_weighted_tail_mean<>
//
namespace tag
{
    template<typename LeftRight>
    struct non_coherent_weighted_tail_mean
      : depends_on<sum_of_weights, tail_weights<LeftRight> >
    {
        typedef accumulators::impl::non_coherent_weighted_tail_mean_impl<mpl::_1, mpl::_2, LeftRight> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::non_coherent_weighted_tail_mean;
//
namespace extract
{
    extractor<tag::abstract_non_coherent_tail_mean> const non_coherent_weighted_tail_mean = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(non_coherent_weighted_tail_mean)
}

using extract::non_coherent_weighted_tail_mean;

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* weighted_tail_mean.hpp
rte4aUIAVxR0xwpvvVIIkzN5xxwt245dXVAMjYS3xIUGrYc5gWu8hizmYq/Ep5vfl0+TjZ+OU+/Cpy7yO8nkgGw5Nz0iW05mYMtR8K26FXi2ZqhDGWTTZFigPth7j92/MaDI3If18kjRg7xuV9T0YSqKI6ntyzXV9MHv00b4mLq/SOy8Vz4gqEoabZR+T/8nb+3Pmk7QHfdx/4z2CJfN18awQT3zj/o4pKAB0yukM+3cmfcHxqFrEbXDoJRPhiCEVG5AlzmoywZGdJmDe+dh6rJLHQr4mGGblDYOxRmn5jGJVBGm4+/Se7OmNYVzOTyOevd+6d3qFdS789TZHundxbNPoua/Nv8f0+Z/earqfDogFpkHlXJG8pH6748GVG9H0DeMiT6eZPyuKZwk37/eyPf24/i+oJHvtzXve+H/5HsMSyqv+bEFWPNG/BeW3vLh0PSf5oWm31UUmr4lLP2CsPTXw9IzXwxNnyfp6rzxvI9xnj8b8WLj/J98JRd3qDfKt+xXa2uQ4at+/sbIciLtAdoGINyh2rigjboVRQckGe31vWUR/qC3zBX4txQG4X/vvmPB/8xcI/yPFzYO/4ai5sB/7Vwd/tzCUPjpPM8If2+CP6L9WgvaFurywl/uBfINGkH4htwk5f11VCRATctDlj9ibORSYEppIVdyQP3ew5XYwgUcEKrfJBnDBbil2A+Pif+46sse0ftkAOrV7+NU73yEK20lRWv1DbuJLn00dHxsYe2xmRPij8X1xIcPB3bMsi9lx5SrGqtBZDvomvmu7vhS8Dv+arrBFLQZ75bT6F27B0l9dBwzlZ5fUq3FlyAhS/Mnt1ZdgA/JYDCZspdepP3YfxZl8sqhcZPextQZ2kHyF6gGfSrHtSMelsgNTHJfUa+547r6JvW6OyTldaRIz4DMVw+Ok9hnNJuWsiN+Ds82GUE9xLGTJjpKb9J+zQdz71Q+erYDmt36Ifh6iewTCuKi2zm2A2K/oNgRHPsExxZEQ6ms+3KbfjBd/yftvhhpSDWCGvmLntfojkLarz/GZqBd//Lrzy5Pxo/u0307At/cPkdW6+3uIL55a8ax8M35c4xLsbe7cXzT/fHm4Ju9s/W1tXtsKL4p+XMovhn/diP++ZsbxvePN9L+2Vr7xwbbnzTrmO2fHdL+sY23/8JZzWr/rGD7x4S2/5ZZoe3vHwn/AvlaXTAmCP+gPx0L/tGzjPCPGtM4/PNvaw783YPwJ4XBb0XHGO/vlBv6fvAF0Nvnn7c3+kIEejPgtpaM21YbOAGYsqjv3M/kJyO2NYItZAtQv75VLKGXmoyILbjUBWWsbQxlqK/yt+4JmsdKh3r9GI64m9DQj7fx+y1SFcVM5uyTcoKIqXnVDJZq2jOmQR584FAvRKSGaNoFMAuiZ4/QMQvarXsEnPxX5loLf3vFN43/mynzKzvfQE8B4ib5Xy1/e0P+ie5jzcddinE+bh/d+HycMb458/ERRZ+Pc0aHzsdDGv1lXP+Ktv45q8D70MSm29dPy9/PkH/e48dqn3+GsX0N9zXevsl/aU77lszQ27fwvtD2ffv3UHwxqjQx9L69sHB1WLj3mwgbv9fCWv2au945LLoLQBHT5TOdq5ebae9P0nzL0e3alx4cHB3tHkH3hbWGhIf0PocVsr1BnZ2NfxHjhox3LaKVbWy5rs6ZHNTYq+MiTcjAqvxiBFYoKkSfQjUWargfcZbJhXSP5zZx9SUadFoNlViECJncvUigBbqsBUpDtSgHctXbXT6ky+lBze9Z1HqNevlEsTXEYh0NnEDoZdb1vHZHUBntHUpOEtSiAiCZUVTNaVKQ8oGU9czvA/qMrttEI/Eq6NZdqWQ=
*/