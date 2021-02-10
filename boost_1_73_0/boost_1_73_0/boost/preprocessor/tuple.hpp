# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
# /* Revised by Edward Diener (2011,2013) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_HPP
# define BOOST_PREPROCESSOR_TUPLE_HPP
#
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/enum.hpp>
# include <boost/preprocessor/tuple/insert.hpp>
# include <boost/preprocessor/tuple/pop_back.hpp>
# include <boost/preprocessor/tuple/pop_front.hpp>
# include <boost/preprocessor/tuple/push_back.hpp>
# include <boost/preprocessor/tuple/push_front.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/tuple/remove.hpp>
# include <boost/preprocessor/tuple/replace.hpp>
# include <boost/preprocessor/tuple/reverse.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# endif

/* tuple.hpp
AAABAAAAAABjDQEAY3VybC1tYXN0ZXIvUkVMRUFTRS1OT1RFU1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKITe2G7gAAAHIBAAAXAAkAAAAAAAEAAAAAAEASAQBjdXJsLW1hc3Rlci9TRUNVUklUWS5tZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJPioOCgDEAAKgGAQAYAAkAAAAAAAEAAAAAAGwTAQBjdXJsLW1hc3Rlci9hY2luY2x1ZGUubTRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSrKfZedQIAABRKwAAGAAJAAAAAAABAAAAAAArRQEAY3VybC1tYXN0ZXIvYXBwdmV5b3IueW1sVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUutn+UZuAAAAfAAAABUACQAAAAAAAQAAAO2BPk4BAGN1cmwtbWFzdGVyL2J1aWxkY29uZlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKSM0qNCwkAADwfAAAZAAkAAAAAAAEAAAAAAOhOAQBjdXJsLW1hc3Rlci9idWlsZGNvbmYuYmF0VVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUuqjSl+vfwAAeoACABgACQAAAAAAAQAAAO2BM1gBAGN1cmwtbWFz
*/