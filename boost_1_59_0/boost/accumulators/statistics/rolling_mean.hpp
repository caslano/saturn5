///////////////////////////////////////////////////////////////////////////////
// rolling_mean.hpp
// Copyright (C) 2008 Eric Niebler.
// Copyright (C) 2012 Pieter Bastiaan Ober (Integricom).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_MEAN_HPP_EAN_26_12_2008
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_MEAN_HPP_EAN_26_12_2008

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/rolling_sum.hpp>
#include <boost/accumulators/statistics/rolling_count.hpp>

namespace boost { namespace accumulators
{
   namespace impl
   {
      ///////////////////////////////////////////////////////////////////////////////
      // lazy_rolling_mean_impl
      //    returns the mean over the rolling window and is calculated only
      //    when the result is requested
      template<typename Sample>
      struct lazy_rolling_mean_impl
         : accumulator_base
      {
         // for boost::result_of
         typedef typename numeric::functional::fdiv<Sample, std::size_t, void, void>::result_type result_type;

         lazy_rolling_mean_impl(dont_care)
         {
         }

         template<typename Args>
         result_type result(Args const &args) const
         {
            return numeric::fdiv(rolling_sum(args), rolling_count(args));
         }
        
         // serialization is done by accumulators it depends on
         template<class Archive>
         void serialize(Archive & ar, const unsigned int file_version) {}
      };

      ///////////////////////////////////////////////////////////////////////////////
      // immediate_rolling_mean_impl
      //     The non-lazy version computes the rolling mean recursively when a new
      //     sample is added
      template<typename Sample>
      struct immediate_rolling_mean_impl
         : accumulator_base
      {
         // for boost::result_of
         typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

         template<typename Args>
         immediate_rolling_mean_impl(Args const &args)
            : mean_(numeric::fdiv(args[sample | Sample()],numeric::one<std::size_t>::value))
         {
         }

         template<typename Args>
         void operator()(Args const &args)
         {
            if(is_rolling_window_plus1_full(args))
            {
               if (rolling_window_plus1(args).front() > args[sample])
                  mean_ -= numeric::fdiv(rolling_window_plus1(args).front()-args[sample],rolling_count(args));
               else if (rolling_window_plus1(args).front() < args[sample])
                  mean_ += numeric::fdiv(args[sample]-rolling_window_plus1(args).front(),rolling_count(args));
            }
            else
            {
               result_type prev_mean = mean_;
               if (prev_mean > args[sample])
                   mean_ -= numeric::fdiv(prev_mean-args[sample],rolling_count(args));
               else if (prev_mean < args[sample])
                   mean_ += numeric::fdiv(args[sample]-prev_mean,rolling_count(args));
            }
         }

         template<typename Args>
         result_type result(Args const &) const
         {
            return mean_;
         }
        
         // make this accumulator serializeable
         template<class Archive>
         void serialize(Archive & ar, const unsigned int file_version)
         { 
            ar & mean_;
         }

      private:

         result_type mean_;
      };
   } // namespace impl

   ///////////////////////////////////////////////////////////////////////////////
   // tag::lazy_rolling_mean
   // tag::immediate_rolling_mean
   // tag::rolling_mean
   //
   namespace tag
   {
      struct lazy_rolling_mean
         : depends_on< rolling_sum, rolling_count >
      {
         /// INTERNAL ONLY
         ///
         typedef accumulators::impl::lazy_rolling_mean_impl< mpl::_1 > impl;

#ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
         /// tag::rolling_window::window_size named parameter
         static boost::parameter::keyword<tag::rolling_window_size> const window_size;
#endif
      };

      struct immediate_rolling_mean
         : depends_on< rolling_window_plus1, rolling_count>
      {
         /// INTERNAL ONLY
         ///
         typedef accumulators::impl::immediate_rolling_mean_impl< mpl::_1> impl;

#ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
         /// tag::rolling_window::window_size named parameter
         static boost::parameter::keyword<tag::rolling_window_size> const window_size;
#endif
      };

      // make immediate_rolling_mean the default implementation
      struct rolling_mean : immediate_rolling_mean {};
   } // namespace tag

   ///////////////////////////////////////////////////////////////////////////////
   // extract::lazy_rolling_mean
   // extract::immediate_rolling_mean
   // extract::rolling_mean
   //
   namespace extract
   {
      extractor<tag::lazy_rolling_mean> const lazy_rolling_mean = {};
      extractor<tag::immediate_rolling_mean> const immediate_rolling_mean = {};
      extractor<tag::rolling_mean> const rolling_mean = {};

      BOOST_ACCUMULATORS_IGNORE_GLOBAL(lazy_rolling_mean)
         BOOST_ACCUMULATORS_IGNORE_GLOBAL(immediate_rolling_mean)
         BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_mean)
   }

   using extract::lazy_rolling_mean;
   using extract::immediate_rolling_mean;
   using extract::rolling_mean;

   // rolling_mean(lazy) -> lazy_rolling_mean
   template<>
   struct as_feature<tag::rolling_mean(lazy)>
   {
      typedef tag::lazy_rolling_mean type;
   };

   // rolling_mean(immediate) -> immediate_rolling_mean
   template<>
   struct as_feature<tag::rolling_mean(immediate)>
   {
      typedef tag::immediate_rolling_mean type;
   };

   // for the purposes of feature-based dependency resolution,
   // immediate_rolling_mean provides the same feature as rolling_mean
   template<>
   struct feature_of<tag::immediate_rolling_mean>
      : feature_of<tag::rolling_mean>
   {
   };

   // for the purposes of feature-based dependency resolution,
   // lazy_rolling_mean provides the same feature as rolling_mean
   template<>
   struct feature_of<tag::lazy_rolling_mean>
      : feature_of<tag::rolling_mean>
   {
   };
}} // namespace boost::accumulators

#endif

/* rolling_mean.hpp
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
*/