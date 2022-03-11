#ifndef BOOST_METAPARSE_V1_IMPL_APPLY_PARSER_HPP
#define BOOST_METAPARSE_V1_IMPL_APPLY_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/unless_error.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct apply_parser
        {
        private:
          template <class ListToAppend>
          struct do_append
          {
            template <class Item>
            struct apply : boost::mpl::push_back<ListToAppend, Item> {};
          };

          template <class Accum, class S, class Pos, class Parser>
          struct apply_unchecked :
            transform<Parser,do_append<typename Accum::type> >::template apply<
              typename S::type,
              typename Pos::type
            >
          {};
          
        public:
          template <class State, class Parser>
          struct apply :
            unless_error<
              State,
              apply_unchecked<
                get_result<State>,
                get_remaining<State>,
                get_position<State>,
                Parser
              >
            >
          {};
        };
      }
    }
  }
}

#endif


/* apply_parser.hpp
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
*/