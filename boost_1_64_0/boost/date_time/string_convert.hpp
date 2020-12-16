#ifndef _STRING_CONVERT_HPP___
#define _STRING_CONVERT_HPP___

/* Copyright (c) 2005 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/compiler_config.hpp"
#include <string>

namespace boost {
namespace date_time {

  //! Converts a string from one value_type to another
  /*! Converts a wstring to a string (or a string to wstring). If both template parameters 
   * are of same type, a copy of the input string is returned. */
  template<class InputT, class OutputT>
  inline
  std::basic_string<OutputT> convert_string_type(const std::basic_string<InputT>& inp_str)
  {
    typedef std::basic_string<OutputT> output_type;
    output_type result;
    result.insert(result.begin(), inp_str.begin(), inp_str.end());
    return result;
  }
  
}} // namespace boost::date_time

#endif // _STRING_CONVERT_HPP___

/* string_convert.hpp
Eu9R+G2c3wrjEkNcHlR6JWB5d6L6ptsX9hSfrsiFT0I+TWDALvX9LpTs4sNqrmlfU2vRNVfD/9Eej/zlr0gIZ79ACWAypif8cCN6+TJ+3atb5/ouVlU6GX7kKlghNTv7xod1eLmMdv/ldsqjpFVS7jqwZzhfP6jE4H0bmmyqUMiEu7/ivXElfERTKaZ5+KCSTIiY8j7oSVx0FU422OTl8j64KT0g9oPvIBbRz3g9QDS2MVBJOgReW81aYqVMnLkJ0iA9u4bv6m0d4PudC2JHpcW3KhW+xzFQAFeLpEbgNQg8SFIsAD8OgT/5lMC4K+ujWjveT/2VlD+2fjNMyh8BiJHSgVwdxTzAmmdDBFgU8QuwdPwxmsaqmOBKZMJ46ygLw97QHh3EwYSdT/ZJrbSUuAOFbAQ2Nw90GfiGjwwMHbSA3+ZjcZyCP4Jn8jtc8i3mdpABbHiZuM+rIrGT1gYXALNB8egie8wZOfNFHvG1zyxyQHpVVHYTjq/qbN4z5uzSQw9gj58lsHG+sDXrxoV/ycp6auN2OyjTORA5lqjtjdvmkLoTx0SVey1EHMoRc3MxhCpdBQVVKFODCgqrwNjR8OtedpYdmfAQ2vVcgXUypZLTQNDALASYpYBLK0EK6CukgLrIkr+0xzkzq9hkzu1tpNgoU8WWYbHsSWc0/LqXofpXwc6CIIH4nMESXuEelZqEtBogRi/TM5ntLMwqzqwGwI862KpnCVtklOWQ7rLmAMnIaqD12DU59nDsrlyxhwKWiq19P3XFBiMapcDXFJYLAhqWRtp6/7qjejujV3atdlQJ6PpzCsVb07w8ekMdL9V14k8E55kIFfzz4ZYKvrg1dQUPexYqOFavYN27XsOsP0SrjxdJUVANfbEeV9pbZER8RXEdBCB/yuL+GoguYLdgQaMJPS5h3bDWItpbLYYT4Dka8Ryid8N9tmplnpx5mWGxvAjYWVYrN0hWq7XvVqPt6NPx/NHr8zTzx+k4C8x7TMwfae2bE8A/9JmcTovFlkmdba64C+sz+JfKnAqlt3jbaHibeylbURTDTzEIZCDmG294SZIIQg+/3iNtPbaBDldZIdXilQigQ4cUrRUyxZ8gBWSDtTny3prwU1CSANsLEo582ysS3gcJoxfAQEoq+vLXzaL3UEXPYcB1PIFZSn/33xLoic+3d+l+3a4+mr4i8Oku0VekkG+e+YTlGyXacN2fe7c97a2dKUWxWQyvxSUO5UFnfPoVkEFIVsF+WskkVYJZNW7yV8b72tNS2SyKSqbuK+Q/LhSVITVk3MbmA6bwdwoojNV1iZlJ10n108q7+mNVXi2Xh9YIiRLnC5+2d6nQRHouQSFw34+lKFf4uRLlGlzIsYX+tZ7331wJavCAOnGAMdKieKX48DHuPB0g94BPmJeIe8BiLLLKRps0e1W2zMiiiems0XLsXGMHo7o4PLFThNq2rErWPEDLdcR7yTtU+WBlSwMD2FcBOA4AxPbgPFBig8ozUeRhTrYUqslzyUewxIG5ZInrh51LeH2dyj//gzEmOq4ela69QdGtStEtiHSrH/kKT/MzDCJaDlNnBCvFevDXPrEhKKwG4X3ez5FvshrdhS2FCXD+7KLBYUr830D8P/9QMvA6Ie1PFf1vKknNZ8I/6Y+xHiUYSDEZsZAboXx7TY38JLaDrzwZ5LgXVRegxA9JgEftiXqgCG0ZDMQcn1HHo83U+guhgpCBC68DGCtZLMefbPdio4ClffwETnHILeQVc3aD8IpJJSzcPpTEyjpaH4+iMNYaLKWiqAnQRiEi1EVbkQRPwoJV3Ch9PBSSvmLRUD5GQyQkaJgPO71e9yK8zRdf93EvelC8loQ=
*/