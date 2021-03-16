#ifndef BOOST_METAPARSE_V1_ACCEPT_TAG_HPP
#define BOOST_METAPARSE_V1_ACCEPT_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>
#include <boost/metaparse/v1/fwd/get_result.hpp>


namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct accept_tag { typedef accept_tag type; };

      template <>
      struct get_position_impl<accept_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };

      template <>
      struct get_remaining_impl<accept_tag>
      {
        template <class A>
        struct apply : A::remaining {};
      };

      template <>
      struct get_result_impl<accept_tag>
      {
        template <class A>
        struct apply { typedef typename A::result type; };
      };
    }
  }
}

#endif


/* accept_tag.hpp
sJ3wGaFSVsLyjH8Btp6dK2EQ1mmLuZ69V8Jw+oxR6TIJuwo+e6l0rYRhqtFPpRsl7GaGcRlLt0nYHYx/u7geJ2sB+y58xqn0sITBFMwGqPQzCXsKPhNUelbCnoPPJJVekLBX4HOQSjgUHDYPSu+k0iEStgRKQ1RaIWHHQmmYSidL2GoobaRSB5RGqPQOKH2USr1Q+jiV8NvqG6j0TihtotIOyXEWlDZTaUzCpqD0SSrtg9KnqfReKeUDdfxrlvU=
*/