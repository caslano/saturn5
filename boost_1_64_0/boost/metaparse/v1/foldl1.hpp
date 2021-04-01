#ifndef BOOST_METAPARSE_V1_FOLDL1_HPP
#define BOOST_METAPARSE_V1_FOLDL1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl1
      {
        typedef foldl1 type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldl<P, State, ForwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldl1.hpp
ZOELKgzr4D0vdB9wja5WosKeK73DL9LPRoXDHtzDAQp2jSH383pQHwqC0qEI6YpgxASEtUdgxWi7jsINQCzMmXQQ8yK//IA5gJnzdx9johCzungl9l4t4IkDWf+849o3P7pCpwUTFG8zUCzpYvCDtPcdoJX9YJGt0Jz607PskmEFopo25Lle14nc0grVbdvzx7SqGPHTfYiSl1myNsBsRDQc17AtV5sdLMfyiGuwD7xK4LgXSSlPGTRD1en5SFRIazxx5jc8k1FuRSwLv/cJEo1lAp6bgiiB6tIzvAXNeU9fhtqEFWfuyIpdeO8M3T6JzMhozVX5MPIU8yaoIn6kJASjsBwaMyQ7DowLazk27Mun6jD64QqDBvTh+0bir50iT/mku/qRwvtjR2FWbFcJd3/stM3pEyjBIdZNAj4a6dysx0jKgNEYRLrOkP7CK/KznUk42JcD/UChygRmV5+o4byiIPcmyqUe833coix0ADqXonDQPqQM9LULgs4y0O4j8pvpCKlHoB9UDrsCqWj0Ul9/F29FnxcgHJGdv4+OMlLRoG4IZPAsf5bbYw==
*/