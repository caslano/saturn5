#ifndef  BOOST_ARCHIVE_BASIC_SERIALIZER_HPP
#define BOOST_ARCHIVE_BASIC_SERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_serializer.hpp: extenstion of type_info required for serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <cstddef> // NULL

#include <boost/noncopyable.hpp>
#include <boost/config.hpp>
#include <boost/serialization/extended_type_info.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {
namespace detail {

class basic_serializer :
    private boost::noncopyable
{
    const boost::serialization::extended_type_info * m_eti;
protected:
    explicit basic_serializer(
        const boost::serialization::extended_type_info & eti
    ) :
        m_eti(& eti)
    {}
public:
    inline bool
    operator<(const basic_serializer & rhs) const {
        // can't compare address since there can be multiple eti records
        // for the same type in different execution modules (that is, DLLS)
        // leave this here as a reminder not to do this!
        // return & lhs.get_eti() < & rhs.get_eti();
        return get_eti() < rhs.get_eti();
    }
    const char * get_debug_info() const {
        return m_eti->get_debug_info();
    }
    const boost::serialization::extended_type_info & get_eti() const {
        return * m_eti;
    }
};

class basic_serializer_arg : public basic_serializer {
public:
    basic_serializer_arg(const serialization::extended_type_info & eti) :
        basic_serializer(eti)
    {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BASIC_SERIALIZER_HPP

/* basic_serializer.hpp
GWu7sXYba7Ox9hprq7F2Gmuj/4r2+Z1F65fjxcT0itCJ48FE/Wy8/vAJyGfobxfuxPq1JqZNlkzk00R9bLz+bXEcf49J5ff8u2w5/Dd2Ptw4+HcsvxB+VXz3islldKLUM24f4C753vyHcwu3bvhJo0mAnUHeEnopBks7c1jCzNL2nk5etcMc39aXrlp62dZF3URIjXgeqGjl1WEREeH9vdv95LK4hfPXn3vxifOjw7aWWr+s91+yfqvecNroZydeEMt7n1qHD8/bnHPo2xwd+bUenAfT9Bd7P3ngk/hvff/7/tLv0dqTucHVhD23p1pq+F7fG6bkcGREpzEwKSSA91Ne0W6NhQNztJJnVe5rFpBW7N4dESpjMWP66T34/phl5Iu8aP5/9farcNea7pw/xdjyiqRzX7yhiuwmXBY/6cAT0oHUsrqAZ5GfzKq/I2z4Of1TZRWb9GlrH6cv7WJd01PZ85ogx1q5Y96Wb44u+b/e/6M/GBWZKdPxM1ebHfHlFrZrnFr0ZDgZ/2lrH3XL46i5AUSZdaUZjOTDHffPFw5+u62VYtaiue2ru9N1g7KvdF7TU7v2NLxf9Jp4awt50Y9x2Gj7C0sXzeIIVZTXaMlUdijPXR0UsCye8sXZU7em3CPf89of01Uodmn1f3N3RG6Hx8YmrQLbaxc/tv+/sf25ZIzaSjuF/JQHLV9E7ZWrOuWvl1nLV1n64p6d2ldLzE+waLd1kx5dNLjxycPWyu9b8Xd2DBnveKPIOXPxsP5aP/cZ4WcDMr/b7bV/Z+0BniR3k7d/dy8nSLDiyr2W4pPqbXHcFVM1rhJ38ZuPzStIO/54z/bUtppNo+U/7Tx8NtXzhUW9OVGc+fHz/z/+/LGff2lZ+/r4tbUr9Gpu/PTdAr0pd+pjNeOkp6yqXo1+RSza5yPb1WotcjLBfHtsqU/vTv6PYuUM/rFN8zar3LZv7WnMUux1vbLs1JUbleqtCYruDy7pephpeXsLW4qdI0++wFhtu1btl3QRc87jyyfPTB+zmlaycS82tlxZHvP25+b5K0RT9shsLDviKN5J09jn112fcOb8wwFewer1lpe+OMNgu5WPfjqvzuMG6Tuh0+yjl1Ij1ldP7fhR8dL8a4wNVnfzM1hPn2d16hNzm7eW192OG5x5VLqFU/2sR/VSSR6z+bPbc+qfGD/fbWqd8LBluR1+Cd4+dbHD1AVPFaqN/GkxMTcffDWkGXHJUedj///Y//9v+/8Zeb+YvC8jFd523beOX3uiwLR9249nfrgaXSE+JblgemJ79nUUw8mv3vLGvVc37ue08IM6i20Lg7+ed39wiTnveIywv/4PvFSlhs7sEKPOkZNn3ny+5Za2tjH+IG4tidkz94ga79l58+g3i5Y9Ngn3aLiwSZSU3PY62yPhwNmUh6uWmOF6/dtsiUK7wdIDfzgcYcB85eD6yqhdLHs3pnCppVvGw8z9ugE1iwY06shTktlDhVNVA3rX55Y0y1Wt7/aMfj0QXqvZeGCJxc4pL3pScr50pLhsnaqxrOWLvci4+am1sF6VfvgNdrl7+qf33efEPzq6z2Tmvbg5X7Vf4Mx5uKFiedSC+g1te3qvt48n/d9xv6mP5WP5d5a//Xs/XDs86bf+Y+0T5wHHvStYYHL3w/E9E8vjxkyKH5tYXmvcpHjHX4jfexfHj5kUv3rvw8tf7fwL8fsfXo8Pb8q07IbyRetmnNrCbz+SmHJUZXBsXpTLdOPT33HayfmeEfkj2x6EqH1m2W5V7VZ1/AI9sNg79+wl/0EvtbzX1u6Lul7fHJ2xMnov9+sdU/esqPph57q2hm+qk7Ju2H2WocOTJxZ8e/wJ8+ysB8Y=
*/