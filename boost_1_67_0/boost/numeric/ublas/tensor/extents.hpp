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