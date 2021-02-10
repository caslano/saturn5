#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>
#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/fail_at_first_char_expected.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete :
        foldr_start_with_parser<
          P,
          first_of<return_<State>, fail_at_first_char_expected<P> >,
          BackwardOp
        >
      {};
    }
  }
}

#endif


/* foldr_reject_incomplete.hpp
yTKBRJ6U1+nMKhn5Uwq+igv++MQfUEsDBAoAAAAIAC1nSlIobX0R1QEAAP0CAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI0OFVUBQABtkgkYGVSXW/bMAx8F+D/QHTIS1FPSZEBq+AFy7qgCdY5WeN1Rd9Um4612pJhyWncX1/6o8mAvVgmdeQdjwocWhdLizMWKJ0aOp6xeTFVYmdsGUWb7gNlZQ4N06Y/A37CBLwvYx9gi9UeK9+qBFlQYZk3dJ1IJ/tOfPJxApfjMax/sO/SoYCoxgsYX0Fo9nQxGcNkKqZXgiA3PyPWtxPQKvRtF/BUPiO7Ntqhdv4t6p3LBEyPmagpsS04OJ65ImcsNYYU9hoCPmgiqde5avG91LgLCNCTzFjmXEnw9zDQsiB/5nGM1oIEbbTfGqEwgcxYBy/KZVBbpXfgMoTYFE9KS6eMBpOC34EbMGWXkTqh1GDlkCSyniOg2oIQvQbBeU0ihMW4Qvd1tFxvo9VGjFo3N+u7iE8up5+P/YeKpC6KRozC9e1qGy3CDvcP4dCEMoU8+E4VCJ+I/shLv4MdZNM9ViptoPUPZOqw6uZrFwKZtPCEqOHMZsadsWDfYakB8TgTm3zGbhYR9Brf9++xJRkm4L9RPDav
*/