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
TSRofJIJZyjJgH2fz5a9VVDVPk3V2oIxVWkJDxTFpmU2A1Z71zrptl7j2ezZu1bvtHNef4SY7fkfPcuWgyec8lUctHsKF7vL2uQeicKxF8ciRWt8P7sIp9DETei9HRe4t0QkY+msFRZlvIiTcAaiZDbHPK64cJf+1SJy1ZVoTPMYN7VXgDTYIpjaR9dIzxjwSMLF0UYT49I4F2/0fo94HPk8qSIb8pFOlGMsJlLnmSVxyjzlLE3bjTzuExOOIJiVdweCJPZvPNC85cyuYfccR+4lJqfdal43fT4dNVMxr3YYJOQ6A0i3iCgLznFSDY555D8Eg6HfeEuduYskFAkxr7zA44ijnRuknhdJJ59cCtE7X55kcUE102njxMQNCT+KE3M5jFyq7CAkIBLXGl24MCoQQnQapFBuWyzPHV+vcZMFQ8OjG1g7EH+XHm3PknfBYERWsfjVMgBpEwY7h33/PY4bZoUO9r//3ekM3qyd/eP/fPcPTqznbGNXvUDlWYPtQbuNvXNM+b9Gdc2Q8UH/Tffw9ARk/GmvR1r78aD3mCjQEaCXsppKUkQzYR5O8fV+tCXFtISRH3uIUh/tOVgVfv9pei8SEyRedInHbZgvlB+wxfjKm/G1ZElajJhtckLZpJXeFGSzaVFq7PNc
*/