//
//  Copyright (c) 2000-2013
//  Joerg Walter, Mathias Koch, Athanasios Iliopoulos
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_BANDED_
#define _BOOST_UBLAS_BANDED_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/detail/temporary.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {


namespace hidden {



/** \brief A helper for band_matrix indexing.
 *
 * The indexing happens as per the netlib description: http://www.netlib.org/lapack/lug/node124.html.
 * In the case of a row_major matrix a different approach is followed;
 */
template <class LayoutType>
class banded_indexing { };

/** \brief A helper for indexing column major banded matrices.
 *
 */
template <>
class banded_indexing<column_major_tag> {
public:

    template <class T>
    BOOST_UBLAS_INLINE static T size(T /*size1*/, T size2) {
        return size2;
    }

//    template <class T>
//    BOOST_UBLAS_INLINE static bool valid_index(T size1, T /*size2*/, T lower, T upper, T i, T j) {
//        return (upper+i >= j) && i <= std::min(size1 - 1, j + lower); // upper + i is used by get_index. Maybe find a way to consolidate the operations to increase performance
//    }

    template <class T>
    BOOST_UBLAS_INLINE static T get_index(T /*size1*/, T size2, T lower, T upper, T i, T j) {
        return column_major::element (upper + i - j, lower + 1 + upper, j, size2);
    }
};

/** \brief A helper for indexing row major banded matrices.
 *
 */
template <>
class banded_indexing<row_major_tag> {
public:

    template <class T>
    BOOST_UBLAS_INLINE static T size(T size1, T /*size2*/) {
        return size1;
    }

  //  template <class T>
  //  BOOST_UBLAS_INLINE static bool valid_index(T /*size1*/, T  size2, T lower, T upper, T i, T j) {
  //      return (lower+j >= i) && j <= std::min(size2 - 1, i + upper); // lower + j is used by get_index. Maybe find a way to consolidate the operations to increase performance
  //  }

