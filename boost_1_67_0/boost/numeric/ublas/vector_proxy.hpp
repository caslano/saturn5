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

#ifndef _BOOST_UBLAS_VECTOR_PROXY_
#define _BOOST_UBLAS_VECTOR_PROXY_

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/detail/vector_assign.hpp>
#include <boost/numeric/ublas/detail/temporary.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    /** \brief A vector referencing a continuous subvector of elements of vector \c v containing all elements specified by \c range.
     *
     * A vector range can be used as a normal vector in any expression. 
     * If the specified range falls outside that of the index range of the vector, then
     * the \c vector_range is not a well formed \i Vector \i Expression and access to an 
     * element outside of index range of the vector is \b undefined.
     *
     * \tparam V the type of vector referenced (for example \c vector<double>)
     */
    template<class V>
    class vector_range:
        public vector_expression<vector_range<V> > {

        typedef vector_range<V> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<self_type>::operator ();
#endif
        typedef const V const_vector_type;
        typedef V vector_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;
        typedef typename V::const_reference const_reference;
        typedef typename boost::mpl::if_<boost::is_const<V>,
                                          typename V::const_reference,
                                          typename V::reference>::type reference;
        typedef typename boost::mpl::if_<boost::is_const<V>,
                                          typename V::const_closure_type,
                                          typename V::closure_type>::type vector_closure_type;
        typedef basic_range<size_type, difference_type> range_type;
        typedef const self_type const_closure_type;
        typedef self_type closure_type;
        typedef typename storage_restrict_traits<typename V::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_range (vector_type &data, const range_type &r):
            data_ (data), r_ (r.preprocess (data.size ())) {
            // Early checking of preconditions here.
            // BOOST_UBLAS_CHECK (r_.start () <= data_.size () &&
            //                   r_.start () + r_.size () <= data_.size (), bad_index ());
        }
        BOOST_UBLAS_INLINE
        vector_range (const vector_closure_type &data, const range_type &r, bool):
            data_ (data), r_ (r.preprocess (data.size ())) {
            // Early checking of preconditions here.
            // BOOST_UBLAS_CHECK (r_.start () <= data_.size () &&
            //                    r_.start () + r_.size () <= data_.size (), bad_index ());
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type start () const {
            return r_.start ();
        }
        BOOST_UBLAS_INLINE
        size_type size () const {
            return r_.size ();
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        const vector_closure_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        vector_closure_type &data () {
            return data_;
        }

        // Element access
#ifndef BOOST_UBLAS_PROXY_CONST_MEMBER
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data_ (r_ (i));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data_ (r_ (i));
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }
#else
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) const {
            return data_ (r_ (i));
        }

        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) const {
            return (*this) (i);
        }
#endif

        // ISSUE can this be done in free project function?
        // Although a const function can create a non-const proxy to a non-const object
        // Critical is that vector_type and data_ (vector_closure_type) are const correct
        BOOST_UBLAS_INLINE
        vector_range<vector_type> project (const range_type &r) const {
            return vector_range<vector_type> (data_, r_.compose (r.preprocess (data_.size ())), false);
        }

        // Assignment
        BOOST_UBLAS_INLINE
        vector_range &operator = (const vector_range &vr) {
            // ISSUE need a temporary, proxy can be overlaping alias
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (vr));
            return *this;
        }
        BOOST_UBLAS_INLINE
        vector_range &assign_temporary (vector_range &vr) {
            // assign elements, proxied container remains the same
            vector_assign<scalar_assign> (*this, vr);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_range &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_range &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_range &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const vector_range &vr) const {
            return (*this).data_.same_closure (vr.data_);
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const vector_range &vr) const {
            return (*this).data_ == vr.data_ && r_ == vr.r_;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (vector_range vr) {
            if (this != &vr) {
                BOOST_UBLAS_CHECK (size () == vr.size (), bad_size ());
                // Sparse ranges may be nonconformant now.
                // std::swap_ranges (begin (), end (), vr.begin ());
                vector_swap<scalar_swap> (*this, vr);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (vector_range vr1, vector_range vr2) {
            vr1.swap (vr2);
        }

        // Iterator types
    private:
        typedef typename V::const_iterator const_subiterator_type;
        typedef typename boost::mpl::if_<boost::is_const<V>,
                                          typename V::const_iterator,
                                          typename V::iterator>::type subiterator_type;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator<vector_range<vector_type>,
                                 typename subiterator_type::iterator_category> iterator;
        typedef indexed_const_iterator<vector_range<vector_type>,
                                       typename const_subiterator_type::iterator_category> const_iterator;
#else
        class const_iterator;
        class iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
            const_subiterator_type it (data_.find (start () + i));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, it.index ());
#else
            return const_iterator (*this, it);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find (size_type i) {
            subiterator_type it (data_.find (start () + i));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, it.index ());
#else
            return iterator (*this, it);
#endif
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_range>,
            public iterator_base_traits<typename const_subiterator_type::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
        public:
            typedef typename const_subiterator_type::difference_type difference_type;
            typedef typename const_subiterator_type::value_type value_type;
            typedef typename const_subiterator_type::reference reference;
            typedef typename const_subiterator_type::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &vr, const const_subiterator_type &it):
                container_const_reference<self_type> (vr), it_ (it) {}
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
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return *it_;
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index () - (*this) ().start ();
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
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_subiterator_type it_;
        };
