///////////////////////////////////////////////////////////////
//  Copyright 2019 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// We used to use lexical_cast internally for quick conversions from integers 
// to strings, but that breaks if the global locale is something other than "C".
// See https://github.com/boostorg/multiprecision/issues/167.
//
#ifndef BOOST_MP_DETAIL_ITOS_HPP
#define BOOST_MP_DETAIL_ITOS_HPP

namespace boost { namespace multiprecision { namespace detail {

   template <class Integer>
   std::string itos(Integer val)
   {
      if (!val)  return "0";
      std::string result;
      bool isneg = false;
      if (val < 0)
      {
         val = -val;
         isneg = true;
      }
      while (val)
      {
         result.insert(result.begin(), char('0' + (val % 10)));
         val /= 10;
      }
      if (isneg)
         result.insert(result.begin(), '-');
      return result;
   }


}}} // namespace boost::multiprecision::detail

#endif

/* itos.hpp
DYQTiKZO+sTdlKsDshxBSLnLWV6Zx30ZezHUMqgU5FF9bfzsyUMwoL9Q05mpl+eStGW49qeHMyHk+wB0yKLSx2n8SV/OHa1l9NovUm4dXZ4sQT8D8WIQT0cyzSWzaBY2yvW82zvElGa2tbJThm9IpG9JLCzxbNniIW9nYb2+A0mJbtZjbTVQXZ3/HqnpGxLx5sTSaGxw6zO4XdalltfVph6Ka3163jdudOVsa+5DNFqQ8y8czvOFvOHGEGuKOu2pyX2cnE2xpd+P9BKRzDgu+X+mu1M8H/yZPo3K8UTGJCMXFjgjY4OuJl2s1a/3ZdzmievEdCZRbOG3om+gdjHGeGc9Jd7u01ks6W+hMoNSTthAa0acocxvozJDkNT4ZMkXwFSzK/Pj/Xn3tubayFqFWs+d4Y2uL3O3zjfNlA5kX0rRH9ROINbsx57SlVs8sz4bU+s6lPtDVC73MVApm1Xu8REc4vpyf4LawGjpuPGSfJhvD+9Mv+947XrHJGORrerLGR/L/SkqN2ehYzaeXBwO5f4M1ZcZ4yjNfFXf9eH+ZGvyT+jlMyncpGicbBN+fAw/hu9yhFFSosJkuar7euGlcGd7A71jMh6yLHr5XA8DrpP/GypfilBHZzQrDuvFmYINy40xRorzOrvamdfaElyAndcre6xgqLZWxakfgMs52Hn18u9JuR0ABVtygUHZyb8Dle90cM6UqTvW+8w52PC+EnORkhqePG8j8xoywOUewuIt/aWx7dhGeV+5r0D+gl4+khCT5qWSKUwuO2ZPyNXScwb3p7i9CuWcCrJMnw+Tp+ubr835NHNcRc4/c9z4VBj68KjiwKjv5nSvuyeE8t7kFZ115pinSLB/wXw8S4IV6yY+Ox0fPmH8FGF4lmPQLK0IVUuFFQiFs9rAR9Danzb6NZ+dGR/4Fka6ktSOVTmaZU7nUqOlfrlGZa2P8MdHka5UIb/jP3rd7aS1MswuslpijH8hDEEUTY47Wsj5qvy7O5+pCPU/aww3zYVX4XNLcsYUk8M1eTDfwO3H724vasDd1PGQZ6ovK5Mom4H9Kv+2MEuSB4d4XwsI3xEutNVCaSJOPlsNQGp0snpKq1GgN1GY2um0L2OLRWcrh0J4Gnw1zhGWIFHzHG1e1O+kef49Oj9vZnb3DiBeJIc7/l43kGybnVYwpJqZPDh7uI52CvH7evlEuE8qZF3fbGsU4mqveNIlvLyE/KC9zq3a27ywqAkf1+8f43YOjGuluSW8HinG0sEWuNeJJBVmJG9v4PNwtNA3vx7GhpHOBx/CMvrjMlBm84OubbDw8ehCvMMY/hvilHn2OVFHwsQJ/DMQliWqRa+VpWEtQQ4uD09O7lU/oDbj+IeDwvye9Wpshy0F17qWswj8f3LVEzwBn7l+Py4k0hAUXeUNq3bIi++gL1+Ao96HJ043eqytQJ3gWdW9cOXOcAvivfwBlS+cZ0wkDeXvbeHyIabHq4cYXl5wp2Izjm158y+qeemXqkn+MXDqbIwfY0wvYmRZlgmzfusgTMgVvNtj3ooumpCjJ3n6zpn66f2oboZo7mhIfsjx9eHjNi+WOYqxb/THkT4jmvFUTAgoxvGa2DHESEJ6qhkl8ZBMxrj758eH9RAMqOu19Ju4z2KQUlFG8keWkntwP4xwOCmG2fZii3CwwSGB2DVD2wQaI6VxCN9cPSuu1gRhjxlwI9XMRW0wLjYihfuAQVdyIahPAuliY1Bol7/3ureFSjFKFtpRcIiJPGCInER0VGMMbPwJMTVfg/fozEpMNi823NX+CSoQY77XCYS1xPI50vZxVl/i9iCvTa+z3esU4rhmlDENOF2vwXg0VQfdGUvvDZNuAmo=
*/