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
/// \file strides.hpp Definition for the basic_strides template class


#ifndef BOOST_UBLAS_TENSOR_STRIDES_HPP
#define BOOST_UBLAS_TENSOR_STRIDES_HPP

#include <vector>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <cassert>

#include <boost/numeric/ublas/functional.hpp>

namespace boost { 
namespace numeric { 
namespace ublas {

using first_order = column_major;
using last_order = row_major;

template<class T>
class basic_extents;


/** @brief Template class for storing tensor strides for iteration with runtime variable size.
 *
 * Proxy template class of std::vector<int_type>.
 *
 */
template<class __int_type, class __layout>
class basic_strides
{
public:

	using base_type = std::vector<__int_type>;

	static_assert( std::numeric_limits<typename base_type::value_type>::is_integer,
								 "Static error in boost::numeric::ublas::basic_strides: type must be of type integer.");
	static_assert(!std::numeric_limits<typename base_type::value_type>::is_signed,
								"Static error in boost::numeric::ublas::basic_strides: type must be of type unsigned integer.");
	static_assert(std::is_same<__layout,first_order>::value || std::is_same<__layout,last_order>::value,
								"Static error in boost::numeric::ublas::basic_strides: layout type must either first or last order");


	using layout_type = __layout;
	using value_type = typename base_type::value_type;
	using reference = typename base_type::reference;
	using const_reference = typename base_type::const_reference;
	using size_type = typename base_type::size_type;
	using const_pointer = typename base_type::const_pointer;
	using const_iterator = typename base_type::const_iterator;


	/** @brief Default constructs basic_strides
	 *
	 * @code auto ex = basic_strides<unsigned>{};
	 */
	constexpr explicit basic_strides()
		: _base{}
	{
	}

	/** @brief Constructs basic_strides from basic_extents for the first- and last-order storage formats
	 *
	 * @code auto strides = basic_strides<unsigned>( basic_extents<std::size_t>{2,3,4} );
	 *
	 */
	template <class T>
	basic_strides(basic_extents<T> const& s)
			: _base(s.size(),1)
	{
		if(s.empty())
			return;

		if(!s.valid())
			throw std::runtime_error("Error in boost::numeric::ublas::basic_strides() : shape is not valid.");		

		if(s.is_vector() || s.is_scalar())
			return;

		if(this->size() < 2)
			throw std::runtime_error("Error in boost::numeric::ublas::basic_strides() : size of strides must be greater or equal 2.");


		if constexpr (std::is_same<layout_type,first_order>::value){
			size_type k = 1ul, kend = this->size();
			for(; k < kend; ++k)
				_base[k] = _base[k-1] * s[k-1];
		}
		else {
			size_type k = this->size()-2, kend = 0ul;
			for(; k > kend; --k)
				_base[k] = _base[k+1] * s[k+1];
			_base[0] = _base[1] * s[1];
		}
	}

	basic_strides(basic_strides const& l)
	    : _base(l._base)
	{}

	basic_strides(basic_strides && l )
	    : _base(std::move(l._base))
	{}

	basic_strides(base_type const& l )
	    : _base(l)
	{}

	basic_strides(base_type && l )
			: _base(std::move(l))
	{}

	~basic_strides() = default;


	basic_strides& operator=(basic_strides other)
	{
		swap (*this, other);
		return *this;
	}

	friend void swap(basic_strides& lhs, basic_strides& rhs) {
		std::swap(lhs._base   , rhs._base);
	}

	const_reference operator[] (size_type p) const{
		return _base[p];
	}

	const_pointer data() const{
		return _base.data();
	}

	const_reference at (size_type p) const{
		return _base.at(p);
	}


	bool empty() const{
		return _base.empty();
	}

	size_type size() const{
		return _base.size();
	}

	template<class other_layout>
	bool operator == (basic_strides<value_type, other_layout> const& b) const{
		return b.base() == this->base();
	}

	template<class other_layout>
	bool operator != (basic_strides<value_type, other_layout> const& b) const{
		return b.base() != this->base();
	}

