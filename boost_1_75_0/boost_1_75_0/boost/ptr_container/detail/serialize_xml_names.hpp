//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2007. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_XML_NAMES
#define BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_XML_NAMES

namespace boost
{
    namespace ptr_container_detail
    {
        inline const char* count()  { return "count"; }
        inline const char* item()   { return "item"; }
        inline const char* first()  { return "first"; }
        inline const char* second() { return "second"; }

        template<class T>
        inline T const& serialize_as_const(T const& r)
        {
            return r;
        }
    }
}
#endif


/* serialize_xml_names.hpp
W1dyrrKSb3cDq6wiIhfiVVajN/uJXoEztvML3TnPR1yENYzY/xbXx2KvuFPXxwy5OSYzLqzHLxuwvodgSRaYDZOxEhsHFYpAPcA0JBtCmLF/3koaNG4Z39FJiXsyq3u6xgRBfvokPA2ZJTJ+ujno+l5RqFOOKgBYY2KdEux6rB7iSmhNQ7qKMPy7ovyh8xoM1ZzGQTJQi/9h95Z0QViB8ndCJBhwdP2IzRguff5n3KdR9/lzEwChF3Wy62DXm+98CEvZ9Xb5/AaTHzAzYxGBEKkNf6CcSXqpGGxOW44QCVavbMiUGZcPV7lkb+oHSbAIMCuxSrEGcuWO7GnI8ybkysXvUkxnwbHNW/mQKwdioXcXhyubwruOOAXBKO+6q9h35jt4M1/LECLBBM7+x2unSUJ1ZHofXTbh/vcL+mlJ7VDR57yCsASK/kh553hcFXrTNo1gRzm3eCuO/7KKGsR15/UgGBHhhtuzN6UGvyv/tiTCJW1xbL1rWoj7d1RGeoBAlvDKGhRyjrqy3wHNyxq069vTpu+Bt8sNUHP+Wh6qjJcmtxh4IAYgtZ8PLdbcvgFv67QtoirxK1w65Szxa/0fTgMHNiKe62tzOergDC1JoZ8H9WgXN0vSeCVSpwOGt56LEReQzkOfsA1cjS9u9wqES9xAm62uq3BVnUWDas7Z/0WpHuyBaF1ure23tm04rAwzN4wz/Y5EtNxj4pQ1
*/