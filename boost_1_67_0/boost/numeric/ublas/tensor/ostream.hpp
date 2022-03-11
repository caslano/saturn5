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