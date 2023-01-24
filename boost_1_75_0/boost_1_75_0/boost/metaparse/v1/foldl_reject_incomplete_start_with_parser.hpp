#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_reject_incomplete_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          foldl_reject_incomplete<
            P,
            typename get_result<Res>::type,
            ForwardOp
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_reject_incomplete_start_with_parser type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename StateP::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename StateP::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl_reject_incomplete_start_with_parser.hpp
dJ2eqOuIoMNrSWrsiSNC1fFsar8GdnouWF4JZwcEOgceZAN1o0G64SDr+SDdUdoM9MGqkfhsH6V0Nb+YSG/oYxxUMfGzJdTyrY+mUInCkwFeeBLePdux8U27KCItt7/RzFh7vH8yu6k/Tag/IgwqlG+iF489TdOUJx4CF0VRN5T54Ea1SGWhx9C8BVt+t2Fy6Vqo4A4jI1xwfj3V+WmS4g7FsfY9i6n+yEnEQv+VKhY6riDSf+OVZPW6jrOCq/nRw887+e8BV3LbjIqz40TBDnBplRHeVnylc2kdakZieXctRbswtO3McdZJOLuMXanPx9VYQE/qBLSZ7CKThmZ32fi2BudXpiCc7cVQkmWLa51JReXFazkqr1lLgSzQjjQ4dSXYE1dCsNXKUTDwpJWoBVE9WnxprNg1ZQ2McUxXHzQBC3wWbQWVrcJVwfXSCk0vZU99uobrpZ+6e/gOuqUHMplasCqq7jEuF/WIBpKVDS7kZudx/xrM3IPMk1nO4Cmzf5oxCh76dYYmK03r3xtVCGxI+PQai0l425S/EYEoIwLB9NP7svTZ3/CWN7W2lc9DEHTPgeYmtLtib8tkhVXvxqTdhX9roawwr/eflRWen/6nZIW73mlGVvjtHXTlnUlWaDNA3Wlv9G0Kp+V7Wsbj5r0TE045F7eQx025lHhcoEUwKrqjWRhdAqydTcQWLuwQsTN9BFOhAraPrFHf
*/