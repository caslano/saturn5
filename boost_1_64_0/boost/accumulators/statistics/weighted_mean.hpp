///////////////////////////////////////////////////////////////////////////////
// weighted_mean.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEAN_HPP_EAN_03_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEAN_HPP_EAN_03_11_2005

#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/weights.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_mean_impl
    //      lazy, by default
    template<typename Sample, typename Weight, typename Tag>
    struct weighted_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        weighted_mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Tag, tag::sample>
                  , tag::weighted_sum
                  , tag::weighted_sum_of_variates<Sample, Tag>
                >::type
            weighted_sum_tag;

            extractor<weighted_sum_tag> const some_weighted_sum = {};

            return numeric::fdiv(some_weighted_sum(args), sum_of_weights(args));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // immediate_weighted_mean_impl
    //      immediate
    template<typename Sample, typename Weight, typename Tag>
    struct immediate_weighted_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        template<typename Args>
        immediate_weighted_mean_impl(Args const &args)
          : mean(
                numeric::fdiv(
                    args[parameter::keyword<Tag>::get() | Sample()]
                      * numeric::one<Weight>::value
                  , numeric::one<Weight>::value
                )
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            // Matthias:
            //  need to pass the argument pack since the weight might be an external
            //  accumulator set passed as a named parameter
            Weight w_sum = sum_of_weights(args);
            Weight w = args[weight];
            weighted_sample const &s = args[parameter::keyword<Tag>::get()] * w;
            this->mean = numeric::fdiv(this->mean * (w_sum - w) + s, w_sum);
        }

        result_type result(dont_care) const
        {
            return this->mean;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & mean;
        }

    private:
        result_type mean;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_mean
// tag::immediate_weighted_mean
//
namespace tag
{
    struct weighted_mean
      : depends_on<sum_of_weights, weighted_sum>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_mean_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };
    struct immediate_weighted_mean
      : depends_on<sum_of_weights>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_weighted_mean_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };
    template<typename VariateType, typename VariateTag>
    struct weighted_mean_of_variates
      : depends_on<sum_of_weights, weighted_sum_of_variates<VariateType, VariateTag> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_mean_impl<VariateType, mpl::_2, VariateTag> impl;
    };
    template<typename VariateType, typename VariateTag>
    struct immediate_weighted_mean_of_variates
      : depends_on<sum_of_weights>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_weighted_mean_impl<VariateType, mpl::_2, VariateTag> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_mean
// extract::weighted_mean_of_variates
//
namespace extract
{
    extractor<tag::mean> const weighted_mean = {};
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, weighted_mean_of_variates, (typename)(typename))

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_mean)
}

using extract::weighted_mean;
using extract::weighted_mean_of_variates;

// weighted_mean(lazy) -> weighted_mean
template<>
struct as_feature<tag::weighted_mean(lazy)>
{
    typedef tag::weighted_mean type;
};

// weighted_mean(immediate) -> immediate_weighted_mean
template<>
struct as_feature<tag::weighted_mean(immediate)>
{
    typedef tag::immediate_weighted_mean type;
};

// weighted_mean_of_variates<VariateType, VariateTag>(lazy) -> weighted_mean_of_variates<VariateType, VariateTag>
template<typename VariateType, typename VariateTag>
struct as_feature<tag::weighted_mean_of_variates<VariateType, VariateTag>(lazy)>
{
    typedef tag::weighted_mean_of_variates<VariateType, VariateTag> type;
};

// weighted_mean_of_variates<VariateType, VariateTag>(immediate) -> immediate_weighted_mean_of_variates<VariateType, VariateTag>
template<typename VariateType, typename VariateTag>
struct as_feature<tag::weighted_mean_of_variates<VariateType, VariateTag>(immediate)>
{
    typedef tag::immediate_weighted_mean_of_variates<VariateType, VariateTag> type;
};

}} // namespace boost::accumulators

#endif

