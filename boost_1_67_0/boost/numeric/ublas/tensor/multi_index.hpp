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