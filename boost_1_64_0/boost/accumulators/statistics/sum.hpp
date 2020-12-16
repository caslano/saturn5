///////////////////////////////////////////////////////////////////////////////
// sum.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_SUM_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_SUM_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // sum_impl
    template<typename Sample, typename Tag>
    struct sum_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        template<typename Args>
        sum_impl(Args const &args)
          : sum(args[parameter::keyword<Tag>::get() | Sample()])
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            // what about overflow?
            this->sum += args[parameter::keyword<Tag>::get()];
        }

        result_type result(dont_care) const
        {
            return this->sum;
        }

        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum;
        }

    private:
        Sample sum;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::sum
// tag::sum_of_weights
// tag::sum_of_variates
//
namespace tag
{
    struct sum
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::sum_impl<mpl::_1, tag::sample> impl;
    };

    struct sum_of_weights
      : depends_on<>
    {
        typedef mpl::true_ is_weight_accumulator;
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::sum_impl<mpl::_2, tag::weight> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct sum_of_variates
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::sum_impl<VariateType, VariateTag> > impl;
    };

    struct abstract_sum_of_variates
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::sum
// extract::sum_of_weights
// extract::sum_of_variates
//
namespace extract
{
    extractor<tag::sum> const sum = {};
    extractor<tag::sum_of_weights> const sum_of_weights = {};
    extractor<tag::abstract_sum_of_variates> const sum_of_variates = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum_of_weights)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum_of_variates)
}

using extract::sum;
using extract::sum_of_weights;
using extract::sum_of_variates;

// So that mean can be automatically substituted with
// weighted_mean when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::sum>
{
    typedef tag::weighted_sum type;
};

template<>
struct feature_of<tag::weighted_sum>
  : feature_of<tag::sum>
{};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::sum_of_variates<VariateType, VariateTag> >
  : feature_of<tag::abstract_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif

/* sum.hpp
+3+jfpfznPytsDx/67/M5G+PqoxNVeNvMdIed+dCA8LTbwXnb85g/G3LN0If47YF42/OavC353r65+9EJfRyxc/ny98Sv/FjtHr8rb4Fni++qy4/Mfn/viq3n1eenz3Sw9/+NdVuH/PFGbh/u3ifhX4v6aEHvPh4ZfR7dK9BvzWMzNtfr4y/xRUF0v9eC3/b1F1X8dSblfG3uXuN+RwXwN8e6V5uPj+61M/fUr6t9nw21z9pUb34t2D8Lc7kb62WVsLfTqWQYtF+odeHys6Dv8UF8recPSY+AvjbPSnl8JFb4Odv7fdXGx96/dtjoY+WKcb6d6zS9W+3QR9l3Yz179XK6CMhyPq320IfK4wqZi6udP3bbeAjIYA+7ulWDh/T3rOsf99UGx/m+ve1Xv82B6OPBJM+It6rhD5Kk2n926fXv8PnQR8JQda/r018BNDHbcnl8HHju5b1b1+18aHXv68s9FEv2Vj/yipd/yQ/Mn+TZKx/L59t/TPqd7nPuf4t1+tfhvTP+w6vfy+K/GtNFdc/aY+7c6UB4enXgq9/7qDr35d6/dsYbP1zn2v96+qXX2y+3LL+7dHr36HzXv++NDF6rvXn1fLrX6oFni92V3f9Mde/XVVuv215+cXKyyzrX7Xbx3xxB1n/dlno9/rLjPUP0pHK5BFHdprw/wbyCLdfHhGx7jeQRwzR0OHer6vuTNILlfHfzkWB9L/Twn+vN6o49XJl/Hf/Fwa/6RzAfy/sWv788baf/z71VbX5jSn/khZV+Lpg/Lez//zxViX819sF/LfJVzKffvz+PPhv50D+u3VHEHzY9P6xS/nzx1t+/uv9str40PcfOyz0+1aiHq9aP1bGf7tKfmS+18gc91xl9OEIpI+j2y30McioYueLldHHqu0GPhwB9FE/sRw+Ypf46WPmrmrjw6CPwdKi2r8mGH04TPp45c1K6GPmpaCPkzuFPjYcOA/6cATSxzvbTHwE0EfopeXwUetNP31M2lltfOj7r20W+nj2Ej1e34HqK1n/JD8ye4zMxxchc9D7XfHyNET44s7PpWQeX1KWiIXP/CdJeZnRnz/1UAbfAeUvnc3OiI4dC8PtDO7zSX/z7+xdCXyTRRZvmgCBFlJEoHhyFEGDClvUQgAbm2oKKRSRw4NDq4iwy7LSAi5nCYWGjwAKCp54r7euCBREoFzlFBRZUHe9lSkVOeQocmT/771J8vVADnWv3+b3S/K9+eZ88+bNmzdv3rxTB5ZVRymfB1E3X+A6TyAZ5hF2r3+Vzev/wZL7obvwmHTTp/P5vLQaRBH1Do0wy5TIBnXf06Kn0geHIOwVzkQISmKlYcy6VbfHAFRpBSgXPtzCZjCy/7tddsXIlfCo1h7jS9T9UtQ96G3jLqTTNWrPY1GrhdfDyl9W9SbvIfxlJR/GGVJYlIwbkeFfW5Zh9LNnBkfY6ZBoPz6TnWI9hUbdqtyuveNwyHfs+e7FH/O9ETdZyHw/eyvdLQxOrLa/JJvbN6EGmdl0qAN6YkRRNSCvh9a6XQfHTF9i1bfctoZpjkkFbL4boDFZo7jvgDnKp3IfhQu5U5p1GDqlGzb9Wp+q79fQ9q8fyZhPYfsctSxBCMwbnMvkF2QzRpCbJzCfrj7FXyr+wsQ39a9EfGOJ75y/O0x8vsAikieJBov99BTCJ0KN8yN78akshfkCC8inH1Akm/PncC1bxP5rm5BbPnz3X9zwxoaoGjfCkf4J+kjNxmx+Rkd8Momq9iEln+yhxrXTORvVWrbA2E5e7Q1MSuK8cTnsIPzTVd+B55kfGSU+BBIrAuEW7YnHHgXd2J2IgLxvQw5EOOqDd/sEwO68byhA/Q08iuwmlXo=
*/