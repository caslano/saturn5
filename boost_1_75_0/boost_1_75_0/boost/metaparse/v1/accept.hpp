#ifndef BOOST_METAPARSE_V1_ACCEPT_HPP
#define BOOST_METAPARSE_V1_ACCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/accept.hpp>
#include <boost/metaparse/v1/accept_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result, class Remaining, class Pos>
      struct accept
      {
        typedef accept_tag tag;

        typedef
          accept<Result, typename Remaining::type, typename Pos::type>
          type;

        typedef Result result;
        typedef Remaining remaining;
        typedef Pos source_position;
      };
    }
  }
}

#endif


/* accept.hpp
mhNTJziDO8xYRQX+yYJqXQVYNaghDhL7oEDoCvZ/tQfqZriqwa9/NkQt79Bx2WrOZadWCy7rlYqqGavCJ2M1z1sVx5vlTX2V/V9Lg9eywb9z8MG16qO1Igij1qRrH1DrDgVepZCX2NVHx8WZRIfHfO8FU+voHRCYcLf2DviCXsL51gZuo1c4+aS7OmnW9pKfmDAYae+VptZRo0CIS8IaMdeaiawXMsWMQfED2IDZbY8gNHm0JxbY9qgdN/daeZgPXZE9aoYkJJJD7X+oyAWcwIq0yNXA6/P6ZF5DMnc+kn75kAOuJzdtw1jIvmm+8BXO55sNOhrkeABfeCahNbq6xmUYkcLzNsO5ZVrzFuqxiP2KeIayr8yYoPzApYxui9F1zkrFMeUSLUZLhBqNukQNNdJNmyHj/pMIuXrsowR4ONkIX4aucQK28GoormvChGGE7XJkshj9CldQaybYFrEr661EGHGvAoCpApvLJAB8TAC4lABcetZpAFwqAFwqjI+UxS4qDOEDxs7PDWYDgCs1AFP7FwOAK40ATr7EUM3BLYJ9Fcepv1nFR/tM/NyPdM7UFMAnCHxCtoyM95V87/dCDnG++Ppl9PVv92nm6xmJ8i0TX79MoJeEDTTZx+FCwahtIfsTMz+TSnnDSl1+NySBtlYxhs3sVHRPrtzV9UNPYOekBKFAJ+jMvwUGzduYLQ6Joq2h+aOj7mLkKknA
*/