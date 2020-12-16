#ifndef BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_ucase_letter : in_range_c<char, 'A', 'Z'>::apply<C> {};

        template <>
        struct is_ucase_letter<boost::mpl::na>
        {
          typedef is_ucase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_ucase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_ucase_letter.hpp
1LWtyMKKkNpkKTOKprR1d5muqZqMdXeZtu7QGby2EoSVuCxAGUDYaUYQiJcsNtkfMQqc9awJtsNT8fm31LkNFCBbZmKN9BnkcyzoeRITH5PvwTppmQYu4KAd76yVzn4rfSnMQh2dLTNDLsZRcdTXycMjfxecBVHvbmyQo749o1gfZWnrY2lLHxbHnchjz/Er0cHFQYUv2ju3+r0ujj4sjgeRR7z4xcVBjGJxfOxNZXF0Rv0PxrxdUe/6mG931Lch5t8T9W/EKWDUeycOpqO+e+B1iPrvh5ck6n3g0CvjWWVlPCivjDf/oa2MO7WVsVfO/JhsVGz6hGFU/I8l2jsLYStgUIfFt5eKdcoNXdop9FPCjC8daRKw/qkj3QSY+ImMMH/R3kjw55yrwmeej798GcpogI3hfuYWu6k+b4swlBpxKMQXHojz9xisdixAuCVBP9ZGtSW8DF45U6gOBdU+d9gtLO9B7D/fwuLq5966n8t3ja9/tS/JSguwVUK5x+7a7E1O7+I2u49NELSPjQgRM5BYC/FymOtDO88qQH/Q8XWRfXnW7dsGrTA6uVR78p7MQ3FFx1Ns8Ff76FJkr8cL17AZbKoyN4zh6r4NLLBVtiXK5YA9ONhcm21F070D9D8MquSSJ3Tcj5ZM0Jc2/Dlz0n0lpN9N+n0fHS39YJJgNCxpDJruCE/zk8rHT5F9/ehKtIaeSQwgmq9yNBTIow039MOsRRQOMe7xfXgEvsbHUsxnuQ5oZvikehjmnULiPXC8RsKDpvppga+r4MH5wjUTLJCOu1DAgJJ7kaFxucLc0tY4FUyFjgAJFe66IMmE49ZaBJXbL8QkCqhayHzCkXoQgrYx7zAaTst0X38+AjA4pQiz2ulmd04zNU4nWJEYOUyypUVJ2PUu/rRDggM+6kj8WnRztOP2QSVtvX3qIwy6GMIruW4OOzFwD5Dvi8zKTgidZF/qj5CunQc9Bs6Fh+QxvQIgCfmcFB5fTIuYnctRrDkco2gLlM7yRiLuJuLX2V2AL8As6qfXeL6TbvWdZGY+ZgVyapEDpcYpSusDz3CfufHq4GeUOQANth/zEkMj5lu/qZ7Y5xM7R5fCBmsB8wNhXW/+VYzhU1z6iJX51T6EgFm9btfmRcnpO2E9wI2yenES4MjEDBJigtwAHSSiKHi73CjmPcNlb5AdbugA8EQpQYba59usJo1ZfvYjCjcaYAajRfiRqA5EtPmLULjAT+UpuW4JUXlEPYfgYrV/KOREjRrp9ctYhnX/754YuvlRItb/JSBEXcT3YsA5eznMXGquuxKAYZc5mPZQkbrC83gC8AstkAdjiCcqNI5X1w3myBJLsuX5kCVhSfxeJ42X2pOMFsK49pix58bU5LA244HhjOy1UOwNmYn6sxi9yD6byLAw4+OoRTKYYWXGBaKKW2TYmDFXVCkTGTnMOE5UmScycpkxCVWa9/IEXOTlMS+PVOhfMLKQA5igcBLAawBbLXGrMv0HMJfXeIdWWzDXOPuZwb5FvZJgwDmM4MT+p44zQfpIn5icgLXSdh2ANOVBS5KzlTPwV/tQBHlvnr79SVG0K4mM1TxncdLmtaDpD2WGaPrheL8mPxSR34r5K5boMRgUnDoqQx+2JKaIZW/DmgUTYF/313Gbk8RugguZoWC10pemiYl/KI3L9u1s/xFsuCWfn74C2wpRVZVQE4KlgdXUAXnBT2G1VZzHUg806ZnUfEFTMCgarK9hvpsGEVZeSiMuOJb5FAnMlr5/oUA+WhWr8adgaXb+YAdgNw/jzwwdf+ygYhD7j36Zly+gh6AGXAJMnXT9kaPiUhZ+hS8CvyYvJb92X5vGr9LgRQq/Ai8AEiw=
*/