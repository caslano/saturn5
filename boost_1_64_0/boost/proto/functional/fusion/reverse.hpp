///////////////////////////////////////////////////////////////////////////////
/// \file reverse.hpp
/// Proto callables Fusion reverse
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_REVERSE_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_REVERSE_HPP_EAN_11_27_2010

#include <boost/fusion/include/reverse.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::reverse() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::reverse() algorithm on its argument. This is
    /// useful for defining a CallableTransform like \c reverse(_)
    /// which reverses the order of the children of a Proto
    /// expression node.
    struct reverse
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq>
        struct result<This(Seq)>
          : result<This(Seq const &)>
        {};

        template<typename This, typename Seq>
        struct result<This(Seq &)>
          : fusion::result_of::reverse<Seq>
        {};

        template<typename Seq>
        typename fusion::result_of::reverse<Seq>::type
        operator ()(Seq &seq) const
        {
            // Work around a const-correctness issue in Fusion
            typedef typename fusion::result_of::reverse<Seq>::type result_type;
            return result_type(seq);
        }

        template<typename Seq>
        typename fusion::result_of::reverse<Seq const>::type
        operator ()(Seq const &seq) const
        {
            return fusion::reverse(seq);
        }
    };
}}}

#endif

/* reverse.hpp
rCqNm0gFEF7OjHte8Pmfni+wnsDURE52FtJMxuzmzhXuP12k7TfUVLf3GIjT7VfL2slMy/w89LPlJlcR7h2dYwrQB0HfFqeD55uJNteMvkuz/7HDFPVvShH4nGeLdpo6h+CEI9q+GGz3qj70PhjOA0sxP5BjC9v+rg3wqF77eK1OJNySTK//UBM4S7Wrni8wEH6DQq2xBGVDPrU5T4sw4hb/OPDbJr/QANHJb4oe7FKFUTdZb8OdNz7Z51Ks8XFEOHKmo05oDVA+NhdpBi/f9O65EeGCq0cutqkceuaZHa47O869voO5wj5R4O/SDYq3HQTgbICLcfEi4stGpEkOeD73YdNwFmGHgZpnisyzBY4w4eRMCTUX2dRZTAnBXy2UFiqrxG3fUoVyPnskQCHVOh5c7LKN2qWe5b7OqXRGSDhD3iNcFWcIduJ6nHobgDT8CcDhdOE5bhe+qcNn5JvZ2FrRDGt6KskQivbQ8b6CSGjX+zAu0b0Fb6vmZCnc7FjBbYaI0YeoN5OyBAku+PLxk9XGFobBeiJb7p3s45qQ+cNv+NGSM9paUDgkMA==
*/