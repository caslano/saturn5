///////////////////////////////////////////////////////////////////////////////
// reference_accumulator.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_REFERENCE_ACCUMULATOR_HPP_EAN_03_23_2006
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_REFERENCE_ACCUMULATOR_HPP_EAN_03_23_2006

#include <boost/ref.hpp>
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
    // reference_accumulator_impl
    //
    template<typename Referent, typename Tag>
    struct reference_accumulator_impl
      : accumulator_base
    {
        typedef Referent &result_type;

        template<typename Args>
        reference_accumulator_impl(Args const &args)
          : ref(args[parameter::keyword<Tag>::instance])
        {
        }

        result_type result(dont_care) const
        {
            return this->ref;
        }

    private:
        reference_wrapper<Referent> ref;
    };
} // namespace impl

namespace tag
{
    //////////////////////////////////////////////////////////////////////////
    // reference_tag
    template<typename Tag>
    struct reference_tag
    {
    };

    //////////////////////////////////////////////////////////////////////////
    // reference
    template<typename Referent, typename Tag>
    struct reference
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::reference_accumulator_impl<Referent, Tag> > impl;
    };
}

namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, reference, (typename)(typename))
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, reference_tag, (typename))
}

using extract::reference;
using extract::reference_tag;

// Map all reference<V,T> features to reference_tag<T> so
// that references can be extracted using reference_tag<T>
// without specifying the referent type.
template<typename ValueType, typename Tag>
struct feature_of<tag::reference<ValueType, Tag> >
  : feature_of<tag::reference_tag<Tag> >
{
};

}} // namespace boost::accumulators

#endif

/* reference_accumulator.hpp
EJl+gKBmty+GIa6Yg3HMx3NxTMGeUnS+k31IqC0yh294HFATNNnuSmq0QIKJ3WVAstEaFTULL1z1ZvgbtLHFu2rTGNAzkPVS+M1hHBYtaBa69eQCl/16Ev0Af8BtUkmT3rnaPEji6ykn3eHYy1haummgarMocmyWsIXI4lo2InLL6/EpDBgs12ihxt8x7qKWoxJZ9ndlbVOPSrE7oTqcE/hO8tSf7xbkaRdFpyshoEUTToFMzRjr7Em1Os32AsV1jrtpxixs8aD3JkUDWVrmOyCQ+hOXTVqtMR1wYFvPYaJh98eZ6w6d9IuHRwCJN4z0lFIY0sz33exMXgVUAy6hJ37xetpyU99jRKgThD5i3x6J4fFtFGoVF9gu6lZWHoKnaz0KChcBDkqUaa3cfIgU25yiAvo5UUDD0SRWK9YR4dMgGSJrvQoKoTCoJyxXK8rTPTDkcdfGagJYcwQu+6/5fzgksvvqPvjTRSXs34F9EjBnMWXDTHvHuHbvN9tt64NUa8oloU8yDLvgrXfrNoXxwrO93UxNn67Siqr3LmsFAtVxQgNbqkTKOzSTDg==
*/