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

#ifndef BOOST_UBLAS_TENSOR_MULTI_INDEX_UTILITY_HPP
#define BOOST_UBLAS_TENSOR_MULTI_INDEX_UTILITY_HPP


#include <tuple>
#include <type_traits>


namespace boost   {
namespace numeric {
namespace ublas   {
namespace detail  {


template<class ... index_types>
struct has_index_impl;

template<class itype_left, class itype_right>
struct has_index_impl<itype_left, itype_right>
{
	static constexpr bool value = itype_left::value == itype_right::value;
};

template<class itype_left>
struct has_index_impl <itype_left, std::tuple<> >
{
	static constexpr bool value = false;
};

template<class itype_left, class itype_right>
struct has_index_impl <itype_left, std::tuple<itype_right> >
{
	static constexpr bool value = has_index_impl<itype_left,itype_right>::value;
};

template<class itype_left, class itype_right, class ... index_types>
struct has_index_impl <itype_left, std::tuple<itype_right, index_types...> >
{
	using next_type = has_index_impl<itype_left, std::tuple<index_types...>>;
	static constexpr bool value = has_index_impl<itype_left,itype_right>::value || next_type::value;
};
} // namespace detail



/** @brief has_index is true if index occurs once or more in a multi-index
 *
 * @note a multi-index represents as tuple of single indexes of type boost::numeric::ublas::index::index_type
 *
 * @code auto has_index_value = has_index<index_type<1>, std::tuple<index_type<2>,index_type<1>> >::value; @endcode
 *
 * @tparam index_type type of index
 * @tparam tuple_type type of std::tuple representing a multi-index
*/
template<class index_type, class tuple_type>
struct has_index
{
	static constexpr bool value = detail::has_index_impl<std::decay_t<index_type>,std::decay_t<tuple_type>>::value;
};

} // namespace ublas
} // namespace numeric
} // namespace boost

////////////////////////////////////////////////
////////////////////////////////////////////////

namespace boost   {
namespace numeric {
namespace ublas   {
namespace detail  {


template<class ... index_types>
struct valid_multi_index_impl;

template<>
struct valid_multi_index_impl<std::tuple<>>
{
	static constexpr bool value = true;
};

template<class itype>
struct valid_multi_index_impl<std::tuple<itype>>
{
	static constexpr bool value = true;
};


template<class itype, class ... index_types>
struct valid_multi_index_impl<std::tuple<itype,index_types...>>
{
	using ttype     = std::tuple<index_types...>;
	using has_index_type = has_index<itype, ttype>;

	static constexpr bool is_index_zero   = itype::value==0ul;
	static constexpr bool has_index_value = has_index_type::value && !is_index_zero;
	static constexpr bool value = !has_index_value && valid_multi_index_impl<ttype>::value;
};
} // namespace detail

/** @brief valid_multi_index is true if indexes occur only once in a multi-index
 *
 * @note a multi-index represents as tuple of single indexes of type boost::numeric::ublas::index::index_type
 *
 * @code auto valid = valid_multi_index<  std::tuple<index_type<2>,index_type<1>>  >::value;
 * @endcode
 *
 * @tparam tuple_type type of std::tuple representing a multi-index
*/
template<class tupe_type>
struct valid_multi_index
{
	static constexpr bool value = detail::valid_multi_index_impl<std::decay_t<tupe_type>>::value;
};

} // namespace ublas
} // namespace numeric
} // namespace boost

////////////////////////////////////////////////
////////////////////////////////////////////////

namespace boost   {
namespace numeric {
namespace ublas   {
namespace detail  {

template<class ... index_types >
struct number_equal_indexes_impl;

template<class ... itypes_right >
struct number_equal_indexes_impl < std::tuple<>, std::tuple<itypes_right...>>
{
	static constexpr unsigned value  = 0;
};

template<class itype, class ... itypes_left, class ... itypes_right>
struct number_equal_indexes_impl < std::tuple<itype,itypes_left...>, std::tuple<itypes_right...>>
{
	using tuple_right = std::tuple<itypes_right...>;
	using has_index_type = has_index<itype, tuple_right>;

