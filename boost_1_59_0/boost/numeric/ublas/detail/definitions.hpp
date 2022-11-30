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

#ifndef _BOOST_UBLAS_DEFINITIONS_
#define _BOOST_UBLAS_DEFINITIONS_


namespace boost { namespace numeric { namespace ublas {

    namespace detail {
        /* Borrowed from boost/concept_checks.hpp
           "inline" is used for ignore_unused_variable_warning()
           to make sure there is no overhead with g++.
         */
        template <class T> inline
        void ignore_unused_variable_warning(const T&) {}
    } // namespace detail

    // Borrowed from Dave Abraham's noncopyable.
    // I believe this should be part of utility.hpp one day...
    namespace nonassignable_  // protection from unintended ADL
    {
        class nonassignable {
        protected:
            nonassignable () {}
            ~nonassignable () {}
        private:  // emphasize the following members are private
            const nonassignable& operator= (const nonassignable &);
        }; // nonassignable
    }
    typedef nonassignable_::nonassignable nonassignable;


    // Assignment proxy.
    // Provides temporary free assigment when LHS has no alias on RHS
    template<class C>
    class noalias_proxy:
        private nonassignable {
    public:
        typedef typename C::closure_type closure_type;

        BOOST_UBLAS_INLINE
        noalias_proxy (C& lval):
            nonassignable (), lval_ (lval) {}
        BOOST_UBLAS_INLINE
        noalias_proxy (const noalias_proxy& p):
            nonassignable (), lval_ (p.lval_) {}

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator= (const E& e) {
            lval_.assign (e);
            return lval_;
        }

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator+= (const E& e) {
            lval_.plus_assign (e);
            return lval_;
        }

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator-= (const E& e) {
            lval_.minus_assign (e);
            return lval_;
        }

    private:
        closure_type lval_;
    };

    // Improve syntax of efficient assignment where no aliases of LHS appear on the RHS
    //  noalias(lhs) = rhs_expression
    template <class C>
    BOOST_UBLAS_INLINE
    noalias_proxy<C> noalias (C& lvalue) {
        return noalias_proxy<C> (lvalue);
    }
    template <class C>
    BOOST_UBLAS_INLINE
    noalias_proxy<const C> noalias (const C& lvalue) {
        return noalias_proxy<const C> (lvalue);
    }

    // Possible future compatible syntax where lvalue possible has an unsafe alias on the RHS
    //  safe(lhs) = rhs_expression
    template <class C>
    BOOST_UBLAS_INLINE
    C& safe (C& lvalue) {
        return lvalue;
    }
    template <class C>
    BOOST_UBLAS_INLINE
    const C& safe (const C& lvalue) {
        return lvalue;
    }


    // Dimension accessors
    namespace dimension {

        // Generic accessors
        template<unsigned dimension>
        struct dimension_properties {};
        
        template<>
        struct dimension_properties<1> {
            template <class E>
            BOOST_UBLAS_INLINE static
            typename E::size_type size (const vector_expression<E> &e) {
                return e ().size ();
            }
            template <class E>
            BOOST_UBLAS_INLINE static
            typename E::size_type size (const matrix_expression<E> &e) {
                return e ().size1 ();
            }
            // Note: Index functions cannot deduce dependant template parameter V or M from i
            template <class V>
            BOOST_UBLAS_INLINE static
            typename V::size_type index (const typename V::iterator &i) {
                return i.index ();
            }
            template <class M>
            BOOST_UBLAS_INLINE static
            typename M::size_type index (const typename M::iterator1 &i) {
                return i.index1 ();
            }
            template <class M>
            BOOST_UBLAS_INLINE static
            typename M::size_type index (const typename M::iterator2 &i) {
                return i.index1 ();
            }
        };
        template<>
        struct dimension_properties<2> {
            template <class E>
            BOOST_UBLAS_INLINE static
            typename E::size_type size (const vector_expression<E> &) {
                return 1;
            }
            template <class E>
            BOOST_UBLAS_INLINE static
            typename E::size_type size (const matrix_expression<E> &e) {
                return e ().size2 ();
            }
            template <class V>
            BOOST_UBLAS_INLINE static
            typename V::size_type index (const typename V::iterator &) {
                return 1;
            }
            template <class M>
            BOOST_UBLAS_INLINE static
            typename M::size_type index (const typename M::iterator1 &i) {
                return i.index2 ();
            }
            template <class M>
            BOOST_UBLAS_INLINE static
            typename M::size_type index (const typename M::iterator2 &i) {
                return i.index2 ();
            }
        };

        template<unsigned dimension, class E>
        BOOST_UBLAS_INLINE
        typename E::size_type size (const E& e) {
            return dimension_properties<dimension>::size (e);
        }

        template<unsigned dimension, class I>
        BOOST_UBLAS_INLINE
        typename I::container_type::size_type
        index (const I& i) {
            typedef typename I::container_type container_type;
            return dimension_properties<dimension>::template index<container_type> (i);
        }


        // Named accessors - just syntactic sugar
        template<class V>
        typename V::size_type num_elements (const V &v) {
            return v.size ();
        }
        template<class M>
        typename M::size_type num_rows (const M &m) {
            return m.size1 ();
        }
        template<class M>
        typename M::size_type num_columns (const M &m) {
            return m.size2 ();
        }
        template<class MV>
        typename MV::size_type num_non_zeros (const MV &mv) {
            return mv.non_zeros ();
        }
    }


}}}

#endif

/* definitions.hpp
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
*/