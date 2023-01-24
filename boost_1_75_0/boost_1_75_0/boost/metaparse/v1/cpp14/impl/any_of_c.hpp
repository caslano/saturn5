#ifndef BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct any_of_c
        {
          typedef any_of_c type;

          static constexpr bool run(char c_)
          {
            const bool values[] = {(c_ == Cs)...};
            for (const bool* i = values; i != values + sizeof...(Cs); ++i)
            {
              if (*i)
              {
                return true;
              }
            }
            return false;
          }

          template <class Chr>
          struct apply : boost::mpl::bool_<any_of_c::run(Chr::type::value)> {};
        };

        template <>
        struct any_of_c<>
        {
          typedef any_of_c type;

          template <class>
          struct apply : boost::mpl::false_ {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
UD0rnJpiRApv154/Ip47M7+9SPkZ+BpEBso6Wi0RNnhIWg5EmpyRY/3m7n2LT8j3dNfDmQy0ZTwEzP+4jKCGY2WoUTom2QaNhj53IMjWmx2fY3T8Wg2cS3eFnzOjdj3kvIyFp0PnBpVxfnj4brF75p8Xf4pSwYzjZ7Xr4YG2cnQIzd+kXWbutcvIXDzktxjmAwOZxWitGQ+bZhS8QM7I3Xxrlqeybw3IgU8u54SVf5hg6I08FOFWBEKaFlS+AvluD1lho0U5IDVmwb880uafT7Za2vPlhRMmsZR/fGvT38jadCTB2rRNO7W9U1ibpkjyccT8Y5uEmB9ia1NczO9PAi+K+XNdvLmmsIRP9jG10ola3Hxv/YWUKozKAP4f1t4EvqlqeRxPmqYNXbgFGikCWqRosaiVgravIAkk9AYSqUKlT0WrSMEdIQGUrZhWGi9RXHB5brg9fU997raUh7YUurAWfEIRxQIutwSwIJYWlPufmXPuzdLC431/fz4fmrueOzNnzpyZOXNmyCqjhODWsFXZfwjM0G93DG4PGETpJK2L3kKeAJt/bBHNS+8nst2bPnsS+hQuw1uWKLr1VPitBLn6SZTHrUfJlrXDPP0NuXiOJfCc29WeOPlleKZ1Lc2Ju+ju5J7YSge0koLY7FOvZ/SkfBkenX+8HnMlfUleBjLm0Ud1ORoQQH/VSUVSnnlS5vVkTqpMeeZBMC1B
*/