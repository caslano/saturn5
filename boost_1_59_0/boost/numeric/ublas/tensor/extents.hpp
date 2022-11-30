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


#ifndef BOOST_NUMERIC_UBLAS_TENSOR_EXTENTS_HPP
#define BOOST_NUMERIC_UBLAS_TENSOR_EXTENTS_HPP

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <vector>

#include <cassert>

namespace boost {
namespace numeric {
namespace ublas {


/** @brief Template class for storing tensor extents with runtime variable size.
 *
 * Proxy template class of std::vector<int_type>.
 *
 */
template<class int_type>
class basic_extents
{
	static_assert( std::numeric_limits<typename std::vector<int_type>::value_type>::is_integer, "Static error in basic_layout: type must be of type integer.");
	static_assert(!std::numeric_limits<typename std::vector<int_type>::value_type>::is_signed,  "Static error in basic_layout: type must be of type unsigned integer.");

public:
	using base_type = std::vector<int_type>;
	using value_type = typename base_type::value_type;
	using const_reference = typename base_type::const_reference;
	using reference = typename base_type::reference;
	using size_type = typename base_type::size_type;
	using const_pointer = typename base_type::const_pointer;
	using const_iterator = typename base_type::const_iterator;


	/** @brief Default constructs basic_extents
	 *
	 * @code auto ex = basic_extents<unsigned>{};
	 */
	constexpr explicit basic_extents()
	  : _base{}
	{
	}

	/** @brief Copy constructs basic_extents from a one-dimensional container
	 *
	 * @code auto ex = basic_extents<unsigned>(  std::vector<unsigned>(3u,3u) );
	 *
	 * @note checks if size > 1 and all elements > 0
	 *
	 * @param b one-dimensional std::vector<int_type> container
	 */
	explicit basic_extents(base_type const& b)
	  : _base(b)
	{
		if (!this->valid()){
			throw std::length_error("Error in basic_extents::basic_extents() : shape tuple is not a valid permutation: has zero elements.");
		}
	}

	/** @brief Move constructs basic_extents from a one-dimensional container
	 *
	 * @code auto ex = basic_extents<unsigned>(  std::vector<unsigned>(3u,3u) );
	 *
	 * @note checks if size > 1 and all elements > 0
	 *
	 * @param b one-dimensional container of type std::vector<int_type>
	 */
	explicit basic_extents(base_type && b)
	  : _base(std::move(b))
	{
		if (!this->valid()){
			throw std::length_error("Error in basic_extents::basic_extents() : shape tuple is not a valid permutation: has zero elements.");
		}
	}

	/** @brief Constructs basic_extents from an initializer list
	 *
	 * @code auto ex = basic_extents<unsigned>{3,2,4};
	 *
	 * @note checks if size > 1 and all elements > 0
	 *
	 * @param l one-dimensional list of type std::initializer<int_type>
	 */
	basic_extents(std::initializer_list<value_type> l)
	  : basic_extents( base_type(std::move(l)) )
	{
	}

	/** @brief Constructs basic_extents from a range specified by two iterators
	 *
	 * @code auto ex = basic_extents<unsigned>(a.begin(), a.end());
	 *
	 * @note checks if size > 1 and all elements > 0
	 *
	 * @param first iterator pointing to the first element
	 * @param last iterator pointing to the next position after the last element
	 */
	basic_extents(const_iterator first, const_iterator last)
	  : basic_extents ( base_type( first,last ) )
	{
	}

	/** @brief Copy constructs basic_extents */
	basic_extents(basic_extents const& l )
	  : _base(l._base)
	{
	}

	/** @brief Move constructs basic_extents */
	basic_extents(basic_extents && l ) noexcept
	  : _base(std::move(l._base))
	{
	}

	~basic_extents() = default;

	basic_extents& operator=(basic_extents other) noexcept
	{
		swap (*this, other);
		return *this;
	}

	friend void swap(basic_extents& lhs, basic_extents& rhs) {
		std::swap(lhs._base   , rhs._base   );
	}



	/** @brief Returns true if this has a scalar shape
	 *
	 * @returns true if (1,1,[1,...,1])
	*/
	bool is_scalar() const
	{
		return
		    _base.size() != 0 &&
		    std::all_of(_base.begin(), _base.end(),
		                [](const_reference a){ return a == 1;});
	}

