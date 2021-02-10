//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_E7255CE26C1211DE85800C9155D89593
#define BOOST_EXCEPTION_E7255CE26C1211DE85800C9155D89593

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Use with parsing errors exceptions, for example in a XML file parser.
    typedef error_info<struct errinfo_at_line_,int> errinfo_at_line;
    }

#endif

/* errinfo_at_line.hpp
6bg/HE1mo/Hw90t6Qa2TM/pHVTCpX7aoletrjjqdRS/OomMM8H8zJe1mZpXj+OIXVLJAiz/QoPOpK/Yhr54hlAhQaW43gQx+aXw5GI7iXiz+rIskr1JFbxi7Jln2i/AwicH4/SMPeIaeZgh/DhbsHQeeZbKkp/64w5/9Se+68fm4N5r0hgMRwxQO79W855dczUfBKJqbmgbVMjELXXxFDv27UtbVWYIkkgsFijRpdg2mivowRpBUVHn+jDmkC8lUYFIAJTN5yk+Gzox1VACH45sax8uKCrmgE5mL3ohkmnL4I+psx6k3Wv21maFFBQicvS41the0Bm+gDp+vS5ncKGe/REJMwOylSpBotDTIfUBBkmoRYe56w5A+y6VCBr3+zIu+8CXYRh4KOcDmCjY3uIAd9sTuYYYsBwNknm/YsPpkENeb5nGsYu85JeqV7Py9oI2G48nBi0PEIqLenArjtihtaii41nkOSZzLKmdVEZVlt3pjTo5fHfv4sYmQCvZBY3ATB7b0msfUXN821n22SaYW6gvEje/feM0rK91o7wpRw8BxYAnSUUTjWEQIFssiNooPk8mIq9/tJqJ3wb51htgUQPT4FExDAmyWXjPu7hfdQdkGK27ADjppWov/WXT6PKqvOETQ4rjfpl+L
*/