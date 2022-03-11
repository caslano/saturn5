//
//  Copyright (c) 2009
//  Gunter Winkler
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//

#ifndef _BOOST_UBLAS_SPARSE_VIEW_
#define _BOOST_UBLAS_SPARSE_VIEW_

#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/detail/matrix_assign.hpp>
#if BOOST_UBLAS_TYPE_CHECK
#include <boost/numeric/ublas/matrix.hpp>
#endif

#include <boost/next_prior.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/numeric/ublas/storage.hpp>

namespace boost { namespace numeric { namespace ublas {

    // view a chunk of memory as ublas array

    template < class T >
    class c_array_view
        : public storage_array< c_array_view<T> > {
    private:
        typedef c_array_view<T> self_type;
        typedef T * pointer;

    public:
        // TODO: think about a const pointer
        typedef const pointer array_type;

        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef T value_type;
        typedef const T  &const_reference;
        typedef const T  *const_pointer;

        typedef const_pointer const_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        //
        // typedefs required by vector concept
        //

        typedef dense_tag  storage_category;
        typedef const vector_reference<const self_type>    const_closure_type;

        c_array_view(size_type size, array_type data) :
            size_(size), data_(data)
        {}

        ~c_array_view()
        {}

        //
        // immutable methods of container concept
        //

        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return data_ + size_;
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

    private:
        size_type  size_;
        array_type data_;
    };


