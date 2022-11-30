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

#ifndef _BOOST_UBLAS_VECTOR_EXPRESSION_
#define _BOOST_UBLAS_VECTOR_EXPRESSION_

#include <boost/numeric/ublas/expression_types.hpp>


// Expression templates based on ideas of Todd Veldhuizen and Geoffrey Furnish
// Iterators based on ideas of Jeremy Siek
//
// Classes that model the Vector Expression concept

namespace boost { namespace numeric { namespace ublas {

    template<class E>
    class vector_reference:
        public vector_expression<vector_reference<E> > {

        typedef vector_reference<E> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<vector_reference<E> >::operator ();
#endif
        typedef typename E::size_type size_type;
        typedef typename E::difference_type difference_type;
        typedef typename E::value_type value_type;
        typedef typename E::const_reference const_reference;
        typedef typename boost::mpl::if_<boost::is_const<E>,
                                          typename E::const_reference,
                                          typename E::reference>::type reference;
        typedef E referred_type;
        typedef const self_type const_closure_type;
        typedef self_type closure_type;
        typedef typename E::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        explicit vector_reference (referred_type &e):
            e_ (e) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return expression ().size ();
        }

    public:
        // Expression accessors - const correct
        BOOST_UBLAS_INLINE
        const referred_type &expression () const {
            return e_;
        }
        BOOST_UBLAS_INLINE
        referred_type &expression () {
            return e_;
        }

