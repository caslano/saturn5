#ifndef BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          foldl<P, typename get_result<Res>::type, ForwardOp>::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_start_with_parser type;

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


/* foldl_start_with_parser.hpp
ImcI/aMrCn5XlFKQglrx0Y/TYbmxfF22AH7gEJSPNypHOz93beaG8p3qnrB/k9D02e5mHD+s4rj3ZjaGntG2t4rHxPK7viXgICi2KsvP1YxmX4bfVM8Pn12C8mm4uahVR+Jt1fNQVIy25Df+lLRiH6fZ07xT5WuKKasQOa6N+IJ7HDR/veK8sy99Rpy7IYhiFQuCv5SHOHxpc+mLlno++asG1Yib37NKKV+2wd6b6BdcmyIs758BjQ7+PsaDpvAeFgECQgV05eqRAfM53rhCxeoR28ncEgrjTLWlyYHwGs1w8BkH0jAhDRP4CIjVCesDiI9CwOhZKlADKjsmbGLm0Erpl1et9JAEW+jyl7ymuNOrS+mP9miQmucSrsvqWKDkANApr8sL9Yldc5lCF2DVwRpJctAU/A/E+1hz+T7pHcfidKq951OlEcbgZ2qRHCZK7K77Rv6jI44XXh1tpFtNo4KD2kNWCzrVpxWtfINRePhX1oUEFkxkpQtnrVC+uyTxYS6qe/ZhUJ+zBo9i1qrZc5WiNigdpDX92qIgQxGWodOZndsMlHXHAMwu4w==
*/