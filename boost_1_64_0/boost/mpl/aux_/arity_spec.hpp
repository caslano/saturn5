
#ifndef BOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/int.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/arity.hpp>
#include <boost/mpl/aux_/template_arity_fwd.hpp>
#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,type,name) \
namespace aux { \
template< BOOST_MPL_AUX_NTTP_DECL(int, N), BOOST_MPL_PP_PARAMS(i,type T) > \
struct arity< \
      name< BOOST_MPL_PP_PARAMS(i,T) > \
    , N \
    > \
{ \
    BOOST_STATIC_CONSTANT(int \
        , value = BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        ); \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,type,name) /**/
#endif

#   define BOOST_MPL_AUX_ARITY_SPEC(i,name) \
    BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,typename,name) \
/**/


#if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   define BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(i, name) \
namespace aux { \
template< BOOST_MPL_PP_PARAMS(i,typename T) > \
struct template_arity< name<BOOST_MPL_PP_PARAMS(i,T)> > \
    : int_<i> \
{ \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(i, name) /**/
#endif


#endif // BOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED

/* arity_spec.hpp
oTFcM3tAQ+KMZgvO6AD3pYR5/zZcOE834mJT98ReasndKgKzZF6L00MlAxbmUuJoMK7v/cLiaNbpEc1sJcduGeliYrIIwGtZ7uWO7CG2LtMgLyMc6nr2LXqVfaTNx97VQxL0fEuqag5f/Mfg4q/ZnUaX/eewOzX+aPuFrzrZ4iWSaa+iDiXKaT2No7vGKOmsB9Z7n6jfWWIq31TKUVDe+1pi0qoa42BbH8bZzPawj9B7bTg5mbNJa0yU1Bdp3WxZwWaDgzmVHdatN47Pxf+Q9GFgfVQAF1Wco/YTtSxGMzCY85GnaZcZYXx9fInOYGrWPhYVo5KqeBF9MQXsSzeDr2uyiRfAmN4Lc+WxRALxBlxlfWVw4yMu1SlLj2o/+mPH4PMgscrMxzhsoRe+0dpnS4tNexrzuQUTUr+FpcXeqYE2S7DFxHZDywuQiDr3aJ0gKcGCEAfCrubqQMC+zKIrvL4W6sOhuyqwsypQOT94LLJU8Laikc7As/xmP4isOUG9mQa+mowYJgm3rFYVQRTA2/msUQDNr4wjzTCDP06tAzFJt0wPSLQYbH6RNFf4ouMlSztk6NDFv0Un8EiIRbLGwKpDyGleF7xH+31bhWb7yA+zMyuSNvfxCkt/lEI/Kr47SJuOqHxyReuDogSxCGYPcVcEWuokKkFCUAJ6LSBSkweJIjPwyx1L3iRebs0Z2kzAm4X9D+mQNcJQuSMYJvGmVLlVphGzWySZ3aUuxewOIE2UWdsFZhdxlOTCPgd7Ks1YplMuECk/jZUpjylfmGMaA+M8ADikilzLda79IteLKtdRlQuyN7CbHum1r0jhCBjw2ZC4NjWz4T7B0Pqg7MUruhbPcqqll6rloKgFWMkCFJlxaoVF7jsu3npm58sVpb4BLe+ESEIjz1MBe0vzeg5TTtpjQD7YayK14jDTVQ1EIiMo3esSHiDZG0DgIY+f1wSthsQ9NyUodvTFxms2zeIq1ht2/AW0GYAOGZlsGTD6vZRW+8JY1uWlGJvJTS34su+Jvukj4GG8sA/afjlobwUPWj2nHLT9GDQLSTqpa6UxQqQzHqM+kPH2GybB4nuOEYeTD2PXM7XiYOgxuj6Wxuid7A3C3Gsr4LmTZj4bEyqiFVRL7zfW4bwn8GFXQv1Nkd3aRxpb5vezMrh5PHIXKvf60ryBw2QY7n5jBCmQR01qxaGQzQMD3vlw9gaicxMEnXuSuC5Mp21MtqJNbt1iahcmowyNS9UtTiq4ywEV00Coz95qLFttwrFILUyKX9ZIvhC+AvYXv1I5oMXJHk35iBEXbN1g+2Rc+JMnY4eDJ8O/Q6yxLoANOwH5iyNp5koMoinH91LYxI/6RrIOjeoo1sHUrMMJxTq8Xl4hjSMb0dOBet5GoaOJgaDtduFP3m4xDt5u/ilC4ucnwxi1ynfKVf518CpvB64gkd5L0pD7Oq/AR0UIjlDzqee8b0NrVnHGoE/69Z8bqrD0FMhOCrBuI7N4nvkXvVKYMvX6M7FKnYHatEQ3+YfQfGFcx1L5NQ1z8f/Pv+gj5KebLquMv7m6XST8zU++K64c/yFi+npXVon/EDH9s40qp09pFxU//qu28v6TCL6iFh2nzPnusRRofM4k0L+OrJv9LzL8eaZX6dA44Bf5rvBV/jyjAlm9Ct0Dx3KCeh8ywnPgFkEWvFqlxmV++K3Kc0FwmSBIOIo3qiQQ93GxGl60LOCsiUwz2nz/9hI7fuqpy6Php/7l22Jb+vejpm/RzV7+c1HTv+y1px8fLT3P94+tES+VaaJGDsBY9ku2LEE8jBCBuYP8jxkOaeaRONDYeLQZu/wXtMEaUzplADck0L+OrFv8v6VapAsGzy8=
*/