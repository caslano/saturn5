// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_INSERT_TAGGED_HPP
#define BOOST_PARAMETER_AUX_PACK_INSERT_TAGGED_HPP

#include <boost/parameter/aux_/set.hpp>

namespace boost { namespace parameter { namespace aux {

    // Inserts Tagged::key_type into the UserArgs set.
    // Extra indirection to lazily evaluate Tagged::key_type.
    template <typename UsedArgs, typename Tagged>
    struct insert_tagged
      : ::boost::parameter::aux::insert_<UsedArgs,typename Tagged::key_type>
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* insert_tagged.hpp
fbvM9w4711vP785D3OZ02+dz2+dyO+ds2+dqyzxt5xxt+/xsPS97Nw3nEeick70BcczDts3Bts+/dp93nYfUI4651TKvWs+p1vOp87J9ei51PbI9gnnTzJOW+dGhc6OPIeac6FzEfS706eZBI4TJNhfaPv9Zz32eg6xBtiB7kQ3YOQq3Zvsinu/snOus5znr+c32uc2YI+ac5lRkDhI6f7n1c5fNecsbkV3IQZmnLPOTZW6y+7zkbGQOUo7Y5x/vROzzjdMQ+zzjDYg5v/gEEn0xv0m7I4iHjjoDmYqUIxuR7ch+pBmJJgmW/qu+/48sWFG3zPj6/8W+/Rvf9Jcne/Qe/URL/T0n7dZ+5Jg6h8h8px5ZUFJRV1NUX1xeUIQL9UH78Or36VFK/ynWosbL+TCmG13s75iYue+1n2r0DereJlzw2+5fosc7jqn7bdE3v1MbAVKDZdrP6Urnp+p9N0bFUJ0Tocfhf6Hujwxc8+ukuo7R7+mVpM2LiZGfBWbu7ZqirmWMyB4u3osfUn7wTJ0QuH5frmNkv9fJkhdbZJ7De0g80mzmRbItL6qN/ZCrlpUWyJh8XU1psWNv5G5mnih7Rzzz+LcaedV9rAP33fJE0lzdG0U/FqfS/afyva2qhMJkuCPpuk/p9SYlo2x7XteRBtaeyM8qnZkqzlP4V9Kc+QBIK85fkzQP7K2v3OQdiwgb1zvk+gO5PirXl6Xqb9BB3+lvl376W8hJY1/ZzlZaG7E8XZkvU7pNnq+7zynBLefe52oPcF2eH+oc5gxHV7uMmxV79HyWywPh9FzuOn6n7es0vgwPVyS3Po2D99dX4XfsJa7CpdK6Dj/VM1Ra4PpdriVv9HjQUV/4cQ338aBw4x2tH/f5Z43jFF2q3H/ptRdHH3+u7dtPD7qv1y2PXhduHKf1+8m6j5e1fjyltfvJuo93hBv3af04nfv4TuvH49zHg8KN+7R+vMZ9HK3140eBPR2lz5M+do9jT8cL5b2jEMbCpXAcLIYTYImMo1wJ58Ll8AJYCZfDKlgLq+FGWAtvgfXwHrgK7oar4T64Bu4X947DQ7r9p9+R8KXKc4DqNyV8nWAXmAr7wK5wJOwp7/PpcCEcD8+D3WENTIP1Yt4AM+B1cDD8OhwCN8Oh8HY4DN4Jh8MtMBPeDUfCx+Fo+AQcA38v7h6B4+A7MAc2B8xl7wBpC6Wt3+PYOyAXPR+cDLvBKbA/nAoHwWkwE86Ek+AsmAfnwAXwHHgJnAvr4Dx4DTwXboL5kh+L4bfk+mSE73/mWuByZA2y2WVdsGNNsMtaYMca4P/Q++CQL/BO6PY+WPhPfCfc3or3Qmt9rX1tbWTragPraf/174mRvCMu0e+JrV8Pe/q1sJGtg7W/L2b+E98ZZ4R5bzz6b353PGx7f9w7mndwJHnMl2s4/5///sXv/5UVS7/4+79xRs/Laarf400Nl0fKi2RdYL5/dTJ9rHxXbpIx/I76WUDmb7+jPuvIC2gxThNqeQfdmxB2vpLY84pemPMgRK81Z4Hhlv0MCLleGjw3yRd65oY3lTgG4lK3XE2/mjIzb8bZ8wvKKqpKZI5Gg3VekGucsK/f0+qUbk19reu8JK2r52Cdm+SJ+Ft7g5wZY5/LV2eYiX/2uA6ICo3rvhTaJre4VjWs8Ehcn0w5bVzFvtd2zk/k4cdtHX57WJOjQ8P6DLo73MK6sqiyoTSysGLf8f7MGY3u+aJ19dlEnzNeQe/K4p/9PB9/TGhcX0qlj9ZxzTeO15k76ZyzC2qqa/S55Gref+Lp44sber7abaocGrbLGqqKXeOs9fU5S62IM2GROFtz1/ATM8tP4q3bkXqXeMcR7wPB8eY=
*/