#endif

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
            return find (size ());
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator:
            public container_reference<vector_range>,
            public iterator_base_traits<typename subiterator_type::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
        public:
            typedef typename subiterator_type::difference_type difference_type;
            typedef typename subiterator_type::value_type value_type;
            typedef typename subiterator_type::reference reference;
            typedef typename subiterator_type::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &vr, const subiterator_type &it):
                container_reference<self_type> (vr), it_ (it) {}

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
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return *it_;
            }
            BOOST_UBLAS_INLINE
            reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index () - (*this) ().start ();
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
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ < it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find (size ());
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

    private:
        vector_closure_type data_;
        range_type r_;
    };

    // ------------------
    // Simple Projections
    // ------------------

    /** \brief Return a \c vector_range on a specified vector, a start and stop index.
     * Return a \c vector_range on a specified vector, a start and stop index. The resulting \c vector_range can be manipulated like a normal vector.
     * If the specified range falls outside that of of the index range of the vector, then the resulting \c vector_range is not a well formed
     * Vector Expression and access to an element outside of index range of the vector is \b undefined.
     */
    template<class V>
    BOOST_UBLAS_INLINE
    vector_range<V> subrange (V &data, typename V::size_type start, typename V::size_type stop) {
        typedef basic_range<typename V::size_type, typename V::difference_type> range_type;
        return vector_range<V> (data, range_type (start, stop));
    }

    /** \brief Return a \c const \c vector_range on a specified vector, a start and stop index.
     * Return a \c const \c vector_range on a specified vector, a start and stop index. The resulting \c const \c vector_range can be manipulated like a normal vector.
     *If the specified range falls outside that of of the index range of the vector, then the resulting \c vector_range is not a well formed
     * Vector Expression and access to an element outside of index range of the vector is \b undefined.
     */
    template<class V>
    BOOST_UBLAS_INLINE
    vector_range<const V> subrange (const V &data, typename V::size_type start, typename V::size_type stop) {
        typedef basic_range<typename V::size_type, typename V::difference_type> range_type;
        return vector_range<const V> (data, range_type (start, stop));
    }

    // -------------------
    // Generic Projections
    // -------------------
    
    /** \brief Return a \c const \c vector_range on a specified vector and \c range
     * Return a \c const \c vector_range on a specified vector and \c range. The resulting \c vector_range can be manipulated like a normal vector.
     * If the specified range falls outside that of of the index range of the vector, then the resulting \c vector_range is not a well formed
     * Vector Expression and access to an element outside of index range of the vector is \b undefined.
     */
    template<class V>
    BOOST_UBLAS_INLINE
    vector_range<V> project (V &data, typename vector_range<V>::range_type const &r) {
        return vector_range<V> (data, r);
    }

    /** \brief Return a \c vector_range on a specified vector and \c range
     * Return a \c vector_range on a specified vector and \c range. The resulting \c vector_range can be manipulated like a normal vector.
     * If the specified range falls outside that of of the index range of the vector, then the resulting \c vector_range is not a well formed
     * Vector Expression and access to an element outside of index range of the vector is \b undefined.
     */
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_range<const V> project (const V &data, typename vector_range<V>::range_type const &r) {
        // ISSUE was: return vector_range<V> (const_cast<V &> (data), r);
        return vector_range<const V> (data, r);
   }

    /** \brief Return a \c const \c vector_range on a specified vector and const \c range
     * Return a \c const \c vector_range on a specified vector and const \c range. The resulting \c vector_range can be manipulated like a normal vector.
     * If the specified range falls outside that of of the index range of the vector, then the resulting \c vector_range is not a well formed
     * Vector Expression and access to an element outside of index range of the vector is \b undefined.
     */
    template<class V>
    BOOST_UBLAS_INLINE
    vector_range<V> project (vector_range<V> &data, const typename vector_range<V>::range_type &r) {
        return data.project (r);
    }

    /** \brief Return a \c vector_range on a specified vector and const \c range
     * Return a \c vector_range on a specified vector and const \c range. The resulting \c vector_range can be manipulated like a normal vector.
     * If the specified range falls outside that of of the index range of the vector, then the resulting \c vector_range is not a well formed
     * Vector Expression and access to an element outside of index range of the vector is \b undefined.
     */
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_range<V> project (const vector_range<V> &data, const typename vector_range<V>::range_type &r) {
        return data.project (r);
    }

    // Specialization of temporary_traits
    template <class V>
    struct vector_temporary_traits< vector_range<V> >
    : vector_temporary_traits< V > {} ;
    template <class V>
    struct vector_temporary_traits< const vector_range<V> >
    : vector_temporary_traits< V > {} ;


    /** \brief A vector referencing a non continuous subvector of elements of vector v containing all elements specified by \c slice.
     *
     * A vector slice can be used as a normal vector in any expression.
     * If the specified slice falls outside that of the index slice of the vector, then
     * the \c vector_slice is not a well formed \i Vector \i Expression and access to an 
     * element outside of index slice of the vector is \b undefined.
     *
     * A slice is a generalization of a range. In a range going from \f$a\f$ to \f$b\f$, 
     * all elements belong to the range. In a slice, a \i \f$step\f$ can be specified meaning to
     * take one element over \f$step\f$ in the range specified from \f$a\f$ to \f$b\f$.
     * Obviously, a slice with a \f$step\f$ of 1 is equivalent to a range.
     *
     * \tparam V the type of vector referenced (for example \c vector<double>)
     */
    template<class V>
    class vector_slice:
        public vector_expression<vector_slice<V> > {

        typedef vector_slice<V> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<self_type>::operator ();
#endif
        typedef const V const_vector_type;
        typedef V vector_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;
        typedef typename V::const_reference const_reference;
        typedef typename boost::mpl::if_<boost::is_const<V>,
                                          typename V::const_reference,
                                          typename V::reference>::type reference;
        typedef typename boost::mpl::if_<boost::is_const<V>,
                                          typename V::const_closure_type,
                                          typename V::closure_type>::type vector_closure_type;
        typedef basic_range<size_type, difference_type> range_type;
        typedef basic_slice<size_type, difference_type> slice_type;
        typedef const self_type const_closure_type;
        typedef self_type closure_type;
        typedef typename storage_restrict_traits<typename V::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_slice (vector_type &data, const slice_type &s):
            data_ (data), s_ (s.preprocess (data.size ())) {
            // Early checking of preconditions here.
            // BOOST_UBLAS_CHECK (s_.start () <= data_.size () &&
            //                    s_.start () + s_.stride () * (s_.size () - (s_.size () > 0)) <= data_.size (), bad_index ());
        }
        BOOST_UBLAS_INLINE
        vector_slice (const vector_closure_type &data, const slice_type &s, int):
            data_ (data), s_ (s.preprocess (data.size ())) {
            // Early checking of preconditions here.
            // BOOST_UBLAS_CHECK (s_.start () <= data_.size () &&
            //                    s_.start () + s_.stride () * (s_.size () - (s_.size () > 0)) <= data_.size (), bad_index ());
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type start () const {
            return s_.start ();
        }
        BOOST_UBLAS_INLINE
        difference_type stride () const {
            return s_.stride ();
        }
        BOOST_UBLAS_INLINE
        size_type size () const {
            return s_.size ();
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        const vector_closure_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        vector_closure_type &data () {
            return data_;
        }

        // Element access
#ifndef BOOST_UBLAS_PROXY_CONST_MEMBER
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data_ (s_ (i));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data_ (s_ (i));
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }
#else
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) const {
            return data_ (s_ (i));
        }

        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) const {
            return (*this) (i);
        }
