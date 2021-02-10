#ifndef BOOST_METAPARSE_V1_ENTIRE_INPUT_HPP
#define BOOST_METAPARSE_V1_ENTIRE_INPUT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/empty.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Msg = error::end_of_input_expected>
      struct entire_input :
        first_of<P, change_error_message<empty<void>, Msg> >
      {};

      template <class P>
      struct entire_input<P, error::end_of_input_expected> :
        first_of<P, empty<void> >
      {};
    }
  }
}

#endif


/* entire_input.hpp
4iTloyf/+f1xOPpoPfiH0p665VHzWzUKe3/k+w1NtTtCIZ0EuXNowJUI58FBKS1kiAo8W2pHJQ4d9zwNH8ZjmG6SaLalbbuYRPM4WUxSJtAYbXJd0AN86vQnFfyqF/z+Mb9QSwMECgAAAAgALWdKUtritHS+AQAAewUAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjM1VVQFAAG2SCRg3VTBattAEL0v6B8GF19C1JVU0oNYBCGkdWioja3kGmRpbC2VdlXtKkEY/3tmZTku5BJCemhBjLTSzHvz3mhXWDQ2zwwmTEi10XT7hf2TbguTsFmaLoYA369Ttq30ei3Vlu32UEljmeCnVMEP1Z9ghe0jtr6RBTLRYlP19LXIbBYeAHn4OYQoCGD+w2PfOqV6v8SsiKFHQ5fHrrSyqKx/i2pryxjCC495zJYIqqvX2IJWhMxHyAE6ei/01wH6SYM0oGSOYLUesSMnauyfZF1V0lUeZOXDghLMIDZhpbUNpR+XIFRWk6V1V1nZVAgt/u7IaAOdIQdhtycPpQIn6m55S/n8UAAi13WdqSJhk+lsvkpvFvHUSVvMlynfhdGXi3MX9rsgCMJzCtF+QsQvVfQ49kY932MrNz04NZBtLFnnCN3EocwM
*/