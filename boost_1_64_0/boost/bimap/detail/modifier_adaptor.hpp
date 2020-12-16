// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/modifier_adaptor.hpp
/// \brief A binary to unary functor relation modifier adaptor.

#ifndef BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP
#define BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/// \brief A binary to unary functor relation modifier adaptor.

template
<
    class Modifier,
    class NewArgument,
    class FirstExtractor,
    class SecondExtractor 
>
struct relation_modifier_adaptor :
    Modifier,
    FirstExtractor,
    SecondExtractor
{
    typedef NewArgument argument_type;
    typedef void result_type;

    relation_modifier_adaptor( const Modifier & m ) : Modifier(m) {}
    relation_modifier_adaptor( const Modifier & m,
                               const FirstExtractor & fe,
                               const SecondExtractor & se ) :
        Modifier(m), FirstExtractor(fe), SecondExtractor(se) {}

    void operator()( NewArgument & x ) const
    {
        Modifier::operator()(
            FirstExtractor ::operator()( x ),
            SecondExtractor::operator()( x )
        );
    }
};

/// \brief A simple unary modifier adaptor.
// This modifier is equivalent to bind( Modifier, bind( Extractor, _1 ) )
// It may be a good idea to start using Boost.Bind instead of it.

template
<
    class Modifier,
    class NewArgument,
    class Extractor
>
struct unary_modifier_adaptor :
    Modifier,
    Extractor
{
    typedef NewArgument argument_type;
    typedef void result_type;

    unary_modifier_adaptor( const Modifier & m ) : Modifier(m) {}
    unary_modifier_adaptor( const Modifier & m,
                            const Extractor & fe) :
        Modifier(m), Extractor(fe) {}

    void operator()( NewArgument & x ) const
    {
        Modifier::operator()( Extractor::operator()( x ) );
    }
};


} // namespace detail
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP

/* modifier_adaptor.hpp
ObF1rLKy2/eUtPj2/QRxNq1067liQV0RBRCq48ej6xh/Cds37gnbN+6tat/j7bw/fhjtO3xe+e70UISX6Fz9Qswi+th1K8L6Q5BJipLJYmxBRKiiCtkhI5Mlv8TQw8niN29Xk8ctoXZ8eUkl5a/2tMX4O8fpzr8jMSobhc824TaHyo5HEU5zOXb8aIe2z/eQLFZZPWJIxv8kH/9j8S+d3rS1lstMDXVlo9x8u+VMHrlv8uiW82ZzL5R+6XKRrJRJY1Sb29Auvs09QF3uDbW5iuGl0X3q2ug2J3+9pE87+uycCXK329SaVvSZa6PblPRDE39M/5ipg+5vVx5uVR4yV7l5sPpH3/la+b/ZUzf4BNe9sytb18/Ylxn/D6tvulw6sPP0nK9bfZbbBtwzGmZF64Onr9pIfaxqzxxCsK/q3LAsUm7qqyi7er+yU303eMyxrvLQr50HH5a/y6228nXdq9e9oa4udtIb02e90iG+/TwVbD9u2Uf3WU/Gtp9VzbSfVa1qP1F90pPNtJ93YXVyLvK/Phc5Myt4/7nem5zVd9Y/+qmxp135y3lv0KBuMvrJj9udsWpO/q/OfOeJU7/WZf648g//HOVBM3dlLr5JzHwRc4y889bfb5t5LP1WABS1cQvoHXM0jyV/fOP7+zvL8peZIL7zXH8Y+evl4W+Q/O3GFMof36b4g/z9jPxdxK0Bmhf9OLxE86rT4Hh4KbwQTodTNV96GcQYHeNFmv8qhgs0T7oIlmoerAyugHPgDbBcurkr4G2wEn4Xztd82ALNf1XBP8Aa+AGshSmaH1X++Rbyz//58lftfneQN/nrCEvlD/8N2bALzIE5sDfsqnLJg0NgLhwGe8BRms88V+4TJDdaKLvSx7jafP2UOxqz4O3y1wHOlL/F2id9JewMr4bnw2vgRfBaiN+QDnZ4HVwCV8JlcLXK+3o7XasSl9uOFN7HNey1xjy7pn2L5hz34a+6YxtnOSbjSu85yMce+mjOQ/70of/8XOShh1o2H5nxcGhOcsjDH515ydS17Z08zBmYaZg6zDrMdsxOzB7MobXJOcvklbySV/JKXskreSWv5JW8ktf/x/Vv9s4DvqrqDOD3vgxGgiQBQgYjhCkzhGEQxMjQSBAioIAgYSRIIEDIgLAUKypaVFSq1FXaUkXroIpKbVWqtmLroJZWWrHiLCq1FKlFa7X/973vnXte3nuMlvLreBdO/u/Me9a95571nZMz/8/W+zknZv1/Z2sOfo3OwU9GtUCNQX2jI2FXh87Bl9VV6Rxk2LyAuk03c47vi34Y45luw3315kzQj8XNAGZUEwMyAXXOp9sxzvuEyvEnPg3mPEp84ePut5OuwprQdFVVM/yucw63ybncM+3zTtV9W2tup17H3tXOGnvvcRznD3Av4q33wqzAzEnUh8z9TdU5/TxNR1fUt3BXVWPmPMvmVAXiXxFYpy0LjNMk/uoOX22cJtHmrtVNXtS56jmeGzM/18u/hyT76HMNwfQSN9ImcTvu+d9gXhzQvGinedEKtYpwty8y5yhU1NaE54WWpbpLNeW14xjm2iLF3z7b4V3dC3G9Pj9XoBbwI6XazM3OrwoVncH9g/GbYZ6HU8X9QmcmYWt8NYxMy/1Mb66twTPXRfRL/O8h8zy9nK7qmPYi2OmcoXUyqJ8ZeLY0zXN0Hn6fpvkN1G4GYbfUeGnmjVEu7y99tnzYsx+gwnu21D1pSNc0/Ez0v2T8lF0e+u54jxtQ+9gY4M1RvyzunnOWEaetKD3Dnov19VJC3hn2abW6V0jPA/5K/H5Twh4rfmZUXmI9C43FfWtxX+S5N/I9rsrg3Um9fwf2g1OpQ/2FR98vEJw=
*/