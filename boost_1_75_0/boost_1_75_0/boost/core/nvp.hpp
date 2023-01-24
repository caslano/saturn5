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
vsW0aBLvr6jLB6seYD/f+5PsLKqJhGYBG4fmFeIZkNxvrer3NQAL5K7pta4mObVDzm4vOEVko5PjBLPfzh/xGQFnKAWv3jSiDEUfTpI4ULgJWTDZ2BzD0CTd7pKfCywwLSQLJxoOIlkvYE1cmgXcdKenlfmlItJjYUe/zc05toJqK5RZd34/XDXwXVAa2goJebp548y4WBCPfNDtUrVwN1CuUpu1dd60N5+6UZO3zC+lqQG0L1J7r+9RKEhj601Vx0fbCm3cqIqd/94lZf8Tsg/l11Rzcyz4OoQutWRuuJwc0ey9+EjToUa71nImmDKM4bOw7q/UZDDJY3Dkwo+xUrkEW2uhTiPelxQjN8OKgsrGQeGr3dJJvo92a4kuiXqqwm0CKklm6cCc99OXFsnh3S/JTsjFdx6cfB34DmrQ6bxkGeFDfdTgJ1jx6ytvn8+4z2JbjvclL+DEWWfWaFkO3scYRRQM+dZyDmsW69j17vi4mU73vvxEPPbm8foP8J1c16m4KTp5KbHG+ZxuRxFAECGm0aA7HaCixSTd37b0WdzjuUyiCUlLbdirENJeK8wopIG9isRbs10cjjkrEuVrZoKVtfoMnPx6zCYrb56O9bbJtlMCubRmDj+rUSJaracHXm7HhBu48nfcULhAj9cWe5tSD+r7WxVy1B2thYDDNm1hFfKxstn5/JlfAnOJ+sX28lf6TbL2QS3CRHsb
*/