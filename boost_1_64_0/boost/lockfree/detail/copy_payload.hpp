//  boost lockfree: copy_payload helper
//
//  Copyright (C) 2011, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED
#define BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4512) // assignment operator could not be generated
#endif

namespace boost    {
namespace lockfree {
namespace detail   {

struct copy_convertible
{
    template <typename T, typename U>
    static void copy(T & t, U & u)
    {
        u = t;
    }
};

struct copy_constructible_and_copyable
{
    template <typename T, typename U>
    static void copy(T & t, U & u)
    {
        u = U(t);
    }
};

template <typename T, typename U>
void copy_payload(T & t, U & u)
{
    typedef typename boost::mpl::if_<typename boost::is_convertible<T, U>::type,
                                     copy_convertible,
                                     copy_constructible_and_copyable
                                    >::type copy_type;
    copy_type::copy(t, u);
}

template <typename T>
struct consume_via_copy
{
    consume_via_copy(T & out):
        out_(out)
    {}

    template <typename U>
    void operator()(U & element)
    {
        copy_payload(element, out_);
    }

    T & out_;
};

struct consume_noop
{
    template <typename U>
    void operator()(const U &)
    {
    }
};


}}}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif  /* BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED */

/* copy_payload.hpp
pol/Hw0OpAWhcX4H9JSK30XowntZx9yr4z2wSpUlNjF8gzxbydLcZLN5S/YseF34R3gEM4PEvQnfxrwjdZCh/jHs2ZIAmLe4nTjoc/y5zr9WcaSM+G6kk50OxH3i5N79LbF7/lZt1y9gN73arm/A7v0qbdcnYPdQtd3ZAbt7qu3SAnY3abt0fd9N1Xb6viuq7c4J2E2stuttyXoWl+p09FfnI/X5OYZ6WeoQw342CdpOPV96ztYXpezSRd+kup0S3YIxXj9Hw0Ytkfs7atQ1mWXlpWG1U1wbrDMk8UuRuqmZ3907zMphjfIr+KpqnKHOMIWzNHvxkjw9b/6Rch+v94eZrM7zmaX3GusEHZ6egy8qyHXsjTtNuc+xBnP3JtpPSXZpdmFmXtE8rhN/d/r1SeRbMQ75Tkjcf6LcR/H9SYwjnHnFmYXFuWSDDqffDv+edj15zuI5/xPPyvUkbFaK/3ma2dxvtjRznte1zQmWF/LRLS9iJ3nL+hpnq3ixbkv7YFmprG9xYC99mjswcS35d3eQrOTmscoOwbtlRac7SvlvaJIdwnLv4Umo5j4Bft3rpuDXtafUHOWnvdXcpJPoCkPvS0MwQfv2KD9NOa+uT/Gi+wpnKPf5Vl/+zzXtpyXhLJJw4i2vu03QMlxf+bkR9wXuvXZ1fHrYfkhNCnITLfva2OvqPIP5s6qLT01GlC6H5LuszSJrtkj+uvorWVKRnyU36Ib5kHAzgvuFBUUF5WHVH1xn7ufKc5+l3M909ONqXY9mfG1924GShkMN/Z5fxSgdsYBs3xKUBr4VDi3fqdK2xqhrNiudpZ7EchhPy3LZ55k4SJiznGnGrg5yf4tZ7p0yW6X8NDXLvPN6v6YCyogqAN0f+r7yMxo//jiPVuc3EF4DiWPguupnbanyk00co2p8b5oq+lxxys+z5I1HPS8jMMsNZZ0qz0OC8v+MdQal1Y3e4WDCLre8en+4Y6kY0Zey+a7aI+7kurh2G3vwlsA3p6f+PCTL9eQn9pKfrrZ2mkTiZmVPnDFfnGkv8BIkY2A+15rlqzm8XPm/Dr0N5s4xRZgNGNOzRNharmY1Vv1gwq/uBz6j3MdbHfE9EGOQNx2Gs/7jn96f/qByn4mU+6zemLEYQ3mq8r9G+b2GsqSviVmAWYOR8lR113v2/pdwBoH/hd/HU09enrWVn53uJEm3szwOyt6SZdKelUp5nNgRVB6qA0CJhFV3ca0pv035il9jvup2pbPKq4HEzav66aZ2pQUcpPx1tlJqPke6nL9U9xppdZLnTtoOnd9/8ec5ffVTaztcea3biArZcPQO0WG9HfMV1x8Jeh+iNg4O2W/4vfIbK3VS4No+6Dk1dpYB9qZ9wM1lIH5N+4Dr/I3drdp3+nM+U31KGO61C8pzykz6ru77WeI39L7j+K9dRt5W7lcTdpw1pqaM6Lybo9JQX6/xV6TOoxxrE5QtptLSeXtchXs5ORtjlKlkzl5Xfq6zUvk/OajfI/1LufdAda92yHG0lrv3UzHSV5lLYB+knnx8ePI6mrJz19HO8nTu4SllpPcpt8RO+3XU55I3zrrj02TZi0fqjmGYvxOvqt1Oedab0oaU6R3Kf4ypLiEsp1zVKsf4dcuVTrdJZvEfvsxW7a6bzOLfJLP6PeW9yj09pKz+QblHG/vITTjbrdxb0buJ1utg/krZNQ8pgw8q97ZcwTXIoFfea3xYh73xDXKHLBnkzvr2chfQnX7AW3ed27ruybi3u23f8EjCpvz2bw755ME+9ycVjlsQWpf4jQa2/eAvunSe9vnqK+4ZM7vF8ZjNl4ReD/Cm+bb9HzbkbtnV/JP7jyXlvHl448PdQuuEv14=
*/