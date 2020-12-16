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
xGVzgsrm/WeYTOP02rrFKqMyhS78M+TCy2jTMxEOET3SKcmVcw9n8dyDHJFoc01E8JE07cOw/5HYt33WLNYz1f244xZukRSut0WkM0gBX6wK2NvCSTYK+RxVyOq+mxS0RxW0t+UrnKG3CCnMt9vOsg6vrdI+HuAxk50/Fgdtn//721axCaxihZKCC4wqdrHEPtKoYudLzG4Vcyi9tuvWYyqONNWAJCdW83q+id3xwGfjzSxCzx9xLKFzDEI3rH1roeSMsGpurEz+DXP1k/na87n/lx8/386VPnGaiM5syPXr1SOM68M3G2+L5mLknzRZRrb8zujOdMWRcIvTL2cI68sw8YnJR+E5utPlELQRxVaffhbfNl7vI+Miy3jfWE7oCg/jmXwG/o4IxrHG5Pc3jAr0vSRMIllq6W96Jf4torRliHIr5QGfKcptovwTlXeI8rdUcrv+aSrvFOUeKneIcheV94jybp53Gt8lAtb4WfLjVE1LFDWsVFss1VZLtc1S3WGptluqOy3VDkt1j6XabKnaLdV9onKJqkNUp4OlLOM/7/+A02/G29RqqTZaqk2Waoul2mqptlmqOyzVdkt1p6XaYanusVSbLVWHpWq3VCYN3uHAGVXbl1fynMsz7yWPvjPRfg5vNO3P425B5/H8V9D/Z9/qv8Emfhv8tA9Z9on+59K+Kon9FYx/SdL4Z9O++K32ie3lEqO99Eu9ftRjtlp9b7rZjPWHqHSL8idUekT5AyqlOWPktZr5F6jMEOVtVGaKMpxutJc+q6IeOLa9HLIsjlgqm8NUuSyV21J5LJXPUqVbqgxLlWmpYuJksyyzbIfZXnIcp6m9KPkCMvlaLnPWXemGhKqrRHerNKEIqCHqVqr7qN5I9SGqN4kahDmdRNFubWcsWUzVfVRnU71FSd46ExIn0hWDgYmQc5hP0eNWy8FFpgOX4eCHdLDNcpBqOnAbDj5FB3coB2f49d+foRwgJzQK4rFOy7LbtPQpyxrt1jsty++alunKcqp26z2W5W2mJTKuJMjfukNZnuvXP2JYkj5y/6HhZjaKBmdvoYb3hVRK75JJQhhAO7/+2yGGQLF+5aBlk9itUw54WGqKmht4BnOpENBgFd/YFg+yGtu1w63GtmC41djmDLca2/ThVmN7/3CrsY0fbjW284dbjW3UcDY2def51g4pSVbud3SY4z/gU4febKpscK6NN9I4pHS+jXtXgvutJ3CfleC+/QTu++3Hut+c3H2puR7GZqN2m2TEj42I7Ar9VZ8xzwqNNSrCB73xbbx3iP4MnLC9wSHvn6hAXLFAvhcfCKvQSAbiigWyiYG4rEDSVSDuWCCB+EDc7P+HsWeJBXIFA3FbgWSoQDJjgYyJD4RVUWMgmbFAUhlIpgokvMtmXlJQ/Q4uiuxisoOjw7vcVPjCuzKpsE5BdUdPcxWuJPd6pVcJ83XJURDZDeuEjKjVbr1UzOFAFUp0tUuf5DWbXhvSalJa93rNhtz8sGBXGvcDjwhJUqESvwiwplq2luRP/wus8BgR7/rsd9QtLj+5BYSaz/81563zeeFxlHalrRYic1hREjFlsEG0ew0heZS5neYHGgXiXfclalxKQzGVLA7jDrtZJGvMRcCFqeZbO/VkH3vEMIy5BLtUMUkXk7pURajE9QE7sMHMfLbq+PP28SQqUlf2SJ2221yC/CBHrRLI6YRZQR33P3Pe+drhrZ91/uEiUx5rRt7BGjkZiRuEUUmy1Sl/fKglxvm38BKzs/rqkqHmiTJeW7iXBXHElOEIHQuDQt6PICSZFchatEZGCGsYcAy1DiQEPyaTQtX7V5lE9Fik1F/yqEqL06zBuZX6G4OF3Z4=
*/