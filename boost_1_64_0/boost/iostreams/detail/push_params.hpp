// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED 

#if defined(_MSC_VER)
# pragma once
#endif                    

#define BOOST_IOSTREAMS_PUSH_PARAMS() \
    , std::streamsize buffer_size = -1 , std::streamsize pback_size = -1 \
    /**/

#define BOOST_IOSTREAMS_PUSH_ARGS() , buffer_size, pback_size     

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED

/* push_params.hpp
42nBrQopi/NWU69XO5gBTONk1rdsDqT4ZAeW8hP3QzuY7JaIDtAvijYZoHSo7qNBfxio0ESbS/V+HBd136YA87/9HiX4XVsAMnERBj4scwadAMkKebcjKTQPcZdZKO5z/UdBfhbATDcdth9sph9sOM9XSpIyl4hkJ3w6wtxuivaZ9U3LmQC9/2dW09s1FGhlGD5p+pzjUjnqQ4ggwhrwFfYXh985t3heUahh4a4fafTgu2/XIBd+GyzvXnLDQXV4OYWYvsAAAfkCeh4Cz3Cbf0liYsOU+R04UDSsWNTUxW4ixOmRRUlV19/HIz82VTQNiOXx9oH11jiPn8agOyljRi2nsEuDlLQ9V27t3xCw1p/GHw+8rwX+CGKgQlOQtcY1rP0iY7jHNBXL44yfQT4cdfT2B24ibZOyiCQu70qgJy/33GpEEQuqyvrpUzbnmDCUzFaIiCzUPWl1EmJTQSdJQ9NKmjWbdackrn+TiYl9wLOL1nmDMYWMCWWusZDBIiAum5MO3XiGT2pVmPJSeocClfFec95wXVINIPKLVOtj/lG3PYariNCIbntYbg==
*/