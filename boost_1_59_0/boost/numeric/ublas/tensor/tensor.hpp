//  Copyright (c) 2018-2019
//  Cem Bassoy
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Fraunhofer and Google in producing this work
//  which started as a Google Summer of Code project.
//


/// \file tensor.hpp Definition for the tensor template class

#ifndef BOOST_UBLAS_TENSOR_IMPL_HPP
#define BOOST_UBLAS_TENSOR_IMPL_HPP

#include <boost/config.hpp>

#include <initializer_list>

#include "algorithms.hpp"
#include "expression.hpp"
#include "expression_evaluation.hpp"
#include "extents.hpp"
#include "strides.hpp"
#include "index.hpp"

namespace boost { namespace numeric { namespace ublas {

template<class T, class F, class A>
class tensor;

template<class T, class F, class A>
class matrix;

template<class T, class A>
class vector;

///** \brief Base class for Tensor container models
// *
// * it does not model the Tensor concept but all derived types should.
// * The class defines a common base type and some common interface for all
// * statically derived Tensor classes
// * We implement the casts to the statically derived type.
// */
//template<class C>
//class tensor_container:
//		public detail::tensor_expression<C>
//{
//public:
//	static const unsigned complexity = 0;
//	typedef C container_type;
//	typedef tensor_tag type_category;

//	BOOST_UBLAS_INLINE
//	const container_type &operator () () const {
//			return *static_cast<const container_type *> (this);
//	}
//	BOOST_UBLAS_INLINE
//	container_type &operator () () {
//			return *static_cast<container_type *> (this);
//	}
//};



/** @brief A dense tensor of values of type \c T.
		*
		* For a \f$n\f$-dimensional tensor \f$v\f$ and \f$0\leq i < n\f$ every element \f$v_i\f$ is mapped
		* to the \f$i\f$-th element of the container. A storage type \c A can be specified which defaults to \c unbounded_array.
		* Elements are constructed by \c A, which need not initialise their value.
		*
		* @tparam T type of the objects stored in the tensor (like int, double, complex,...)
		* @tparam A The type of the storage array of the tensor. Default is \c unbounded_array<T>. \c <bounded_array<T> and \c std::vector<T> can also be used
		*/
template<class T, class F = first_order, class A = std::vector<T,std::allocator<T>> >
class tensor:
		public detail::tensor_expression<tensor<T, F, A>,tensor<T, F, A>>
{

	static_assert( std::is_same<F,first_order>::value ||
								 std::is_same<F,last_order >::value, "boost::numeric::tensor template class only supports first- or last-order storage formats.");

	using self_type  = tensor<T, F, A>;
public:



	template<class derived_type>
	using tensor_expression_type = detail::tensor_expression<self_type,derived_type>;

	template<class derived_type>
	using matrix_expression_type = matrix_expression<derived_type>;

	template<class derived_type>
	using vector_expression_type = vector_expression<derived_type>;

	using super_type = tensor_expression_type<self_type>;

//	static_assert(std::is_same_v<tensor_expression_type<self_type>, detail::tensor_expression<tensor<T,F,A>,tensor<T,F,A>>>, "tensor_expression_type<self_type>");

	using array_type  = A;
	using layout_type = F;


	using size_type       = typename array_type::size_type;
	using difference_type = typename array_type::difference_type;
	using value_type      = typename array_type::value_type;

	using reference       = typename array_type::reference;
	using const_reference = typename array_type::const_reference;

	using pointer         = typename array_type::pointer;
	using const_pointer   = typename array_type::const_pointer;

	using iterator        = typename array_type::iterator;
	using const_iterator  = typename array_type::const_iterator;

	using reverse_iterator        = typename array_type::reverse_iterator;
	using const_reverse_iterator  = typename array_type::const_reverse_iterator;

	using tensor_temporary_type = self_type;
	using storage_category = dense_tag;

	using strides_type = basic_strides<std::size_t,layout_type>;
	using extents_type = shape;

	using matrix_type     = matrix<value_type,layout_type,array_type>;
	using vector_type     = vector<value_type,array_type>;


	/** @brief Constructs a tensor.
	 *
	 * @note the tensor is empty.
	 * @note the tensor needs to reshaped for further use.
	 *
	 */
	BOOST_UBLAS_INLINE
	constexpr tensor ()
		: tensor_expression_type<self_type>() // container_type
		, extents_()
		, strides_()
		, data_()
	{
	}


	/** @brief Constructs a tensor with an initializer list
	 *
	 * By default, its elements are initialized to 0.
	 *
	 * @code tensor<float> A{4,2,3}; @endcode
	 *
	 * @param l initializer list for setting the dimension extents of the tensor
	 */
	explicit BOOST_UBLAS_INLINE
	tensor (std::initializer_list<size_type> l)
		: tensor_expression_type<self_type>()
		, extents_ (std::move(l))
		, strides_ (extents_)
		, data_    (extents_.product())
	{
	}


	/** @brief Constructs a tensor with a \c shape
	 *
	 * By default, its elements are initialized to 0.
	 *
	 * @code tensor<float> A{extents{4,2,3}}; @endcode
	 *
	 * @param s initial tensor dimension extents
	 */
	explicit BOOST_UBLAS_INLINE
	tensor (extents_type const& s)
		: tensor_expression_type<self_type>() //tensor_container<self_type>()
		, extents_ (s)
		, strides_ (extents_)
		, data_    (extents_.product())
	{}


	/** @brief Constructs a tensor with a \c shape and initiates it with one-dimensional data
	 *
	 * @code tensor<float> A{extents{4,2,3}, array }; @endcode
	 *
	 *
	 *  @param s initial tensor dimension extents
	 *  @param a container of \c array_type that is copied according to the storage layout
	 */
	BOOST_UBLAS_INLINE
	tensor (extents_type const& s, const array_type &a)
		: tensor_expression_type<self_type>() //tensor_container<self_type>()
		, extents_ (s)
		, strides_ (extents_)
		, data_    (a)
	{
		if(this->extents_.product() != this->data_.size())
			throw std::runtime_error("Error in boost::numeric::ublas::tensor: size of provided data and specified extents do not match.");
	}



	/** @brief Constructs a tensor using a shape tuple and initiates it with a value.
	 *
	 *  @code tensor<float> A{extents{4,2,3}, 1 }; @endcode
	 *
	 *  @param e initial tensor dimension extents
	 *  @param i initial value of all elements of type \c value_type
	 */
	BOOST_UBLAS_INLINE
	tensor (extents_type const& e, const value_type &i)
		: tensor_expression_type<self_type>() //tensor_container<self_type> ()
		, extents_ (e)
		, strides_ (extents_)
		, data_    (extents_.product(), i)
	{}



	/** @brief Constructs a tensor from another tensor
	 *
	 *  @param v tensor to be copied.
	 */
	BOOST_UBLAS_INLINE
	tensor (const tensor &v)
		: tensor_expression_type<self_type>()
		, extents_ (v.extents_)
		, strides_ (v.strides_)
		, data_    (v.data_   )
	{}



	/** @brief Constructs a tensor from another tensor
	 *
	 *  @param v tensor to be moved.
	 */
	BOOST_UBLAS_INLINE
	tensor (tensor &&v)
		: tensor_expression_type<self_type>() //tensor_container<self_type> ()
		, extents_ (std::move(v.extents_))
		, strides_ (std::move(v.strides_))
		, data_    (std::move(v.data_   ))
	{}


	/** @brief Constructs a tensor with a matrix
	 *
	 * \note Initially the tensor will be two-dimensional.
	 *
	 *  @param v matrix to be copied.
	 */
	BOOST_UBLAS_INLINE
	tensor (const matrix_type &v)
		: tensor_expression_type<self_type>()
		, extents_ ()
		, strides_ ()
		, data_    (v.data())
	{
		if(!data_.empty()){
			extents_ = extents_type{v.size1(),v.size2()};
			strides_ = strides_type(extents_);
		}
	}

	/** @brief Constructs a tensor with a matrix
	 *
	 * \note Initially the tensor will be two-dimensional.
	 *
	 *  @param v matrix to be moved.
	 */
	BOOST_UBLAS_INLINE
	tensor (matrix_type &&v)
		: tensor_expression_type<self_type>()
		, extents_ {}
		, strides_ {}
		, data_    {}
	{
		if(v.size1()*v.size2() != 0){
			extents_ = extents_type{v.size1(),v.size2()};
			strides_ = strides_type(extents_);
			data_    = std::move(v.data());
		}
	}

	/** @brief Constructs a tensor using a \c vector
	 *
	 * @note It is assumed that vector is column vector
	 * @note Initially the tensor will be one-dimensional.
	 *
	 *  @param v vector to be copied.
	 */
	BOOST_UBLAS_INLINE
	tensor (const vector_type &v)
		: tensor_expression_type<self_type>()
		, extents_ ()
		, strides_ ()
		, data_    (v.data())
	{
		if(!data_.empty()){
			extents_ = extents_type{data_.size(),1};
			strides_ = strides_type(extents_);
		}
	}

	/** @brief Constructs a tensor using a \c vector
	 *
	 *  @param v vector to be moved.
	 */
	BOOST_UBLAS_INLINE
	tensor (vector_type &&v)
		: tensor_expression_type<self_type>()
		, extents_ {}
		, strides_ {}
		, data_    {}
	{
		if(v.size() != 0){
			extents_ = extents_type{v.size(),1};
			strides_ = strides_type(extents_);
			data_    = std::move(v.data());
		}
	}


	/** @brief Constructs a tensor with another tensor with a different layout
	 *
	 * @param other tensor with a different layout to be copied.
	 */
	BOOST_UBLAS_INLINE
	template<class other_layout>
	tensor (const tensor<value_type, other_layout> &other)
		: tensor_expression_type<self_type> ()
		, extents_ (other.extents())
		, strides_ (other.extents())
		, data_    (other.extents().product())
	{
		copy(this->rank(), this->extents().data(),
				 this->data(), this->strides().data(),
				 other.data(), other.strides().data());
	}

	/** @brief Constructs a tensor with an tensor expression
	 *
	 * @code tensor<float> A = B + 3 * C; @endcode
	 *
	 * @note type must be specified of tensor must be specified.
	 * @note dimension extents are extracted from tensors within the expression.
	 *
	 * @param expr tensor expression
	 */
	BOOST_UBLAS_INLINE
	template<class derived_type>
	tensor (const tensor_expression_type<derived_type> &expr)
		: tensor_expression_type<self_type> ()
		, extents_ ( detail::retrieve_extents(expr) )
		, strides_ ( extents_ )
		, data_    ( extents_.product() )
	{
		static_assert( detail::has_tensor_types<self_type, tensor_expression_type<derived_type>>::value,
									 "Error in boost::numeric::ublas::tensor: expression does not contain a tensor. cannot retrieve shape.");
		detail::eval( *this, expr );
	}

	/** @brief Constructs a tensor with a matrix expression
	 *
	 * @code tensor<float> A = B + 3 * C; @endcode
	 *
	 * @note matrix expression is evaluated and pushed into a temporary matrix before assignment.
	 * @note extents are automatically extracted from the temporary matrix
	 *
	 * @param expr matrix expression
	 */
	BOOST_UBLAS_INLINE
	template<class derived_type>
	tensor (const matrix_expression_type<derived_type> &expr)
		: tensor(  matrix_type ( expr )  )
	{
	}

	/** @brief Constructs a tensor with a vector expression
	 *
	 * @code tensor<float> A = b + 3 * b; @endcode
	 *
	 * @note matrix expression is evaluated and pushed into a temporary matrix before assignment.
	 * @note extents are automatically extracted from the temporary matrix
	 *
	 * @param expr vector expression
	 */
	BOOST_UBLAS_INLINE
	template<class derived_type>
	tensor (const vector_expression_type<derived_type> &expr)
		: tensor(  vector_type ( expr )  )
	{
	}

	/** @brief Evaluates the tensor_expression and assigns the results to the tensor
	 *
	 * @code A = B + C * 2;  @endcode
	 *
	 * @note rank and dimension extents of the tensors in the expressions must conform with this tensor.
	 *
	 * @param expr expression that is evaluated.
	 */
	BOOST_UBLAS_INLINE
	template<class derived_type>
	tensor &operator = (const tensor_expression_type<derived_type> &expr)
	{
		detail::eval(*this, expr);
		return *this;
	}

	tensor& operator=(tensor other)
	{
		swap (*this, other);
		return *this;
	}

	tensor& operator=(const_reference v)
	{
		std::fill(this->begin(), this->end(), v);
		return *this;
	}

	/** @brief Returns true if the tensor is empty (\c size==0) */
	BOOST_UBLAS_INLINE
	bool empty () const {
		return this->data_.empty();
	}


	/** @brief Returns the size of the tensor */
	BOOST_UBLAS_INLINE
	size_type size () const {
		return this->data_.size ();
	}

	/** @brief Returns the size of the tensor */
	BOOST_UBLAS_INLINE
	size_type size (size_type r) const {
		return this->extents_.at(r);
	}

	/** @brief Returns the number of dimensions/modes of the tensor */
	BOOST_UBLAS_INLINE
	size_type rank () const {
		return this->extents_.size();
	}

	/** @brief Returns the number of dimensions/modes of the tensor */
	BOOST_UBLAS_INLINE
	size_type order () const {
		return this->extents_.size();
	}

	/** @brief Returns the strides of the tensor */
	BOOST_UBLAS_INLINE
	strides_type const& strides () const {
		return this->strides_;
	}

	/** @brief Returns the extents of the tensor */
	BOOST_UBLAS_INLINE
	extents_type const& extents () const {
		return this->extents_;
	}


	/** @brief Returns a \c const reference to the container. */
	BOOST_UBLAS_INLINE
	const_pointer data () const {
		return this->data_.data();
	}

	/** @brief Returns a \c const reference to the container. */
	BOOST_UBLAS_INLINE
	pointer data () {
		return this->data_.data();
	}

	/** @brief Element access using a single index.
	 *
	 *  @code auto a = A[i]; @endcode
	 *
	 *  @param i zero-based index where 0 <= i < this->size()
	 */
	BOOST_UBLAS_INLINE
	const_reference operator [] (size_type i) const {
		return this->data_[i];
	}

	/** @brief Element access using a single index.
	 *
	 *
	 *  @code A[i] = a; @endcode
	 *
	 *  @param i zero-based index where 0 <= i < this->size()
	 */
	BOOST_UBLAS_INLINE
	reference operator [] (size_type i)
	{
		return this->data_[i];
	}


	/** @brief Element access using a multi-index or single-index.
	 *
	 *
	 *  @code auto a = A.at(i,j,k); @endcode or
	 *  @code auto a = A.at(i);     @endcode
	 *
	 *  @param i zero-based index where 0 <= i < this->size() if sizeof...(is) == 0, else 0<= i < this->size(0)
	 *  @param is zero-based indices where 0 <= is[r] < this->size(r) where  0 < r < this->rank()
	 */
	template<class ... size_types>
	BOOST_UBLAS_INLINE
	const_reference at (size_type i, size_types ... is) const {
		if constexpr (sizeof...(is) == 0)
			return this->data_[i];
		else
			return this->data_[detail::access<0ul>(size_type(0),this->strides_,i,std::forward<size_types>(is)...)];
	}

	/** @brief Element access using a multi-index or single-index.
	 *
	 *
	 *  @code A.at(i,j,k) = a; @endcode or
	 *  @code A.at(i) = a;     @endcode
	 *
	 *  @param i zero-based index where 0 <= i < this->size() if sizeof...(is) == 0, else 0<= i < this->size(0)
	 *  @param is zero-based indices where 0 <= is[r] < this->size(r) where  0 < r < this->rank()
	 */
	BOOST_UBLAS_INLINE
	template<class ... size_types>
	reference at (size_type i, size_types ... is) {
		if constexpr (sizeof...(is) == 0)
			return this->data_[i];
		else
			return this->data_[detail::access<0ul>(size_type(0),this->strides_,i,std::forward<size_types>(is)...)];
	}




	/** @brief Element access using a single index.
	 *
	 *
	 *  @code A(i) = a; @endcode
	 *
	 *  @param i zero-based index where 0 <= i < this->size()
	 */
	BOOST_UBLAS_INLINE
	const_reference operator()(size_type i) const {
		return this->data_[i];
	}


	/** @brief Element access using a single index.
	 *
	 *  @code A(i) = a; @endcode
	 *
	 *  @param i zero-based index where 0 <= i < this->size()
	 */
	BOOST_UBLAS_INLINE
	reference operator()(size_type i){
		return this->data_[i];
	}




	/** @brief Generates a tensor index for tensor contraction
	 *
	 *
	 *  @code auto Ai = A(_i,_j,k); @endcode
	 *
	 *  @param i placeholder
	 *  @param is zero-based indices where 0 <= is[r] < this->size(r) where  0 < r < this->rank()
	 */
	BOOST_UBLAS_INLINE
	template<std::size_t I, class ... index_types>
	decltype(auto) operator() (index::index_type<I> p, index_types ... ps) const
	{
		constexpr auto N = sizeof...(ps)+1;
		if( N != this->rank() )
			throw std::runtime_error("Error in boost::numeric::ublas::operator(): size of provided index_types does not match with the rank.");

		return std::make_pair( std::cref(*this),  std::make_tuple( p, std::forward<index_types>(ps)... ) );
	}





	/** @brief Reshapes the tensor
	 *
	 *
	 * (1) @code A.reshape(extents{m,n,o});     @endcode or
	 * (2) @code A.reshape(extents{m,n,o},4);   @endcode
	 *
	 * If the size of this smaller than the specified extents than
	 * default constructed (1) or specified (2) value is appended.
	 *
	 * @note rank of the tensor might also change.
	 *
	 * @param e extents with which the tensor is reshaped.
	 * @param v value which is appended if the tensor is enlarged.
	 */
	BOOST_UBLAS_INLINE
	void reshape (extents_type const& e, value_type v = value_type{})
	{
		this->extents_ = e;
		this->strides_ = strides_type(this->extents_);

		if(e.product() != this->size())
			this->data_.resize (this->extents_.product(), v);
	}





	friend void swap(tensor& lhs, tensor& rhs) {
		std::swap(lhs.data_   , rhs.data_   );
		std::swap(lhs.extents_, rhs.extents_);
		std::swap(lhs.strides_, rhs.strides_);
	}


	/// \brief return an iterator on the first element of the tensor
	BOOST_UBLAS_INLINE
	const_iterator begin () const {
		return data_.begin ();
	}

	/// \brief return an iterator on the first element of the tensor
	BOOST_UBLAS_INLINE
	const_iterator cbegin () const {
		return data_.cbegin ();
	}

	/// \brief return an iterator after the last element of the tensor
	BOOST_UBLAS_INLINE
	const_iterator end () const {
		return data_.end();
	}

	/// \brief return an iterator after the last element of the tensor
	BOOST_UBLAS_INLINE
	const_iterator cend () const {
		return data_.cend ();
	}

	/// \brief Return an iterator on the first element of the tensor
	BOOST_UBLAS_INLINE
	iterator begin () {
		return data_.begin();
	}

	/// \brief Return an iterator at the end of the tensor
	BOOST_UBLAS_INLINE
	iterator end () {
		return data_.end();
	}

	/// \brief Return a const reverse iterator before the first element of the reversed tensor (i.e. end() of normal tensor)
	BOOST_UBLAS_INLINE
	const_reverse_iterator rbegin () const {
		return data_.rbegin();
	}

	/// \brief Return a const reverse iterator before the first element of the reversed tensor (i.e. end() of normal tensor)
	BOOST_UBLAS_INLINE
	const_reverse_iterator crbegin () const {
		return data_.crbegin();
	}

	/// \brief Return a const reverse iterator on the end of the reverse tensor (i.e. first element of the normal tensor)
	BOOST_UBLAS_INLINE
	const_reverse_iterator rend () const {
		return data_.rend();
	}

	/// \brief Return a const reverse iterator on the end of the reverse tensor (i.e. first element of the normal tensor)
	BOOST_UBLAS_INLINE
	const_reverse_iterator crend () const {
		return data_.crend();
	}

	/// \brief Return a const reverse iterator before the first element of the reversed tensor (i.e. end() of normal tensor)
	BOOST_UBLAS_INLINE
	reverse_iterator rbegin () {
		return data_.rbegin();
	}

	/// \brief Return a const reverse iterator on the end of the reverse tensor (i.e. first element of the normal tensor)
	BOOST_UBLAS_INLINE
	reverse_iterator rend () {
		return data_.rend();
	}


#if 0
	// -------------
	// Serialization
	// -------------

	/// Serialize a tensor into and archive as defined in Boost
	/// \param ar Archive object. Can be a flat file, an XML file or any other stream
	/// \param file_version Optional file version (not yet used)
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */){
		ar & serialization::make_nvp("data",data_);
	}
#endif



private:

	extents_type extents_;
	strides_type strides_;
	array_type data_;
};

}}} // namespaces





#endif

/* tensor.hpp
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
*/