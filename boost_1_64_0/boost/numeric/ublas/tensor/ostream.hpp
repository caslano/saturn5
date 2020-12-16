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
gPv9EC2sp3MsO/tF+zcc5A65iefShYCloN+u6o5XoPEFrvJoZWV13O3w0UX17v4uzxL9dDHQfRwzf7QW+RJQW9rtGHhdtUU2z9M7CHeSKBRpru3DvNgOv0m5Z1zzvoYFpYsI3cXXjPFN//WaU7DT1z6AqKfsF3usoKx2n+Sxv1g99ROXKaGvVmWwzRKPn6e4r4pfN/uKnRtS7Cu6H5XoV4si4XWfgyjdva/e4r7S/X4NPS8nLyNHXxGv1Puq+PWW9VXx6833Vfhf3FcTua8Oc0b/kGUF/B1wO/pqxBu6r6T3SV206ZEV31/OvtH8LMecpMdOEaUfQX+sdPYH0zt9WNz7w8RtoNpVUM21HF1L6c+LTSg1+SjhKefHMq5ASP1lNeT3RAj7o1K36QzlJS0Y9uJZpm1BeDDEes950Ht83rA3qPSYbE4/HmLdJ9g5pt8w30Uo4D2sFwVCC0I3St3Iq3ifBN2QsOINzlabUCECr5/oOb0e6XdqetB6QmEvyEm3Go60mnCCbsXQCrLmIVk7NXnj+dmcsxNkrrQyUbY6cA6f9qh5YJhHyVbjj+Nli2eClGRL+aExD3B+TeRYuu853lXO8rnv36L0N60+6OuAtVR8xQo55Y34pC5vJm4m1Zl1DS5r2n6ZfqdVgJVAni2T0UU16kNHJJvan2sj8cr1zEf5NsNqUs1XFvO4zcqDT71DrtlX7ijRVsJeuIDjNN1nrBxYaEoZOoICn2ilZNB7DQTIygrVGjLYiLRdAC2D80IDbRnU6ccBd2p6T+uw16fkbzfij7XS8ndNnPzlc96rW/O4avxWqFzl7HPoGtwWl1DZC/gZPfAT+dxd0FhAPuWt7XJ6Gr8fGoTQL8cC5Uc4SG+tx2Ljt5CZL4PTJWif6zURBTURKlvSMRI5Q2NE6z+Zhl6q/d+OeJKfrbufobf8DNr9zD35GfodERn/5mPfKv7hxBUf9xj6ydsnN86f3/KzZvcz9ORnwe5n9MnPiN3PylvuF+d+Zt3ys3v3M/GWn6231BbC3eYhuc2Auw1Ay/3WWnoW/5eYPxvGMbUv7THdRX8rX4c7+e93pc8F//2+wJjmvwssHrMestEm37lie59I8avh908R53WUfR/eR5jLvg757APRmX0eCthHois/a77HmG+PRL5sKy7YVjyPbebPQTgQYRfy6QE/tiHvzs/Ml/cAMOe48H2Hy/suwgz2JQjLuQJhJvsSyHfbbxB25HjNt7gJvp2pvNSGxKcLwtaybggjsu0sxbe7Bb4cr32vGplvkPmavlcXcHl7I5T59RGGTwvTtWI606elK9Ody/XsxvXrzvQ1ep3D68C1cu4FlDF9FtNnM10b7scc9vXLQ3gx872EfRRHsk9iiaw/whs5/4USj/NtJJ2dbf05X8m/nvO9EigeicM+IZPYx3Ay+15djfAq9qlCmpjGvlgzEF7LvlrVCEsRfpZ9s7azL9ZTko7LgTjWbaGvczlkflu4HL24/v0Q9mXftAH8PIifi9hXbSz7po1jX7QHEI5kn8XRCF9QctK4G+F4hN9GeCnCHyC8TKo8HL9fyj3Co+w79zf2nfu7TOdyn9A6EumCqtwdaByqXzX71tSwL9tCLu9N3E43s4/aMoSL5PqE22kFws3s2/kY+3I+LucPhF+RcwS34xpux/sRjkZGX0D4nKV8QfdYyhd0r6XoX0P4RYQHLcX3HYTrEJ5E+IAcdx4V39qj8CMIb0HYE+FnEA5GeCvCYZye42veL2PTyNR9Mxx+GWfQJ+NM2SP9N/hjJLNL2nYKtklDtO9FC/wuzvpcJPG5OIN2TEn9Lf7N9kymr8XyOYgH7J6DeMDJOaAtAy2gpgy8AQc=
*/