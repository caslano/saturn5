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

#ifndef _BOOST_UBLAS_VECTOR_SPARSE_
#define _BOOST_UBLAS_VECTOR_SPARSE_

#include <boost/config.hpp>

// In debug mode, MSCV enables iterator debugging, which additional checks are
// executed for consistency. So, when two iterators are compared, it is tested
// that they point to elements of the same container. If the check fails, then
// the program is aborted.
//
// When matrices MVOV are traversed by column and then by row, the previous
// check fails.
//
// MVOV::iterator2 iter2 = mvov.begin2();
// for (; iter2 != mvov.end() ; iter2++) {
//    MVOV::iterator1 iter1 = iter2.begin();
//    .....
// }
//
// These additional checks in iterators are disabled in this file, but their
// status are restored at the end of file.
// https://msdn.microsoft.com/en-us/library/hh697468.aspx
#ifdef BOOST_MSVC
#define _BACKUP_ITERATOR_DEBUG_LEVEL _ITERATOR_DEBUG_LEVEL
#undef _ITERATOR_DEBUG_LEVEL
#define _ITERATOR_DEBUG_LEVEL 0
#endif

#include <boost/numeric/ublas/storage_sparse.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/detail/vector_assign.hpp>
#if BOOST_UBLAS_TYPE_CHECK
#include <boost/numeric/ublas/vector.hpp>
#endif

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

