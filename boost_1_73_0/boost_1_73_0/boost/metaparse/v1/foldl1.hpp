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
i9K67yhzW4zhualITGyp5BiSShlkzM2Ucom/oxD8TElK06pspjulpH0QwLT6ASusrQl+eYKQ8Q67CPDluf43HEtbgLH7LIM4s6hBxzJHuH8ZjkZDDzTmGo0hLw80zbtxEIna7WKZBqzXn4fraLEc95tcy3AVca8l5v7jk9cj7SuUrmd7ZHuDusxO0OQ569oCoVk7FLGBLaKEnimUJYpDiyWCWiurElUF7HUWAfe8VgQuG3XYXBk7hj+WHPZJG3AnOanTSve64v3NbLVehB8OmyQJ1lQe8IHDnDOz/w/Mgt/8C34NxW9/7RdQSwMECgAAAAgALWdKUutJCOLiAQAAmwQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjQxVVQFAAG2SCRgxVRda9tAEHw/0H/YxvglcDoplLYRVxUTQh1SahO7eQ1naR2plXVCt/76992zIjuE0D40UDiEdm81Ozs7SBM6yozDVOiyXtpUDGCDbbncAxWGILfEB1pc2Y2pIDM1LBDy0plFhfk7oX/hfmvb3KViPJ9PDw/4ej3vXprW7vZCq1ORVl0XMeBGM2y5l3RljkK32FR7LsgNmQ5MxWEMF1EEk1txZWvCmuQ3rB+pSOCDz9SYUWnrBLLKOhRCLq2V
*/