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