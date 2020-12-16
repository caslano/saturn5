///////////////////////////////////////////////////////////////////////////////
// weighted_sum_kahan.hpp
//
//  Copyright 2011 Simon West. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP_EAN_11_05_2011
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP_EAN_11_05_2011

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>
#include <boost/numeric/conversion/cast.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
#if _MSC_VER > 1400
# pragma float_control(push)
# pragma float_control(precise, on)
#endif

    ///////////////////////////////////////////////////////////////////////////////
    // weighted_sum_kahan_impl
    template<typename Sample, typename Weight, typename Tag>
    struct weighted_sum_kahan_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;

        // for boost::result_of
        typedef weighted_sample result_type;

        template<typename Args>
        weighted_sum_kahan_impl(Args const &args)
          : weighted_sum_(
                args[parameter::keyword<Tag>::get() | Sample()] * numeric::one<Weight>::value),
                compensation(boost::numeric_cast<weighted_sample>(0.0))
        {
        }

        template<typename Args>
        void 
#if BOOST_ACCUMULATORS_GCC_VERSION > 40305
        __attribute__((__optimize__("no-associative-math")))
#endif
        operator ()(Args const &args)
        {
            const weighted_sample myTmp1 = args[parameter::keyword<Tag>::get()] * args[weight] - this->compensation;
            const weighted_sample myTmp2 = this->weighted_sum_ + myTmp1;
            this->compensation = (myTmp2 - this->weighted_sum_) - myTmp1;
            this->weighted_sum_ = myTmp2;

        }

        result_type result(dont_care) const
        {
            return this->weighted_sum_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & weighted_sum_;
            ar & compensation;
        }

    private:
        weighted_sample weighted_sum_;
        weighted_sample compensation;
    };

#if _MSC_VER > 1400
# pragma float_control(pop)
#endif

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_sum_kahan
// tag::weighted_sum_of_variates_kahan
//
namespace tag
{
    struct weighted_sum_kahan
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_kahan_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct weighted_sum_of_variates_kahan
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_kahan_impl<VariateType, mpl::_2, VariateTag> impl;
    };

}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_sum_kahan
// extract::weighted_sum_of_variates_kahan
//
namespace extract
{
    extractor<tag::weighted_sum_kahan> const weighted_sum_kahan = {};
    extractor<tag::abstract_weighted_sum_of_variates> const weighted_sum_of_variates_kahan = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_kahan)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_of_variates_kahan)
}

using extract::weighted_sum_kahan;
using extract::weighted_sum_of_variates_kahan;

// weighted_sum(kahan) -> weighted_sum_kahan
template<>
struct as_feature<tag::weighted_sum(kahan)>
{
    typedef tag::weighted_sum_kahan type;
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_sum_of_variates_kahan<VariateType, VariateTag> >
  : feature_of<tag::abstract_weighted_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif

/* weighted_sum_kahan.hpp
HbPxD8gz3w6Rounn5xKgazVzyjd4Oi1V/s9Le+g63qUx+qtv9jDsr1MbSBrzgAtF+KiIvNUoY2bc0gVUxtySZxdQGRv9e0qpZq2MfwVfXwm+dtNLVjZwR6nnPC3OAYG7rQvp6BQjz35J1qrDJ1MS9WalfHMtgH0Ffw78leLPZGniZ5ZHVJPJx/6Zoiy//hd1x5zHAOff8TdTYBe4o6OjzdH/xz8sSPyjHlj3v/bT/B8tCOwn2cpqQUMjkiIza/uvEcODBBBaTEN0DsWw/0k4yRhuKV8b98ew/dZG+53x+7D09Ej8e1T9x+cEUYyPBloaty7RpFwAJQOfA1ZqdFufGpXPzJ37PG+qtzCa9XxMoufj0PR8MjU9HwfZG7JxbmYmr9NmI61I/C9AgVgSqcJnazXdt9PBd4XtNwNC2ycbUOP9I+HMiP4/Wn+hw4/ev3HGsIxvE/rzt/xDunqH0oA2xaNN0sfobPWJ+6SbY7zp3uHRzdcf9Q4dEOJCjC5tlojg/AkLZ4aFk7SwVl5CeHm20PR0YxDhuPD8nSSicfpH+I/r/67Txz0hi/KvThSlQOqM3Lt8jvU4KL9TvXQWuUMSngT93KiYEMsqQn4g9y5to4q++VuAY9n5U/sAx7JQc3GP6uhwBX6NhMBSP54v7OsS5qoTF57eAQcopAIJPjLLQdeGs79X9elxdFLtd7dFJgWZlI3qmMUiA8F9PJ14i495uAVP3bfQtuCVSdk+u1kdzmONeoagHmhOuuDXfyNz2fkJZFlUxfAV2shGMVrZVdPDc9hfkERXPa9M/6PJfdpU0nyYMjbe4S/zV2Smpxd8a11ee6anwV8w3qHU2dkun/R47DiQmP+KnMRfNVWXTxQXmaib3dTjhSIAPA+DsGct64KqVdBZIJmKwORSBB7imRZqLPKtrzLPRB1MJxLMNannaxVdeDerS3BF90PqplV0n1TUh/Q3paKaeTAZSOchWEcG5yB/2N5JrA/kiMC/FV3ajb6fJKdPA/EtSsTnmCGF1VfrN6u68LbcrYk4/yCZbZT5yodRbYz6gyKOYUY4IEA4Lct3RS7GZsjz8Sa1BvR9TSLUnZfnslLk4+Lsd8SbUUKq/bIGNNqVpSwfPQjqZ91/9a9xfkIE57uellP6teI+uj5LeIoEB7wK5kDLRDkAz2O1dCdrPHHRf/ER9wA7UhTHdznYlY8hzFu3KHgS8OsPhI8G7/kCr8MzsEfHDjSdGyBkUL4G2AWdQDzbLciz6i7k8cbEIAOhz5vspc/LsLXFuuOlqJ6XRwBvo+SBYvMOAZnXYcPiXd+hgykLG9vIaG9+nLcwQf1gIivbXGcvXSTFrKti/UT1b0sgSHhWm19vyPxaWBUUof9NneOlKXKUnpHTos/W/aqfpv/7lIbWEhPQAoC5j7bqcx5BbGXMT+3RWU0JW7X9SKb6k4ZTIKjgabcPjWA3cxUiPE18CaXBROh3hP56sB899Zn7Bf11QPLM9oz+xsrqJwx4vo4B58jm/eb7BgyYyhjwhlGB7G6F5lsM0Ls3Fgo79JZAphVzWepP0zMWWyomh5jt6PAdc2Ns4udSVjs99Z3HEE02xBediXnUmeDzJZRDcIXqzXavGdUSINFapUerStN/eYJ7Em1+EkHpADnfumfk0c+30srSze42AwMIvdxfNqW/qeA76/IDZ1YcZfyf0Oij/TJLe67S6KNDC8PpI3NKVEELtCXl8uiKRsIuUpuJtyumFHNBrB2iphRs2JH071+D57l/G92I/09D+u/ubMT/pyF96pzI9GxD+pV/bsT/pyE9DlKREH6XVqVq0XIoMT/sb288JiBWHFNZm3yaXp2aOJ/XOWkGHeGxelI=
*/