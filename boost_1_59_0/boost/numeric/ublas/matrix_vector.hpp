//  Copyright (c) 2012 Oswin Krause
//  Copyright (c) 2013 Joaquim Duran
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_UBLAS_MATRIX_VECTOR_HPP
#define BOOST_UBLAS_MATRIX_VECTOR_HPP

#include <boost/numeric/ublas/matrix_proxy.hpp> //for matrix_row, matrix_column and matrix_expression
#include <boost/numeric/ublas/vector.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace numeric { namespace ublas {

namespace detail{

/** \brief Iterator used in the represention of a matrix as a vector of rows or columns
 *
 * Iterator used in the represention of a matrix as a vector of rows/columns. It refers
 * to the i-th element of the matrix, a column or a row depending of Reference type.
 *
 * The type of Reference should provide a constructor Reference(matrix, i)
 *
 * This iterator is invalidated when the underlying matrix is resized.
 *
 * \tparameter Matrix type of matrix that is represented as a vector of row/column
 * \tparameter Reference Matrix row or matrix column type.
 */
template<class Matrix, class Reference>
class matrix_vector_iterator: public boost::iterator_facade<
    matrix_vector_iterator<Matrix,Reference>,
    typename vector_temporary_traits<Reference>::type,
    boost::random_access_traversal_tag,
    Reference
>{
public:
    matrix_vector_iterator(){}

    ///\brief constructs a matrix_vector_iterator as pointing to the i-th proxy
    BOOST_UBLAS_INLINE
    matrix_vector_iterator(Matrix& matrix, std::size_t position)
    : matrix_(&matrix),position_(position) {}

    template<class M, class R>
    BOOST_UBLAS_INLINE
    matrix_vector_iterator(matrix_vector_iterator<M,R> const& other)
    : matrix_(other.matrix_),position_(other.position_) {}

private:
    friend class boost::iterator_core_access;
    template <class M,class R> friend class matrix_vector_iterator;

    BOOST_UBLAS_INLINE
    void increment() {
        ++position_;
    }

    BOOST_UBLAS_INLINE
    void decrement() {
        --position_;
    }

    BOOST_UBLAS_INLINE
    void advance(std::ptrdiff_t n){
        position_ += n;
    }

    template<class M,class R>
    BOOST_UBLAS_INLINE
    std::ptrdiff_t distance_to(matrix_vector_iterator<M,R> const& other) const{
        BOOST_UBLAS_CHECK (matrix_ == other.matrix_, external_logic ());
        return (std::ptrdiff_t)other.position_ - (std::ptrdiff_t)position_;
    }

    template<class M,class R>
    BOOST_UBLAS_INLINE
    bool equal(matrix_vector_iterator<M,R> const& other) const{
        BOOST_UBLAS_CHECK (matrix_ == other.matrix_, external_logic ());
        return (position_ == other.position_);
    }

    BOOST_UBLAS_INLINE
    Reference dereference() const {
        return Reference(*matrix_,position_);
    }

    Matrix* matrix_;//no matrix_closure here to ensure easy usage
    std::size_t position_;
};

}

/** \brief Represents a \c Matrix as a vector of rows.
 *
 * Implements an interface to Matrix that the underlaying matrix is represented as a
 * vector of rows.
 *
 * The vector could be resized which causes the resize of the number of rows of
 * the underlaying matrix.
 */
template<class Matrix>
class matrix_row_vector {
public:
    typedef ublas::matrix_row<Matrix> value_type;
    typedef ublas::matrix_row<Matrix> reference;
    typedef ublas::matrix_row<Matrix const> const_reference;

    typedef ublas::detail::matrix_vector_iterator<Matrix, ublas::matrix_row<Matrix> > iterator;
    typedef ublas::detail::matrix_vector_iterator<Matrix const, ublas::matrix_row<Matrix const> const> const_iterator;
    typedef boost::reverse_iterator<iterator> reverse_iterator;
    typedef boost::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef typename boost::iterator_difference<iterator>::type difference_type;
    typedef typename Matrix::size_type size_type;

    BOOST_UBLAS_INLINE
    explicit matrix_row_vector(Matrix& matrix) :
        matrix_(&matrix) {
    }

    BOOST_UBLAS_INLINE
    iterator begin(){
        return iterator(*matrix_, 0);
    }

    BOOST_UBLAS_INLINE
    const_iterator begin() const {
        return const_iterator(*matrix_, 0);
    }

    BOOST_UBLAS_INLINE
    const_iterator cbegin() const {
        return begin();
    }

    BOOST_UBLAS_INLINE
    iterator end() {
        return iterator(*matrix_, matrix_->size1());
    }

    BOOST_UBLAS_INLINE
    const_iterator end() const {
        return const_iterator(*matrix_, matrix_->size1());
    }

    BOOST_UBLAS_INLINE
    const_iterator cend() const {
        return end();
    }

    BOOST_UBLAS_INLINE
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    BOOST_UBLAS_INLINE
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    BOOST_UBLAS_INLINE
    const_reverse_iterator crbegin() const {
        return rbegin();
    }  

    BOOST_UBLAS_INLINE
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    BOOST_UBLAS_INLINE
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    BOOST_UBLAS_INLINE
    const_reverse_iterator crend() const {
        return end();
    }

    BOOST_UBLAS_INLINE
    value_type operator()(size_type index) {
        return value_type(*matrix_, index);
    }

    BOOST_UBLAS_INLINE
    value_type operator()(size_type index) const {
        return value_type(*matrix_, index);
    }

    BOOST_UBLAS_INLINE
    reference operator[](size_type index){
        return (*this) (index);
    }

    BOOST_UBLAS_INLINE
    const_reference operator[](size_type index) const {
        return (*this) (index);
    }

