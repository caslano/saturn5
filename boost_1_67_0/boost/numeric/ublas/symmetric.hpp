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
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
*/