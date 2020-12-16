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
u6yT/PB5IlurkY4ZgekqBgnH+3KMb6cnHMZ6YLoNeTe0J8jNkUUh6IfLUz+sgH4Y0jLJaEzLedPZjng2UBjSsolYq9afSGk53gdHYlD/U0aNV5SFpYop5XJJNZdnOmbwP4H85aIlYaRfEspdciEcSkllHTBLSD6O5OzvpejvlZWS6iWAMxY+F+C8NDvDoJmHowyOpcGLPJa3hLJMJc9bSXknQN5yKS/o1PPw2UC5Uk15aoqUtxSencsbT3knUF425i4FcV8VcW1+Xs0vyGjKIiYrsNJQ1p+MDuQUJquCfBVKNB5XY30sjkxWC7JxSn9W05gQZVhuJfKi2QGSLQu8WiUTzeaQqPOW4zJkbgH1MhrqejngirSiEivk8ukhlZkypOUH03GsIpsUamstx3qND4pqxb+A109+87gMRnODaorNa1CGfucSAymzrAJl0VRc0MmvOoX5n2WgIj4vpWQZS5mmjML5wgq6Pywu+WROBXo0OZAThkki0e62cPRFG86osURmUMuqsfx8kd0sRQ1YzytRPW9UVNdQXNZjSAwdq5COyY46YumhjKxBfDbyr0r5pxXvc1oul0inhAqTyOiDq5OeHanuVq5EH1IxdV42kddYoTz+laz+uIxVgminq7G2i/ZmQTmv1zWw7VJhVJ+rYh1pmXRsUNma6m9Nqf5qlTjUVpOa1fLZaCo3lMiDldG8hrY7Q8Xr80+0bRaDtSkGkygG66BdjJJT9D7LP6uxdAHn/C1QLhRauq7kQ4W93JxzwTm0/ccyfZ7eySYRaouvLRjy8e9NIQtOp+/0VhJ4Q2qHr7MzyL6s/W2zVTZ38YUjoI/PxQxaONRDXPG9ZWBeXygivh9GWeRsnheZEcZyl5Cw6b7Zqm+Wt0PkG23Jx0wRWIXVjlaYNZKNY2TMF8YZR8Tvne6j79clZb0dnkA7zQHGSvI2f8Af7vC1ivLG6dhM+AYMRGS/lzIwk99LG3Kbb8tY8qg9obbZYl5nYCb7qiR5wDcrAhcowQjZUG1gNttrBBaeyc3GQHKsVsdCNr/GK616xpHaxARDv61NLKtj5tgsp8vtsVnewGz1PtHAbPW+go6Z29+KhtxW1koGZquHlQ3MFO+/ev1frYyeUAL8a+DzoaCgDMphsjKSHdJtyEaR7Kn1Ddlokn0pycaQ7MJWQ7Y8yH4C2amjDNmKJFtqCUO2FskmSbxJJLtBkq0PsrXh/QXRMkPWALI5INtMMWSNJFtfkk0G2cEgu0aSTaMyDpDK2Izy1kq8LYi3mcTzkGyyJPNSXq+UNwKyZ0F2pCRLUd5bpbzzSfZliSE7BmRjYPDdX8p7KsimgWxbSXYHyDIg80uyu8iWkCR7kOL3qSR7EmTnQt4WSfY6yF4CWVCy5V2QrQVxby2T4lfFbZ4ryQJVPO/Hkr5tQJYHzjuSLEp5z5DKyJBsfrkhWwCyCyDvslLeA0D2A8iWl2R3U945pYbsKZD5QNc9kn0fV/FYJaW831Zx396W8v5CNmsSb3Q1r492STammsdvkiSrrOa29En1W015qyTeBtW8Pd7eLbU/yhuQbNmimtu8ipS3rZrbfJ0kCyLP3Bf6STZZkiVBtgDi8rjcJkF2GcgyUn3sRb5tIvEOAtmbwFtNkp1CZewgyU4DWS34/6AkuwZk7SBbW5LdRHl7JNmtIDt8lLl+b6f4BSTZfWTLFpLsEYrfplL8ngPZbRZ9X5G+7STZNyAbC+PSOpJswxqubxVpvJpSw9vGVIm3UQ2P6b3yuFHDfeuWZFuRbECSdYDMA/qbJZm/hsfvMUnWReV+JclmkX0Ryd90DfetTuLtArJDoYy3pfq9mvJeL8lureHj1c2S7HaQvQA=
*/