    public:
        // Element access
#ifndef BOOST_UBLAS_REFERENCE_CONST_MEMBER
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return expression () (i);
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return expression () (i);
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return expression () [i];
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return expression () [i];
        }
#else
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) const {
            return expression () (i);
        }

        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) const {
            return expression () [i];
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        vector_reference &operator = (const vector_reference &v) {
            expression ().operator = (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_reference &operator = (const vector_expression<AE> &ae) {
            expression ().operator = (ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_reference &assign (const vector_expression<AE> &ae) {
            expression ().assign (ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_reference &operator += (const vector_expression<AE> &ae) {
            expression ().operator += (ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_reference &plus_assign (const vector_expression<AE> &ae) {
            expression ().plus_assign (ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_reference &operator -= (const vector_expression<AE> &ae) {
            expression ().operator -= (ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        vector_reference &minus_assign (const vector_expression<AE> &ae) {
            expression ().minus_assign (ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_reference &operator *= (const AT &at) {
            expression ().operator *= (at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        vector_reference &operator /= (const AT &at) {
            expression ().operator /= (at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (vector_reference &v) {
            expression ().swap (v.expression ());
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const vector_reference &vr) const {
            return &(*this).e_ == &vr.e_;
        }

        // Iterator types
        typedef typename E::const_iterator const_iterator;
        typedef typename boost::mpl::if_<boost::is_const<E>,
                                          typename E::const_iterator,
                                          typename E::iterator>::type iterator;

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
            return expression ().find (i);
        }
        BOOST_UBLAS_INLINE
        iterator find (size_type i) {
            return expression ().find (i);
        }

        // Iterator is the iterator of the referenced expression.

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return expression ().begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return expression ().end ();
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        BOOST_UBLAS_INLINE
        iterator begin () {
            return expression ().begin ();
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return expression ().end ();
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
        referred_type &e_;
    };


    template<class E, class F>
    class vector_unary:
        public vector_expression<vector_unary<E, F> > {

        typedef F functor_type;
        typedef typename boost::mpl::if_<boost::is_same<F, scalar_identity<typename E::value_type> >,
                                          E,
                                          const E>::type expression_type;
        typedef typename boost::mpl::if_<boost::is_const<expression_type>,
                                          typename E::const_closure_type,
                                          typename E::closure_type>::type expression_closure_type;
        typedef vector_unary<E, F> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<vector_unary<E, F> >::operator ();
#endif
        typedef typename E::size_type size_type;
        typedef typename E::difference_type difference_type;
        typedef typename F::result_type value_type;
        typedef value_type const_reference;
        typedef typename boost::mpl::if_<boost::is_same<F, scalar_identity<value_type> >,
                                          typename E::reference,
                                          value_type>::type reference;
        typedef const self_type const_closure_type;
        typedef self_type closure_type;
        typedef unknown_storage_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        // May be used as mutable expression.
        explicit vector_unary (expression_type &e):
            e_ (e) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return e_.size ();
        }

    public:
        // Expression accessors
        BOOST_UBLAS_INLINE
        const expression_closure_type &expression () const {
            return e_;
        }

    public:
        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return functor_type::apply (e_ (i));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            BOOST_STATIC_ASSERT ((boost::is_same<functor_type, scalar_identity<value_type > >::value));
            return e_ (i);
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return functor_type::apply (e_ [i]);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            BOOST_STATIC_ASSERT ((boost::is_same<functor_type, scalar_identity<value_type > >::value));
            return e_ [i];
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const vector_unary &vu) const {
            return (*this).expression ().same_closure (vu.expression ());
        }

        // Iterator types
    private:
        typedef typename E::const_iterator const_subiterator_type;
        typedef const value_type *const_pointer;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_const_iterator<const_closure_type, typename const_subiterator_type::iterator_category> const_iterator;
        typedef const_iterator iterator;
#else
        class const_iterator;
        typedef const_iterator iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            const_subiterator_type it (e_.find (i));
            return const_iterator (*this, it.index ());
#else
            return const_iterator (*this, e_.find (i));
#endif
        }

        // Iterator enhances the iterator of the referenced expression
        // with the unary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_unary>,
            public iterator_base_traits<typename E::const_iterator::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
        public:
            typedef typename E::const_iterator::iterator_category iterator_category;
            typedef typename vector_unary::difference_type difference_type;
            typedef typename vector_unary::value_type value_type;
            typedef typename vector_unary::const_reference reference;
            typedef typename vector_unary::const_pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &vu, const const_subiterator_type &it):
                container_const_reference<self_type> (vu), it_ (it) {}

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
                return functor_type::apply (*it_);
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

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;

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

    private:
        expression_closure_type e_;
    };

    template<class E, class F>
    struct vector_unary_traits {
        typedef vector_unary<E, F> expression_type;
//FIXME
// #ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
        typedef expression_type result_type;
// #else
//         typedef typename E::vector_temporary_type result_type;
// #endif
    };

    // (- v) [i] = - v [i]
    template<class E> 
    BOOST_UBLAS_INLINE
    typename vector_unary_traits<E, scalar_negate<typename E::value_type> >::result_type
    operator - (const vector_expression<E> &e) {
        typedef typename vector_unary_traits<E, scalar_negate<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }

    // (conj v) [i] = conj (v [i])
    template<class E> 
    BOOST_UBLAS_INLINE
    typename vector_unary_traits<E, scalar_conj<typename E::value_type> >::result_type
    conj (const vector_expression<E> &e) {
        typedef typename vector_unary_traits<E, scalar_conj<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }

    // (real v) [i] = real (v [i])
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_unary_traits<E, scalar_real<typename E::value_type> >::result_type
    real (const vector_expression<E> &e) {
        typedef typename vector_unary_traits<E, scalar_real<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }

    // (imag v) [i] = imag (v [i])
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_unary_traits<E, scalar_imag<typename E::value_type> >::result_type
    imag (const vector_expression<E> &e) {
        typedef typename vector_unary_traits<E, scalar_imag<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }

    // (trans v) [i] = v [i]
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_unary_traits<const E, scalar_identity<typename E::value_type> >::result_type
    trans (const vector_expression<E> &e) {
        typedef typename vector_unary_traits<const E, scalar_identity<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_unary_traits<E, scalar_identity<typename E::value_type> >::result_type
    trans (vector_expression<E> &e) {
        typedef typename vector_unary_traits<E, scalar_identity<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }

    // (herm v) [i] = conj (v [i])
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_unary_traits<E, scalar_conj<typename E::value_type> >::result_type
    herm (const vector_expression<E> &e) {
        typedef typename vector_unary_traits<E, scalar_conj<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }

    template<class E1, class E2, class F>
    class vector_binary:
        public vector_expression<vector_binary<E1, E2, F> > {

        typedef E1 expression1_type;
        typedef E2 expression2_type;
        typedef F functor_type;
        typedef typename E1::const_closure_type expression1_closure_type;
        typedef typename E2::const_closure_type expression2_closure_type;
        typedef vector_binary<E1, E2, F> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<vector_binary<E1, E2, F> >::operator ();
#endif
        typedef typename promote_traits<typename E1::size_type, typename E2::size_type>::promote_type size_type;
        typedef typename promote_traits<typename E1::difference_type, typename E2::difference_type>::promote_type difference_type;
        typedef typename F::result_type value_type;
        typedef value_type const_reference;
        typedef const_reference reference;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;
        typedef unknown_storage_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_binary (const expression1_type &e1, const expression2_type &e2):
            e1_ (e1), e2_ (e2) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const { 
            return BOOST_UBLAS_SAME (e1_.size (), e2_.size ()); 
        }

    private:
        // Accessors
        BOOST_UBLAS_INLINE
        const expression1_closure_type &expression1 () const {
            return e1_;
        }
        BOOST_UBLAS_INLINE
        const expression2_closure_type &expression2 () const {
            return e2_;
        }

    public:
        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return functor_type::apply (e1_ (i), e2_ (i));
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return functor_type::apply (e1_ [i], e2_ [i]);
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const vector_binary &vb) const {
            return (*this).expression1 ().same_closure (vb.expression1 ()) &&
                   (*this).expression2 ().same_closure (vb.expression2 ());
        }

        // Iterator types
    private:
        typedef typename E1::const_iterator const_subiterator1_type;
        typedef typename E2::const_iterator const_subiterator2_type;
        typedef const value_type *const_pointer;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef typename iterator_restrict_traits<typename const_subiterator1_type::iterator_category,
                                                  typename const_subiterator2_type::iterator_category>::iterator_category iterator_category;
        typedef indexed_const_iterator<const_closure_type, iterator_category> const_iterator;
        typedef const_iterator iterator;
#else
        class const_iterator;
        typedef const_iterator iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
            const_subiterator1_type it1 (e1_.find (i));
            const_subiterator1_type it1_end (e1_.find (size ()));
            const_subiterator2_type it2 (e2_.find (i));
            const_subiterator2_type it2_end (e2_.find (size ()));
            i = (std::min) (it1 != it1_end ? it1.index () : size (),
                          it2 != it2_end ? it2.index () : size ());
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, i);
#else
            return const_iterator (*this, i, it1, it1_end, it2, it2_end);
#endif
        }

        // Iterator merges the iterators of the referenced expressions and
        // enhances them with the binary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_binary>,
            public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
                                                                          typename E2::const_iterator::iterator_category>::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
        public:
            typedef typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
                                                      typename E2::const_iterator::iterator_category>::iterator_category iterator_category;
            typedef typename vector_binary::difference_type difference_type;
            typedef typename vector_binary::value_type value_type;
            typedef typename vector_binary::const_reference reference;
            typedef typename vector_binary::const_pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), i_ (), it1_ (), it1_end_ (), it2_ (), it2_end_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &vb, size_type i,
                            const const_subiterator1_type &it1, const const_subiterator1_type &it1_end,
                            const const_subiterator2_type &it2, const const_subiterator2_type &it2_end):
                container_const_reference<self_type> (vb), i_ (i), it1_ (it1), it1_end_ (it1_end), it2_ (it2), it2_end_ (it2_end) {}

        private: 
            // Dense specializations
            BOOST_UBLAS_INLINE
            void increment (dense_random_access_iterator_tag) {
                ++ i_; ++ it1_; ++ it2_;
            }
            BOOST_UBLAS_INLINE
            void decrement (dense_random_access_iterator_tag) {
                -- i_; -- it1_; -- it2_;
            }
            BOOST_UBLAS_INLINE
            void increment (dense_random_access_iterator_tag, difference_type n) {
                i_ += n; it1_ += n; it2_ += n;
            }
            BOOST_UBLAS_INLINE
            void decrement (dense_random_access_iterator_tag, difference_type n) {
                i_ -= n; it1_ -= n; it2_ -= n;
            }
            BOOST_UBLAS_INLINE
            value_type dereference (dense_random_access_iterator_tag) const {
                return functor_type::apply (*it1_, *it2_);
            }

            // Packed specializations
            BOOST_UBLAS_INLINE
            void increment (packed_random_access_iterator_tag) {
                if (it1_ != it1_end_)
                    if (it1_.index () <= i_)
                        ++ it1_;
                if (it2_ != it2_end_)
                    if (it2_.index () <= i_)
                        ++ it2_;
                ++ i_;
            }
            BOOST_UBLAS_INLINE
            void decrement (packed_random_access_iterator_tag) {
                if (it1_ != it1_end_)
                    if (i_ <= it1_.index ())
                        -- it1_;
                if (it2_ != it2_end_)
                    if (i_ <= it2_.index ())
                        -- it2_;
                -- i_;
            }
            BOOST_UBLAS_INLINE
            void increment (packed_random_access_iterator_tag, difference_type n) {
                while (n > 0) {
                    increment (packed_random_access_iterator_tag ());
                    --n;
                }
                while (n < 0) {
                    decrement (packed_random_access_iterator_tag ());
                    ++n;
                }
            }
            BOOST_UBLAS_INLINE
            void decrement (packed_random_access_iterator_tag, difference_type n) {
                while (n > 0) {
                    decrement (packed_random_access_iterator_tag ());
                    --n;
                }
                while (n < 0) {
                    increment (packed_random_access_iterator_tag ());
                    ++n;
                }
            }
            BOOST_UBLAS_INLINE
            value_type dereference (packed_random_access_iterator_tag) const {
                typename E1::value_type t1 = typename E1::value_type/*zero*/();
                if (it1_ != it1_end_)
                    if (it1_.index () == i_)
                        t1 = *it1_;
                typename E2::value_type t2 = typename E2::value_type/*zero*/();
                if (it2_ != it2_end_)
                    if (it2_.index () == i_)
                        t2 = *it2_;
                return functor_type::apply (t1, t2);
            }

            // Sparse specializations
            BOOST_UBLAS_INLINE
            void increment (sparse_bidirectional_iterator_tag) {
                size_type index1 = (*this) ().size ();
                if (it1_ != it1_end_) {
                    if  (it1_.index () <= i_)
                        ++ it1_;
                    if (it1_ != it1_end_)
                        index1 = it1_.index ();
                }
                size_type index2 = (*this) ().size ();
                if (it2_ != it2_end_) {
                    if (it2_.index () <= i_)
                        ++ it2_;
                    if (it2_ != it2_end_)
                        index2 = it2_.index ();
                }
                i_ = (std::min) (index1, index2);
            }
            BOOST_UBLAS_INLINE
            void decrement (sparse_bidirectional_iterator_tag) {
                size_type index1 = (*this) ().size ();
                if (it1_ != it1_end_) {
                    if (i_ <= it1_.index ())
                        -- it1_;
                    if (it1_ != it1_end_)
                        index1 = it1_.index ();
                }
                size_type index2 = (*this) ().size ();
                if (it2_ != it2_end_) {
                    if (i_ <= it2_.index ())
                        -- it2_;
                    if (it2_ != it2_end_)
                        index2 = it2_.index ();
                }
                i_ = (std::max) (index1, index2);
            }
            BOOST_UBLAS_INLINE
            void increment (sparse_bidirectional_iterator_tag, difference_type n) {
                while (n > 0) {
                    increment (sparse_bidirectional_iterator_tag ());
                    --n;
                }
                while (n < 0) {
                    decrement (sparse_bidirectional_iterator_tag ());
                    ++n;
                }
            }
            BOOST_UBLAS_INLINE
            void decrement (sparse_bidirectional_iterator_tag, difference_type n) {
                while (n > 0) {
                    decrement (sparse_bidirectional_iterator_tag ());
                    --n;
                }
                while (n < 0) {
                    increment (sparse_bidirectional_iterator_tag ());
                    ++n;
                }
            }
            BOOST_UBLAS_INLINE
            value_type dereference (sparse_bidirectional_iterator_tag) const {
                typename E1::value_type t1 = typename E1::value_type/*zero*/();
                if (it1_ != it1_end_)
                    if (it1_.index () == i_)
                        t1 = *it1_;
                typename E2::value_type t2 = typename E2::value_type/*zero*/();
                if (it2_ != it2_end_)
                    if (it2_.index () == i_)
                        t2 = *it2_;
                return static_cast<value_type>(functor_type::apply (t1, t2));
            }

        public: 
            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                increment (iterator_category ());
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                decrement (iterator_category ());
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                increment (iterator_category (), n);
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                decrement (iterator_category (), n);
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return index () - it.index ();
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                return dereference (iterator_category ());
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return i_;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                i_ = it.i_;
                it1_ = it.it1_;
                it1_end_ = it.it1_end_;
                it2_ = it.it2_;
                it2_end_ = it.it2_end_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return index () == it.index ();
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                return index () < it.index ();
            }

        private:
            size_type i_;
            const_subiterator1_type it1_;
            const_subiterator1_type it1_end_;
            const_subiterator2_type it2_;
            const_subiterator2_type it2_end_;
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

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;

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

    private:
        expression1_closure_type e1_;
        expression2_closure_type e2_;
    };

    template<class E1, class E2, class F>
    struct vector_binary_traits {
        typedef vector_binary<E1, E2, F> expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
        typedef expression_type result_type; 
#else
        typedef typename E1::vector_temporary_type result_type;
#endif
    };

    // (v1 + v2) [i] = v1 [i] + v2 [i]
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    typename vector_binary_traits<E1, E2, scalar_plus<typename E1::value_type, 
                                                      typename E2::value_type> >::result_type
    operator + (const vector_expression<E1> &e1,
                const vector_expression<E2> &e2) {
        typedef typename vector_binary_traits<E1, E2, scalar_plus<typename E1::value_type,
                                                                              typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1 (), e2 ());
    }

    // (v1 - v2) [i] = v1 [i] - v2 [i]
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    typename vector_binary_traits<E1, E2, scalar_minus<typename E1::value_type,
                                                       typename E2::value_type> >::result_type
    operator - (const vector_expression<E1> &e1,
                const vector_expression<E2> &e2) {
        typedef typename vector_binary_traits<E1, E2, scalar_minus<typename E1::value_type,
                                                                               typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1 (), e2 ());
    }

    // (v1 * v2) [i] = v1 [i] * v2 [i]
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    typename vector_binary_traits<E1, E2, scalar_multiplies<typename E1::value_type,
                                                            typename E2::value_type> >::result_type
    element_prod (const vector_expression<E1> &e1,
                  const vector_expression<E2> &e2) {
        typedef typename vector_binary_traits<E1, E2, scalar_multiplies<typename E1::value_type,
                                                                                    typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1 (), e2 ());
    }

    // (v1 / v2) [i] = v1 [i] / v2 [i]
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    typename vector_binary_traits<E1, E2, scalar_divides<typename E1::value_type,
                                                         typename E2::value_type> >::result_type
    element_div (const vector_expression<E1> &e1,
                 const vector_expression<E2> &e2) {
        typedef typename vector_binary_traits<E1, E2, scalar_divides<typename E1::value_type,
                                                                                 typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1 (), e2 ());
    }


    template<class E1, class E2, class F>
    class vector_binary_scalar1:
        public vector_expression<vector_binary_scalar1<E1, E2, F> > {

        typedef F functor_type;
        typedef E1 expression1_type;
        typedef E2 expression2_type;
    public:
        typedef const E1& expression1_closure_type;
        typedef typename E2::const_closure_type expression2_closure_type;
    private:
        typedef vector_binary_scalar1<E1, E2, F> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<vector_binary_scalar1<E1, E2, F> >::operator ();
#endif
        typedef typename E2::size_type size_type;
        typedef typename E2::difference_type difference_type;
        typedef typename F::result_type value_type;
        typedef value_type const_reference;
        typedef const_reference reference;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;
        typedef unknown_storage_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_binary_scalar1 (const expression1_type &e1, const expression2_type &e2):
            e1_ (e1), e2_ (e2) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return e2_.size ();
        }

    public:
        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return functor_type::apply (e1_, e2_ (i));
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return functor_type::apply (e1_, e2_ [i]);
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const vector_binary_scalar1 &vbs1) const {
            return &e1_ == &(vbs1.e1_) &&
                   (*this).e2_.same_closure (vbs1.e2_);
        }

        // Iterator types
    private:
        typedef expression1_type const_subiterator1_type;
        typedef typename expression2_type::const_iterator const_subiterator2_type;
        typedef const value_type *const_pointer;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_const_iterator<const_closure_type, typename const_subiterator2_type::iterator_category> const_iterator;
        typedef const_iterator iterator;
#else
        class const_iterator;
        typedef const_iterator iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            const_subiterator2_type it (e2_.find (i));
            return const_iterator (*this, it.index ());
#else
            return const_iterator (*this, const_subiterator1_type (e1_), e2_.find (i));
#endif
        }

        // Iterator enhances the iterator of the referenced vector expression
        // with the binary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_binary_scalar1>,
            public iterator_base_traits<typename E2::const_iterator::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
        public:
            typedef typename E2::const_iterator::iterator_category iterator_category;
            typedef typename vector_binary_scalar1::difference_type difference_type;
            typedef typename vector_binary_scalar1::value_type value_type;
            typedef typename vector_binary_scalar1::const_reference reference;
            typedef typename vector_binary_scalar1::const_pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &vbs, const const_subiterator1_type &it1, const const_subiterator2_type &it2):
                container_const_reference<self_type> (vbs), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                // FIXME we shouldn't compare floats
                // BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                return functor_type::apply (it1_, *it2_);
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it2_.index ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                // FIXME we shouldn't compare floats
                // BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                // FIXME we shouldn't compare floats
                // BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
                return it2_ < it.it2_;
            }

        private:
            const_subiterator1_type it1_;
            const_subiterator2_type it2_;
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

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;

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
            return end ();
        }

    private:
        expression1_closure_type e1_;
        expression2_closure_type e2_;
    };

    template<class E1, class E2, class F>
    struct vector_binary_scalar1_traits {
        typedef vector_binary_scalar1<E1, E2, F> expression_type;   // allow E1 to be builtin type
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
        typedef expression_type result_type;
#else
        typedef typename E2::vector_temporary_type result_type;
#endif
    };

    // (t * v) [i] = t * v [i]
    template<class T1, class E2>
    BOOST_UBLAS_INLINE
    typename boost::enable_if< is_convertible<T1, typename E2::value_type >,
    typename vector_binary_scalar1_traits<const T1, E2, scalar_multiplies<T1, typename E2::value_type> >::result_type
    >::type
    operator * (const T1 &e1,
                const vector_expression<E2> &e2) {
        typedef typename vector_binary_scalar1_traits<const T1, E2, scalar_multiplies<T1, typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1, e2 ());
    }


    template<class E1, class E2, class F>
    class vector_binary_scalar2:
        public vector_expression<vector_binary_scalar2<E1, E2, F> > {

        typedef F functor_type;
        typedef E1 expression1_type;
        typedef E2 expression2_type;
        typedef typename E1::const_closure_type expression1_closure_type;
        typedef const E2& expression2_closure_type;
        typedef vector_binary_scalar2<E1, E2, F> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<vector_binary_scalar2<E1, E2, F> >::operator ();
#endif
        typedef typename E1::size_type size_type;
        typedef typename E1::difference_type difference_type;
        typedef typename F::result_type value_type;
        typedef value_type const_reference;
        typedef const_reference reference;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;
        typedef unknown_storage_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_binary_scalar2 (const expression1_type &e1, const expression2_type &e2):
            e1_ (e1), e2_ (e2) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return e1_.size (); 
        }

    public:
        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return functor_type::apply (e1_ (i), e2_);
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return functor_type::apply (e1_ [i], e2_);
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const vector_binary_scalar2 &vbs2) const {
            return (*this).e1_.same_closure (vbs2.e1_) &&
                   &e2_ == &(vbs2.e2_);
        }

        // Iterator types
    private:
        typedef typename expression1_type::const_iterator const_subiterator1_type;
        typedef expression2_type const_subiterator2_type;
        typedef const value_type *const_pointer;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_const_iterator<const_closure_type, typename const_subiterator2_type::iterator_category> const_iterator;
        typedef const_iterator iterator;
