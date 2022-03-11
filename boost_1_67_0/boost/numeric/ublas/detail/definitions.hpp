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