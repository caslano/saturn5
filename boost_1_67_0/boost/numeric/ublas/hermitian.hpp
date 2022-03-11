//
//  Copyright (c) 2000-2010
//  Joerg Walter, Mathias Koch, David Bellot
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef BOOST_UBLAS_HERMITIAN_H
#define BOOST_UBLAS_HERMITIAN_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>  // for resize_preserve
#include <boost/numeric/ublas/detail/temporary.hpp>

// Iterators based on ideas of Jeremy Siek
// Hermitian matrices are square. Thanks to Peter Schmitteckert for spotting this.

namespace boost { namespace numeric { namespace ublas {

    template<class M>
    bool is_hermitian (const M &m) {
        typedef typename M::size_type size_type;

        if (m.size1 () != m.size2 ())
            return false;
        size_type size = BOOST_UBLAS_SAME (m.size1 (), m.size2 ());
        for (size_type i = 0; i < size; ++ i) {
            for (size_type j = i; j < size; ++ j) {
                if (m (i, j) != conj (m (j, i)))
                    return false;
            }
        }
        return true;
    }

#ifdef BOOST_UBLAS_STRICT_HERMITIAN

    template<class M>
    class hermitian_matrix_element:
       public container_reference<M> {
    public:
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef value_type *pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        hermitian_matrix_element (matrix_type &m, size_type i, size_type j, value_type d):
            container_reference<matrix_type> (m), i_ (i), j_ (j), d_ (d), dirty_ (false) {}
        BOOST_UBLAS_INLINE
        ~hermitian_matrix_element () {
            if (dirty_)
                (*this) ().insert_element (i_, j_, d_);
        }

        // Assignment
        BOOST_UBLAS_INLINE
        hermitian_matrix_element &operator = (const hermitian_matrix_element &p) {
            // Overide the implict copy assignment
            d_ = p.d_;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        hermitian_matrix_element &operator = (const D &d) {
            d_ = d;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        hermitian_matrix_element &operator += (const D &d) {
            d_ += d;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        hermitian_matrix_element &operator -= (const D &d) {
            d_ -= d;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        hermitian_matrix_element &operator *= (const D &d) {
            d_ *= d;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        hermitian_matrix_element &operator /= (const D &d) {
            d_ /= d;
            dirty_ = true;
            return *this;
        }
        
        // Comparison
        template<class D>
        BOOST_UBLAS_INLINE
        bool operator == (const D &d) const {
            return d_ == d;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        bool operator != (const D &d) const {
            return d_ != d;
        }

        // Conversion
        BOOST_UBLAS_INLINE
        operator const_reference () const {
            return d_;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (hermitian_matrix_element p) {
            if (this != &p) {
                dirty_ = true;
                p.dirty_ = true;
                std::swap (d_, p.d_);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (hermitian_matrix_element p1, hermitian_matrix_element p2) {
            p1.swap (p2);
        }

    private:
        size_type i_;
        size_type j_;
        value_type d_;
        bool dirty_;
    };

    template<class M>
    struct type_traits<hermitian_matrix_element<M> > {
        typedef typename M::value_type element_type;
        typedef type_traits<hermitian_matrix_element<M> > self_type;
        typedef typename type_traits<element_type>::value_type value_type;
        typedef typename type_traits<element_type>::const_reference const_reference;
        typedef hermitian_matrix_element<M> reference;
        typedef typename type_traits<element_type>::real_type real_type;
        typedef typename type_traits<element_type>::precision_type precision_type;

        static const unsigned plus_complexity = type_traits<element_type>::plus_complexity;
        static const unsigned multiplies_complexity = type_traits<element_type>::multiplies_complexity;

        static
        BOOST_UBLAS_INLINE
        real_type real (const_reference t) {
            return type_traits<element_type>::real (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type imag (const_reference t) {
            return type_traits<element_type>::imag (t);
        }
        static
        BOOST_UBLAS_INLINE
        value_type conj (const_reference t) {
            return type_traits<element_type>::conj (t);
        }

        static
        BOOST_UBLAS_INLINE
        real_type type_abs (const_reference t) {
            return type_traits<element_type>::type_abs (t);
        }
        static
        BOOST_UBLAS_INLINE
        value_type type_sqrt (const_reference t) {
            return type_traits<element_type>::type_sqrt (t);
        }

        static
        BOOST_UBLAS_INLINE
        real_type norm_1 (const_reference t) {
            return type_traits<element_type>::norm_1 (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type norm_2 (const_reference t) {
            return type_traits<element_type>::norm_2 (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type norm_inf (const_reference t) {
            return type_traits<element_type>::norm_inf (t);
        }

        static
        BOOST_UBLAS_INLINE
        bool equals (const_reference t1, const_reference t2) {
            return type_traits<element_type>::equals (t1, t2);
        }
    };

    template<class M1, class T2>
    struct promote_traits<hermitian_matrix_element<M1>, T2> {
        typedef typename promote_traits<typename hermitian_matrix_element<M1>::value_type, T2>::promote_type promote_type;
    };
    template<class T1, class M2>
    struct promote_traits<T1, hermitian_matrix_element<M2> > {
        typedef typename promote_traits<T1, typename hermitian_matrix_element<M2>::value_type>::promote_type promote_type;
    };
    template<class M1, class M2>
    struct promote_traits<hermitian_matrix_element<M1>, hermitian_matrix_element<M2> > {
        typedef typename promote_traits<typename hermitian_matrix_element<M1>::value_type,
                                        typename hermitian_matrix_element<M2>::value_type>::promote_type promote_type;
    };

#endif
    /** \brief A hermitian matrix of values of type \c T
     *
     * For a \f$(n \times n)\f$-dimensional matrix and \f$ 0 \leq i < n, 0 \leq j < n\f$, every element 
     * \f$m_{i,j}\f$ is mapped to the \f$(i.n + j)\f$-th element of the container for row major orientation 
     * or the \f$(i + j.m)\f$-th element of the container for column major orientation. And 
     * \f$\forall i,j\f$, \f$m_{i,j} = \overline{m_{i,j}}\f$.
     *
     * Orientation and storage can also be specified, otherwise a row major and unbounded array are used. 
     * It is \b not required by the storage to initialize elements of the matrix. 
     * Moreover, only the given triangular matrix is stored and the storage of hermitian matrices is packed.
     *
     * See http://en.wikipedia.org/wiki/Hermitian_matrix for more details on hermitian matrices.
     *
     * \tparam T the type of object stored in the matrix (like double, float, complex, etc...)
     * \tparam TRI the type of triangular matrix is either \c lower or \c upper. Default is \c lower
     * \tparam L the storage organization. It is either \c row_major or \c column_major. Default is \c row_major
     * \tparam A the type of Storage array. Default is \unbounded_array.
     */
    template<class T, class TRI, class L, class A>
    class hermitian_matrix:
        public matrix_container<hermitian_matrix<T, TRI, L, A> > {

        typedef T &true_reference;
        typedef T *pointer;
        typedef TRI triangular_type;
        typedef L layout_type;
        typedef hermitian_matrix<T, TRI, L, A> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_container<self_type>::operator ();
#endif
        typedef typename A::size_type size_type;
        typedef typename A::difference_type difference_type;
        typedef T value_type;
        // FIXME no better way to not return the address of a temporary?
        // typedef const T &const_reference;
        typedef const T const_reference;
#ifndef BOOST_UBLAS_STRICT_HERMITIAN
        typedef T &reference;
#else
        typedef hermitian_matrix_element<self_type> reference;
#endif
        typedef A array_type;

        typedef const matrix_reference<const self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;
        typedef vector<T, A> vector_temporary_type;
        typedef matrix<T, L, A> matrix_temporary_type;  // general sub-matrix
        typedef packed_tag storage_category;
        typedef typename L::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        hermitian_matrix ():
            matrix_container<self_type> (),
            size_ (0), data_ (0) {}
        BOOST_UBLAS_INLINE
        hermitian_matrix (size_type size):
            matrix_container<self_type> (),
            size_ (BOOST_UBLAS_SAME (size, size)), data_ (triangular_type::packed_size (layout_type (), size, size)) {
        }
        BOOST_UBLAS_INLINE
        hermitian_matrix (size_type size1, size_type size2):
            matrix_container<self_type> (),
            size_ (BOOST_UBLAS_SAME (size1, size2)), data_ (triangular_type::packed_size (layout_type (), size1, size2)) {
        }
        BOOST_UBLAS_INLINE
        hermitian_matrix (size_type size, const array_type &data):
            matrix_container<self_type> (),
            size_ (size), data_ (data) {}
        BOOST_UBLAS_INLINE
        hermitian_matrix (const hermitian_matrix &m):
            matrix_container<self_type> (),
            size_ (m.size_), data_ (m.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_matrix (const matrix_expression<AE> &ae):
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
            // if (i == j)
            //    return type_traits<value_type>::real (data () [triangular_type::element (layout_type (), i, size_, i, size_)]);
            // else
            if (triangular_type::other (i, j))
                return data () [triangular_type::element (layout_type (), i, size_, j, size_)];
            else
                return type_traits<value_type>::conj (data () [triangular_type::element (layout_type (), j, size_, i, size_)]);
        }
        BOOST_UBLAS_INLINE
        true_reference at_element (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            BOOST_UBLAS_CHECK (j < size_, bad_index ());
            BOOST_UBLAS_CHECK (triangular_type::other (i, j), bad_index ());
            return data () [triangular_type::element (layout_type (), i, size_, j, size_)];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
#ifndef BOOST_UBLAS_STRICT_HERMITIAN
            if (!triangular_type::other (i, j)) {
                bad_index ().raise ();
                // NEVER reached
            }
            return at_element (i, j);
#else
        if (triangular_type::other (i, j))
            return reference (*this, i, j, data () [triangular_type::element (layout_type (), i, size_, j, size_)]);
        else
            return reference (*this, i, j, type_traits<value_type>::conj (data () [triangular_type::element (layout_type (), j, size_, i, size_)]));
#endif
        }

        // Element assignemnt
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, size_type j, const_reference t) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            BOOST_UBLAS_CHECK (j < size_, bad_index ());
            if (triangular_type::other (i, j)) {
                return (data () [triangular_type::element (layout_type (), i, size_, j, size_)] = t);
            } else {
                return (data () [triangular_type::element (layout_type (), j, size_, i, size_)] = type_traits<value_type>::conj (t));
            }
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            BOOST_UBLAS_CHECK (j < size_, bad_index ());
            data () [triangular_type::element (layout_type (), i, size_, j, size_)] = value_type/*zero*/();
        }

        // Zeroing
        BOOST_UBLAS_INLINE
        void clear () {
            std::fill (data ().begin (), data ().end (), value_type/*zero*/());
        }

        // Assignment
        BOOST_UBLAS_INLINE
        hermitian_matrix &operator = (const hermitian_matrix &m) {
            size_ = m.size_;
            data () = m.data ();
            return *this;
        }
        BOOST_UBLAS_INLINE
        hermitian_matrix &assign_temporary (hermitian_matrix &m) {
            swap (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_matrix &operator = (const matrix_expression<AE> &ae) {
            self_type temporary (ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_matrix &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_matrix& operator += (const matrix_expression<AE> &ae) {
            self_type temporary (*this + ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_matrix &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_matrix& operator -= (const matrix_expression<AE> &ae) {
            self_type temporary (*this - ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_matrix &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        hermitian_matrix& operator *= (const AT &at) {
            // Multiplication is only allowed for real scalars,
            // otherwise the resulting matrix isn't hermitian.
            // Thanks to Peter Schmitteckert for spotting this.
            BOOST_UBLAS_CHECK (type_traits<value_type>::imag (at) == 0, non_real ());
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        hermitian_matrix& operator /= (const AT &at) {
            // Multiplication is only allowed for real scalars,
            // otherwise the resulting matrix isn't hermitian.
            // Thanks to Peter Schmitteckert for spotting this.
            BOOST_UBLAS_CHECK (type_traits<value_type>::imag (at) == 0, non_real ());
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (hermitian_matrix &m) {
            if (this != &m) {
                std::swap (size_, m.size_);
                data ().swap (m.data ());
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (hermitian_matrix &m1, hermitian_matrix &m2) {
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
            public container_const_reference<hermitian_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               const_iterator1, value_type> {
        public:
            typedef typename hermitian_matrix::value_type value_type;
            typedef typename hermitian_matrix::difference_type difference_type;
            typedef typename hermitian_matrix::const_reference reference;
            typedef const typename hermitian_matrix::pointer pointer;

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
            public container_reference<hermitian_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               iterator1, value_type> {
        public:
            typedef typename hermitian_matrix::value_type value_type;
            typedef typename hermitian_matrix::difference_type difference_type;
            typedef typename hermitian_matrix::true_reference reference;
            typedef typename hermitian_matrix::pointer pointer;

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
            return find1 (0, size_, 0);
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator2:
            public container_const_reference<hermitian_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef typename hermitian_matrix::value_type value_type;
            typedef typename hermitian_matrix::difference_type difference_type;
            typedef typename hermitian_matrix::const_reference reference;
            typedef const typename hermitian_matrix::pointer pointer;

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
            const_iterator1 crbegin () const {
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
            const_iterator1 crend () const {
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
            public container_reference<hermitian_matrix>,
            public random_access_iterator_base<packed_random_access_iterator_tag,
                                               iterator2, value_type> {
        public:
            typedef typename hermitian_matrix::value_type value_type;
            typedef typename hermitian_matrix::difference_type difference_type;
            typedef typename hermitian_matrix::true_reference reference;
            typedef typename hermitian_matrix::pointer pointer;

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
            return rbegin2();
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

    /** \brief A Hermitian matrix adaptator: convert a any matrix into a Hermitian matrix expression
     *
     * For a \f$(m\times n)\f$-dimensional matrix, the \c hermitian_adaptor will provide a hermitian matrix.
     * Storage and location are based on those of the underlying matrix. This is important because
     * a \c hermitian_adaptor does not copy the matrix data to a new place. Therefore, modifying values
     * in a \c hermitian_adaptor matrix will also modify the underlying matrix too.
     *
     * \tparam M the type of matrix used to generate a hermitian matrix
     */
    template<class M, class TRI>
    class hermitian_adaptor:
        public matrix_expression<hermitian_adaptor<M, TRI> > {

        typedef hermitian_adaptor<M, TRI> self_type;
        typedef typename M::value_type &true_reference;
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
        typedef typename M::value_type const_reference;
#ifndef BOOST_UBLAS_STRICT_HERMITIAN
        typedef typename boost::mpl::if_<boost::is_const<M>,
                                          typename M::value_type,
                                          typename M::reference>::type reference;
#else
        typedef typename boost::mpl::if_<boost::is_const<M>,
                                          typename M::value_type,
                                          hermitian_matrix_element<self_type> >::type reference;
#endif
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
        hermitian_adaptor (matrix_type &data):
            matrix_expression<self_type> (),
            data_ (data) {
            BOOST_UBLAS_CHECK (data_.size1 () == data_.size2 (), bad_size ());
        }
        BOOST_UBLAS_INLINE
        hermitian_adaptor (const hermitian_adaptor &m):
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
            // if (i == j)
            //     return type_traits<value_type>::real (data () (i, i));
            // else
            if (triangular_type::other (i, j))
                return data () (i, j);
            else
                return type_traits<value_type>::conj (data () (j, i));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
#ifndef BOOST_UBLAS_STRICT_HERMITIAN
            if (triangular_type::other (i, j))
                return data () (i, j);
            else {
                external_logic ().raise ();
                return conj_ = type_traits<value_type>::conj (data () (j, i));
            }
#else
            if (triangular_type::other (i, j))
                return reference (*this, i, j, data () (i, j));
            else
                return reference (*this, i, j, type_traits<value_type>::conj (data () (j, i)));
#endif
        }
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, size_type j, value_type t) {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
            // if (i == j)
            //     data () (i, i) = type_traits<value_type>::real (t);
            // else
            if (triangular_type::other (i, j))
                return data () (i, j) = t;
            else
                return data () (j, i) = type_traits<value_type>::conj (t);
        }
#else
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
#ifndef BOOST_UBLAS_STRICT_HERMITIAN
            if (triangular_type::other (i, j))
                return data () (i, j);
            else {
                external_logic ().raise ();
                return conj_ = type_traits<value_type>::conj (data () (j, i));
            }
#else
            if (triangular_type::other (i, j))
                return reference (*this, i, j, data () (i, j));
            else
                return reference (*this, i, j, type_traits<value_type>::conj (data () (j, i)));
#endif
        }
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, size_type j, value_type t) {
            BOOST_UBLAS_CHECK (i < size1 (), bad_index ());
            BOOST_UBLAS_CHECK (j < size2 (), bad_index ());
            // if (i == j)
            //     data () (i, i) = type_traits<value_type>::real (t);
            // else
            if (triangular_type::other (i, j))
                return data () (i, j) = t;
            else
                return data () (j, i) = type_traits<value_type>::conj (t);
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        hermitian_adaptor &operator = (const hermitian_adaptor &m) {
            matrix_assign<scalar_assign, triangular_type> (*this, m);
            return *this;
        }
        BOOST_UBLAS_INLINE
        hermitian_adaptor &assign_temporary (hermitian_adaptor &m) {
            *this = m;
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_adaptor &operator = (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign, triangular_type> (*this, matrix<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_adaptor &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign, triangular_type> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_adaptor& operator += (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign, triangular_type> (*this, matrix<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_adaptor &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign, triangular_type> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_adaptor& operator -= (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign, triangular_type> (*this, matrix<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        hermitian_adaptor &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign, triangular_type> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        hermitian_adaptor& operator *= (const AT &at) {
            // Multiplication is only allowed for real scalars,
            // otherwise the resulting matrix isn't hermitian.
            // Thanks to Peter Schmitteckert for spotting this.
            BOOST_UBLAS_CHECK (type_traits<value_type>::imag (at) == 0, non_real ());
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        hermitian_adaptor& operator /= (const AT &at) {
            // Multiplication is only allowed for real scalars,
            // otherwise the resulting matrix isn't hermitian.
            // Thanks to Peter Schmitteckert for spotting this.
            BOOST_UBLAS_CHECK (type_traits<value_type>::imag (at) == 0, non_real ());
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const hermitian_adaptor &ha) const {
            return (*this).data ().same_closure (ha.data ());
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (hermitian_adaptor &m) {
            if (this != &m)
                matrix_swap<scalar_swap, triangular_type> (*this, m);
        }
        BOOST_UBLAS_INLINE
        friend void swap (hermitian_adaptor &m1, hermitian_adaptor &m2) {
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
            if (rank == 0)
                i = triangular_type::global_mutable_restrict1 (i, size1(), j, size2());
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
            if (rank == 0)
                j = triangular_type::global_mutable_restrict2 (i, size1(), j, size2());
            return iterator2 (*this, data ().find2 (rank, i, j));
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator1:
            public container_const_reference<hermitian_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
                                                   typename const_subiterator1_type::iterator_category, dense_random_access_iterator_tag>::iterator_category,
                                               const_iterator1, value_type> {
        public:
            typedef typename const_subiterator1_type::value_type value_type;
            typedef typename const_subiterator1_type::difference_type difference_type;
            // FIXME no better way to not return the address of a temporary?
            // typedef typename const_subiterator1_type::reference reference;
            typedef typename const_subiterator1_type::value_type reference;
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
                } else /* if (current_ == 1 && it.current_ == 1) */ {
                    return it2_ - it.it2_;
                }
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    if (triangular_type::other (index1 (), index2 ()))
                        return *it1_;
                    else
                        return type_traits<value_type>::conj (*it1_);
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    if (triangular_type::other (index1 (), index2 ()))
                        return *it2_;
                    else
                        return type_traits<value_type>::conj (*it2_);
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
            public container_reference<hermitian_adaptor>,
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
            public container_const_reference<hermitian_adaptor>,
            public random_access_iterator_base<typename iterator_restrict_traits<
            typename const_subiterator2_type::iterator_category, dense_random_access_iterator_tag>::iterator_category,
                                               const_iterator2, value_type> {
        public:
            typedef typename const_subiterator2_type::value_type value_type;
            typedef typename const_subiterator2_type::difference_type difference_type;
            // FIXME no better way to not return the address of a temporary?
            // typedef typename const_subiterator2_type::reference reference;
            typedef typename const_subiterator2_type::value_type reference;
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
                } else /* if (current_ == 1 && it.current_ == 1) */ {
                    return it2_ - it.it2_;
                }
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (current_ == 0 || current_ == 1, internal_logic ());
                if (current_ == 0) {
                    BOOST_UBLAS_CHECK (it1_ != it1_end_, internal_logic ());
                    if (triangular_type::other (index1 (), index2 ()))
                        return *it1_;
                    else
                        return type_traits<value_type>::conj (*it1_);
                } else /* if (current_ == 1) */ {
                    BOOST_UBLAS_CHECK (it2_ != it2_end_, internal_logic ());
                    if (triangular_type::other (index1 (), index2 ()))
                        return *it2_;
                    else
                        return type_traits<value_type>::conj (*it2_);
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
                return end ();
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
            public container_reference<hermitian_adaptor>,
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
            return rbegin1();
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
        static value_type conj_;
    };

    template<class M, class TRI>
    typename hermitian_adaptor<M, TRI>::value_type hermitian_adaptor<M, TRI>::conj_;

    // Specialization for temporary_traits
    template <class M, class TRI>
    struct vector_temporary_traits< hermitian_adaptor<M, TRI> >
    : vector_temporary_traits< M > {} ;
    template <class M, class TRI>
    struct vector_temporary_traits< const hermitian_adaptor<M, TRI> >
    : vector_temporary_traits< M > {} ;

    template <class M, class TRI>
    struct matrix_temporary_traits< hermitian_adaptor<M, TRI> >
    : matrix_temporary_traits< M > {} ;
    template <class M, class TRI>
    struct matrix_temporary_traits< const hermitian_adaptor<M, TRI> >
    : matrix_temporary_traits< M > {} ;

}}}

#endif

/* hermitian.hpp
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
*/