	static constexpr bool is_index_zero   = itype::value==0ul;
	static constexpr bool has_index_value = has_index_type::value && !is_index_zero;

	using next_type = number_equal_indexes_impl< std::tuple<itypes_left...>, tuple_right >;
	static constexpr unsigned v = has_index_value ? 1 : 0;
	static constexpr unsigned value  = v + next_type::value;
};
} // namespace detail


/** @brief number_equal_indexes contains the number of equal indexes of two multi-indexes
 *
 * @note a multi-index represents as tuple of single indexes of type boost::numeric::ublas::index::index_type
 *
 *
 * @code auto num = number_equal_indexes<
 *                        std::tuple<index_type<2>,index_type<1>>,
 *                        std::tuple<index_type<1>,index_type<3>>  >::value;
 * @endcode
 *
 * @tparam tuple_type_left  type of left std::tuple representing a multi-index
 * @tparam tuple_type_right type of right std::tuple representing a multi-index
*/
template<class tuple_left, class tuple_right>
struct number_equal_indexes
{
	static constexpr unsigned value  =
	    detail::number_equal_indexes_impl< std::decay_t<tuple_left>, std::decay_t<tuple_right>>::value;
};

} // namespace ublas
} // namespace numeric
} // namespace boost


////////////////////////////////////////////////
////////////////////////////////////////////////

namespace boost   {
namespace numeric {
namespace ublas   {
namespace detail  {


template<std::size_t r, std::size_t m, class itype, class ttype>
struct index_position_impl
{
	static constexpr auto is_same = std::is_same< std::decay_t<itype>, std::decay_t<std::tuple_element_t<r,ttype>> >::value;
	static constexpr auto value   = is_same ? r : index_position_impl<r+1,m,itype,ttype>::value;
};



template<std::size_t m, class itype, class ttype>
struct index_position_impl < m, m, itype, ttype>
{
	static constexpr auto value = std::tuple_size<ttype>::value;
};

} // namespace detail



/** @brief index_position contains the zero-based index position of an index type within a multi-index
 *
 * @note a multi-index represents as tuple of single indexes of type boost::numeric::ublas::index::index_type
 *
 * @code auto num = index_position<
 *                       index_type<1>,
 *                       std::tuple<index_type<2>,index_type<1>>  >::value;
 * @endcode
 *
 * @returns value returns 0 and N-1 if index_type is found, N otherwise where N is tuple_size_v<tuple_type>.
 *
 * @tparam index_type type of index
 * @tparam tuple_type type of std::tuple that is searched for index
*/
template<class index_type, class tuple_type>
struct index_position
{
	static constexpr auto value  = detail::index_position_impl<0ul,std::tuple_size<tuple_type>::value,std::decay_t<index_type>,std::decay_t<tuple_type>>::value;
};

} // namespace ublas
} // namespace numeric
} // namespace boost

////////////////////////////////////////////////
////////////////////////////////////////////////


