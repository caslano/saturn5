///////////////////////////////////////////////////////////////////////////////
/// \file begin.hpp
/// Proto callables for boost::begin()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_BEGIN_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_BEGIN_HPP_EAN_27_08_2012

#include <boost/range/begin.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::begin()
    struct begin
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::begin(rng);
        }

        template<typename Rng>
        typename boost::range_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::begin(rng);
        }
    };

}}}

#endif

/* begin.hpp
ijcWH1G2HlaL2cqYzUkUT5j6nmMM27D1bIayPJj6LFUNNmDv2nSKJ6wNM1PLuj9QbfZHj2T2T6celEuOsNbMvpy1LFlZIMyMWVTTshPKQmDmzNZn/9WBchDWmNlvDj9QPONhdsycnh0LVpairbu4yWcczQ6YC7OjswO6KyuGmTLzcDpAeV0Kc2XW92xKS8qXQHw+Y3a++cN+FBdYQ2Yp4yZfor4Eq8VswrYImnEBML7P76q+7KgsAsb3+exMfDHVJozvc1qtrRTPJJgJs+7zn/ekXILZM4vr1Yxyab92vpbFw+iZWTBHZg0TB99VVgirzcwnuO5fFE+YB8+z6pZFVGMDDHNi7r1HdD4XmCez/K5etC4Qxve5amvcKsozWFdmaU5jnypLhnVg1rqh30GqFZglz+s1XnQPxTB+hsnb1tM+zT9EP2N2JeXeKcoJWDNmH26b3ZbuHebNrNezbluUxcDaMztSq1sk3RGM72VS4F8/0T3AGjB7XubdjGYxjN9RrT//YabMdCB6JLOVPdL9lbnBzJldTnI+rMwLxnOp+b1Or+h8ML6XbmN/vUj1DuOxHlI2aivNW1gNZp9MGuitLFZ738tJ5Y/obmE2zIx/cu1Fcxpmzezrlc88Ka9hvG4DLy2yoBmu7SXOJHytshIYr4c6v/X3UGYchO+3zGblftyXcgLWiJmXjR3NPz8Yf5/9nJ5JFE8Yv6OA0/NMKJ4w3iNTWzWaQbmk7cXpX/+qRX0CZsJj7e4fRn0C1oXZmz3XnGh2wMyYde1XXodqBcbjYpHwWaIyo0GG67LbbapBdQRzYtZ5yl76zOeprTtc9933MR+YAzO76Mkf0yyG8fNdS203QlkozJVZtU3rx1Ceae9bsLqY6jYB1oRZfEJgENUmjPelBo8WrKE8gzVlFrzng1TKJe19j/K6X1NWDuP357tt4AOK2WDDO5rjPfMk5QuMP/MDy9xEigusI7NFUVcX0/lgPJcq4jafU7YFxusv/VhiFWWZg7XZMecs5VkOjMds7nGzW8rKYF7MGo0ZFkczYAj+XRG8/oZ/60YzAMZn/52cOctpNsLceG1OK3xLOa+t6+6aTHHJgDVgNi7hl9rK8mF8hjeZn0s1XQRrw6ye66J0mnHBhntxLfHzoNyFOfMaW/R8Gs0xWF1mPstiacZFwPgdfZv67CzlLsyU2ZpW1em7bzyM31HsmlW9KC7auhHbmnxOvQBmzutotH2GslRtL9M+C31NOQ+zZnb83lfFFE+YDbMed8bMo3qAWTKLmPakXFmlZn+utIhWZvGRYcx+sD1TjXIJZsEsMGLdtzTHYK7Mfpp97xjVCsyW2dAFtzsri4TZ83zZu2OlsjhtL7Zrh/9BsYY5McuYcH879RBYQx4XB7PBFDOYObM/nsyqSjkIc2H24ju3jtR3hxrOjnYR9el9jjAnvs9e/seV+WrWs+PlWOqfMH6+E72nRFFcYNV5f6nRm+ZmFMyK2c8LT5RQfsJ4rfS94Ui9J30o/bwDhh7S+STVXxmsLVtXPPZwqTK3YfgZNLNbNxO6KPOAmfJ51HMg7dMLxs9gmrR5NdWt9sy1/XefoJjB7Pj7Er7YSLmk3oe/J9wb9p//XVkYbNHfFuTnp1kZLPhvM/L7VLOAkCr07z3vB+vfonY6xQxmrK2jPIPN+d9edPP8GLX5HvOD+Vb9/xYz4n/vg3XVLFawOMHiBUuEOf7v7KEw56+aTqazMxsOG3vOPFtZHuzD/8XFiD8Tv1xC6exZPvgnN29mnTULYOarWSizsZrNYBauWRyzSKOeY97Zk8fJzGYYTYri69KYTTN4Zp8hWcyijKoZvC+fWbTButHdS5hNNuoVwtY=
*/