/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/restrict.hpp
 * Date:        Sun Jan 06 12:57:30 MST 2008
 * Copyright:   2008 CodeRage, LLC
                2004-2007 Jonathan Turkanis
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the class template boost::iostreams::restriction and the 
 * overloaded function template boost::iostreams::slice.
 *
 * This header is provided for platforms on which "restrict" is a keyword.
 */

#ifndef BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED
#define BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED

#include <boost/iostreams/detail/restrict_impl.hpp>
#define BOOST_IOSTREAMS_RESTRICT slice
#include <boost/iostreams/detail/restrict_impl.hpp>
#undef BOOST_IOSTREAMS_RESTRICT

#endif // #ifndef BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED

/* slice.hpp
3T3umsh97D/nu7ufHJ7IVNGRDW+EC587xkjn7wO4htqCkUFLHhlbBN2ntzdgwdbWG7a2mxyrX1PAJBDSavRg8qs3vadAIHn4Hj4B8bgKnbmd3QK1f0f6vWMV3uLPODQvcE2r98MJB3zburxbrbxrRRnqxhro6+d7Fj7/U8hfi1fs/mgSo4ecSdiIpMBrQc+9ndSs4fT9BxdKhiDfn2pzdrUZVWUnlRVn7KmtY6Pa0dJBMs6u9tMzE+J/PQoLx5bW8wMDb8XidSveT7NfgE0If23h/++RCot9TXL08XflJ0YQeUovwV9pn26o/8ILMfzHP3HZ//0MU8LcxNiK81/yTz17nSGXTej3xBop2Xomgd8+imPYJjqYDlARX80jqN+RT8LyYCLymEawZUA/lmChnnfFsSubYRHoY43nfp8NKwn0sGXWzsLBJTIoEk7NH7sXzYUJN7BWFnOmyq6qkAkqEg2hHRc4RGfVtT3sYlJTBCYKu9N4Hba9uN1nbNSZuTnUPmS/O+yxvr8uvn0MyvWKaQx00nHVaAMJZC6nx+Ml9rvosBE1HHbiduRxfOPsd9ptkm++BbFPeJDkkc74m0tyUayHt6G7UQHg8QyIMNK/r+FGX/w4FgllBfJOJsjQqH0L/8IGWLY+1vgTYG3IfZ9G69c8e3Z4QBZxUpP4kP8e59Ml98b5Ve1QTEWjL49poijeSNdN5H730/3w9hea
*/