namespace boost   {
namespace numeric {
namespace ublas   {
namespace detail  {

template<std::size_t r, std::size_t m>
struct index_position_pairs_impl
{
	template<class array_type, class tuple_left, class tuple_right>
	static constexpr void run(array_type& out, tuple_left const& lhs, tuple_right const& rhs, std::size_t p)
	{
		using index_type     = std::tuple_element_t<r-1,tuple_left>;
		using has_index_type = has_index<index_type, tuple_right>;
		using get_index_type = index_position<index_type,tuple_right>;
		using next_type      = index_position_pairs_impl<r+1,m>;
		if constexpr ( has_index_type::value && index_type::value != 0)
		    out[p++] = std::make_pair(r-1,get_index_type::value);
		next_type::run( out, lhs, rhs, p );
	}
};

template<std::size_t m>
struct index_position_pairs_impl<m,m>
{
	template<class array_type, class tuple_left, class tuple_right>
	static constexpr void run(array_type& out, tuple_left const& , tuple_right const& , std::size_t p)
	{
		using index_type     = std::tuple_element_t<m-1,tuple_left>;
		using has_index_type = has_index<index_type, tuple_right>;
		using get_index_type = index_position<index_type, tuple_right>;
		if constexpr ( has_index_type::value && index_type::value != 0 )
		    out[p] = std::make_pair(m-1,get_index_type::value);
	}
};

template<std::size_t r>
struct index_position_pairs_impl<r,0>
{
	template<class array_type, class tuple_left, class tuple_right>
	static constexpr void run(array_type&, tuple_left const& , tuple_right const& , std::size_t)
	{}
};


} // namespace detail


/** @brief index_position_pairs returns zero-based index positions of matching indexes of two multi-indexes
 *
 * @note a multi-index represents as tuple of single indexes of type boost::numeric::ublas::index::index_type
 *
 * @code auto pairs = index_position_pairs(std::make_tuple(_a,_b), std::make_tuple(_b,_c));
 * @endcode
 *
 * @returns a std::array instance containing index position pairs of type std::pair<std::size_t, std::size_t>.
 *
 * @param lhs left std::tuple instance representing a multi-index
 * @param rhs right std::tuple instance representing a multi-index
*/
template<class tuple_left, class tuple_right>
auto index_position_pairs(tuple_left const& lhs, tuple_right const& rhs)
{
	using pair_type = std::pair<std::size_t,std::size_t>;
	constexpr auto m = std::tuple_size<tuple_left >::value;
	constexpr auto p = number_equal_indexes<tuple_left, tuple_right>::value;
	auto array = std::array<pair_type,p>{};
	detail::index_position_pairs_impl<1,m>::run(array, lhs, rhs,0);
	return array;
}

} // namespace ublas
} // namespace numeric
} // namespace boost

////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


namespace boost   {
namespace numeric {
namespace ublas   {
namespace detail  {

template<class array_type, std::size_t ... R>
constexpr auto array_to_vector_impl( array_type const& array, std::index_sequence<R...> )
{
	return std::make_pair(
	      std::vector<std::size_t>{std::get<0>( std::get<R>(array) )+1 ...} ,
	      std::vector<std::size_t>{std::get<1>( std::get<R>(array) )+1 ...} );
}

} // namespace detail


/** @brief array_to_vector converts a std::array of zero-based index position pairs into two std::vector of one-based index positions
 *
 * @code auto two_vectors = array_to_vector(std::make_array ( std::make_pair(1,2), std::make_pair(3,4) ) ) ;
 * @endcode
 *
 * @returns two std::vector of one-based index positions
 *
 * @param array std::array of zero-based index position pairs
*/
template<class pair_type, std::size_t N>
constexpr auto array_to_vector( std::array<pair_type,N> const& array)
{
	constexpr auto sequence = std::make_index_sequence<N>{};
	return detail::array_to_vector_impl( array, sequence );
}


} // namespace ublas
} // namespace numeric
} // namespace boost


#endif // _BOOST_UBLAS_TENSOR_MULTI_INDEX_UTILITY_HPP_

