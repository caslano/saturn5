#ifndef BOOST_METAPARSE_V1_TRANSFORM_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/unless_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class T>
      struct transform
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename T::template apply<
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type,
            get_remaining<typename P::template apply<S, Pos> >,
            get_position<typename P::template apply<S, Pos> >
          >
        {};
      public:
        typedef transform type;
        
        template <class S, class Pos>
        struct apply :
          unless_error<typename P::template apply<S, Pos>, no_error<S, Pos> >
        {};
      };
    }
  }
}

#endif


/* transform.hpp
VpkZ3LzVlo+yny5x9vckszy5l+nJ25wGsQ75rAb0sjmpoARfR7VBmWtJbCs8xOgz7Dj5wdvKys2KEU8jxIFwcZRe/EmjSPHbMBVdo/cJ8xFTOdQBGtDlv+i5EtlCFyQ2Q/n42X2yz5C8X0AUyund2BEo43ONwqmlkwKYhhWQLG/wBXI1TsGRInupnI4yHVa2+jX2BaCNKpLb1+kXl/5DtGsKIBZU7LS9VMOx9wdigc8JmEh4aNuFYRWs63tt3LI0h31j8am9TE+8o3YlEeIiuwAyJkSKa5nV/2eUA9YAzlpSNcZ+PhLcac1Y+gTjdIFZxuIwKJW59XxrbFIMUimEyDYzBMKEn+M/w71uXKONiH0QrwusgACdKbhgHaFy5j8o4L9rdEuxGpFDZT9s6hhL86Hqx6n/XDz9j6L5FTRYCJd5brcLyztw/vmzRU7G4jFIL/m9onIaYw2nWmn7sAA0+6h+yZkOU7OYRcUMoSzHuaxVn1PdwN9fsdczoMIrc7T+8Kwn3gWiPRRWCmcK4k2JCfZ6YwoeKVHmK8hhvgMrc9pWFBzOmdqa3x4G7A==
*/