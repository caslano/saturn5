#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/apply_parser.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/deque.hpp>
#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ps, class S, class Pos>
        struct sequence_impl :
          boost::mpl::fold<
            Ps,
            accept<boost::mpl::deque<>, S, Pos>,
            apply_parser
          >
        {};
      }
    }
  }
}

#endif


/* sequence_impl.hpp
B79eKyjbHF1hNKcsJQBuiYes9sGixlVFVj5HnB+arQk8Zlbx7Srdi7eivPjtYIj1Oe/e+rOXZUtSVlmMhV67qYyo36JnK0uk7t5gnzegLiGBcQ4RrLmiB3FebbpSFqMZv0j9deDEkxdwHwKIdwPygw3X2fB3+xqJCrLjDdWfxQhvJxiJLVL41/yydXrLQK5W+9xRWkW2wu9HDrCd4I7q0uYSM5s8k8qDCziFImlVOyH28ZXhbzMA4h/2mySOmGal6pjU/Tdg2woHE2AOaZpEjcwEz0lCgRGkTgVJ0YFT4EH9CXENBgJqGaYbAkzbtRdkNS1oHqVAcOvwOVlhFYMqDIbX/ltQ56kmLYHYfFG/ZTLPlzdHAkLlFF7fMdoKvafTf4NwJf7qzu+kiyi5DYIfMkZslkKN5j0yUN4Q/v0AMB4j0UZK58VBDqnqP3h9jUZJtrHaJcC2rKaoVLGnQgQM2WItezI6WKYWJyYLZLG8Wtz3ty0ADQ5retKJZ1FRVqPZQ4I3ZfjBVca9L4BUci0LDkzL1voqVzkP+UO5biXGTFei1HwhTO52dgUJqw==
*/