#ifndef  BOOST_SERIALIZER_MAP_HPP
#define BOOST_SERIALIZER_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_serializer_map.hpp: extenstion of type_info required for serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <set>

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
}

namespace archive {
namespace detail {

class basic_serializer;

class BOOST_SYMBOL_VISIBLE
basic_serializer_map : public
    boost::noncopyable
{
    struct type_info_pointer_compare
    {
        bool operator()(
            const basic_serializer * lhs, const basic_serializer * rhs
        ) const ;
    };
    typedef std::set<
        const basic_serializer *,
        type_info_pointer_compare
    > map_type;
    map_type m_map;
public:
    BOOST_ARCHIVE_DECL bool insert(const basic_serializer * bs);
    BOOST_ARCHIVE_DECL void erase(const basic_serializer * bs);
    BOOST_ARCHIVE_DECL const basic_serializer * find(
        const boost::serialization::extended_type_info & type_
    ) const;
private:
    // cw 8.3 requires this
    basic_serializer_map& operator=(basic_serializer_map const&);
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // must be the last header

#endif // BOOST_SERIALIZER_MAP_HPP

/* basic_serializer_map.hpp
mn3We1SkB2I33YteECS5Nuti9tK95/KIw6dz6mc9mR3w7fw7X95h392wf3cqraTru1LtnuXzk3UM1g5d8UxNvrD1qopfdrxRXnH0jqaDC29uOXAiDEOtZvtwKKvJnxw4HEd9FaxNz97ZYVxQcb1luOXFNP6+hNm75i/9Qv3YcWWsEvM53pcRtj7eY47TZ5qPI/XEEXqKo8scbybM/ObTa55yrwiZFX3OB0NCFcxHapsbmg56PZCTedv+A1XjZNQM667sxihO3ui94IH1FbE7wmuihzsF1CMejdKy+uCMbiVZWj8vyxjPvL+SW1fxnX791w8WnHmY0lWRu+nyhoNO5/Z0xAaIU5JMXS/ZDl2OmEr9ae+6PayY/c0chZdy0T/1ie+cj97IN0kLcFLsxiq1Jm8+bRKkn2j5xa4V4i3VpeSMHyr230VLz/BPbzWknTr3c6t5r/z2oXqSds2Jq+XNqz1syn37UjVvvfK83ddbb7VT4fulRbMSHSIO749RmHfyAVtW5WuTLUukPaz23DWOdnuLW+fMG2Irvn4QS2WfyGB5lDXlSJZ0LaIf4NT5pee/XnDzagFvl+Z6uaLXQo7q9Z0nPy8NWWGQQD6duArz5OcOlR9UPxltjNJgzFtTdXBp1tuVb3vDsKVfvT3dkbgLs2z78eGlcy4zsx07L9mUJQ6IAhM0Dyzt20yIvx9871ZbcGZTb1KHXM8OGssqkVr+zasL+jc61Qj+JWoykUfiK/tM8pQ6dU2WzzF/ddNt7yzVpj075M17NvSfWRs187tzP5ddXhBze3Z2GuWG5mNtPMv93pZ69VlXF+af3GpeM4/Pv/piOjZTVS4srqZl6c0jmJ3zz8zaRF24tmRd3ayc71F8dnTh6+ky+RjOl23PDlfIzZi+8XDn6P1G8tJNMcXbMjevOXNn2cxvRlI/ow1kd+418uozdfymJyq4NHOvdfXpK9bu83w2cOTiozLfpm2vM6drjJ9+zGCpaT6aTmm9SOlreR1vHRYYJb+cf00pSKF4T42JS9lBnBOmJTb4eWytXPds6u68Wu4DWhUVc+POHP3dm3+ee/Ks3oKZUascLpb+vOn4g6SGixq6iwiKXa4dobd0VQ6Wheb+vMNz1u548x9tCw9We++NsOuX3TLVInTWLKOd5Ycvdly0PRHn8F1i3YpWr88STBSq99ucPpnVVTJj0Knii52BN+Tf+C9bUx3r3FdyV/vsp+7+Kx8M7eoNbQw3yd4yr2q1d8YimX1aa/fKJkUIXkiORlLM5W/VKpkc/S7Irf3l6xtzVW/2v6LfRZL5LjeeGgY8v0pfTP756bZMP9WQr5sqR+0WnzjOfnAkxU/ph2WMTzwWb6zb09fI5833nr3qxtQm95uvZJ/t/JwULKqd8h1bOstD5cT6c5f1FTefnyUcolvpX02wenJ3UaXEopRFuTyXtfzqk8wgTPu1ymvlFV/oEjQ9pl5QfHudGS0xaKU+3tiUXDHr6oavJQ9H1asO+ho7DNeE1rd3LIqKez4PX5a2SxSZaq7ITjq9w3njqgeLrHtvbrwWV7tl4ZGTRw0erIv3UHzyqCv4RdvzuavPi4d2Y0KoyInZOe+QSuW271/pK+xcGLltfXW01ekS93AZ9WW2Z3zLaN9M7/UadZhyJn5mTaucbi5NzXbVC9JsrT5uakn+J1OrehcsnhlvTPNkRmcZljpcHx5c9PYYOY8WW6q57mBJ5oFsBce4TPfjGfsp+c6Wr7ahj+WfKn/7+3lRWNyk7+eFy1cGLV8E4wRmBDp/Mm2GK9zmbOzv6HEhK8cHEE6U9+aPj6gJHB+V86H5YZNe/qH5MC7sg/HYFYtgvb/GFy43XRQSjCY=
*/