    template <class T>
    BOOST_UBLAS_INLINE static T get_index(T size1, T /*size2*/, T lower, T upper, T i, T j) {
        return row_major::element (i, size1, lower + j - i, lower + 1 + upper);
    }
};

}

    /** \brief A banded matrix of values of type \c T.
     *
     * For a \f$(mxn)\f$-dimensional banded matrix with \f$l\f$ lower and \f$u\f$ upper diagonals and 
     * \f$0 \leq i < m\f$ and \f$0 \leq j < n\f$, if \f$i>j+l\f$ or \f$i<j-u\f$ then \f$b_{i,j}=0\f$. 
     * The default storage for banded matrices is packed. Orientation and storage can also be specified. 
     * Default is \c row_major and and unbounded_array. It is \b not required by the storage to initialize 
     * elements of the matrix.
     *
     * \tparam T the type of object stored in the matrix (like double, float, complex, etc...)
     * \tparam L the storage organization. It can be either \c row_major or \c column_major. Default is \c row_major
     * \tparam A the type of Storage array. Default is \c unbounded_array
     */
    template<class T, class L, class A>
    class banded_matrix:
        public matrix_container<banded_matrix<T, L, A> > {

        typedef T *pointer;
        typedef L layout_type;
        typedef banded_matrix<T, L, A> self_type;



    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_container<self_type>::operator ();
#endif
        typedef typename A::size_type size_type;
        typedef typename A::difference_type difference_type;
        typedef T value_type;
        typedef const T &const_reference;
        typedef T &reference;
        typedef A array_type;
        typedef const matrix_reference<const self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;
        typedef vector<T, A> vector_temporary_type;
        typedef matrix<T, L, A> matrix_temporary_type;  // general sub-matrix
        typedef packed_tag storage_category;
        typedef typename L::orientation_category orientation_category;

    private:
    public:

        // Construction and destruction
        BOOST_UBLAS_INLINE
        banded_matrix ():
            matrix_container<self_type> (),
            size1_ (0), size2_ (0),
            lower_ (0), upper_ (0), data_ (0) {}
        BOOST_UBLAS_INLINE
        banded_matrix (size_type size1, size_type size2, size_type lower = 0, size_type upper = 0):
            matrix_container<self_type> (),
            size1_ (size1), size2_ (size2),
            lower_ (lower), upper_ (upper),
#if defined(BOOST_UBLAS_OWN_BANDED) || (BOOST_UBLAS_LEGACY_BANDED)
            data_ ((std::max) (size1, size2) * (lower + 1 + upper))
#else
            data_ ( hidden::banded_indexing<orientation_category>::size(size1, size2) * (lower + 1 + upper)) // This is the netlib layout as described here: http://www.netlib.org/lapack/lug/node124.html
#endif
        {
        }
        BOOST_UBLAS_INLINE
        banded_matrix (size_type size1, size_type size2, size_type lower, size_type upper, const array_type &data):
            matrix_container<self_type> (),
            size1_ (size1), size2_ (size2),
            lower_ (lower), upper_ (upper), data_ (data) {}
        BOOST_UBLAS_INLINE
        banded_matrix (const banded_matrix &m):
            matrix_container<self_type> (),
            size1_ (m.size1_), size2_ (m.size2_),
            lower_ (m.lower_), upper_ (m.upper_), data_ (m.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_matrix (const matrix_expression<AE> &ae, size_type lower = 0, size_type upper = 0):
            matrix_container<self_type> (),
            size1_ (ae ().size1 ()), size2_ (ae ().size2 ()),
            lower_ (lower), upper_ (upper),
#if defined(BOOST_UBLAS_OWN_BANDED) || (BOOST_UBLAS_LEGACY_BANDED)
            data_ ((std::max) (size1_, size2_) * (lower_ + 1 + upper_))
#else
            data_ ( hidden::banded_indexing<orientation_category>::size(size1_, size2_) * (lower_ + 1 + upper_)) // This is the netlib layout as described here: http://www.netlib.org/lapack/lug/node124.html
#endif
        {
            matrix_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return size1_;
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const {
            return size2_;
        }
        BOOST_UBLAS_INLINE
        size_type lower () const {
            return lower_;
        }
        BOOST_UBLAS_INLINE
        size_type upper () const {
            return upper_;
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        const array_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        array_type &data () {
            return data_;
        }

#if !defined (BOOST_UBLAS_OWN_BANDED)||(BOOST_UBLAS_LEGACY_BANDED)
        BOOST_UBLAS_INLINE
        bool is_element_in_band(size_type i, size_type j) const{
            //return (upper_+i >= j) && i <= std::min(size1() - 1, j + lower_); // We don't need to check if i is outside because it is checked anyway in the accessors.
            return (upper_+i >= j) && i <= ( j + lower_); // Essentially this band has "infinite" positive dimensions
        }
#endif
        // Resizing
        BOOST_UBLAS_INLINE
        void resize (size_type size1, size_type size2, size_type lower = 0, size_type upper = 0, bool preserve = true) {
            if (preserve) {
                self_type temporary (size1, size2, lower, upper);
                detail::matrix_resize_preserve<layout_type> (*this, temporary);
            }
            else {
                data ().resize ((std::max) (size1, size2) * (lower + 1 + upper));
                size1_ = size1;
                size2_ = size2;
                lower_ = lower;
                upper_ = upper;
            }
        }

        BOOST_UBLAS_INLINE
        void resize_packed_preserve (size_type size1, size_type size2, size_type lower = 0, size_type upper = 0) {
            size1_ = size1;
            size2_ = size2;
            lower_ = lower;
            upper_ = upper;
            data ().resize ((std::max) (size1, size2) * (lower + 1 + upper), value_type ());
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (i < size1_, bad_index ());
            BOOST_UBLAS_CHECK (j < size2_, bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
            const size_type k = (std::max) (i, j);
            const size_type l = lower_ + j - i;
            if (k < (std::max) (size1_, size2_) && // TODO: probably use BOOST_UBLAS_CHECK here instead of if
                l < lower_ + 1 + upper_)
                return data () [layout_type::element (k, (std::max) (size1_, size2_),
                                                       l, lower_ + 1 + upper_)];
#elif BOOST_UBLAS_LEGACY_BANDED // Prior to version: TODO: add version this is actually incorporated in
            const size_type k = j;
            const size_type l = upper_ + i - j;
            if (k < size2_ &&
                l < lower_ + 1 + upper_)
                return data () [layout_type::element (k, size2_,
                                                       l, lower_ + 1 + upper_)];
#else  // New default
            // This is the netlib layout as described here: http://www.netlib.org/lapack/lug/node124.html
            if ( is_element_in_band( i, j) ) {
                return data () [hidden::banded_indexing<orientation_category>::get_index(size1_, size2_, lower_, upper_, i, j)];
            }
#endif
            return zero_;
        }

        BOOST_UBLAS_INLINE
        reference at_element (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1_, bad_index ());
            BOOST_UBLAS_CHECK (j < size2_, bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
            const size_type k = (std::max) (i, j);
            const size_type l = lower_ + j - i; // TODO: Don't we need an if or BOOST_UBLAS_CHECK HERE?
            return data () [layout_type::element (k, (std::max) (size1_, size2_),
                                                   l, lower_ + 1 + upper_)];
#elif BOOST_UBLAS_LEGACY_BANDED // Prior to version: TODO: add version this is actually incorporated in
            const size_type k = j;
            const size_type l = upper_ + i - j;
            if (! (k < size2_ &&
                   l < lower_ + 1 + upper_) ) {
                bad_index ().raise ();
                // NEVER reached
            }
            return data () [layout_type::element (k, size2_,
                                                       l, lower_ + 1 + upper_)];
#else
            // This is the netlib layout as described here: http://www.netlib.org/lapack/lug/node124.html
            BOOST_UBLAS_CHECK(is_element_in_band( i, j) , bad_index());
            return data () [hidden::banded_indexing<orientation_category>::get_index(size1_, size2_, lower_, upper_, i, j)];
#endif
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1_, bad_index ());
            BOOST_UBLAS_CHECK (j < size2_, bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
            const size_type k = (std::max) (i, j);
            const size_type l = lower_ + j - i;
            if (! (k < (std::max) (size1_, size2_) && // TODO: probably use BOOST_UBLAS_CHECK here instead of if
                  l < lower_ + 1 + upper_) ) {
                bad_index ().raise ();
                // NEVER reached
            }
            return data () [layout_type::element (k, (std::max) (size1_, size2_),
                                                       l, lower_ + 1 + upper_)];
#elif BOOST_UBLAS_LEGACY_BANDED // Prior to version: TODO: add version this is actually incorporated in
            const size_type k = j;
            const size_type l = upper_ + i - j;
            if (! (k < size2_ &&
                   l < lower_ + 1 + upper_) ) {
                bad_index ().raise ();
                // NEVER reached
            }
            return data () [layout_type::element (k, size2_,
                                                       l, lower_ + 1 + upper_)];
#else
            // This is the netlib layout as described here: http://www.netlib.org/lapack/lug/node124.html
            BOOST_UBLAS_CHECK( is_element_in_band( i, j) , bad_index());
            return data () [hidden::banded_indexing<orientation_category>::get_index(size1_, size2_, lower_, upper_, i, j)];
#endif

        }

        // Element assignment
        BOOST_UBLAS_INLINE
        reference insert_element (size_type i, size_type j, const_reference t) {
            return (operator () (i, j) = t);
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i, size_type j) {
            operator () (i, j) = value_type/*zero*/();
        }

        // Zeroing
        BOOST_UBLAS_INLINE
        void clear () {
            std::fill (data ().begin (), data ().end (), value_type/*zero*/());
        }

        // Assignment
        BOOST_UBLAS_INLINE
        banded_matrix &operator = (const banded_matrix &m) {
            size1_ = m.size1_;
            size2_ = m.size2_;
            lower_ = m.lower_;
            upper_ = m.upper_;
            data () = m.data ();
            return *this;
        }
        BOOST_UBLAS_INLINE
        banded_matrix &assign_temporary (banded_matrix &m) {
            swap (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_matrix &operator = (const matrix_expression<AE> &ae) {
            self_type temporary (ae, lower_, upper_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_matrix &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_matrix& operator += (const matrix_expression<AE> &ae) {
            self_type temporary (*this + ae, lower_, upper_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_matrix &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_matrix& operator -= (const matrix_expression<AE> &ae) {
            self_type temporary (*this - ae, lower_, upper_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_matrix &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        banded_matrix& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        banded_matrix& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (banded_matrix &m) {
            if (this != &m) {
                std::swap (size1_, m.size1_);
                std::swap (size2_, m.size2_);
                std::swap (lower_, m.lower_);
                std::swap (upper_, m.upper_);
                data ().swap (m.data ());
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (banded_matrix &m1, banded_matrix &m2) {
            m1.swap (m2);
        }

        // Iterator types
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator1<self_type, packed_random_access_iterator_tag> iterator1;
        typedef indexed_iterator2<self_type, packed_random_access_iterator_tag> iterator2;
        typedef indexed_const_iterator1<self_type, packed_random_access_iterator_tag> const_iterator1;
        typedef indexed_const_iterator2<self_type, packed_random_access_iterator_tag> const_iterator2;
#else
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
#endif
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator1 find1 (int rank, size_type i, size_type j) const {
            if (rank == 1) {
                size_type lower_i = (std::max) (difference_type (j - upper_), difference_type (0));
                i = (std::max) (i, lower_i);
                size_type upper_i = (std::min) (j + 1 + lower_, size1_);
                i = (std::min) (i, upper_i);
            }
            return const_iterator1 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            if (rank == 1) {
                size_type lower_i = (std::max) (difference_type (j - upper_), difference_type (0));
                i = (std::max) (i, lower_i);
                size_type upper_i = (std::min) (j + 1 + lower_, size1_);
                i = (std::min) (i, upper_i);
            }
            return iterator1 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find2 (int rank, size_type i, size_type j) const {
            if (rank == 1) {
                size_type lower_j = (std::max) (difference_type (i - lower_), difference_type (0));
                j = (std::max) (j, lower_j);
                size_type upper_j = (std::min) (i + 1 + upper_, size2_);
                j = (std::min) (j, upper_j);
            }
            return const_iterator2 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            if (rank == 1) {
                size_type lower_j = (std::max) (difference_type (i - lower_), difference_type (0));
                j = (std::max) (j, lower_j);
                size_type upper_j = (std::min) (i + 1 + upper_, size2_);
                j = (std::min) (j, upper_j);
            }
            return iterator2 (*this, i, j);
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator1:
            public container_const_reference<banded_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               const_iterator1, value_type> {
        public:
            typedef typename banded_matrix::value_type value_type;
            typedef typename banded_matrix::difference_type difference_type;
            typedef typename banded_matrix::const_reference reference;
            typedef const typename banded_matrix::pointer pointer;

            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<self_type> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const self_type &m, size_type it1, size_type it2):
                container_const_reference<self_type> (m), it1_ (it1), it2_ (it2) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<self_type> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                return (*this) () (it1_, it2_);
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 begin () const {
                return (*this) ().find2 (1, it1_, 0);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 cbegin () const {
                return begin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 end () const {
                return (*this) ().find2 (1, it1_, (*this) ().size2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 cend () const {
                return end ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 crbegin () const {
                return rbegin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 crend () const {
                return rend ();
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_;
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<self_type>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ == it.it1_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ < it.it1_;
            }

        private:
            size_type it1_;
            size_type it2_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 cbegin1 () const {
            return begin1 ();
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find1 (0, size1_, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 cend1 () const {
            return end1 ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator1:
            public container_reference<banded_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               iterator1, value_type> {
        public:
            typedef typename banded_matrix::value_type value_type;
            typedef typename banded_matrix::difference_type difference_type;
            typedef typename banded_matrix::reference reference;
            typedef typename banded_matrix::pointer pointer;

            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<self_type> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (self_type &m, size_type it1, size_type it2):
                container_reference<self_type> (m), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().at_element (it1_, it2_);
            }
            BOOST_UBLAS_INLINE
            reference operator [] (difference_type n) const {
                return *(*this + n);
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator2 begin () const {
                return (*this) ().find2 (1, it1_, 0);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator2 end () const {
                return (*this) ().find2 (1, it1_, (*this) ().size2 ());
            }

            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_;
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<self_type>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ == it.it1_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ < it.it1_;
            }

        private:
            size_type it1_;
            size_type it2_;

            friend class const_iterator1;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find1 (0, size1_, 0);
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator2:
            public container_const_reference<banded_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef typename banded_matrix::value_type value_type;
            typedef typename banded_matrix::difference_type difference_type;
            typedef typename banded_matrix::const_reference reference;
            typedef const typename banded_matrix::pointer pointer;

            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<self_type> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const self_type &m, size_type it1, size_type it2):
                container_const_reference<self_type> (m), it1_ (it1), it2_ (it2) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<self_type> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                return (*this) () (it1_, it2_);
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 begin () const {
                return (*this) ().find1 (1, 0, it2_);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 cbegin () const {
                return begin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 end () const {
                return (*this) ().find1 (1, (*this) ().size1 (), it2_);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 cend () const {
                return end();
            }

            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 crbegin () const {
                return rbegin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 crend () const {
                return rend ();
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_;
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<self_type>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ < it.it2_;
            }

        private:
            size_type it1_;
            size_type it2_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 cbegin2 () const {
            return begin2 ();
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find2 (0, 0, size2_);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 cend2 () const {
            return end2 ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator2:
            public container_reference<banded_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               iterator2, value_type> {
        public:
            typedef typename banded_matrix::value_type value_type;
            typedef typename banded_matrix::difference_type difference_type;
            typedef typename banded_matrix::reference reference;
            typedef typename banded_matrix::pointer pointer;

            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<self_type> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (self_type &m, size_type it1, size_type it2):
                container_reference<self_type> (m), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().at_element (it1_, it2_);
            }
            BOOST_UBLAS_INLINE
            reference operator [] (difference_type n) const {
                return *(*this + n);
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator1 begin () const {
                return (*this) ().find1 (1, 0, it2_);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator1 end () const {
                return (*this) ().find1 (1, (*this) ().size1 (), it2_);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_;
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<self_type>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ < it.it2_;
            }

        private:
            size_type it1_;
            size_type it2_;

            friend class const_iterator2;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find2 (0, 0, size2_);
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 crbegin1 () const {
            return rbegin1 ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 crend1 () const {
            return rend1 ();
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 crbegin2 () const {
            return rbegin2 ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 crend2 () const {
            return rend2 ();
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

    private:
        size_type size1_;
        size_type size2_;
        size_type lower_;
        size_type upper_;
        array_type data_;
        typedef const value_type const_value_type;
        static const_value_type zero_;
    };

    template<class T, class L, class A>
    typename banded_matrix<T, L, A>::const_value_type banded_matrix<T, L, A>::zero_ = value_type/*zero*/();


    /** \brief A diagonal matrix of values of type \c T, which is a specialization of a banded matrix
     *
     * For a \f$(m\times m)\f$-dimensional diagonal matrix, \f$0 \leq i < m\f$ and \f$0 \leq j < m\f$, 
     * if \f$i\neq j\f$ then \f$b_{i,j}=0\f$. The default storage for diagonal matrices is packed. 
     * Orientation and storage can also be specified. Default is \c row major \c unbounded_array. 
     *
     * As a specialization of a banded matrix, the constructor of the diagonal matrix creates 
     * a banded matrix with 0 upper and lower diagonals around the main diagonal and the matrix is 
     * obviously a square matrix. Operations are optimized based on these 2 assumptions. It is 
     * \b not required by the storage to initialize elements of the matrix.  
     *
     * \tparam T the type of object stored in the matrix (like double, float, complex, etc...)
     * \tparam L the storage organization. It can be either \c row_major or \c column_major. Default is \c row_major
     * \tparam A the type of Storage array. Default is \c unbounded_array
     */
    template<class T, class L, class A>
    class diagonal_matrix:
        public banded_matrix<T, L, A> {
    public:
        typedef typename A::size_type size_type;
        typedef banded_matrix<T, L, A> matrix_type;
        typedef A array_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        diagonal_matrix ():
            matrix_type () {}
        BOOST_UBLAS_INLINE
        diagonal_matrix (size_type size):
            matrix_type (size, size) {}
        BOOST_UBLAS_INLINE
        diagonal_matrix (size_type size, const array_type& data):
            matrix_type (size, size, 0, 0, data) {}
        BOOST_UBLAS_INLINE
        diagonal_matrix (size_type size1, size_type size2):
            matrix_type (size1, size2) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        diagonal_matrix (const matrix_expression<AE> &ae):
            matrix_type (ae) {}
        BOOST_UBLAS_INLINE
        ~diagonal_matrix () {}

        // Assignment
        BOOST_UBLAS_INLINE
        diagonal_matrix &operator = (const diagonal_matrix &m) {
            matrix_type::operator = (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        diagonal_matrix &operator = (const matrix_expression<AE> &ae) {
            matrix_type::operator = (ae);
            return *this;
        }
    };

    /** \brief A banded matrix adaptator: convert a any matrix into a banded matrix expression
     *
     * For a \f$(m\times n)\f$-dimensional matrix, the \c banded_adaptor will provide a banded matrix
     * with \f$l\f$ lower and \f$u\f$ upper diagonals and \f$0 \leq i < m\f$ and \f$0 \leq j < n\f$,
     * if \f$i>j+l\f$ or \f$i<j-u\f$ then \f$b_{i,j}=0\f$. 
     *
     * Storage and location are based on those of the underlying matrix. This is important because
     * a \c banded_adaptor does not copy the matrix data to a new place. Therefore, modifying values
     * in a \c banded_adaptor matrix will also modify the underlying matrix too.
     *
     * \tparam M the type of matrix used to generate a banded matrix
     */
    template<class M>
    class banded_adaptor:
        public matrix_expression<banded_adaptor<M> > {

        typedef banded_adaptor<M> self_type;

    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_expression<self_type>::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename boost::mpl::if_<boost::is_const<M>,
                                          typename M::const_reference,
                                          typename M::reference>::type reference;
        typedef typename boost::mpl::if_<boost::is_const<M>,
                                          typename M::const_closure_type,
                                          typename M::closure_type>::type matrix_closure_type;
        typedef const self_type const_closure_type;
        typedef self_type closure_type;
        // Replaced by _temporary_traits to avoid type requirements on M
        //typedef typename M::vector_temporary_type vector_temporary_type;
        //typedef typename M::matrix_temporary_type matrix_temporary_type;
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 packed_proxy_tag>::storage_category storage_category;
        typedef typename M::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        banded_adaptor (matrix_type &data, size_type lower = 0, size_type upper = 0):
            matrix_expression<self_type> (),
            data_ (data), lower_ (lower), upper_ (upper) {}
        BOOST_UBLAS_INLINE
        banded_adaptor (const banded_adaptor &m):
            matrix_expression<self_type> (),
            data_ (m.data_), lower_ (m.lower_), upper_ (m.upper_) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return data_.size1 ();
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const {
            return data_.size2 ();
        }
        BOOST_UBLAS_INLINE
        size_type lower () const {
            return lower_;
        }
        BOOST_UBLAS_INLINE
        size_type upper () const {
            return upper_;
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        const matrix_closure_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_closure_type &data () {
            return data_;
        }

#if !defined (BOOST_UBLAS_OWN_BANDED)||(BOOST_UBLAS_LEGACY_BANDED)
        BOOST_UBLAS_INLINE
        bool is_element_in_band(size_type i, size_type j) const{
            //return (upper_+i >= j) && i <= std::min(size1() - 1, j + lower_); // We don't need to check if i is outside because it is checked anyway in the accessors.
            return (upper_+i >= j) && i <= ( j + lower_); // Essentially this band has "infinite" positive dimensions
        }
#endif

        // Element access
#ifndef BOOST_UBLAS_PROXY_CONST_MEMBER
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
            size_type k = (std::max) (i, j);
            size_type l = lower_ + j - i;
            if (k < (std::max) (size1 (), size2 ()) &&
                l < lower_ + 1 + upper_)
                return data () (i, j);
#elif BOOST_UBLAS_LEGACY_BANDED
            size_type k = j;
            size_type l = upper_ + i - j;
            if (k < size2 () &&
                l < lower_ + 1 + upper_)
                return data () (i, j);
#else
            if (is_element_in_band( i, j))
                return data () (i, j);
#endif
            return zero_;
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
            size_type k = (std::max) (i, j);
            size_type l = lower_ + j - i;
            if (k < (std::max) (size1 (), size2 ()) &&
                l < lower_ + 1 + upper_)
                return data () (i, j);
#elif BOOST_UBLAS_LEGACY_BANDED
            size_type k = j;
            size_type l = upper_ + i - j;
            if (k < size2 () &&
                l < lower_ + 1 + upper_)
                return data () (i, j);
#else
            if (is_element_in_band( i, j))
                return data () (i, j);
#endif
#ifndef BOOST_UBLAS_REFERENCE_CONST_MEMBER
            bad_index ().raise ();
#endif
            return const_cast<reference>(zero_);
        }
#else
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
            size_type k = (std::max) (i, j);
            size_type l = lower_ + j - i;
            if (k < (std::max) (size1 (), size2 ()) &&
                l < lower_ + 1 + upper_)
                return data () (i, j);
#elif BOOST_UBLAS_LEGACY_BANDED
            size_type k = j;
            size_type l = upper_ + i - j;
            if (k < size2 () &&
                l < lower_ + 1 + upper_)
                return data () (i, j);
#else
            if (is_element_in_band( i, j))
                return data () (i, j);
#endif
#ifndef BOOST_UBLAS_REFERENCE_CONST_MEMBER
            bad_index ().raise ();
#endif
            return const_cast<reference>(zero_);
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        banded_adaptor &operator = (const banded_adaptor &m) {
            matrix_assign<scalar_assign> (*this, m);
            return *this;
        }
        BOOST_UBLAS_INLINE
        banded_adaptor &assign_temporary (banded_adaptor &m) {
            *this = m;
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_adaptor &operator = (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, matrix<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_adaptor &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_adaptor& operator += (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, matrix<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_adaptor &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_adaptor& operator -= (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, matrix<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        banded_adaptor &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        banded_adaptor& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        banded_adaptor& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const banded_adaptor &ba) const {
            return (*this).data ().same_closure (ba.data ());
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (banded_adaptor &m) {
            if (this != &m) {
                BOOST_UBLAS_CHECK (lower_ == m.lower_, bad_size ());
                BOOST_UBLAS_CHECK (upper_ == m.upper_, bad_size ());
                matrix_swap<scalar_swap> (*this, m);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (banded_adaptor &m1, banded_adaptor &m2) {
            m1.swap (m2);
        }

        // Iterator types
    private:
        // Use the matrix iterator
        typedef typename M::const_iterator1 const_subiterator1_type;
        typedef typename boost::mpl::if_<boost::is_const<M>,
                                          typename M::const_iterator1,
                                          typename M::iterator1>::type subiterator1_type;
        typedef typename M::const_iterator2 const_subiterator2_type;
        typedef typename boost::mpl::if_<boost::is_const<M>,
                                          typename M::const_iterator2,
                                          typename M::iterator2>::type subiterator2_type;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator1<self_type, packed_random_access_iterator_tag> iterator1;
        typedef indexed_iterator2<self_type, packed_random_access_iterator_tag> iterator2;
        typedef indexed_const_iterator1<self_type, packed_random_access_iterator_tag> const_iterator1;
        typedef indexed_const_iterator2<self_type, packed_random_access_iterator_tag> const_iterator2;
#else
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
#endif
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator1 find1 (int rank, size_type i, size_type j) const {
            if (rank == 1) {
                size_type lower_i = (std::max) (difference_type (j - upper_), difference_type (0));
                i = (std::max) (i, lower_i);
                size_type upper_i = (std::min) (j + 1 + lower_, size1 ());
                i = (std::min) (i, upper_i);
            }
            return const_iterator1 (*this, data ().find1 (rank, i, j));
        }
        BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            if (rank == 1) {
                size_type lower_i = (std::max) (difference_type (j - upper_), difference_type (0));
                i = (std::max) (i, lower_i);
                size_type upper_i = (std::min) (j + 1 + lower_, size1 ());
                i = (std::min) (i, upper_i);
            }
            return iterator1 (*this, data ().find1 (rank, i, j));
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find2 (int rank, size_type i, size_type j) const {
            if (rank == 1) {
                size_type lower_j = (std::max) (difference_type (i - lower_), difference_type (0));
                j = (std::max) (j, lower_j);
                size_type upper_j = (std::min) (i + 1 + upper_, size2 ());
                j = (std::min) (j, upper_j);
            }
            return const_iterator2 (*this, data ().find2 (rank, i, j));
        }
        BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            if (rank == 1) {
                size_type lower_j = (std::max) (difference_type (i - lower_), difference_type (0));
                j = (std::max) (j, lower_j);
                size_type upper_j = (std::min) (i + 1 + upper_, size2 ());
                j = (std::min) (j, upper_j);
            }
            return iterator2 (*this, data ().find2 (rank, i, j));
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator1:
            public container_const_reference<banded_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
                                                   typename const_subiterator1_type::iterator_category, packed_random_access_iterator_tag>::iterator_category,
                                               const_iterator1, value_type> {
        public:
            typedef typename const_subiterator1_type::value_type value_type;
            typedef typename const_subiterator1_type::difference_type difference_type;
            typedef typename const_subiterator1_type::reference reference;
            typedef typename const_subiterator1_type::pointer pointer;

            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<self_type> (), it1_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const self_type &m, const const_subiterator1_type &it1):
                container_const_reference<self_type> (m), it1_ (it1) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<self_type> (it ()), it1_ (it.it1_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                size_type i = index1 ();
                size_type j = index2 ();
                BOOST_UBLAS_CHECK (i < (*this) ().size1 (), bad_index ());
                BOOST_UBLAS_CHECK (j < (*this) ().size2 (), bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
                size_type k = (std::max) (i, j);
                size_type l = (*this) ().lower () + j - i;
                if (k < (std::max) ((*this) ().size1 (), (*this) ().size2 ()) &&
                    l < (*this) ().lower () + 1 + (*this) ().upper ())
                    return *it1_;
#else
                size_type k = j;
                size_type l = (*this) ().upper () + i - j;
                if (k < (*this) ().size2 () &&
                    l < (*this) ().lower () + 1 + (*this) ().upper ())
                    return *it1_;
#endif
                return (*this) () (i, j);
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 begin () const {
                return (*this) ().find2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 cbegin () const {
                return begin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 end () const {
                return (*this) ().find2 (1, index1 (), (*this) ().size2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 cend () const {
                return end ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 crbegin () const {
                return rbegin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 crend () const {
                return rend ();
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index1 ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it1_.index2 ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<self_type>::assign (&it ());
                it1_ = it.it1_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_;
            }

        private:
            const_subiterator1_type it1_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 cbegin1 () const {
            return begin1 ();
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find1 (0, size1 (), 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 cend1 () const {
            return end1 ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator1:
            public container_reference<banded_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
                                                   typename subiterator1_type::iterator_category, packed_random_access_iterator_tag>::iterator_category,
                                               iterator1, value_type> {
        public:
            typedef typename subiterator1_type::value_type value_type;
            typedef typename subiterator1_type::difference_type difference_type;
            typedef typename subiterator1_type::reference reference;
            typedef typename subiterator1_type::pointer pointer;

            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<self_type> (), it1_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (self_type &m, const subiterator1_type &it1):
                container_reference<self_type> (m), it1_ (it1) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                size_type i = index1 ();
                size_type j = index2 ();
                BOOST_UBLAS_CHECK (i < (*this) ().size1 (), bad_index ());
                BOOST_UBLAS_CHECK (j < (*this) ().size2 (), bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
                size_type k = (std::max) (i, j);
                size_type l = (*this) ().lower () + j - i;
                if (k < (std::max) ((*this) ().size1 (), (*this) ().size2 ()) &&
                    l < (*this) ().lower () + 1 + (*this) ().upper ())
                    return *it1_;
#else
                size_type k = j;
                size_type l = (*this) ().upper () + i - j;
                if (k < (*this) ().size2 () &&
                    l < (*this) ().lower () + 1 + (*this) ().upper ())
                    return *it1_;
#endif
                return (*this) () (i, j);
            }
            BOOST_UBLAS_INLINE
            reference operator [] (difference_type n) const {
                return *(*this + n);
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator2 begin () const {
                return (*this) ().find2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator2 end () const {
                return (*this) ().find2 (1, index1 (), (*this) ().size2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index1 ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it1_.index2 ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<self_type>::assign (&it ());
                it1_ = it.it1_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_;
            }

        private:
            subiterator1_type it1_;

            friend class const_iterator1;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find1 (0, size1 (), 0);
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator2:
            public container_const_reference<banded_adaptor>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef typename iterator_restrict_traits<typename const_subiterator2_type::iterator_category,
                                                      packed_random_access_iterator_tag>::iterator_category iterator_category;
            typedef typename const_subiterator2_type::value_type value_type;
            typedef typename const_subiterator2_type::difference_type difference_type;
            typedef typename const_subiterator2_type::reference reference;
            typedef typename const_subiterator2_type::pointer pointer;

            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<self_type> (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const self_type &m, const const_subiterator2_type &it2):
                container_const_reference<self_type> (m), it2_ (it2) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<self_type> (it ()), it2_ (it.it2_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                size_type i = index1 ();
                size_type j = index2 ();
                BOOST_UBLAS_CHECK (i < (*this) ().size1 (), bad_index ());
                BOOST_UBLAS_CHECK (j < (*this) ().size2 (), bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
                size_type k = (std::max) (i, j);
                size_type l = (*this) ().lower () + j - i;
                if (k < (std::max) ((*this) ().size1 (), (*this) ().size2 ()) &&
                    l < (*this) ().lower () + 1 + (*this) ().upper ())
                    return *it2_;
#else
                size_type k = j;
                size_type l = (*this) ().upper () + i - j;
                if (k < (*this) ().size2 () &&
                    l < (*this) ().lower () + 1 + (*this) ().upper ())
                    return *it2_;
#endif
                return (*this) () (i, j);
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 begin () const {
                return (*this) ().find1 (1, 0, index2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 cbegin () const {
                return begin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 end () const {
                return (*this) ().find1 (1, (*this) ().size1 (), index2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 cend () const {
                return end ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 crbegin () const {
                return rbegin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 crend () const {
                return rend ();
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it2_.index1 ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index2 ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<self_type>::assign (&it ());
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it2_ < it.it2_;
            }

        private:
            const_subiterator2_type it2_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 cbegin2 () const {
            return begin2 ();
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find2 (0, 0, size2 ());
        }
        BOOST_UBLAS_INLINE
        const_iterator2 cend2 () const {
            return end2 ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator2:
            public container_reference<banded_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
                                                   typename subiterator2_type::iterator_category, packed_random_access_iterator_tag>::iterator_category,
                                               iterator2, value_type> {
        public:
            typedef typename subiterator2_type::value_type value_type;
            typedef typename subiterator2_type::difference_type difference_type;
            typedef typename subiterator2_type::reference reference;
            typedef typename subiterator2_type::pointer pointer;

            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<self_type> (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (self_type &m, const subiterator2_type &it2):
                container_reference<self_type> (m), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                size_type i = index1 ();
                size_type j = index2 ();
                BOOST_UBLAS_CHECK (i < (*this) ().size1 (), bad_index ());
                BOOST_UBLAS_CHECK (j < (*this) ().size2 (), bad_index ());
#ifdef BOOST_UBLAS_OWN_BANDED
                size_type k = (std::max) (i, j);
                size_type l = (*this) ().lower () + j - i;
                if (k < (std::max) ((*this) ().size1 (), (*this) ().size2 ()) &&
                    l < (*this) ().lower () + 1 + (*this) ().upper ())
                    return *it2_;
#else
                size_type k = j;
                size_type l = (*this) ().upper () + i - j;
                if (k < (*this) ().size2 () &&
                    l < (*this) ().lower () + 1 + (*this) ().upper ())
                    return *it2_;
#endif
                return (*this) () (i, j);
            }
            BOOST_UBLAS_INLINE
            reference operator [] (difference_type n) const {
                return *(*this + n);
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator1 begin () const {
                return (*this) ().find1 (1, 0, index2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator1 end () const {
                return (*this) ().find1 (1, (*this) ().size1 (), index2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it2_.index1 ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index2 ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<self_type>::assign (&it ());
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it2_ < it.it2_;
            }

        private:
            subiterator2_type it2_;

            friend class const_iterator2;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find2 (0, 0, size2 ());
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 crbegin1 () const {
            return rbegin1 ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 crend1 () const {
            return rend1 ();
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 crbegin2 () const {
            return rbegin2 ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 crend2 () const {
            return rend2 ();
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

    private:
        matrix_closure_type data_;
        size_type lower_;
        size_type upper_;
        typedef const value_type const_value_type;
        static const_value_type zero_;
    };

    // Specialization for temporary_traits
    template <class M>
    struct vector_temporary_traits< banded_adaptor<M> >
    : vector_temporary_traits< M > {} ;
    template <class M>
    struct vector_temporary_traits< const banded_adaptor<M> >
    : vector_temporary_traits< M > {} ;

    template <class M>
    struct matrix_temporary_traits< banded_adaptor<M> >
    : matrix_temporary_traits< M > {} ;
    template <class M>
    struct matrix_temporary_traits< const banded_adaptor<M> >
    : matrix_temporary_traits< M > {} ;


    template<class M>
    typename banded_adaptor<M>::const_value_type banded_adaptor<M>::zero_ = value_type/*zero*/();

    /** \brief A diagonal matrix adaptator: convert a any matrix into a diagonal matrix expression
     *
     * For a \f$(m\times m)\f$-dimensional matrix, the \c diagonal_adaptor will provide a diagonal matrix
     * with \f$0 \leq i < m\f$ and \f$0 \leq j < m\f$, if \f$i\neq j\f$ then \f$b_{i,j}=0\f$. 
     *
     * Storage and location are based on those of the underlying matrix. This is important because
     * a \c diagonal_adaptor does not copy the matrix data to a new place. Therefore, modifying values
     * in a \c diagonal_adaptor matrix will also modify the underlying matrix too.
     *
     * \tparam M the type of matrix used to generate the diagonal matrix
     */

    template<class M>
    class diagonal_adaptor:
        public banded_adaptor<M> {
    public:
        typedef M matrix_type;
        typedef banded_adaptor<M> adaptor_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        diagonal_adaptor ():
            adaptor_type () {}
        BOOST_UBLAS_INLINE
        diagonal_adaptor (matrix_type &data):
            adaptor_type (data) {}
        BOOST_UBLAS_INLINE
        ~diagonal_adaptor () {}

        // Assignment
        BOOST_UBLAS_INLINE
        diagonal_adaptor &operator = (const diagonal_adaptor &m) {
            adaptor_type::operator = (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        diagonal_adaptor &operator = (const matrix_expression<AE> &ae) {
            adaptor_type::operator = (ae);
            return *this;
        }
    };

}}}

#endif

/* banded.hpp
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
*/