#else
        class const_iterator;
        typedef const_iterator iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            const_subiterator1_type it (e1_.find (i));
            return const_iterator (*this, it.index ());
#else
            return const_iterator (*this, e1_.find (i), const_subiterator2_type (e2_));
#endif
        }

        // Iterator enhances the iterator of the referenced vector expression
        // with the binary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
        class const_iterator:
            public container_const_reference<vector_binary_scalar2>,
            public iterator_base_traits<typename E1::const_iterator::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
        public:
            typedef typename E1::const_iterator::iterator_category iterator_category;
            typedef typename vector_binary_scalar2::difference_type difference_type;
            typedef typename vector_binary_scalar2::value_type value_type;
            typedef typename vector_binary_scalar2::const_reference reference;
            typedef typename vector_binary_scalar2::const_pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &vbs, const const_subiterator1_type &it1, const const_subiterator2_type &it2):
                container_const_reference<self_type> (vbs), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                // FIXME we shouldn't compare floats
                // BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                return functor_type::apply (*it1_, it2_);
            }
            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it1_.index ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                // FIXME we shouldn't compare floats
                // BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ == it.it1_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
                // FIXME we shouldn't compare floats
                // BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
                return it1_ < it.it1_;
            }

        private:
            const_subiterator1_type it1_;
            const_subiterator2_type it2_;
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

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;

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

    private:
        expression1_closure_type e1_;
        expression2_closure_type e2_;
    };

    template<class E1, class E2, class F>
    struct vector_binary_scalar2_traits {
        typedef vector_binary_scalar2<E1, E2, F> expression_type;   // allow E2 to be builtin type
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
        typedef expression_type result_type;
#else
        typedef typename E1::vector_temporary_type result_type;
#endif
    };

    // (v * t) [i] = v [i] * t
    template<class E1, class T2>
    BOOST_UBLAS_INLINE
    typename boost::enable_if< is_convertible<T2, typename E1::value_type >,
    typename vector_binary_scalar2_traits<E1, const T2, scalar_multiplies<typename E1::value_type, T2> >::result_type
    >::type
    operator * (const vector_expression<E1> &e1,
                const T2 &e2) {
        typedef typename vector_binary_scalar2_traits<E1, const T2, scalar_multiplies<typename E1::value_type, T2> >::expression_type expression_type;
        return expression_type (e1 (), e2);
    }

    // (v / t) [i] = v [i] / t
    template<class E1, class T2>
    BOOST_UBLAS_INLINE
    typename boost::enable_if< is_convertible<T2, typename E1::value_type >,
    typename vector_binary_scalar2_traits<E1, const T2, scalar_divides<typename E1::value_type, T2> >::result_type
    >::type
    operator / (const vector_expression<E1> &e1,
                const T2 &e2) {
        typedef typename vector_binary_scalar2_traits<E1, const T2, scalar_divides<typename E1::value_type, T2> >::expression_type expression_type;
        return expression_type (e1 (), e2);
    }


    template<class E, class F>
    class vector_scalar_unary:
        public scalar_expression<vector_scalar_unary<E, F> > {

        typedef E expression_type;
        typedef F functor_type;
        typedef typename E::const_closure_type expression_closure_type;
        typedef typename E::const_iterator::iterator_category iterator_category;
        typedef vector_scalar_unary<E, F> self_type;
    public:
        typedef typename F::result_type value_type;
        typedef typename E::difference_type difference_type;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;
        typedef unknown_storage_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        explicit vector_scalar_unary (const expression_type &e):
            e_ (e) {}

    private:
        // Expression accessors
        BOOST_UBLAS_INLINE
        const expression_closure_type &expression () const {
            return e_;
        }

    public:
        BOOST_UBLAS_INLINE
        operator value_type () const {
            return evaluate (iterator_category ());
        }

    private:
        // Dense random access specialization
        BOOST_UBLAS_INLINE
        value_type evaluate (dense_random_access_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INDEXING
            return functor_type::apply (e_);
#elif BOOST_UBLAS_USE_ITERATING
            difference_type size = e_.size ();
            return functor_type::apply (size, e_.begin ());
#else
            difference_type size = e_.size ();
            if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
                return functor_type::apply (size, e_.begin ());
            else
                return functor_type::apply (e_);
#endif
        }

        // Packed bidirectional specialization
        BOOST_UBLAS_INLINE
        value_type evaluate (packed_random_access_iterator_tag) const {
            return functor_type::apply (e_.begin (), e_.end ());
        }

        // Sparse bidirectional specialization
        BOOST_UBLAS_INLINE
        value_type evaluate (sparse_bidirectional_iterator_tag) const {
            return functor_type::apply (e_.begin (), e_.end ());
        }

    private:
        expression_closure_type e_;
    };

    template<class E, class F>
    struct vector_scalar_unary_traits {
        typedef vector_scalar_unary<E, F> expression_type;
#if !defined (BOOST_UBLAS_SIMPLE_ET_DEBUG) && defined (BOOST_UBLAS_USE_SCALAR_ET)
// FIXME don't define USE_SCALAR_ET other then for testing
// They do not work for complex types
         typedef expression_type result_type;
#else
         typedef typename F::result_type result_type;
#endif
    };

    // sum v = sum (v [i])
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_scalar_unary_traits<E, vector_sum<E> >::result_type
    sum (const vector_expression<E> &e) {
        typedef typename vector_scalar_unary_traits<E, vector_sum<E> >::expression_type expression_type;
        return expression_type (e ());
    }

    // real: norm_1 v = sum (abs (v [i]))
    // complex: norm_1 v = sum (abs (real (v [i])) + abs (imag (v [i])))
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_scalar_unary_traits<E, vector_norm_1<E> >::result_type
    norm_1 (const vector_expression<E> &e) {
        typedef typename vector_scalar_unary_traits<E, vector_norm_1<E> >::expression_type expression_type;
        return expression_type (e ());
    }

    // real: norm_2 v = sqrt (sum (v [i] * v [i]))
    // complex: norm_2 v = sqrt (sum (v [i] * conj (v [i])))
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_scalar_unary_traits<E, vector_norm_2<E> >::result_type
    norm_2 (const vector_expression<E> &e) {
        typedef typename vector_scalar_unary_traits<E, vector_norm_2<E> >::expression_type expression_type;
        return expression_type (e ());
    }

    // real: norm_2_square v = sum(v [i] * v [i])
    // complex: norm_2_square v = sum(v [i] * conj (v [i]))
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_scalar_unary_traits<E, vector_norm_2_square<E> >::result_type
    norm_2_square (const vector_expression<E> &e) {
        typedef typename vector_scalar_unary_traits<E, vector_norm_2_square<E> >::expression_type expression_type;
        return expression_type (e ());
    }

    // real: norm_inf v = maximum (abs (v [i]))
    // complex: norm_inf v = maximum (maximum (abs (real (v [i])), abs (imag (v [i]))))
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_scalar_unary_traits<E, vector_norm_inf<E> >::result_type
    norm_inf (const vector_expression<E> &e) {
        typedef typename vector_scalar_unary_traits<E, vector_norm_inf<E> >::expression_type expression_type;
        return expression_type (e ());
    }

    // real: index_norm_inf v = minimum (i: abs (v [i]) == maximum (abs (v [i])))
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_scalar_unary_traits<E, vector_index_norm_inf<E> >::result_type
    index_norm_inf (const vector_expression<E> &e) {
        typedef typename vector_scalar_unary_traits<E, vector_index_norm_inf<E> >::expression_type expression_type;
        return expression_type (e ());
    }

    template<class E1, class E2, class F>
    class vector_scalar_binary:
        public scalar_expression<vector_scalar_binary<E1, E2, F> > {

        typedef E1 expression1_type;
        typedef E2 expression2_type;
        typedef F functor_type;
        typedef typename E1::const_closure_type expression1_closure_type;
        typedef typename E2::const_closure_type expression2_closure_type;
        typedef typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
                                                  typename E2::const_iterator::iterator_category>::iterator_category iterator_category;
        typedef vector_scalar_binary<E1, E2, F> self_type;
    public:
        static const unsigned complexity = 1;
        typedef typename F::result_type value_type;
        typedef typename E1::difference_type difference_type;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;
        typedef unknown_storage_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        vector_scalar_binary (const expression1_type &e1, const expression2_type  &e2):
            e1_ (e1), e2_ (e2) {}

    private:
        // Accessors
        BOOST_UBLAS_INLINE
        const expression1_closure_type &expression1 () const {
            return e1_;
        }
        BOOST_UBLAS_INLINE
        const expression2_closure_type &expression2 () const {
            return e2_;
        }

    public:
        BOOST_UBLAS_INLINE
        operator value_type () const {
            return evaluate (iterator_category ());
        }

    private:
        // Dense random access specialization
        BOOST_UBLAS_INLINE
        value_type evaluate (dense_random_access_iterator_tag) const {
            BOOST_UBLAS_CHECK (e1_.size () == e2_.size (), external_logic());
#ifdef BOOST_UBLAS_USE_INDEXING
            return functor_type::apply (e1_, e2_);
#elif BOOST_UBLAS_USE_ITERATING
            difference_type size = BOOST_UBLAS_SAME (e1_.size (), e2_.size ());
            return functor_type::apply (size, e1_.begin (), e2_.begin ());
#else
            difference_type size = BOOST_UBLAS_SAME (e1_.size (), e2_.size ());
            if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
                return functor_type::apply (size, e1_.begin (), e2_.begin ());
            else
                return functor_type::apply (e1_, e2_);
#endif
        }

        // Packed bidirectional specialization
        BOOST_UBLAS_INLINE
        value_type evaluate (packed_random_access_iterator_tag) const {
            BOOST_UBLAS_CHECK (e1_.size () == e2_.size (), external_logic());
            return functor_type::apply (e1_.begin (), e1_.end (), e2_.begin (), e2_.end ());
        }

        // Sparse bidirectional specialization
        BOOST_UBLAS_INLINE
        value_type evaluate (sparse_bidirectional_iterator_tag) const {
            BOOST_UBLAS_CHECK (e1_.size () == e2_.size (), external_logic());
            return functor_type::apply (e1_.begin (), e1_.end (), e2_.begin (), e2_.end (), sparse_bidirectional_iterator_tag ());
        }

    private:
        expression1_closure_type e1_;
        expression2_closure_type e2_;
    };

    template<class E1, class E2, class F>
    struct vector_scalar_binary_traits {
        typedef vector_scalar_binary<E1, E2, F> expression_type;
#if !defined (BOOST_UBLAS_SIMPLE_ET_DEBUG) && defined (BOOST_UBLAS_USE_SCALAR_ET)
// FIXME don't define USE_SCALAR_ET other then for testing
// They do not work for complex types
        typedef expression_type result_type;
#else
        typedef typename F::result_type result_type;
#endif
    };

    // inner_prod (v1, v2) = sum (v1 [i] * v2 [i])
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    typename vector_scalar_binary_traits<E1, E2, vector_inner_prod<E1, E2,
                                                                   typename promote_traits<typename E1::value_type,
                                                                                           typename E2::value_type>::promote_type> >::result_type
    inner_prod (const vector_expression<E1> &e1,
                const vector_expression<E2> &e2) {
        typedef typename vector_scalar_binary_traits<E1, E2, vector_inner_prod<E1, E2,
                                                                   typename promote_traits<typename E1::value_type,
                                                                                           typename E2::value_type>::promote_type> >::expression_type expression_type;
        return expression_type (e1 (), e2 ());
    }

    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    typename vector_scalar_binary_traits<E1, E2, vector_inner_prod<E1, E2,
                                                                   typename type_traits<typename promote_traits<typename E1::value_type,
                                                                                                                typename E2::value_type>::promote_type>::precision_type> >::result_type
    prec_inner_prod (const vector_expression<E1> &e1,
                     const vector_expression<E2> &e2) {
        typedef typename vector_scalar_binary_traits<E1, E2, vector_inner_prod<E1, E2,
                                                                   typename type_traits<typename promote_traits<typename E1::value_type,
                                                                                                                typename E2::value_type>::promote_type>::precision_type> >::expression_type expression_type;
        return expression_type (e1 (), e2 ());
    }

}}}

#endif

/* vector_expression.hpp
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
*/