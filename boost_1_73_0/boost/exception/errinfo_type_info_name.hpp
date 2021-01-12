//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593
#define BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //BOOST_THROW_EXCEPTION(
    //    bad_type() <<
    //    errinfo_type_info_name(typeid(x).name()) );
    typedef error_info<struct errinfo_type_info_name_,std::string> errinfo_type_info_name;
    }

#endif

/* errinfo_type_info_name.hpp
zfxp+DFxL0PZnRlHDtK8eoDUpVMbxd7k4bPEf75zKbXIHQf10bzMIHLL3Ly8YCPb4FORZEZz0fwTaC2GqMTYZEZ1sYkxtRNj402ebkz6vrjhDuN6XTf2hLsjCdG+/ORkUwbGDLVsjNn0+41qoKPPjfdSHTdJm48YN91kGTd5nxU61tGxkanDYn+kEvtjFnvvM6ez6ux/C0lUPZR3cc99Er+V8shhiWhGLstEljUY82w4IO6f
*/