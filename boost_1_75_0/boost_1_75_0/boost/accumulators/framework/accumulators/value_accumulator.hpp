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
CEhKpcoiJmzDOZiGS1ruLnOyRdBEj5l1btWmmNcpFpkUKUOaAUxmhlyYSdhwwCTeDynl8S/ACJXLJRlS4TiXZFI+CBaaHMoHUPDBs95hcuHYnINnfeekwrH9pIjc0vWap6i55rcwSIkj1UE6iRbfEGiUBUuMbQnLbtQLDCeTtCRDghFYkiktyZaW5EhL8qUlRcjlLnFIS6ZJS2ag8/OSudjLLA8WamR4jOFJA4YnCRs43eRJk+KVPzrYFTsGQixyTgUMexCWerHJQawCbpdrrwAe0z5v2MQOnX9DYFKsIniHOjYzpfgBHbKjGSFlP4w0sVHNsRp34inTXpO0BY11SlvG0RVNccpkp1NehWHVCmcpdDnMxmqcjW1kTxNXTBuZ0MSQtMVBuafRFQ1iBlehCJ727ktVgT7UNYShA1MIDBVXIU6AfEspB/lJ2OLH7cflTRrIlLaspNjVdH2crk/R9Rm6rqXrRrpuoutmujbTdTtdQ3TdTd/RSeEO/DKaIDAjgssZYUAIdMcCUTXgARAivUs23Iu6YAUb4REAfDaGE+Q9VVKhwK7rIj8X7J1v0JI+cE7dLAWiIh7AxWwjRIY79dLyXYQdN68j6EvWRBZsQ0F0GfwpSXcR1tyrYU0vvCnzKC7393vjBUdw+QFqTJJbgzj34Wv0PvaAw+FyH9wVL5QFlx9R08zQ0ty/jVBW42VEL5QqSZPXmoUW+Vag
*/