#ifndef BOOST_METAPARSE_V1_CHANGE_ERROR_MESSAGE_HPP
#define BOOST_METAPARSE_V1_CHANGE_ERROR_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/reject.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Msg>
      struct change_error_message
      {
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            reject<Msg, Pos>,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef change_error_message type;
      };
    }
  }
}

#endif


/* change_error_message.hpp
B9LtgQx4INs9kKyn9nKmw6CZ9nBd7IF81AO53gP5Xx7IPR7IDz2QpzyQ//ZAXvdADp1jQo7xQDZ5IEMeSMED+ZAHcr0H8jUP5CEP5KceyLMeyEseyFwZ7B1IiweyUUDmSUifh+bdHkjBA7lGQJYChBdvFJBFErJfQJok5DEBWSAhzwvIQRJyiHC5hRJyqoAcQhDLykzssiu7OAzb0xJPtDmeg146n6lvMlrO0JcbBP72x/78oXnSl5P1Cg1T32s=
*/