    BOOST_UBLAS_INLINE
    size_type size() const {
        return matrix_->size1();
    }

    BOOST_UBLAS_INLINE
    void resize(size_type size, bool preserve = true) {
        matrix_->resize(size, matrix_->size2(), preserve);
    }

private:
    Matrix* matrix_;
};


/** \brief Convenience function to create \c matrix_row_vector.
 *
 * Function to create \c matrix_row_vector objects.
 * \param matrix the \c matrix_expression that generates the matrix that \c matrix_row_vector is referring.
 * \return Created \c matrix_row_vector object.
 *
 * \tparam Matrix the type of matrix that \c matrix_row_vector is referring.
 */
template<class Matrix>
BOOST_UBLAS_INLINE
matrix_row_vector<Matrix> make_row_vector(matrix_expression<Matrix>& matrix){
    return matrix_row_vector<Matrix>(matrix());
}


/** \brief Convenience function to create \c matrix_row_vector.
 *
 * Function to create \c matrix_row_vector objects.
 * \param matrix the \c matrix_expression that generates the matrix that \c matrix_row_vector is referring.
 * \return Created \c matrix_row_vector object.
 *
 * \tparam Matrix the type of matrix that \c matrix_row_vector is referring.
 */
template<class Matrix>
BOOST_UBLAS_INLINE
matrix_row_vector<Matrix const> make_row_vector(matrix_expression<Matrix> const& matrix){
    return matrix_row_vector<Matrix const>(matrix());
}


/** \brief Represents a \c Matrix as a vector of columns.
 *
 * Implements an interface to Matrix that the underlaying matrix is represented as a
 * vector of columns.
 *
 * The vector could be resized which causes the resize of the number of columns of
 * the underlaying matrix.
 */
template<class Matrix>
class matrix_column_vector {
public:
    typedef ublas::matrix_column<Matrix> value_type;
    typedef ublas::matrix_column<Matrix> reference;
    typedef const ublas::matrix_column<Matrix const> const_reference;

    typedef ublas::detail::matrix_vector_iterator<Matrix, ublas::matrix_column<Matrix> > iterator;
    typedef ublas::detail::matrix_vector_iterator<Matrix const, ublas::matrix_column<Matrix const> const > const_iterator;
    typedef boost::reverse_iterator<iterator> reverse_iterator;
    typedef boost::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef typename boost::iterator_difference<iterator>::type difference_type;
    typedef typename Matrix::size_type size_type;

    BOOST_UBLAS_INLINE
    explicit matrix_column_vector(Matrix& matrix) :
        matrix_(&matrix){
    }

    BOOST_UBLAS_INLINE
    iterator begin() {
        return iterator(*matrix_, 0);
    }

    BOOST_UBLAS_INLINE
    const_iterator begin() const {
        return const_iterator(*matrix_, 0);
    }

    BOOST_UBLAS_INLINE
    const_iterator cbegin() const {
        return begin();
    }

    BOOST_UBLAS_INLINE
    iterator end() {
        return iterator(*matrix_, matrix_->size2());
    }

    BOOST_UBLAS_INLINE
    const_iterator end() const {
        return const_iterator(*matrix_, matrix_->size2());
    }

    BOOST_UBLAS_INLINE
    const_iterator cend() const {
        return end();
    }

    BOOST_UBLAS_INLINE
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    BOOST_UBLAS_INLINE
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    BOOST_UBLAS_INLINE
    const_reverse_iterator crbegin() const {
        return rbegin();
    }

    BOOST_UBLAS_INLINE
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    BOOST_UBLAS_INLINE
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    BOOST_UBLAS_INLINE
    const_reverse_iterator crend() const {
        return rend();
    }

    BOOST_UBLAS_INLINE
    value_type operator()(size_type index) {
        return value_type(*matrix_, index);
    }

    BOOST_UBLAS_INLINE
    value_type operator()(size_type index) const {
        return value_type(*matrix_, index);
    }

    BOOST_UBLAS_INLINE
    reference operator[](size_type index) {
        return (*this) (index);
    }

    BOOST_UBLAS_INLINE
    const_reference operator[](size_type index) const {
        return (*this) (index);
    }

    BOOST_UBLAS_INLINE
    size_type size() const {
        return matrix_->size2();
    }

    BOOST_UBLAS_INLINE
    void resize(size_type size, bool preserve = true) {
        matrix_->resize(matrix_->size1(), size, preserve);
    }

private:
    Matrix* matrix_;
};


/** \brief Convenience function to create \c matrix_column_vector.
 *
 * Function to create \c matrix_column_vector objects.
 * \param matrix the \c matrix_expression that generates the matrix that \c matrix_column_vector is referring.
 * \return Created \c matrix_column_vector object.
 *
 * \tparam Matrix the type of matrix that \c matrix_column_vector is referring.
 */
template<class Matrix>
BOOST_UBLAS_INLINE
matrix_column_vector<Matrix> make_column_vector(matrix_expression<Matrix>& matrix){
    return matrix_column_vector<Matrix>(matrix());
}


/** \brief Convenience function to create \c matrix_column_vector.
 *
 * Function to create \c matrix_column_vector objects.
 * \param matrix the \c matrix_expression that generates the matrix that \c matrix_column_vector is referring.
 * \return Created \c matrix_column_vector object.
 *
 * \tparam Matrix the type of matrix that \c matrix_column_vector is referring.
 */
template<class Matrix>
BOOST_UBLAS_INLINE
matrix_column_vector<Matrix const> make_column_vector(matrix_expression<Matrix> const& matrix){
    return matrix_column_vector<Matrix const>(matrix());
}

}}}

#endif

/* matrix_vector.hpp
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
*/