/* multi_index_utility.hpp
vM4YxzOuQAomwhFgg97rFC/Tai9FjhfOuapZTJC7rEOsmJ7Fm3ONZGPrUs42NtptHChmY/MINjb+DRvFHPYTBxuDYOMOwkb7KjhHO+Mj2LnDP2DnMUs723mE1U5jrHe085gR7Dzib9gpvoe/ppzhEv4++hCctwE77+B2Fnti79ifH8Q8/pLWkiL9mduLeQ/AeWcA8zJD7kFsc4jTyvax2jHvgJ536TcYtokynvKOk/KOw7zGOLIf5s1FQaznD1vyV0r5K+Wy9fzDet4TLHlrpby1mNc6F8EmidzlJO5yEncjZQ76sBONQ6nKxfv7z47nS9P31gE4Jw/g53HiM8a3CmOxH/vMY4acWl02jJzlxLyH+4btq4Xa1wWsEdM9hBI4DoZjBruGe3PE9gVXNZbxhdrYcZivyfma7k0j1tdhPta1HL77bVxxTaDY248jdyCbAbmtrVi452BttAeorWHcdkV8D2Us9ts5+PuEWen7KUdH3qE+x41cn/o85Dr2mfuOsnFCxn3k9SpkzBfLdehWtfR9V8LHr+/g2JbdB3kL62wxVqYojuPDNMz/tvKg4z0hpt+IXZ5fk8cV6ft+S8RfVe4Eia1OrfnRA9hcJN2zmI24j39m10Vvs88TlCX1e1B9I95/Kjjcf6r4k/ef8LqI9RXybWnTPak++Dy1aiazE+fT5nrpnsAL0kr42BKleWQG/VgIdaKvDuQ3B8QuWVoYphSplz0x/5iS8pJSkLWAzaQTSvpQaTD3sbfNYyFERVka8nwPPhyAWFeJgU0HjLf7gxBrLzHqBg3Sbdj3HYZvDf6WSbrnY37m9t6kW1zDK/x6mseQ2schyGkBjigDFoDhwkujDQSxnGXgM/dzNn7eFdtMXTnlQX4L1qOGeEYfk4chdvPgmA/HAjh2hmMXOHaFYzep/+7OztRe5HfAVjrMIQ96p+gcEtvD28wvvHdibg8/L8sVvUHfNa/RfdrGd23tgTrrSO3BGGM9mP9hagukD0o5VVnfPJ9719oWput10YbYvXI70duCl/Rb2oJe137E71FGqse73zXX46P42Vu0Hl9EfGP9+mgPqseFjnVo1F35H9TdD++Kuht5nrXi8jzjdfQ9eC2Nqd3vYV0Z172mYdVcPxPEtSDmuUDZRRmjnFXsevA921iadL4ONrgTITaj2HhQyY+9KDZ7/4W5hWms42VjW76LlcWvlTE+Xyv8R5DeLGfroF67fJHnqmPPOWfOx0/0bHvqO29BLy9l8n3OP/nZd+9vbNzz/vD8xKHnfQJ9D/nPH/n2gy1a4vQ9v9q576rVLgTjJ41m8ssbJ27dPDB8xmbT2rY858izV4GYofznV+6qOHH3PY9of/HbaGLbNaHjnI3ytkBs4tuzvl5/TGbFN/aY8v3t8F2F5TY2nht576mflgu9sMuKodNWfACuc0cx+bffLnniBRscts9mDy3MTZjy1mrQ/1C+ZZ327W69A+uVDQ+M3fVD7Wm4v4T67x1Xc4va3Hz3FqPWm7rTyj74Ul29gsmf2uXpB3/75vCvFxy8yrJXH7ItTAZ+Upj8nOeWmbpvWdcv7Wstc+uja735IMzzkL/Sc7Gxye2n7/3amP0ya6zbDS/iuBnl5x7fH7qm/NNXbz17rd9OOuYAePHGMmOYfMK4uP/xbT4ZmrTm8QfuuuAi2Fj5whJMvnP18XfdtdPEGU+cueN1b6y7Lfxw5izkX71l59c/T9vo6WM/fPP+WEnsMbgXivLSsxOrrbH7t1Mnfj+xavx1fbB5+dxSLPeqJW5ae/PDfpxyasXFsyMnwSb0a9D+L1qCKxbWOeyQ25bb7LAxb/z6EVTxkkw+8c5dD/l59Vm37j9/6ys=
*/