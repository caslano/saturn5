#ifndef BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct last_of
      {
        typedef last_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<sizeof...(Ps) - 1, S, Pos, Ps...> {};
      };

      template <>
      struct last_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* last_of.hpp
cve8L1R2z0XI0yHyfFrl2aXyfCafzVLEuGb37xWdS1U7XYbwpSFtmlawn0M4HQI7rGA/j/CwAzue2sPd1766yjkvR+nY1xayesN8hgGPLMyXYE9eqnBep3BeCpzXB20LfuvzfzeottfpX0U7XiLa8UZlf94UgvfrUlax37oeviesvWuOgbW0Gjcm8D4DPxRuGrzVwC+NSlvaunSt9XMgfJ58syqQlv4se6dBGL5p0CecM6m3VLl94tYqPnd5DumUxDRaWz/E//2twvx1z11+S7Td04fRnuxkj/Svq2e+zbwmGINXvRvGOARNF8edKGd5Bc66zJH34pmuPs9+N9O2MLq9vi/SszgXJ88H3MNlo3K5skb4bNnuFTBZc2a+TJ+zpfe3qsLPhA9OG3km/KesvwCr4FC3+5iugFN33MA3Ssd5eXV+rETyDPfcRFn12Vtd1t+Isg55PM7o93UfqHLvGb4bcJIX+p7hg44eZ3jNh4eq4O+AcTv4w/OVeg9X5XvnaXPuto/VuBzkOx5iTeQxrInctZ9nw48j7O1w32mZ53k5m/ZPBGNuU+Gb0jbmvlu8Tfg2KNq9uZjz/FnYD1faMlahePRl1ijGiHsu7JEnBL4dFl8shy9mbJy8dKPpqIXEN8EudmjvTPcOZXbAPkcZdlp/IzuIZ1yWHTtj3cQTlOfvTnkKtwFki++jEJ+fPJjfHeH+aPuE/ck8TxuZCWt7zVfY7f9Suv8ZCuv7OM+yLgFdN/15kV4Zkv5vjHGPijWfx9R49xKFX64ydXTr8wrF6ToPKZj/CPpp80N6Jej/t8qFv22hWx9dXy+O9yphB7w214Gnnwu/XzzP+1dhMgW+T4jzWVhqA/b/aOOF/qNwKf1eVnU4IJ6nnbW8g96BTI9oM72D4m77TzJ1j7v1e0vclQ+dPjnu4z1Q4D1Y4kU9ylW+qXG2vZ5Rttc0pgkeuHkPFemTQtIPE7hfUrjfGpdyh3eOlEy9nfOzPCH/4ZRm6jhVnHWsFN+Hie+3iu858jwkzuOmQ8apecA/Pz7yfcSlsEHfgbQX86xVz6L0Euu/Ej4zEVdq44b6bSz02GyKn2TjyRcoXB6Z+DkUX2bj+c2QuaYdbZyhBV9zWX5L6whKnw6/mYObEQ/aFfAJE4QrlU+YI+P2LZSO7JbOnXTzNpd3Qdzene4d6DReYAe2Dhl/SvD5eVRc7CEV9tfp3Esqof2JPzpv73Vvb6PD+KCJc8XZLVWxtQPdQ71JWqTKxZfa+JbBATpjn6EExBMPj+/t7O3qz67LdGxOMnyZZ2A5nu900FUQmrgnl5rKMt3pQbwpEOKPsT5Tt/iFQdy3Zlj/WWcg0sYtMnwdlzmjYUeyhRjpHYc3DSOCT7PNG+prm5evW9PQ0NTeurHKVxc6kscjKutE6lOv4KxqDLJ3hyt7A93uPgmF8aYjYEj2ksOpLmevYxLiDGQAV2buLJNrVwlXjjgJN90zQPJ9UwA4/mTxRhtgZpswynUkeBMXvJln0wP5wTdx4peo6+FR1xfPfVOorjYMn2CgU5rHl+Ek5cuwzPVliP5VqG85/crqjwpbZvR9xFXad3poUT9IEn7PZuMuSFD/Gll/5e+48Pry2OXI+vVwxwRblqPjrPuMjC2G7nun0H2Hh9zHvdu8OUnh/zh+0XEPLA47H3CvlIXB4h5YnOeFs/i9S+VzneeFy1C+ejVOwx865ZU+XMk/XNzV33cehTyiDp7S/ytN+R3/2/69oUctbI+3DO+BroqPZU1ve6q/KsaaHW+BrtgLHFIDWzTP850g0k/cjlTPteBTE/gUah+F9jW8WyZsiROAQ/obbo27/obbEDblmCjGyXU2L87YyzY=
*/