#endif

        // ISSUE can this be done in free project function?
        // Although a const function can create a non-const proxy to a non-const object
        // Critical is that vector_type and data_ (vector_closure_type) are const correct
        BOOST_UBLAS_INLINE
        vector_slice<vector_type> project (const range_type &r) const {
            return vector_slice<vector_type>  (data_, s_.compose (r.preprocess (data_.size ())), false);
        }
        BOOST_UBLAS_INLINE
        vector_slice<vector_type> project (const slice_type &s) const {
            return vector_slice<vector_type>  (data_, s_.compose (s.preprocess (data_.size ())), false);
        }

        // Assignment
        BOOST_UBLAS_INLINE
        vector_slice &operator = (const vector_slice &vs) {
            // ISSUE need a temporary, proxy can be overlaping alias
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (vs));
            return *this;
        }
        BOOST_UBLAS_INLINE
        vector_slice &assign_temporary (vector_slice &vs) {
            // assign elements, proxied container remains the same
            vector_assign<scalar_assign> (*this, vs);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_slice &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_slice &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_slice &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const vector_slice &vr) const {
            return (*this).data_.same_closure (vr.data_);
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const vector_slice &vs) const {
            return (*this).data_ == vs.data_ && s_ == vs.s_;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (vector_slice vs) {
            if (this != &vs) {
                BOOST_UBLAS_CHECK (size () == vs.size (), bad_size ());
                // Sparse ranges may be nonconformant now.
                // std::swap_ranges (begin (), end (), vs.begin ());
                vector_swap<scalar_swap> (*this, vs);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (vector_slice vs1, vector_slice vs2) {
            vs1.swap (vs2);
        }

        // Iterator types
    private:
        // Use slice as an index - FIXME this fails for packed assignment
        typedef typename slice_type::const_iterator const_subiterator_type;
        typedef typename slice_type::const_iterator subiterator_type;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator<vector_slice<vector_type>,
                                 typename vector_type::iterator::iterator_category> iterator;
        typedef indexed_const_iterator<vector_slice<vector_type>,
                                       typename vector_type::const_iterator::iterator_category> const_iterator;
#else
        class const_iterator;
        class iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, i);
#else
            return const_iterator (*this, s_.begin () + i);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find (size_type i) {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, i);
#else
            return iterator (*this, s_.begin () + i);
#endif
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_slice>,
            public iterator_base_traits<typename V::const_iterator::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
        public:
            typedef typename V::const_iterator::difference_type difference_type;
            typedef typename V::const_iterator::value_type value_type;
            typedef typename V::const_reference reference;    //FIXME due to indexing access
            typedef typename V::const_iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &vs, const const_subiterator_type &it):
                container_const_reference<self_type> (vs), it_ (it) {}
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
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                // FIXME replace find with at_element
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().data_ (*it_);
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index ();
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
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_subiterator_type it_;
        };