	bool operator == (basic_strides const& b) const{
		return b._base == _base;
	}

	bool operator != (basic_strides const& b) const{
		return b._base != _base;
	}

	const_iterator begin() const{
		return _base.begin();
	}

	const_iterator end() const{
		return _base.end();
	}

	void clear() {
		this->_base.clear();
	}

	base_type const& base() const{
		return this->_base;
	}


protected:
	base_type _base;
};

template<class layout_type>
using strides = basic_strides<std::size_t, layout_type>;

namespace detail {


/** @brief Returns relative memory index with respect to a multi-index
 *
 * @code auto j = access(std::vector{3,4,5}, strides{shape{4,2,3},first_order}); @endcode
 *
 * @param[in] i multi-index of length p
 * @param[in] w stride vector of length p
 * @returns relative memory location depending on \c i and \c w
*/
BOOST_UBLAS_INLINE
template<class size_type, class layout_type>
auto access(std::vector<size_type> const& i, basic_strides<size_type,layout_type> const& w)
{
	const auto p = i.size();
	size_type sum = 0u;
	for(auto r = 0u; r < p; ++r)
		sum += i[r]*w[r];
	return sum;
}

/** @brief Returns relative memory index with respect to a multi-index
 *
 * @code auto j = access(0, strides{shape{4,2,3},first_order}, 2,3,4); @endcode
 *
 * @param[in] i   first element of the partial multi-index
 * @param[in] is  the following elements of the partial multi-index
 * @param[in] sum the current relative memory index
 * @returns relative memory location depending on \c i and \c w
*/
BOOST_UBLAS_INLINE
template<std::size_t r, class layout_type, class ... size_types>
auto access(std::size_t sum, basic_strides<std::size_t, layout_type> const& w, std::size_t i, size_types ... is)
{
	sum+=i*w[r];
	if constexpr (sizeof...(is) == 0)
		return sum;
	else
		return detail::access<r+1>(sum,w,std::forward<size_types>(is)...);
}

}

}
}
}

#endif

