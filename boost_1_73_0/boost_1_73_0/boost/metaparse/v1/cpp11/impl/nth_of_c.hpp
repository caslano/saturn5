#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c_skip_remaining.hpp>

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class S, class Pos, class... Ps>
        struct nth_of_c;

        template <int N, class S, class Pos, class P, class... Ps>
        struct nth_of_c<N, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c<
              N - 1,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};

        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };

        template <class P, class S, class Pos, class... Ps>
        struct nth_of_c<0, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_skip_remaining<
              typename get_result<NextResult>::type,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};

        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };
      }
    }
  }
}

#endif


/* nth_of_c.hpp
AJbxFnM5cgAQI4N5RURNIBaFJUcF9SLWps6CSYWl3Ewusy7z6Nn5Nt2h7FwpyHJtdKiTLqMBhsdWLmaxxi5tiD48cb7Gvtgh8N6MrTw7T2We8M3bd4Obq97nGnsThpjZ8jbfrj2ZxFa7tSwOrfE+pGViZCZyw2lsPDriKdzpUkUin3e8Z542jk6i4/3GUev4oMZq7DnsOnqh4VwWdlKluxkrAlxS9K5T62qq/gUDZV3/tSWpnGH0m3aIlYc0/1SAMEaEcWrrp9XcOhWPpnFdjcGZ4VkipKKuK5P6F/x4gZxHN/W/UPRig1YT87w/G2HCB3x5jwP+cO/58s/tO1BLAwQKAAAACAAtZ0pSnlkxwrkCAAAmBgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMTZVVAUAAbZIJGClVdtum0AQfV+Jfxg5ivpSjLHjJLYoapS4Sqr6UpvcHjcwGBRg0bLY5u87i22cVmkaNSuEl905c85e5thRWCifF+gyJ85CQT/PWK2FDAqXffNmbHaxuGM/bhYeu/boU7/gcjqZjC63I5BLsamYYx1gjrXNdMSOYIFyhdIs4gCZIzFPKpcxxxdZhr5y6wyW3bah2+nAOF5GqoIwzhDiLEAMDDbmy9gfQlFK
*/