#endif

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
            return find (size ());
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator:
            public container_reference<vector_slice>,
            public iterator_base_traits<typename V::iterator::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
        public:
            typedef typename V::iterator::difference_type difference_type;
            typedef typename V::iterator::value_type value_type;
            typedef typename V::reference reference;    //FIXME due to indexing access
            typedef typename V::iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &vs, const subiterator_type &it):
                container_reference<self_type> (vs), it_ (it) {}

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
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                // FIXME replace find with at_element
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().data_ (*it_);
            }
            BOOST_UBLAS_INLINE
            reference operator [] (difference_type n) const {
                return *(*this + n);
            }


            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index ();
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
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ < it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find (size ());
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

    private:
        vector_closure_type data_;
        slice_type s_;
    };

    // Simple Projections
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> subslice (V &data, typename V::size_type start, typename V::difference_type stride, typename V::size_type size) {
        typedef basic_slice<typename V::size_type, typename V::difference_type> slice_type;
        return vector_slice<V> (data, slice_type (start, stride, size));
    }
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<const V> subslice (const V &data, typename V::size_type start, typename V::difference_type stride, typename V::size_type size)  {
        typedef basic_slice<typename V::size_type, typename V::difference_type> slice_type;
        return vector_slice<const V> (data, slice_type (start, stride, size));
    }

    // Generic Projections
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (V &data, const typename vector_slice<V>::slice_type &s) {
        return vector_slice<V> (data, s);
    }
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_slice<const V> project (const V &data, const typename vector_slice<V>::slice_type &s) {
        // ISSUE was: return vector_slice<V> (const_cast<V &> (data), s);
        return vector_slice<const V> (data, s);
    }
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (vector_slice<V> &data, const typename vector_slice<V>::slice_type &s) {
        return data.project (s);
    }
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_slice<V> project (const vector_slice<V> &data, const typename vector_slice<V>::slice_type &s) {
        return data.project (s);
    }
    // ISSUE in the following two functions it would be logical to use vector_slice<V>::range_type but this confuses VC7.1 and 8.0
    template<class V>
    BOOST_UBLAS_INLINE
    vector_slice<V> project (vector_slice<V> &data, const typename vector_range<V>::range_type &r) {
        return data.project (r);
    }
    template<class V>
    BOOST_UBLAS_INLINE
    const vector_slice<V> project (const vector_slice<V> &data, const typename vector_range<V>::range_type &r) {
        return data.project (r);
    }

    // Specialization of temporary_traits
    template <class V>
    struct vector_temporary_traits< vector_slice<V> >
    : vector_temporary_traits< V > {} ;
    template <class V>
    struct vector_temporary_traits< const vector_slice<V> >
    : vector_temporary_traits< V > {} ;


    // Vector based indirection class
    // Contributed by Toon Knapen.
    // Extended and optimized by Kresimir Fresl.

    /** \brief A vector referencing a non continuous subvector of elements given another vector of indices.
     *
     * It is the most general version of any subvectors because it uses another vector of indices to reference
     * the subvector. 
     *
     * The vector of indices can be of any type with the restriction that its elements must be
     * type-compatible with the size_type \c of the container. In practice, the following are good candidates:
     * - \c boost::numeric::ublas::indirect_array<A> where \c A can be \c int, \c size_t, \c long, etc...
     * - \c std::vector<A> where \c A can \c int, \c size_t, \c long, etc...
     * - \c boost::numeric::ublas::vector<int> can work too (\c int can be replaced by another integer type)
     * - etc...
     *
     * An indirect vector can be used as a normal vector in any expression. If the specified indirect vector 
     * falls outside that of the indices of the vector, then the \c vector_indirect is not a well formed 
     * \i Vector \i Expression and access to an element outside of indices of the vector is \b undefined.
     *
     * \tparam V the type of vector referenced (for example \c vector<double>)
     * \tparam IA the type of index vector. Default is \c ublas::indirect_array<>
     */
    template<class V, class IA>
    class vector_indirect:
        public vector_expression<vector_indirect<V, IA> > {

        typedef vector_indirect<V, IA> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<self_type>::operator ();
#endif
        typedef const V const_vector_type;
        typedef V vector_type;
        typedef const IA const_indirect_array_type;
        typedef IA indirect_array_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        typedef typename V::value_type value_type;
        typedef typename V::const_reference const_reference;
        typedef typename boost::mpl::if_<boost::is_const<V>,
                                          typename V::const_reference,
                                          typename V::reference>::type reference;
        typedef typename boost::mpl::if_<boost::is_const<V>,
                                          typename V::const_closure_type,
                                          typename V::closure_type>::type vector_closure_type;
        typedef basic_range<size_type, difference_type> range_type;
        typedef basic_slice<size_type, difference_type> slice_type;
        typedef const self_type const_closure_type;
        typedef self_type closure_type;
        typedef typename storage_restrict_traits<typename V::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_indirect (vector_type &data, size_type size):
            data_ (data), ia_ (size) {}
        BOOST_UBLAS_INLINE
        vector_indirect (vector_type &data, const indirect_array_type &ia):
            data_ (data), ia_ (ia.preprocess (data.size ())) {}
        BOOST_UBLAS_INLINE
        vector_indirect (const vector_closure_type &data, const indirect_array_type &ia, int):
            data_ (data), ia_ (ia.preprocess (data.size ())) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return ia_.size ();
        }
        BOOST_UBLAS_INLINE
        const_indirect_array_type &indirect () const {
            return ia_;
        }
        BOOST_UBLAS_INLINE
        indirect_array_type &indirect () {
            return ia_;
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        const vector_closure_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        vector_closure_type &data () {
            return data_;
        }

        // Element access
#ifndef BOOST_UBLAS_PROXY_CONST_MEMBER
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data_ (ia_ (i));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data_ (ia_ (i));
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }
#else
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) const {
            return data_ (ia_ (i));
        }

        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) const {
            return (*this) (i);
        }
#endif

        // ISSUE can this be done in free project function?
        // Although a const function can create a non-const proxy to a non-const object
        // Critical is that vector_type and data_ (vector_closure_type) are const correct
        BOOST_UBLAS_INLINE
        vector_indirect<vector_type, indirect_array_type> project (const range_type &r) const {
            return vector_indirect<vector_type, indirect_array_type> (data_, ia_.compose (r.preprocess (data_.size ())), 0);
        }
        BOOST_UBLAS_INLINE
        vector_indirect<vector_type, indirect_array_type> project (const slice_type &s) const {
            return vector_indirect<vector_type, indirect_array_type> (data_, ia_.compose (s.preprocess (data_.size ())), 0);
        }
        BOOST_UBLAS_INLINE
        vector_indirect<vector_type, indirect_array_type> project (const indirect_array_type &ia) const {
            return vector_indirect<vector_type, indirect_array_type> (data_, ia_.compose (ia.preprocess (data_.size ())), 0);
        }

        // Assignment
        BOOST_UBLAS_INLINE
        vector_indirect &operator = (const vector_indirect &vi) {
            // ISSUE need a temporary, proxy can be overlaping alias
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (vi));
            return *this;
        }
        BOOST_UBLAS_INLINE
        vector_indirect &assign_temporary (vector_indirect &vi) {
            // assign elements, proxied container remains the same
            vector_assign<scalar_assign> (*this, vi);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, typename vector_temporary_traits<V>::type (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_indirect &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_indirect &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_indirect &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const vector_indirect &/*vr*/) const {
            return true;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const vector_indirect &vi) const {
            return (*this).data_ == vi.data_ && ia_ == vi.ia_;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (vector_indirect vi) {
            if (this != &vi) {
                BOOST_UBLAS_CHECK (size () == vi.size (), bad_size ());
                // Sparse ranges may be nonconformant now.
                // std::swap_ranges (begin (), end (), vi.begin ());
                vector_swap<scalar_swap> (*this, vi);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (vector_indirect vi1, vector_indirect vi2) {
            vi1.swap (vi2);
        }

        // Iterator types
    private:
        // Use indirect array as an index - FIXME this fails for packed assignment
        typedef typename IA::const_iterator const_subiterator_type;
        typedef typename IA::const_iterator subiterator_type;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator<vector_indirect<vector_type, indirect_array_type>,
                                 typename vector_type::iterator::iterator_category> iterator;
        typedef indexed_const_iterator<vector_indirect<vector_type, indirect_array_type>,
                                       typename vector_type::const_iterator::iterator_category> const_iterator;
#else
        class const_iterator;
        class iterator;
#endif
        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, i);
#else
            return const_iterator (*this, ia_.begin () + i);
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find (size_type i) {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, i);
#else
            return iterator (*this, ia_.begin () + i);
#endif
        }

        // Iterators simply are indices.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_indirect>,
            public iterator_base_traits<typename V::const_iterator::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
        public:
            typedef typename V::const_iterator::difference_type difference_type;
            typedef typename V::const_iterator::value_type value_type;
            typedef typename V::const_reference reference;    //FIXME due to indexing access
            typedef typename V::const_iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &vi, const const_subiterator_type &it):
                container_const_reference<self_type> (vi), it_ (it) {}
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
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                // FIXME replace find with at_element
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().data_ (*it_);
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index ();
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
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_subiterator_type it_;
        };
