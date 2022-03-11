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