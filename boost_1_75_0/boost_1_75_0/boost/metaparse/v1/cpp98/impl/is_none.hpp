#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_IS_NONE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_IS_NONE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_char_except_size.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Stub = int>
        struct is_none0
        {
          template <class C>
          struct apply : boost::mpl::true_ {};
        };

        #ifdef BOOST_METAPARSE_DEFINE_IS_NONE
        #  error BOOST_METAPARSE_DEFINE_IS_NONE already defined
        #endif
        #define BOOST_METAPARSE_DEFINE_IS_NONE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, class T)> \
          struct BOOST_PP_CAT(is_none, n) \
          { \
            template <class C> \
            struct apply : \
              boost::mpl::eval_if< \
                boost::mpl::bool_< \
                  C::type::value \
                  == BOOST_PP_CAT(T, BOOST_PP_DEC(n))::type::value \
                >, \
                boost::mpl::false_, \
                typename BOOST_PP_CAT(is_none, BOOST_PP_DEC(n))< \
                  BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(n), T) \
                >::template apply<C> \
              > \
            {}; \
          };

        BOOST_PP_REPEAT_FROM_TO(
          1,
          BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
          BOOST_METAPARSE_DEFINE_IS_NONE,
          ~
        )

        #undef BOOST_METAPARSE_DEFINE_IS_NONE
      }
    }
  }
}

#endif


/* is_none.hpp
Y/p6LONtgYeRzClWVDLuQ8uDqqEvSqORTnD+AA9mB/agbizVYGUUyn0R6Bm+aCabJisRMhX7NoXpMLgY25nTb95FTmm+ySEl7GNWAhkIDm/aPp1Sm3vxnAMha9jSIsbk2NXnlJmp0nGXtN+FQnoPgOvBDi3D5TtJj6moc+vm4zZ2OPRgqOAEKaF6oi+hno69adVYj1oygIScsz8wJUsBM308Gox10hkKLJQSoib4Ev5Cx940zMJxo8nhlfWe/YEBTmmuSfpVqQd0joajc1QnGXI75uwjzy3MG7gWhz67Il+W07fQRKlvu5VsvH5e2LhedpjV/zV+2BmlVYyHK+hQofWPKWnk3enYxspruGPpunRa+OI3sK4tz+qYQ9eimKdtpZxS+VGeRPIsw7EtWhjXRuuSoj/xz1pcpRE2g9EifLENutW+GazAq/5Ci2qZ8FPaKAr29aLPeIvTQH4YdsuIP+zGX9iN9xLpxo+9tBv98IbEYb0VYF0ZiAasU9mCezA+C8c7qzuL1uF7ebzyK/N0JDkkmGmkg2jfhOSid/CgFO90i2qI+icmlTycrnPH11mxRkRgC7rvSNcJr7eVyTaekKqE3jvmnIH+uT6slpVviQXARXFEcjEk3L82bK2PsSRa5vqOKC0aga3g4wJ+J6XfxSS7SAb7Vha95o5HQYi02RswEpFgkk6DXoGZPavRIeVZxJwYYVXNOF8C9Pc8
*/