#endif

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
            return find (size ());
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class iterator:
            public container_reference<vector_indirect>,
            public iterator_base_traits<typename V::iterator::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
        public:
            typedef typename V::iterator::difference_type difference_type;
            typedef typename V::iterator::value_type value_type;
            typedef typename V::reference reference;    //FIXME due to indexing access
            typedef typename V::iterator::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &vi, const subiterator_type &it):
                container_reference<self_type> (vi), it_ (it) {}

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
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                // FIXME replace find with at_element
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().data_ (*it_);
            }
            BOOST_UBLAS_INLINE
            reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index ();
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
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return it_ < it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find (size ());
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

    private:
        vector_closure_type data_;
        indirect_array_type ia_;
    };

    // Projections
    template<class V, class A>
    BOOST_UBLAS_INLINE
    vector_indirect<V, indirect_array<A> > project (V &data, const indirect_array<A> &ia) {
        return vector_indirect<V, indirect_array<A> > (data, ia);
    }
    template<class V, class A>
    BOOST_UBLAS_INLINE
    const vector_indirect<const V, indirect_array<A> > project (const V &data, const indirect_array<A> &ia) {
        // ISSUE was: return vector_indirect<V, indirect_array<A> > (const_cast<V &> (data), ia)
        return vector_indirect<const V, indirect_array<A> > (data, ia);
    }
    template<class V, class IA>
    BOOST_UBLAS_INLINE
    vector_indirect<V, IA> project (vector_indirect<V, IA> &data, const typename vector_indirect<V, IA>::range_type &r) {
        return data.project (r);
    }
    template<class V, class IA>
    BOOST_UBLAS_INLINE
    const vector_indirect<V, IA> project (const vector_indirect<V, IA> &data, const typename vector_indirect<V, IA>::range_type &r) {
        return data.project (r);
    }
    template<class V, class IA>
    BOOST_UBLAS_INLINE
    vector_indirect<V, IA> project (vector_indirect<V, IA> &data, const typename vector_indirect<V, IA>::slice_type &s) {
        return data.project (s);
    }
    template<class V, class IA>
    BOOST_UBLAS_INLINE
    const vector_indirect<V, IA> project (const vector_indirect<V, IA> &data, const typename vector_indirect<V, IA>::slice_type &s) {
        return data.project (s);
    }
    template<class V, class A>
    BOOST_UBLAS_INLINE
    vector_indirect<V, indirect_array<A> > project (vector_indirect<V, indirect_array<A> > &data, const indirect_array<A> &ia) {
        return data.project (ia);
    }
    template<class V, class A>
    BOOST_UBLAS_INLINE
    const vector_indirect<V, indirect_array<A> > project (const vector_indirect<V, indirect_array<A> > &data, const indirect_array<A> &ia) {
        return data.project (ia);
    }

    // Specialization of temporary_traits
    template <class V>
    struct vector_temporary_traits< vector_indirect<V> >
    : vector_temporary_traits< V > {} ;
    template <class V>
    struct vector_temporary_traits< const vector_indirect<V> >
    : vector_temporary_traits< V > {} ;

}}}

#endif

