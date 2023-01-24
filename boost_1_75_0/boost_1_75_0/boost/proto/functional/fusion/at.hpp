///////////////////////////////////////////////////////////////////////////////
/// \file at.hpp
/// Proto callables Fusion at
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_AT_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_AT_HPP_EAN_11_27_2010

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::at() accessor on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::at() accessor on its argument.
    struct at
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq, typename N>
        struct result<This(Seq, N)>
          : fusion::result_of::at<
                typename boost::remove_reference<Seq>::type
              , typename boost::remove_const<typename boost::remove_reference<N>::type>::type
            >
        {};

        template<typename Seq, typename N>
        typename fusion::result_of::at<Seq, N>::type
        operator ()(Seq &seq, N const & BOOST_PROTO_DISABLE_IF_IS_CONST(Seq)) const
        {
            return fusion::at<N>(seq);
        }

        template<typename Seq, typename N>
        typename fusion::result_of::at<Seq const, N>::type
        operator ()(Seq const &seq, N const &) const
        {
            return fusion::at<N>(seq);
        }
    };
}}}

#endif

/* at.hpp
QV8rnv9avd08yyUm2ABWaJnAx6YnHehiYp9+4CR2cKudr3n//W2hywPy9zQcGp43jtIkpNkrgMSK1N4/h8sMU6xMvXjvkXi/6iysXR8x+qVreGQ+skPu+vY25Mthw/+cxuiI/XxjLkFWUzyGIJ3b0d6kKUY+jqTbP9lbKRyeh7pUVJIaNZGzuJlJ0P7GwvJihL6iVlJvdcbir0oytjhCTc0sXLafiwfY7PTD4Zo7waQb70zZhOk/ne+OSa25cBx16VRdNkHZq0YXEgNL23SHTCW8incWhKvnE61OtP4hsrayNzKjQpphvfYV1X68IAHB53DnQ2ZBLpvkDDl+nxaAdV94Y2xglyuCM5c4tZyVVBqDblaI/51efdeeztE04dXPZbvTF8Pxj2CPxQLhh7YOWm40ODRXIqcA51CC7I2U2w8qXdelxHbgVT2jSepz2+3FXZRFSnaXrPaNjYSOZdqWoPVVXk3HahO/zVFQ2UDtlYp9Wvun10XZ3WPjHekBSpJk9utJHNJ9aOIkPcrTyX88iY5S/ky85P9MnAD+X+qE5n/iJpz/2jXNjP8LNvF2UFv2/JoyCyWBZxDGi/bUQ0I3nMGE3GO8EDMwJmFLlLCZGNFci2qtW6u83JKAH56qYLVkM0EZMtng2M9x5ae+kKuyHLXO5nBMjM0qll8vRqORT2qOlZ3TnBuwy1xDuXl8ynF2+41hTFH+QZE7+nLU
*/