#ifdef BOOST_UBLAS_STRICT_VECTOR_SPARSE

    template<class V>
    class sparse_vector_element:
       public container_reference<V> {
    public:
        typedef V vector_type;
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;
        typedef const value_type &const_reference;
        typedef value_type *pointer;

    private:
        // Proxied element operations
        void get_d () const {
            pointer p = (*this) ().find_element (i_);
            if (p)
                d_ = *p;
            else
                d_ = value_type/*zero*/();
        }

        void set (const value_type &s) const {
            pointer p = (*this) ().find_element (i_);
            if (!p)
                (*this) ().insert_element (i_, s);
            else
                *p = s;
        }

    public:
        // Construction and destruction
        sparse_vector_element (vector_type &v, size_type i):
            container_reference<vector_type> (v), i_ (i) {
        }
        BOOST_UBLAS_INLINE
        sparse_vector_element (const sparse_vector_element &p):
            container_reference<vector_type> (p), i_ (p.i_) {}
        BOOST_UBLAS_INLINE
        ~sparse_vector_element () {
        }

        // Assignment
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator = (const sparse_vector_element &p) {
            // Overide the implict copy assignment
            p.get_d ();
            set (p.d_);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator = (const D &d) {
            set (d);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator += (const D &d) {
            get_d ();
            d_ += d;
            set (d_);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator -= (const D &d) {
            get_d ();
            d_ -= d;
            set (d_);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator *= (const D &d) {
            get_d ();
            d_ *= d;
            set (d_);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator /= (const D &d) {
            get_d ();
            d_ /= d;
            set (d_);
            return *this;
        }

        // Comparison
        template<class D>
        BOOST_UBLAS_INLINE
        bool operator == (const D &d) const {
            get_d ();
            return d_ == d;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        bool operator != (const D &d) const {
            get_d ();
            return d_ != d;
        }

        // Conversion - weak link in proxy as d_ is not a perfect alias for the element
        BOOST_UBLAS_INLINE
        operator const_reference () const {
            get_d ();
            return d_;
        }

        // Conversion to reference - may be invalidated
        BOOST_UBLAS_INLINE
        value_type& ref () const {
            const pointer p = (*this) ().find_element (i_);
            if (!p)
                return (*this) ().insert_element (i_, value_type/*zero*/());
            else
                return *p;
        }

    private:
        size_type i_;
        mutable value_type d_;
    };

    /*
     * Generalise explicit reference access
     */
    namespace detail {
        template <class R>
        struct element_reference {
            typedef R& reference;
            static reference get_reference (reference r)
            {
                return r;
            }
        };
        template <class V>
        struct element_reference<sparse_vector_element<V> > {
            typedef typename V::value_type& reference;
            static reference get_reference (const sparse_vector_element<V>& sve)
            {
                return sve.ref ();
            }
        };
    }
    template <class VER>
    typename detail::element_reference<VER>::reference ref (VER& ver) {
        return detail::element_reference<VER>::get_reference (ver);
    }
    template <class VER>
    typename detail::element_reference<VER>::reference ref (const VER& ver) {
        return detail::element_reference<VER>::get_reference (ver);
    }


    template<class V>
    struct type_traits<sparse_vector_element<V> > {
        typedef typename V::value_type element_type;
        typedef type_traits<sparse_vector_element<V> > self_type;
        typedef typename type_traits<element_type>::value_type value_type;
        typedef typename type_traits<element_type>::const_reference const_reference;
        typedef sparse_vector_element<V> reference;
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

    template<class V1, class T2>
    struct promote_traits<sparse_vector_element<V1>, T2> {
        typedef typename promote_traits<typename sparse_vector_element<V1>::value_type, T2>::promote_type promote_type;
    };
    template<class T1, class V2>
    struct promote_traits<T1, sparse_vector_element<V2> > {
        typedef typename promote_traits<T1, typename sparse_vector_element<V2>::value_type>::promote_type promote_type;
    };
    template<class V1, class V2>
    struct promote_traits<sparse_vector_element<V1>, sparse_vector_element<V2> > {
        typedef typename promote_traits<typename sparse_vector_element<V1>::value_type,
                                        typename sparse_vector_element<V2>::value_type>::promote_type promote_type;
    };

#endif


    /** \brief Index map based sparse vector
     *
     * A sparse vector of values of type T of variable size. The sparse storage type A can be 
     * \c std::map<size_t, T> or \c map_array<size_t, T>. This means that only non-zero elements
     * are effectively stored.
     *
     * For a \f$n\f$-dimensional sparse vector,  and 0 <= i < n the non-zero elements \f$v_i\f$ 
     * are mapped to consecutive elements of the associative container, i.e. for elements 
     * \f$k = v_{i_1}\f$ and \f$k + 1 = v_{i_2}\f$ of the container, holds \f$i_1 < i_2\f$.
     *
     * Supported parameters for the adapted array are \c map_array<std::size_t, T> and 
     * \c map_std<std::size_t, T>. The latter is equivalent to \c std::map<std::size_t, T>.
     *
     * \tparam T the type of object stored in the vector (like double, float, complex, etc...)
     * \tparam A the type of Storage array
     */
    template<class T, class A>
    class mapped_vector:
        public vector_container<mapped_vector<T, A> > {

        typedef T &true_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef mapped_vector<T, A> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_container<self_type>::operator ();
#endif
        typedef typename A::size_type size_type;
        typedef typename A::difference_type difference_type;
        typedef T value_type;
        typedef A array_type;
        typedef const value_type &const_reference;
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
        typedef typename detail::map_traits<A,T>::reference reference;
#else
        typedef sparse_vector_element<self_type> reference;
#endif
        typedef const vector_reference<const self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef self_type vector_temporary_type;
        typedef sparse_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        mapped_vector ():
            vector_container<self_type> (),
            size_ (0), data_ () {}
        BOOST_UBLAS_INLINE
        mapped_vector (size_type size, size_type non_zeros = 0):
            vector_container<self_type> (),
            size_ (size), data_ () {
            detail::map_reserve (data(), restrict_capacity (non_zeros));
        }
        BOOST_UBLAS_INLINE
        mapped_vector (const mapped_vector &v):
            vector_container<self_type> (),
            size_ (v.size_), data_ (v.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector (const vector_expression<AE> &ae, size_type non_zeros = 0):
            vector_container<self_type> (),
            size_ (ae ().size ()), data_ () {
            detail::map_reserve (data(), restrict_capacity (non_zeros));
            vector_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz_capacity () const {
            return detail::map_capacity (data ());
        }
        BOOST_UBLAS_INLINE
        size_type nnz () const {
            return data (). size ();
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
    private:
        BOOST_UBLAS_INLINE
        size_type restrict_capacity (size_type non_zeros) const {
            non_zeros = (std::min) (non_zeros, size_);
            return non_zeros;
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size, bool preserve = true) {
            size_ = size;
            if (preserve) {
                data ().erase (data ().lower_bound(size_), data ().end());
            }
            else {
                data ().clear ();
            }
        }

        // Reserving
        BOOST_UBLAS_INLINE
				void reserve (size_type non_zeros, bool /*preserve*/ = true) {
            detail::map_reserve (data (), restrict_capacity (non_zeros));
        }

        // Element support
        BOOST_UBLAS_INLINE
        pointer find_element (size_type i) {
            return const_cast<pointer> (const_cast<const self_type&>(*this).find_element (i));
        }
        BOOST_UBLAS_INLINE
        const_pointer find_element (size_type i) const {
            const_subiterator_type it (data ().find (i));
            if (it == data ().end ())
                return 0;
            BOOST_UBLAS_CHECK ((*it).first == i, internal_logic ());   // broken map
            return &(*it).second;
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            const_subiterator_type it (data ().find (i));
            if (it == data ().end ())
                return zero_;
            BOOST_UBLAS_CHECK ((*it).first == i, internal_logic ());   // broken map
            return (*it).second;
        }
        BOOST_UBLAS_INLINE
        true_reference ref (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            std::pair<subiterator_type, bool> ii (data ().insert (typename array_type::value_type (i, value_type/*zero*/())));
            BOOST_UBLAS_CHECK ((ii.first)->first == i, internal_logic ());   // broken map
            return (ii.first)->second;
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
            return ref (i);
#else
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return reference (*this, i);
#endif
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Element assignment
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, const_reference t) {
            std::pair<subiterator_type, bool> ii = data ().insert (typename array_type::value_type (i, t));
            BOOST_UBLAS_CHECK (ii.second, bad_index ());        // duplicate element
            BOOST_UBLAS_CHECK ((ii.first)->first == i, internal_logic ());   // broken map
            if (!ii.second)     // existing element
                (ii.first)->second = t;
            return (ii.first)->second;
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i) {
            subiterator_type it = data ().find (i);
            if (it == data ().end ())
                return;
            data ().erase (it);
        }

        // Zeroing
        BOOST_UBLAS_INLINE
        void clear () {
            data ().clear ();
        }

        // Assignment
        BOOST_UBLAS_INLINE
        mapped_vector &operator = (const mapped_vector &v) {
            if (this != &v) {
                size_ = v.size_;
                data () = v.data ();
            }
            return *this;
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        mapped_vector &operator = (const vector_container<C> &v) {
            resize (v ().size (), false);
            assign (v);
            return *this;
        }
        BOOST_UBLAS_INLINE
        mapped_vector &assign_temporary (mapped_vector &v) {
            swap (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &operator = (const vector_expression<AE> &ae) {
            self_type temporary (ae, detail::map_capacity (data()));
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }

        // Computed assignment
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &operator += (const vector_expression<AE> &ae) {
            self_type temporary (*this + ae, detail::map_capacity (data()));
            return assign_temporary (temporary);
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        mapped_vector &operator += (const vector_container<C> &v) {
            plus_assign (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &operator -= (const vector_expression<AE> &ae) {
            self_type temporary (*this - ae, detail::map_capacity (data()));
            return assign_temporary (temporary);
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        mapped_vector &operator -= (const vector_container<C> &v) {
            minus_assign (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        mapped_vector &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        mapped_vector &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (mapped_vector &v) {
            if (this != &v) {
                std::swap (size_, v.size_);
                data ().swap (v.data ());
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (mapped_vector &v1, mapped_vector &v2) {
            v1.swap (v2);
        }

        // Iterator types
    private:
        // Use storage iterator
        typedef typename A::const_iterator const_subiterator_type;
        typedef typename A::iterator subiterator_type;

        BOOST_UBLAS_INLINE
        true_reference at_element (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            subiterator_type it (data ().find (i));
            BOOST_UBLAS_CHECK (it != data ().end(), bad_index ());
            BOOST_UBLAS_CHECK ((*it).first == i, internal_logic ());   // broken map
            return it->second;
        }

    public:
        class const_iterator;
        class iterator;

        // Element lookup
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
        const_iterator find (size_type i) const {
            return const_iterator (*this, data ().lower_bound (i));
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
        iterator find (size_type i) {
            return iterator (*this, data ().lower_bound (i));
        }


        class const_iterator:
            public container_const_reference<mapped_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename mapped_vector::value_type value_type;
            typedef typename mapped_vector::difference_type difference_type;
            typedef typename mapped_vector::const_reference reference;
            typedef const typename mapped_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &v, const const_subiterator_type &it):
                container_const_reference<self_type> (v), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator (const typename self_type::iterator &it):  // ISSUE self_type:: stops VC8 using std::iterator here
                container_const_reference<self_type> (it ()), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*it_).second;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*it_).first < (*this) ().size (), bad_index ());
                return (*it_).first;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            const_subiterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return const_iterator (*this, data ().begin ());
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return const_iterator (*this, data ().end ());
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        class iterator:
            public container_reference<mapped_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator, value_type> {
        public:
            typedef typename mapped_vector::value_type value_type;
            typedef typename mapped_vector::difference_type difference_type;
            typedef typename mapped_vector::true_reference reference;
            typedef typename mapped_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &v, const subiterator_type &it):
                container_reference<self_type> (v), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*it_).second;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*it_).first < (*this) ().size (), bad_index ());
                return (*it_).first;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return iterator (*this, data ().begin ());
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return iterator (*this, data ().end ());
        }

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
        typedef reverse_iterator_base<iterator> reverse_iterator;

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator crbegin () const {
            return rbegin ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator crend () const {
            return rend ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

         // Serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */){
            serialization::collection_size_type s (size_);
            ar & serialization::make_nvp("size",s);
            if (Archive::is_loading::value) {
                size_ = s;
            }
            ar & serialization::make_nvp("data", data_);
        }

    private:
        size_type size_;
        array_type data_;
        static const value_type zero_;
    };

    template<class T, class A>
    const typename mapped_vector<T, A>::value_type mapped_vector<T, A>::zero_ = value_type/*zero*/();


    // Thanks to Kresimir Fresl for extending this to cover different index bases.
    
    /** \brief Compressed array based sparse vector
     *
     * a sparse vector of values of type T of variable size. The non zero values are stored as 
     * two seperate arrays: an index array and a value array. The index array is always sorted 
     * and there is at most one entry for each index. Inserting an element can be time consuming.
     * If the vector contains a few zero entries, then it is better to have a normal vector.
     * If the vector has a very high dimension with a few non-zero values, then this vector is
     * very memory efficient (at the cost of a few more computations).
     *
     * For a \f$n\f$-dimensional compressed vector and \f$0 \leq i < n\f$ the non-zero elements 
     * \f$v_i\f$ are mapped to consecutive elements of the index and value container, i.e. for 
     * elements \f$k = v_{i_1}\f$ and \f$k + 1 = v_{i_2}\f$ of these containers holds \f$i_1 < i_2\f$.
     *
     * Supported parameters for the adapted array (indices and values) are \c unbounded_array<> ,
     * \c bounded_array<> and \c std::vector<>.
     *
     * \tparam T the type of object stored in the vector (like double, float, complex, etc...)
     * \tparam IB the index base of the compressed vector. Default is 0. Other supported value is 1
     * \tparam IA the type of adapted array for indices. Default is \c unbounded_array<std::size_t>
     * \tparam TA the type of adapted array for values. Default is unbounded_array<T>
     */
    template<class T, std::size_t IB, class IA, class TA>
    class compressed_vector:
        public vector_container<compressed_vector<T, IB, IA, TA> > {

        typedef T &true_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef compressed_vector<T, IB, IA, TA> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_container<self_type>::operator ();
#endif
        // ISSUE require type consistency check
        // is_convertable (IA::size_type, TA::size_type)
        typedef typename IA::value_type size_type;
        typedef typename IA::difference_type difference_type;
        typedef T value_type;
        typedef const T &const_reference;
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
        typedef T &reference;
#else
        typedef sparse_vector_element<self_type> reference;
#endif
        typedef IA index_array_type;
        typedef TA value_array_type;
        typedef const vector_reference<const self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef self_type vector_temporary_type;
        typedef sparse_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        compressed_vector ():
            vector_container<self_type> (),
            size_ (0), capacity_ (restrict_capacity (0)), filled_ (0),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
        }
        explicit BOOST_UBLAS_INLINE
        compressed_vector (size_type size, size_type non_zeros = 0):
            vector_container<self_type> (),
            size_ (size), capacity_ (restrict_capacity (non_zeros)), filled_ (0),
            index_data_ (capacity_), value_data_ (capacity_) {
        storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        compressed_vector (const compressed_vector &v):
            vector_container<self_type> (),
            size_ (v.size_), capacity_ (v.capacity_), filled_ (v.filled_),
            index_data_ (v.index_data_), value_data_ (v.value_data_) {
            storage_invariants ();
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector (const vector_expression<AE> &ae, size_type non_zeros = 0):
            vector_container<self_type> (),
            size_ (ae ().size ()), capacity_ (restrict_capacity (non_zeros)), filled_ (0),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
            vector_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz_capacity () const {
            return capacity_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz () const {
            return filled_;
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        static size_type index_base () {
            return IB;
        }
        BOOST_UBLAS_INLINE
        typename index_array_type::size_type filled () const {
            return filled_;
        }
        BOOST_UBLAS_INLINE
        const index_array_type &index_data () const {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        const value_array_type &value_data () const {
            return value_data_;
        }
        BOOST_UBLAS_INLINE
        void set_filled (const typename index_array_type::size_type & filled) {
            filled_ = filled;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        index_array_type &index_data () {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        value_array_type &value_data () {
            return value_data_;
        }

        // Resizing
    private:
        BOOST_UBLAS_INLINE
        size_type restrict_capacity (size_type non_zeros) const {
            non_zeros = (std::max) (non_zeros, size_type (1));
            non_zeros = (std::min) (non_zeros, size_);
            return non_zeros;
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size, bool preserve = true) {
            size_ = size;
            capacity_ = restrict_capacity (capacity_);
            if (preserve) {
                index_data_. resize (capacity_, size_type ());
                value_data_. resize (capacity_, value_type ());
                filled_ = (std::min) (capacity_, filled_);
                while ((filled_ > 0) && (zero_based(index_data_[filled_ - 1]) >= size)) {
                    --filled_;
                }
            }
            else {
                index_data_. resize (capacity_);
                value_data_. resize (capacity_);
                filled_ = 0;
            }
            storage_invariants ();
        }

        // Reserving
        BOOST_UBLAS_INLINE
        void reserve (size_type non_zeros, bool preserve = true) {
            capacity_ = restrict_capacity (non_zeros);
            if (preserve) {
                index_data_. resize (capacity_, size_type ());
                value_data_. resize (capacity_, value_type ());
                filled_ = (std::min) (capacity_, filled_);
            }
            else {
                index_data_. resize (capacity_);
                value_data_. resize (capacity_);
                filled_ = 0;
            }
            storage_invariants ();
        }

        // Element support
        BOOST_UBLAS_INLINE
        pointer find_element (size_type i) {
            return const_cast<pointer> (const_cast<const self_type&>(*this).find_element (i));
        }
        BOOST_UBLAS_INLINE
        const_pointer find_element (size_type i) const {
            const_subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return 0;
            return &value_data_ [it - index_data_.begin ()];
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            const_subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return zero_;
            return value_data_ [it - index_data_.begin ()];
        }
        BOOST_UBLAS_INLINE
        true_reference ref (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return insert_element (i, value_type/*zero*/());
            else
                return value_data_ [it - index_data_.begin ()];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
            return ref (i) ;
#else
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return reference (*this, i);
#endif
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Element assignment
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, const_reference t) {
            BOOST_UBLAS_CHECK (!find_element (i), bad_index ());        // duplicate element
            if (filled_ >= capacity_)
                reserve (2 * capacity_, true);
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            // ISSUE max_capacity limit due to difference_type
            typename std::iterator_traits<subiterator_type>::difference_type n = it - index_data_.begin ();
            BOOST_UBLAS_CHECK (filled_ == 0 || filled_ == typename index_array_type::size_type (n) || *it != k_based (i), internal_logic ());   // duplicate found by lower_bound
            ++ filled_;
            it = index_data_.begin () + n;
            std::copy_backward (it, index_data_.begin () + filled_ - 1, index_data_.begin () + filled_);
            *it = k_based (i);
            typename value_array_type::iterator itt (value_data_.begin () + n);
            std::copy_backward (itt, value_data_.begin () + filled_ - 1, value_data_.begin () + filled_);
            *itt = t;
            storage_invariants ();
            return *itt;
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i) {
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            typename std::iterator_traits<subiterator_type>::difference_type  n = it - index_data_.begin ();
            if (filled_ > typename index_array_type::size_type (n) && *it == k_based (i)) {
                std::copy (it + 1, index_data_.begin () + filled_, it);
                typename value_array_type::iterator itt (value_data_.begin () + n);
                std::copy (itt + 1, value_data_.begin () + filled_, itt);
                -- filled_;
            }
            storage_invariants ();
        }

        // Zeroing
        BOOST_UBLAS_INLINE
        void clear () {
            filled_ = 0;
            storage_invariants ();
        }

        // Assignment
        BOOST_UBLAS_INLINE
        compressed_vector &operator = (const compressed_vector &v) {
            if (this != &v) {
                size_ = v.size_;
                capacity_ = v.capacity_;
                filled_ = v.filled_;
                index_data_ = v.index_data_;
                value_data_ = v.value_data_;
            }
            storage_invariants ();
            return *this;
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        compressed_vector &operator = (const vector_container<C> &v) {
            resize (v ().size (), false);
            assign (v);
            return *this;
        }
        BOOST_UBLAS_INLINE
        compressed_vector &assign_temporary (compressed_vector &v) {
            swap (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator = (const vector_expression<AE> &ae) {
            self_type temporary (ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }

        // Computed assignment
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator += (const vector_expression<AE> &ae) {
            self_type temporary (*this + ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        compressed_vector &operator += (const vector_container<C> &v) {
            plus_assign (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator -= (const vector_expression<AE> &ae) {
            self_type temporary (*this - ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        compressed_vector &operator -= (const vector_container<C> &v) {
            minus_assign (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        compressed_vector &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        compressed_vector &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (compressed_vector &v) {
            if (this != &v) {
                std::swap (size_, v.size_);
                std::swap (capacity_, v.capacity_);
                std::swap (filled_, v.filled_);
                index_data_.swap (v.index_data_);
                value_data_.swap (v.value_data_);
            }
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        friend void swap (compressed_vector &v1, compressed_vector &v2) {
            v1.swap (v2);
        }

        // Back element insertion and erasure
        BOOST_UBLAS_INLINE
        void push_back (size_type i, const_reference t) {
            BOOST_UBLAS_CHECK (filled_ == 0 || index_data_ [filled_ - 1] < k_based (i), external_logic ());
            if (filled_ >= capacity_)
                reserve (2 * capacity_, true);
            BOOST_UBLAS_CHECK (filled_ < capacity_, internal_logic ());
            index_data_ [filled_] = k_based (i);
            value_data_ [filled_] = t;
            ++ filled_;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        void pop_back () {
            BOOST_UBLAS_CHECK (filled_ > 0, external_logic ());
            -- filled_;
            storage_invariants ();
        }

        // Iterator types
    private:
        // Use index array iterator
        typedef typename IA::const_iterator const_subiterator_type;
        typedef typename IA::iterator subiterator_type;

        BOOST_UBLAS_INLINE
        true_reference at_element (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            BOOST_UBLAS_CHECK (it != index_data_.begin () + filled_ && *it == k_based (i), bad_index ());
            return value_data_ [it - index_data_.begin ()];
        }

    public:
        class const_iterator;
        class iterator;

        // Element lookup
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
        const_iterator find (size_type i) const {
            return const_iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
        iterator find (size_type i) {
            return iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }


        class const_iterator:
            public container_const_reference<compressed_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename compressed_vector::value_type value_type;
            typedef typename compressed_vector::difference_type difference_type;
            typedef typename compressed_vector::const_reference reference;
            typedef const typename compressed_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &v, const const_subiterator_type &it):
                container_const_reference<self_type> (v), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator (const typename self_type::iterator &it):  // ISSUE self_type:: stops VC8 using std::iterator here
                container_const_reference<self_type> (it ()), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data_ [it_ - (*this) ().index_data_.begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*this) ().zero_based (*it_) < (*this) ().size (), bad_index ());
                return (*this) ().zero_based (*it_);
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            const_subiterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find (size_);
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        class iterator:
            public container_reference<compressed_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator, value_type> {
        public:
            typedef typename compressed_vector::value_type value_type;
            typedef typename compressed_vector::difference_type difference_type;
            typedef typename compressed_vector::true_reference reference;
            typedef typename compressed_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &v, const subiterator_type &it):
                container_reference<self_type> (v), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data_ [it_ - (*this) ().index_data_.begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*this) ().zero_based (*it_) < (*this) ().size (), bad_index ());
                return (*this) ().zero_based (*it_);
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find (size_);
        }

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
        typedef reverse_iterator_base<iterator> reverse_iterator;

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator crbegin () const {
            return rbegin ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator crend () const {
            return rend ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

         // Serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */){
            serialization::collection_size_type s (size_);
            ar & serialization::make_nvp("size",s);
            if (Archive::is_loading::value) {
                size_ = s;
            }
            // ISSUE: filled may be much less than capacity
            // ISSUE: index_data_ and value_data_ are undefined between filled and capacity (trouble with 'nan'-values)
            ar & serialization::make_nvp("capacity", capacity_);
            ar & serialization::make_nvp("filled", filled_);
            ar & serialization::make_nvp("index_data", index_data_);
            ar & serialization::make_nvp("value_data", value_data_);
            storage_invariants();
        }

    private:
        void storage_invariants () const
        {
            BOOST_UBLAS_CHECK (capacity_ == index_data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (capacity_ == value_data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (filled_ <= capacity_, internal_logic ());
            BOOST_UBLAS_CHECK ((0 == filled_) || (zero_based(index_data_[filled_ - 1]) < size_), internal_logic ());
        }

        size_type size_;
        typename index_array_type::size_type capacity_;
        typename index_array_type::size_type filled_;
        index_array_type index_data_;
        value_array_type value_data_;
        static const value_type zero_;

        BOOST_UBLAS_INLINE
        static size_type zero_based (size_type k_based_index) {
            return k_based_index - IB;
        }
        BOOST_UBLAS_INLINE
        static size_type k_based (size_type zero_based_index) {
            return zero_based_index + IB;
        }

        friend class iterator;
        friend class const_iterator;
    };

    template<class T, std::size_t IB, class IA, class TA>
    const typename compressed_vector<T, IB, IA, TA>::value_type compressed_vector<T, IB, IA, TA>::zero_ = value_type/*zero*/();

    // Thanks to Kresimir Fresl for extending this to cover different index bases.

    /** \brief Coordimate array based sparse vector
     *
     * a sparse vector of values of type \c T of variable size. The non zero values are stored 
     * as two seperate arrays: an index array and a value array. The arrays may be out of order 
     * with multiple entries for each vector element. If there are multiple values for the same 
     * index the sum of these values is the real value. It is way more efficient for inserting values
     * than a \c compressed_vector but less memory efficient. Also linearly parsing a vector can 
     * be longer in specific cases than a \c compressed_vector.
     *
     * For a n-dimensional sorted coordinate vector and \f$ 0 \leq i < n\f$ the non-zero elements 
     * \f$v_i\f$ are mapped to consecutive elements of the index and value container, i.e. for 
     * elements \f$k = v_{i_1}\f$ and \f$k + 1 = v_{i_2}\f$ of these containers holds \f$i_1 < i_2\f$.
     *
     * Supported parameters for the adapted array (indices and values) are \c unbounded_array<> ,
     * \c bounded_array<> and \c std::vector<>.
     *
     * \tparam T the type of object stored in the vector (like double, float, complex, etc...)
     * \tparam IB the index base of the compressed vector. Default is 0. Other supported value is 1
     * \tparam IA the type of adapted array for indices. Default is \c unbounded_array<std::size_t>
     * \tparam TA the type of adapted array for values. Default is unbounded_array<T>
     */
    template<class T, std::size_t IB, class IA, class TA>
    class coordinate_vector:
        public vector_container<coordinate_vector<T, IB, IA, TA> > {

        typedef T &true_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef coordinate_vector<T, IB, IA, TA> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_container<self_type>::operator ();
#endif
        // ISSUE require type consistency check
        // is_convertable (IA::size_type, TA::size_type)
        typedef typename IA::value_type size_type;
        typedef typename IA::difference_type difference_type;
        typedef T value_type;
        typedef const T &const_reference;
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
        typedef T &reference;
#else
        typedef sparse_vector_element<self_type> reference;
#endif
        typedef IA index_array_type;
        typedef TA value_array_type;
        typedef const vector_reference<const self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef self_type vector_temporary_type;
        typedef sparse_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        coordinate_vector ():
            vector_container<self_type> (),
            size_ (0), capacity_ (restrict_capacity (0)),
            filled_ (0), sorted_filled_ (filled_), sorted_ (true),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
        }
        explicit BOOST_UBLAS_INLINE
        coordinate_vector (size_type size, size_type non_zeros = 0):
            vector_container<self_type> (),
            size_ (size), capacity_ (restrict_capacity (non_zeros)),
            filled_ (0), sorted_filled_ (filled_), sorted_ (true),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        coordinate_vector (const coordinate_vector &v):
            vector_container<self_type> (),
            size_ (v.size_), capacity_ (v.capacity_),
            filled_ (v.filled_), sorted_filled_ (v.sorted_filled_), sorted_ (v.sorted_),
            index_data_ (v.index_data_), value_data_ (v.value_data_) {
            storage_invariants ();
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector (const vector_expression<AE> &ae, size_type non_zeros = 0):
            vector_container<self_type> (),
            size_ (ae ().size ()), capacity_ (restrict_capacity (non_zeros)),
            filled_ (0), sorted_filled_ (filled_), sorted_ (true),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
            vector_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz_capacity () const {
            return capacity_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz () const {
            return filled_;
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        static size_type index_base () {
            return IB;
        }
        BOOST_UBLAS_INLINE
        typename index_array_type::size_type filled () const {
            return filled_;
        }
        BOOST_UBLAS_INLINE
        const index_array_type &index_data () const {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        const value_array_type &value_data () const {
            return value_data_;
        }
        BOOST_UBLAS_INLINE
        void set_filled (const typename index_array_type::size_type &sorted, const typename index_array_type::size_type &filled) {
            sorted_filled_ = sorted;
            filled_ = filled;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        index_array_type &index_data () {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        value_array_type &value_data () {
            return value_data_;
        }

        // Resizing
    private:
        BOOST_UBLAS_INLINE
        size_type restrict_capacity (size_type non_zeros) const {
             // minimum non_zeros
             non_zeros = (std::max) (non_zeros, size_type (1));
             // ISSUE no maximum as coordinate may contain inserted duplicates
             return non_zeros;
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size, bool preserve = true) {
            if (preserve)
                sort ();    // remove duplicate elements.
            size_ = size;
            capacity_ = restrict_capacity (capacity_);
            if (preserve) {
                index_data_. resize (capacity_, size_type ());
                value_data_. resize (capacity_, value_type ());
                filled_ = (std::min) (capacity_, filled_);
                while ((filled_ > 0) && (zero_based(index_data_[filled_ - 1]) >= size)) {
                    --filled_;
                }
            }
            else {
                index_data_. resize (capacity_);
                value_data_. resize (capacity_);
                filled_ = 0;
            }
            sorted_filled_ = filled_;
            storage_invariants ();
        }
        // Reserving
        BOOST_UBLAS_INLINE
        void reserve (size_type non_zeros, bool preserve = true) {
            if (preserve)
                sort ();    // remove duplicate elements.
            capacity_ = restrict_capacity (non_zeros);
            if (preserve) {
                index_data_. resize (capacity_, size_type ());
                value_data_. resize (capacity_, value_type ());
                filled_ = (std::min) (capacity_, filled_);
                }
            else {
                index_data_. resize (capacity_);
                value_data_. resize (capacity_);
                filled_ = 0;
            }
            sorted_filled_ = filled_;
            storage_invariants ();
        }

        // Element support
        BOOST_UBLAS_INLINE
        pointer find_element (size_type i) {
            return const_cast<pointer> (const_cast<const self_type&>(*this).find_element (i));
        }
        BOOST_UBLAS_INLINE
        const_pointer find_element (size_type i) const {
            sort ();
            const_subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return 0;
            return &value_data_ [it - index_data_.begin ()];
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            sort ();
            const_subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return zero_;
            return value_data_ [it - index_data_.begin ()];
        }
        BOOST_UBLAS_INLINE
        true_reference ref (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            sort ();
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return insert_element (i, value_type/*zero*/());
            else
                return value_data_ [it - index_data_.begin ()];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
            return ref (i);
#else
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return reference (*this, i);
#endif
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Element assignment
        BOOST_UBLAS_INLINE
        void append_element (size_type i, const_reference t) {
            if (filled_ >= capacity_)
                reserve (2 * filled_, true);
            BOOST_UBLAS_CHECK (filled_ < capacity_, internal_logic ());
            index_data_ [filled_] = k_based (i);
            value_data_ [filled_] = t;
            ++ filled_;
            sorted_ = false;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, const_reference t) {
            BOOST_UBLAS_CHECK (!find_element (i), bad_index ());        // duplicate element
            append_element (i, t);
            return value_data_ [filled_ - 1];
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i) {
            sort ();
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            typename std::iterator_traits<subiterator_type>::difference_type n = it - index_data_.begin ();
            if (filled_ > typename index_array_type::size_type (n) && *it == k_based (i)) {
                std::copy (it + 1, index_data_.begin () + filled_, it);
                typename value_array_type::iterator itt (value_data_.begin () + n);
                std::copy (itt + 1, value_data_.begin () + filled_, itt);
                -- filled_;
                sorted_filled_ = filled_;
            }
            storage_invariants ();
        }

        // Zeroing
        BOOST_UBLAS_INLINE
        void clear () {
            filled_ = 0;
            sorted_filled_ = filled_;
            sorted_ = true;
            storage_invariants ();
        }

        // Assignment
        BOOST_UBLAS_INLINE
        coordinate_vector &operator = (const coordinate_vector &v) {
            if (this != &v) {
                size_ = v.size_;
                capacity_ = v.capacity_;
                filled_ = v.filled_;
                sorted_filled_ = v.sorted_filled_;
                sorted_ = v.sorted_;
                index_data_ = v.index_data_;
                value_data_ = v.value_data_;
            }
            storage_invariants ();
            return *this;
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        coordinate_vector &operator = (const vector_container<C> &v) {
            resize (v ().size (), false);
            assign (v);
            return *this;
        }
        BOOST_UBLAS_INLINE
        coordinate_vector &assign_temporary (coordinate_vector &v) {
            swap (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator = (const vector_expression<AE> &ae) {
            self_type temporary (ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }

        // Computed assignment
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator += (const vector_expression<AE> &ae) {
            self_type temporary (*this + ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        coordinate_vector &operator += (const vector_container<C> &v) {
            plus_assign (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator -= (const vector_expression<AE> &ae) {
            self_type temporary (*this - ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class C>          // Container assignment without temporary
        BOOST_UBLAS_INLINE
        coordinate_vector &operator -= (const vector_container<C> &v) {
            minus_assign (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (coordinate_vector &v) {
            if (this != &v) {
                std::swap (size_, v.size_);
                std::swap (capacity_, v.capacity_);
                std::swap (filled_, v.filled_);
                std::swap (sorted_filled_, v.sorted_filled_);
                std::swap (sorted_, v.sorted_);
                index_data_.swap (v.index_data_);
                value_data_.swap (v.value_data_);
            }
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        friend void swap (coordinate_vector &v1, coordinate_vector &v2) {
            v1.swap (v2);
        }

        // replacement if STL lower bound algorithm for use of inplace_merge
        size_type lower_bound (size_type beg, size_type end, size_type target) const {
            while (end > beg) {
                size_type mid = (beg + end) / 2;
                if (index_data_[mid] < index_data_[target]) {
                    beg = mid + 1;
                } else {
                    end = mid;
                }
            }
            return beg;
        }

        // specialized replacement of STL inplace_merge to avoid compilation
        // problems with respect to the array_triple iterator
        void inplace_merge (size_type beg, size_type mid, size_type end) const {
            size_type len_lef = mid - beg;
            size_type len_rig = end - mid;

            if (len_lef == 1 && len_rig == 1) {
                if (index_data_[mid] < index_data_[beg]) {
                    std::swap(index_data_[beg], index_data_[mid]);
                    std::swap(value_data_[beg], value_data_[mid]);
                }
            } else if (len_lef > 0 && len_rig > 0) {
                size_type lef_mid, rig_mid;
                if (len_lef >= len_rig) {
                    lef_mid = (beg + mid) / 2;
                    rig_mid = lower_bound(mid, end, lef_mid);
                } else {
                    rig_mid = (mid + end) / 2;
                    lef_mid = lower_bound(beg, mid, rig_mid);
                }
                std::rotate(&index_data_[0] + lef_mid, &index_data_[0] + mid, &index_data_[0] + rig_mid);
                std::rotate(&value_data_[0] + lef_mid, &value_data_[0] + mid, &value_data_[0] + rig_mid);

                size_type new_mid = lef_mid + rig_mid - mid;
                inplace_merge(beg, lef_mid, new_mid);
                inplace_merge(new_mid, rig_mid, end);
            }
        }

        // Sorting and summation of duplicates
        BOOST_UBLAS_INLINE
        void sort () const {
            if (! sorted_ && filled_ > 0) {
                typedef index_pair_array<index_array_type, value_array_type> array_pair;
                array_pair ipa (filled_, index_data_, value_data_);
#ifndef BOOST_UBLAS_COO_ALWAYS_DO_FULL_SORT
                const typename array_pair::iterator iunsorted = ipa.begin () + sorted_filled_;
                // sort new elements and merge
                std::sort (iunsorted, ipa.end ());
                inplace_merge(0, sorted_filled_, filled_);
#else
                const typename array_pair::iterator iunsorted = ipa.begin ();
                std::sort (iunsorted, ipa.end ());
#endif

                // sum duplicates with += and remove
                size_type filled = 0;
                for (size_type i = 1; i < filled_; ++ i) {
                    if (index_data_ [filled] != index_data_ [i]) {
                        ++ filled;
                        if (filled != i) {
                            index_data_ [filled] = index_data_ [i];
                            value_data_ [filled] = value_data_ [i];
                        }
                    } else {
                        value_data_ [filled] += value_data_ [i];
                    }
                }
                filled_ = filled + 1;
                sorted_filled_ = filled_;
                sorted_ = true;
                storage_invariants ();
            }
        }

        // Back element insertion and erasure
        BOOST_UBLAS_INLINE
        void push_back (size_type i, const_reference t) {
            // must maintain sort order
            BOOST_UBLAS_CHECK (sorted_ && (filled_ == 0 || index_data_ [filled_ - 1] < k_based (i)), external_logic ());
            if (filled_ >= capacity_)
                reserve (2 * filled_, true);
            BOOST_UBLAS_CHECK (filled_ < capacity_, internal_logic ());
            index_data_ [filled_] = k_based (i);
            value_data_ [filled_] = t;
            ++ filled_;
            sorted_filled_ = filled_;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        void pop_back () {
            // ISSUE invariants could be simpilfied if sorted required as precondition
            BOOST_UBLAS_CHECK (filled_ > 0, external_logic ());
            -- filled_;
            sorted_filled_ = (std::min) (sorted_filled_, filled_);
            sorted_ = sorted_filled_ = filled_;
            storage_invariants ();
        }

        // Iterator types
    private:
        // Use index array iterator
        typedef typename IA::const_iterator const_subiterator_type;
        typedef typename IA::iterator subiterator_type;

        BOOST_UBLAS_INLINE
        true_reference at_element (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            sort ();
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            BOOST_UBLAS_CHECK (it != index_data_.begin () + filled_ && *it == k_based (i), bad_index ());
            return value_data_ [it - index_data_.begin ()];
        }

    public:
        class const_iterator;
        class iterator;

        // Element lookup
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
        const_iterator find (size_type i) const {
            sort ();
            return const_iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
        iterator find (size_type i) {
            sort ();
            return iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }


        class const_iterator:
            public container_const_reference<coordinate_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename coordinate_vector::value_type value_type;
            typedef typename coordinate_vector::difference_type difference_type;
            typedef typename coordinate_vector::const_reference reference;
            typedef const typename coordinate_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &v, const const_subiterator_type &it):
                container_const_reference<self_type> (v), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator (const typename self_type::iterator &it):  // ISSUE self_type:: stops VC8 using std::iterator here
                container_const_reference<self_type> (it ()), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data_ [it_ - (*this) ().index_data_.begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*this) ().zero_based (*it_) < (*this) ().size (), bad_index ());
                return (*this) ().zero_based (*it_);
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            const_subiterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find (size_);
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end();
        }

        class iterator:
            public container_reference<coordinate_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator, value_type> {
        public:
            typedef typename coordinate_vector::value_type value_type;
            typedef typename coordinate_vector::difference_type difference_type;
            typedef typename coordinate_vector::true_reference reference;
            typedef typename coordinate_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &v, const subiterator_type &it):
                container_reference<self_type> (v), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data_ [it_ - (*this) ().index_data_.begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*this) ().zero_based (*it_) < (*this) ().size (), bad_index ());
                return (*this) ().zero_based (*it_);
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find (size_);
        }

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
        typedef reverse_iterator_base<iterator> reverse_iterator;

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator crbegin () const {
            return rbegin ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator crend () const {
            return rend ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

         // Serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */){
            serialization::collection_size_type s (size_);
            ar & serialization::make_nvp("size",s);
            if (Archive::is_loading::value) {
                size_ = s;
            }
            // ISSUE: filled may be much less than capacity
            // ISSUE: index_data_ and value_data_ are undefined between filled and capacity (trouble with 'nan'-values)
            ar & serialization::make_nvp("capacity", capacity_);
            ar & serialization::make_nvp("filled", filled_);
            ar & serialization::make_nvp("sorted_filled", sorted_filled_);
            ar & serialization::make_nvp("sorted", sorted_);
            ar & serialization::make_nvp("index_data", index_data_);
            ar & serialization::make_nvp("value_data", value_data_);
            storage_invariants();
        }

    private:
        void storage_invariants () const
        {
            BOOST_UBLAS_CHECK (capacity_ == index_data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (capacity_ == value_data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (filled_ <= capacity_, internal_logic ());
            BOOST_UBLAS_CHECK (sorted_filled_ <= filled_, internal_logic ());
            BOOST_UBLAS_CHECK (sorted_ == (sorted_filled_ == filled_), internal_logic ());
            BOOST_UBLAS_CHECK ((0 == filled_) || (zero_based(index_data_[filled_ - 1]) < size_), internal_logic ());
        }

        size_type size_;
        size_type capacity_;
        mutable typename index_array_type::size_type filled_;
        mutable typename index_array_type::size_type sorted_filled_;
        mutable bool sorted_;
        mutable index_array_type index_data_;
        mutable value_array_type value_data_;
        static const value_type zero_;

        BOOST_UBLAS_INLINE
        static size_type zero_based (size_type k_based_index) {
            return k_based_index - IB;
        }
        BOOST_UBLAS_INLINE
        static size_type k_based (size_type zero_based_index) {
            return zero_based_index + IB;
        }

        friend class iterator;
        friend class const_iterator;
    };

    template<class T, std::size_t IB, class IA, class TA>
    const typename coordinate_vector<T, IB, IA, TA>::value_type coordinate_vector<T, IB, IA, TA>::zero_ = value_type/*zero*/();

}}}

#ifdef BOOST_MSVC
#undef _ITERATOR_DEBUG_LEVEL
#define _ITERATOR_DEBUG_LEVEL _BACKUP_ITERATOR_DEBUG_LEVEL
#undef _BACKUP_ITERATOR_DEBUG_LEVEL
#endif

#endif

/* vector_sparse.hpp
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
*/