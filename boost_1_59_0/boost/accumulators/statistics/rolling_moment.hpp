///////////////////////////////////////////////////////////////////////////////
// rolling_moment.hpp
// Copyright 2005 Eric Niebler.
// Copyright (C) 2014 Pieter Bastiaan Ober (Integricom).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_MOMENT_HPP_EAN_27_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_MOMENT_HPP_EAN_27_11_2005

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/rolling_count.hpp>

namespace boost { namespace accumulators
{
namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // rolling_moment_impl
    template<typename N, typename Sample>
    struct rolling_moment_impl
      : accumulator_base
    {
        BOOST_MPL_ASSERT_RELATION(N::value, >, 0);
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t,void,void>::result_type result_type;

        template<typename Args>
        rolling_moment_impl(Args const &args)
          : sum_(args[sample | Sample()])
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            if(is_rolling_window_plus1_full(args))
            {
                this->sum_ -= numeric::pow(rolling_window_plus1(args).front(), N());
            }
            this->sum_ += numeric::pow(args[sample], N());
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(this->sum_, rolling_count(args));
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum_;
        }

    private:
        result_type sum_;
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_moment
//
namespace tag
{
    template<int N>
    struct rolling_moment
      : depends_on< rolling_window_plus1, rolling_count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_moment_impl<mpl::int_<N>, mpl::_1> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_moment
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, rolling_moment, (int))
}

using extract::rolling_moment;

// There is no weighted_rolling_moment (yet)...
//
//// So that rolling_moment<N> can be automatically substituted with
//// weighted_rolling_moment<N> when the weight parameter is non-void
//template<int N>
//struct as_weighted_feature<tag::rolling_moment<N> >
//{
//    typedef tag::weighted_rolling_moment<N> type;
//};
//
//template<int N>
//struct feature_of<tag::weighted_rolling_moment<N> >
//  : feature_of<tag::rolling_moment<N> >
//{
//};
}} // namespace boost::accumulators

#endif

/* rolling_moment.hpp
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
*/