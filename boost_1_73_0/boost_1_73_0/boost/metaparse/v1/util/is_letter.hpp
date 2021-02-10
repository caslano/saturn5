#ifndef BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_ucase_letter.hpp>
#include <boost/metaparse/v1/util/is_lcase_letter.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_letter :
          boost::mpl::bool_<
            is_lcase_letter<C>::type::value || is_ucase_letter<C>::type::value
          >
        {};

        template <>
        struct is_letter<boost::mpl::na>
        {
          typedef is_letter type;
          
          template <class C = boost::mpl::na>
          struct apply : is_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_letter.hpp
bd09LRkn3bXX8bcm+fvL/g9QSwMECgAAAAgALWdKUjBV3W7jAgAAJAUAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzc5VVQFAAG2SCRgdVR/a9swEP1f4O9w81ZIRlPlB9vYcMO2JmWBjWZJurIRFlRbbkQdyUhyW9P2u+9OcdpQmENs6d7du/PpnRMvnU+Fk0OWKJ0bfFzL+tbYzA3Z6WLKZuPFjCX82ZjwrR97DXNpb6TtOJVJllhZFjXCmfACtEnXMr0+jmvp4iHLjTFsQ7eEE04sjT/SnBRKat/QpGGDDi6QY6wv0Xu3S7TYyFAZjL4fQq4KCbfKr03l4aQzAqWJ5hAqp/QVdAzkFACIkCsSbeOT1Gw2QmdgSq+MPo616SBFWflDXCmdFlUm45D8E+cH387mi8n00wGmnZ7NFrwUfs2JsDf48JGyFOaKZ+ZWF0ZkW9so2NZSZI4MmLlJiclLgz2n/gxZKW0BB/PZyWgy44W6pOPg2nh5p5x3R2URaHapkGUvFimbZmETf0mr8hpC90XupQW/lkB0sBYOLqXUELu18TFLboIvFWKNN6kphux8Pp6B0EbXG1O5iE2/zOeAb/9Z3olNWcgjrB6tF6OInVyMgBoQsfF0/itii9/TMUwi
*/