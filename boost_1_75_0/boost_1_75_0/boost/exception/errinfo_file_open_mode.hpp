//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_056F1F266C1311DE8E74299255D89593
#define BOOST_EXCEPTION_056F1F266C1311DE8E74299255D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //FILE * f=fopen(name,mode);
    //if( !f )
    //    BOOST_THROW_EXCEPTION(
    //        file_open_error() <<
    //        errinfo_file_name(name) <<
    //        errinfo_file_open_mode(mode) );
    typedef error_info<struct errinfo_file_open_mode_,std::string> errinfo_file_open_mode;
    }

#endif

/* errinfo_file_open_mode.hpp
eWi+1QYJqk2HHkhSkcIyqKrJkSJXJUelOgg5W9RQ9i89z1cJkOKJf7iFektFJn3+Mek+/xQvWyyQLDNRfvJqUpCuyKHfR8S12XUE5//im23FrzlvN5ormvO966Hh38P5/M81cP6HGvx8DdHjbP8XvsoxTl/lnbFsfU7G2JQa72ozNuWXfKEYjRWU+dgFnQ1f5cD4LNI4r3uqneGrGhJvPphEOmweRcjNzRU9DQVIxQrAZgRjq1W8mgDm9ktkik5zosttBOAota+qxJFRmtrF58oSSglGqQo95RhAcxQeHoHKQRllG4HNk4r1ZHdKyFs0sSoniP6PS6R8UjSSCg9nhrwyrjsJIeLLv+PC74Zlj8WFpcQQl1/CSUCpWLT/LrFkZeuSUVs1MwWN2GJuGwkQG+rfQIbTd+e2MwIjRpwJgp4qwJZQtjl41LX6+oSyOkexC2bcNNvvqLrWkQEOibXiawlj1m7Zgp2IdhkJwZq1W+z1sk/CJmw++bVOhn8/fKCJNy2ySFwVx2X4PxO7Il38bc4eCslBm2eLv6FNJsSWw/YWam22X5CQPUL7By2eMlDLFBCccbqUL5KAkpUQoIIjcrUK2aKbfa92MgLJ3jNBmpfPv69iR1H0shgjrLRuMIhF0csAKev6imF8ItpiegYY43bx8nxxwzySjWNcLP72VsaIvxa8SqN14j5wijcYHFZ99VgAguBibcF2LWQY
*/