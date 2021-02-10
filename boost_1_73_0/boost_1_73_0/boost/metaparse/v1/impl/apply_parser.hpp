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
3oWsjjkAwt02buMn/FmwcR2t/VmoJ5sO4JokSkRWajWAKNPmZBNWuSAXX62f2m12lE+kybWR9RHKQ/GtuKUXJfQeopQXRtjbpFSqeg86J8tbYwuungRjd3N8sECUKxVqXxKsyTiT5L+uVOQ2VCqbSgOFwL0BrXArIBaP5RMkgtuyEGA18CzTL1AaWmNsiGWBSemicgJcCDqHztpz0KXNSwtSXeIBqZ6cx/H98vMmnK7CyWwJO15I/pghin0I7KgLiXBPkmFd2BFLbI6Kw25IlXC0gFi/qEzz+NKVCV6kTWHcnmBoyvEQHiG1JaCYjNBRfR69Y7V3I3aO7PZi8TDxM/3k4tX6YaS3W67iQ6EbSrfrFC9xJVWUlbFoOJQD37/4NF+Fs8XgAvEt5svQz7lN/SMbj1gwhp8KHhsSY7R9EAyHvbeOoCOWiyKDi9VyjND8TD4S3XylkTLSIKPzzLk5MAO9nJ1Fl/sOY1e+iEImFTj688SKwvWE3EHKDTwKoaBhUm0bbLhztgSk0FZHOhux+9V0CVxpVW11aTy2+GW1Asz3Z/GVb/NMdBA9Sh8mHhs/TIBS9th0sfrisfDPxRRmHlvN/poeh9JzA322/eN+FnqE/xgSqUFacNxvUJoH6//xyLoUD7n3znI/MgWT
*/