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

#ifndef BOOST_UBLAS_TENSOR_MULTI_INDEX_HPP
#define BOOST_UBLAS_TENSOR_MULTI_INDEX_HPP


#include <cstddef>
#include <array>
#include <vector>

#include "multi_index_utility.hpp"

namespace boost {
namespace numeric {
namespace ublas {
namespace index {

template<std::size_t I>
struct index_type;

} // namespace indices
}
}
}


namespace boost {
namespace numeric {
namespace ublas {

/** @brief Proxy class for the einstein summation notation
 *
 * Denotes an array of index_type types ::_a for 0<=K<=16 is used in tensor::operator()
*/
template<std::size_t N>
class multi_index
{
public:
	multi_index() = delete;

	template<std::size_t I, class ... indexes>
	constexpr multi_index(index::index_type<I> const& i, indexes ... is )
	  : _base{i(), is()... }
	{
		static_assert( sizeof...(is)+1 == N,
		               "Static assert in boost::numeric::ublas::multi_index: number of constructor arguments is not equal to the template parameter." );

		static_assert( valid_multi_index<std::tuple<index::index_type<I>, indexes ...> >::value,
		               "Static assert in boost::numeric::ublas::multi_index: indexes occur twice in multi-index." );
	}

	multi_index(multi_index const& other)
	  : _base(other._base)
	{
	}

	multi_index& operator=(multi_index const& other)
	{
		this->_base = other._base;
		return *this;
	}

	~multi_index() = default;

	auto const& base() const { return _base; }
	constexpr auto size() const { return _base.size(); }
	constexpr auto at(std::size_t i) const { return _base.at(i); }
	constexpr auto operator[](std::size_t i) const { return _base.at(i); }

private:
	std::array<std::size_t, N> _base;
};

template<std::size_t K, std::size_t N>
constexpr auto get(multi_index<N> const& m) { return std::get<K>(m.base()); }

template<std::size_t M, std::size_t N>
auto array_to_vector(multi_index<M> const& lhs, multi_index<N> const& rhs)
{
	using vtype = std::vector<std::size_t>;

	auto pair_of_vector = std::make_pair( vtype {}, vtype{}  );

	for(auto i = 0u; i < N; ++i)
		for(auto j = 0u; j < M; ++j)
			if ( lhs.at(i) == rhs.at(j) && lhs.at(i) != boost::numeric::ublas::index::_())
				pair_of_vector.first .push_back( i+1 ),
				    pair_of_vector.second.push_back( j+1 );

	return pair_of_vector;
}





} // namespace ublas
} // namespace numeric
} // namespace boost

#endif // MULTI_INDEX_HPP

/* multi_index.hpp
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
*/