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
8KscidKHf22FvM4M598i/h3JvyP418e/+fxbwL+j6Hf+reehbja+p+Gbh+9wfAvxLcN3PL5V+ILvdTqdsux04Q8fXOPTR5JSnE43PpK71yc1KY3yXMfxy0/0IRm3O6hPssnOUEF2suMRdlBbbaRnMAJSuM2S2rkdjwra8yjRnugFDn9AaW5zmL6tvsAkw/u7cCUaTJCVZ7y/U76xrfuspsM0ajxm+lN6hzJxV9P7uEMDiDLtXFm5a1trVjVTl2dWXQ5vHiBU09Cit0eLO9EiCNUg0SI19SaasmnU9mQaFfHEn/FVG1d8YDnJPAFyC/RcWTMF+TWkQja3A/8YST4Din60eMGkhrjdIQnVttI68Y/lVR3HoB/MqQmhDnZE8vLiPuw9nhTRwbbRP7BupuqicnOncDXthwtFiVOidNC4js/hM4kpjHij75c0ZIWmM1eqzsKPMdHD2WAB/a1NXKW16REn/hnnoSLaia3/AJfdY0XV6qSqaUepeoirvj/SrDpByERQCiPnD2Ule+k+LTTb4o6vMv2/K+Y50j8hyl0vfhmKCsMPxblrNlJBWDbLONCP+dHOilnsfteoGEbFcvgW73aZs9tioG8wZv85R/g2LGliRa5Z4lTaKW8Zg6psEwysi5dUdVZk7zvN4ekeTnoS30ImbrO9dJooFS+ZJRIoGMl2eOIl4/W1DuGw1WM59r9dPCA9JIVyRTzEpGgEkPotKNoZmK/xeQEukHLbKeK4jJEFfHbwGXpwYHhCMVptetTawUf604JMUrwam4I/6iZL1oY6v14zB0eLQ6FHClmK3AH2QSg5JKQoDUGpoq4APsNX/Ubo7zYWZ0WwVA54mx3+CkGVz4iPttRQZtlK+lDoxV2BYPnqK/YOLKXLFD9lzTZlBrWYMVb0dVZMreHt6KyAaAj9cXZPRCfBRZnbU0REPScRcu9viba7zxMt5HALdYFEFSHNYvVWQGPNzuXnqh8k7QprBd5fmml5D9HOFqdaOKaandxB9Buqfx9rGfvEHzGegvAop5eQJq/rxovn2/6V8CLMspIfw/YQJr1rrHB9qJcVJ8ZQufk9wZtlIrx1eDkFwL4Co0qNrfyFkBmSWWwjUeGXKLFKQuoZTjmR2sEpGaktTNkW2dNPaQ6BarNg25UsTu7y4y4bQAoatYZEW0HSQ45MQjj7SElxamQ84SUAa4qZkmVOs8wHAN2ERApRN92UawdwVhdZbeNELSqG7u50JlmhdBq9J0baAXM7WAaYGD4PNBn9QpeAJPUqXQrNRqO40ELjUX5jHcgNb8ddQCIciDi5a7NrRa8sxWgXT15l4zQJVhpCXRcJmRNoHAqiMbMmSyot0oUWPsN5/0k/tn+eINTak4hXhThJiJxFIeeHcgAdFmhEJqrfcpiAf5SlkjyyMzHhfqN+yc6BfBMnnd0TcLtD/Wrv20MDwrccG3Z85QxLZe1cdYNVsnWZDzPyGjGsO9wJ7wnvgmLCh8Io22N1R1KnTyVaPptpqtvsfzqorXmUUdsmf3pw2/wAAIJXwBMGqrt6AuROAgidGGQlPOihvL6eBDreS1zhE9Rn7RqjCSLXdQ/z92lmfuIcYwneVkjEvOqLdrkiSt1BPwsEUH6amgDKy8MJKKeNTHLjTZM6XEVswknqK6iWxCn8PjWJU2hOZjKeHsKcAsmwBaPBCIrWRDuv9mznK73bsTkOLbmdCbLZzvGKDD/Wh/Yn2HJnendFSPYlxKU2E6Gw1OEbltSho+lgknRiB2+rkdjdUzbxob2kZzW9x85h+XlgJ1nXX/CS2nRXx1Hpt3ADX58DAws2bLwKh6DS+QDQsAYr3IMIfP2R8mDxwMyxpS4W9hEHmgk=
*/