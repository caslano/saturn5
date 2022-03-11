//  Copyright (c) 2000-2013
//  Joerg Walter, Mathias Koch. David Bellot
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//
#ifndef _BOOST_UBLAS_EXPRESSION_TYPE_
#define _BOOST_UBLAS_EXPRESSION_TYPE_

#include <boost/numeric/ublas/exception.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublas/functional.hpp>


// Expression templates based on ideas of Todd Veldhuizen and Geoffrey Furnish
// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    /** \brief Base class for uBLAS statically derived expressions using the the Barton Nackman trick
     *
     * This is a NonAssignable class
     * Directly implement nonassignable - simplifes debugging call trace!
     * 
     * \tparam E an expression type
     */
    template<class E>
    class ublas_expression {
    public:
        typedef E expression_type;
        /* E can be an incomplete type - to define the following we would need more template arguments
        typedef typename E::type_category type_category;
        typedef typename E::value_type value_type;
        */
        
    protected:
        ublas_expression () {}
        ~ublas_expression () {}
    private:
        const ublas_expression& operator= (const ublas_expression &);
    };


    /** \brief Base class for Scalar Expression models
     *
     * It does not model the Scalar Expression concept but all derived types should.
     * The class defines a common base type and some common interface for all statically 
     * derived Scalar Expression classes.
     *
     * We implement the casts to the statically derived type.
     *
     * \tparam E an expression type
     */
    template<class E>
    class scalar_expression:
        public ublas_expression<E> {
    public:
        typedef E expression_type;
        typedef scalar_tag type_category;

        BOOST_UBLAS_INLINE
        const expression_type &operator () () const {
            return *static_cast<const expression_type *> (this);
        }
        BOOST_UBLAS_INLINE
        expression_type &operator () () {
            return *static_cast<expression_type *> (this);
        }
    };

    template<class T>
    class scalar_reference:
        public scalar_expression<scalar_reference<T> > {

        typedef scalar_reference<T> self_type;
    public:
        typedef T value_type;
        typedef const value_type &const_reference;
        typedef typename boost::mpl::if_<boost::is_const<T>,
                                          const_reference,
                                          value_type &>::type reference;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        explicit scalar_reference (reference t):
            t_ (t) {}

        // Conversion
        BOOST_UBLAS_INLINE
        operator value_type () const {
            return t_;
        }

        // Assignment
        BOOST_UBLAS_INLINE
        scalar_reference &operator = (const scalar_reference &s) {
            t_ = s.t_;
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        scalar_reference &operator = (const scalar_expression<AE> &ae) {
            t_ = ae;
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const scalar_reference &sr) const {
            return &t_ == &sr.t_;
        }

    private:
        reference t_;
    };

    template<class T>
    class scalar_value:
        public scalar_expression<scalar_value<T> > {

        typedef scalar_value<T> self_type;
    public:
        typedef T value_type;
        typedef const value_type &const_reference;
        typedef typename boost::mpl::if_<boost::is_const<T>,
                                          const_reference,
                                          value_type &>::type reference;
        typedef const scalar_reference<const self_type> const_closure_type;
        typedef scalar_reference<self_type> closure_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        scalar_value ():
            t_ () {}
        BOOST_UBLAS_INLINE
        scalar_value (const value_type &t):
            t_ (t) {}

        BOOST_UBLAS_INLINE
        operator value_type () const {
            return t_;
        }

        // Assignment
        BOOST_UBLAS_INLINE
        scalar_value &operator = (const scalar_value &s) {
            t_ = s.t_;
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        scalar_value &operator = (const scalar_expression<AE> &ae) {
            t_ = ae;
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const scalar_value &sv) const {
            return this == &sv;    // self closing on instances value
        }

    private:
        value_type t_;
    };


    /** \brief Base class for Vector Expression models
     *
     * it does not model the Vector Expression concept but all derived types should.
     * The class defines a common base type and some common interface for all
     * statically derived Vector Expression classes.
     * We implement the casts to the statically derived type.
     */
    template<class E>
    class vector_expression:
        public ublas_expression<E> {
    public:
        static const unsigned complexity = 0;
        typedef E expression_type;
        typedef vector_tag type_category;
        /* E can be an incomplete type - to define the following we would need more template arguments
        typedef typename E::size_type size_type;
        */
 
        BOOST_UBLAS_INLINE
        const expression_type &operator () () const {
            return *static_cast<const expression_type *> (this);
        }
        BOOST_UBLAS_INLINE
        expression_type &operator () () {
            return *static_cast<expression_type *> (this);
        }

#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
    private:
        // projection types
        typedef vector_range<E> vector_range_type;
        typedef vector_range<const E> const_vector_range_type;
        typedef vector_slice<E> vector_slice_type;
        typedef vector_slice<const E> const_vector_slice_type;
        // vector_indirect_type will depend on the A template parameter 
        typedef basic_range<> default_range;    // required to avoid range/slice name confusion
        typedef basic_slice<> default_slice;
   public:
        BOOST_UBLAS_INLINE
        const_vector_range_type operator () (const default_range &r) const {
            return const_vector_range_type (operator () (), r);
        }
        BOOST_UBLAS_INLINE
        vector_range_type operator () (const default_range &r) {
            return vector_range_type (operator () (), r);
        }
        BOOST_UBLAS_INLINE
        const_vector_slice_type operator () (const default_slice &s) const {
            return const_vector_slice_type (operator () (), s);
        }
        BOOST_UBLAS_INLINE
        vector_slice_type operator () (const default_slice &s) {
            return vector_slice_type (operator () (), s);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        const vector_indirect<const E, indirect_array<A> > operator () (const indirect_array<A> &ia) const {
            return vector_indirect<const E, indirect_array<A> >  (operator () (), ia);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        vector_indirect<E, indirect_array<A> > operator () (const indirect_array<A> &ia) {
            return vector_indirect<E, indirect_array<A> > (operator () (), ia);
        }

        BOOST_UBLAS_INLINE
        const_vector_range_type project (const default_range &r) const {
            return const_vector_range_type (operator () (), r);
        }
        BOOST_UBLAS_INLINE
        vector_range_type project (const default_range &r) {
            return vector_range_type (operator () (), r);
        }
        BOOST_UBLAS_INLINE
        const_vector_slice_type project (const default_slice &s) const {
            return const_vector_slice_type (operator () (), s);
        }
        BOOST_UBLAS_INLINE
        vector_slice_type project (const default_slice &s) {
            return vector_slice_type (operator () (), s);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        const vector_indirect<const E, indirect_array<A> > project (const indirect_array<A> &ia) const {
            return vector_indirect<const E, indirect_array<A> > (operator () (), ia);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        vector_indirect<E, indirect_array<A> > project (const indirect_array<A> &ia) {
            return vector_indirect<E, indirect_array<A> > (operator () (), ia);
        }
#endif
    };

    /** \brief Base class for Vector container models
     *
     * it does not model the Vector concept but all derived types should.
     * The class defines a common base type and some common interface for all
     * statically derived Vector classes
     * We implement the casts to the statically derived type.
     */
    template<class C>
    class vector_container:
        public vector_expression<C> {
    public:
        static const unsigned complexity = 0;
        typedef C container_type;
        typedef vector_tag type_category;
 
        BOOST_UBLAS_INLINE
        const container_type &operator () () const {
            return *static_cast<const container_type *> (this);
        }
        BOOST_UBLAS_INLINE
        container_type &operator () () {
            return *static_cast<container_type *> (this);
        }

#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<C>::operator ();
#endif
    };


    /** \brief Base class for Matrix Expression models
     *
     * it does not model the Matrix Expression concept but all derived types should.
     * The class defines a common base type and some common interface for all
     * statically derived Matrix Expression classes
     * We implement the casts to the statically derived type.
     */
    template<class E>
    class matrix_expression:
        public ublas_expression<E> {
    private:
        typedef matrix_expression<E> self_type;
    public:
        static const unsigned complexity = 0;
        typedef E expression_type;
        typedef matrix_tag type_category;
        /* E can be an incomplete type - to define the following we would need more template arguments
        typedef typename E::size_type size_type;
        */

        BOOST_UBLAS_INLINE
        const expression_type &operator () () const {
            return *static_cast<const expression_type *> (this);
        }
        BOOST_UBLAS_INLINE
        expression_type &operator () () {
            return *static_cast<expression_type *> (this);
        }

#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
    private:
        // projection types
        typedef vector_range<E> vector_range_type;
        typedef const vector_range<const E> const_vector_range_type;
        typedef vector_slice<E> vector_slice_type;
        typedef const vector_slice<const E> const_vector_slice_type;
        typedef matrix_row<E> matrix_row_type;
        typedef const matrix_row<const E> const_matrix_row_type;
        typedef matrix_column<E> matrix_column_type;
        typedef const  matrix_column<const E> const_matrix_column_type;
        typedef matrix_range<E> matrix_range_type;
        typedef const matrix_range<const E> const_matrix_range_type;
        typedef matrix_slice<E> matrix_slice_type;
        typedef const matrix_slice<const E> const_matrix_slice_type;
        // matrix_indirect_type will depend on the A template parameter 
        typedef basic_range<> default_range;    // required to avoid range/slice name confusion
        typedef basic_slice<> default_slice;

    public:
        BOOST_UBLAS_INLINE
        const_matrix_row_type operator [] (std::size_t i) const {
            return const_matrix_row_type (operator () (), i);
        }
        BOOST_UBLAS_INLINE
        matrix_row_type operator [] (std::size_t i) {
            return matrix_row_type (operator () (), i);
        }
        BOOST_UBLAS_INLINE
        const_matrix_row_type row (std::size_t i) const {
            return const_matrix_row_type (operator () (), i);
        }
        BOOST_UBLAS_INLINE
        matrix_row_type row (std::size_t i) {
            return matrix_row_type (operator () (), i);
        }
        BOOST_UBLAS_INLINE
        const_matrix_column_type column (std::size_t j) const {
            return const_matrix_column_type (operator () (), j);
        }
        BOOST_UBLAS_INLINE
        matrix_column_type column (std::size_t j) {
            return matrix_column_type (operator () (), j);
        }

        BOOST_UBLAS_INLINE
        const_matrix_range_type operator () (const default_range &r1, const default_range &r2) const {
            return const_matrix_range_type (operator () (), r1, r2);
        }
        BOOST_UBLAS_INLINE
        matrix_range_type operator () (const default_range &r1, const default_range &r2) {
            return matrix_range_type (operator () (), r1, r2);
        }
        BOOST_UBLAS_INLINE
        const_matrix_slice_type operator () (const default_slice &s1, const default_slice &s2) const {
            return const_matrix_slice_type (operator () (), s1, s2);
        }
        BOOST_UBLAS_INLINE
        matrix_slice_type operator () (const default_slice &s1, const default_slice &s2) {
            return matrix_slice_type (operator () (), s1, s2);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        const matrix_indirect<const E, indirect_array<A> > operator () (const indirect_array<A> &ia1, const indirect_array<A> &ia2) const {
            return matrix_indirect<const E, indirect_array<A> > (operator () (), ia1, ia2);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        matrix_indirect<E, indirect_array<A> > operator () (const indirect_array<A> &ia1, const indirect_array<A> &ia2) {
            return matrix_indirect<E, indirect_array<A> > (operator () (), ia1, ia2);
        }

        BOOST_UBLAS_INLINE
        const_matrix_range_type project (const default_range &r1, const default_range &r2) const {
            return const_matrix_range_type (operator () (), r1, r2);
        }
        BOOST_UBLAS_INLINE
        matrix_range_type project (const default_range &r1, const default_range &r2) {
            return matrix_range_type (operator () (), r1, r2);
        }
        BOOST_UBLAS_INLINE
        const_matrix_slice_type project (const default_slice &s1, const default_slice &s2) const {
            return const_matrix_slice_type (operator () (), s1, s2);
        }
        BOOST_UBLAS_INLINE
        matrix_slice_type project (const default_slice &s1, const default_slice &s2) {
            return matrix_slice_type (operator () (), s1, s2);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        const matrix_indirect<const E, indirect_array<A> > project (const indirect_array<A> &ia1, const indirect_array<A> &ia2) const {
            return matrix_indirect<const E, indirect_array<A> > (operator () (), ia1, ia2);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        matrix_indirect<E, indirect_array<A> > project (const indirect_array<A> &ia1, const indirect_array<A> &ia2) {
            return matrix_indirect<E, indirect_array<A> > (operator () (), ia1, ia2);
        }
#endif
    };

#ifdef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
    struct iterator1_tag {};
    struct iterator2_tag {};

    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_iterator_type begin (const I &it, iterator1_tag) {
        return it ().find2 (1, it.index1 (), 0);
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_iterator_type end (const I &it, iterator1_tag) {
        return it ().find2 (1, it.index1 (), it ().size2 ());
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_reverse_iterator_type rbegin (const I &it, iterator1_tag) {
        return typename I::dual_reverse_iterator_type (end (it, iterator1_tag ()));
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_reverse_iterator_type rend (const I &it, iterator1_tag) {
        return typename I::dual_reverse_iterator_type (begin (it, iterator1_tag ()));
    }

    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_iterator_type begin (const I &it, iterator2_tag) {
        return it ().find1 (1, 0, it.index2 ());
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_iterator_type end (const I &it, iterator2_tag) {
        return it ().find1 (1, it ().size1 (), it.index2 ());
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_reverse_iterator_type rbegin (const I &it, iterator2_tag) {
        return typename I::dual_reverse_iterator_type (end (it, iterator2_tag ()));
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_reverse_iterator_type rend (const I &it, iterator2_tag) {
        return typename I::dual_reverse_iterator_type (begin (it, iterator2_tag ()));
    }
#endif

    /** \brief Base class for Matrix container models
     *
     * it does not model the Matrix concept but all derived types should.
     * The class defines a common base type and some common interface for all
     * statically derived Matrix classes
     * We implement the casts to the statically derived type.
     */
    template<class C>
    class matrix_container:
        public matrix_expression<C> {
    public:
        static const unsigned complexity = 0;
        typedef C container_type;
        typedef matrix_tag type_category;

        BOOST_UBLAS_INLINE
        const container_type &operator () () const {
            return *static_cast<const container_type *> (this);
        }
        BOOST_UBLAS_INLINE
        container_type &operator () () {
            return *static_cast<container_type *> (this);
        }

#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_expression<C>::operator ();
#endif
    };

}}}

#endif

/* expression_types.hpp
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
*/