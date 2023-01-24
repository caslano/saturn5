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
sw9WZ4iGH4VyPueX8DLKsSAGCe6yh13jg4h5DeW+okvk714aoavJWAm9TmXVPzBpRBYZ5MyB2hTTWZZkn3zQdUNiFr7nVOFgwcgHBPoyUf7QwwhO8ugd/ipUPHDfFPNAB4rkKqiMF4lDt1z12aTxVsaqce0cmcTi0RpYnjB6x1ZmT6lXdDUdggGYYtCce/IJJPkMMBysfybCpTOX8UXw5hLLzxYjiVl39rtbz5i2r3K8CzbSpA2o1lNH7HfcVnT8nD8BWaRkUA8RWgYmxWaeHgqPs9WRg1Noi8j/frcn3KWrjEJo8My2o93b6MHWPTOvYNi3j04lqQC/uw9qiKg4T5CnBBKylVfPzr0ICp4W91rJaaGszLnkTLAre1CfkcpQ6YrjXYjUq6H300puSAMzpW3pHVtEcGK9azOM9C3pW/JFhyn9wUUIeWEMRZ4elYNFCpGFxJRVyVOfTTvs2MgEsshH6b9YscwopT/hVCuCqEN6VW0pr5ic9LSwZY1lZoVj4Wkq78U66EjW2/IfqP4FThGuRmnsHOsXwcXYxSIDV3eQ9vG1XXCYOHZRMk/NW0y9/Y5Ee9QyQ4fLwIEf/oZVeAJ19JKyK4RGQrBA8WjdkgbgsEO6i/8rFVz4PCZlw6Jsw7oG2pGYt2GFfuvXWsJ3J7ODw5PTRAcDT5EBdLvrahtIJAIc+B/DAS2/hHVEeFGb4stQ70WM/NLVG4OC
*/