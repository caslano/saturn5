///////////////////////////////////////////////////////////////////////////////
// value_accumulator.hpp
//
//  Copyright 2005 Eric Niebler, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_VALUE_ACCUMULATOR_HPP_EAN_03_23_2006
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_VALUE_ACCUMULATOR_HPP_EAN_03_23_2006

#include <boost/mpl/always.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/framework/depends_on.hpp> // for feature_tag
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>

namespace boost { namespace accumulators
{

namespace impl
{

    //////////////////////////////////////////////////////////////////////////
    // value_accumulator_impl
    template<typename ValueType, typename Tag>
    struct value_accumulator_impl
      : accumulator_base
    {
        typedef ValueType result_type;

        template<typename Args>
        value_accumulator_impl(Args const &args)
          : val(args[parameter::keyword<Tag>::instance])
        {
        }

        result_type result(dont_care) const
        {
            return this->val;
        }

    private:
        ValueType val;
    };

} // namespace impl

namespace tag
{
    //////////////////////////////////////////////////////////////////////////
    // value_tag
    template<typename Tag>
    struct value_tag
    {
    };

    //////////////////////////////////////////////////////////////////////////
    // value
    template<typename ValueType, typename Tag>
    struct value
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::value_accumulator_impl<ValueType, Tag> > impl;
    };
}

namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, value, (typename)(typename))
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, value_tag, (typename))
}

using extract::value;
using extract::value_tag;

// Map all value<V,T> features to value_tag<T> so
// that values can be extracted using value_tag<T>
// without specifying the value type.
template<typename ValueType, typename Tag>
struct feature_of<tag::value<ValueType, Tag> >
  : feature_of<tag::value_tag<Tag> >
{
};

}} // namespace boost::accumulators

#endif

/* value_accumulator.hpp
Bz3z2nND/0bhVPY0gUcoifzmPls5Wvmn5ctbHegqZqWBG72ejpBiRI1FikeWmcb/tbmogBQA0ugpDo5a+aAjprO0Syz9HCn6CPbsyb71uxSk+j3TpO8+ItmPv818AioOTopSHYRDA7Y2enrJH4T425C2KFdMnfz0//46AOINqW6M6m7fWjrOLX5nTi1PWLJh/DVW+1cwJ9V3hK+ODgTCmW+UJC+uLDnXaWG/bEWPDWTeug87UNS7Nrsi4xnOnde8odGMvub+W9/ePQ+PGOeHkafITfG3MnQw7dFFaysnHAbsdz1yN/82mRJ03RKsXENArSMo/Q9MYn66nu42uliiD59uXTwX4h8VHb/O/aHOz8mmHcD/FNh158dtmlOWBkwaauJSS3WjHeaiWUCcESjlYWTlh12md9sXhutBfRK7BXlSnI0ooRif9y6CV190ltAu1roJY2p3pc5UpO9f+i/b5Doh+kuUAD9mdXdAVwysa9zYLacnlhOq29TEVazHuoC4kUdDrJeicUQiQitOgylms2Ly4Na7tPXvLSoSGzAUh2T7A/boitVNaAPyFQ==
*/