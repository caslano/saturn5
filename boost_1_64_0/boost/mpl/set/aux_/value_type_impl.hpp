
#ifndef BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct value_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
66eSr2Og8g6MSjuVvzHU5gzK7ltmDWbFDDgtmc5+m+Ivid3ad7j2cSWda9TGVYT1vTPvnnONuRdJO2yfbacBI7MCNc6uI5rp+IWe7cgcK88JuGH63XxmKtouxT6dirhP0LMSPVQOF7eozGSnv82GaDGJZ6+AX8u7RU9XSYSV7pvYR6/zuJN5Dlmr/MBLgsAbwAYAqCkS+KWx5qMgkJFrmJQGTapYu5M28MwAfpG2RT7Z/HBW0o5eggYQaPB7GQ8JaKnwC0nqe19fQWoU/ql8pG8FRLUASIrgtQiaIrMpsnDQslxY1gYUmfgmBL7Qn1MN9MqXzsV+FqBw8kn0Tjh8IqxcsOhC6vpBmoOZP1DkWKttKWJkOoTOUY03TCpDzDQcQXIprBSLAx0qzMZtzI1UFmvBw8+cPcs5wYqGW9+8n+Kb6G+xpz/hz/6plLcLyOkttYtqqoNmyAuYub5OGcmpep1YpQ+p/v9ONmYIeaujYfCNUVkEzlNaaGK3amvbUXGR/iVS3WkpKjM5cFGawiDlH8f1z50zgnx9BuJDWir+3li6w5076uBtTkqLVA==
*/