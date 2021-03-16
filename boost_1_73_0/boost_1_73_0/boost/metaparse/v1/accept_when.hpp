#ifndef BOOST_METAPARSE_V1_ACCEPT_WHEN_HPP
#define BOOST_METAPARSE_V1_ACCEPT_WHEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Pred, class Msg>
      struct accept_when
      {
      private:
        struct unchecked
        {
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename Pred::template apply<
                typename get_result<typename P::template apply<S, Pos> >::type
              >::type,
              typename P::template apply<S, Pos>,
              reject<Msg, Pos>
            >
          {};
        };
      public:
        typedef accept_when type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            unchecked
          >::type::template apply<
            S,
            Pos
          >
        {};
      };
    }
  }
}

#endif


/* accept_when.hpp
7GoofYFKH5fYT0HpNCp9UcrDjfp3UOnfJezrUDqdSndL2H1Q+hcqPSRhj0BpG5V+DKUzqfQzKG2n0tNQejeVflvHEwHQfR1fXLlJClraJiNY43fL0UNegevrHRLs/dLeLGIzBubtdS4YZWNgRq64gK9gPDlphiuUMTmqnsxoPqti9VCuhuAKCWQVrWkNXLG37XCdYNS3Ksze6HFVSGxQ29UPM7KAKo4QjGv1K4zGsgqJKI5B9X5Geq8+ykjX1V8=
*/