    /** \brief Present existing arrays as compressed array based
     *  sparse matrix.
     *  This class provides CRS / CCS storage layout.
     *
     *  see also http://www.netlib.org/utk/papers/templates/node90.html
     *
     *       \param L layout type, either row_major or column_major
     *       \param IB index base, use 0 for C indexing and 1 for
     *       FORTRAN indexing of the internal index arrays. This
     *       does not affect the operator()(int,int) where the first
     *       row/column has always index 0.
     *       \param IA index array type, e.g., int[]
     *       \param TA value array type, e.g., double[]
     */
    template<class L, std::size_t IB, class IA, class JA, class TA>
    class compressed_matrix_view:
        public matrix_expression<compressed_matrix_view<L, IB, IA, JA, TA> > {

    public:
        typedef typename vector_view_traits<TA>::value_type value_type;

    private:
        typedef value_type &true_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef L layout_type;
        typedef compressed_matrix_view<L, IB, IA, JA, TA> self_type;

    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_expression<self_type>::operator ();
#endif
        // ISSUE require type consistency check
        // is_convertable (IA::size_type, TA::size_type)
        typedef typename boost::remove_cv<typename vector_view_traits<JA>::value_type>::type index_type;
        // for compatibility, should be removed some day ...
        typedef index_type size_type;
        // size_type for the data arrays.
        typedef typename vector_view_traits<JA>::size_type array_size_type;
        typedef typename vector_view_traits<JA>::difference_type difference_type;
        typedef const value_type & const_reference;

        // do NOT define reference type, because class is read only
        // typedef value_type & reference;

        typedef IA rowptr_array_type;
        typedef JA index_array_type;
        typedef TA value_array_type;
        typedef const matrix_reference<const self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;

        // FIXME: define a corresponding temporary type
        // typedef compressed_vector<T, IB, IA, TA> vector_temporary_type;

        // FIXME: define a corresponding temporary type
        // typedef self_type matrix_temporary_type;

        typedef sparse_tag storage_category;
        typedef typename L::orientation_category orientation_category;

        //
        // private types for internal use
        //

    private:
        typedef typename vector_view_traits<index_array_type>::const_iterator const_subiterator_type;

        //
        // Construction and destruction
        //
    private:
        /// private default constructor because data must be filled by caller
        BOOST_UBLAS_INLINE
        compressed_matrix_view () { }

    public:
        BOOST_UBLAS_INLINE
        compressed_matrix_view (index_type n_rows, index_type n_cols, array_size_type nnz
                                , const rowptr_array_type & iptr
                                , const index_array_type & jptr
                                , const value_array_type & values):
            matrix_expression<self_type> (),
            size1_ (n_rows), size2_ (n_cols), 
            nnz_ (nnz),
            index1_data_ (iptr), 
            index2_data_ (jptr), 
            value_data_ (values) {
            storage_invariants ();
        }

        BOOST_UBLAS_INLINE
        compressed_matrix_view(const compressed_matrix_view& o) :
            size1_(o.size1_), size2_(o.size2_),
            nnz_(o.nnz_),
            index1_data_(o.index1_data_),
            index2_data_(o.index2_data_),
            value_data_(o.value_data_)
        {}

        //
        // implement immutable iterator types
        //

        class const_iterator1 {};
        class const_iterator2 {};

        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

        //
        // implement all read only methods for the matrix expression concept
        // 

        //! return the number of rows 
        index_type size1() const {
            return size1_;
        }

        //! return the number of columns
        index_type size2() const {
            return size2_;
        }

        //! return value at position (i,j)
        value_type operator()(index_type i, index_type j) const {
            const_pointer p = find_element(i,j);
            if (!p) {
                return zero_;
            } else {
                return *p;
            }
        }
        

    private:
        //
        // private helper functions
        //

        const_pointer find_element (index_type i, index_type j) const {
            index_type element1 (layout_type::index_M (i, j));
            index_type element2 (layout_type::index_m (i, j));

            const array_size_type itv      = zero_based( index1_data_[element1] );
            const array_size_type itv_next = zero_based( index1_data_[element1+1] );

            const_subiterator_type it_start = boost::next(vector_view_traits<index_array_type>::begin(index2_data_),itv);
            const_subiterator_type it_end = boost::next(vector_view_traits<index_array_type>::begin(index2_data_),itv_next);
            const_subiterator_type it = find_index_in_row(it_start, it_end, element2) ;
            
            if (it == it_end || *it != k_based (element2))
                return 0;
            return &value_data_ [it - vector_view_traits<index_array_type>::begin(index2_data_)];
        }

        const_subiterator_type find_index_in_row(const_subiterator_type it_start
                                                 , const_subiterator_type it_end
                                                 , index_type index) const {
            return std::lower_bound( it_start
                                     , it_end
                                     , k_based (index) );
        }


    private:
        void storage_invariants () const {
            BOOST_UBLAS_CHECK (index1_data_ [layout_type::size_M (size1_, size2_)] == k_based (nnz_), external_logic ());
        }
        
        index_type size1_;
        index_type size2_;

        array_size_type nnz_;

        const rowptr_array_type & index1_data_;
        const index_array_type & index2_data_;
        const value_array_type & value_data_;

        static const value_type zero_;

        BOOST_UBLAS_INLINE
        static index_type zero_based (index_type k_based_index) {
            return k_based_index - IB;
        }
        BOOST_UBLAS_INLINE
        static index_type k_based (index_type zero_based_index) {
            return zero_based_index + IB;
        }

        friend class iterator1;
        friend class iterator2;
        friend class const_iterator1;
        friend class const_iterator2;
    };

    template<class L, std::size_t IB, class IA, class JA, class TA  >
    const typename compressed_matrix_view<L,IB,IA,JA,TA>::value_type 
    compressed_matrix_view<L,IB,IA,JA,TA>::zero_ = value_type/*zero*/();


    template<class L, std::size_t IB, class IA, class JA, class TA  >
    compressed_matrix_view<L,IB,IA,JA,TA>
    make_compressed_matrix_view(typename vector_view_traits<JA>::value_type n_rows
                                , typename vector_view_traits<JA>::value_type n_cols
                                , typename vector_view_traits<JA>::size_type nnz
                                , const IA & ia
                                , const JA & ja
                                , const TA & ta) {

        return compressed_matrix_view<L,IB,IA,JA,TA>(n_rows, n_cols, nnz, ia, ja, ta);

    }

}}}

#endif

/* sparse_view.hpp
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
*/