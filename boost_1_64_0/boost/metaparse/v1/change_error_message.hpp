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
+UfN8KnK+ovN8b8q6y+2wO9wXObPbYNPVtZfzOHHa+uj4Mdp6x9Uh23+5xLXtxs+Q4lP7o5PV+KTE/h4JX62Adeuf9Ce+98Z35Txs1V4I1yuf1Jh4tfxkPAsbuJPIvjvJdY/KdYf8ceEp193xl/3DgebnfLL8eHL8VUlxj/M9UviK5Txj+Q+ev0khavjY57tM7hav/J4PX618vu9jF+ijD/VxajfaOuz4XFtfTZcqx9ncfN+KBW/uwzvrpQv6BAOBintlxD+J239fny/RrY8Mv5/DN7ccTl/fiweEb4cN2d9Ld7Ycfn+uB7/vcJxmd9jf9q/SvzyaLw24N+Ni/iGPL5Aa5/j87T4g07hYLDr8v2On+q6fL/jxyvt89gB4WCr8nwejL8m1g8mvqEYfxnH1wqv3Gj3PwTPCH/xd3u0M/E5wg8MnPivA8PEF5efn1ODn1EivsSc/0B8sBJfUo/fpsx/WoHf4rq8fzt7+q9wN/5Ofh+n4lMdl9/He/FJjsvvR+gg+icdl9+Pnvi2wLqMj0wfHFbjz7L4H0Pl87O8jB+Iy/wMVWZ9P7wjXi4/w0a8WvgyPGTyW+KcX9n8DLWH0D+h5D8fhJ9eYn0IE396Cn6a8DW4mZ99Bn6y8NY9nPh+fLASv7wCP1WJX34J/6PyfMa7hoNjlP13w/sq+z8c1/rn0vhoJz+VfL6m4xc4Lu/P+/FzHZf9ZzPxsx2X/Wez8KGuy/6zbvSPKfmf5uHDlfxP8/GzlfxUC/Chjsvvw9/xwVr+px7hYHkj67L/dzT+CF5pnfqXfT4uwRcLz+Km/3cM/oDwoNqW7yo847hcfy56ZDg4QJuf4PGkxzP4wcrz9yC+r5b/CX9Y2X4b/pDjMn78Y3yBMj/tE3yeUr+u76n3X+VwrX6X92zf4Nk+OErfPoqr81Pwd0t4u4Ifjj8T0E6yzvwq+37ohT8pPLvDaZ/0Eu07kX/ldHxsif3vZsYH8IuU/QdHh4Ou2vxfvIs2foEfo41f4H21/Gu4GR8otT7sPJzr6zr3nz2/+fjbjsv8TQ/imxyX+ZsW4etdl+vz9wkHCWd8Qb6fm+F9hFO+4vulFd7Dcfn+a4cfooxvVOMHa+MbfWk/a/0/CX38LIpHFI/hUcUTuNb/U4eP0fLz4Zcr90cDrjyf3GCe/mtcnT/k2T7u2T6Bq/Frnv3XeTyJ5538XDJ/5Xh8PR52vHNn+/39M/6a8Itwc//dgK8V/jRu7r8b8dXCqw9yno/+fH+d+qlsP7bDH8ErrfP9teN/1fhi4Vnc1F/a44uEB9W2fHvjf3dcfn8TJ/B+0r6f+JNK/PzD+EOB7L+x7+8svkD4fw521ifCrxDe7hdn/BgfI3wCXmwfDAgX5m/hJdbXm4v/vUT7y5RvIT5faX99jZ8hvO0OJz/FieFgmJJf4wb8FMdl/fdmfKCyPnZwUjj4xjk/md+oLf5ywE/u+PlO+/4s/Fbh83Hz11B8svDvcHN+5+I3Oi7zT8ZraJ8r638djz+LD7BOfhf7/q/Blwrf/ot9/mrxJcL7/Wrv70H4o47L/C7pP9L/ob3/T/bUb3C1fuPZPu7xhMdrcfX96PGkx1P41yXu3ypz/+JfCp8ANjX3L77NcZm/9Xb8bcdl/Tb7p3BwpDJ+EtTS/694La59f+rwrtr3FT9Iie8YhbdV4jsy+Din/i7jO+bhYx2X8R3z8aTjsn26AL/McVn/WYhfosyPTwzy3F94b+X6ZvBdFM/i2vzzevwNZ3tZP1yBb3Zc1g9fwl91XNYPV+PrHJft43X4S67L8ZdT9OuTx7XnpwE/VVv/Dx+k9M9FTw0H3ZT3fx2+r3L90x6v93gDrpYfV8t/mqc=
*/