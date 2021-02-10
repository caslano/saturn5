#ifndef BOOST_METAPARSE_V1_ALPHANUM_HPP
#define BOOST_METAPARSE_V1_ALPHANUM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef one_of<letter, digit> alphanum;
    }
  }
}

#endif


/* alphanum.hpp
mdRUvniPgyXoxjTH2uys5xYUO0dP+K3rtsI7bsuv67knZus5yFNga54IonjlieQjCiD0RBx+BuCsev1+h/Q3xyU805n8N+ntPUw8nvLqUsmLdXn9xX4AUEsDBAoAAAAIAC1nSlKi9G6kYAEAAC0CAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTIyNlVUBQABtkgkYE1SwU7DMAy9R+o/WKAdRwQHDlNUQKyInShrtwluoXVptLaeErPRv8ftBiOH2I7t957lGMbAhQ0YK+O6isRssT+QL0OsnvJUpQ/ZWi2TfKmMPmeMPhZfQoZ+j34aXInKeNw1vWRLyzZWw61ADtNoAAKi4toyDMgCtQ2SCAQlYQDHd4J7bDX6BCUMj43Djk8MxRhIQRh5Y1XxTqp/IzCdbXFUDhVyUYOFyjUIlacWuEbwRAyl81gw+R4OjmsIrvtssDiU0q+PAGAKalvblSPDTOvJ80uWL9LZRKDTl2Wu9fXNzS1Mp5Ketsg1lf9wjP5rH/yTaBlmjd5VPQxTgq0Y/ShqWALUNsAHYgcXoSa+UGY/1sqsO09MBTWxWmXJEmxHXd/SV4iG7WQgCu7x27a7Bq+EVl4380g9buagI5Wk2TpS+VuawCJS2eI9gUF4NO70
*/