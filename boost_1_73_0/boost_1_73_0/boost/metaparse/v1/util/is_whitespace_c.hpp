#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct is_whitespace_c : boost::mpl::false_ {};

        template <> struct is_whitespace_c<' '> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\r'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\n'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\t'> : boost::mpl::true_ {};
      }
    }
  }
}

#endif


/* is_whitespace_c.hpp
2yPNKBdc2pom8Qs0MJ4cfW2B1vtVJNmG+8xg/OMYMpFz2Aq7VqWFUXsMQjqaYyiNkDfQVpA5B0DE2BSNkGrHECVqs2EyBVVYoeRpKFUb8aK0xzgTMsnLlIc+/Amlje/n8WI6O2lg4Nn5fEELZtfURe8NPnVdnFzd0FRtZa5YutsbQxuj1WEwYKGw0q4qQ1JwnUMjno/G0znNxbVrApXK8nthrOkUuafb0yPLgS9S1iXC0l1yLbIKfM1ZZrkGu+bg6GDNDFxzLiE0a2VDEt15W5eIVlYlKh+Si3gyByaVrDaqNAGZfY1jwBN/4fdsU+S8g9nj7tU4IKOrMbhDB2Qyiy8Dsvg9m8A0IPH0zwT2mQZeLgfLXxfTReDyfw5JIo+C68Jp+Lpqr7TiTfc+/QOfXTNrj36/24b6Wfn/Cp/dHCB4xnHzEXY/xJb+fYBTeMEfVy14hT9C0+Or2v/BzTGMx53h0vG7gTqb5cpNcScgg0EPrjgwzbEpRVFBpUooVFHwFPX6BgkGXTTIsdjcY0bkeQUoEqMkou8/QkhDEAaSUmtsPaRC88QqXTm0C643ezmbMkm4MVmZd1xmn2EiURbuMsyYMeKOw0+Vcmgaq4XLoEX63S5MYaNSpyTfVlSOS2PL0DVFlt4AetjMHob6
*/