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