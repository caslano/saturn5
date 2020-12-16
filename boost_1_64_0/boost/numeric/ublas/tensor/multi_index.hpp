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
mtFx3ZsTLqoc7CjkaI63hYHlG3Fw5TZvqcsd52qYdyuZgw2Ryz2SnF97cnmLSW7MJ72G3DYfa5Uwfn1LXZVwn4Fb9wfzdyrIOFgo4t1uyG37gTsMzDQ/E7jfwB3nYFtLOF13kdH0HgUDL/bsDG3vlHlxra9A17JdhrzovClgcEaaNyE3aHCLPu8SceuWuKI1iP6zjYz1x9HXEMmKPXsSesMSD5sMXgLSuxIMzPFdCjMItz+P4vfMeghfnOdFzJaZBl+ec6E/swgr9pxI8GYTb4RnRFjWHOKZnw9xv7bVMdu8CPP26rh9/rOdjpnnP9vr8uLzH1Xn2OY/WO4OJtw8748SVuT5EnL6HDj8B+iwFyIn5sAR9zlBD8Y4PiIHdaG9msEzIkj29puwbIbqiY9OVJcDI3HUjH6vc1DnmeYaWE6CsCLPfJCzI3GKPO/Bep1LHONZD5cndbk+n+DvPtDlzvOUlI5b5iGkN63jYk7B5RmSG/Hk485OJLfHaV4iP6jP3jBeWcGVv9bIrpzAbF95fKzJEy7fPy2QzPIsCWM7TFiR51HImWdw7M+iyK75xLE/O+I6FlhwS1HI2dnCsRSF5ewicZzuM+xaBMdSqN3uRpwRnjmhrt2L8JBB5e1hcOzPmqitLCSO9ZnonkI+L5rIs2qE6SO/J8Lrci8DB1VctjfJ+DvyeP/ah8lsrzzk/H0Jk99ZuB+T2V53yG3an2H8FYKWlxJyXw6QcPk9OAdKcie9Bxn4ZCe9B0u4rPcQSe6k91Adt2rleg/TcfO7EA/X5VatPKZHMDw+OQGx1p9JCOxIhiUmx82Y8TsX2+LvXOx3TE/PJbuuvcQvJ2/d+ct3y7+juMlNbnKTm9zkJje5yU1u+g+mcjj6+Pv//8nX9vcC2gu3QNgtgoZ0347KNPgtAfaiwdFKDf2GQI3jbwkEM/AwN7EzXEHWeeGJM1ycZuFdhJ1VGrwQfiOlEu08o4TbfgocE+A4BI5PAO9+rgweDy+0vlEdytmiamylAlgOriM9+N71HZE7D/IvA/pbq8rxmtRXNR5jQrrgv6Uhb7qSlZZlL1hH7iPwjsQJyhzM0w/YAByDcCTgWFmprmw2xVdPXjAebJlW9TPkH4+6q1AHs2082laFutPsM5VXCiVOI78XlnJF7HkYC0Ed/LNxLZyf536H8a66aWUZ2j+uivHx/di6/2tinhVKRsO/dv9JJ/w3Cfwcw+IFNs0d6SDfFWffW6qYfvKX2TOe2WPxr7GMky+nTJcp3L8jXrD4Z6yOs/m3NPjHlB2DeS5y8E3oK7HZqyymvVuQvXXk4HjKVAvH5vBP5kXDXvvqesVms91GpsNof2XljAt5iVshcSsk7pJQV6xdJCuVv+QbyFA3K288K4/83Zr8XXEUV1BDiqrh2JLVj/B3MXYLLI7vR0i+P1SN3D6liO9HWHwf+pu+s/LGs/IsdV27hL2uPfDPFcJ3550Pi+XvFeRDNXAzWNciu7PPV/xD9T2BfGZljtfLNPs9brTdby/884Tw23k3x2L5/YTkd15hXJHd2e8n/mG/WZnj9TLNfv882rm+v3D0W7/nvVh+fyHat17fLKuzz1/8Qz5Xy3WN5Zn79vcV9r7tA38rXyJ//3C3zeL1bdCn+35l1Qh9G7n/bN+G8kx9OyB8H2P3vR18bxS+L9buocXzv1Hyv69yZP8b/2H/oTzZf30+9ciS1nkFzad0/01zCsf51IyXRppPMF3//HzCMn8y+fTzWE48opS/y/rwUu7THS8Ln0zzCEef7kXuQaXDpU4+CV0ler0r0hxrOTg/g/jOpfHSciUEfrP2laoc+UjDkan8a/GpsMVnVNX9rzIbFFgFOXI=
*/