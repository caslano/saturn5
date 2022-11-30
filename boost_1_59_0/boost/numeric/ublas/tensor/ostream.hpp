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

#ifndef BOOST_UBLAS_TENSOR_OSTREAM_HPP
#define BOOST_UBLAS_TENSOR_OSTREAM_HPP

#include <ostream>
#include <complex>

namespace boost {
namespace numeric {
namespace ublas {
namespace detail {

template <class value_type>
void print(std::ostream& out, value_type const& p)
{
	out << p << " ";
}

template <class value_type>
void print(std::ostream& out, const std::complex<value_type>& p)
{
	out << std::real(p) << "+" << std::imag(p) << "i ";
}


template <class size_type, class value_type>
void print(std::ostream& out, size_type r, const value_type* p, const size_type* w, const size_type* n)
{

	if(r < 2)
	{
		out << "[ ... " << std::endl;

		for(auto row = 0u; row < n[0]; p += w[0], ++row) // iterate over one column
		{
			auto p1 = p;
			for(auto col = 0u; col < n[1]; p1 += w[1], ++col) // iterate over first row
			{
				print(out,*p1);
			}
			if(row < n[0]-1)
				out << "; " << std::endl;
		}
		out << "]";
	}
	else
	{
		out << "cat("<< r+1 <<",..." << std::endl;
		for(auto d = 0u; d < n[r]-1; p += w[r], ++d){
			print(out, r-1, p, w, n);
			out << ",..." << std::endl;
		}
		print(out, r-1, p, w, n);
	}
	if(r>1)
		out << ")";
}

////////////////////////////


}
}
}
}


namespace boost {
namespace numeric {
namespace ublas {

template<class T, class F, class A>
class tensor;

template<class T, class F, class A>
class matrix;

template<class T, class A>
class vector;

}
}
}


template <class V, class F, class A>
std::ostream& operator << (std::ostream& out, boost::numeric::ublas::tensor<V,F,A> const& t)
{

	if(t.extents().is_scalar()){
		out << '[';
		boost::numeric::ublas::detail::print(out,t[0]);
		out << ']';
	}
	else if(t.extents().is_vector()) {
		const auto& cat = t.extents().at(0) > t.extents().at(1) ? ';' : ',';
		out << '[';
		for(auto i = 0u; i < t.size()-1; ++i){
			boost::numeric::ublas::detail::print(out,t[i]);
			out << cat << ' ';
		}
		boost::numeric::ublas::detail::print(out,t[t.size()-1]);
		out << ']';
	}
	else{
		boost::numeric::ublas::detail::print(out, t.rank()-1, t.data(), t.strides().data(), t.extents().data());
	}
	return out;
}


#endif

/* ostream.hpp
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
*/