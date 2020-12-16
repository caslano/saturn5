
#ifndef BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename List::item type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

/* front.hpp
6IZn0R1lPeTelHLPSrMeVs/EPIKl8Qv0xWPSTsc1Y6p1w68wFk/I/noSF+DXuAtP4yH8Fo/hP/FHPIdX8Qd8gOfl2aI/YTW8gLXxIrbCS9gGL8v2SHaR+0a4WbZHYZxoHktOPiffRm+chuUwGSvhTGyMs9AfZ2NbnIOd8B3siu9iX5yLiTgP38D5uA4XYiouQtNYdXK/B1OkfbVj1b0k9RqApTEYfdGA1XEQ1scQ7IahGIthOAvDcRFG4AocgntwKB7CKLyKMXgPX5HP5Vj0wAQsh8OxFo5AP0zEAByJ3XEcBuF4DMXXMA4n4DychAvxdTRd78g9Hqxo53rnJfk+0BfL48t4AyfnMN+nUe7fmPIp11tjUHkNk/0xCj0xFitgPFbDBKyDI7AJJmJPHImxOEr2y9E4F8fgVnwV92ES/x3B8fgVTsCzOBF/wkl4Hd/A+zgZ80oMdVGchmVxOlbG2VgH52ATnIf+uAAH4GIcjyk4E5fgfFyGq3E5fokr8RdcjQ/xfcxL+6xBb1yLzXAddsT12AM3YH9MxSDciONwE07BLTgTt+Fc3IEL8EPzGIBK3eS+RQfZHso2rIHKq4DsvwXRE4tgBfTEhuiFzdEb22JxDMESOBFL4nIsjRvQB7djWUzDcngaK+JD9EXKdKmEpbAyVsRqWA+r4/P4HLbHOhiGDXE6Nsb30A9XYxPcgs3xALbAz7EVnsLW+CsGSOxzO6yMHfA57IiNsRM+jy9iAHZBN8z4zfRc2T4kx/HS2c+ddSY2+mnGRduLiS7wO7HXpGDSVNJa0kFSOuk+qcRtnkFLak8KJyWRFpI2k46QLpJy3cnnUp7UmBR4JztmOvuV/cp+Zb+yX9mv7Nff//pL4v8Ng2Lin+L4f8Ha+H8WPig0huH/TL8BqGMc/6+wbvy/j0mupAOkY0pcyRo1nrZV69YBgabh/x4dU2vubz4q4//pYvakrLYSw/I8KU0pa611WYRUZTG+WemDPurE+H/+67Qx99IwWSzrUeP/1ZWyxzgY/y/VUrZ5kzyyPbXj6Pk4GEdvn2m5yh701MbRO6oZR+8iy5dx9IzTv8n0l35WMUoSmz2GAgsqSgx17eVq/WRcvayPKVV1tT6O+uoqSxz1t6tsx9U7tsp2XL2DlnlqbPB+y7za6th4q2zH31u/ynb8vaWrbMffS11pG4M9cqVtbHWjlbax1QUs8yR+kfjt5ZpnsTG9Z7l+TL1Ry//9Y+odtXom0XnL+HlqDNUfLChGnsdWnv2zB/vAcBf6mJZrYoqtx85zsR3X7kRu++PaBa5R950nHtfuqINx7drLmHoDpewBUnba+2rZjzWunfZYGmiwivHJY3+cu/Rlapl/yzh3yXlt44Z/UY5hS73+lnHujjp4Nlm4u8QY56a+4gk/6rveUl/tOHbls3DO2bXJco4ZtMn2GZPpH9gewxU/0B7DkjfV9jcOoRs0v1OQY33Eev1zGDdv0o9hN21T1sewk/O27TbXxmdaYvStx8jU/nbLeEzPzkvFaGOlP0vqLmNn2oxrp76/h7tpfw7+QD8O5qfULSIqLFob55WaKnFYVp8lXvnkuWWyHw6Xce2Sl6rb9S8f186yD2aPW/d3jFt30xijVWTqLxne1WLXF1/5sFByi7h6zsew/Z3j1iW5yLW1XHOHS7xzvOywgyS2JQTdMRQL4WD0xXBsghHYAYdgEA7FBIzEt3AYLsEoTMVoPIAx6vh2ct0t1+PW49v1kb6jl7EK9sPq2B8b4ABsiUH4PAbLcpFrbMfj21WQvnZfLIuV0BcrY1Wsgv5YFQPwWeyK1bA7VkfpM+N62vH4dm2kHQPQDdui9HVzvex43Lk4We/h6I0=
*/