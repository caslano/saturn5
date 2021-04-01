#ifndef BOOST_METAPARSE_V1_NEXT_LINE_HPP
#define BOOST_METAPARSE_V1_NEXT_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_line.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_line :
        next_line_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_line.hpp
XlokqDDwi/dujJDHQ+cNf3Ezs+u5R0MxI69E9xV3bnzbX5qnQqNBh/U0j4MkA1CYJbqwmUSihzeTTTfd2/WTH9qFb9kcQE7grNc4ry7b8pWD6UiF0G2578/Fd8f17dEF++5iV3YWBaf9z6UA3B5DQhVjNkYaaen2jPvG9kSw+Ydndiq/x5AvpP+7A17GIw39y4TrZe4yIVeGs2wOkQCWQ0z1aVAmNaqMIrHNthlgX5HKhg5GuiIa9UTXHRrOhZgVhvREg30NyK9ZvoIz/7j1XMRFTMLrXcqrmZ+vqpYEfXyRwUlQrlSbAqDOL1jIrIhR1ieaxRM8Mj8P3ptGNYJBX9e3AX2DBLI2qWEvfscqGZbgLvUvB/q3S5W5gGvxQdGh9VyOv+OSFR2RoxyG0hWgAdOBZpqUtE7S6rQ7dGRANU8gH5FmChwnZgwQQ47PetEHF+2rkDIYjQPm6DV9Ybz61IdMKO1Av91qukTxzffR5BOgVXBadDweiR55dEVkcaVgq6iP4tLRnieGxgnxp9N7FX9OWWyLbz+kjPb73D/llGy3ONHSA+vNgGOTZA==
*/