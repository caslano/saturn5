#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_front;

        template <char C, char... Cs>
        struct pop_front<string<C, Cs...>> : string<Cs...> {};
      }
    }
  }
}

#endif


/* pop_front.hpp
q0Q0yTrjdodKn7BAA7jhplqm0WgHrF+0/gRuAtg7wU13N6xgucXUVyMJg/ED2aMmgKvuKpKQuDVqYZj8CJlaXFKbqbsz7SUknpVjuwKU3fjZKnBjfdQ1yvpN3sLKACmVcRxEBUBZ5iC9+RJ63MqxhG9S3FdhgbRPbgdR1MLmuKYopEUW0Dq1jqhORjPFnrEPOYF4ojVc3QpdcpqyRFnxtXiPLWoiVicxAyJ0Zh7EQ55fU+IESkRFmToh7m4EEkp75T53VXtva0H+7FsA4/bbLaMiQHqwqBusz9qRhSOMGA7wJGZsQIk7Bb3iNhVINlbWgiO9GTh1XigdYYZUAG0mvcZpLPaxdYxW2DjgdqqAx40QDnLPOyad/4vAdYF3rbaJ0PLF2Gq6nNy0IohLR98Jfy3rVyugvo7aZrxdwDhybobn6QDT8yLWPoX9vbqzcV01zM7g06MXkZrffG1RK8R3TtKJdPbwC/F541Dc7HCH/CUX1nw5K6iF9XwfLuclayCP3fqJyF7/7RX5yoFebfycT7+z89dOCrTPdCq6B0pJ9Qal1c1vElfQC2LBkw==
*/