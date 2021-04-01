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
mOMJ9A6lkVjfEI1Ir0LDO5SSq+LQOkIX2YKWJMy79laMjUxyZw0I+tFGM+Zipg1RorY4cSxhu6XQvZuZ1FS5RF4HsWNeJBNU87Unis3HxjoAzb8Xo0MGdp8QfrRmCi5YwNHXfo+MLRxIuyfycqdKWvqpbZhoGNx78i25ye4UfKOafi8GK1jLzyn4UNLzmg6YchuY3p89i7+e+oc9/cAFDLoJwPb8BKxWoI2ui/QRp449gYIcI6kt3r4jHIN+QloaN9uQecyTVjvr0R1TsKbO5kDeGwK/8cTtrATuoz4tnUz8B++wzpDTucGKCNlR1MNFW+m42kjW96UMURfgU4CeVm7FdASQFRMh2WgHvDb6rlFlJ6txhGxdtqFbvUtNhp98tw9OjVlsbh0rMk8qf1Yy0eqPVJeYpbTuCBvfD02fofRLczmM19FhfGnL6HG7mTUDnQZjuzxPvjCynmxRo7/PaiHq2Aam/qjdlv60DkvJYvXlBLgyE33QuP+swMzw5Rc0lVnxBhyI++vCEtef4s/iNcwxBmc0fTCOrh4J1beC5KS6xubMz/CTY2Hsug==
*/