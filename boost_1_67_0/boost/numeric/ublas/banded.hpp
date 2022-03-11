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