// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_ASYNC_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ASYNC_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/decl.hpp>

namespace boost { namespace asio {

class io_context;
}}

namespace boost { namespace process { namespace detail {

struct async_tag {};

template<>
struct initializer_builder<async_tag>;

template<> struct initializer_tag<::boost::asio::io_context> { typedef async_tag type;};




}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* async.hpp
cmXtrLxml9IvvGNIzNTLbArQgyq+DJ1axr+MaJ0K7H2OChh/Ti9MqhFLlp+4pGeWeSTL7b9sBJRiBjy2f9G+0Ygi4Khku3NRCla6vOKdShwsSVMsHmRnTOIp/rILlWp0Q/yy4cgr5gvUtFoT4IRMPrC5TVwVuV3ODOKLrd73yFEA7q3daPzbWc+GhZ7bnrO6EKwugo/IIOa/99WzweD4+N98tUk1SbNvslAV16eTazGKAlIXGzGyVQ18ZQV4R1xklOJONcjfJ9lsxJwqHKxajfzOFmE5uGk4P0RWOplSaVyCq0PwxjktmhR3XX5adNlBBCAVXnfMKwYsjHWinh1edxL8P3FDOKewyNO0rIqtQldsDH2QTApTFjnoYO3HsrKev7fTz7Zq7t78VhRTkJfe0pqjalUhMSrGUZkTOKYS6etUdZqjNB96dQdmFT407nZ8IqcbVpHehJLvQ6vrgIKpW8jyW/DdodWmMZxm8THwNutEWITu/R0vmlrEwFl+RDyWOX61y26hm0c2YBKGkSGplEeDsZR+u2pDvwVU5oXB8Enpc34w02VxaVdlMD8/4cL8qK0Wy5Hkb7g/HwG5HsuHTRyP1khLu3Yf8FGNNPO71nAguB4/xp0t4FedyiKH182txk9CBoJIGg8azGdb1K13VxAnb/vyUnEAyO8c7UnlKUdm/lIA/v7vND2OuEvYSC1HXZz1aKsEHB0Gs9/1
*/