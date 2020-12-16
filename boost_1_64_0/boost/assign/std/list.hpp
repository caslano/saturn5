// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_LIST_HPP
#define BOOST_ASSIGN_STD_LIST_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <list>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::list<V,A> >, V >
    operator+=( std::list<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::list<V, A> >, V >
    operator+=(std::list<V, A>& c, V2&& v)
    {
        return push_back(c)(boost::forward<V2>(v));
    }

#endif

}
}

#endif

/* list.hpp
ycWUY1ZiNmH2YJp8FGf6YyZiKjDXf1Qnv/z/dvxK8/9zCe0KAPyk+f/26Ke+vDfPp3PdPjQgVjC9rJckPsXdYMAYkREYmsWYXedW+jpVvzGsxr80Lji3orMpY7il8eNH4a3v37G/TXq/G/BRWo5yTGvMFEyy+y4dSN+9yGnFs+bI5A0v1igdCnyTebZV6F14hBMMf6Cdq79D7CMkbPN0mT8J6RSKC98b7zaxH2nSbNj5c+SkJqTL6pa40FxGnqbh3bfw3biQHqPHW3n0f+ncywrxPyakXyiuer3Hb4h/gtpt+lbn/3EZPFsxLksyatb710j1yZBv8h6vexKqnt4Zolcnx9rt/dt5u8clHvcUUX652uV1wjTEtNLyaxtftfxmBYovWvlp+FbRykv90nWekseE2NNillcuYbIlTFOx59k0UqKWz1jr38nKdkzXPM2KoaPnl8hTq3Mu3sjxqLaJWzCNyNO8UJ7OLCy3+Wp1SDoROiRLJfxSzWOJH6pzMt9ZPHd6frHmc9C/u62zZ2n8iDyz7aYsPrTXQp7E1zah5at12rbJW8W/0LQgj91bLMpgPM2LcYFyTq3qcXzqx/GeeQ0tA+6fvJT7t3qSuEfc5B51Tjp2npfWM3L012/XvTE/dKVehPoh6SZnoHi1rMjEzPPeEr5TqF6LPc3KizyWoaYW9xrl3uw1a2csRwONVF+vOSX8mlVXbPRr5ho1fIMa+239Xhjzepjbk2NGHN81tG84l4xc9s+UsOspmVswxVUL3si233nZnnl3Dd/d1rM/iT0rzu0bukn44Vpng2GPtLre4n3uvfxR5rIrTOxy+qvES4/TuqvpDIrZf78g/m0k/FgbfkCU/ntIoE8Q/15xeo+ufy/+WF2LW/X8If/T5qE/0uoh3SP+3/hD/iU2/rH4bxf/enENrP+pVr9s3A+u35P+tcb4g/ugrPMFZBlC4UutLMF3ktZ6v8953Cf5aMN384SfbtvxY5L+X0xk2qFrLSg5tZexZfJPCZ/gS9O075Xwg0g7MSwOuz7Yc5xv3DB32HM8L3F6eMKXkqGh8D0d2RPEkTyw5ziScyRh7Dls+GLxH2aihX/OnCBleDFt9DxrRAevmL9lBEzXZgGzN0UMv0P+12P0t/qLGwx3z4HPwYHwbhvHhvX6CXPEL+T+fHh61pyTUbN+PrcvfdEX3peW2ueVtkmd++0mbsN13rdqf7s0vG8VPf79jaRtGvcJ2J+MsO9xwu03+6w9bL7lg8ahvW86wgfhLvq5DV+H9ytsinxafnmh1f8fITtj593/8I30Jzr/EkznSOkzVhgTVU5npBMeblUMuaG8iHCV1fRBX0u46/zap2i8A6vdM2vBd24Yv0d+R+Op/M6TxmgbsX2Sla85Ru77I99450LtWx3T9/uUgA5Y1ac6XsIM9of6NZnbt3Is38q5rvY3CPV7poXm6zq5tgmUXXPTGtMf00bloBpJumf7H/T5zEbMdkyC32/7WxPR32ZI+IWe85xizzNPznOLGceZSjBLMUE9mYfJ/TTxtPkZts8cImk296fZ8YkdQtl+uYGEOZ8wGr/K2NIxY75N0X2rhsg4LkHiXOoPyTWpHknt/3zif4m/hb0XGZPYARwOUnY5MKyv0nL7g5yvSpnJvN/kJPqDRnw3d+f90n+z0DN+lTnAU7A3x35BRnh/tt7dFw3zDOZw7EdnBdyPgtqfhPVtf8EcgV82ZhRmNGay9jO/wbRLDfQ3RTX0N8dw7d7+ZkUUuZJVUeRPKqPIrqwN74dkvP1klL3a2oTttx6R99pXNaVOefuigWpPieiLUlQX+r3aF12jfVHOF9H7osI5sfuiNBOMl2MytJ0sEns=
*/