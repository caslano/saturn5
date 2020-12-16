/* Boost interval.hpp header file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_HPP
#define BOOST_NUMERIC_INTERVAL_HPP

#include <boost/limits.hpp>
#include <boost/numeric/interval/interval.hpp>
#include <boost/numeric/interval/policies.hpp>

#include <boost/numeric/interval/hw_rounding.hpp>
#include <boost/numeric/interval/rounded_arith.hpp>
#include <boost/numeric/interval/rounded_transc.hpp>
#include <boost/numeric/interval/constants.hpp>

#include <boost/numeric/interval/checking.hpp>
#include <boost/numeric/interval/compare.hpp>
#include <boost/numeric/interval/utility.hpp>

#include <boost/numeric/interval/arith.hpp>
#include <boost/numeric/interval/arith2.hpp>
#include <boost/numeric/interval/arith3.hpp>
#include <boost/numeric/interval/transc.hpp>

#endif // BOOST_NUMERIC_INTERVAL_HPP

/* interval.hpp
Sb6zf4k+LlvDfdXRnwa7mPmhDX1msEKRS2ahXwx2r9X4fcjdYClyZXiM/AwWW6OHFXPQYKtq5cL8DBjsZLdozEGxVG/F2w0ug/wMNmTA+R7Iz2Cz09WohvwM9vGbuJ7Ij8yl2RBa/n17NeanWGYXzZklDHxfH2NEllOz5IB9xyrvQL8YLHVOZxusf8Y4i9OE+pbr7eq9T1+wPpBFwPTXe2IUFsvNeG8T2f/fT5t8fJBz/aBMyG8lnW8KaSX2PZuEfQ7ZzBBpsw4n1sJ2YrVdFGJxDY+sbIgc1tjF+jBpRz5VxRiZN2rbVs3K7C+SC3FkmZm5WrQ/jhzILMx+uHb5b4wtWSSzWke29sMYkWWEGb49SrY09F8bmHwO+3hlS/TnVrtICJP2ufGJxRiH3Xaxh8U1PTfQh37ZZxcrWdzR9cNuYU4csYsl4dJG3vwtBOvKSa2dmmUpMR3rnzhlF6WYnX5c2I92kkXADONO9iOz96/bTEN9ZFmZvVmyeAPGKNEu1jH7es+kFsiPbLVmA2hZtUvuv5DfaTrvZ9a7i/c4yjxLcSZpUbPHnsa4n6fzP2YzQwc+x3b3IuYLmX6++MiimHW9ObYO2kKWGaafS+KSXeRg1u6gZTXaQmaB6edZLFkkTD/P4skywgy/7ZLFa5a8gX8yP7e89/yyXbxm1uNhxTMYvyt20YNZm8Pl5mIcyI6GSDv9tPYEtOWGXZwwsfpyrKmNPgvQMTQzy63wFWjLHeppZuVMZ8qhLXe1sdVsTZ4Wr7GO3bOLg2HS7o3z14Y9totjodLGF+tVB2Um2UVKVt+4trfOoZ3P6JiIWb2QTwVhL+yirpB2re/p3JhnL+W1oH7J+b24cxrjQDaEWcdJR3/HuL+S2+S+tJxxLTQc7SSLC5V20N2qJMp8p48TWXMgdz/ZWxY3Lzz1WdhnO+4LSj6oGd3/aRzGgWZZMWZlS77AGHlNkaKSZr2Tx6FkL+QeHRopWglpj/9OPRB9RnaXWS57p6FYV8IixbxQacd3LF+J3FNFCptWX/KGZVj7tvI6ZkSkGMTs2z65J6CdaSLxXEHy3LftG3MN+aWNFMeY1T6c81dYukjR0yQto7/xB8z59JHiktbO5B178eYnZV/bI0Vfk7QRKx89RFsckeKbr/+1Hsk5FImKQn7l9VY7dFlfec0xUgxxSJvU1t4c+4DhkfidpHuyDcuJcfCRFdasGy1LN3y2HzmQldCsKy1zHK14W15noLZo9hMtf9l0Rz7jRzZEsy6Ga79OdySuUXdOPs+59/466vslUtQRMN016tjRkSIKZniOnWyuCaa7Ru0eS2OUT1qhuU/XYv3bEYnfV36k5Z2B/7zCOJBFwgzvAyTbxKzznJMtELczUmSEGfbhZMHqi90VKWaFShub8lNJzHm/vr4MHTquxvjto36B6fslkYz6Bdbr46cA9qkHIkWDItIWZcxZF/3yJRLP/HSi5aHCHc3IgSwSZrh/KdlM0py7C67AfDE50C+dDP3iIgtWnznEIVaHSXt5P/1D+fuKQ1ffxkVu+e7oVA70SyfjfCE7y9uZo1N35JfaIVKnlbapTMImtCWLA/cFdaTlja8TGyGOrJZJ2p+eOjOR39cOcYNZw4FPNiPO6RDhzI7cbRmH+nKgz8j0fRZNdp/FPXiasia287moXxBn+L2fbBmz9h+PP8a6ktshRjDLH75DPveSxyFczP54OuQs5jwZb+fSXwe0Rn5kJVk7T394fBBjlM+B51qTt7+tWt3sgrlLlmiSViquxDO0pQDyIzM8V0d2IlRa42f1cC+qiNb6WjPf6SYb0JZvHeImi2spavVFX5ekcWdx36SMlNcASztEbSHtzg8=
*/