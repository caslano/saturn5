///////////////////////////////////////////////////////////////////////////////
// weighted_tail_quantile.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_QUANTILE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_quantile.hpp>
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
    // weighted_tail_quantile_impl
    //  Tail quantile estimation based on order statistics of weighted samples
    /**
        @brief Tail quantile estimation based on order statistics of weighted samples (for both left and right tails)

        An estimator \f$\hat{q}\f$ of tail quantiles with level \f$\alpha\f$ based on order statistics
        \f$X_{1:n} \leq X_{2:n} \leq\dots\leq X_{n:n}\f$ of weighted samples are given by \f$X_{\lambda:n}\f$ (left tail)
        and \f$X_{\rho:n}\f$ (right tail), where

            \f[
                \lambda = \inf\left\{ l \left| \frac{1}{\bar{w}_n}\sum_{i=1}^{l} w_i \geq \alpha \right. \right\}
            \f]

        and

            \f[
                \rho = \sup\left\{ r \left| \frac{1}{\bar{w}_n}\sum_{i=r}^{n} w_i \geq (1 - \alpha) \right. \right\},
            \f]

        \f$n\f$ being the number of samples and \f$\bar{w}_n\f$ the sum of all weights.

        @param quantile_probability
    */
    template<typename Sample, typename Weight, typename LeftRight>
    struct weighted_tail_quantile_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Weight, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef Sample result_type;

        weighted_tail_quantile_impl(dont_care) {}

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
                        return Sample(0);
                    }
                }
            }

            // Note that the cached samples of the left are sorted in ascending order,
            // whereas the samples of the right tail are sorted in descending order
            return *(boost::begin(tail(args)) + n - 1);
        }
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_tail_quantile<>
//
namespace tag
{
    template<typename LeftRight>
    struct weighted_tail_quantile
      : depends_on<sum_of_weights, tail_weights<LeftRight> >
    {
        /// INTERNAL ONLY
        typedef accumulators::impl::weighted_tail_quantile_impl<mpl::_1, mpl::_2, LeftRight> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_tail_quantile
//
namespace extract
{
    extractor<tag::quantile> const weighted_tail_quantile = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_tail_quantile)
}

using extract::weighted_tail_quantile;

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* weighted_tail_quantile.hpp
aUpS4HA16wQRR7UZyVdR3E5cM9qhcf9TNO6/5FGmJqjrxfntHyqUVTVbCJgEtIYvvPBvrXnXobRUJxZQSYXLHPMhVMnRiCXOob58JyOuJ0Tg+ei6/+RP+NF9DzZlr7MOMB7LXifpeuOcfDxQVkzJzrA5Wc2TgF+dSez48oe6bJl/JGZjD3Bwv4gRaolx9X+s1NfcHTqeG4bX+hF7vdrzL7rQ2u0QRdIx1/LcuJ2+70QDiyHJJv3sj2luzKHC9emxVoqbMjzgDv08IHo6+uiOsTzTMD1yACcVIb1x4CrInGKVyhoLzt2MM+O+uXwLCc8Ywww5+S7nZLz6TW/KXqCL6djjpd/Xrp0jfFWsSU/GJ5nA37DXT0i8xVNOgdWpfEizdgv1uHcQtlX8oZ9/D4RwMDM6umA4LatrmbanfO5RPLs7K0So939YTr2+u13XbOy9HEo2IvoT+dBZrwePCY6oo+7nk6TV4hOl0EQDifFzp7kU9riYQ6qswAYsspq0haCpzEyilJr+6r0zePmmogBxP5iZH5p/gZY/k/K3VL9xMqyzqZK0gw5xPltPVa/x0wFblu8qs9r3SSFp7gA9RJq5sZTb6W0tkLU5eDlQa6ys5Q6wW9KoEwt3Q6Z13iplFbvBDHrAvPm3JxvC738qkv0yZmRwv/SOPdZ+ucFj3C9X39n4ftnyyebslx6Pvl9OuTN0v+zkC90vnUuw3zUq//QY/HOmbfI5PlKjMFtExZqUxCEavscid/EmsaxY/TZXkzU2V9IY4v9lWkR9D+eH1fdzVEh9t4z/FfXdEl7fNvXs8Po+0esz0yetf037vpsaUd/i0eH9GVrf5MLjrE8f/6kG/xwFcWllIoXCRtlhVmBeLecufPaPjMY/VVqpj/lCkmS6TPljc+VFVr1OVPMayqKChJivIrHRRVwTHesZBEeoNilYrXSyQLRNGRKNI7B+/Vu5L1BHBPJULjdPQZ6vb+I8S5FH3T0zNG090pqvsdJ4/w2aIm2RgfpCbXkf1ad3pHSQvqQeQY1HL692srE8VX3z3rDyzMbyBjVZnsb/SmlwpYZvVrgUnI8PjaPrHOy2tIA+WBw2fRsppGvBo5V3/UkuL0bK8zl2qGOx0ctcHoU3z2q/eiue6jJMfEaLdw86qpRwhckULi8cpl18z1TzE5MC1M+MTTr1s1tTqBlh5jvvSWdkJF6dcvSWKQo27Pu7NdCX3dMfriKi8ZYDPx/WokMYWlKBqSegJ83R5Llb1QmYAi7WJGElobtelTOg8/kMqABnQNlYyGPUTnfxhtoBFZIbMgdKMmlMfYzvfnNNrNp3IhHcTqUFpSt82XM688zQr4mxK5/U9CQFm7Pw1qiGTVZ6kmjYqA+xWKA+cCq17RXjqVRB4FTqwVFihbD8BigdK+/XPIBBFJ5CXQ+elvkNtukJXKjx1HUS+znHAjDNzCdd9WgplWbxZG7BKKI0kR/iy2evkvTnKR1hlarOU2Etm0aLXnrChWe9Runv1ui5p2cwpR9nZjpOc8/JtkAZtZOGGe5LCMJ+mgZ7Bhe5Uodh17US3x3xRtiiNdhaId5fkfHZhKXkVLTcS7oDbHR1oxx2Pvwyq0JX4KGuwj5OuZ5ALleelEX3hfER76IdLU2UeGiG7ifkD1LE1VLENirCoxXx0Qx+wqBQXY3XLKWKSysNCFkd9pRy2uvnOywb1RtQNLSR8qlpWnVsRIT2iP/vLeQP3CEkaN04RoUX6YZEI1TH1ZpdkQ7sRRSj16Weg6D9bepfHrbreGZU/x4iqOUFGrXYW6hFz0t0mvgQ04oD7+SpPei/Xuvo5P2OVx9Ctxcs5fP7n8cH0FPNB2FqAC/D4o7VAbA=
*/