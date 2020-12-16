
#ifndef BOOST_MPL_HAS_KEY_HPP_INCLUDED
#define BOOST_MPL_HAS_KEY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/has_key_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct has_key
    : has_key_impl< typename sequence_tag<AssociativeSequence>::type >
        ::template apply<AssociativeSequence,Key>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,has_key,(AssociativeSequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2, has_key)

}}

#endif // BOOST_MPL_HAS_KEY_HPP_INCLUDED

/* has_key.hpp
fMx7pg6sxDo9/rcsMEFaFdReDjmaY47XIcc+WXdsRHdsRHdsRLdLJrt5sRXXIUo7xEom1lBhd08bRcUBjVNzWrm0EgONxD/KMuCylb4FmvbP+Zr2Ev37M/37Nf27h/4toX9X078HqzTtLvq3kP5dRv/C9G8i/Tua/uXQv+ahz9Dn//DD59kxuP9t7uoxV3pvTXY+L0MQKNFwwpTb3hq/BimcbNin0SmgLijqeMJ+tYp4mnjyYuNKc55qw3YwUfhQlrR+rBxHCw1yeVNBcMY/yaUgDKne+Cb6FSOpndj/Iom88RpWxgTe42QTaIDr8GQBQWtaO6e1W9KSS/YCBZIreMlQ+BAtGhIFalnk0opL7Y5v4VJ4BkH1xu+kXzGNpNH+3QRvvBsCKykuy6LoTnGo/TgApyMTtxUvfGhEtFwAH0swkUn9JIDjG6gQlaCe0gFr/Hb6xdrq+P4XCOD4fCyNcdhMZWOx7CgOJz3huKKfjs7pfdBPpyKgn87005l+upV+uoUucQ/vluLohQ55mywOxzGsHcXlcRzP25HVQS3h0JdQpEyAlIk+SCmOQTyGTEoaTWrLSsqESUr02EPQOtLT2jmt3ZKWBEl5GDC2h6a35FCqxfSmsaQ+WumdtNA7URxuV8SOg9jxPogdpyIgdpyJTaNJNLUSO24QGxRNesrjin46Oqf3QT8diymPIdNPZ/rpVvrpFrrEPTxScfRDx3RLYhCpix3FoTg2eu3I6sA+oh27FJAyAVImDk3KBJUAKRNMShpLaslKyoRJSvTXQ8A60tPaOa3dkpYUFOVxwND2QW9xwuUxZHrTaFIfrfROWuidKC5vV8TmWUWD1Aex41QExI4zsWk0iaZWYscNYoOiSU8oLumno3f6oemnUwnQT2f66Uw/3Uo/3UKXuIfHKY5e6JhsSQxhElIhjnNZO7I6cFJoH5KzQ3J2SM4OydkhOTskZ4fk7JCcHZKzH7achUyN28he/SOVs3K6GJzKl6FPSodWfA6P+rm6KqSnFxI603IqNPAQAEOfoc/Q53/kY9irnFLH9ipFNV6svxr2NUGIqDFkvTINUf87sD514Aqig673KeMkGMfprsLlz7khz8XdH9aVFERVConi7i9ul+61S++daKoe47hkNBtK2DWUsEv32qX3TjQvGRNpl4x/WCvMOsN8gWrch1EJpewMkoR1gQQr2HcQVoqUWJQdc7wOOXbJSsUqzAiS6X5XUnxrksJKmRKbOsccr0OObTJ6K27qCBHaE5MVTfH2FaEeixGN/5bynhUjTIsElEOa8GFT3T6M1u/ObQcoqNuXFR+1Wfiojfhowv8LHy348f8zH92StSJ00HIFnKKNOaf1KK45uGJE4cMhsrUMHyxuYJuWLJOx4DWres8wvvn+PXHTE6GDLq5R3sNVqC9mcMgkD6451vhpXB2CH4qIOaNDm58P+8PriQb7R7J5Hyybk8Rg2ZzQ9NZoGifIMduPetucJISpmJNtF04Xjjleh5w+bLsS4uxob3GCDM0pw2ufYZNquWBP9Lpgx2+LGeAAH4MPwof5sZXM7oGV1b/gWQ+lv7fAzqcNO58Ww5tHEMfMuLA/xZYojjFAorQ/7bBL99qm2yYCsm4HWbdL99qm90o0I+d2sBmNKRd1FoS1EITpZiIJZrAEaosczTHH65Bjn6w7NqI7NqI7NqLbJ7eQmzPyHoINRQu5NKENRYi2EdhaLPdgQxEoJd8h5Jjvh5i3tWzHmbCaE0FN0G7OpATPgITQxCFDc8rw2mdkpKYbKwlLWctyn+A1OiEUDMjRHHO8Djn2yc1ovFmINwrGUvjw1FHJ4qZ0oWJZk9uofPXeYWQ01Xk/7MuaiZw=
*/