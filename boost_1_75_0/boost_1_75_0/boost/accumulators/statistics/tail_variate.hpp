///////////////////////////////////////////////////////////////////////////////
// tail_variate.hpp
//
//  Copyright 2005 Eric Niebler, Michael Gauckler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STAT_STATISTICS_TAIL_VARIATE_HPP_EAN_28_10_2005
#define BOOST_STAT_STATISTICS_TAIL_VARIATE_HPP_EAN_28_10_2005

#include <boost/range.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/serialization/vector.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // tail_variate_impl
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef
            typename detail::tail_range<
                typename std::vector<VariateType>::const_iterator
              , std::vector<std::size_t>::iterator
            >::type
        result_type;

        template<typename Args>
        tail_variate_impl(Args const &args)
          : variates(args[tag::tail<LeftRight>::cache_size], args[parameter::keyword<VariateTag>::get() | VariateType()])
        {
        }

        template<typename Args>
        void assign(Args const &args, std::size_t index)
        {
            this->variates[index] = args[parameter::keyword<VariateTag>::get()];
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            // getting the order result causes the indices vector to be sorted.
            extractor<tag::tail<LeftRight> > const some_tail = {};
            return this->do_result(some_tail(args));
        }

    private:
        template<typename TailRng>
        result_type do_result(TailRng const &rng) const
        {
            return detail::make_tail_range(
                this->variates.begin()
              , rng.end().base().base()   // the index iterator
              , rng.begin().base().base() // (begin and end reversed because these are reverse iterators)
            );
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & variates;
        }

    private:
        std::vector<VariateType> variates;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::tail_variate<>
//
namespace tag
{
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate
      : depends_on<tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::tail_variate_impl<VariateType, VariateTag, LeftRight> > impl;
    };

    struct abstract_tail_variate
      : depends_on<>
    {
    };

    template<typename LeftRight>
    struct tail_weights
      : depends_on<tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::tail_variate_impl<mpl::_2, tag::weight, LeftRight> impl;
    };

    struct abstract_tail_weights
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail_variate
// extract::tail_weights
//
namespace extract
{
    extractor<tag::abstract_tail_variate> const tail_variate = {};
    extractor<tag::abstract_tail_weights> const tail_weights = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_variate)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_weights)
}

using extract::tail_variate;
using extract::tail_weights;

template<typename VariateType, typename VariateTag, typename LeftRight>
struct feature_of<tag::tail_variate<VariateType, VariateTag, LeftRight> >
  : feature_of<tag::abstract_tail_variate>
{
};

template<typename LeftRight>
struct feature_of<tag::tail_weights<LeftRight> >
{
    typedef tag::abstract_tail_weights type;
};

}} // namespace boost::accumulators

#endif

/* tail_variate.hpp
XHRkZbWpHMzqFqza+o4E8eoIMwu31BYazjj1mVbWtg2tUpoywlqNoRvgtltiHG6UsuCN40oQ54vzxKhBSIjVJO+NEyZ4u/hVsyAWsPZEmlpHNXtMH2D6c6XMYvUAP+dK+cXqpxYuQnsgmP4ZzfNzwmqz5XdaIXaWDeOTvAP9527z3upJznXUev/sPzdGWHcBErpzzuWdg+mbUnanOyqENQpaiVUb4fX4J5Ono1pPKWrFY80roPerX+B57Sf7Au3bsRIf46jwdfTE5Mq+LeqNqCQ5F7Aq9jRyX0M/ogtvUhd8gdBr2JKCOBB99r1Ju3RSZJt6z0i+N1GDHT1rdgrrFkJeW75JhR0+D/mlYPoBz1XcmTXwAO2xqFdRn4KjWwjMI9OxNM5zlXrGpHu+VZK8fcaP99rhKUT8o4GV1rsjek6cf7dGM1uiLgG8xammFm4CuGVtbig2ijxqvb+2jX/J39QaNKY3s+R5HmRt6G+p+Yne64Ojw9SFSJP/GD/ed5s/s4SayVW7ooEOuZjQDnnU8QDcaagaCIbs9zFcn5mT6sPmyMKulS+EejNSGzFP64A64QFgpeaKNxhW2PWu6Y0v6hX6wpP8CZS+c0N2fCKs6Qt9jGj3hVXx9Bj6V6mzaXjMkzHh8hJnk5z55iRPQjqN/k01gd42nVDH0p+kol7qNDN29T51IK1bRpMTF8craGfrEYf8RbWEo3M4tYtS
*/