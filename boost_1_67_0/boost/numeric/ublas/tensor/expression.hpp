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