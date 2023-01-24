#ifndef BOOST_METAPARSE_V1_OPTIONAL_HPP
#define BOOST_METAPARSE_V1_OPTIONAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Default = void>
      struct optional
      {
        typedef optional type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Default, S, Pos>,
            // is_error evaluates it anyway
            typename P::template apply<S, Pos>::type
          >
        {};
      };
    }
  }
}

#endif


/* optional.hpp
/dIOvbUgvc3lI/K5pLc/LdEhKtFbC6O3P/8jvbWrTFp0wjOguNZCIzq+PSjJwc8QRQ3kx4ueIZJrDXKS+y1IF7o8I/VCHjOfSOGY0KACkHPyGQ30ZeJ1WnCUDZKnUCDe3MY5eCr0N3ojmKybBsHmliGUO4plzdDGt8pQIVhUGyOk2Qw2iDBZhweBSe7sXCTWhMTAhF2q0xCTweF3tDag6ZkPK4UwoQ7/ncKJqVaCUr6lhIVV7W61/7eglPl5fL4iiF9LBpQ/EtPH8CKY7EyOsgaRKCYmX2j6F8+37lGcddy/hMdFAOIGSeZDFkkZ9ehCrv+HjxGI6j9eKcfItbCOjE7Y/9+Q0tmQIcmzxmvHmbqiZmpwDpZ/4a92wpkvPGbzT8XRa/D0nahh7Bo6LXcctqOuREPmFCR8Dt0lR0zDJ2EkAMRzHl8/HAUKpPiZZnwFHIne84yEuVSsyQWPo1MCDEKaNuoIEhR8x/KqmKb3ivb6yTIyuFTic+4KSK/xtgBB/x/i4xZbyseNbCJmHOBthifx71eIYRxEKPVsMXcmGovmNHaSICkBmJNxDec9kJ8Kfv/ZLwjwM7duAj6rMwUl+KLtCvC8f6HudoK9pYZd1WWO53OdhMjJtvUp+4li97OPXNZo2db3810WbxHb+n7GaGvgXPi2/h18NJPa3UrMrhWZFHYoDVvzJ7tWxf7VE0qpiO6CMJE+rH8O3dmn
*/