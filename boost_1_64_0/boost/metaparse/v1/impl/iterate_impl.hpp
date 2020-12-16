#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl_unchecked.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl
        {
          typedef iterate_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<typename P::template apply<S, Pos> >::type,
              typename P::template apply<S, Pos>,
              iterate_impl_unchecked<N, P, Accum, S, Pos>
            >
          {};
        };
        
        template <class P, class Accum>
        struct iterate_impl<0, P, Accum> : return_<Accum> {};
      }
    }
  }
}

#endif


/* iterate_impl.hpp
X7dreel/TQY7YRVmIaMM3vfXcsjf1Aav87w+WDq9n/bVdDZwXOQ/vNep3zuTtOLP6/lweKwXeX30X6zv43+hN8G6v4/3sB2fYBv2I18Zz4RQDG3RFxnbONj7Tgi2s6PXAZD2a5vvKRNq99wyobbeWybU3ueLRgTW93EO9lzUn7enzH+m+3/Z9wOL6f90/Uwfhwy6usy9+mQYg22DopzZjAiM2mU/fFXz1nuBQLNm5mf+1s9sxI18iTXk6kgednYov7k7f8oBmNfOsW0dnCviyxS/zfy2hj/Alx7Ahzzxo7/5zfums/t82j7mjXId+SNNIgJD6XBLpLf/f9P2+/6B/dv0kvskW/uk649+SO/7R/Hrb6P/i3VRj7/b/0O9rlamcfB76eljsULaNnT4F8Zlrf3+31qDvFXaGOj/uFvM/wX42Nt9x8Jp3015ke9Y1pzs4ftgOt/nEeeg7Etf78xFBN8xybpuQwFjaw59yTnPO5ua8/gmmws7Y2a9MJNPeZ7+T+P79ltnvg/OSa35CLWsxa5xNsc59GNJ/7gfPk3z3TpZov5qLN/XlvfwAT4v87/p10/LpPetfjWWf+rb9HHv8xd9ujuofzhaJr1f8/BHF01x/oUveLx94Nfn35F5Q8+/s8YEn/9aC3nN7/n3T/mCz4/5HvmtZZYpp4C2bNaWgj4/qK2FpAesZwqHnn+/WMR7fb2pqDmlH5/zaunTrTGD9zYvjCkeuHI+r1cJ6Qf5nSWv3N33wLjOOqdhKfmsceO1oWw/ayx1D9CjsmW98vucB/L8nF553ez59zvllROI+pvr/3WR7uV1Ej7ZHR248E3WwMYiobzPoE1nOjGJPHTJwc/Up0ggF3F09+CuzIHZmfWrdjbiY49Z6Zm/9yfvIi/a2KEync/tWfgQ46Ath6Xl935jXvm9FtPuPE08or/GtVmVo55nstMLr/WKyi+tZ7L95ijbQT+6Jkt+1/ZVhmftW3PI697nlsjXwbX6LyFGufp/hryD9NdsFNMPa4zRhngy3d71OdXLa5s8/k5Tz6yhtJnZtK9RSE6q9lEncZBald1XmXlcuyPoA1TRxfINk5Z8t/Go5nptTwr/vkRSXX2ujK3akFbYOOQJvdaKU546fJvLa6S6XRVqf/L1gcCUKPkrqlMR9aVfLzd2f+l5CoX6ZEY2ed0v4Jozrdyvk/vGuCZC32BBBZ91UbeSrrna5yWU6+/oaO+xJkq9vBZGmv7blVO/5TDe2bXJPSrmck+vG4P9XSv0XSj549VRuUtyu156clC2yqljLp8rJyGLuhSWx2uKsbqQFLpX2eA4q+cE1yzIrD2oKH2YOsTnDZWXJXtQTOlIJn8XJCtR6hIwjqW8KmuK/MUa6jP13OX15TRy5boNTeX12QTXvV9UmrZWlWdYFnWKVYeSyqvgOv2YEEzT35uDMphDXWNcV0z7ycbxwWQ7WAcsQb3S2ljbfdW5bBuyWtz1mfTNcPg7Ol4/Vwz91mdPbW7k72Fd5b1K+dX1u/VBoJQ8WUJ9MKWbv5UXiNF+19dSVv5gfTKHfrciITuC+pFZnWuQifrKKKUOedzbOKSV81kO99K25KBeRclf1KvrBmUOjWtsvtBritcdJeXLrV2FXRMl7WqfVw/tw1omv/E3Du4l7wT1mVlEXXIZ73quLeF1gDoX0J+l9LX61coufw7t9ZrWxmfqPgZpRcmi6xbKu0G+qoW8wjV0J5TWNLe+zRZiWLRyCruW7CR1vKK7ZEe+Jq7RtgmlENSbvKG8xZQdny0oQz53v5uyhto3IU57irt3sdCYBujEyRjtcs1qLJvgep+fc6/pWUJ7cZ8prayCkP5mCW0LtiuL/EnGPJc=
*/