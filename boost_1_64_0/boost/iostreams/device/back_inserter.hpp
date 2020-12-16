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
Ij04vl7WYys4rl4hzdgKG1fDINJsTCW0MqYeP1uPF5XeQ1rGmB4/w9X4oc96HD/0NeP44fmWsluxyis2dj1/H9lZx3WrXwC5uTec2PQ8UT3hKyjhRHN5Ecdhfbzn/VCmsSN5ffr9M2dgy8Pptp1afyYXevYZrPOa5u82El+B74ttdyOjsdW2sLqWl4Tem57KesYjfaFSnnvTt5T+t6wxlH49YmoDZepxlSlzSI30zx7wLbX+Qt4TOMIwJ+j8zj5ZUryKcxnHGNqjdO7kjCeeuNROalvfUsfxGs66S/RY6DJJHWexXZfgMlIJatkoevBA4znWe6rsQu55+x3lFlMq25cx8YHSyWf9UOs8qwNkuS67gz4v/EjpLVH+AaPpL6/T+V5V5zOd/Un4B9DesGNgmugmsM9es3WTA/54Nmo47iq9kSG9DiUGHdWPVP/5JTrje7Q+1kJjKVWNJbX/9VjKlPFV4xoLyVLIY3If9FFkKLqbJ4X1r+rqWsaS4ZrG0JfI7z6WqPN9PQ9/U63fQT+Ps25FDP3JUYaeM4u5cJN9Bifb6zu7+4Ja90eVdxo2Gqrn+LOVfk9yxEech1Ph31TeucRNJujxZAXtqfvxfUrnG9Y4ytqEOPpbER1Oz992/7H9ffp3C50/dfP7kv3JHc39R+nmhHR9y/yE55nOtZReWTc5b0v+jKmPKZ1NWmd1mE5f0onSx16nj/0K+bVQ9zWjj6Cn8x61v1mm7IBtWKZs02x+OyrP45eofsSxExlEmXWTm/rfMlxWCoK7Se23W1OVD7YsMfY/ye9z91Xd/zao9blWP3paADH0P8owng+ZznHQNZ7jGM5ftK6pD+p56stKZypj0kc/9Lmvd3Q/vEHpzSbdkXmvo+t6qvV3n4X8QWyb9tI2lX1p2L9+w3HZeA4r+zdbHq68i/RFXkMGU6Y1xbh/C7gKC7N3XxmXA1WeZ9lmN2s0cjti2PdStraZ8sFw3ntJV+tHMRP0NO538uv9k6EK5NSrrKi6zOH/9hmlczXnEJP1td5ralmyOoYcoc+XqPRN7vlJ7bdlat1VzDKpznsJ+vj3BbV+Cc9bU/Txr0otu5z+tkTVLSFNjpvBuqm2HJU55y3K29IzNI8U+JM7+H2FXFIarydFf09PmSs6VUU8Hv0mnT6HbqP0rf7m49F0VChjihr7vZQt6WeGvqPeV6vmhvKQn6tqA21jmbTNdcxa1Du4kV/76EvweXg2fSrrnKY+tbKoprhMjlmUHDyG6D7FdsTOeSrPw77Z9IXLfD1M/UnK9ek53uc4p0iFc9T6x3wL6I/Fvm6GPqXLcJ+f6f5wkVp/j2+ANcdnml+c+YtV+0uWcxWp81ep9V/g2XQv7Rt5X7b0Y/rjHmx6pdL5im+6b4rj2mllCVE1Og7mYaXzbennaKt0KldmKT47z8juwWsNvu+gj8MvKp2uqsxP91Zlal+4vWzXdZ2m8/02W+WTNHdDVbqnc7zoev1QrZuox9oHKt3Zsu+fBNgJ69Pk/My3dhMHTb9vVMv3T8iD31fo/GvtNnd/D/nTZ1PRzT24PpB7CbfAR+FvydfoOFbOinIcFOtx0DTXyjHSGZ/iPpdT9sTGLMPGrnExKz240XzZeB4yivybz20aF1xhtel4GizD576/YOzrWlf6C9fbK433mJWu6RhrPG6iazzGmt55jm7rx9gHlM5Z6HQlpsqn++GTanmXUN9hzkOi8B03HksN17h+iH1Ypuyjj6XuOTLVcHydKvv8w/Rwf8YstmNNDfkzqttEC2fnzpw7Y8EM/lQOmMqGYzNb9GWkjLb7X1K29k901vdo3/D6jkc3JWJ9lfOlp/qmTPXue5kyte2+l2M=
*/