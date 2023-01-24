#ifndef BOOST_METAPARSE_V1_FOLDL_HPP
#define BOOST_METAPARSE_V1_FOLDL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl
      {
      private:
        template <class Res>
        struct apply_unchecked :
          // foldl never returns error
          // I need to use apply_wrap, and not apply, because apply would
          // build a metafunction class from foldl<P, State, ForwardOp>
          // when ForwardOp is a lambda expression.
          foldl<
            P,
            typename ForwardOp::template apply<
              typename State::type,
              typename get_result<Res>::type
            >,
            ForwardOp
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};

        template <class S, class Pos>
        struct next_iteration : accept<typename State::type, S, Pos> {};
      public:
        typedef foldl type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            next_iteration<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl.hpp
XfHZ0qRuT2X3mtS518fZUm6P7F65537OuEyZUyp/qtfH7M9eZZKrk9XVln4BA/6YX6gcHo5LHuRSZrNBXIqrV3n2INdRdq5Dtt3rOjrIZYULPqur12fZg3wn2FTZed8JpvKB4OAAl8hOsP+D9MD0bvwIahn7eHZ0y1hddUVdPIKqEdzzW5wuo+YwkxSYxCCD6CAD+d74WXRKzZyPNgOhDIxlbDDufStbmuc+Ax7XSk2vefKzlqTXyMN1saRcLyBvwG4vUIUYc/3nr6eda/tm53q1c/0KOyz5bvnZ2ymRCWf606ctmemQZmd6iVdfU8Mw1y6nn+tNn55mrj/wuR66TTfXrBbN9fFhzc11zqiYc4VApDuPqHN141y/NMz1/UqLLqsyC7Mqaa53b2iHm7MfQn5DW/zR8zMQqCrBuLJxKzsjX3SPWeAHBqrOqBQeo/TYaaQYqFrp1Il/BfpaG+9fFQM/4DtePnza7/ilovnv6ItTn46rsuEy/DHl06jvmFxg/I63K1ryHaZmv+MXj65WtFYjFrBn7yFBZo9RFTw0WpWbRFQD41J1MvTMVMs6UgeFsdwkhrVlyROVRDHvDVQaYWbkHMZSZDacv6tHMlHB50q6di08AlexZwsGX4WscGdH9BSx2/HWpFgBVyK0qmOWin/cQ4GuoWvHcP/PGNU+0eDW7BMJYOdK5rwfPjfjZ6irNRPElBnTnKG07LDL
*/