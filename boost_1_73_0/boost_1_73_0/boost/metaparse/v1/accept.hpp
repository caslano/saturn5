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
Hjg1g3cKBwrzaEtSJtCu6eS6RMZETXXUBX9oLDke8aI/CBD7JktV2UZkPR3BOGxpkO+0BhkjwtFyDT97Ch1EDtZtBdMDZwrftuhK8Du23uWZ83PrimZfUnbq0vgCm9pHvkqrrV+/HkXa6pTB7WJxc82/fI/r3iCvvN9gmGEVcNvKqDLbaCFmqR8k4zz730DcCu9YXkSwDhCizCn0uF8qKZZpf8nlk4KtOkiBAVZMAbgmSD2hxggbIgdZrD1nyhx6NsXGpd/zZa+JMfr0TJ//+w9QSwMECgAAAAgALWdKUkmoQRvIAQAAaQMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjIzVVQFAAG2SCRgxVNRa9swEH4X+D8cKaFQlinO8lKjGUpXmrCtCa3Xp8Fw5Uus1ZaMdGlnRv/7JDuxB/sBe7Gt091333ffWRA6krnDlAmld8a/nrF9NbZwKVtl2bZ7wO1NxgQfbwTvk9kZO4NCufypQihyykGWKJ/BKS0RFMEeyYFDTUAGHBXmQJDrApSDF7Rqp7AAKtEiExabqvXQHYw2HdDHSYtu0jPh8fsYFvM5bD6zTzlhAtkB38H8Eu7Mi7+I5xAvk+Vl4lNuv2bs2mjyjWdfUO+pTGAZIholKaMT
*/