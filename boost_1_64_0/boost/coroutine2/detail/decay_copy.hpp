
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_DECAY_COPY_H
#define BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
XJoVgLy6i3l5m+Q2U7i/qILbIm6eT+ePj3p/EKX5ZkTvu9yhoPgz+WN9ZY93sAPvKKD1+us8I0U46/LgVinJGwzxgxbMj4qj0VWRlzD+sCg1zqqnPXPDWu6WlN7VYmRjS+ljETsdY4z/aA3P2aVo8oJIKvQHYPQIquVS8vZm+Ye0Ex8qIf+aPHf9TlEwZRKxdiLpomCqFuTztvJ3qvSK4Nsr8FmCrr6sR7GT99PQmo4gP22u/VI3y0aq66lT9KOz0J3rBkB4Bd0Pqrvfyv9ySsRXOgN/4LvuAwRqqZdn75PswVPyuILh2kleJxEUdaO1KbrgeaPri5MTtb5I7RH1ARh/EOQ+NZgfVfLLPy4L3jJL93kyEdO/U6O5DhIP5VjNkNG2wlznmXdwdVcGfXgRqj1+qvN0J1PkNVAwSjc6phpwdru8GM86euSyoLU9ZXR/pGPQB/kO18bSuLUdeNVtCYynUmPnFALzwg7C03x7B12fNQBUGWPy5/HypYDW08WOyKtHgB7D/emParR7Jwzifq/hZcQB+UvU8V0+y74ap/dSjeDFVpMkexuxwM7ajw7BQcf6JDfOp65Bu+7xaGKhZQi6raPat/7aj9yAaudLcOMb2i0YD0r3QJLeTfTeTDdsVfRQ7lYgnDZbqvv4BJis7wbAdB1gHnrY0x+jmR8t9mh9bkvpOpl+O58B9ZtGeyN7d+RtQtLtBRL1qG0vf7H8OXE6/+ox3h699mreDHbNOrIbVMokWPFc7/UOwMvdClpfXgCV8k3nXz0bbCXJj4rdktqU0uzln1xjDJ6cbGfyyV8XS7WYPSQzSkP8LC/EH6Xnyvt136jt+LFMtdgTPvCnc89R2ZgbrkIyO6/8L9d13ppOsv51SJbLaDvUltYaLPPT+1i977xGQWUXppWXtpjHXSDJTNR7Qj2JXHrHjfkxQPt5vPx1d2X/aTEPdiHw0D744SF53X4PVNGCxOJlbxSXWHX1TPdTOHnrt1myHniQVyiWvChV8zHo/sOLNkoNkz/xjC328yI33f9qP3pGNevGWl9aQbzvKXk7u8resKTApKvec+WgsJoz7eBP3oW00uhqW0vdl+WhhiHcU/4I+e+tIG4rjT8bovXUXvcBzpDY6Ho05QGx+QItv0L20DydV0cRi9yt8fLGGXnlTHoVTRvXrCDuEAbx3Ju633qt9UX3iJVnA/XciWCkXoA5edhoP3KFP83aDU+0Hmhq1JISq8pIqCj7pXkCDPWSSs7KAt0xR/bLSTgw3qrzYHu6oslS6ka0h+SmJY1v3eUDf1Nk/yXQxuj5Gs/DQfbVSclDS2Sv8ww9o2263zeHOHdz6Iq7w324uJ+apfGiUVwvS/OjGcQH5LB/qTndzM5B7zEJ9jRFnbW/oWKz/V6Mv0ayd9UBBeyoMTiF5E55SB93oPPeDoGDIMnbp7zuF64BcGsUDHXMhPue8jrbd9f7Ym1FoW56P6RJN6MLovaWiW0sq2ClnoEdUUHsNb3niqP0irbAwAM6H8WjDcuaxKL1KmJNF2pM7wTJcI0/B3VKi086H20AL1lQLaeTTNGr0yHxEK8SSvYyShccofSlme4HpfaLEWhjzgG9Z70s/5/q3plMbKy249wqKK4m65aBtSWaKSZ75b8aIv/kB8Qy7UO/2U0lr6NM3VwNPZlvA/Xetnte5NUAeR3hLvsUlOoaeg3FWst5bvRvGdlXctuUDyfo85TGLyj5cicSjW4C1AM1XrEnANtn6H3YF5IZZQPgbxM9U7pxLsZzO/C+1zWjPyYh6vn71D31ELqci3of1kXj74HsZ83fqnK4+OpoPkb+7OEtXPU+1g68UrqvEBvGOnz/biPEKRk0FLs=
*/