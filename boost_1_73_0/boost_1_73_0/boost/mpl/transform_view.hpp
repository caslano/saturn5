
#ifndef BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED
#define BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/transform_iter.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(F)
    >
struct transform_view
{
 private:
    typedef typename lambda<F>::type f_;
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;
 
 public:
    struct tag;
    typedef transform_view type;
    typedef aux::transform_iter< first_,last_,f_ > begin;
    typedef aux::transform_iter< last_,last_,f_ > end;
};

BOOST_MPL_AUX_NA_SPEC(2, transform_view)

}}

#endif // BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

/* transform_view.hpp
Cf5uXoCKkwIkEq4AkZGJEOLrdg0R+morEfZxEsTgp6nYgxJQoKpBKtlQ/iOIRrpczlgdyAJZ5kpQkfMlczN/g41OcFoJ2CcqBrUXkEuxI76yAD8Lic2aBKcETZCrhEhHLE1eqwGQu7GpObHZEL5pytH1y+l86d0tnMuqzGL+4NUT0yuB/TypT4o+RdHrUR2S4QllEpVQL54fKZRNkxQCsV/AK2IG7SIWqs3cXY2tRFUyyUfs+ZHk1MZryuVcf2LP/wywcoyDAPP6jpRvYlxqWYmgauT2iwcfmcL7TrXYVBTKgQ/dtdh4q2Ihk9/HBV2tVpY2vR9PtOV0bHZ7MJEYEpHET4eHw4Fq9DmtoaFLKXXD7OvktF4k/tpSvStYJusMwyn61SCGwbEJRU3cxMTg5qCVZamRQthg6+EOTYv3u5wmb5u9TmgFAwywbwTc6EUd27Bfuz3sGgPTsjs2x4iwfYtHtoXRIIwGVi9qsZX2g/I2n8w7RY/Xz88Wa5FmZ61c/SS+fv4H/QFQSwMECgAAAAgALWdKUgBb4AyPAgAAmAQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxOTM2VVQFAAG2SCRgvVTfb5tADH4/Kf+DlaovUymEkKahJFKUTU21dIkK
*/