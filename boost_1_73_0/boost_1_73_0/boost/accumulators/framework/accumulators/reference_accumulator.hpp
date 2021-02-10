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
aWK/vCJgNHnfOgERVCrf6WaE+R7UrA+qbF/Bj7It0kSCD0klWGUvNLrTTJnV0g7mlitdiCUcnmuwAq9bExAqQA9Fg4rUeKa8RmEA2/QkxP2X5Db5x/2xS/s92WO43uMojONtnqMLduw1HY2gQVKxo4rX2VeoRuII2Ndfi0GsvtfYvchF+/FtGH1MNSXaD09O+6s7jkcHgGFT6qkkTn/OszOJmbwfvEyywlLUnrP9fVZBtJrBpd6dn9SeG/I2w0CizvKkqiW6clVf/L9V+i1TFvQMsLaEWjbGqZxLq2xyFVJrqeM+k+9UGBXqvClzYllU7LARqbL9tdJM8+1Bv99pP8aB/04d9wVegiICwxwDD8jauGUoDhxSpzkZKzEaJ4D3CC/EpTng0Xd+CdPlTnxMu+XHaocq1+f5fIr0926/3Ts96AxtgRQFNVX4kVbVopqLOeeU8iROHFFoVcj1csrkllPJybsPtUQqea6Kcx+S9R0nVojFWrgYj+xhwzpgyT2rHBamtM45S8jI2JHeuuIaKqxLq4Kvmf9KCIWa6XSswx6YKcuFjpkCEg9GxCRr8L1B15m2GvjckJpL5Ld/CQIadmIJSt51MzsTZ1a7y0RtASnIpSnJYa1VtC6dkcO6gD4ekMdaQDnPVBXecUtN
*/