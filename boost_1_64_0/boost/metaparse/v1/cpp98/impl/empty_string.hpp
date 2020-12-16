#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_EMPTY_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ignore = int>
        struct empty_string
        {
          typedef empty_string type;

          static const char value[1];
        };

        template <class Ignore>
        const char empty_string<Ignore>::value[1] = {0};
      }
    }
  }
}

#endif


/* empty_string.hpp
X/8Saxe24dvSnm2Ebfi+pAVt/KS68x3x7nPHT+pzy9Q9eOs0uvX7zxe/c+0Bs0899p2nVyx4+3rRb0JtKr2kJt2RiU2ArsQ3E7BgEzqLXru1i+0ibbCDP2KE4fzhB2/ELYq+rJi/t+YPP0TN/PDz3NzJfb7J/7/J/7/J/7/J/7/J/7/J/7/J/7/J/7/J/7/J/7/J/7/J/7/J/7/J/7/J//+f+X9ZbNPB4k7qntsKnYGw6IJoW+pp+xltCdp2kW3Yj8ExfsaPX8R/mWwync937Tlp/KTxEzsWJdOLRbSzKBlvS2RT49vAHx7rN3hjbtSjffw5mj/C8qA9wAbH+jAWdxOYQ3SILy3khKHdWbZfQTtRe3xxshBPJ5cX4slcLpOLd6Vac4ncihhjg8fPlRIv2yNRGHu0hP1KwroyiXa8TC6VXozvd+DIiI6hxr4aeGNTRbw7WehkEUJGI9g1wKpKwK4DRpRfQyqYZ/mUL0rChOzGwvWsMmEdXYlgvSFNfmeNm06B1JMuhnHrwOsAMd+pMEvhtSehQGaFQgzXfJOJB0kUjW41YZAkhpwA4+d2AxawIZtLLV2SXGGse4rEv8ODj4TF27pSXCaJtyVz5n7HyX53m/3autvZS0faoN29Fk4h1+Ud64n+SmbINRpqIrFQPLxPl4uOXDKpwVYLuSgB+xOw6eTo+XSWIQsduiw+ImURVZaiLpy2ovODoZ6AYMk5a1awrkSeUAG4Nu/lcmyxHakkkf5dDKzYXlQ/Nd8Top1MvLk+3p3oovCn6eyTwJal2pPxQiaeyLfFwvanVR92ruT6hYj2qDNqury4N7WGlyVdUKN4B3FV2O+f4Z5FyITkZJYyaS4fzfeq7Ccm0/XvNaOfEJs8NtE3ZlsmXUhgthhU6/+G2gfMbyfUU3L0puyPBC1HkoJlCS1GzZfHlBy9XQoPHA+NjwporHj6Vdh/sd7XkVNsly2pij6b4Tm6kul2+NSa1vi3xSDoVhdvTaXLaVfr2Yp2ZFdMOTEe2PPIBmwTwRQDyyRs22A82Kd42l/iU/QRgGicMq09zzyC7uE4A4NxYKeadzBt9Q3VdU1NtdiBZCKdV7AdB0kaiR5xrIq2l53lPHm13kgeH4t4g2iwI6yKoG5Etwn0FXIVaKna0yTa28tT8QV7T9xXtxnltIu24lD5ntYjyKwDy674uVeII0oMwcisK+Ydgzg235PMiSEMuZ4icVR3Nf4+gyx5wT1QxI/g+4bw9p7urEKIaDINeEP1nPiyXKqQRDQyxV2qvR9VFsxt27SZ+rywQF9vTQgToUIxzVO8+3bEuxQCKhih1nqwPqYAWbxdo+sW69HpXD9It/PQyLKj86RcIJNFG51pV7AFkcwg/9kjF+t7WajB7H0eKuac1xBvmF19iB0LHKbBMJZ5UvCIBt8B1lhiLYcLmDlfxIvWQE/E/pZlcu3ReO2ijyXzYZ8OCRPk0sdaLPYVtSuZPnJQaJtClRerhFdIXUjrXDAme6tsmhSvh8loqWajlg3S/CSjEKS1Ylfa9HlW6Dh5HWfd4+Dh1z/OenEIRoqTrQeHgXSc4+z1kPpDoaw+1/eNcfw4p9jjtKYjtBDnVHschRPx4QwdR0V8EfxcG44U6v5gZSADIQejfueJdqef0rWLBFxf/1KKeB0rov4XG/1d+GUC7q472vuVAr4eOl8lcNZD52sEznrofJ3A8dM50q/3Nbtj6/kehn0VRkvpcrVu6yxb1mzYbRN2PbD8kqIhRpwhjDbfTZpfBAew4vfvtX4skzJUV5cea95s9FUog8O4XetPCSva/11mP0Bqj/dofTiy7dFt8h/NfgJs+LX7VV8nlnvA6GvGlQ8Bg9I=
*/