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
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
*/