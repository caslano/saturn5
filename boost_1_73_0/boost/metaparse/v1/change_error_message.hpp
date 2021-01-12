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
73AYK3I4j+IIVuflPJkjeRpHsT1HcxvHiWnB9B8Mpl9GjBRelpHpx+43a8WWbM1zeSq7sw378TRmsi2vZDtexzM4kR14K8/k3ezE6TyH23ibyPtNi7uC8pQV44PydA3Kcx4b83y24gXsyAvZjakcz4s4iX04hWl8kOl8nP34PPtzHS/hRmZwMwfzS2ZyGyceGf5+lf97VgrfcNHlWHmvvPvIjuAMVuMsfmLk+7mTc/gT57KE
*/