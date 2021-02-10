
//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_BIG_LANCZOS
#define BOOST_MP_BIG_LANCZOS

#include <boost/math/bindings/detail/big_lanczos.hpp>

namespace boost {
namespace math {

namespace lanczos {

template <class T, class Policy>
struct lanczos;

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
struct lanczos<multiprecision::number<Backend, ExpressionTemplates>, Policy>
{
   typedef typename boost::math::policies::precision<multiprecision::number<Backend, ExpressionTemplates>, Policy>::type precision_type;
   typedef typename mpl::if_c<
       precision_type::value && (precision_type::value <= 73),
       lanczos13UDT,
       typename mpl::if_c<
           precision_type::value && (precision_type::value <= 122),
           lanczos22UDT,
           undefined_lanczos>::type>::type type;
};

}

}} // namespace boost::math::lanczos

#endif

/* big_lanczos.hpp
8NVSYufdbonxEvDVBiIp0LEW2OvMawMPIIkS+NVSAg8niRL41QpD9RW/2mB027IV/Gopsd3p7KVLJMF6oyD4gIFsH+SZJbPywW73QFTGryZ4Tcj1k3JZxngDqxqCUnrypMneuXQeAe2ra8pDNAkAF2Tfh6XsSB7zimtPVqHiCPjP5bmLPJxFeVafTC3Jh6W11VVKbxI5sHbGx6zGWvDrmr1qHe6l63V/E5Siei2Rh4jhY4zxw2avHB/mpnRFxbSl5voqo7QGiCiGqamjLek6io2XqKPYtrQGdbR0BXJ7Yjgd1dOVjn+TDa0119mbw9avrHs9cTfY/vclZIR/Y0wSncrByR3Dy89NAP/vTUsCWGvCROLy/ztn10l9vgrMAXDwS4L2d2wHpk2c368x7DkJCczttJKB0hPo9G+uc8Gu8Q8mG3JpHo15IgnQ3gAzXX13b18b1PYv4r8rMLZcPMZDzORkWz18dZS0eiSzYxHSQThAZ14H1vARnQa49AYupTTKQum2S2rA2h8wTNHxP0R19go9PiFmJUHzRoZLDjKjd9hudzRexq2T1klpzBP7nAfBAK2HQUCh3wHRPgOi89PxvziIdQCBv+icIgb8u7iJlOXnzlG7q9WAX/NqXHHRpEpyYWKWWFtbrckfRqo3
*/