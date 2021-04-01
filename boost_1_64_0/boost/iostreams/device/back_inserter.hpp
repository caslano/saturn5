// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_BACK_INSERTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_BACK_INSERTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/detail/ios.hpp> // streamsize.
#include <boost/iostreams/categories.hpp>

namespace boost { namespace iostreams {

template<typename Container>
class back_insert_device {
public:
    typedef typename Container::value_type  char_type;
    typedef sink_tag                        category;
    back_insert_device(Container& cnt) : container(&cnt) { }
    std::streamsize write(const char_type* s, std::streamsize n)
    { 
        container->insert(container->end(), s, s + n); 
        return n;
    }
protected:
    Container* container;
};

template<typename Container>
back_insert_device<Container> back_inserter(Container& cnt)
{ return back_insert_device<Container>(cnt); }

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_BACK_INSERTER_HPP_INCLUDED

/* back_inserter.hpp
kZ22RlBGR2/12JbAGq58qm102vBEduqQISbaUfsKURv3A9BHJjMNVE/jvnCpzV/tyCnQXZ+K/0W9ClW0jCSeQvpfeIoPhnMEMaMIRwCPFesVCtWyEEuU2yPGd4ZuYBA3Rq0WaGyIopVvTV2qhf0JTTQXK+3UROIA33aSMNIbjtM4GIvhpRSh9XjmkYrPrrwgBjwGHIiAYBu0TK6Dn1X14lWdHBjMMAT82nd5HKmTv8K2Lqt89qey0TF5uGXD+t6l87fnb9EHB1vrSUVoplIszewSl1y3LVOCQy4XAeEd5P7w2qn8kLPb/GQSsCZqKIGK/0SWKTicvytNP9Cyh/NG/RiG7Qm3RtjXHDIL00KEx9VQMXoOl/6Jc1xcLpAIjNhdFmXivvtp/YrR3GcBXWthPHa6K99iSwQEpJN71SoLhUbclOND8A50tSFRkgDckE3lWl72DlLc6l65ISVRq8NCnXs3XSHXaoF9f2YktvPV/JLzjmcIeI2yspaWVhaXJN7k2DUsWbSmQ22ixArH+Cl9Qh86c9XLEbCuYtvUlhacnUwEcTD0FJllp5gVcQ==
*/