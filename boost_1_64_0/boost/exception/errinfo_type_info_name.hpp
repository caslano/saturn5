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
U03YRtzkvKU/Gz2OTyh3Bfz4mjxm1VdnvMdGM7RJ9sRAhmY1+pUgiSldM6Yih5HLWHwypszZwKDUxAF3FfU2p39odo/onsP8Y6xfQh28iuqXzG2GeSc0yJo9UElNtvOvjT11okAfWdTKGALimeiTn7JRlCp/12xrglJrrY++DLxM0V5a0RkWnxbqcNS16t6A3d9nG4IXpZrAZNMZv5moQB9GYb55d9coEtUC2dpVPyzBcNkcVbEbvIN3jbxALgnxdy7vUAvJ8PSjdoAcgzoR/8cLE2MZ3eSErJHGFZ38TiJpHgmrI6D73ws3StIW3oVEOQr8TlIgQZUxpCp2rFOVPUQZyzzfsRYH8R0ESMjP0lsy4S37d2yRCGe6+EtFnYHZ57MVoE3rtJMWJ1gyHzTe+e9APrA6L7lvHGcLtKALHCj6eW/JtVPRU+sf8sipE5KH4y8M0u+xFqTfO7/EN+Xo9DtGR/0KB9wE5N+tDUu8UecaF7VNwnbp5z4qXMJfDmYkIeBik6bS2lGS2Sg6VeHmVeTFcWqjEUkXQ/gQuPtvF/hgEDaby6FHXqFOFQ==
*/