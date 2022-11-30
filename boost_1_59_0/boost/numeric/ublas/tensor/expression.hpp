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

#ifndef BOOST_UBLAS_TENSOR_EXPRESSIONS_HPP
#define BOOST_UBLAS_TENSOR_EXPRESSIONS_HPP

#include <cstddef>
#include <boost/numeric/ublas/expression_types.hpp>


namespace boost   {
namespace numeric {
namespace ublas   {


template<class element_type, class storage_format, class storage_type>
class tensor;

template<class size_type>
class basic_extents;


//TODO: put in fwd.hpp
struct tensor_tag {};

}
}
}

namespace boost   {
namespace numeric {
namespace ublas   {
namespace detail  {

/** @\brief base class for tensor expressions
 *
 * \note implements crtp - no use of virtual function calls
 *
 * \tparam T type of the tensor
 * \tparam E type of the derived expression (crtp)
 *
 **/
template<class T, class E>
struct tensor_expression
    : public ublas_expression<E>
{
	//	static const unsigned complexity = 0;
	using expression_type = E;
	using type_category = tensor_tag;
	using tensor_type = T;

	BOOST_UBLAS_INLINE
	auto const& operator()() const { return *static_cast<const expression_type*> (this); }

protected :
	explicit tensor_expression() = default;
	tensor_expression(const tensor_expression&) = delete;
	tensor_expression& operator=(const tensor_expression&) = delete;
};


template<class T, class EL, class ER, class OP>
struct binary_tensor_expression
    : public tensor_expression <T, binary_tensor_expression<T,EL,ER,OP>>
{
	using self_type = binary_tensor_expression<T,EL,ER,OP>;
	using tensor_type  = T;
	using binary_operation = OP;
	using expression_type_left  = EL;
	using expression_type_right = ER;
	using derived_type =  tensor_expression <tensor_type,self_type>;

	using size_type = typename tensor_type::size_type;

	explicit binary_tensor_expression(expression_type_left  const& l, expression_type_right const& r, binary_operation o)
	  : el(l) , er(r) , op(o) {}
	binary_tensor_expression() = delete;
	binary_tensor_expression(const binary_tensor_expression& l) = delete;
	binary_tensor_expression(binary_tensor_expression&& l)
	  : el(l.el), er(l.er), op(l.op) {}

	BOOST_UBLAS_INLINE
	decltype(auto)  operator()(size_type i) const { return op(el(i), er(i)); }

	expression_type_left const& el;
	expression_type_right const& er;
	binary_operation op;
};

/// @brief helper function to simply instantiation of lambda proxy class
template<class T, class EL, class ER, class OP>
auto make_binary_tensor_expression( tensor_expression<T,EL> const& el, tensor_expression<T,ER> const& er, OP op)
{
	return binary_tensor_expression<T,EL,ER,OP>( el(), er(), op) ;
}

template<class T, class EL, class ER, class OP>
auto make_binary_tensor_expression( matrix_expression<EL> const& el, tensor_expression<T,ER> const& er, OP op)
{
	return binary_tensor_expression<T,EL,ER,OP>( el(), er(), op) ;
}

template<class T, class EL, class ER, class OP>
auto make_binary_tensor_expression( tensor_expression<T,EL> const& el, matrix_expression<ER> const& er, OP op)
{
	return binary_tensor_expression<T,EL,ER,OP>( el(), er(), op) ;
}

template<class T, class EL, class ER, class OP>
auto make_binary_tensor_expression( vector_expression<EL> const& el, tensor_expression<T,ER> const& er, OP op)
{
	return binary_tensor_expression<T,EL,ER,OP>( el(), er(), op) ;
}

template<class T, class EL, class ER, class OP>
auto make_binary_tensor_expression( tensor_expression<T,EL> const& el, vector_expression<ER> const& er, OP op)
{
	return binary_tensor_expression<T,EL,ER,OP>( el(), er(), op) ;
}



template<class T, class E, class OP>
struct unary_tensor_expression
    : public tensor_expression <T, unary_tensor_expression<T,E,OP>>
{

	using self_type = unary_tensor_expression<T,E,OP>;
	using tensor_type  = T;
	using expression_type = E;

	using derived_type = tensor_expression <T, unary_tensor_expression<T,E,OP>>;

	using size_type = typename tensor_type::size_type;

	explicit unary_tensor_expression(E const& ee, OP o) : e(ee) , op(o) {}
	unary_tensor_expression() = delete;
	unary_tensor_expression(const unary_tensor_expression& l) = delete;
	unary_tensor_expression(unary_tensor_expression&& l)
	  : e(l.e), op(op.l) {}

	BOOST_UBLAS_INLINE
	decltype(auto) operator()(size_type i) const { return op(e(i)); }

	E const& e;
	OP op;
};

// \brief helper function to simply instantiation of lambda proxy class
template<class T, class E, class OP>
auto make_unary_tensor_expression( tensor_expression<T,E> const& e, OP op)
{
	return unary_tensor_expression<T,E,OP>( e() , op);
}

template<class T, class E, class OP>
auto make_unary_tensor_expression( matrix_expression<E> const& e, OP op)
{
	return unary_tensor_expression<T,E,OP>( e() , op);
}

template<class T, class E, class OP>
auto make_unary_tensor_expression( vector_expression<E> const& e, OP op)
{
	return unary_tensor_expression<T,E,OP>( e() , op);
}


}
}
}
}
#endif

/* expression.hpp
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
*/