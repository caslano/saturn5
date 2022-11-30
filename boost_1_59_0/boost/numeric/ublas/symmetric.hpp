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

#ifndef _BOOST_UBLAS_SYMMETRIC_
#define _BOOST_UBLAS_SYMMETRIC_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/detail/temporary.hpp>

// Iterators based on ideas of Jeremy Siek
// Symmetric matrices are square. Thanks to Peter Schmitteckert for spotting this.

namespace boost { namespace numeric { namespace ublas {

    template<class M>
    bool is_symmetric (const M &m) {
        typedef typename M::size_type size_type;

        if (m.size1 () != m.size2 ())
            return false;
        size_type size = BOOST_UBLAS_SAME (m.size1 (), m.size2 ());
        for (size_type i = 0; i < size; ++ i) {
            for (size_type j = i; j < size; ++ j) {
                if (m (i, j) != m (j, i))
                    return false;
            }
        }
        return true;
    }

    // Array based symmetric matrix class
    template<class T, class TRI, class L, class A>
    class symmetric_matrix:
        public matrix_container<symmetric_matrix<T, TRI, L, A> > {

        typedef T *pointer;
        typedef TRI triangular_type;
        typedef L layout_type;
        typedef symmetric_matrix<T, TRI, L, A> self_type;
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
        symmetric_matrix ():
            matrix_container<self_type> (),
            size_ (0), data_ (0) {}
        BOOST_UBLAS_INLINE
        symmetric_matrix (size_type size):
            matrix_container<self_type> (),
            size_ (BOOST_UBLAS_SAME (size, size)), data_ (triangular_type::packed_size (layout_type (), size, size)) {
        }
        BOOST_UBLAS_INLINE
        symmetric_matrix (size_type size1, size_type size2):
            matrix_container<self_type> (),
            size_ (BOOST_UBLAS_SAME (size1, size2)), data_ (triangular_type::packed_size (layout_type (), size1, size2)) {
        }
        BOOST_UBLAS_INLINE
        symmetric_matrix (size_type size, const array_type &data):
            matrix_container<self_type> (),
            size_ (size), data_ (data) {}
        BOOST_UBLAS_INLINE
        symmetric_matrix (const symmetric_matrix &m):
            matrix_container<self_type> (),
            size_ (m.size_), data_ (m.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_matrix (const matrix_expression<AE> &ae):
            matrix_container<self_type> (),
            size_ (BOOST_UBLAS_SAME (ae ().size1 (), ae ().size2 ())),
            data_ (triangular_type::packed_size (layout_type (), size_, size_)) {
            matrix_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const {
            return size_;
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
        void resize (size_type size, bool preserve = true) {
            if (preserve) {
                self_type temporary (size, size);
                detail::matrix_resize_preserve<layout_type, triangular_type> (*this, temporary);
            }
            else {
                data ().resize (triangular_type::packed_size (layout_type (), size, size));
                size_ = size;
            }
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size1, size_type size2, bool preserve = true) {
            resize (BOOST_UBLAS_SAME (size1, size2), preserve);
        }
        BOOST_UBLAS_INLINE
        void resize_packed_preserve (size_type size) {
            size_ = BOOST_UBLAS_SAME (size, size);
            data ().resize (triangular_type::packed_size (layout_type (), size_, size_), value_type ());
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            BOOST_UBLAS_CHECK (j < size_, bad_index ());
            if (triangular_type::other (i, j))
                return data () [triangular_type::element (layout_type (), i, size_, j, size_)];
            else
                return data () [triangular_type::element (layout_type (), j, size_, i, size_)];
        }
        BOOST_UBLAS_INLINE
        reference at_element (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            BOOST_UBLAS_CHECK (j < size_, bad_index ());
            return data () [triangular_type::element (layout_type (), i, size_, j, size_)];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            BOOST_UBLAS_CHECK (j < size_, bad_index ());
            if (triangular_type::other (i, j))
                return data () [triangular_type::element (layout_type (), i, size_, j, size_)];
            else
                return data () [triangular_type::element (layout_type (), j, size_, i, size_)];
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
        symmetric_matrix &operator = (const symmetric_matrix &m) {
            size_ = m.size_;
            data () = m.data ();
            return *this;
        }
        BOOST_UBLAS_INLINE
        symmetric_matrix &assign_temporary (symmetric_matrix &m) {
            swap (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_matrix &operator = (const matrix_expression<AE> &ae) {
            self_type temporary (ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_matrix &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_matrix& operator += (const matrix_expression<AE> &ae) {
            self_type temporary (*this + ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_matrix &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_matrix& operator -= (const matrix_expression<AE> &ae) {
            self_type temporary (*this - ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_matrix &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        symmetric_matrix& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        symmetric_matrix& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (symmetric_matrix &m) {
            if (this != &m) {
                std::swap (size_, m.size_);
                data ().swap (m.data ());
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (symmetric_matrix &m1, symmetric_matrix &m2) {
            m1.swap (m2);
        }

        // Iterator types
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator1<self_type, packed_random_access_iterator_tag> iterator1;
        typedef indexed_iterator2<self_type, packed_random_access_iterator_tag> iterator2;
        typedef indexed_const_iterator1<self_type, dense_random_access_iterator_tag> const_iterator1;
        typedef indexed_const_iterator2<self_type, dense_random_access_iterator_tag> const_iterator2;
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
        const_iterator1 find1 (int /* rank */, size_type i, size_type j) const {
            return const_iterator1 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            if (rank == 1)
                i = triangular_type::mutable_restrict1 (i, j, size1(), size2());
            if (rank == 0)
                i = triangular_type::global_mutable_restrict1 (i, size1(), j, size2());
            return iterator1 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find2 (int /* rank */, size_type i, size_type j) const {
            return const_iterator2 (*this, i, j);
        }
        BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            if (rank == 1)
                j = triangular_type::mutable_restrict2 (i, j, size1(), size2());
            if (rank == 0)
                j = triangular_type::global_mutable_restrict2 (i, size1(), j, size2());
            return iterator2 (*this, i, j);
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator1:
            public container_const_reference<symmetric_matrix>,
            public random_access_iterator_base<dense_random_access_iterator_tag,
                                               const_iterator1, value_type> {
        public:
            typedef typename symmetric_matrix::value_type value_type;
            typedef typename symmetric_matrix::difference_type difference_type;
            typedef typename symmetric_matrix::const_reference reference;
            typedef const typename symmetric_matrix::pointer pointer;

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
            return find1 (0, size_, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 cend1 () const {
            return end1 ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator1:
            public container_reference<symmetric_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               iterator1, value_type> {
        public:
            typedef typename symmetric_matrix::value_type value_type;
            typedef typename symmetric_matrix::difference_type difference_type;
            typedef typename symmetric_matrix::reference reference;
            typedef typename symmetric_matrix::pointer pointer;
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
            return find1 (0, size_, 0);
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator2:
            public container_const_reference<symmetric_matrix>,
            public random_access_iterator_base<dense_random_access_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef typename symmetric_matrix::value_type value_type;
            typedef typename symmetric_matrix::difference_type difference_type;
            typedef typename symmetric_matrix::const_reference reference;
            typedef const typename symmetric_matrix::pointer pointer;

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
            return find2 (0, 0, size_);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 cend2 () const {
            return end2 ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator2:
            public container_reference<symmetric_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               iterator2, value_type> {
        public:
            typedef typename symmetric_matrix::value_type value_type;
            typedef typename symmetric_matrix::difference_type difference_type;
            typedef typename symmetric_matrix::reference reference;
            typedef typename symmetric_matrix::pointer pointer;

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
            return find2 (0, 0, size_);
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
        size_type size_;
        array_type data_;
    };


    // Symmetric matrix adaptor class
    template<class M, class TRI>
    class symmetric_adaptor:
        public matrix_expression<symmetric_adaptor<M, TRI> > {

        typedef symmetric_adaptor<M, TRI> self_type;
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
        symmetric_adaptor (matrix_type &data):
            matrix_expression<self_type> (),
            data_ (data) {
            BOOST_UBLAS_CHECK (data_.size1 () == data_.size2 (), bad_size ());
        }
        BOOST_UBLAS_INLINE
        symmetric_adaptor (const symmetric_adaptor &m):
            matrix_expression<self_type> (),
            data_ (m.data_) {
            BOOST_UBLAS_CHECK (data_.size1 () == data_.size2 (), bad_size ());
        }

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
            else
                return data () (j, i);
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
            if (triangular_type::other (i, j))
                return data () (i, j);
            else
                return data () (j, i);
        }
#else
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) const {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
            if (triangular_type::other (i, j))
                return data () (i, j);
            else
                return data () (j, i);
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        symmetric_adaptor &operator = (const symmetric_adaptor &m) {
            matrix_assign<scalar_assign, triangular_type> (*this, m);
            return *this;
        }
        BOOST_UBLAS_INLINE
        symmetric_adaptor &assign_temporary (symmetric_adaptor &m) {
            *this = m;
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_adaptor &operator = (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign, triangular_type> (*this, matrix<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_adaptor &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign, triangular_type> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_adaptor& operator += (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign, triangular_type> (*this, matrix<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_adaptor &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign, triangular_type> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_adaptor& operator -= (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign, triangular_type> (*this, matrix<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        symmetric_adaptor &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign, triangular_type> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        symmetric_adaptor& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        symmetric_adaptor& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const symmetric_adaptor &sa) const {
            return (*this).data ().same_closure (sa.data ());
       }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (symmetric_adaptor &m) {
            if (this != &m)
                matrix_swap<scalar_swap, triangular_type> (*this, m);
        }
        BOOST_UBLAS_INLINE
        friend void swap (symmetric_adaptor &m1, symmetric_adaptor &m2) {
            m1.swap (m2);
        }

        // Iterator types
    private:
        // Use matrix iterator
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
        typedef indexed_const_iterator1<self_type, dense_random_access_iterator_tag> const_iterator1;
        typedef indexed_const_iterator2<self_type, dense_random_access_iterator_tag> const_iterator2;
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
            if (triangular_type::other (i, j)) {
                if (triangular_type::other (size1 (), j)) {
                    return const_iterator1 (*this, 0, 0,
                                            data ().find1 (rank, i, j), data ().find1 (rank, size1 (), j),
                                            data ().find2 (rank, size2 (), size1 ()), data ().find2 (rank, size2 (), size1 ()));
                } else {
                    return const_iterator1 (*this, 0, 1,
                                            data ().find1 (rank, i, j), data ().find1 (rank, j, j),
                                            data ().find2 (rank, j, j), data ().find2 (rank, j, size1 ()));
                }
            } else {
                if (triangular_type::other (size1 (), j)) {
                    return const_iterator1 (*this, 1, 0,
                                            data ().find1 (rank, j, j), data ().find1 (rank, size1 (), j),
                                            data ().find2 (rank, j, i), data ().find2 (rank, j, j));
                } else {
                    return const_iterator1 (*this, 1, 1,
                                            data ().find1 (rank, size1 (), size2 ()), data ().find1 (rank, size1 (), size2 ()),
                                            data ().find2 (rank, j, i), data ().find2 (rank, j, size1 ()));
                }
            }
        }
        BOOST_UBLAS_INLINE
        iterator1 find1 (int rank, size_type i, size_type j) {
            if (rank == 1)
                i = triangular_type::mutable_restrict1 (i, j, size1(), size2());
            return iterator1 (*this, data ().find1 (rank, i, j));
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find2 (int rank, size_type i, size_type j) const {
            if (triangular_type::other (i, j)) {
                if (triangular_type::other (i, size2 ())) {
                    return const_iterator2 (*this, 1, 1,
                                            data ().find1 (rank, size2 (), size1 ()), data ().find1 (rank, size2 (), size1 ()),
                                            data ().find2 (rank, i, j), data ().find2 (rank, i, size2 ()));
                } else {
                    return const_iterator2 (*this, 1, 0,
                                            data ().find1 (rank, i, i), data ().find1 (rank, size2 (), i),
                                            data ().find2 (rank, i, j), data ().find2 (rank, i, i));
                }
            } else {
                if (triangular_type::other (i, size2 ())) {
                    return const_iterator2 (*this, 0, 1,
                                            data ().find1 (rank, j, i), data ().find1 (rank, i, i),
                                            data ().find2 (rank, i, i), data ().find2 (rank, i, size2 ()));
                } else {
                    return const_iterator2 (*this, 0, 0,
                                            data ().find1 (rank, j, i), data ().find1 (rank, size2 (), i),
                                            data ().find2 (rank, size1 (), size2 ()), data ().find2 (rank, size2 (), size2 ()));
                }
            }
        }
        BOOST_UBLAS_INLINE
        iterator2 find2 (int rank, size_type i, size_type j) {
            if (rank == 1)
                j = triangular_type::mutable_restrict2 (i, j, size1(), size2());
            return iterator2 (*this, data ().find2 (rank, i, j));
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator1:
            public container_const_reference<symmetric_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
                                                   typename const_subiterator1_type::iterator_category, dense_random_access_iterator_tag>::iterator_category,
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
                container_const_reference<self_type> (),
                begin_ (-1), end_ (-1), current_ (-1),
                it1_begin_ (), it1_end_ (), it1_ (),
                it2_begin_ (), it2_end_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const self_type &m, int begin, int end,
                             const const_subiterator1_type &it1_begin, const const_subiterator1_type &it1_end,
                             const const_subiterator2_type &it2_begin, const const_subiterator2_type &it2_end):
                container_const_reference<self_type> (m),
                begin_ (begin), end_ (end), current_ (begin),
                it1_begin_ (it1_begin), it1_end_ (it1_end), it1_ (it1_begin_),
                it2_begin_ (it2_begin), it2_end_ (it2_end), it2_ (it2_begin_) {
                if (current_ == 0 && it1_ == it1_end_)
                    current_ = 1;
                if (current_ == 1 && it2_ == it2_end_)
                    current_ = 0;
                if ((current_ == 0 && it1_ == it1_end_) ||
                    (current_ == 1 && it2_ == it2_end_))
                    current_ = end_;
                BOOST_UBLAS_CHECK (current_ == end_ ||
                                   (current_ == 0 && it1_ != it1_end_) ||
                                   (current_ == 1 && it2_ != it2_end_), internal_logic ());
            }
            // FIXME cannot compile
            //  iterator1 does not have these members!
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<self_type> (it ()),
                begin_ (it.begin_), end_ (it.end_), current_ (it.current_),
                it1_begin_ (it.it1_begin_), it1_end_ (it.it1_end_), it1_ (it.it1_),
                it2_begin_ (it.it2_begin_), it2_end_ (it.it2_end_), it2_ (it.it2_) {
                BOOST_UBLAS_CHECK (current_ == end_ ||
                                   (current_ == 0 && it1_ != it1_end_) ||
                                   (current_ == 1 && it2_ != it2_end_), internal_logic ());
            }

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    ++ it1_;
                    if (it1_ == it1_end_ && end_ == 1) {
                        it2_ = it2_begin_;
                        current_ = 1;
                    }
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    ++ it2_;
                    if (it2_ == it2_end_ && end_ == 0) {
                        it1_ = it1_begin_;
                        current_ = 0;
                    }
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    if (it1_ == it1_begin_ && begin_ == 1) {
                        it2_ = it2_end_;
                        BOOST_UBLAS_CHECK (it2_ != it2_begin_, internal_logic ());
                        -- it2_;
                        current_ = 1;
                    } else {
                        -- it1_;
                    }
                } else /* if (current_ == 1) */ {
                    if (it2_ == it2_begin_ && begin_ == 0) {
                        it1_ = it1_end_;
                        BOOST_UBLAS_CHECK (it1_ != it1_begin_, internal_logic ());
                        -- it1_;
                        current_ = 0;
                    } else {
                        -- it2_;
                    }
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator += (difference_type n) {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    size_type d = (std::min) (n, it1_end_ - it1_);
                    it1_ += d;
                    n -= d;
                    if (n > 0 || (end_ == 1 && it1_ == it1_end_)) {
                        BOOST_UBLAS_CHECK (end_ == 1, external_logic ());
                        d = (std::min) (n, it2_end_ - it2_begin_);
                        it2_ = it2_begin_ + d;
                        n -= d;
                        current_ = 1;
                    }
                } else /* if (current_ == 1) */ {
                    size_type d = (std::min) (n, it2_end_ - it2_);
                    it2_ += d;
                    n -= d;
                    if (n > 0 || (end_ == 0 && it2_ == it2_end_)) {
                        BOOST_UBLAS_CHECK (end_ == 0, external_logic ());
                        d = (std::min) (n, it1_end_ - it1_begin_);
                        it1_ = it1_begin_ + d;
                        n -= d;
                        current_ = 0;
                    }
                }
                BOOST_UBLAS_CHECK (n == 0, external_logic ());
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -= (difference_type n) {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    size_type d = (std::min) (n, it1_ - it1_begin_);
                    it1_ -= d;
                    n -= d;
                    if (n > 0) {
                        BOOST_UBLAS_CHECK (end_ == 1, external_logic ());
                        d = (std::min) (n, it2_end_ - it2_begin_);
                        it2_ = it2_end_ - d;
                        n -= d;
                        current_ = 1;
                    }
                } else /* if (current_ == 1) */ {
                    size_type d = (std::min) (n, it2_ - it2_begin_);
                    it2_ -= d;
                    n -= d;
                    if (n > 0) {
                        BOOST_UBLAS_CHECK (end_ == 0, external_logic ());
                        d = (std::min) (n, it1_end_ - it1_begin_);
                        it1_ = it1_end_ - d;
                        n -= d;
                        current_ = 0;
                    }
                }
                BOOST_UBLAS_CHECK (n == 0, external_logic ());
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                BOOST_UBLAS_CHECK (it.current_ == 0 || it.current_ == 1, internal_logic ());
                BOOST_UBLAS_CHECK (/* begin_ == it.begin_ && */ end_ == it.end_, internal_logic ());
                if (current_ == 0 && it.current_ == 0) {
                    return it1_ - it.it1_;
                } else if (current_ == 0 && it.current_ == 1) {
                    if (end_ == 1 && it.end_ == 1) {
                        return (it1_ - it.it1_end_) + (it.it2_begin_ - it.it2_);
                    } else /* if (end_ == 0 && it.end_ == 0) */ {
                        return (it1_ - it.it1_begin_) + (it.it2_end_ - it.it2_);
                    }

                } else if (current_ == 1 && it.current_ == 0) {
                    if (end_ == 1 && it.end_ == 1) {
                        return (it2_ - it.it2_begin_) + (it.it1_end_ - it.it1_);
                    } else /* if (end_ == 0 && it.end_ == 0) */ {
                        return (it2_ - it.it2_end_) + (it.it1_begin_ - it.it1_);
                    }
                }
                /* current_ == 1 && it.current_ == 1 */ {
                    return it2_ - it.it2_;
                }
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    return *it1_;
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    return *it2_;
                }
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
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    return it1_.index1 ();
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    return it2_.index2 ();
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    return it1_.index2 ();
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    return it2_.index1 ();
                }
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<self_type>::assign (&it ());
                begin_ = it.begin_;
                end_ = it.end_;
                current_ = it.current_;
                it1_begin_ = it.it1_begin_;
                it1_end_ = it.it1_end_;
                it1_ = it.it1_;
                it2_begin_ = it.it2_begin_;
                it2_end_ = it.it2_end_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                BOOST_UBLAS_CHECK (it.current_ == 0 || it.current_ == 1, internal_logic ());
                BOOST_UBLAS_CHECK (/* begin_ == it.begin_ && */ end_ == it.end_, internal_logic ());
                return (current_ == 0 && it.current_ == 0 && it1_ == it.it1_) ||
                       (current_ == 1 && it.current_ == 1 && it2_ == it.it2_);
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it - *this > 0;
            }

        private:
            int begin_;
            int end_;
            int current_;
            const_subiterator1_type it1_begin_;
            const_subiterator1_type it1_end_;
            const_subiterator1_type it1_;
            const_subiterator2_type it2_begin_;
            const_subiterator2_type it2_end_;
            const_subiterator2_type it2_;
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
            public container_reference<symmetric_adaptor>,
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
                return *it1_;
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
            public container_const_reference<symmetric_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
                                                   typename const_subiterator2_type::iterator_category, dense_random_access_iterator_tag>::iterator_category,
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
                container_const_reference<self_type> (),
                begin_ (-1), end_ (-1), current_ (-1),
                it1_begin_ (), it1_end_ (), it1_ (),
                it2_begin_ (), it2_end_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const self_type &m, int begin, int end,
                             const const_subiterator1_type &it1_begin, const const_subiterator1_type &it1_end,
                             const const_subiterator2_type &it2_begin, const const_subiterator2_type &it2_end):
                container_const_reference<self_type> (m),
                begin_ (begin), end_ (end), current_ (begin),
                it1_begin_ (it1_begin), it1_end_ (it1_end), it1_ (it1_begin_),
                it2_begin_ (it2_begin), it2_end_ (it2_end), it2_ (it2_begin_) {
                if (current_ == 0 && it1_ == it1_end_)
                    current_ = 1;
                if (current_ == 1 && it2_ == it2_end_)
                    current_ = 0;
                if ((current_ == 0 && it1_ == it1_end_) ||
                    (current_ == 1 && it2_ == it2_end_))
                    current_ = end_;
                BOOST_UBLAS_CHECK (current_ == end_ ||
                                   (current_ == 0 && it1_ != it1_end_) ||
                                   (current_ == 1 && it2_ != it2_end_), internal_logic ());
            }
            // FIXME cannot compiler
            //  iterator2 does not have these members!
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<self_type> (it ()),
                begin_ (it.begin_), end_ (it.end_), current_ (it.current_),
                it1_begin_ (it.it1_begin_), it1_end_ (it.it1_end_), it1_ (it.it1_),
                it2_begin_ (it.it2_begin_), it2_end_ (it.it2_end_), it2_ (it.it2_) {
                BOOST_UBLAS_CHECK (current_ == end_ ||
                                   (current_ == 0 && it1_ != it1_end_) ||
                                   (current_ == 1 && it2_ != it2_end_), internal_logic ());
            }

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    ++ it1_;
                    if (it1_ == it1_end_ && end_ == 1) {
                        it2_ = it2_begin_;
                        current_ = 1;
                    }
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    ++ it2_;
                    if (it2_ == it2_end_ && end_ == 0) {
                        it1_ = it1_begin_;
                        current_ = 0;
                    }
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    if (it1_ == it1_begin_ && begin_ == 1) {
                        it2_ = it2_end_;
                        BOOST_UBLAS_CHECK (it2_ != it2_begin_, internal_logic ());
                        -- it2_;
                        current_ = 1;
                    } else {
                        -- it1_;
                    }
                } else /* if (current_ == 1) */ {
                    if (it2_ == it2_begin_ && begin_ == 0) {
                        it1_ = it1_end_;
                        BOOST_UBLAS_CHECK (it1_ != it1_begin_, internal_logic ());
                        -- it1_;
                        current_ = 0;
                    } else {
                        -- it2_;
                    }
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator += (difference_type n) {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    size_type d = (std::min) (n, it1_end_ - it1_);
                    it1_ += d;
                    n -= d;
                    if (n > 0 || (end_ == 1 && it1_ == it1_end_)) {
                        BOOST_UBLAS_CHECK (end_ == 1, external_logic ());
                        d = (std::min) (n, it2_end_ - it2_begin_);
                        it2_ = it2_begin_ + d;
                        n -= d;
                        current_ = 1;
                    }
                } else /* if (current_ == 1) */ {
                    size_type d = (std::min) (n, it2_end_ - it2_);
                    it2_ += d;
                    n -= d;
                    if (n > 0 || (end_ == 0 && it2_ == it2_end_)) {
                        BOOST_UBLAS_CHECK (end_ == 0, external_logic ());
                        d = (std::min) (n, it1_end_ - it1_begin_);
                        it1_ = it1_begin_ + d;
                        n -= d;
                        current_ = 0;
                    }
                }
                BOOST_UBLAS_CHECK (n == 0, external_logic ());
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -= (difference_type n) {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    size_type d = (std::min) (n, it1_ - it1_begin_);
                    it1_ -= d;
                    n -= d;
                    if (n > 0) {
                        BOOST_UBLAS_CHECK (end_ == 1, external_logic ());
                        d = (std::min) (n, it2_end_ - it2_begin_);
                        it2_ = it2_end_ - d;
                        n -= d;
                        current_ = 1;
                    }
                } else /* if (current_ == 1) */ {
                    size_type d = (std::min) (n, it2_ - it2_begin_);
                    it2_ -= d;
                    n -= d;
                    if (n > 0) {
                        BOOST_UBLAS_CHECK (end_ == 0, external_logic ());
                        d = (std::min) (n, it1_end_ - it1_begin_);
                        it1_ = it1_end_ - d;
                        n -= d;
                        current_ = 0;
                    }
                }
                BOOST_UBLAS_CHECK (n == 0, external_logic ());
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                BOOST_UBLAS_CHECK (it.current_ == 0 || it.current_ == 1, internal_logic ());
                BOOST_UBLAS_CHECK (/* begin_ == it.begin_ && */ end_ == it.end_, internal_logic ());
                if (current_ == 0 && it.current_ == 0) {
                    return it1_ - it.it1_;
                } else if (current_ == 0 && it.current_ == 1) {
                    if (end_ == 1 && it.end_ == 1) {
                        return (it1_ - it.it1_end_) + (it.it2_begin_ - it.it2_);
                    } else /* if (end_ == 0 && it.end_ == 0) */ {
                        return (it1_ - it.it1_begin_) + (it.it2_end_ - it.it2_);
                    }

                } else if (current_ == 1 && it.current_ == 0) {
                    if (end_ == 1 && it.end_ == 1) {
                        return (it2_ - it.it2_begin_) + (it.it1_end_ - it.it1_);
                    } else /* if (end_ == 0 && it.end_ == 0) */ {
                        return (it2_ - it.it2_end_) + (it.it1_begin_ - it.it1_);
                    }
                }
                /* current_ == 1 && it.current_ == 1 */ {
                    return it2_ - it.it2_;
                }
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    return *it1_;
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    return *it2_;
                }
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
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    return it1_.index2 ();
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    return it2_.index1 ();
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    return it1_.index1 ();
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    return it2_.index2 ();
                }
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<self_type>::assign (&it ());
                begin_ = it.begin_;
                end_ = it.end_;
                current_ = it.current_;
                it1_begin_ = it.it1_begin_;
                it1_end_ = it.it1_end_;
                it1_ = it.it1_;
                it2_begin_ = it.it2_begin_;
                it2_end_ = it.it2_end_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                BOOST_UBLAS_CHECK (it.current_ == 0 || it.current_ == 1, internal_logic ());
                BOOST_UBLAS_CHECK (/* begin_ == it.begin_ && */ end_ == it.end_, internal_logic ());
                return (current_ == 0 && it.current_ == 0 && it1_ == it.it1_) ||
                       (current_ == 1 && it.current_ == 1 && it2_ == it.it2_);
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it - *this > 0;
            }

        private:
            int begin_;
            int end_;
            int current_;
            const_subiterator1_type it1_begin_;
            const_subiterator1_type it1_end_;
            const_subiterator1_type it1_;
            const_subiterator2_type it2_begin_;
            const_subiterator2_type it2_end_;
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
            public container_reference<symmetric_adaptor>,
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
                return *it2_;
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
    };

    // Specialization for temporary_traits
    template <class M, class TRI>
    struct vector_temporary_traits< symmetric_adaptor<M, TRI> >
    : vector_temporary_traits< M > {} ;
    template <class M, class TRI>
    struct vector_temporary_traits< const symmetric_adaptor<M, TRI> >
    : vector_temporary_traits< M > {} ;

    template <class M, class TRI>
    struct matrix_temporary_traits< symmetric_adaptor<M, TRI> >
    : matrix_temporary_traits< M > {} ;
    template <class M, class TRI>
    struct matrix_temporary_traits< const symmetric_adaptor<M, TRI> >
    : matrix_temporary_traits< M > {} ;

}}}

#endif

/* symmetric.hpp
+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
*/