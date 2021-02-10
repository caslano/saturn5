#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_EMPTY_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ignore = int>
        struct empty_string
        {
          typedef empty_string type;

          static const char value[1];
        };

        template <class Ignore>
        const char empty_string<Ignore>::value[1] = {0};
      }
    }
  }
}

#endif


/* empty_string.hpp
gqpF6wqCtPs4heQgVo0d2Q4d/35nBwrS9gv2JbHv5bnnnrskdmhdnllMWCzUWtPrHfcf2hQ2YU9pOg8PeHxIWcxPnpg3weyCxQYruSdTkbkMlM5LzN9H7T3adoPAB1cDGPb7MPveYpPMYQRpjV3o38KL3pFn0IfBTXRzG1HM44+0xZZodmgi8Nx6Nlz4OnvHFhtr5VC53jOqjSsj+BpMCnMntIogl9qeRaX7Cj3Kb8dLt5Unx0TYSlvRJK2FRJVtceQfg+vrb3eQl5mx6EbrWqn9HejKR46sM5naEH6LDYbXN19IBd+zV+OgAclxAWMpfA0rCmRxHi4JmV0pLBikuwWt6IpQ4KrewBozVxsEpyGTUn9Abf2Z6kMhDLWmzT4Y6IA+j8B6M9C1q2oHQnUpQahNQBy/Lp5/pQ/LdDJdwC4zIltJYnEoQYMLJYnwyRI3AiesdK4iz/EaezmSz/HDh3Clr5upAv6hYxd6E6JYEC0CaXIJmsJ2CTunNerMf0641JtQq/HHud5uPfBB6bbSvaa/Lp2EymVdYLuhGHHeeZot0+k86nhy89ki5X5snhxx6BHuAY6AiZ4LG5mwCo2EznIxJhJcipXfLq40rYewzl5VEogUPy4BoZzlEuRhkGHEb2jEeg9h47O1QxPE
*/