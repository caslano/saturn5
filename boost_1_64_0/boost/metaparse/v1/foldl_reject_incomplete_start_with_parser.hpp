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
mvPGtwmt/N6n7OoSp9PiO+f2VGZ5X+2BE8u8mlgl1RGwSf1rTzfXpizpokvKdI7hYubJ3fuoXxh8djOufpcurjtqD1b1FiJYqIzDIBHUL+8C7cWmmLox30kcHY/bFWXInzhY70UBp11V8v2CPlraYRKqnqcat8QdvM9d4I4EWOTyZST7tYMxv4TKhI7T5EZY9Q3xzAVEpyd/gp1omZss9vprgTHHkj1NreM9jHBAqeZbDJMCy0zDsObvxtyG3fn27VqxjxUxCMFx2CpKFUHMgqfZqaDgwDXqe/EpvAYyXqpnpUvgIMw1fbeInX2dBC3hxB9vGVCAnduuvy8MfWzZSmFFIOZDPGpOHDgTj6SFxMWdgy/cVeniq8W07i00TtFYXGK4MRC9iUD/qSMFoHuwpjv5KDHnwIxHb1EUlek6fEyc28mUXD5iO7PqZVZ9dVVuBO3ru1ibdzzp3SUPhFmuhp4V8gh7EgqUvsHiXRRjUG21mpe5mnluTplPBkxjFilRNGfKK6Am3srSNPXLSiHdUCWClimPrJUcQyCuILBVt0mwGpg4rXv3gU/IEQ==
*/