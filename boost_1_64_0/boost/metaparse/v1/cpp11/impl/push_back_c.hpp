#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_back_c;

        template <char... Cs, char C>
        struct push_back_c<string<Cs...>, C> : string<Cs..., C> {};
      }
    }
  }
}

#endif


/* push_back_c.hpp
aj33MjnfSv33TExfVp2uPtrBfyPZM8vbMHYs/J5G7+8zL76IPo6DzWF7Hxgxn1YM5mGcJdk9vr6/7pB1A1qjxVPitpfvF5FXKfDS/PYXlqPGVM611uLyj2FXjx3q9xGRkDddfsuf5+ap4d8Rpw+pMWO0ie9s2WqNdbT1uIV0aHt1tj50Q3XkVvn1Mnuf22wdaQNsPUuv4PH66ThSD+RuPfdLYMbn6TRTZlrhQbzeXKymWpu5Ri2mD7NKzbG+PY6mnS43nyVi6nc0yif2U7QqD6v0KzrQnkt78N3D7LyA3pihhuOTUe/CPX3gefTbM1PNUV2+o1NEHSY+1GCpWeX3qzBpCaxbh6Nqwcqy7F6IHfRfS08Wq7DkpWvsCu5hPP2Msxit2x0nXY0jWhnbJnye6Hqz8EF/PcLzatHSfKzP1Af/D1UD5voOHs/WW7gZX7+iL15bP3CdegmOjVSY1pL7g2DJwN7mVkndTJ93mKsmftgYH3SO88YtzvurKzKvp6/gfSfrfHnUtZe/IXdq0Mhyb205eF6RFqaJm+lB3wJzonD71ho4xTUTcNL4+NqW645x7h5HYXcjmpxWP6X2Xil35/Dtknrme9J5rVf9YaJ+lzEO6qM+/WMk1MQJGwvzS1W6SMwc0O/OPoQmoZfnypOkZD0jNs3zov0gb6lPjhuXMb5tLWX1e/Q0TCrHJ+f9vghWzUnHJX/UE6ZtE/FI6bvlv/q0c1x3msPpG+TwPlgjF87MUS83srYgFhqP0Gt413eu/KXPQZqFlDX0oXWwQtZ2GtnrUG2h2Ctk/l3oVLVWn9Jyvg+9MgIusl3Lu9kQNpY4R9ucjmb09u/NDE+X4w058NEg+SwHTlh329YJ9t8Ba/LBZbHVxXmr1devpJUniKfPeqjrxfZrehZ736ax9WYy7Y3oYelDTGXTgeplti5Z1jrAJeLUvDrgihdowrz0fCnXnl9ZDMzUK2xJQ8HmIeq1inpxV3wgd8VdEdrqS375WS8++Zj9LQm0PgyuRLfUhf+PwNN8NG3fN+xNqBusS1hPsvaWY5H9LnEDqeW7t2f/vXoM5tbJHAY+ASv0wpr1ZqPWrrlC72GAWIcrn8rRH/FIhwdc5wlYLa4a3hY17hAGXqUP9BGtNMl4DvkcNoRFNOqgYL8bfrqH/2s6Jr+8pfsrn6XzaKqO8Oko/dBbfE+F6aPe1GsrACPzOG/VeG/PMcb8hFg4rcYvO08clGYf12lZiZ8vCyFTV+O0Vn3VC3hkHFte5TMaOF8q7D1ofg3in+lViqHfVlcfVKBZtor3QfL8JP+uwtHG/Mc/wLiAp/19wFu0U+O4NtOnU7utiffVXPcA3yXTzDv5r368p/oOzMtOBxVnH7G8rCkbtIzoXYvbb2Lhfj2D++F9kv0z53PILzrhfdrwSF99+o54PgE38sWs4XoSvXC4MX1Da3z4bQhv9deTaQYTluLG+8y7rBr7c9cfag02lzny4xF8PaiUz/lv7TKxQ8vloMuLjrLnkL8/EYPH5WU/uPiD7z4Pw56TE5MbyFM4kAW/5tNLqVxZTO9w3FHXTrDeS9utozU7TLGvjg3uf4bWKE3r94MbX1jfFHuRj1xfHiYb42cnaJju9Lhae8iHdPUD8uMo/Fvh7wPVRmz0JS3VTl+jgTFPfhM/0Gbz24ntdvR0dtxTyHpAFfpygXXWs54ZW9Ga5cPs9YwcOCl2voBjzrNMzPy2PKxZIgdK89OlvveT/NKnC+Lw1vy0QT0ajj+fE3eJteAzzNkfn2e8B55f75YOKF2Mvv2cDiuMm5vQNHoVufDgWT20qkfElp+j+akWrd4wvqZT2/m/ZesiMDCZ5jgsX+XtMXtMOsE=
*/