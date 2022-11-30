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
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
*/