/* weighted_mean.hpp
sfGVQ6A6+gTU7Eeqf2mhK9X/2IfHXFs0PqSCNtCGfL0Itp/ox+rxI6kUcwwtpVWylCr1pfS0vpSGsGAhJViXNVhXidSFOdV4RRcaKpofHba8fgv2iOnLMHr0xrBwy15h/AelH/28uaCvxslX8/nS9+rsFP0g5fDZoWfLT/aknXB8z+XPaNz1pyJ2XXxBULb2i3rh6cxfX4NC1LV1tSwLmFpf6+9BggCfww/Xjg+0Aie/D+oSGIRYvC7oTkw9DqiZqb8QH4Gpr4/i7hTOfnaSWWPWT9oRc6P8+R3nRfLnE8818OdJRv588IUB/nyLpUn+PMnAn3fgD4Q//7uF2W40uim2O+8M5s/HHzPji93/Q/z5xX0i+fOaPjp/Pqh3M/nzTubfgD8/ir3h5JRIe8NHe+k7adU5QXvDw2a2N+xkboa94aoLg/aGHtMpszdcdG6EPZ40QezxDvUM2uPNOx/v4h3CTPCh55tpj/dgatAe73l/7W9jj9d4+z7sHdk+tafevtMN7Xu9b6B9g0zH1753uwbbV/nLb9S+JkzNDvSKtDeM7Rlqb/jUGUF7w149gmZoFecFcNBQf+2vtTfckBws+C694Hp0h5MQ0PHZG54ZEzRVKwAr3Ji94c2GChv6BCp8EBUG7Q1RcXPsDRdGB6trcaT2f87esKZnpL3hZd2D3XOwu8HekDYVtdyukyvXH6k9HnvDN84Ve0N07THsDXv8UKv36sLDtafS3hDytjPD6J2zQsPVSWH0Tnh6WLghrDxn2Pedw+Sn3u5h6WHh1eHpyWHy3HB5bFjYGZb/zR5h6ceQpzp7hvVPuDyWwk3y039ONvLTrTsH+GnfWQZ+enX334CfNiWfID/9ca8AK/gnMEXabv1p0lH46Xe+r20GPz1JLzchWG5xUlP89Mjva085P73u7BPmpxu6hfDTD50TaOyZDVpjD6jzz2wWP/18dQg//XRd7X83P/3oWZH89EU1zean7+gZ4KcLu4Xz06cn/wf46VVJJ8JP13cJ8rgpGDJt03iu6zH56ac7B9ncRT/VNoOfnmmo672Del3pXY/OT/czVOT4qfbU8NP9ux8d3/dPbhrfa/6LXMrQfLI5ynf5roxi7Mr49JAz5XsnlFhSIPTe7qzb+RYZQNCsCt6nBgsG8+XWZS6rpfzzuFZVeM1qbQ68Rsfz2xBfdCtHuRqV43NG270J0xyeGnMBu0mzkS+fYU5fbhQ4L7JWTNnhSDnkSlnhUnbI1aqo1bosChW0lQpQfkcp347ybfyGyduWynf4rkH5rmlJTroAgm+BEV989srL8wnYk9DvwGc3YCYLNvulq7b3jMoH/FlKdr7DN5HQFugPVirIRvMcQGrus6E3kDm2Cy6/s/vL0JpeqRe2cvgr7CWtnf5VPAE/y/LGstHfZYCYchdYK2PZTVd2krnA4s9OhqkUcJAvO8nlfZmp+CzlW7tn32Uu79sapkvPVvYBC2Qxjez5JXPMOPs7RD27fLcnWc/EJzQPf3GUf9fCmXHEaR2Me/D9djCvGZVjW+AsLBu6e+VftWD160qqja5CJgQ5rC21sy4bOjU4I3BZ6rKL/QwSVTL25SwmhgEY3zQMGFyKQJSN5XRH2ibhLH05qWwW1AYuEOPwZ4OcJRPPTvhLwl8v/KXiLx2O2dR9p/3op697EF5OqQ3ON4x/SuqFFnsJeGzfH8xOzzfmgpos7/kuRfrEpaCTdNyMpXbzycLMJ/bj+VLqoNmy8YzA0ed7o+XoU+6dvzEfciunUsZ+w76ny+xa8qEfKYmxvAFqwC7vkvkcXPKsPF5gV17QtNAOW+juN7q8zIWeZqYwT1lKk6fBNrktnXloSunOlCp1+/g=
*/