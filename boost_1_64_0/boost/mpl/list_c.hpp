
#ifndef BOOST_MPL_LIST_C_HPP_INCLUDED
#define BOOST_MPL_LIST_C_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/list.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_LIST_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE),_c).hpp \
    /**/
#else
#   define AUX778076_LIST_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE),_c)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_LIST_C_HEADER)
#   undef AUX778076_LIST_C_HEADER
#   include <climits>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER list_c.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/list.hpp>

#   define AUX778076_SEQUENCE_NAME list_c
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_LIST_SIZE
#   define AUX778076_SEQUENCE_NAME_N(n) BOOST_PP_CAT(BOOST_PP_CAT(list,n),_c)
#   define AUX778076_SEQUENCE_INTEGRAL_WRAPPER
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_LIST_C_HPP_INCLUDED

/* list_c.hpp
QVvxHU1pOMGagzn+/4K50+5+bTKpergt2XW9mUJyH1dYM9Y3uGk9wf49G7K5+6X/ZO9KwKMqkvDMJIEBAhkkQMBEwimIyq0g4gISxSNK0HiDx3o8R44VJnJoOAwIIUQRUVGRRY2Kije6uIICi8DuooKisooaFd0XZ9CoUaMGslV/dfd7M5mQcOge3873QWa6q6vvqurq6iqK81Ww9uhwV1iLFA87bHA4I3w48hrDIiQx3DRMUJVJRdmUPTyRR6Qe+r4PRxt53vCm8pp8q5jUcsVYm5Vy1tmJywDSANrw8oO0TUJwsXi65WhlMaxLGuZ1AnE8TJIHLSOcec2xXqpHIImsEaeRJw30+QjE/f7CnUFWaYFNnmHnnNOLzDXYaGzzCAcT5TcrIhMZH+X35mCrGda3ZpFOs26WRXrPyF/PaNDIA8Wj+PzNClEVgPd0aC5ER5gqbaZnNPRA5TRqIYbt6yz9QhcFKiz1M8LWdutTyGcCWQaJAhODMPKcIb1oJ4BigR6RlL3JS6m9mYFrBa297XLHkvK+s4GTVtk9NBcJ69dVJgzMikxTRImsKo1gu13mULS6Oxwvy52vAjZY4GXHw1Y1PQSnKz3jZ54PnyQt4meeAI8qP5wVNzODCZn9jziZWBhJNBQ03219znwXyHw/NuLXm+8t9VgP2N/5JFfbc4+HTKcOrRDpRpPibAidWEdArvjGKLpPibqBe2CMTj9WX78ivdCkt8IyE3V5dlALPA3Vlgbw5ov2U1mj2t8f/i8uitYvb9YaZMgA0N5umr1DJdrD+1BHoVaUyLX8CgXeXjJZYaJVpnCMOUI7utgOlWqUqwxbvEN0pXYDAnpB/p/jXj9sZtqy5shMv3qWPG55j7OW63zaLAVraSMMHVVDP8lxch93jlAazySF5zZoprnCHNUYHBXQW/Htk7632kitlzM0dNIJWUrJHfQLMGs50ZfSrxsyxxYwapWAEfn2T8y0XjAtydct2Z0tLUnyYXsXlPkL0R7BV7DeX3hnKdcjEr/HfiedlpJWAq84zxGp4ZtU1PlcOXTMW9EyIBiplcDPXeGUWUBloqASoPI1sLOPVOtMS13Fpaj31BYeeaq1BX7C+H+mSimzkglIfhOBpt98PortSRPuy25yZfoVRkoCMVPPfjmce3bnTgzjW7lOKznAoYRltv1HK/9g26XNu0TXvBW6ZmmcxvC3yx0MywlDFFQCOm1g7+/iHCCmF0NDj/NgvE6GujkdpBP262ZKr9JT2vZMOWH3CzejZjMLy+mOZstIFKLV8IGt7kT+0Q3Zhdhzuk19BolN/A6zyrGsSTc6WJgvoOUgPuyiX/8g/h/6Mfaie3Kd8wqkpaPYH8LEDtZo16abKzM0+XTFMMBVw1cQZBpB/r4m5FkGkk8ykMlPD3iUPerM/MojvnnhGVIMWaZkSJdMNSXvFfoMD/tVOLg0FBRA90uKQldRzDQ8Ij9JZ1roRf4HOiGt0Eu0deYJHtq1k5qQ0m1mfw9JIjewGv0ENrYPHUmlCgaw1miKac8U3Z5Zp2mtUVMt6P8a9ru16pNHnevoT4pzA7hK5sEQXUSy6CK+gqVgGmmG21kve3QfplqzpA9rh+s+TOTD5JcU4zvZePnCeakCUb4HZCVPbGetNQhu1AimGwS9MWJpUrpKlCyBr1A63CqcGpVul1fvvyOMfd3nIv7JOdH6R9t1boY3RBWjuqXSPwZomW1z9Wi29OjJU/UyG8gEmh2flRZjOLcrB3tbRxA6Povd7tWDy1pIJtUifmyXcPcjv1MR0nfNzN/Fi+yGztb7ukJoD3WdA0ydMMT7UANB7bImFw2GfzSb3a1+bBo9RCOoPEUo5AQoc0o=
*/