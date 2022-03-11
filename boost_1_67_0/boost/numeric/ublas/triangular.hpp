//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_TRIANGULAR_
#define _BOOST_UBLAS_TRIANGULAR_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/detail/temporary.hpp>
#include <boost/type_traits/remove_const.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    namespace detail {
        using namespace boost::numeric::ublas;

        // Matrix resizing algorithm
        template <class L, class T, class M>
        BOOST_UBLAS_INLINE
        void matrix_resize_preserve (M& m, M& temporary) {
            typedef L layout_type;
            typedef T triangular_type;
            typedef typename M::size_type size_type;
            const size_type msize1 (m.size1 ());        // original size
            const size_type msize2 (m.size2 ());
            const size_type size1 (temporary.size1 ());    // new size is specified by temporary
            const size_type size2 (temporary.size2 ());
            // Common elements to preserve
            const size_type size1_min = (std::min) (size1, msize1);
            const size_type size2_min = (std::min) (size2, msize2);
            // Order for major and minor sizes
            const size_type major_size = layout_type::size_M (size1_min, size2_min);
            const size_type minor_size = layout_type::size_m (size1_min, size2_min);
            // Indexing copy over major
            for (size_type major = 0; major != major_size; ++major) {
                for (size_type minor = 0; minor != minor_size; ++minor) {
                        // find indexes - use invertability of element_ functions
                    const size_type i1 = layout_type::index_M(major, minor);
                    const size_type i2 = layout_type::index_m(major, minor);
                    if ( triangular_type::other(i1,i2) ) {
                        temporary.data () [triangular_type::element (layout_type (), i1, size1, i2, size2)] =
                            m.data() [triangular_type::element (layout_type (), i1, msize1, i2, msize2)];
                    }
                }
            }
            m.assign_temporary (temporary);
        }
    }

    /** \brief A triangular matrix of values of type \c T.
     *
     * For a \f$(n \times n )\f$-dimensional lower triangular matrix and if \f$0 \leq i < n\f$, \f$0 \leq j < n\f$ and \f$i>j\f$ holds, 
     * \f$m_{i,j}=0\f$. Furthermore if \f$m_{i,i}=1\f$, the matrix is called unit lower triangular.
     *
     * For a \f$(n \times n )\f$-dimensional upper triangular matrix and if \f$0 \leq i < n\f$, \f$0 \leq j < n\f$ and \f$i<j\f$ holds, 
     * \f$m_{i,j}=0\f$. Furthermore if \f$m_{i,i}=1\f$, the matrix is called unit upper triangular.
     *
     * The default storage for triangular matrices is packed. Orientation and storage can also be specified. 
     * Default is \c row_major and and unbounded_array. It is \b not required by the storage to initialize 
     * elements of the matrix.
     *
     * \tparam T the type of object stored in the matrix (like double, float, complex, etc...)
     * \tparam TRI the type of the triangular matrix. It can either be \c lower or \c upper. Default is \c lower
     * \tparam L the storage organization. It can be either \c row_major or \c column_major. Default is \c row_major
     * \tparam A the type of Storage array. Default is \c unbounded_array
     */
    template<class T, class TRI, class L, class A>
    class triangular_matrix:
        public matrix_container<triangular_matrix<T, TRI, L, A> > {

        typedef T *pointer;
        typedef TRI triangular_type;
        typedef L layout_type;
        typedef triangular_matrix<T, TRI, L, A> self_type;
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

        // Construction and destruction
        BOOST_UBLAS_INLINE
        triangular_matrix ():
            matrix_container<self_type> (),
            size1_ (0), size2_ (0), data_ (0) {}
        BOOST_UBLAS_INLINE
        triangular_matrix (size_type size1, size_type size2):
            matrix_container<self_type> (),
            size1_ (size1), size2_ (size2), data_ (triangular_type::packed_size (layout_type (), size1, size2)) {
        }
        BOOST_UBLAS_INLINE
        triangular_matrix (size_type size1, size_type size2, const array_type &data):
            matrix_container<self_type> (),
            size1_ (size1), size2_ (size2), data_ (data) {}
        BOOST_UBLAS_INLINE
        triangular_matrix (const triangular_matrix &m):
            matrix_container<self_type> (),
            size1_ (m.size1_), size2_ (m.size2_), data_ (m.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_matrix (const matrix_expression<AE> &ae):
            matrix_container<self_type> (),
            size1_ (ae ().size1 ()), size2_ (ae ().size2 ()),
            data_ (triangular_type::packed_size (layout_type (), size1_, size2_)) {
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

        // Storage accessors
        BOOST_UBLAS_INLINE
        const array_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        array_type &data () {
            return data_;
        }

        // Resizing
        BOOST_UBLAS_INLINE
        void resize (size_type size1, size_type size2, bool preserve = true) {
            if (preserve) {
                self_type temporary (size1, size2);
                detail::matrix_resize_preserve<layout_type, triangular_type> (*this, temporary);
            }
            else {
                data ().resize (triangular_type::packed_size (layout_type (), size1, size2));
                size1_ = size1;
                size2_ = size2;
            }
        }
        BOOST_UBLAS_INLINE
        void resize_packed_preserve (size_type size1, size_type size2) {
            size1_ = size1;
            size2_ = size2;
            data ().resize (triangular_type::packed_size (layout_type (), size1_, size2_), value_type ());
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (i < size1_, bad_index ());
            BOOST_UBLAS_CHECK (j < size2_, bad_index ());
            if (triangular_type::other (i, j))
                return data () [triangular_type::element (layout_type (), i, size1_, j, size2_)];
            else if (triangular_type::one (i, j))
                return one_;
            else
                return zero_;
        }
        BOOST_UBLAS_INLINE
        reference at_element (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1_, bad_index ());
            BOOST_UBLAS_CHECK (j < size2_, bad_index ());
            return data () [triangular_type::element (layout_type (), i, size1_, j, size2_)];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1_, bad_index ());
            BOOST_UBLAS_CHECK (j < size2_, bad_index ());
            if (!triangular_type::other (i, j)) {
                bad_index ().raise ();
                // NEVER reached
            }
            return data () [triangular_type::element (layout_type (), i, size1_, j, size2_)];
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
            // data ().clear ();
            std::fill (data ().begin (), data ().end (), value_type/*zero*/());
        }

        // Assignment
        BOOST_UBLAS_INLINE
        triangular_matrix &operator = (const triangular_matrix &m) {
            size1_ = m.size1_;
            size2_ = m.size2_;
            data () = m.data ();
            return *this;
        }
        BOOST_UBLAS_INLINE
        triangular_matrix &assign_temporary (triangular_matrix &m) {
            swap (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_matrix &operator = (const matrix_expression<AE> &ae) {
            self_type temporary (ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_matrix &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_matrix& operator += (const matrix_expression<AE> &ae) {
            self_type temporary (*this + ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_matrix &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_matrix& operator -= (const matrix_expression<AE> &ae) {
            self_type temporary (*this - ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_matrix &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        triangular_matrix& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        triangular_matrix& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (triangular_matrix &m) {
            if (this != &m) {
                // BOOST_UBLAS_CHECK (size2_ == m.size2_, bad_size ());
                std::swap (size1_, m.size1_);
                std::swap (size2_, m.size2_);
                data ().swap (m.data ());
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (triangular_matrix &m1, triangular_matrix &m2) {
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
            if (rank == 1)
                i = triangular_type::restrict1 (i, j, size1_, size2_);
            if (rank == 0)
                i = triangular_type::global_restrict1 (i, size1_, j, size2_);
            return const_iterator1 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            if (rank == 1)
                i = triangular_type::mutable_restrict1 (i, j, size1_, size2_);
            if (rank == 0)
                i = triangular_type::global_mutable_restrict1 (i, size1_, j, size2_);
            return iterator1 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find2 (int rank, size_type i, size_type j) const {
            if (rank == 1)
                j = triangular_type::restrict2 (i, j, size1_, size2_);
            if (rank == 0)
                j = triangular_type::global_restrict2 (i, size1_, j, size2_);
            return const_iterator2 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            if (rank == 1)
                j = triangular_type::mutable_restrict2 (i, j, size1_, size2_);
            if (rank == 0)
                j = triangular_type::global_mutable_restrict2 (i, size1_, j, size2_);
            return iterator2 (*this, i, j);
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator1:
            public container_const_reference<triangular_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               const_iterator1, value_type> {
        public:
            typedef typename triangular_matrix::value_type value_type;
            typedef typename triangular_matrix::difference_type difference_type;
            typedef typename triangular_matrix::const_reference reference;
            typedef const typename triangular_matrix::pointer pointer;

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
            public container_reference<triangular_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               iterator1, value_type> {
        public:
            typedef typename triangular_matrix::value_type value_type;
            typedef typename triangular_matrix::difference_type difference_type;
            typedef typename triangular_matrix::reference reference;
            typedef typename triangular_matrix::pointer pointer;

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
                return (*this) () (it1_, it2_);
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
            public container_const_reference<triangular_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef typename triangular_matrix::value_type value_type;
            typedef typename triangular_matrix::difference_type difference_type;
            typedef typename triangular_matrix::const_reference reference;
            typedef const typename triangular_matrix::pointer pointer;

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
            public container_reference<triangular_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               iterator2, value_type> {
        public:
            typedef typename triangular_matrix::value_type value_type;
            typedef typename triangular_matrix::difference_type difference_type;
            typedef typename triangular_matrix::reference reference;
            typedef typename triangular_matrix::pointer pointer;

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
                return (*this) () (it1_, it2_);
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
        array_type data_;
        static const value_type zero_;
        static const value_type one_;
    };

    template<class T, class TRI, class L, class A>
    const typename triangular_matrix<T, TRI, L, A>::value_type triangular_matrix<T, TRI, L, A>::zero_ = value_type/*zero*/();
    template<class T, class TRI, class L, class A>
    const typename triangular_matrix<T, TRI, L, A>::value_type triangular_matrix<T, TRI, L, A>::one_ (1);


    // Triangular matrix adaptor class
    template<class M, class TRI>
    class triangular_adaptor:
        public matrix_expression<triangular_adaptor<M, TRI> > {

        typedef triangular_adaptor<M, TRI> self_type;

    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_expression<self_type>::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef TRI triangular_type;
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
        triangular_adaptor (matrix_type &data):
            matrix_expression<self_type> (),
            data_ (data) {}
        BOOST_UBLAS_INLINE
        triangular_adaptor (const triangular_adaptor &m):
            matrix_expression<self_type> (),
            data_ (m.data_) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return data_.size1 ();
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const {
            return data_.size2 ();
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

        // Element access
#ifndef BOOST_UBLAS_PROXY_CONST_MEMBER
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
            if (triangular_type::other (i, j))
                return data () (i, j);
            else if (triangular_type::one (i, j))
                return one_;
            else
                return zero_;
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
            if (!triangular_type::other (i, j)) {
                bad_index ().raise ();
                // NEVER reached
            }
            return data () (i, j);
        }
#else
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
            if (!triangular_type::other (i, j)) {
                bad_index ().raise ();
                // NEVER reached
            }
            return data () (i, j);
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        triangular_adaptor &operator = (const triangular_adaptor &m) {
            matrix_assign<scalar_assign> (*this, m);
            return *this;
        }
        BOOST_UBLAS_INLINE
        triangular_adaptor &assign_temporary (triangular_adaptor &m) {
            *this = m;
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_adaptor &operator = (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, matrix<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_adaptor &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_adaptor& operator += (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, matrix<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_adaptor &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_adaptor& operator -= (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, matrix<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        triangular_adaptor &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        triangular_adaptor& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        triangular_adaptor& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const triangular_adaptor &ta) const {
            return (*this).data ().same_closure (ta.data ());
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (triangular_adaptor &m) {
            if (this != &m)
                matrix_swap<scalar_swap> (*this, m);
        }
        BOOST_UBLAS_INLINE
        friend void swap (triangular_adaptor &m1, triangular_adaptor &m2) {
            m1.swap (m2);
        }

        // Iterator types
   private:
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
            if (rank == 1)
                i = triangular_type::restrict1 (i, j, size1(), size2());
            if (rank == 0)
                i = triangular_type::global_restrict1 (i, size1(), j, size2());
            return const_iterator1 (*this, data ().find1 (rank, i, j));
        }
        BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            if (rank == 1)
                i = triangular_type::mutable_restrict1 (i, j, size1(), size2());
            if (rank == 0)
                i = triangular_type::global_mutable_restrict1 (i, size1(), j, size2());
            return iterator1 (*this, data ().find1 (rank, i, j));
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find2 (int rank, size_type i, size_type j) const {
            if (rank == 1)
                j = triangular_type::restrict2 (i, j, size1(), size2());
            if (rank == 0)
                j = triangular_type::global_restrict2 (i, size1(), j, size2());
            return const_iterator2 (*this, data ().find2 (rank, i, j));
        }
        BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            if (rank == 1)
                j = triangular_type::mutable_restrict2 (i, j, size1(), size2());
            if (rank == 0)
                j = triangular_type::global_mutable_restrict2 (i, size1(), j, size2());
            return iterator2 (*this, data ().find2 (rank, i, j));
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator1:
            public container_const_reference<triangular_adaptor>,
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
                if (triangular_type::other (i, j))
                    return *it1_;
                else
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
            public container_reference<triangular_adaptor>,
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
                if (triangular_type::other (i, j))
                    return *it1_;
                else
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
            public container_const_reference<triangular_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
                                                   typename const_subiterator1_type::iterator_category, packed_random_access_iterator_tag>::iterator_category,
                                               const_iterator2, value_type> {
        public:
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
                if (triangular_type::other (i, j))
                    return *it2_;
                else
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
            public container_reference<triangular_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
                                                   typename subiterator1_type::iterator_category, packed_random_access_iterator_tag>::iterator_category,
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
                if (triangular_type::other (i, j))
                    return *it2_;
                else
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
        static const value_type zero_;
        static const value_type one_;
    };

    template<class M, class TRI>
    const typename triangular_adaptor<M, TRI>::value_type triangular_adaptor<M, TRI>::zero_ = value_type/*zero*/();
    template<class M, class TRI>
    const typename triangular_adaptor<M, TRI>::value_type triangular_adaptor<M, TRI>::one_ (1);

    template <class M, class TRI>
    struct vector_temporary_traits< triangular_adaptor<M, TRI> >
    : vector_temporary_traits< typename boost::remove_const<M>::type > {} ;
    template <class M, class TRI>
    struct vector_temporary_traits< const triangular_adaptor<M, TRI> >
    : vector_temporary_traits< typename boost::remove_const<M>::type > {} ;

    template <class M, class TRI>
    struct matrix_temporary_traits< triangular_adaptor<M, TRI> >
    : matrix_temporary_traits< typename boost::remove_const<M>::type > {};
    template <class M, class TRI>
    struct matrix_temporary_traits< const triangular_adaptor<M, TRI> >
    : matrix_temporary_traits< typename boost::remove_const<M>::type > {};


    template<class E1, class E2>
    struct matrix_vector_solve_traits {
        typedef typename promote_traits<typename E1::value_type, typename E2::value_type>::promote_type promote_type;
        typedef vector<promote_type> result_type;
    };

    // Operations:
    //  n * (n - 1) / 2 + n = n * (n + 1) / 2 multiplications,
    //  n * (n - 1) / 2 additions

    // Dense (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag, column_major_tag, dense_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (size_type n = 0; n < size; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n) /= e1 () (n, n);
            if (t != value_type/*zero*/()) {
                for (size_type m = n + 1; m < size; ++ m)
                    e2 () (m) -= e1 () (m, n) * t;
            }
        }
    }
    // Packed (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag, column_major_tag, packed_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (size_type n = 0; n < size; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n) /= e1 () (n, n);
            if (t != value_type/*zero*/()) {
                typename E1::const_iterator1 it1e1 (e1 ().find1 (1, n + 1, n));
                typename E1::const_iterator1 it1e1_end (e1 ().find1 (1, e1 ().size1 (), n));
                difference_type m (it1e1_end - it1e1);
                while (-- m >= 0)
                    e2 () (it1e1.index1 ()) -= *it1e1 * t, ++ it1e1;
            }
        }
    }
    // Sparse (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag, column_major_tag, unknown_storage_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (size_type n = 0; n < size; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n) /= e1 () (n, n);
            if (t != value_type/*zero*/()) {
                typename E1::const_iterator1 it1e1 (e1 ().find1 (1, n + 1, n));
                typename E1::const_iterator1 it1e1_end (e1 ().find1 (1, e1 ().size1 (), n));
                while (it1e1 != it1e1_end)
                    e2 () (it1e1.index1 ()) -= *it1e1 * t, ++ it1e1;
            }
        }
    }

    // Dense (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag, row_major_tag, dense_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (size_type n = 0; n < size; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n) /= e1 () (n, n);
            if (t != value_type/*zero*/()) {
                for (size_type m = n + 1; m < size; ++ m)
                    e2 () (m) -= e1 () (m, n) * t;
            }
        }
    }
    // Packed (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag, row_major_tag, packed_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (size_type n = 0; n < size; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n);
            typename E1::const_iterator2 it2e1 (e1 ().find2 (1, n, 0));
            typename E1::const_iterator2 it2e1_end (e1 ().find2 (1, n, n));
            while (it2e1 != it2e1_end) {
              t -= *it2e1 * e2 () (it2e1.index2());
              ++ it2e1;
            }
            e2() (n) = t / e1 () (n, n);
        }
    }
    // Sparse (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag, row_major_tag, unknown_storage_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (size_type n = 0; n < size; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n);
            typename E1::const_iterator2 it2e1 (e1 ().find2 (1, n, 0));
            typename E1::const_iterator2 it2e1_end (e1 ().find2 (1, n, n));
            while (it2e1 != it2e1_end) {
              t -= *it2e1 * e2 () (it2e1.index2());
              ++ it2e1;
            }
            e2() (n) = t / e1 () (n, n);
        }
    }

    // Redirectors :-)
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag, column_major_tag) {
        typedef typename E1::storage_category storage_category;
        inplace_solve (e1, e2,
                       lower_tag (), column_major_tag (), storage_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag, row_major_tag) {
        typedef typename E1::storage_category storage_category;
        inplace_solve (e1, e2,
                       lower_tag (), row_major_tag (), storage_category ());
    }
    // Dispatcher
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        lower_tag) {
        typedef typename E1::orientation_category orientation_category;
        inplace_solve (e1, e2,
                       lower_tag (), orientation_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        unit_lower_tag) {
        typedef typename E1::orientation_category orientation_category;
        inplace_solve (triangular_adaptor<const E1, unit_lower> (e1 ()), e2,
                       unit_lower_tag (), orientation_category ());
    }

    // Dense (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag, column_major_tag, dense_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (difference_type n = size - 1; n >= 0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n) /= e1 () (n, n);
            if (t != value_type/*zero*/()) {
                for (difference_type m = n - 1; m >= 0; -- m)
                    e2 () (m) -= e1 () (m, n) * t;
            }
        }
    }
    // Packed (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag, column_major_tag, packed_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (difference_type n = size - 1; n >= 0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n) /= e1 () (n, n);
            if (t != value_type/*zero*/()) {
                typename E1::const_reverse_iterator1 it1e1 (e1 ().find1 (1, n, n));
                typename E1::const_reverse_iterator1 it1e1_rend (e1 ().find1 (1, 0, n));
                while (it1e1 != it1e1_rend) {
                  e2 () (it1e1.index1 ()) -= *it1e1 * t, ++ it1e1;
                }
            }
        }
    }
    // Sparse (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag, column_major_tag, unknown_storage_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e2 ().size ();
        for (difference_type n = size - 1; n >= 0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n) /= e1 () (n, n);
            if (t != value_type/*zero*/()) {
                typename E1::const_reverse_iterator1 it1e1 (e1 ().find1 (1, n, n));
                typename E1::const_reverse_iterator1 it1e1_rend (e1 ().find1 (1, 0, n));
                while (it1e1 != it1e1_rend) {
                  e2 () (it1e1.index1 ()) -= *it1e1 * t, ++ it1e1;
                }
            }
        }
    }

    // Dense (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag, row_major_tag, dense_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e1 ().size1 ();
        for (difference_type n = size-1; n >=0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n);
            for (difference_type m = n + 1; m < static_cast<difference_type>(e1 ().size2()); ++ m) {
              t -= e1 () (n, m)  * e2 () (m);
            }
            e2() (n) = t / e1 () (n, n);
        }
    }
    // Packed (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag, row_major_tag, packed_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e1 ().size1 ();
        for (difference_type n = size-1; n >=0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n);
            typename E1::const_iterator2 it2e1 (e1 ().find2 (1, n, n+1));
            typename E1::const_iterator2 it2e1_end (e1 ().find2 (1, n, e1 ().size2 ()));
            while (it2e1 != it2e1_end) {
              t -= *it2e1 * e2 () (it2e1.index2());
              ++ it2e1;
            }
            e2() (n) = t / e1 () (n, n);

        }
    }
    // Sparse (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag, row_major_tag, unknown_storage_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size (), bad_size ());
        size_type size = e1 ().size1 ();
        for (difference_type n = size-1; n >=0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            value_type t = e2 () (n);
            typename E1::const_iterator2 it2e1 (e1 ().find2 (1, n, n+1));
            typename E1::const_iterator2 it2e1_end (e1 ().find2 (1, n, e1 ().size2 ()));
            while (it2e1 != it2e1_end) {
              t -= *it2e1 * e2 () (it2e1.index2());
              ++ it2e1;
            }
            e2() (n) = t / e1 () (n, n);

        }
    }

    // Redirectors :-)
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag, column_major_tag) {
        typedef typename E1::storage_category storage_category;
        inplace_solve (e1, e2,
                       upper_tag (), column_major_tag (), storage_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag, row_major_tag) {
        typedef typename E1::storage_category storage_category;
        inplace_solve (e1, e2,
                       upper_tag (), row_major_tag (), storage_category ());
    }
    // Dispatcher
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        upper_tag) {
        typedef typename E1::orientation_category orientation_category;
        inplace_solve (e1, e2,
                       upper_tag (), orientation_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, vector_expression<E2> &e2,
                        unit_upper_tag) {
        typedef typename E1::orientation_category orientation_category;
        inplace_solve (triangular_adaptor<const E1, unit_upper> (e1 ()), e2,
                       unit_upper_tag (), orientation_category ());
    }

    template<class E1, class E2, class C>
    BOOST_UBLAS_INLINE
    typename matrix_vector_solve_traits<E1, E2>::result_type
    solve (const matrix_expression<E1> &e1,
           const vector_expression<E2> &e2,
           C) {
        typename matrix_vector_solve_traits<E1, E2>::result_type r (e2);
        inplace_solve (e1, r, C ());
        return r;
    }


    // Redirectors :-)
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (vector_expression<E1> &e1, const matrix_expression<E2> &e2,
                        lower_tag, row_major_tag) {
        typedef typename E2::storage_category storage_category;
        inplace_solve (trans(e2), e1,
                       upper_tag (), column_major_tag (), storage_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (vector_expression<E1> &e1, const matrix_expression<E2> &e2,
                        lower_tag, column_major_tag) {
        typedef typename E2::storage_category storage_category;
        inplace_solve (trans (e2), e1,
                       upper_tag (), row_major_tag (), storage_category ());
    }
    // Dispatcher
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (vector_expression<E1> &e1, const matrix_expression<E2> &e2,
                        lower_tag) {
        typedef typename E2::orientation_category orientation_category;
        inplace_solve (e1, e2,
                       lower_tag (), orientation_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (vector_expression<E1> &e1, const matrix_expression<E2> &e2,
                        unit_lower_tag) {
        typedef typename E2::orientation_category orientation_category;
        inplace_solve (e1, triangular_adaptor<const E2, unit_lower> (e2 ()),
                       unit_lower_tag (), orientation_category ());
    }


    // Redirectors :-)
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (vector_expression<E1> &e1, const matrix_expression<E2> &e2,
                        upper_tag, row_major_tag) {
        typedef typename E2::storage_category storage_category;
        inplace_solve (trans(e2), e1,
                       lower_tag (), column_major_tag (), storage_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (vector_expression<E1> &e1, const matrix_expression<E2> &e2,
                        upper_tag, column_major_tag) {
        typedef typename E2::storage_category storage_category;
        inplace_solve (trans (e2), e1,
                       lower_tag (), row_major_tag (), storage_category ());
    }
    // Dispatcher
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (vector_expression<E1> &e1, const matrix_expression<E2> &e2,
                        upper_tag) {
        typedef typename E2::orientation_category orientation_category;
        inplace_solve (e1, e2,
                       upper_tag (), orientation_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (vector_expression<E1> &e1, const matrix_expression<E2> &e2,
                        unit_upper_tag) {
        typedef typename E2::orientation_category orientation_category;
        inplace_solve (e1, triangular_adaptor<const E2, unit_upper> (e2 ()),
                       unit_upper_tag (), orientation_category ());
    }

    template<class E1, class E2, class C>
    BOOST_UBLAS_INLINE
    typename matrix_vector_solve_traits<E1, E2>::result_type
    solve (const vector_expression<E1> &e1,
           const matrix_expression<E2> &e2,
           C) {
        typename matrix_vector_solve_traits<E1, E2>::result_type r (e1);
        inplace_solve (r, e2, C ());
        return r;
    }

    template<class E1, class E2>
    struct matrix_matrix_solve_traits {
        typedef typename promote_traits<typename E1::value_type, typename E2::value_type>::promote_type promote_type;
        typedef matrix<promote_type> result_type;
    };

    // Operations:
    //  k * n * (n - 1) / 2 + k * n = k * n * (n + 1) / 2 multiplications,
    //  k * n * (n - 1) / 2 additions

    // Dense (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        lower_tag, dense_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        size_type size1 = e2 ().size1 ();
        size_type size2 = e2 ().size2 ();
        for (size_type n = 0; n < size1; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            for (size_type l = 0; l < size2; ++ l) {
                value_type t = e2 () (n, l) /= e1 () (n, n);
                if (t != value_type/*zero*/()) {
                    for (size_type m = n + 1; m < size1; ++ m)
                        e2 () (m, l) -= e1 () (m, n) * t;
                }
            }
        }
    }
    // Packed (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        lower_tag, packed_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        size_type size1 = e2 ().size1 ();
        size_type size2 = e2 ().size2 ();
        for (size_type n = 0; n < size1; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            for (size_type l = 0; l < size2; ++ l) {
                value_type t = e2 () (n, l) /= e1 () (n, n);
                if (t != value_type/*zero*/()) {
                    typename E1::const_iterator1 it1e1 (e1 ().find1 (1, n + 1, n));
                    typename E1::const_iterator1 it1e1_end (e1 ().find1 (1, e1 ().size1 (), n));
                    difference_type m (it1e1_end - it1e1);
                    while (-- m >= 0)
                        e2 () (it1e1.index1 (), l) -= *it1e1 * t, ++ it1e1;
                }
            }
        }
    }
    // Sparse (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        lower_tag, unknown_storage_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        size_type size1 = e2 ().size1 ();
        size_type size2 = e2 ().size2 ();
        for (size_type n = 0; n < size1; ++ n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            for (size_type l = 0; l < size2; ++ l) {
                value_type t = e2 () (n, l) /= e1 () (n, n);
                if (t != value_type/*zero*/()) {
                    typename E1::const_iterator1 it1e1 (e1 ().find1 (1, n + 1, n));
                    typename E1::const_iterator1 it1e1_end (e1 ().find1 (1, e1 ().size1 (), n));
                    while (it1e1 != it1e1_end)
                        e2 () (it1e1.index1 (), l) -= *it1e1 * t, ++ it1e1;
                }
            }
        }
    }
    // Dispatcher
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        lower_tag) {
        typedef typename E1::storage_category dispatch_category;
        inplace_solve (e1, e2,
                       lower_tag (), dispatch_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        unit_lower_tag) {
        typedef typename E1::storage_category dispatch_category;
        inplace_solve (triangular_adaptor<const E1, unit_lower> (e1 ()), e2,
                       unit_lower_tag (), dispatch_category ());
    }

    // Dense (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        upper_tag, dense_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        size_type size1 = e2 ().size1 ();
        size_type size2 = e2 ().size2 ();
        for (difference_type n = size1 - 1; n >= 0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            for (difference_type l = size2 - 1; l >= 0; -- l) {
                value_type t = e2 () (n, l) /= e1 () (n, n);
                if (t != value_type/*zero*/()) {
                    for (difference_type m = n - 1; m >= 0; -- m)
                        e2 () (m, l) -= e1 () (m, n) * t;
                }
            }
        }
    }
    // Packed (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        upper_tag, packed_proxy_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        size_type size1 = e2 ().size1 ();
        size_type size2 = e2 ().size2 ();
        for (difference_type n = size1 - 1; n >= 0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            for (difference_type l = size2 - 1; l >= 0; -- l) {
                value_type t = e2 () (n, l) /= e1 () (n, n);
                if (t != value_type/*zero*/()) {
                    typename E1::const_reverse_iterator1 it1e1 (e1 ().find1 (1, n, n));
                    typename E1::const_reverse_iterator1 it1e1_rend (e1 ().find1 (1, 0, n));
                    difference_type m (it1e1_rend - it1e1);
                    while (-- m >= 0)
                        e2 () (it1e1.index1 (), l) -= *it1e1 * t, ++ it1e1;
                }
            }
        }
    }
    // Sparse (proxy) case
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        upper_tag, unknown_storage_tag) {
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename E2::value_type value_type;

        BOOST_UBLAS_CHECK (e1 ().size1 () == e1 ().size2 (), bad_size ());
        BOOST_UBLAS_CHECK (e1 ().size2 () == e2 ().size1 (), bad_size ());
        size_type size1 = e2 ().size1 ();
        size_type size2 = e2 ().size2 ();
        for (difference_type n = size1 - 1; n >= 0; -- n) {
#ifndef BOOST_UBLAS_SINGULAR_CHECK
            BOOST_UBLAS_CHECK (e1 () (n, n) != value_type/*zero*/(), singular ());
#else
            if (e1 () (n, n) == value_type/*zero*/())
                singular ().raise ();
#endif
            for (difference_type l = size2 - 1; l >= 0; -- l) {
                value_type t = e2 () (n, l) /= e1 () (n, n);
                if (t != value_type/*zero*/()) {
                    typename E1::const_reverse_iterator1 it1e1 (e1 ().find1 (1, n, n));
                    typename E1::const_reverse_iterator1 it1e1_rend (e1 ().find1 (1, 0, n));
                    while (it1e1 != it1e1_rend)
                        e2 () (it1e1.index1 (), l) -= *it1e1 * t, ++ it1e1;
                }
            }
        }
    }
    // Dispatcher
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        upper_tag) {
        typedef typename E1::storage_category dispatch_category;
        inplace_solve (e1, e2,
                       upper_tag (), dispatch_category ());
    }
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    void inplace_solve (const matrix_expression<E1> &e1, matrix_expression<E2> &e2,
                        unit_upper_tag) {
        typedef typename E1::storage_category dispatch_category;
        inplace_solve (triangular_adaptor<const E1, unit_upper> (e1 ()), e2,
                       unit_upper_tag (), dispatch_category ());
    }

    template<class E1, class E2, class C>
    BOOST_UBLAS_INLINE
    typename matrix_matrix_solve_traits<E1, E2>::result_type
    solve (const matrix_expression<E1> &e1,
           const matrix_expression<E2> &e2,
           C) {
        typename matrix_matrix_solve_traits<E1, E2>::result_type r (e2);
        inplace_solve (e1, r, C ());
        return r;
    }

}}}

#endif

/* triangular.hpp
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
*/