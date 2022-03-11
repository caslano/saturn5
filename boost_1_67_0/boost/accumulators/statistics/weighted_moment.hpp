///////////////////////////////////////////////////////////////////////////////
// weighted_moment.hpp
//
//  Copyright 2006, Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MOMENT_HPP_EAN_15_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MOMENT_HPP_EAN_15_11_2005

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/moment.hpp> // for pow()
#include <boost/accumulators/statistics/sum.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_moment_impl
    template<typename N, typename Sample, typename Weight>
    struct weighted_moment_impl
      : accumulator_base // TODO: also depends_on sum of powers
    {
        BOOST_MPL_ASSERT_RELATION(N::value, >, 0);
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        template<typename Args>
        weighted_moment_impl(Args const &args)
          : sum(args[sample | Sample()] * numeric::one<Weight>::value)
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->sum += args[weight] * numeric::pow(args[sample], N());
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(this->sum, sum_of_weights(args));
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum;
        }

    private:
        weighted_sample sum;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_moment
//
namespace tag
{
    template<int N>
    struct weighted_moment
      : depends_on<count, sum_of_weights>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_moment_impl<mpl::int_<N>, mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_moment
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, weighted_moment, (int))
}

using extract::weighted_moment;

}} // namespace boost::accumulators

#endif

/* weighted_moment.hpp
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
*/