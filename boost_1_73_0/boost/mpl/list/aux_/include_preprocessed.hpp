
// Copyright Aleksey Gurtovoy 2001-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#   define AUX778076_HEADER \
    aux_/preprocessed/plain/BOOST_MPL_PREPROCESSED_HEADER \
/**/

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
oy8BddLNAbXSbUH10qsDaqZvukLd9K7/sXa6O6h+eiM0B9VQ74bTYAjnv3D6CjFXqavuUm31GqgNqK/eohrrh65SZ90cVGvddoV66ytVc31TQM31LtVdPwvGaz9bfz07oP76oqD6640BNdg7gmuwB9RfzwS76rC7/ota7D2qxe6vwx6vWuzpEfQroCa7R3XZg2uyd0bQrwj6FUG/VKM9IpJ+BdRqt6pee3FAzfblqttef4Xa
*/