#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/sequence_impl.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        #ifdef BOOST_METAPARSE_SEQUENCE_CASE
        #  error BOOST_METAPARSE_SEQUENCE_CASE already defined
        #endif
        #define BOOST_METAPARSE_SEQUENCE_CASE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, class P)> \
          struct BOOST_PP_CAT(sequence, n) \
          { \
            typedef BOOST_PP_CAT(sequence, n) type; \
            \
            template <class S, class Pos> \
            struct apply : \
              sequence_impl< \
                boost::mpl::vector<BOOST_PP_ENUM_PARAMS(n, P)>, \
                S, \
                Pos \
              > \
            {}; \
          };
        
        BOOST_PP_REPEAT_FROM_TO(
          1,
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          BOOST_METAPARSE_SEQUENCE_CASE,
          ~
        )
        
        #undef BOOST_METAPARSE_SEQUENCE_CASE
      } 
    }
  }
}

#endif


/* sequence.hpp
8tEe8mzc055nUuCv9iJ9cRz2Z8EjnGVMTCx8Or75KpB5CAVC9h3wBYYhe+z9KczsSxIhowBUN42n7fqPP4S2+5ddrjYgiaStIK00gegoz4o6gG9YXQ79EJ3r/uqT9qtV0kEz15oEN9pOUeJXNQhvTVXL1RORmQpql+0zS+wzewTvVrtcSwLzBxdOK/0jv2zXKLP/Ab9zbICKh5x6DZMpcIHTccFVnVIvFqPA7otu6gJTGF68kg1rS2Hc2cp1Gm6QBQG3+DQHzpiC2ngw76xSnvS4Tiu45R/BwOz4909kuo0guCrQh8NqL8B1LptoeOicWpvbWfMjJPMSnVB6AvLt538fO4VLfTgC9k47oSXjyZSAj4U4NEMXiWqLM2bPwOxktQbNdALN/cipIPm4hjA7A1aWMk76rZkaWwptmsWkd/mnziX92FCgHYO6vADglPzFteD98eu2UIDEExyKxi5Ixk6ywoJ577ZS3a2jY9Fy3H1MOA2IwH9N6dJezuZht1+Ru0ktpU0EcUbQTf1fOqeHPY5JzgWp1wF2hutuBzfn9Na9GhpcNt6kusjuvw==
*/