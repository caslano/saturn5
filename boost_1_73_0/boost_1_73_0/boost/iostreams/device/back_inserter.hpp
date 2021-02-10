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
OOCWMuFy6DB+pq4BSMU8ZOxASpVewlW0brjQuUeaB6W4ajNN1izfAwjzIt8hJmkSQLhO66GzRZh10w4zBuInoIN4c23FBaPohQog/Omy4h3mVZuYSIYM6LmP/1UwUUqExUGpfT9jmkmoN3cofDtMRAgRZL2D5JmfrRZg2js2Ueqp9gXImwsrD3ZxB2lYJafsCdMOdeQOIXHl8wQEoXZP8xTgYjntmZ4My8PvCIfRSDnZBr2e0XCUZ/SGebM9Dfeeabj5TMPSHZSfBjlft6pw5Y7vLX/ZbsJaD5lUgXvEMPEdxE9ZJw/RrEMEs6rMjojQuvauLxzC9EE/v4yN31rql4qAOLzuwH+vIBxA85+FhN4XvHXaJ5xiv/eWYyckD1ebFnLgjsKwCuUMN7Cr0wp7TFE3csozlq2ONbiAtY2P8qw5CZuubZKOLXZt8S0xs4PzCPqicmcJd/0juLuz8oyzbnnObjHJI3uLC101Wp48jHqzwhxADN6evz+CP6yakZnjh0Mysr/TQlY1Phq5afJ8YMR/Qvzr4OdXx9/R49/J8S8vj66H8iRejGGu5dHGazfOvUc9R2UYw2D4zdGGPvoxODSVePRucPjmaLQUHNg6hv5HlputksWYaFqD16I/eujCn6DiX7uDHFLS4zhe
*/