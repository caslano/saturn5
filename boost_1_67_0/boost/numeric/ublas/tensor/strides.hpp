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
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
*/