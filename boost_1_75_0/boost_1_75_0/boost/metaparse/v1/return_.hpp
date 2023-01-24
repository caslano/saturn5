#ifndef BOOST_METAPARSE_V1_RETURN__HPP
#define BOOST_METAPARSE_V1_RETURN__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>


#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct return_
      {
        typedef return_ type;
        
        template <class S, class Pos>
        struct apply : accept<C, S, Pos> {};
      };
    }
  }
}

#endif


/* return_.hpp
gRdWGh2tFOODC3VllBhNI1+XF8gU6UaL99iUxlei6EUVRi8rqJcJW0X2hqNkInqlN9AlKsApX0a1oStNfqTwUrXCd9PLa/HdNHWinntlBEe0iNywTFkU6sZHoD/j4XWauRvVu9mUqfVN95maAd2opG5M22K3lC2vNE+W0WqYrHUypGO8uBge478PYvwBwhc9oLMiafjIGYf+fPpzBxPg0ojX3RspSdTuHwhNo1l9lrv6vtCuuBicBnjzcLiZ7pgsXbAE457hVmf0i3EP/tk97BdHYTksavauar7UEjV9s67DK2yR5JETISBxMEr/+BpGqaaxCZzW7L2IfmIl66UvGUzzAjNdp5oeQObJNozNgM9jJm9PwHjAYf4CJCVxiL0HECdCOB2pTgfqZjEQmafGUWAego14IkydUG0qLQVj1x8UIdcBfKyCPsZrHZvoGOp3ZvOxRWDPoFtPG9bwyJVWT6jV2Q0U3J0Lm+ayLIvwnS7IMe5DML6OopuR5WwQCwgc4cNsptdWmIZB39KYylY9vMBR1MNmEAGo3Nkg/ezvr1AtZLbmyA3uKDqgWObTUbRXoU/W8uNaxdIEIMIKFMZRDDvfToQiQMCSPSKcAYsLQlwtjzaoQHJ8CqMN5txoQuKlBRwWcPDvXTa8CG82RYpAZ1IRc+tTfgM8DaJWt+4KWhCcq3fxWARRACtOdy77yqY0AToyPn+aetcO6KvF
*/