/* strides.hpp
IyIu8qupHneFG6YxlukBHQO+BEMY78ro+VP13+9QArX/XRkiBLKM0ctG5q+tWHcgl0C9CN+BeCTqHG1ADz+Y4uTCANMu/UAOWRWfU/BfmBXjUytgQIbGP0awc5DbjLwKHDJ2bfaGV9caft0Ol5wgj8lSbdmFZ3/l4k/PzAZiYx3DlOoH2oXd4fXMCDOVTJsX7Pd/ZDsx6uhI1gTWtpTQFrQ0q39MrDLddjNC7QXfZoP78w1pU1dHYJkXxbyj39x7RWxLMcfFSNSFL3im1vZMAGH/bnmYjUGHFfXAFr0bAOw0s7Xkr1/Z2u6/41CIFkvahT8AxUMA0u1Xr9zp22kMCRkaPmKxMni25EzEx/aUujXFmjwXnZPbEgLYtIl0ViBx6+Ie8fP9r9ljP7GjHDewcTUnAh4TnFvR66m39g75ZQTbktLLqBAlMpLWfz/mhfqEAqJ9u988Yo8erdnvKAfmTbySeqRsriaDliHZLn7c4Nv4HVLDfuZ53zB5GHIuSBPAzEWI8NOBf/ZHjAIM0QQT98zYzqV2ITM6SFUmxJ20VZyvStcYLTwtXw/QuhBOaWkzQMhnU1ftJDQQg2QS+zhZkmjh1628jbrQNbDrjcAvyvmVk1uk7rf3cwrveTc0sy6FEIApFaQf+J1JqgS4OezFBWmn/0xrIsXUbSM9dn76e/3tOCsFhSfh4nzErP3PiWFhB3CXZ9LK/rHndRu7X94DRJAem6QI/mQqI0v3KF5bbjGBEXIffZzArydcVfjD0Oe936R2mI53j+eoGmd5+0BfeXto0+lClatr0mRrWPV/gh6Yk58M0/Rv5yyfsVzbNvTGtqmlBXwwXYWwSB+h81/2RDzv5PwKteTTU81nvfkqHzkKL4t7jGbYAP0p6BMH8txu//MVecLGXJ5BPgc7eG0R6IdJvicuMRC59FMkpX7XaTp1/NVS9pfiZwP5L0igYovFaUa2yENR/6th2xFsJ8/nE2Fc64Dld195ba/5r1y7UywmtzgSfe5OK7rQt2oRy7LyyWRdmeLCpsE3bDsPdOQbkf9T7NhYt6bew7guBA49NsRf8TwaBigmHq0C9hrLla66wvelIRcZtX5d+JpCCn6yW4xlroP26nU+u1+Jn2AfyC6hJu0Svtz7WQxp2OFNW/xafMhG8vjnADGLgWl14xtJpnbsAZHSRJayRASLNu2cw9aKtR62LMe4x5y4q3Sryfx1NmODGRpCgvKSf7M0GfkD9mLljsjRqWXe/cVM8POt9e5X043MIKwkK4/989r2Hh+jrNQ0eSQAYUQBB81+eFXbSz7gRCaKR4uwXa57vh9Epq1lZLng9ftAz0pukEf510HkHVoCnLAHc+rN3v0gLXvA2Bpj2pen4xqxpnrqNes/b8sTTrEoCXPxExQ6hl0/htoaSzppJMreU1/lDcRfmwUHoaUSsb/Mdov2sTBp4fH2jyOm1NUa6PUCTA0kl/mQTmaXIwSau5FSp+DsWE781gQ/c/znOjke32dOH4Fdl1fdq5tCc4K29b2rm7aegAbwfvuLJXFgaGXAMEj4TBPOk1m/6CPb1/PSnJeEaue3oLviLbpqry2xiczCf0mQXQKDLpn28/HiGRh/JJdvnUHT4ET50022WzBwZYEwE1HCcUIFtZI+GEAGMsSmzKctTDLGC0ajBASY05dq4K7ZpIWQbrCqHMtnV5m9cGh8lSZe0dsPzHLpUQyRPYnRk+p6bUzMaU/HJUbf2+K3QYa/qQxtSfBNv+BG8oqD+Rk9CXz/g4fnaMbwzYDnKFSfKVMRKWVidiwNtgFc9NlWDhSbW5mkq/w50XGwAPAp7S/NeTbVVwzU8+XHK/1xeDb39WyZXMNzZ0XBrPgMaomxzIfXZfH7M3suVZitCJ+quVi2G/CKxULJ/B/nc9ld5euMAevzyXUYCpmYd+Ihr4/YjpBjJEl+yV95MH2Cs7mb4lt/a2rZnOboJ4RNzhtdoyQ0N1A3yqBmwcPVZes2scadW/c93wt4L+6Z4xV7/RrcFPAk8nzsEmLfExKkTB/AFa1xJ4JNu2TMWR7MZME6F3i1dCQ+P3TipR0QILRHg3Po/m6tmScVQGcVyFqM5L9Q99V4d+hFKtQ+yxWLiLFp6mt0IYy+Cor6xO7C5rS0eaYPfhdHP5QL+ZrDePjsn7Gi6A9BEJor+VCkggX5B/x4B0BdMAsD1h4+jp1z/xPiuz9NEIID5bHF9Ql33hP9s9oPE0D4XNv9eWhIcmjKCyU0RAEBlEAQjK/KKk/gJuQoJyZPOLpkgKCFsIUZ0EmifwV17iRtAVrjR0L147rYlNd2KqYL2if9c5H4se8krq6RnInz/9XGwjYRT4jkewM4A4VSM0DdrW+nOyxMwS7R9Z4kGIIHpa9Wb0gD8f4Kg4GZd4WOsGX0hAFDLza6GN3cxbnVVI1TCt+dG2cCQ3+7vynJhJFMj6LKbfGbiOjqAlK/l/8uCo9dm8AiKnOEjgcz9bTwgVRwJ18RGMzpzoc7S4RuRJBNOfC7ODGPo8ZxizVzoMYivmbP48Khbj8tohUptGqMs0V2bsemoYFRWYthtzh3TeVoPI2Tp94T1hdAWjP7QXhnlxlszCLPv8ME44XsNQczb/sycapL4gVa15G5j55vzyIAPxRJgSWTMz/0h5Que07Y6QgMOZdZHCHuPFKjWWXLIcAbx9t988jm0KHfvFNnUsfjAZBb99ss1UY0y3Aihu7GbMNu0hYQWlwVLCXGCa7M1Wj+tiHS5dLotfEZ1bORpHMcZ+kk3GsXVYSu/9ghPZi2YyhNZOozn3yqnvD8wMzGOxaQs3Fbar1u5+yKhfiCbHCAvVRLbfWBXv/R6o89Hmq3d6tz/MbFcg6ZXC3WOj8d/NfcjctzbYJtE8ubSg0n3vT39FUAjAd6OilIm+9VyJyzI0owJACSITZgFBAsAx2vJFJ+/HHtsaSgeNktW2kpFp0xZKtj9Fc8Nr41m2/fLWETw5mYOJ6dK/Jeqvxe6vDwXip6+Q/sQB36VcAqkQs/hGaKMkFu4O9MVj0mFQt2DDu7eXq7za2j2525xR4Hh/i3sKVqnVTq5j2q5Wh5DRkC5OvfTZUG7crMFQ5j7fBp0Vstt/3R0HiysRpFdvvm4LfANqV780QkKhDsXXVQoLkujW9wDEonDsIX2J129WjeQunMnsrhx/oaVKA01YuQhh9Ks7fOsv4vXxMoLjjG2IMIPSzx1LCsfkz5h3diJ0Wo13FdsY9LAU/fGIA85Cia0vY63hDRQbVrMnthZ1xgOtHHyog1bHUF+4zmrOj1GpOyCf3ltkSUbx8qvt2y9hZZfT3c1CtLb8DAvvgd+BoQ4qkfKzpAOGvAHj5qybjc60yjlBW5y/wDey16Y0cEvPiCCRQmcX6nxetFHfwKdefBWzxvDLr7dRAdPU/WrxcjCa4Kxjn6I8B0LthwRvvA07SY46N4wJHyjdC27Lk4+RnTbam3Vtv34owr8jSUIQ0V/eGQb5GkcWsvqBjH6FWjWevW1FX+pUOGJBd28cvi8Y07+++DmP+P4mfVwB8lBg7XIogumDK2FRxOGihlsDNMu9eYOLcBmmQDa/3sZI8Kan8z1B5YcUk9h8JfSvsiPwOzGa7xw9JiStMoCMcBwlBMe/Gva+SEP+fWFWN6DYyLNm7CxIn18m2TrrI5LaZZYxU5WfwHevppQ3vZ7qjaNcOXIZOFt1A2ZbOtAtb/GkjWc0YizEUpsn0RwJBcEbSyT9EjDbCwRIEgb4TsW2486UJix15gLhrhwD6yxn4+0KmOwX7K7FtCBvZhGmrPRTsqH2JIT2/p7o6awleH4wTj2BqJTebqF0lIHJzXuhqYTt+IyOdWWBeIrDtCB2ZPBQret+O+b6kBnZtXbA+jQIxsgU9HXoQeRtPGIEelazgOWrK5Rblnuv1XS7DFGh5PiWw66nkr9LMldrwbcMJ2+fHnnMQy9bJ0g7UeXtZaIkn0pr+hykg2PVKMmlxZtjtjq2OQKwjL9b2bH6aW0KF7ww82K+72i7YGAQYX5pmQY49XTGdmzLQEbT7qgZKKLk44/yC7zpRoNfNsKPI6UbLmdNT+DCM6aR2VAhC/ZH9Ttj/9MjIHsy1bM9trajaK3Zxr97ZPvErGU+W7hfTHPIvwlr+P48T6KlJ+pta6APCcdQl7Nhi8SsZy7Q/auE9BwoHY5vpXs68dGVBrldMyK385bLAVVYrvDi6TUajMPf9otYK+kBInXLqkBGieg5CBfV0eFYd3X/izfssoVyzWBK9BEQj8MBdPr7+S747v8eD4he6Q1zKfzHlbDjKGnuvFNY2dCw/lFPWP4dzjyg/FpOM4/CONP4qHOKsV1i+vGNI2HU0rqfHfefjwtwQWxeiWSvnkmB8onaRgInwv3ry3OsuQRgiqBMLWgAl6n70F+sibshdPj8rgae/ycOeBuE/4ZqkeNPT6DM+r15Dhs7o4OBwhItNM973cZylLi90X1tJ+BzKsP8ItrjZofxU7UGvwOb0PM1UHiD0GhmnO4v0ch3e02/c5UqNlCOREINZn7ZhRFEFSbS4AXcN7A527NkQEkDHOC94WTQX7Z/kbkwRVoQD1GjOTza0s7UEO9OXTzm756q7QSOV6Il5fpBFpDs7wqauEjSC+eGjvbc4jvDNIr19/AGDkcCXufq/IORVRKWcSgP5BHhCUXUnrJTcyQ3kX1ywupPbuZykZFAizDgRf63FOoul2YDPSTaAPyXiIuQ3qVU1n/lL/euWRN+xAj/UMnd45YAfynysK5FwXEi7GvF4PBBhDP+3lYgEqQywkUNw4JZkuNn15zOD/xILlMhEOn6ca5UOtSd0pJ/R5ws+GPlRwLX3hvP0NTA44MhS/ssI8SfiPbld4UXvyjvmXTdzyLCKH0yaFuBm3qhvnwejII6qfY7fW3711ZOOYf74Fq03Eq4B8JlWa1r49jwRYk3tzHE2IfJiKT11Xxjot4/nTz4SV9rVpA7BGJyQbyCyyQekQAuTUeGm5FKNuKEnpOzM4ZPyRXQri39fpcRdhsgr6syIqdj3n4dh1LTWTWewUhmDiWZCjbs1dRzhxBEdOkfLBh5TcOjZiqSfPrM0r9FUtHFR7i0b1PP1z+4HWrrf8e8YGyoyhQ6UrWg8aZEBfvvZbG+C2lLVgyS4aHSJYW3Rc7dsLYQfIhe+ampwRe+NFi+lJkPYd8dgxxK0We5AVmuB2k2goD916Y6w9WuvSYmfp170Ser9c4vrlmr6ndC37MmKzJ47NS+FJmn1WH4H5ebxGPtHF2CZfNsVSCWVjBjbwljFS3xsJeGuf9CUfOhUYKQK0gKjh+xMrTOYBrwtHUXnFS+rhzP4ihqh43D0b0TbxgUInJQadbrf0TNxdebmIU1HMDG3kkfkHytFlwfVRouIzcXJwjA81I2VfEbkuZyv0JyXAvMEafwdytQedpdnebdgoyoOxoi3n9U/fQzefeF+473SLVLuhoK4j/Jw3mh9VX9zj7YoPKJjhUchHHVCaPV8wKSwHfRBWm/YcmcNhOLNdutmxkZjZzaDd51MdaieoCq1IomW/MfWsvFkbe5bUZsXqJ7lTheotvIxYhF3znOzvSkRHucLGww1CnpLLlUBxPYrQfhjmeP/H+U6qEdChE/D2TiiKynFRrVnw535DBhJSl+EdNTRwmBJasStgAjXgiNP6D4nhS1ixHGfgWoYGdeVRBc+iMGiavszEyImgf8C63aFRS5cn7K7B50N/Mq+YxGB2yBKmpHXBktVQN47jPOm5wjz3Xve3+wDFvutTHLZscOZrKd3TqIosFxxcrxO62h3XT9DVySdAODNbweZtetuFKJposIlvGboHi5WPwG8+xNEy9e9urnbZDXu9LtULrex6+7SM1fiLV+bkRIMjuajP3u8vVcxNS8vk6bcA5sNkCR7CkofCfj9fuL2B+AK6lCQ3ZbaWmZZUf2S/x0FPk1Q/A8j7UtkwwgCyT7tgm4j82S9lTAkhX36tt8GDy1kXv1m5qD6l8vnkc9bfAqnrcyc0T1uIT8Np/zlrzxFxaeqgFFWS6PR1pscf/qPkBc6yCX5kQn5RDiiq3KlTu4im8ql1je6BteN0sNqE5MARYelTIun/OiJe4A3yME4WB1L89Wc1JOWSxhloxdafMHICf6cN16RB4oZv8Gd/sXANaigj/pEItvcBbsQwoAkXA5shTaIf2lxhCJm/OCj5owVcDoKp/kC6KpiOqFLzi56udDOrfqsu5UHXZqxkjdwmdEpgbxWu+R2aLduwYDBTgzRz1rE6SJYS+zXfgWNknOcg/s+edynhwsfh2XnKxwgIYSF5KdM95uF0jfZ6EoY7dUAtyFQxPdrPkOte5eFVVQiO9Esn5cSYfECw1M6ZRkDBiGjg/NC4UwEGx+jYptKujsg1Ru5tvMJRMV328qt4KoR6s/Lpuio2DSA6pGyxRXES4qPHhgXFLjxAxwhMlkrTL9rnS1vgHheIrrwYgaxBxy7GX+43sFcw1m0cWQqson1eSye91mY1mHpC6+HC3mEWK9BU1Lqqkbh/rgj/b0PKiDurcgwWS+qypwPWQjvzZ+C5uZbs3xe41KGAtw+TnYAHbp1IRZ4wcRek3/a6thTtBVCBD7IbeMGKHHj8146kwOIhNqL3NPdyWTOa+wbxvW4aMemNKDSXxJt+8VDkk1P+BFhQP0IVrFa/XuHxMHy/RuulWVUUYKFm+lJX6lyZIh4LATVRnvpA6KtHfFb3pyWH8vgwjUCgM1zYbwrVgBZjJInMX9BId4Xg2NPugX97hrNU3teNC6UVeBTq3g45Dv4xWYc/OwSpgsvxH68+LkLna2Y/5IMLvNhfgaZBhf6Gynn1GsT6T+tcMv4xREUCVE+/j5AHldbpdSaWCYz7oeLX7KyVyZnZI/ByIFNG9zNpq1wLIoFymCtdDkpAP8/mdNA5bjF/LYYioWlq+SeTanIO9B2HNn/uyJL80/KsIHCs+sQxwDrZWvBdpnFOCTTN8MB5Qn+WHUHh3/jIER/IjOnKj/8EKOjfk1G8rZdbqMcRV8ixqnOZoxuVRThltsfrGDmh1QtPm/xE6HnyjmjJHTHFq6bwAUVdfDKnxqm9pg0MQmoQpfMYhGbELLwD1GBheX/d+ZVXUP6HRzCJ39P3O8v8tiDNZPkhn0k7/5WQkfXi0Vr4Cuwglmn6dXMWPi4rrlcOJoD4jtnuxz9mJhqXatbMq8VsVtOHTEjxD6ItxCOpVfCXiphscozBnNCro/0PQR3JJ6ReG0el5lWD4JpWemJkrBQyKBVN0miGcLz0/Tpnl0b0sJ+OG4XPo6EmrJk3dOFgXpLnfoG0a+N0COr+DhpdCdmVSUqTyOwTOPDd/2mNtPaKh1F9fjWiOCHe64+AUv/7ghj8j9sd1HY8ejNYu1pKIg9+7ih7/NgPaVpcr4xCz2AsLSk/brookopQBVdqZnjGlsucMgM/mLDl6I7aAx4DYeTW9HuRGukhCqFkw7QDaooMzu3UKZ7OZYi2UqaLLv9BmuTYBqQikWQ6LOCjgVlrWt+yb6Jw7gwnoAHPoxXEQU9/A6SnfpY4G6rW/UkrPDZLhQT897x+21/+dOZSK7l9NUJAPZXqzhfO+UfoPa6aPcWSCQDlhpRRrDXZzoQaeaeT
*/