#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_SKIP_REMANING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_SKIP_REMANING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/return_.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class FinalResult, class S, class Pos, class... Ps>
        struct nth_of_c_skip_remaining;

        template <class FinalResult, class S, class Pos>
        struct nth_of_c_skip_remaining<FinalResult, S, Pos> :
          return_<FinalResult>::template apply<S, Pos>
        {};

        template <class FinalResult, class S, class Pos, class P, class... Ps>
        struct nth_of_c_skip_remaining<FinalResult, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_skip_remaining<
              FinalResult,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};
        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };
      }
    }
  }
}

#endif


/* nth_of_c_skip_remaining.hpp
YlsH3YelJZzncZsc2ZQGK3f7DQm73rZJO/s7QNLoLKDrH0OTFwSjd3CTLbKiadearVK/TnTwUgeFab36v4UvniNSIjebDkNUCvwjjFvYuU/O3QCU5A4ViM15CHh3i4wmvtXmANTpmF39jr5ttyFP8q8dwOJoISA1Zg5YmYsAIM4mRHXlBVFJ14kJ/5QvMNQ/ENmuB/Tm8imFY+8Mt6M1nMAcKsyBQ29hn4D7yEJ7IPdIzAZiu2wkVv3uF7RHFYSyc8J93kJVZ9tztJBDcDcowYLMxV8is+tdi6Q60ukJnYGNnYqRm9C6tOqyQqAnwUJZd71diMTGvTfkk/Vtsd2iiSKlmapCBQvgka/gkYC7OXwqtnHacdqYL9oID6Gx4KzEU8EozCPWD5veQE48SvyebMPy28r7uuvLAiAFuuvuQiIP6aSK1F2TC4lAUKjLCXBPaTbTWleZ7kHErcIalHl/gcO2bSU61CbXjKqZnwqw6qSQ1GkJCmwSqzJib6BO9mNWaeWRP6FLeIwOQQdIvJDaNDXVklwN7Dhko7stOTIf+Y3O0BVyZL7TAryLchupQUfKysUOfbCsXOd8M1NsyNmv4udhVGR9ydWbuITTjMTqPVyJYe44q4WKPP12facHQXgzoqS1G3SDChULKvTTK92pUPfxw50fEwzUXiC46lUeudAdHh1UM14fk8L5szFV11TUMN8dQJfwayeKXF0S
*/