	/** @brief Returns true if this has a vector shape
	 *
	 * @returns true if (1,n,[1,...,1]) or (n,1,[1,...,1]) with n > 1
	*/
	bool is_vector() const
	{
		if(_base.size() == 0){
			return false;
		}

		if(_base.size() == 1){
			return _base.at(0) > 1;
		}

		auto greater_one = [](const_reference a){ return a >  1;};
		auto equal_one   = [](const_reference a){ return a == 1;};

		return
		    std::any_of(_base.begin(),   _base.begin()+2, greater_one) &&
		    std::any_of(_base.begin(),   _base.begin()+2, equal_one  ) &&
		    std::all_of(_base.begin()+2, _base.end(),     equal_one);
	}

	/** @brief Returns true if this has a matrix shape
	 *
	 * @returns true if (m,n,[1,...,1]) with m > 1 and n > 1
	*/
	bool is_matrix() const
	{
		if(_base.size() < 2){
			return false;
		}

		auto greater_one = [](const_reference a){ return a >  1;};
		auto equal_one   = [](const_reference a){ return a == 1;};

		return
		    std::all_of(_base.begin(),   _base.begin()+2, greater_one) &&
		    std::all_of(_base.begin()+2, _base.end(),     equal_one  );
	}

	/** @brief Returns true if this is has a tensor shape
	 *
	 * @returns true if !empty() && !is_scalar() && !is_vector() && !is_matrix()
	*/
	bool is_tensor() const
	{
		if(_base.size() < 3){
			return false;
		}

		auto greater_one = [](const_reference a){ return a > 1;};

		return std::any_of(_base.begin()+2, _base.end(), greater_one);
	}

	const_pointer data() const
	{
		return this->_base.data();
	}

	const_reference operator[] (size_type p) const
	{
		return this->_base[p];
	}

	const_reference at (size_type p) const
	{
		return this->_base.at(p);
	}

	reference operator[] (size_type p)
	{
		return this->_base[p];
	}

	reference at (size_type p)
	{
		return this->_base.at(p);
	}


	bool empty() const
	{
		return this->_base.empty();
	}

	size_type size() const
	{
		return this->_base.size();
	}

	/** @brief Returns true if size > 1 and all elements > 0 */
	bool valid() const
	{
		return
		    this->size() > 1 &&
		    std::none_of(_base.begin(), _base.end(),
		                 [](const_reference a){ return a == value_type(0); });
	}

	/** @brief Returns the number of elements a tensor holds with this */
	size_type product() const
	{
		if(_base.empty()){
			return 0;
		}

		return std::accumulate(_base.begin(), _base.end(), 1ul, std::multiplies<>());

	}


	/** @brief Eliminates singleton dimensions when size > 2
	 *
	 * squeeze {  1,1} -> {  1,1}
	 * squeeze {  2,1} -> {  2,1}
	 * squeeze {  1,2} -> {  1,2}
	 *
	 * squeeze {1,2,3} -> {  2,3}
	 * squeeze {2,1,3} -> {  2,3}
	 * squeeze {1,3,1} -> {  3,1}
	 *
	*/
	basic_extents squeeze() const
	{
		if(this->size() <= 2){
			return *this;
		}

		auto new_extent = basic_extents{};
		auto insert_iter = std::back_insert_iterator<typename basic_extents::base_type>(new_extent._base);
		std::remove_copy(this->_base.begin(), this->_base.end(), insert_iter ,value_type{1});
		return new_extent;

	}

	void clear()
	{
		this->_base.clear();
	}

	bool operator == (basic_extents const& b) const
	{
		return _base == b._base;
	}

	bool operator != (basic_extents const& b) const
	{
		return !( _base == b._base );
	}

	const_iterator
	begin() const
	{
		return _base.begin();
	}

	const_iterator
	end() const
	{
		return _base.end();
	}

	base_type const& base() const { return _base; }

private:

	base_type _base;

};

using shape = basic_extents<std::size_t>;

} // namespace ublas
} // namespace numeric
} // namespace boost

#endif

/* extents.hpp
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
*/