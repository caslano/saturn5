// Copyright 2011 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H
#define BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

#include <boost/phoenix/core/argument.hpp>
// provide some meaningful placeholders (instead of arg1...arg4)
namespace boost { namespace msm { namespace front { namespace euml
{
    boost::phoenix::expression::argument<1>::type const _event = {};
    boost::phoenix::expression::argument<2>::type const _fsm = {};
    boost::phoenix::expression::argument<3>::type const _source = {};
    boost::phoenix::expression::argument<4>::type const _target = {};
    // this is for state actions
    boost::phoenix::expression::argument<3>::type const _state = {};
}}}}

#endif //BOOST_MSM_FRONT_EUML_PHOENIX_PLACEHOLDERS_H

/* phoenix_placeholders.hpp
HQ6Z+SVZziQatDdeF1ux7bStbClLkKFD3wOlrsUOzJu71wm4n/RWKE9FyXhTcWy0LV+qghSs6B6iBe5Zog+vbjpB1n3XGV115eT1WJpIw0a5oCmBK2GNM9wmt6Sivyh/wVdtCSGaCosP/TyoAivCPuSPVhGkdw6QhK7w5B201ZM7M+72Sdo4zvBINJV6/19e9UEsdR/3ts4CUs5ADQIoUzniya3GCrSO7LxJ2AUsVlsultHfkAn7STu+zDAn1uT1hfV4PA/wmeWuD4sIynkxnLckAYrs25Z0sV+7d5CKEag8INdxantfj1C6Bmrtnw52aTm/3ts9mSrtFRBhhWKDo5IlClVIeaXEfHhAHOY+wB2ZKN7yjry+UlN9FEvaBFyDADDxT0e2K+ci2zgIWuacIeYRNQvAY37fIH9XBURC5WRnn6fyUTlKT5Vh3d8JzNQepTMic/02EQA9732UcXAvAYbjUyGESORg0hx70o5rlYDMEMI2gLyLd6xrzI3PJIFMkfgxGz3u7QSckpOfGghIMW/M+/0/vdkdCQAQ3mKN+e7U3e/QO0avxmV4nA==
*/