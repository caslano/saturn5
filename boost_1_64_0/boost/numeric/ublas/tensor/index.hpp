//
//  Copyright (c) 2018-2019, Cem Bassoy, cem.bassoy@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Fraunhofer IOSB, Ettlingen, Germany
//

#ifndef BOOST_UBLAS_TENSOR_INDEX_HPP
#define BOOST_UBLAS_TENSOR_INDEX_HPP


#include <cstddef>
#include <array>
#include <vector>

namespace boost {
namespace numeric {
namespace ublas {
namespace index {

/** @brief Proxy template class for the einstein summation notation
 *
 * @note index::index_type<K> for 0<=K<=16 is used in tensor::operator()
 *
 * @tparam I wrapped integer
*/
template<std::size_t I>
struct index_type
{
	static constexpr std::size_t value = I;

	constexpr bool operator == (std::size_t other) const { return value == other; }
	constexpr bool operator != (std::size_t other) const { return value != other; }

	template <std::size_t K>
	constexpr bool operator == (index_type<K> /*other*/) const {  return I==K; }
	template <std::size_t  K>
	constexpr bool operator != (index_type<K> /*other*/) const {  return I!=K; }

	constexpr bool operator == (index_type /*other*/) const {  return true;  }
	constexpr bool operator != (index_type /*other*/) const {  return false; }

	constexpr std::size_t operator()() const { return I; }
};

/** @brief Proxy classes for the einstein summation notation
 *
 * @note index::_a ... index::_z is used in tensor::operator()
*/

static constexpr index_type< 0> _;
static constexpr index_type< 1> _a;
static constexpr index_type< 2> _b;
static constexpr index_type< 3> _c;
static constexpr index_type< 4> _d;
static constexpr index_type< 5> _e;
static constexpr index_type< 6> _f;
static constexpr index_type< 7> _g;
static constexpr index_type< 8> _h;
static constexpr index_type< 9> _i;
static constexpr index_type<10> _j;
static constexpr index_type<11> _k;
static constexpr index_type<12> _l;
static constexpr index_type<13> _m;
static constexpr index_type<14> _n;
static constexpr index_type<15> _o;
static constexpr index_type<16> _p;
static constexpr index_type<17> _q;
static constexpr index_type<18> _r;
static constexpr index_type<19> _s;
static constexpr index_type<20> _t;
static constexpr index_type<21> _u;
static constexpr index_type<22> _v;
static constexpr index_type<23> _w;
static constexpr index_type<24> _x;
static constexpr index_type<25> _y;
static constexpr index_type<26> _z;

} // namespace indices

}
}
}

#endif // _BOOST_UBLAS_TENSOR_INDEX_HPP_

/* index.hpp
YjhbSJRMR+MqrI5iS40SqYEcxaGa4WLhVCKVyLMAU94ahnX7umCXHM8rdlZRvdWa8L5EWuaQjvHE4Vv/ZALXMcGEW5VwG5dlHGMBl5qJwjI00r8cnDGH19/d4QvB2qdcLJvI5KH1YN7lLXg/LFgT7W6iGcO1U9FCnm8ZJf0r2Dm48EjoWNGO0/5OpoVzVnLgxBMDWi7PONzHlR04CarjVRywufMhL+F1DngqOqQJH1Z1wKGh5ESMVrPgiZwahRpVJgG2uo4Fu7pVtk+Y9mWy3JY+tYbMZaU0ohmoZ00r5qBHtMm1bFxjHFjbivEisIx1TFgOyncqhNfJugY30KZ6I7P40ji+g5riNsnG6YcekhsUtqxnxXFhHcfWt2Js8KM2U2/FmK1NKhjan5hPZTc4cbh1iG/ggGPfpTIai+FskSKNNU0mTmwoTn5Ntshxb/gw17uhDYMXzRQ0vhudbG8mDiuW9Vs9NIRPccBx7CF8IwlnTU4MlF4P7MMBfOMiuLEllvM2sfDEAGnweHlTbTzeYoQ/0yTcvL6Tx2RTEz6oAZjJJoZhRSFbush1bCY4RlNL4yiV43WxuQlPp/oTA5hvC5M8z/qmlor2JbU4z7elGc+K+t9KlsejKc2hfXusHFIt/G6x4UOsmllLQtxrxY02iu2oVcJJNZjIdfskDLIUcoMi6jn0q41wve2QX+2yfAC7uJbNw3rVWDQvOB12Th5WuKtQ61mN2rjfyuHfKph/aysmqhNrk7et6VYOWzVagO+wBdCuIBj5KPez08JDc7kliHfJuPHloX+/BCy40RdweoCcoCOHior1ob3dJo6xSBjczuXmxRlNaQDeNn/IUwvQjZiDaH/IwhfeC/vDVjyR6k/rnYjHKGLhiJ4hdMyw4jsVEvCvmAWifz0Wjl4dellc18yivKQ2rCXRnlk2Ti4pz+FmW/F8YkhLF/Kibcyx4HxFtWGJ8GvbIry4lskPEqfXmcOWWWuivO0kDnuRQrHxcHuJh/NBUgZ/x6LSWKQKnvG1hX7vIMuz2lB6WBOdFm2NSjgCzGDeIPuEz31OHFaIxIk5cahAoCEnbuPkbGVpdo6trH47Ry4Lx4oBK4eFivIPmjDLWEP1k7By7GMFlrOjhdckjUlzLZgaTWZSMC6l82m9nyQdOTm4ToyxsGAdDpk5+iAh6jjlhKM3fB6XdsBtDZzsyZi4+tjGBy7i7GTj2Me3rI1jH99yI3H4rivk5W28dHpuQtP3AAh9BQtvlML3N24Gxya0t5+dl4CDYWV4j8BNbnKTm9zkJje5yU1ucpOb3OQmN/2XU4XiJje5yU1ucpOb3OQmN7nJTW5yk5v+74nWCegrHfoUvuZ02LaeIK/iT+/hghp9RQSuKZhn4fKlIrjOAVaWsnV3fA3WfDPPWINl56PeBSZ+8bVdO/8hT1/bhfxdivBxvbfYBJDUUsKOXZ35xrqmRBZjttvIPOEbcnf/A24G3sAg1jPuYeIaa9GEroUWXF/0Yew30NeG72niWtetcc5eVs5QbkCnUJl7WzkpWI7F1+0YK3Oo3vcpzs3ButRhttAxp/H6nAz8fW38NKubXGEIllrqTukWYYz2M+cx1tqRvftb8UxuLq2l0RUJ7gEOXH2NrcHFcg+0cQvZTDqniXgfZMKd1/gdbOIUX+N3iIlnW+OHug61cowmwJbf5iHyaPdhNl42AxXAVkRjnR3ugIt4ZebFbWv+jnDg8/6XzsaJc6QDh23bgGVM+rrAoxw42HvZcniqn6NH4hiWoR/HOHCpj/FVaJYYH2vj55KML6+bPs7Esa+TPN6GJ3MQd2YiFJ/PCN4JNh78clV8ULdIrMc/0cbLwgpIjp1kwcg=
*/