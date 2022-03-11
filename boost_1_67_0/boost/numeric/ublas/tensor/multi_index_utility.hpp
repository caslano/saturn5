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