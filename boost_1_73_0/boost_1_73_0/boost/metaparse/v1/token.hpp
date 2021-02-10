#ifndef BOOST_METAPARSE_V1_TOKEN_HPP
#define BOOST_METAPARSE_V1_TOKEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/space.hpp>
#include <boost/metaparse/v1/repeated.hpp>
#include <boost/metaparse/v1/first_of.hpp>

#include <boost/mpl/void.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct token : first_of<P, repeated<space> > {};
    }
  }
}

#endif


/* token.hpp
5+Ans/QheV7A0If30hVwlg/EosdDnJn1Wul8chYiXA4vgf+BA1k7UQoxmCaL9GEmB21es2SeCuBT8FNq1EaSsVHkk7AjLT3utXdbvWBdLhtoFwa1dFiDK7DLDwpl4RVRg28L44hk12GJYlMbZzJTTdhxMzh8Lh6bGusknOny2G9yh9+uaDilsq0rMXi5ny+o39vnKmEohh77X7vHPJJ8GhiLowpx+g/+AVBLAwQKAAAACAAtZ0pSa+7b5WwBAABdAgAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzVVQFAAG2SCRgbZJfa8IwFMXfA/0Odw6RCV2me1oXCuIEBzJFO9lrbK+2WJsuuVX89ru1/oFtUJomPfec302iCB3F2mEoVFasDQ9bPB6MTVwoxlE0O70grhyZHVj8rlgvlLyJlGzq7mGBdo/Wd1mCQlks8yP/TTTpxkn2HnvQf3qCOeoEjqbyxNAUhAX5Eyw2lAbQf/HEG+ZImATgqrI0DuGAsDEEGlKuQwt5tkWgNHN38Oo/eMITq1zz8wuSR1flNWuDoOQZiUmHeVbHNqTxacICd+IPRUpUsvwyBVXoHYb/bQR03kaTUTTqsEg2KlCx2e10kTQ+gZTt8XQRvc+Cdm0wm84jedAF
*/