/* vector_proxy.hpp
yuAL5QK7HEEn6NQmRChQDNUoxRyNUkB/IkbosiEXkIo5spuqt/2B83wVkF+dJ1IxXsdHfvJIc2iKmz+KiUTQjiYWGq1YDB82X6MVuV04+8SU6V83N+TL1SgzcRTZl6sR650ilT1ExsaVpp/JKCgkV67pODXz8c9kDRgLe9aB53MK2mX4b1v9J75OE5asLOQ+gv1DaoU0OeIX9DN04JP09gOwdz6VguawsM5ptWd3/hzoKsFHwl/rn2PKGVx0dGBGpWb/1Mx441Pk/+xl0tsot9NH9+TiqNWs4FHL79LF64J1u7ktYt32iGvpyg8kYwHSQu/lCv3XzyuQ0X7750jsIGUBbvl4SmPTHyKYUnxyys8RWL6d2vDtqYg2zDZ3aWPUlT02HlkOWpsYBrQ64/K/nEAWZPvcSkEt/OrRrrR4Kw5yxrRsa/GXSIx9Har3Ni3G5j+J0RrmUOgieDlFx+ynpRdYHUrRJ/05uMyn5yk+BIJQ1Kq2NpjhTjEhwS4KEh2pE+rtxgJEd3Q5jRMMqcja5DU6jBNqjQXfQCsa7bt+3vUrXEjV1j4E+bsJjQXmjILD3pu0syNmjG23dOOzI4fYSTE9augQafMIzRuNdU1sAH3kw/CJZxcG0JHnDTHs4a3mDkd1sC1jMXFmFoLlwoPj7JDNUSQGNQyiskBqemP8kP0jCKFqqyFOe7t8+kwIiSjy7Dvt91Fn34PhVgaGdj77/m1e5Nl3cVzo7LvpGXj+53/R2fd3z/DZd1YIH34Q4sM/tjn6+PsPX2nH3/94JnT8fY2g4+8lz0Qdf3ey1yJVDc/xgh6kg51/WlWDk7XpjglHf0U7HT5R6y4DB2lnKLg3QuEeryncS1S0rfYNN3aph/fxeD6Qq0N2P3S1ydBVrNoLcXxWMcu7N8KGPfnzCBwf9PJOVzPoeNha8t+ouVFeBb7V/OA7xO9XRuk/bWFZ6+0OkNb9k0DIf5fEShF0+GfFUJCarXbxDWGz5Lr9S1Ah7CnZD2TTG++GHqLYuY7hajw1ZEbzZW9YE8Yja5HBdxuly1hv9/2cMHO1sD023GIoqSuwypJGHrony46MQHffW/shAsWG4f0MobgQ80jSfeM86on4OmXVKVWYG+6wGDJfq0cxbYhC/9Hhkp/4cMkpCt2p3S6CW+g9cLGvHoGVeABbqNq+6wOCi20+FNPegCcMfuSUp19F/OEBhzJOdYi8HxzCExzpN3Xn40QRUJxG4Tkywm/qr8HaxDsUTw/FA5TB2Vtx9nUoeVfAyKFc5xSV7OgHPDCs88t4iGGJDG9H71kaOZNbjEzoNGwl+CTIufBrZ1kVW3tTH9SHTgRxbGCyfA+oJ1pPKDOAHZ2RPNzNGwLIl0gtIpwV/z7SxBBEOWIHG1LAxHvOpXzRyDJpep19LZpnoHGr/64WNSOr8nbgdm6Vx75nbud6EgRzxAzU4s0gfBiHMP/udouB/S1Le8LCTN/USpbTO+RbGGNF2YBKEfi3glUX377NM46m1/wDzSGslPT3mGk1MNO66kKslIfu1rFSou0eckVxMjt49s8RTUoRMtqQVKob2R138xmXUoTss/zD+QsMT7R4ODBGJSP4CIdia+8khX607QnF8kpCC2LSVO1WbQOuMAEfPR7PwVk/73+DmhN1FB6OJsOeCWhal6vbTyTptjaPaI5Ek/4ZsrXJTd+vPJTgEY0ZV2bcRuf4BYny8e9UVQRxrZg1fza0Liu/VXPacQlb9a3hc+ndO6LOpbeeQto4f7h2ZJ+tmccDh6za9vTi2Iso9LjdYjZSMEcq5Kc6kh0OZWk2nZ47aLUDXYMnsAbfrIRYbwL8NYqKAo4ZjEMoZudSHdOS+EwMQ6KRKtlNoHq3/IoB8UKzDpW+fe9sUUuaC67X2cNsmF5qOrpKW25NtLCt89e63kFWb2zlAuBVp9+eUDnbren+5c4M7COaIaH9z9KwO1CKbv8zlu1//HfpeP9dnXuNztKPBghGenoSn7gR85X+5+NqOND7S5bT6iV0eWfl2qf4iMdERcZrsWwJKUwGiqAo33LC/fYtZ18TPwVFkEWIu+G/csM+ZPyX0qGCb3kHe6MsT+IXCGrWt9zE/xL4XxL/S2RqUhnW4nXB5/38awSPNeTn5i55rNFa4K7tn4bmZloYOzgMVBAO76kBCB8awMzAmxmo+TWL7haad4NKUNHrsDrN1ZAivQdbdRg7LTbnNe/GRFmhhs9ZNJRte7gl2V23pIlb0qC1ZAy15N+4SIP3uUQ7+hG94BJTYTnfg1NurDXpXpCyCTCSOGp7e3163Uk8Q0lTbX/qy8F+0sgC45MBhHGQDGUUrEZKgI4AiH/9DpOxQu2Ul/2ftga/l9fAwO6QA/GvbnuM4/nKP8Lj6dBRq/eV1Hlnqdu8L8AvD373wO8KhMDthWcUcXR2oOAHD06CFRB8Sig4a3zlZoFWMOl1uzrsxkD7cYeoclhXVgdHiCLKD5itK4twggRv7JziSK0KXsGJTr87xhzsuRbopJpKKQ4jBokks4aAs6TaaR1Vbs8MOKzugCOTwJG9U3XYCgejJTvENnl2ohaBratvw19kaz+TgTY8kI8uh0tcMr5tamoV7MExbj5MhcdaL4+ApObDDtV2CyVqk+X0EoIdz9b9qXq7/EWDQrwV4jAUxJLCPXzWGOeNtIdmARV5VZc61NqPcd3DNn1KkhZYYYBsaTzV+T3gH/qaDGH/pJJqa/Fq+pCb8/QA51HYExs7KRqmfqxza8PYjC6bysghEImNKAcarMWZiP/WCcMBeIK+qm1WXxQdn++LJyjt2nguATbOVw1DGeNRy4BFAD5uBEJFtKu2ZZAlxrU7xPPnHakrecbtpQ35TJAUB2sIiZUCsDetpq3sJ1gf2lG8uJ28nNMDwA2QW561eAkxFaZkkFkJig6ZA7cfN/m8eGQ2QLiAzVDxLAdWKdOpzuwnnO2Z9QXxwgPtC3YX9cL5sdP/nNksZuN0UzxLFef7yrhFDuX5Jcq4lcZ9iA8p8hahzlPJ+8wlnEsJVm6T4lxvTXKuPGnHNZqPTaDq8n0VJmxwyUjodzBRLu/Apfe3DhIoSO3pFtnUg4DuWFiMmWK+voycxlTn+bfazzpEo11kPwdXos2eegrKnPcBa+t5du3H2fUKzK4nfRPi4Yv0gJ8Vfr015A1UCxzEL8GGK4RwMbhPaNKf6Y3YGdbUWnvqXgWfN/LYiRqMX4trKpdQJQK0pKh1dmgeLOqdDmU+rkiHQhRf48c4oG2NvGo8hm/ZmBirHan8+SgpASio7bbFUVASEUFtx4ViN+tr5NCUljAQy9BfVPWivllOcTAHAaUINKF9Fr62hON4SRylJ+gk6QqXeCmJIiNdrv52Cq7NH5B+moCEmShwaWa5dwCnENDa6GzChy/tTeakMAXiQPJlhC21lPg72ESsji1BowuPoC/i/hSmtdYViRFhqIs6tFgBUPbDDkb6tiZl5xPRCZN+oD+zgC0qi9VMm9nFc+xlXZCkpb04UbX92DuCOI1ZFCZOneW3FfUoYBcda+ukqEKqkL9ca64WEa2Bok8ddmT8DT9sgVkuZLXDIPmbI6hP6nD5H05BJZpqM/fB+t+lGDzMIpbstxaPQts3SzcjCEvExHivUOg/g+e8Og8FJYywLf8Al8ilIe6mR2zW7ErmYXGy7oNT6AtdzJDYG9gXRrUWH6Q2HqDrarq+xyUeT7LD61A3E4qPyU1iZD4N7BQHQ4fTUJPaSrXZkjSVfMbYZK/VP5tARoszHMkzZk5yiGdTHOKPLuQUc25uUencCdlQa9mzKZcFe7gy3+0gIEzHQXIiNeKxCJ6JoPFBGg4chq9GC383dwVtZqbkMHBLbppDgeLRNRE6UJLOhOOFU0g4JuNfbRgjR8I9GxlrT6nsMeKMWuoUW3D0aPjvhm7I78ag2VuHNcVZyHYYLkFAE/40wgNDrOU3ykFQK+W9n+0gxicPCjerRl2Iw1tKldzvPAPF+XUcaeNfmNFAJSziSMd0kpciYoytS4pwOIqTb51EOlhUTmysY/pxDJ7ICMOIEYWfP/OsyomYQuu0B04RWIq2Pp0MTy8dq/jdD0IaOLf4G6+3s+7MQwXd5STYk5o+IOX2gg49THp6MxoDuJXn8QfVfZhEUSpXwR3+1qq253piA5biKDQtoV6dpKl9gK6nkkchblXVNNOQnWMYUb+nUV/SCLXwDwsaci3FinMyTxb0QBwC0oIHzTmZpwoc2mr3NNJif7GnScN5y0OUolp0sIFfvWrbYiHS1EcLu1yrU4K/WChYpLVkLPnReVaptjt7Esf4gsjbIZybhefLjLzVr5oyq2aNFUuRkqduSqWm+vskiIrMr63uTSWBl3vZxXfBXvKn4zgPG/Ev5jTwmSspsmowJMk8Mq4fpQUaUZZiOaotyWLSovs+atWvnuvFmJWG51r0QFTXuMQT2bhr3HBjC2Hyu4GNs64JUBAc1fY6vcGKxXmvx1wiyC/qeYHxK6l7uWd6nTwE2wVrJu8AWktM93Wo9ODQVr9NQuha4NSu9v0pweCNc4gRjqAJ/mY7YRPYhPqxOtIJy6Nt2PfDbRF8M+5NvnNDrMVFKOScS/ZmTJ3iO3ftVKfvXMq0iS7BEwoKH6xNc9gZ5S3e44RT9nuEfIK8p2CmB0HiXkfsFVrILqBG2iPePxjx/ok/8vvXY1SG4L95Tyx/Bm34uQgEe9CUor9Nkj+EUdiB5nNsrKJjpYZobLkE3C6n07i/kbxK8/zrc1LVtQAJLPbTl49qaqK//IxKRhLq0IMYtf2v4/EIRy54YhBpAMhMEeT/fpDAGjP/w3H88OBYLRRpmnybDgQ0lIaizdiiSBt00nzsk8lQYbCfLuxuK21V0+sIi7GKEB848K2h4Hvf+yx+vs/i5/skfuphmKfHiL3yqbEtWghXorRIJeTMx9kZJDt8HqcsIJIsRky2+wJxDqWI/bxHTEZOzxeIV0gSaXqE1pP5xpvZX6fkFhSnH0ogyKtyxr99idJiwrpqO/rEninEDg/yxlXGMjXMSZDGVIoWETvY2Bkjx29OvUXH0jqzKcZrlj2am9Uom0Ligx7RA7MM8mUtNlvIM91aQopfYckfSjh51uLFoYgZuy1suPoax5NAXsWSMZQlYjpFy5W/v/206uswWUumcSkDMFu81S9W28RPU+ufne4qabYWs3mo5doi9GLfLTd8wSd8LvSOwtblatFiOlTbez1MFKUUkh7IB3mrB1GuLGS3fgPVfJZsYRS7OUbaVQdA2lJI849OIr0L2YertmLoAKPfbeGN3/uk7sA+PUEPJh5vYSKzZBL52Kc8xz72g74IBfm7AZkjF++msCOPIR+1204j/MgLM62+jtiZU30dRu9Tvg6zdxy0xNapdTmQFoOty41q3U+JGFk+pQdXP3ASIxMOdPltHzydSGmTP6eoD93QXkWq15G7csgVg2T1B7KDNoyRZEb92kGo560hFm130uCwEdc90UQmL/JLKKIpSK7eYT5z+TsROpKsQiPNi4aCyVCYewhjJ47tWmORo4ddOtaNtQ2DSNtwd3faO0A4tPQYoo1EIakV6ZCmxnWeYhXGR5wEabznt3MjeE/9bIMdhAT6ih8nKRZal1nOsOHW4u8oQOgr1uJ5cJGFq2bqzVnv4b8ns9D3YOqQrP/Bfw9nfYj/bFlokzPV6X/5fGalt3+WiQKR8bCmRSKCCcuoa7jzh3gxVFGvvN+4nx6JX1HsDd5v3TgCeSQ8TobLAfD/Lpyzw+VcpEf52H+tjHe5jGIuoxSksKTLCpTwN4JHGwdbtGW3s7s+ayeScs+yZbC2NIme0DN3duelOQJZv7oskgaKT+AQxNAlanSyjHj52tXwSJYZLqe+kBVHKRZMQdo3dezG7vAvs9JacpaOziyP6VU1/apXVdONq9rLTwyHJ3zrii8nKb/iV+S9HujnFiOT8GmxV7VZoWlNHyGgIA1P98jhkbePD511DXSJHqrtJSodratG0Wwartq+N/PaJ5cH+3mVwIyCVDu8kM3NKUHvi6bdF6mm5mleTFaMhacVOzuy2F+RoVuPK0GLUYwr4Z23QythuMuXZRtlQaGzDeabOGstXkikbJPrxr/hvgacqjSC/Id/+7huRKwsbyLdxbmAGBRMviBUWV9oeJcQqcL8yYP47V0JmiMIjvpbcdxaiv+Sotqa4mhR9eI0YXkZXpHJ5+iTTIBrt9jpFhU4/sPMLM0NxxX13wqvKLaHD+uIFNuUqy3ENdwBPR0CBRgKklXbwl+NtB/6bT/C2Nj9rngHMtI7THjQYP4FwWCVK3+Ff0HgwyzNHp7dPVXbH+JRpTS0wYPUI/SffPyE+SuPxcABW7y3ID+C6Bpmu6hFqfm3GBM1AfHKzTmiClOAqmTuyrE6AlDjQniz0xnwJtL0wD6bNDGzsmCsdU0DcBxLLscw75a/XsUNuonH0BZPc2sw5PwZchz++wZo9LfMQNzieHhAVAb7wwP9r+VXe4ivpX1PO+60P+pkIcoHFPfnfb5lSGkOIH6RG1I8UMvdiOuXg9MNQ166EF0os8rbF+MzPm8kAFBo0Un8qpCfig/75tAmrw9TTgI+W6L7N/ntMaqtIi6kqcMwwNvcYp9a9Vb7ulxSqtbahd1E94+grEw8ibrNkVknttmt7m0OESipntkN7uGuDghtnV0BFp0d4qodmeWiHDJA1MVn8LIKnqm2Kzkm5C2oPuvKIqxKDSixoggrsa4cYYK7ESagx+FM9EfVchPxNpFv9aNHQc/liGpKAB5RHdpgQKVlaD6qtidjeRu05cPKzawoiFNtb8aE/ERJD6FpJZkrdR6J0D0cfjPCXBJPCdLPuJSCvvC7GnWOPBvijRjms0q196hlfNh7Y8hYEoFqSQ/1NpGY2Ty2sx8h6Xylc7/D6LxCVFlXevYaPX0VzwGH4vxB8QwzVimem9ByEK3sFE8qR/4Emh6uY5hqO2QwafrKVnnvXuCBHazSI5NNTLyuGo0lF/VjHr7AJPbQqoBJRrAi8p0GYkNIYy0IokT+9AJ6LVQ5hHO/wJZr+CPzTxsNmr3rHxPITJVLeLyhRQuGcqWJx/if6KntX1Rv0GOtIZVUbfNUI0nvrdJAAY7Z0tFVwqJ7IIIDp3heLEvPSO6XFwYVfPwvITA634SAwTdhM7zrhJVMM8CN3qJAexbove01mObs4AU4JZs2k44vJwGE16qyQdSnr88YDcK5gxTzGtgcg6+fMii+JIrZUouRihQfTWrbkBjSXroIeg5k4adVfL/N5V+PrripTvlWO2E9KM6AcJ5KdR6D+z50v5nb6cuNYUbR6vLNSjDwKVN5fQu6NVIoO5oWwjyzLdGQucnqrkUjhC2njOS1AVzj5fU0coQw17M4fJTXLxzbiOIj8pDhppPyRsSQNULXDhMnTxFMD8fqers8uJtn4LvOI4EDAHykAZVRS6iVPm3yLkmiRUmD4zCOk0bnMQJyx+FRxrUpzlOqrdRARPIJsbAUrT7qvHZ1m/dW+A2D3wD4WdRtBSBmCheGzwLCJTCkEtJ/imqJxJNChAeBARBoxBmM18Izq7bEX4zMyQQTUC60Px4enON/5gMzipsRrcf9b1uLKkts+KyrX1nSPVjSY1CSi0Ncyt9j/gQ9vyfl38n5WL+8H/Oder6V8gdwPoVuuR7zh+r5iZR/7mfKJw/b7phv1vMtlN/A+dh1ebQP5P/YR8vvRfllmE9Ioa5QlMO7206p0b7Ob41hpZJmjgSL1Ur4sV4anscwjDmTB1ruOLV+f4LLRcE6BNb0z90allASx0UMx/LdvyAMBulb10+DCrIWN2i7StdTpxkG5z+YOuGFFZo8Rup23iBMV21O4B5gKk0RvlIOvefyBX4FwWSaG+oheJg7ziKJdQ7SkSdhNtQqznrF2UhGyxhUsEpxfqt4DluTnPWIVYOo/sFEqgPeP0nvo8666LyRaNmP/xWeU+8U8pyajGeZIV9VXYF9wVH3ZDwZmOIWh3DSbRnJR972IRqW4xm38hlSSPjHhhLkgyInVJKd52ck/yuf5fK/fPbPWf0QudmM4UTSOetBWj+bzv8KKaLPVv04qiBOrvm+Wd3hVt6fww9oBfPR1Ge8V5BeA+j3OSNNineOG9noiZsUW4vnJ5+VcmCD6bTyTpzFT+qLmktXtemvYQPls1/T8VkFj5iAoSBwPk0pW3FpX58B17CxAces1tYfr3/VdiPfUCgk2yC+oQhntt58k003cXzjopuzOJP8HBLen/VsLvv5XPEl+/nQuoH7Hto99XtnTUtnp59Fx05F+2rTuQUsj6Jjhcw2rI1gG/4xLwIClyy3xf2D5PydeDwhteOJWtU2EaaaW5jjg4m4Xmo56NWT0HjY6JG7qeXH2juMeK5ZS55hzEZYVxJQmNEJk7xKzGcWaX4fIgKw21CwKcWzw5riDBCI7HpNUUogPlDkBx34FS2Wo4m451x2lBoQwCBdr1eg35qltQlzKgiwf4W0fENzOG8FPlFbRzpTsYiWtSfgH9hdeKpSt2Xum5XpEJ7NdrUcVbL+vGX49M5t5Om2w65Wia8xoX8FJizFl+3G/cJZZU+tyKyfuYV7IZyb/QNj4PnU8mA6vBewqwEHfAkoTfq2oXteFTCiGGDmK1mziUp6RC9pB5QE6VAYOtPIFGonMUDp+0kyaGpltWSIB3prF36RNof4IWMpkaV5q7Vwen3o7k2OlknQuhozFNsMS6UO6EPWJGSWOtBSdjzkRjN3W4G32yx22a0rvzHmBZS8ZcDbfaDkNfpNvTASonAuw2+kOA9rlMlzLOKTw45sajeisRxuz9jTcRtbVXVr5hpq1VwMNW5XNzsyyfTFOtcN9x60FcrRTcm5d+trmfJM85Cx2Qr6lNesaw6FU936CnNgtcyBFXYyNoP5fmZTjLXYSyZTpLwNWRczxxyI5pjxHB9Nyj8Vkef4xDLHw8/Kh8HIMn/TjvNvXLxdbHdkjJtmHeWZJpzWzCqrGxjdaSKvR0beK9ZRea8IZ+/MWqt7k+J8Rcxm2o+Sat405J7uOQWi9iojRwLtiYqybqQxfAeSYObH48zvG7Ve7MYKxXl15/XSV18vQ0Ln08DEFyHXizy+fz5TvintRtIP3I0aJ6Vgr9t/m+2PaJBUUMNvbGzSyKCnRk7aqXskLJfLt/PqqaE=
*/