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
ouEmg6bsWLs6DBk7PWXL7SnNhha4TaNRRtiLtmemAsdfqZYPTUp/yze7TIsIOrx4PhTRo8Kp2ec3UcM5jjILTRxXDeCBjzcb7y98MwAnYur+K51Q0WSkvHmPp4nZv7KE9wnXjyrAHXuKjk3Y+j5PSA/8nifr7Bz/rGryQ0tMRSZ3fs3lFBiJo6m8QVaoesjM7weehEkCuMRbjfezOb/0dp7g1BRGHBqlnq0rfW+U0XsIvKPpLqn3FMgz5yupJ1otPrf9ez9pnSfSg3HtrVZYfeHGaqIZ5YXpPcojz5f7lV9pOnEpTu7Azgjeg0RxSgyoSq9tBJr7dvCsW8VLRo8cyLrSYgzXO5OcibwE8ETgZds8wCdvlvc/MiMEib9iSRDrcOPb1Y1xHLgTp7D18ZaFbOIqlEpG703jKc9T2J0PAbfmdMuaf1rJyOjl7pGYbe983OiLObfzClMd/KORtdybOxwueqikhVeI8jhXgWM2PvL3wd/kUiZLZgK7ip+ApWRJkBkfF1yo8XLIj7kzl8ikDspk9axoszXK2XeA2AdrbtHwaNdtyCnfezDi8+5FWV+70KbR0KSz/6cG/gFNEptOam/0C3pjl91X87msC+KPtKhSrp7viieBdJl/HSoWmLU6FdXp/mJWUJbBI5BdwF7AnNfTASREO7rZzFjIVhKdAcCe9RZk33b06c6NLIZtdm79hm03SWVciKbKI7XYAMOBFdfRi7krPiqnmeG8ZiyF8lQIJo5FznVxmtRV3WrKY5BbGE9MslP9z0rpsjPpX5NnFGGReYzYBgn2zjvuiO9Fjjv1SKgwaXi9l+Zvp3Zht18AtVcC6YPnE2zMCJUvAo+51s8e2MZaHCw+dpiVoXx6IoZdXfXKl3+cmi5J5ZRIzIZ6uVRA5OPiQM69V0BuT62k6+BV78gABaPLLevrTNBdiyvimmOJpUp6vv72KtlyxJKYhe6rZMpL7pPgVUDPKFXijxkinnJPSThtcZU9RX2VKHDLOjYCHyqocgDJPPHRVmZ/FCS8is4KZcpgnNxNNi0nzXcyNcpMf29W5djXVrNq7JS67pKHffu63nSwit7NFC+tPqZNoAkGa1vSbk0g0m+SAOuWbechAAM5M1Uvw5vTdySeGdu//QAd8rrwiN7VShRdL3DKQAcc7mXzoZ3qOpvFvZD+cjQhS8jEZt1f1mL9266kMf5RuKLdiMfzGI/asc8SYYTx+KuX6plsUnBZ3cr2L+tKgAx7eDcyfSqAf0XCYKf3sLZZBxz6v3fWKo7zGRkE8rYCYS+oBDPx9/yxDkNxvX41+WDsQeyFCOWKd/zfG0KGb5vXz91GxnHTF1JGklcMmwxSk1smLzGdtKfGff5/5AGJtEMB9Xc552LN+bBfJVCSZXarrFlV7/ApP6gCMB+pEVUp65cIVZCIuO5JZ2NBe5uem2NzFsZGhAopBLoLu4eDCxqoXtqc//OqQfyXhc+uS/91qW4SC/qkAgjFfFIJYGEyx35cw0jtn+89D7tYqVE0FVztGOrIcN3+XMG9blL2mRf7ajWceRQXexz426n28IhKpIHi/J90BMlBv0cCc4wTrDZgspDKc2G1aiXoYc8bBnaF22hHIYf7TEsvsAaWGGaO0wG7SElzxNaZKOPOvNKe+YJJkLe36JnYuupuc39uZLjfWgr/ZscPq8aM4xAybjMyH82uhUW6wHV1k+ZsjwBq2P0cePfzsWN1CtskaT1OHHyAkNXaH5BSQNrE5NZE+8U1ZJf36dmnQWAyMoi0YIU5UOqle/2zPMp0qWgyjaygQOaEAHHkQe9jZeR1b43T3YrS70WPT43DT9nKFPoo1fPP+Q5rTbQesAm8heXZLg+4Mgoe1qrLftsUr5DmAQ1Cf0KJs5Ka7eCaZy8EdWn5Nbm5orpwWHbxCwpob+4XodPyTsFA1E6r6tNjB2hWkrdsis4Jon1mRZYbW/QtDB87dWv61n+3iUiI7hDdJbpHREp0n+gB0UMiMiJyIgoiSiIqokdE1ESPiWiInhA9JXpGREtER0RP9JyIgQhAxEjERMRM9IKIhYiViI2InYiDiJOIi+glETcRDxEvER8RP5EAkSCREJEwkQiRKNErIjEicSIJIkkiKSJpIhkiWSI5InkiBaLXRG+I3hIpEr0jek+kRKRM9IFIhUiVSI1InUiDSJNIi+gjkTaRDpEukR6RPtEnIgMiQyIjos9ExkQmRKZEZkTmRF+ILIgsiayIrIlsiGyJ7Ii+EtkTfSNyIHIkciJyJnIhciUCErkRuRN9J/Ig8iTyIvIm8iHyJfIj8icCEQUQBRL9JPoAkh/IsSTczE24HUrN/XTBufMd56bcKO/GmHW6gYjlFj1HlKEf0kCq4tku0Ay+H1JJGGhR0gQ0lLgXeao171UpZqc3SjZpNsT0GdE2wX4nRnSa/M6yPbkwtXRC7XMyL5olNWODBE1enVmWiVSf5vhGLK798T2+CqJO5d5Vy/RLFuaa6/AasyCYZrxqUynOMxMTuRczFSterI3Py7ZfJ79K/6swXdlVEFiztyV+iAIn6MY4XSd4+ruum9tie2R1zYMN1EFsAUDTuaHvJ84iME4l3TY3Ap+CCI77PCaiFuiSKEuShLzJyB+z9V912Y4TXPm7NRE7q7CLYU432D7f6CTmFxM9tC5HWUqAKD+XjMt+/rl2Y9vl3uTGUQJlnkum+0+0hknYGTfVRYe08x/DiS7DlWFFsQ28UcfGem5bymFZVKMJu3Kzb5FOJK71rXqtStmyfWKWzhWsj39+WuByJ0RUI+snxROMHGB3ixP3c35lWVGf33q5q3JJQ57pe6o47+HvXsUOskgt3w/MvmssqnSgir6h8gL5B3FpTQ9H9g8+qqBmvqxmTxV6tkRMH1i4RJAIjRvj/xD+xITx2C5a+58KUBWkiLpUw8NkLbE//eT0rpTM9X8uMh1UrfRyd0cEMPEkZ90xuXqBfYRefaN68hAf3cj8Crm7n8v01xDGSSkBfLWyt5WrM+j1/ehjjKmsHnX1HBMq9+1xEfRNXHwi5IbAR4VzlqDS/5AVDG0ZadJfG2NimhPN31EB+6mCyMYDEtwVAzhPtzkID3pJniC8fMb7BP1GvG2/9OkylSyrzknsHteFRY6tmUWAZfmRKZH9uUw8WQBsQkf0U6D89aSB2/ODXCH3tqZMnTead8VDVGLF85itrrPBG5MBU408dWdnH1lmZA6kVPmAgPGCfGq7te5r2+tVJ5rSW1mpt9z4HszzLik+9Ufb0R+XhbmVHdWWFfZRO9hRnnxM76Nvku9RnH1Mu2YeNDQEAZ+vuIvkqGz55yAhK8TU/dUj2lyM0HYQhQF5otWo4tlaNPoMv//Ar+jS3No/AnQo3V+dgePJcNc85BJg6vYJiPBRLwMd2MDZx7vxdANZhn5W7CA25+7tvLSbPnvJa7GBMEMZ8XHF5C06O6hKoMjhnsT2xPM5J/+vdc0CrgockfiHJ+ldWeZIu2ben+5KJqFDEXXmq3bNR3JUyTLhl3yUNz+uK23krYbCmEqiDVvxunPBzE0IixNyKhtjtJ0UkMk9SPJWK9/q0pMjQMjlsw8KI8LrDNuZnqMSIqkDyF2X0epVMRoJS7eGsIuyrGMrS6fGkCw2OFX3yBNCsxPJPf4EAHYkKp9At9Q8WBY2b1PdR3GuQgkb8SU47uZ+Foz3dWm7Lg/D8cGD2VJUM4W9JVPd34E4xo05oQkhfikqmvTiAmj/xDzC15CwNs/e55HX4zkNVjlGasAJ1c1jX8LV6PO0CbH3JiG1Han1EjSClWveMAxiy6co8KH1ijhSGWN4IyFUeWCdG4aTUhPLMRa0mgp2cf6NHO6FBiY5BR16ROLOtIGxEaLCTR9i1Yx12S8o5oF5RmHVvx6PBtQHuiRZ2St1ajDN+eVfz3slzoRZ/I2ov8i0NodnZo6KdaQfVxmNG9yvgPPhLgzbF8oU5jsNiQVEoE4ZArI6yJ/AHDXd8EGmuGmwTyqtSv8osfpLKcrBxTkZUB/T4ZIo+UhZp0dqwDtLS+XFeP+/x1QX/o+sGkQ3Zxz24Sw4+fNtSveJ/sHsE6NOqh8kamNXUJSOaCOwg7i2gIe4oUatKG9R4e+NfXDosGxZoC4fnTm/6Jk83wKv+2sZHFcFUE7CdU0rITHIC5t4ChLKXerFV/w5DbxMV1NwY6pevkWFEcv2PLk1FAflJUU16d1dZDz5eEuaGcpku3yjHcj1M4AxXqrSgyn58KQHEqcqk7slObDEan5J+z5wv+DBooGKAgFonwxwuZUjjhOb3w7Ogr6+2g2egViMqgzBPEtPq1YcKLobSwqotpsgcBOIoVvkNe2F0bhM7/nO/sqXzufNez2Hk7VubW+a9sukBLcOS8P8ue7sy090LDQwyt9knrA8jApIBNlDZn0MESTq/X0IbpSDMmykus9Kt72uEhuo0kABu16zIFD4OKmTIEcb4PuVbvzUtKuRSgOubGec/utac1eiAJnrBWLZiufcJTTW0UeScuPrX3P4XrFd4noWOMffQTVOGycnRHYKm2Ordgrr8kw9R8r4vRFOC3O0yCRdjtpyT3VeyDdWpjjIS6QEkKm6caxYJELx0CrSjEH30LRVd2/Ee14Al+ydaVn+1FlzFrpc/HxBnNz8xLXkYKzswfl7B4gqiyYU6CWt/1oYGf30CabWPvowxbNuuq1A/qmTk3UnnMUpaxMhkevCqdnv9ASz772q7KUiQ98E69uYLynvE8+yXdfb3UPqVZ9w3UGvYPXs+4zm3eJ0L1wOa8nt0UkITuSp5xRYJ8sTrJscnxi5zOT6OVBR5s4I828A1lUBIqb197AMPANbTz/V1B9rENtCajGbfXNpPmCBeFROdCOphoQ/IbkYs+bOMDrCGIuBdKd6httZPN68x/S6MlLlF5XlW+yguYDz8GnfTgmSM3nLgTtUsjtJndo/JJiS8c/aTiUJuWNKV3Wl0xmJ9k3tpaikdZdlSQhqJtfAi1j9ne3VIHzbZPrsl3Xha1ostupVui7jtIv31idXEsxDMDmeJTo7ZNVH9JASlrnreZh9ewdvT4jFY/QqhpBd4lMaYOZRYsAqmeLU1tF7c09UoXG702VIin64mX2ugyBLQFTcjJMjqbF6PjJXfGGdKL03MlLKTcB83fe7M4Gw/uIAJvvNpysB7/HFSlKzgsgsHivItQzPaO87SKTgRttqNVXWUcuXSN2xP+e7luNW2Cf0zNgk64hEIEIPMsw00NxVqlvQQQ3xZ79UHaDhztKFFw8EgIVoI3oPl7WyeSIlH6SCNvUi+nzOF79vCgEZY897ih9GWB0kCo7ifvlpmMR6FY5I4QbGt/83wkN1+hueesf8VYgjyxgKsFXtOC0XbJb3wiACpWYrzVXBmIORSpSJ3ZdW8mJYhQSQusE67SKU0XYogOQgyEgHHK0wKoIMDRxNcco8WJTKUjjNjFIYi89SPRlMcmqvSycG6NvvsWs5UeYZeHLZdO7j2mfm6SNtrFzPXHQHaEp9NGc9curoo/f9+UEf+oyN6vLcN2Vmry5qKK2RAarCOH3vl4v2IIOqx4J2agqZrnjWzTtSRk2g+G2FFAHPz4iJSSXUh3ZPHo786GvkAGBbS7jies4etGn4YyzJ0K0uMyUD4M+Z6v4GRDeet3U2UHugVIGSTJGa/WfzWNmS7L1C3jea1Ez3GBqDDwidaueQ6ExPfSao2uXF+YUqBJeJ+L7UNnVyS7CcuM52QToT5YMt6Qt+OtUrfwLGnoo4z/OYHzl5Y/02H+Fi6No/w2c+pRteor9JQTTmgTG6IQnM0VJJqPaAFNK5DwF3r3W64BUTMrFGvOjvsveuX1R7FkaIVnX3wZVh6Q53wKLAJ2Z/tiYEMMKF/+zlSr/Sltu1ideaWTSy4vM6XaJ1xYFmJ500MRxJAILLztqsxtSEEvk8X3UDcz++1el81pb+hnypyWigxLt2JU73mtHzyqv2ZKx0vvjeUzUZakmI4VHtIZZfE+Oyyf4X8QlypcFj0qYPn+gO4AB0Buz1nKmOtj9NdU6VpFX0Gl76x5kqXY7I/8rgObmZf5py6Get8Y8zeagBPtr+GJ2L0dpsQ66CR7OuVOJiogPlKZftdoCj8u78Vhi32tg1u40EYhk9YqM+LOTaKdXZdPqfMEigb+jpSQxxUOp9yGz+KvM1h14InFB6k3LfWfodSNadQYJxU14TJGwm7bgpJVCcBNpYX2UrnDD0fudWlxcrXX723uoQpe1TWDKwB2VXuKNY0gTD7A8hr3jsRRnA8gJnJx/9D9lBcmMEshspbqmx+e0kKbOrzSSUndWFPQTn++7ygn5IBcohNtVo4o8uaz4VRpfNOEiAkw+5e5nHpZLzsqy633f+g7kRzl5mlTiVO2KCmjnnWm6+zQGiJaob0D6QSKtFM8m9toXKhtjLvApoFpnmRjv4kpryelmWdP0tDXpVn0Zi/ZJ2TJSpov0lTJMlp+1rTvFBQ4TijtENZoxAHViSKswNvdkZAz1UFCDW72w3v+0ght/bHTcfnHbwIWkiEzWygnnVNZmYRIFP4QzWnbfOdYLSJ5rGZlJXt3g1Me3d3m2a3PLY0gwhXEkfXCPp9gCEjlA51PDmfEfMXpTSIA0vC1h5CbN6Ne6QlMXnj9aSqngHOEjtWzP0ynZIP62/vhmUe9tamX6hApKKvTKAR/cbuAy2v6DUj5pxQBpbO9Y3GGedgQl8djo64aIHzAZaySq7VT4llsTU/V6b81lSJ+Rn7bKcPotUuiRsWteH+c9N0d6BXjHpFR/ij6E7OUy3DJY2v6Gp5VBO2cNOA0F6RuL2J/MgjSi/NQrVeaD5U/iArumfJ5zH/lFUSxxSHeehEcjD+IYaxGv1JqjuXb1zowp7aEPfXfilnP7WG4WRa6oPAZICZ7i6uWDZssMzPSDq64iM9+dKQn06ld/nQPQbvzWLBRe5AJouQ7ke/A9aad/PgYsNTApb7FZp0QXZ1uafG8dz5hwoSM22+HC4LcR7+Iy49klLrulNEcCP2qzAsJOa7EgP/DGBaicw8J8uBflmFrXyar5zTsnhn+ucBgheLhgo+U7hsIMJwFAtSIlluYx5d5OTM+w5P+G2kxgtBXzo7K2D1w3W9Z2Uxw2dmwoWTyhXrjgab9tdqLvYi5LrqpctF1m5RQJ3RKP5gQ9zdjDFGbw4v+2cnWyhoYmBKSF788z5Cd0KsiWVyX2GGct3gfSLL5fmESikC8HGf6dq/z/63q+jz19gHQTJf3vuAD81QXArHziv6QWk2nNwen4vu5VPEGcHel5UJ0kw3XmrP3UIsmlS4sp99XpbkRFPkeAbGM3AfgGXIZ22g58MMAVxdNLu0fUA8jqeBDJawrt/f9DSV25vwLpnQfIChkkVvHMwYZL0YHpO6ONQZ+2cuTNjwHlA0q4EfSfE+rf5DwMl7xLWddusixpICft4F7/giJjhr3YloOkx3ChTShWft8yEsW9P1Y80NUs+pOpxf4LBiY37jukm8zlVihyGwDgUntvpnLS/IDk2S+2wR0QhfS3MVZquKMZpgEwdN4V16dGNiCRQ8aQJMs9m8XV0wZPfldn0gsfsJI39I+epFit0A6gkcMGE4bbWfwPRx3XXm2mnx0C36O1zrKR956NMqFrmt1+QFodfM5erOY2y5WfPhv+JazfMdlivHzY5/j1h+b//DEUEhDkURjrcmmhnu/iZmBaUiKKbPvzHXkvJ7kah4zYk+BY2ZGu+dS1wfCyJfo7+eEJ4SZOZ0CReBLNtF7QqImyRND/TEXKJhOBcfL62BvQ9fwuIJlVICPi0HsX9WBn5nIb2yxzX6IOj+k6I7+czqC/gpji6vOHn30CyMoKrtHva1RN/z1DIFb8lXzoL9C/BL7QOEf0eLLqHchAMELAyi+M2Hzz/yjtFn+iyaBybw43xlB2H3AGvGpGdjSWJjxzOGwBkcPrncD4pCFDSvwF1xezwgZ7w+O3/Lh8hthzoH7Nx03UYVRhaW1ubXSuWkf6ZPpR7NkEk/TmnbmLykDVdSkrhM17eKAvh55+elXLmJQ/977oRyThho+cxoRHfhOtFojsqMQHmCIWVOPTiRkvl5f++ArNq3fdogmTcJAuLdCOdSw33qwVSckplPlcKMxIDHr6M8ffiZEsqQ3glStXn4cCmMFecR7VJmt3m0z1RHymz4cRjFZpYsxGxULywpFf2gtJuW0fet4Il5loJ9zF8cdRG7JgIZ4GkBQNS3Ue2ozU7YEc6Df/0+IcsoyAjiq5ywxva2ikMUwY4HBmavLF2j0atNrjkgwu2SpKki+f3WmPn7ByXgEdebhUf+sQQKoFHrv9yY+fQkb3AUxZ7LhKrUmumb4s3WkcvdkGGsWMfo2X4MKp9s2E2CyaOQj6i43JTky0IzV4PZet2DkMXt/IJKh0EFRfhxRndA++Uf5XJz10Htd2XoWexqgTArjkbsnIMX513ZGcKX1ZQJYi0IQ2VMa1q19CTANvForxsQuLokF7bUWL6BN33LG/JrpqWijwcyA6rxmVEO8JptTIUuynfmZdxQ3YceUSe9XHi8DVTXA6kQIOUSYGfUNaraTfa/mjv2xcB7U5y5MSQxxuMx5uBhRBkYKLn+iSO1EoZ5ARTSHdB/aTzj5fP2rGUwotcPN3kKjRL8bDfx5fm4c6yX2SdeylvnIkio1luamJQcHqDtMZOfCl729utszVjoc1vyhgP8NwsDzRPnBj6YZTNk9ocHxVuUyF+S8/OeyvufJ12GTaZcjYQx0jcUTu8Z9EusTJQeASH67HB2Mpv+MUdluomaOYQEf8QY0lWFLlneQ2mMpmqEKq9La/SsZazaYH9L7ohSehVXkanOcn8VXKqzG9/ZR/Q+sKT8jQRCHhS3HThuvLdlwpZKAfdN0lcq8OLTjxZsrSkFwso6VisjArC8dyFa9uYrNArBTt17RemYSPawO/dhyjUsYfci/OqL1Y9kj7Z4hyRdp1aPjlmx/QX7kWPqBD89MVxblVlvHdbT1dvXlL1R7y70cW774rXl0I05Bejfdqt2+HOLOKYtIc9KsEdHeyrXsEdkJIeP181cJBwdWOZ2mUpd+ePPPy83m1M5IAPaFTc0qhoLCMM3ue3fTP33wj2bKEMrZC0fkTq2EZpa/5ljGSqw3M+KEHZ4m6ueedXg1Di7vrN9cY=
*/