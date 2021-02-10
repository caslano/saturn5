#ifndef BOOST_METAPARSE_V1_RETURN__HPP
#define BOOST_METAPARSE_V1_RETURN__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>


#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct return_
      {
        typedef return_ type;
        
        template <class S, class Pos>
        struct apply : accept<C, S, Pos> {};
      };
    }
  }
}

#endif


/* return_.hpp
L3Rlc3QxMjkxVVQFAAG2SCRgXVLBatwwEL3rKwankARie91bGq0h9BLIJdBt6SEQVGu8FpElI80ma0r/vSPZyYboYHvGb57mvRlJGKlTEVtxBrvBREgJSBngYApmVMHYGUZUjoA8vGAw/Qw0KIJJhWjcHpTToLROnzQgNJvNPdP1xmJMLAriq+kJ/IRBkfGuEtK43rdCPuP86oOOrbjb7R7yAx5+7oSsT39kvYDFGZP+wMAdlNFoFDLgZGcGaEUq4d7ea57h361BRyu8ywEDYiZphfOO0/VbKJ0a2YhbIhynLPYwWa90ErRZ5fw5EPTKWDDjiNooQjszxVIpOz+ObEYrynuwfl93o26+XjdQlqmmRBUy+h0mEymk4m2R8Mt9JfEgilb8Xs6RKxIujWiPLnmI2efOu97sc2NCTgG7AbvnVrDLFkqE896HiwaqKvd/CX/TOB31F8V6TSrcfrr20R2C3Q6UzvStrtmiEo8mEg+3HHykalDHYxVxLaqTvkdXXMGXp8ubf+fQfhR+w62fGmPh6wRYya9lj9LIQPWEIUvK2zco9hnRQREHT4WQy84xAYbgQ+c1e9Ew3YdQ1u+g+rTT/wFQSwMECgAAAAgALWdKUhzvyjCNAQAAhgIAAB8ACQBjdXJsLW1hc3Rl
*/