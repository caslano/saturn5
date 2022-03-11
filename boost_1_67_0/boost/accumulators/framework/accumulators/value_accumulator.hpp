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