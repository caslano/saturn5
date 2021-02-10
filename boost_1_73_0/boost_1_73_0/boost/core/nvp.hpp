/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_NVP_HPP
#define BOOST_CORE_NVP_HPP

#include <boost/core/addressof.hpp>
#include <boost/config.hpp>

namespace boost {
namespace serialization {

template<class T>
class nvp {
public:
    nvp(const char* n, T& v) BOOST_NOEXCEPT
        : n_(n)
        , v_(boost::addressof(v)) { }

    const char* name() const BOOST_NOEXCEPT {
        return n_;
    }

    T& value() const BOOST_NOEXCEPT {
        return *v_;
    }

    const T& const_value() const BOOST_NOEXCEPT {
        return *v_;
    }

private:
    const char* n_;
    T* v_;
};

template<class T>
inline const nvp<T>
make_nvp(const char* n, T& v) BOOST_NOEXCEPT
{
    return nvp<T>(n, v);
}

} /* serialization */

using serialization::nvp;
using serialization::make_nvp;

} /* boost */

#define BOOST_NVP(v) boost::make_nvp(BOOST_STRINGIZE(v), v)

#endif

/* nvp.hpp
BQsYL3qw5UYaD67Gyw/haglXwXweTJdrCN9DMF23/j6OpxfIDYlRKxC3ZSUMZlGBLMpciuRO8B/a6cxffoDz1XwSzpbRxeh9sJoso9k8XIbn4QSeQe/JCwjqa+T3k+c96OVySwSAX/yfn/uPcYFmkeBmHxlh6ajxH1ll0PHiA0yDyxH7pvfNI2R3yuscj67SVsc6b5kCsjkAtCRwC2mMVNfAmYkzUQhQvBAuwGI9DWeL8YL9JFWc14mAN5RRw9LsLXPBY43r9xPt0xs4y5A/OdLoW0kiZzNesbMuwcFrF/ditDifj2fLcThljgtN2UifPKf+bVBqi9mk4858k86+VRs0tTGqzWdshYZaiZaKODlA1G82DhwK5hVjiYyt50iKoy3dgIy71iWyyXOd24y4KAteNiNO8oQmNOKk1OUzj9GIk8oafGNiGpxLU2zdYGhsFpw/LFgJjG5xF2OBwlb6rPROEXlrZeqy1BX1xCH7mCMkBkRV6YohMgT8KFpNF6vZLJwvRxcH6AmrXSbUAU7UMDLtkMqpR9Dahxm+QAxZxssShbOxQt/HM0dpSHVV9J8NyCvm1r0tkH3y3muUipjnObad08YudWz4Qznb/SGrncxzuOHVHsmM0RM6TGRCpneAmrTjhm1rmVsfVg0V
*/