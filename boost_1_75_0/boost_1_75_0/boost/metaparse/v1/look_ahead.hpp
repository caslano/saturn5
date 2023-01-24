#ifndef BOOST_METAPARSE_V1_LOOK_AHEAD_HPP
#define BOOST_METAPARSE_V1_LOOK_AHEAD_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)   2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct look_ahead
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename get_result<typename P::template apply<S, Pos> >::type,
            S,
            Pos
          >
        {};
      public:
        typedef look_ahead type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            no_error<S, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* look_ahead.hpp
gFBvnW6C9v4WxZgxkB9Vp/06E51e7MRYOFGrfQMn0JGJ/kHhhcQor80oSaDzz1dLlxr4JRK23Bo5CSv9jPHt9LR+e97eJuinPyp4u62pF5wDc+tLaaSqiNu35TmY/DvCLl7OzrNF3Q3vfYNOa/RNLiHWGhIi+TDPEn5OPmDkW/RV0HjlQm44SoxL+Q6ymJiUeV1zirhkmoXj4HLW2HLWgPzyriPMo7xo9K6rf6TgOnIUr0PxcQEuHHUpLCotbtwpnZ0i08NSjDc9mQn11ReH4MqKVaguXht2gWJaF1eEXaCQXc7fDl5rWRUW/rZV8rcR5YJ61Dwhl9EOc3mlhc8lsPFIFONxTrZ5PCB0Jb1wkqaIEbn32lAWPHcj7ZwF1lw31osVob0oX0HDtoGklzYP7KVbISuPd6zntWfCuKd+IGRNFYzWpo7dupE61k6/XPedtl8Lh595v8Lms7yM+lVp6tcln5r6NXz4mfTrqfc76tfsTzrs17Sp5n6BPGrp1z+HhfXrE+rX9BDwUPWpMHL8ZK2Z6h4bdiad2Lauo06Uf2xagzHYB+mAI8X0pSmyL1k+EK9/RfHaFWA9vnMt69JaaEf9X7nwhovSox4XwvVYNOGO9KB01KKnUgCNF3aodPWxGJjHHkwOxgCaFhlAk6b+EYAKDIh6BKL5B4rCc14DmJh0swidyTDsiX/gwIAgS5fGM7ZIsnID6pxfo11G
*/