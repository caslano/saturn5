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
g1WSdfFVsfpbI2GeT4aFMOOQ1a3LNZp9oooCalzsHvv4PHQ0zXswwzs9AnzVkS4XUG5fzPsLTEY/3abNTT/Q1fAYBF9xYbILG6MbfD+UGgyRlw0fXx2EXd+0oBy7vovY9RCHsIiHXjbYta/k98KO++kkjyTVToOxpJKZktZTpw1/2WTVKYhSyfX9j+qXmay6M5Lw5Ieg7YyxYA1xk1W3QCLyNMMXv2vXGe4yWXU0UkrKxBYzWDXQsKWev5UCs6If7Nh/eleAQdcKyqDT7WknUN0GZMMx5Rz8+RXNn5cIf2aNLtW1v1a/E+aMNGHOBPe9p+H9/lpg99qKzLkw2sqc+4H2S56VnXGWXbBY/yXNn0Xju9cA4c/Fwp8p6kQXccuPsYXH/akNYXpE2ec7cNDh1+sfCXdeItz5Lb0XHD6EC3XBvG/+jDHv723O8z5KIjx2XhPgY6M18oKTU7nSTqQRcqwiRz8cZeXo91wqHP1KzdGfjjY4+nPRFTj6TTMCOPrO69DF2N54c/OkahaL3xcUix8Nm4b9aghu0SOKgiKPYY49y1eERJpsanID4GD7nVB+xqrEk7LkYQxBxe1PDwvQO9S6S2hy8xWsaKDDvgI/78B0FgUXuXCXezdMZ80HfrPb2f/+j+b/acyIeSu8ErO1YnpXS3rckMD0GEt6o8aB6Ud7+dPfbhqYvtWS3iNI++9Y0gsvQnqg/WfJkZ8VjSXUF9PRK7yzNliLsSwWBVsPcZ0X9D6nl9QHQ2SJO/Oz9vL1Bia3asZv9GckFL6mCfcj7Vc+EmtSf1qTdqtGnfyGj1+pBcURNE2BqhBlxaezWuXir6kMjriL9B5m+aRYRA6LFFFAHltEvi7ffQyCgAbqkd8BBnmjh5V66AawD56HLRN4Le+NCO+ip6nqt920SA2DCBpXv7ADNncnC8XublP4oO7iw9LFJ+uQ9sRCdLFMJXL1zBhzf6kDn/bUep+jucdrTRtIN8gXH7ufokJzXOzCBFpDvb2fMC+RPe2qcGwHx5stvCQtXG62cEBt6giOstpX6kJ1Oa3MnH+RnFHI2Ts/dTpyq5c7MpeIC9oSbq8D39t2/ucJHtj+Cdtb1CN5wMkjaZpVZIHqn8SWH85LvIWaMZUt5zg9WRBoJfrys75kYiBx4dMDRc7AOkjs1Rx+FNJY5xKOoe/iVKd9UTHbqzWtj0yWt7fXFUGsMSHEU1cNq2fsybcXvq1Ru0dQ+3aEnwVvU/06MHLfNnNtkFzzLbkeVq2Qi5sC2RuN/TYodg4easyBJVeIoh+9Gj9kYO5Dm8bcOzYTcyRios2d/d6JiAxA4dVYr72K9mD9kUx7zs/U4XC/t9C6LOq8j066S+Ryk4sKknE1Wl/FDmAmwFYNSTuVfbW+UsOTRoZhLi98XaMqXh5GX1/Lj6ov1Yl2AbJGkCNsg4k8uHQWbZsuMOvoLHVcgDryBxB72VW67BVYicXQU+4Br9hyWlI+Ur4RU2hoioscqGkP4WpKva6COnIrxpolvpht94M7ejMQSvnJ08aZlJxzIVpP8y7Xbw0II4mZflIqycTG1wTJLSA9UNPfrS9KWiEHmTCwq9PRmrRKYq2lakmpqyylvir54RdLjqMC96WWHAvVmraELkHSv6MBtcTlSTZPPdq9zM6ug42pb/ns5JCcH+2Fh1oEBZbt2a/onbjZ3oLdA7hyk0I8/dO9zghari7JxBVz+9Xjx1vkEY5UbJEj2m/KoW0ymP5BsNfaLt/K9Nzl8aXLuXxkeu70iBBPDZd3ZRF45tmwBKLx2kidGHMFRaJSVmajMiB4RXzptyibXM9lT1vuryE3OcRTR/KGJS4vkuu3YPoP3Y27pN7e7Wk=
*/