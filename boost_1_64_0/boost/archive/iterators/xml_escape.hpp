#ifndef BOOST_ARCHIVE_ITERATORS_XML_ESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_XML_ESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_escape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <boost/archive/iterators/escape.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert escapes into xml text

template<class Base>
class xml_escape
    : public escape<xml_escape<Base>, Base>
{
    friend class boost::iterator_core_access;

    typedef escape<xml_escape<Base>, Base> super_t;

public:
    char fill(const char * & bstart, const char * & bend);
    wchar_t fill(const wchar_t * & bstart, const wchar_t * & bend);

    template<class T>
    xml_escape(T start) :
        super_t(Base(static_cast< T >(start)))
    {}
    // intel 7.1 doesn't like default copy constructor
    xml_escape(const xml_escape & rhs) :
        super_t(rhs.base_reference())
    {}
};

template<class Base>
char xml_escape<Base>::fill(
    const char * & bstart,
    const char * & bend
){
    char current_value = * this->base_reference();
    switch(current_value){
    case '<':
        bstart = "&lt;";
        bend = bstart + 4;
        break;
    case '>':
        bstart = "&gt;";
        bend = bstart + 4;
        break;
    case '&':
        bstart = "&amp;";
        bend = bstart + 5;
        break;
    case '"':
        bstart = "&quot;";
        bend = bstart + 6;
        break;
    case '\'':
        bstart = "&apos;";
        bend = bstart + 6;
        break;
    default:
        return current_value;
    }
    return *bstart;
}

template<class Base>
wchar_t xml_escape<Base>::fill(
    const wchar_t * & bstart,
    const wchar_t * & bend
){
    wchar_t current_value = * this->base_reference();
    switch(current_value){
    case '<':
        bstart = L"&lt;";
        bend = bstart + 4;
        break;
    case '>':
        bstart = L"&gt;";
        bend = bstart + 4;
        break;
    case '&':
        bstart = L"&amp;";
        bend = bstart + 5;
        break;
    case '"':
        bstart = L"&quot;";
        bend = bstart + 6;
        break;
    case '\'':
        bstart = L"&apos;";
        bend = bstart + 6;
        break;
    default:
        return current_value;
    }
    return *bstart;
}

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_XML_ESCAPE_HPP

/* xml_escape.hpp
cAJ7n59Kly4qY9H1BHzr2sEOi4+E+shJpDmlgz5KfeM+aecx9ttOnB85B0l2Ieyrvzxqx/UQF52AYbo/mKOAp+oE3IeVq4A/lb+FyqZsyvdq4dM+OFNCjRNf3fmE+mdoUUSQBeVNPsiErl4kUdd+TNHKp3jbRMwf34MxIQN8WVsuyYvGI3OYLV1J1+ASN+9SceFmdsTrJEWpHaBqwfzxulOYQdaJFnbY8JXRNnhbbcw8J6ygzYkP6HmbCWRV5whyxhGcXKfKU/+oYFviIPakBeHf10AsTV4Lk9UT6XXlKLQ5RpLNbEvil7V49XEHnA6/zSUm50FeS4ru2xlBP7+O6tPn0OzF21jLuS4YO/7Hl0ZvhaR9LL4MaFLbG2E697yWEm/WcOEWCWQffgkZFkg+K6O43ddBQVdqMlexrKDI+o1sU6AUfj5Vxq79baS8w4vLHemnIKVuPrIvlYL3+tPZq9ehduMZmdeeoZJtl3Dm0VUa7haEfUfEBZxeny+X1afGDI5fv2XRpVZO8Uv6Bf/p6sRhaTGIzGrmQy7vh+PEo/T1pS1OVmbw21XnyMI+hs02P42UBFem71KEn3PSYLDIn0aVmvLj//Ipy1WJPx0AnvZHUce3dxRZ8RLTu9xhaGTK2h22QqHfn9mKLiX3Wmnsf/ecDnvkkoGYDF4s7UOYxWkELg5iu1t3oGDTVKj2+aL83Vp67WdMBzO/4/qQk5QZeo8t/B1EMWZ32HbtXnJ+pksbXwTSe9VmFtz0iGoLB8jkxDjKjkigyXMlafi2tfyhSS1+mliSk2op/XpzEbXBEaT/eRG/32tJt3QuMpXPGrCf/R7TJ+RTZpoErNbHU3vJYxZ+tg1NDcNZUaoIvqtrsn+eGSgalkplbtdxddIrHNhsSePkR9FjMQfoL/zAE8IOQe1VFS0Nk6RLl/zZ9iQ/Sp/sSz6agv1eKMqmqo6mOxmlLKhUhLaLReCz/XooOJzltlChoj5TvjtiPX13OcE3HptH+vIy3PzNKOR75cM+8BmuF2TzytEdZODtxzXa9KCyfzIfZuZJHrd+Y4tvKbpDKlB2YDPOi8dj1xMVTFG9TqeW+SFn9WF+XsIPb5piMDP2Ejbt0UPW45GUbGHGFpjmo0/OjZyF3pNm2Dy2ZH42Hn8Q4iKbTuBE1lha1XOP3Cb40BvtN2S9vg6W5r/pdMU+Wlk7H6N611Pxx1tobBjN1v2XTYsV/8Ou89LwHZHEf3edh576GZiUB2LcyYP0xqOdLv/+S0MCT1DzaW0m+CQL1i6EVJNz6NzKTWxzznAoa1oLHH48LRTMK0q5BQibPo+nWarC89ZPJuJ9lIb/fMbuG6hR8dkd/H5PEIVISPC1dlvgPhDDfiwQcPyw1+T/tJdOLN3Por5poevTQajqTaOlvqvZYNo0kgsYxSxLC2nQq4vdeyUPxWI7hG6/ixcfNvD0SH30NT3lu71Xk/FuW+53ewR2e2uhuqyJdva9gZnIN8pZV4HOhkQ4jp1JnqsnUOCyVpjyO7jb7spUlvrTzw89pF/4Ba9+bufbA5PpR1kRFo41wcwjO0nuaxbc78xgLVcCySO/DILhkY7J3qfk0ki89pzKFuQK+mrdL/hxg2bMlp3Bcl03YKZ6En/YsxDaq8N4bMpL2r47mor4a7oh9gcdo8rQGdUNG5251CW5k0ZZxVDTps8U77sB5ZYvWNfnDLq0M5Rp3jIijb2pzLTWCW9knOGuvQgjJMXx48ozXKu4iJOG83HWbCaKu4egSuUEs0q/h+aoPcz2YRNObXjIuz74kb3iMJ76VBX/RLeyc6u9oBc2ly3ZLUG5Sa78v+/22PDWnrx1t9DG4N+szvMGjSsOZK8=
*/