#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_EMPTY_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ignore = int>
        struct empty_string
        {
          typedef empty_string type;

          static const char value[1];
        };

        template <class Ignore>
        const char empty_string<Ignore>::value[1] = {0};
      }
    }
  }
}

#endif


/* empty_string.hpp
1PwvjnqNmRb2P1xj/goDKFxqCfhx4QSqiu3czugjr28xoupHgImPGrZK1WwLVI2mCeiqBzPjxxbxnwXlyBPGXW5hhIyr3apiNGtCR3oO2Yv0Ssk5a1jmr678Z0mjyvJb8pFZoqQP4myJW7sBFqdUqZ6yTfIwmUrjilm8FdJPbBLAY5k/BTjdPAjQ5N2FtagZ3qMIAcudidrKpR8Hy5AtayejGabIe41M3eg3pViQN34w7yCvpTKmZkAF5+SJgiL+RPPeH7TfPWlQ8Vy9NqlQ5ggpQoNZonJ/qbvAsUmCyx62llTVPZPgBv8Dax4zjwkCwZOwaZu7XgZ3bqZ8USuS/SU+8oJiGDp58OevcYDuV6SFQ7uWwcB5ptBnsFHJfGwVp/Bc2BSRyuRH1b4nJLblfoMRa8yN7k/YRI5URodRcFSS6I0EziqpKqpMj1fplBMntUz13juRwzvslOx/MYUXrhCakXD85TSut5sKkbi+DgpPESc67iRMG8xBO8Rw+o/qmit+1BqhYcXyBdwx+aerp6dxE1p3jSn8cuxN1bqVa8wwd5oG1pbCS54DeQ==
*/