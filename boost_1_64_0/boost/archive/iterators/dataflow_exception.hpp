#ifndef BOOST_ARCHIVE_ITERATORS_DATAFLOW_EXCEPTION_HPP
#define BOOST_ARCHIVE_ITERATORS_DATAFLOW_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// dataflow_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifndef BOOST_NO_EXCEPTIONS
#include <exception>
#endif //BOOST_NO_EXCEPTIONS

#include <boost/assert.hpp>

namespace boost {
namespace archive {
namespace iterators {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by dataflows
//
class dataflow_exception : public std::exception
{
public:
    typedef enum {
        invalid_6_bitcode,
        invalid_base64_character,
        invalid_xml_escape_sequence,
        comparison_not_permitted,
        invalid_conversion,
        other_exception
    } exception_code;
    exception_code code;

    dataflow_exception(exception_code c = other_exception) : code(c)
    {}

    virtual const char *what( ) const throw( )
    {
        const char *msg = "unknown exception code";
        switch(code){
        case invalid_6_bitcode:
            msg = "attempt to encode a value > 6 bits";
            break;
        case invalid_base64_character:
            msg = "attempt to decode a value not in base64 char set";
            break;
        case invalid_xml_escape_sequence:
            msg = "invalid xml escape_sequence";
            break;
        case comparison_not_permitted:
            msg = "cannot invoke iterator comparison now";
            break;
        case invalid_conversion:
            msg = "invalid multbyte/wide char conversion";
            break;
        default:
            BOOST_ASSERT(false);
            break;
        }
        return msg;
    }
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif //BOOST_ARCHIVE_ITERATORS_DATAFLOW_EXCEPTION_HPP

/* dataflow_exception.hpp
UtJT4lDywvTpCp6Sr5z8i8pKotoYSRVhlJMAXYtqJ0x8fS2OBNIhEFhuDGGr8ISNkWKT04AjFdskxYb0ZT0CJW6FFg2Tkw+Vvc5GZ6vkS2+nTg9y8qvOJ8kUnmIzUr8kTFLl+//h3zeoH76Qn8DKUlv7K52Lly6npl3589X0a9dv3LyVcfvO3Xv3Hzx89DjzydNnz19kZb/87dXrN2/fvf/w8dNnjsCM8hnnL1DQpFDhIgoqWsy0uJl5iZKlSpcpW658hYqVKlexkKpWq17DUv5fs5ZV7To/1K1Xv4G1ja2dfcNGjZs0dWjWvEXLVo5OrZ3bqNk62qVtO9f2HTq6dXLv7NGlq6dXt+49vHv28vMPCNQE9Q8OGRAaFh4RGTUwWhsTGzcoPmEwfGdgzMjI2LhgQROTIkWKFTM1NTMrWbJ06TJlypevUKFSJQsLSape3dKyZs3atevUqVu3QQMbG1tbe/vGjZs0adasRYuWLR0dnZ1dXNq2bd++Qwc3t86du3Tp2tXLq0cPb+/evfv27dfPz8/fPzCwf//g4NDQ8PCIiKgo+pp2bFxcQsLgwUOHJiYmJY0alZw8Zsz48SkpEydOmTJt2vTpM2fOmTN37oIFixYtXvynPy1btmLF6tVr1qxbt2HDxo2bN2/dun37jh27d+/Zs2/fwYOHDx85cuzYyZM//3zq1JkzZ8+eP3/pUmpqWtrVq+np16/fupWRcffu/fsPHjx+nJn59OmLF9nZL1++evX27bt3Hz9+/sw5UwJXggUFUwoZFLIpMC5/6E98LDIsMkyzTbMJWRAyZRn0yWbZCmIW3IKb0ocrF8yCPqbMVEakzjN4Nn24cqF680EyE+MNI1oMtRJhSSxi5FlbIkw0yQkIS4TFrGQtD3ASYaIZ0WKOJprkJiQnICwRJprkBIQlwmJZYCYvCyTCRBcCMwLCEmFKj+QEhCXCRJOcgLBEWCIGpScyJhGWJLK1JiAsEab0SE5AWCJMNMkJCEuEJf0sJKZcwvIF0WLuNhJzDcmNJcISYZITEE2Y5PJKlexqEK5BWFYkWiKa9EhOYGRMcgKiJSAgmjDJleovQdGaEZRQmoFowpJUwpjkxiQ3lghLhElOQDRhklPaZgQlKG0zAqIlMwKiJaJJj+TGJDcmOQHREtHEJzkBpadaqytLa/2ymkCXwXwEVDDCVBCS5SMwIlk+AsEgoJIRNiZM9gREEyZ7kuUjoLucsDFhsicgmrBYuIneROkRNiYMhRgB0YUYgRHJ8hEYkSwfgRHJ8hEYkSwfARiRPQGlR9iYMNkTEE2Y7EmWj4DSI0z2JCOa+GRPoN9piS6v9ESi5S5upuwU6J85EBBf7AEImxMmmoLcRJRZsjcWBSFaFIZosicgbA4ExDcDAsJEk72oMGpeuRJZCXnbTbQoFNFgZkRA2NyIgPhmRgSEzQkTTfaie5A9QQljURFEi8ogmuwJCJsbERDfjPhEkz0B8Q0qwNigQEQqtziTCKyVpT5hJhFYG1aQYYFJJhFYk0wisCaZREDYXCKwls11H0aY0ieagDClTzRJJAJrkhGm9IkmIEzpE61LmoD0zAlT+nRJQJjSJ5pkEoE1yQhT+kQTEDYnTOmLoHgc6E++n4kmbEJYbh+9B4XkYpFMcqIJi1ojVTFiEZYX3UQTJiC5uBlILjqlibL4JjnRhJXFY2HhviAsbjFjogmbECa2EQHJhcuD5EZGBCQnmjAjIUHhQoQLEWbGRBsTTZiA5EZGBCQ3Ijnpkx0ByYkmDPoBwISwiUzRh2j6L+4A0TTU4wkTkJxo4pOM5PKUQQBWhAlAIikBWBG2Ij1JbjqwIkxAcqKJTzKSg36AMSFsIsY=
*/