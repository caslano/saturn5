
#ifndef BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
 || BOOST_WORKAROUND(__GNUC__, < 3) \
 || BOOST_WORKAROUND(__MWERKS__, <= 0x3001)
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) (T)(expr)
#else
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) static_cast<T>(expr)
#endif

#endif // BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

/* static_cast.hpp
IjgIGbuUipflYg+wkBbog4UgPbwk2jOxRSasCLeKRyLTKl9JfpJYbGiGXFo+KcWG2PCV2MOgByNtzAKejFaztTkfwo//SWZ4wu7v771TokfLMuNIEC1lJ3Te77q8NGWXsfTFBw4Tnq/pbboRtm74yyRsw3kp3YltQLLmhdS3E0xYgVhR+/I1Vnwukj+jp4185ii1cqMQqjFW1/j6N0JpN8eZns8pGaArt97vKu1Rd1XjHlVSZWWdi27CvBqcuJrOjlzh9IDjE/n+zuBmlA5vox3H5PbmLvXD4DAIaNY0PEUWu4f2Jg3Ff+8hR4jaCyd3c5YekDdjYeR0Ac444FOkSLuI4fK+TASJ7dpCY5fFj00vAVRGo850mTC6pbAmtsxRhw20xQj+4tNhp5uGLQedX42f88H4+cf34ae2Piuyg+t+h30ja7zTGbGNIKtN6e+ML+5Gw5uvhJRloqLlXX+3wzobTML3MXk/dOyvBccWcxpl8ubVfCOpS5jYX7nqr/8YfwNQSwMECgAAAAgALWdKUtKnsfFbAgAA0QMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDQxVVQFAAG2SCRgbVNbb9owFH63xH84aoXYugUniLVrliF1lNJ25VJIK3VvxpyQ
*/