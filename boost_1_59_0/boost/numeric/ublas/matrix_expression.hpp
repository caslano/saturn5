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

#ifndef _BOOST_UBLAS_MATRIX_EXPRESSION_
#define _BOOST_UBLAS_MATRIX_EXPRESSION_

#include <boost/numeric/ublas/vector_expression.hpp>

// Expression templates based on ideas of Todd Veldhuizen and Geoffrey Furnish
// Iterators based on ideas of Jeremy Siek
//
// Classes that model the Matrix Expression concept

namespace boost { namespace numeric { namespace ublas {

template<class E>
class matrix_reference:
    public matrix_expression<matrix_reference<E> > {

	typedef matrix_reference<E> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using matrix_expression<self_type>::operator ();
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
	typedef typename E::orientation_category orientation_category;
	typedef typename E::storage_category storage_category;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	explicit matrix_reference (referred_type &e):
	  e_ (e) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size1 () const {
		return e_.size1 ();
	}
	BOOST_UBLAS_INLINE
	size_type size2 () const {
		return e_.size2 ();
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
	const_reference operator () (size_type i, size_type j) const {
		return expression () (i, j);
	}
	BOOST_UBLAS_INLINE
	reference operator () (size_type i, size_type j) {
		return expression () (i, j);
	}
#else
	BOOST_UBLAS_INLINE
	reference operator () (size_type i, size_type j) const {
		return expression () (i, j);
	}
#endif

#ifndef BOOST_UBLAS_REFERENCE_CONST_MEMBER
	BOOST_UBLAS_INLINE
	const_reference operator () (size_type i) const {
		return expression () (i);
	}
	BOOST_UBLAS_INLINE
	reference operator () (size_type i) {
		return expression () (i);
	}
#else
	BOOST_UBLAS_INLINE
	reference operator () (size_type i) const {
		return expression () (i);
	}
#endif


	// Assignment
	BOOST_UBLAS_INLINE
	matrix_reference &operator = (const matrix_reference &m) {
		expression ().operator = (m);
		return *this;
	}
	template<class AE>
	BOOST_UBLAS_INLINE
	matrix_reference &operator = (const matrix_expression<AE> &ae) {
		expression ().operator = (ae);
		return *this;
	}
	template<class AE>
	BOOST_UBLAS_INLINE
	matrix_reference &assign (const matrix_expression<AE> &ae) {
		expression ().assign (ae);
		return *this;
	}
	template<class AE>
	BOOST_UBLAS_INLINE
	matrix_reference &operator += (const matrix_expression<AE> &ae) {
		expression ().operator += (ae);
		return *this;
	}
	template<class AE>
	BOOST_UBLAS_INLINE
	matrix_reference &plus_assign (const matrix_expression<AE> &ae) {
		expression ().plus_assign (ae);
		return *this;
	}
	template<class AE>
	BOOST_UBLAS_INLINE
	matrix_reference &operator -= (const matrix_expression<AE> &ae) {
		expression ().operator -= (ae);
		return *this;
	}
	template<class AE>
	BOOST_UBLAS_INLINE
	matrix_reference &minus_assign (const matrix_expression<AE> &ae) {
		expression ().minus_assign (ae);
		return *this;
	}
	template<class AT>
	BOOST_UBLAS_INLINE
	matrix_reference &operator *= (const AT &at) {
		expression ().operator *= (at);
		return *this;
	}
	template<class AT>
	BOOST_UBLAS_INLINE
	matrix_reference &operator /= (const AT &at) {
		expression ().operator /= (at);
		return *this;
	}

	// Swapping
	BOOST_UBLAS_INLINE
	void swap (matrix_reference &m) {
		expression ().swap (m.expression ());
	}

	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_reference &mr) const {
		return &(*this).e_ == &mr.e_;
	}

	// Iterator types
	typedef typename E::const_iterator1 const_iterator1;
	typedef typename boost::mpl::if_<boost::is_const<E>,
	typename E::const_iterator1,
	typename E::iterator1>::type iterator1;
	typedef typename E::const_iterator2 const_iterator2;
	typedef typename boost::mpl::if_<boost::is_const<E>,
	typename E::const_iterator2,
	typename E::iterator2>::type iterator2;

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator1 find1 (int rank, size_type i, size_type j) const {
		return expression ().find1 (rank, i, j);
	}
	BOOST_UBLAS_INLINE
	iterator1 find1 (int rank, size_type i, size_type j) {
		return expression ().find1 (rank, i, j);
	}
	BOOST_UBLAS_INLINE
	const_iterator2 find2 (int rank, size_type i, size_type j) const {
		return expression ().find2 (rank, i, j);
	}
	BOOST_UBLAS_INLINE
	iterator2 find2 (int rank, size_type i, size_type j) {
		return expression ().find2 (rank, i, j);
	}

	// Iterators are the iterators of the referenced expression.

	BOOST_UBLAS_INLINE
	const_iterator1 begin1 () const {
		return expression ().begin1 ();
	}
	BOOST_UBLAS_INLINE
	const_iterator1 cbegin1 () const {
		return begin1 ();
	}
	BOOST_UBLAS_INLINE
	const_iterator1 end1 () const {
		return expression ().end1 ();
	}
	BOOST_UBLAS_INLINE
	const_iterator1 cend1 () const {
		return end1 ();
	}

	BOOST_UBLAS_INLINE
	iterator1 begin1 () {
		return expression ().begin1 ();
	}
	BOOST_UBLAS_INLINE
	iterator1 end1 () {
		return expression ().end1 ();
	}

	BOOST_UBLAS_INLINE
	const_iterator2 begin2 () const {
		return expression ().begin2 ();
	}
	BOOST_UBLAS_INLINE
	const_iterator2 cbegin2 () const {
		return begin2 ();
	}
	BOOST_UBLAS_INLINE
	const_iterator2 end2 () const {
		return expression ().end2 ();
	}
	BOOST_UBLAS_INLINE
	const_iterator2 cend2 () const {
		return end2 ();
	}

	BOOST_UBLAS_INLINE
	iterator2 begin2 () {
		return expression ().begin2 ();
	}
	BOOST_UBLAS_INLINE
	iterator2 end2 () {
		return expression ().end2 ();
	}

	// Reverse iterators
	typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
	typedef reverse_iterator_base1<iterator1> reverse_iterator1;

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

	typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
	typedef reverse_iterator_base2<iterator2> reverse_iterator2;

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
	referred_type &e_;
};


template<class E1, class E2, class F>
class vector_matrix_binary:
    public matrix_expression<vector_matrix_binary<E1, E2, F> > {

	typedef E1 expression1_type;
	typedef E2 expression2_type;
public:
	typedef typename E1::const_closure_type expression1_closure_type;
	typedef typename E2::const_closure_type expression2_closure_type;
private:
	typedef vector_matrix_binary<E1, E2, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using matrix_expression<self_type>::operator ();
#endif
	typedef F functor_type;
	typedef typename promote_traits<typename E1::size_type, typename E2::size_type>::promote_type size_type;
	typedef typename promote_traits<typename E1::difference_type, typename E2::difference_type>::promote_type difference_type;
	typedef typename F::result_type value_type;
	typedef value_type const_reference;
	typedef const_reference reference;
	typedef const self_type const_closure_type;
	typedef const_closure_type closure_type;
	typedef unknown_orientation_tag orientation_category;
	typedef unknown_storage_tag storage_category;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	vector_matrix_binary (const expression1_type &e1, const expression2_type &e2):
	  e1_ (e1), e2_ (e2) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size1 () const {
		return e1_.size ();
	}
	BOOST_UBLAS_INLINE
	size_type size2 () const {
		return e2_.size ();
	}

public:
	// Expression accessors
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
	const_reference operator () (size_type i, size_type j) const {
		return functor_type::apply (e1_ (i), e2_ (j));
	}



	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const vector_matrix_binary &vmb) const {
		return (*this).expression1 ().same_closure (vmb.expression1 ()) &&
		    (*this).expression2 ().same_closure (vmb.expression2 ());
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
	typedef indexed_const_iterator1<const_closure_type, iterator_category> const_iterator1;
	typedef const_iterator1 iterator1;
	typedef indexed_const_iterator2<const_closure_type, iterator_category> const_iterator2;
	typedef const_iterator2 iterator2;
#else
	class const_iterator1;
	typedef const_iterator1 iterator1;
	class const_iterator2;
	typedef const_iterator2 iterator2;
#endif
	typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
	typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator1 find1 (int rank, size_type i, size_type j) const {
		const_subiterator1_type it1 (e1_.find (i));
		const_subiterator1_type it1_end (e1_.find (size1 ()));
		const_subiterator2_type it2 (e2_.find (j));
		const_subiterator2_type it2_end (e2_.find (size2 ()));
		if (it2 == it2_end || (rank == 1 && (it2.index () != j || *it2 == typename E2::value_type/*zero*/()))) {
			it1 = it1_end;
			it2 = it2_end;
		}
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator1 (*this, it1.index (), it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		return const_iterator1 (*this, it1, it2, it2 != it2_end ? *it2 : typename E2::value_type/*zero*/());
#else
		return const_iterator1 (*this, it1, it2);
#endif
#endif
	}
	BOOST_UBLAS_INLINE
	const_iterator2 find2 (int rank, size_type i, size_type j) const {
		const_subiterator2_type it2 (e2_.find (j));
		const_subiterator2_type it2_end (e2_.find (size2 ()));
		const_subiterator1_type it1 (e1_.find (i));
		const_subiterator1_type it1_end (e1_.find (size1 ()));
		if (it1 == it1_end || (rank == 1 && (it1.index () != i || *it1 == typename E1::value_type/*zero*/()))) {
			it2 = it2_end;
			it1 = it1_end;
		}
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator2 (*this, it1.index (), it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		return const_iterator2 (*this, it1, it2, it1 != it1_end ? *it1 : typename E1::value_type/*zero*/());
#else
		return const_iterator2 (*this, it1, it2);
#endif
#endif
	}

	// Iterators enhance the iterators of the referenced expressions
	// with the binary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator1:
	    public container_const_reference<vector_matrix_binary>,
	    public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
	    typename E2::const_iterator::iterator_category>::iterator_category>::template
	    iterator_base<const_iterator1, value_type>::type {
	public:
		typedef typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
		typename E2::const_iterator::iterator_category>::iterator_category iterator_category;
		typedef typename vector_matrix_binary::difference_type difference_type;
		typedef typename vector_matrix_binary::value_type value_type;
		typedef typename vector_matrix_binary::const_reference reference;
		typedef typename vector_matrix_binary::const_pointer pointer;

		typedef const_iterator2 dual_iterator_type;
		typedef const_reverse_iterator2 dual_reverse_iterator_type;

		// Construction and destruction
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), it1_ (), it2_ (), t2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &vmb, const const_subiterator1_type &it1, const const_subiterator2_type &it2, value_type t2):
		  container_const_reference<self_type> (vmb), it1_ (it1), it2_ (it2), t2_ (t2) {}
#else
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), it1_ (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &vmb, const const_subiterator1_type &it1, const const_subiterator2_type &it2):
		  container_const_reference<self_type> (vmb), it1_ (it1), it2_ (it2) {}
#endif

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
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ - it.it1_;
		}

		// Dereference
		BOOST_UBLAS_INLINE
		const_reference operator * () const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (*it1_, t2_);
#else
			return functor_type::apply (*it1_, *it2_);
#endif
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
			return it1_.index ();
		}
		BOOST_UBLAS_INLINE
		size_type  index2 () const {
			return it2_.index ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator1 &operator = (const const_iterator1 &it) {
			container_const_reference<self_type>::assign (&it ());
			it1_ = it.it1_;
			it2_ = it.it2_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			t2_ = it.t2_;
#endif
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ == it.it1_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ < it.it1_;
		}

	private:
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		const_subiterator1_type it1_;
		// Mutable due to assignment
		/* const */ const_subiterator2_type it2_;
		value_type t2_;
#else
		const_subiterator1_type it1_;
		const_subiterator2_type it2_;
#endif
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
	class const_iterator2:
	    public container_const_reference<vector_matrix_binary>,
	    public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
	    typename E2::const_iterator::iterator_category>::iterator_category>::template
	    iterator_base<const_iterator2, value_type>::type {
	public:
		typedef typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
		typename E2::const_iterator::iterator_category>::iterator_category iterator_category;
		typedef typename vector_matrix_binary::difference_type difference_type;
		typedef typename vector_matrix_binary::value_type value_type;
		typedef typename vector_matrix_binary::const_reference reference;
		typedef typename vector_matrix_binary::const_pointer pointer;

		typedef const_iterator1 dual_iterator_type;
		typedef const_reverse_iterator1 dual_reverse_iterator_type;

		// Construction and destruction
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), it1_ (), it2_ (), t1_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &vmb, const const_subiterator1_type &it1, const const_subiterator2_type &it2, value_type t1):
		  container_const_reference<self_type> (vmb), it1_ (it1), it2_ (it2), t1_ (t1) {}
#else
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), it1_ (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &vmb, const const_subiterator1_type &it1, const const_subiterator2_type &it2):
		  container_const_reference<self_type> (vmb), it1_ (it1), it2_ (it2) {}
#endif

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
			BOOST_UBLAS_CHECK ((*this) ().same_closure(it ()), external_logic ());
			BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ - it.it2_;
		}

		// Dereference
		BOOST_UBLAS_INLINE
		const_reference operator * () const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (t1_, *it2_);
#else
			return functor_type::apply (*it1_, *it2_);
#endif
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
			return it1_.index ();
		}
		BOOST_UBLAS_INLINE
		size_type  index2 () const {
			return it2_.index ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator2 &operator = (const const_iterator2 &it) {
			container_const_reference<self_type>::assign (&it ());
			it1_ = it.it1_;
			it2_ = it.it2_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			t1_ = it.t1_;
#endif
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure( it ()), external_logic ());
			BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ == it.it2_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ < it.it2_;
		}

	private:
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		// Mutable due to assignment
		/* const */ const_subiterator1_type it1_;
		const_subiterator2_type it2_;
		value_type t1_;
#else
		const_subiterator1_type it1_;
		const_subiterator2_type it2_;
#endif
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

private:
	expression1_closure_type e1_;
	expression2_closure_type e2_;
};

template<class E1, class E2, class F>
struct vector_matrix_binary_traits {
	typedef vector_matrix_binary<E1, E2, F> expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	// ISSUE matrix is arbitary temporary type
	typedef matrix<typename F::value_type> result_type;
#endif
};

// (outer_prod (v1, v2)) [i] [j] = v1 [i] * v2 [j]
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename vector_matrix_binary_traits<E1, E2, scalar_multiplies<typename E1::value_type, typename E2::value_type> >::result_type
outer_prod (const vector_expression<E1> &e1,
            const vector_expression<E2> &e2) {
	BOOST_STATIC_ASSERT (E1::complexity == 0 && E2::complexity == 0);
	typedef typename vector_matrix_binary_traits<E1, E2, scalar_multiplies<typename E1::value_type, typename E2::value_type> >::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

template<class E, class F>
class matrix_unary1:
    public matrix_expression<matrix_unary1<E, F> > {

	typedef E expression_type;
	typedef F functor_type;
public:
	typedef typename E::const_closure_type expression_closure_type;
private:
	typedef matrix_unary1<E, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using matrix_expression<self_type>::operator ();
#endif
	typedef typename E::size_type size_type;
	typedef typename E::difference_type difference_type;
	typedef typename F::result_type value_type;
	typedef value_type const_reference;
	typedef const_reference reference;
	typedef const self_type const_closure_type;
	typedef const_closure_type closure_type;
	typedef typename E::orientation_category orientation_category;
	typedef unknown_storage_tag storage_category;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	explicit matrix_unary1 (const expression_type &e):
	  e_ (e) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size1 () const {
		return e_.size1 ();
	}
	BOOST_UBLAS_INLINE
	size_type size2 () const {
		return e_.size2 ();
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
	const_reference operator () (size_type i, size_type j) const {
		return functor_type::apply (e_ (i, j));
	}

	// Element access
	BOOST_UBLAS_INLINE
	const_reference operator () (size_type i) const {
		return functor_type::apply (e_ (i));
	}


	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_unary1 &mu1) const {
		return (*this).expression ().same_closure (mu1.expression ());
	}

	// Iterator types
private:
	typedef typename E::const_iterator1 const_subiterator1_type;
	typedef typename E::const_iterator2 const_subiterator2_type;
	typedef const value_type *const_pointer;

public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
	typedef indexed_const_iterator1<const_closure_type, typename const_subiterator1_type::iterator_category> const_iterator1;
	typedef const_iterator1 iterator1;
	typedef indexed_const_iterator2<const_closure_type, typename const_subiterator2_type::iterator_category> const_iterator2;
	typedef const_iterator2 iterator2;
#else
	class const_iterator1;
	typedef const_iterator1 iterator1;
	class const_iterator2;
	typedef const_iterator2 iterator2;
#endif
	typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
	typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator1 find1 (int rank, size_type i, size_type j) const {
		const_subiterator1_type it1 (e_.find1 (rank, i, j));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator1 (*this, it1.index1 (), it1.index2 ());
#else
		return const_iterator1 (*this, it1);
#endif
	}
	BOOST_UBLAS_INLINE
	const_iterator2 find2 (int rank, size_type i, size_type j) const {
		const_subiterator2_type it2 (e_.find2 (rank, i, j));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator2 (*this, it2.index1 (), it2.index2 ());
#else
		return const_iterator2 (*this, it2);
#endif
	}

	// Iterators enhance the iterators of the referenced expression
	// with the unary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator1:
	    public container_const_reference<matrix_unary1>,
	    public iterator_base_traits<typename E::const_iterator1::iterator_category>::template
	    iterator_base<const_iterator1, value_type>::type {
	public:
		typedef typename E::const_iterator1::iterator_category iterator_category;
		typedef typename matrix_unary1::difference_type difference_type;
		typedef typename matrix_unary1::value_type value_type;
		typedef typename matrix_unary1::const_reference reference;
		typedef typename matrix_unary1::const_pointer pointer;

		typedef const_iterator2 dual_iterator_type;
		typedef const_reverse_iterator2 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), it_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &mu, const const_subiterator1_type &it):
		  container_const_reference<self_type> (mu), it_ (it) {}

		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator1 &operator ++ () {
			++ it_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -- () {
			-- it_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator += (difference_type n) {
			it_ += n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -= (difference_type n) {
			it_ -= n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		difference_type operator - (const const_iterator1 &it) const {
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
			return it_.index1 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it_.index2 ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator1 &operator = (const const_iterator1 &it) {
			container_const_reference<self_type>::assign (&it ());
			it_ = it.it_;
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it_ == it.it_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it_ < it.it_;
		}

	private:
		const_subiterator1_type it_;
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
	class const_iterator2:
	    public container_const_reference<matrix_unary1>,
	    public iterator_base_traits<typename E::const_iterator2::iterator_category>::template
	    iterator_base<const_iterator2, value_type>::type {
	public:
		typedef typename E::const_iterator2::iterator_category iterator_category;
		typedef typename matrix_unary1::difference_type difference_type;
		typedef typename matrix_unary1::value_type value_type;
		typedef typename matrix_unary1::const_reference reference;
		typedef typename matrix_unary1::const_pointer pointer;

		typedef const_iterator1 dual_iterator_type;
		typedef const_reverse_iterator1 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), it_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &mu, const const_subiterator2_type &it):
		  container_const_reference<self_type> (mu), it_ (it) {}

		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator2 &operator ++ () {
			++ it_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator -- () {
			-- it_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator += (difference_type n) {
			it_ += n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator -= (difference_type n) {
			it_ -= n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		difference_type operator - (const const_iterator2 &it) const {
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
			return it_.index1 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it_.index2 ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator2 &operator = (const const_iterator2 &it) {
			container_const_reference<self_type>::assign (&it ());
			it_ = it.it_;
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it_ == it.it_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it_ < it.it_;
		}

	private:
		const_subiterator2_type it_;
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

private:
	expression_closure_type e_;
};

template<class E, class F>
struct matrix_unary1_traits {
	typedef matrix_unary1<E, F> expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename E::matrix_temporary_type result_type;
#endif
};

// (- m) [i] [j] = - m [i] [j]
template<class E>
BOOST_UBLAS_INLINE
typename matrix_unary1_traits<E, scalar_negate<typename E::value_type> >::result_type
operator - (const matrix_expression<E> &e) {
	typedef typename matrix_unary1_traits<E, scalar_negate<typename E::value_type> >::expression_type expression_type;
	return expression_type (e ());
}

// (conj m) [i] [j] = conj (m [i] [j])
template<class E>
BOOST_UBLAS_INLINE
typename matrix_unary1_traits<E, scalar_conj<typename E::value_type> >::result_type
conj (const matrix_expression<E> &e) {
	typedef typename matrix_unary1_traits<E, scalar_conj<typename E::value_type> >::expression_type expression_type;
	return expression_type (e ());
}

// (real m) [i] [j] = real (m [i] [j])
template<class E>
BOOST_UBLAS_INLINE
typename matrix_unary1_traits<E, scalar_real<typename E::value_type> >::result_type
real (const matrix_expression<E> &e) {
	typedef typename matrix_unary1_traits<E, scalar_real<typename E::value_type> >::expression_type expression_type;
	return expression_type (e ());
}

// (imag m) [i] [j] = imag (m [i] [j])
template<class E>
BOOST_UBLAS_INLINE
typename matrix_unary1_traits<E, scalar_imag<typename E::value_type> >::result_type
imag (const matrix_expression<E> &e) {
	typedef typename matrix_unary1_traits<E, scalar_imag<typename E::value_type> >::expression_type expression_type;
	return expression_type (e ());
}

template<class E, class F>
class matrix_unary2:
    public matrix_expression<matrix_unary2<E, F> > {

	typedef typename boost::mpl::if_<boost::is_same<F, scalar_identity<typename E::value_type> >,
	E,
	const E>::type expression_type;
	typedef F functor_type;
public:
	typedef typename boost::mpl::if_<boost::is_const<expression_type>,
	typename E::const_closure_type,
	typename E::closure_type>::type expression_closure_type;
private:
	typedef matrix_unary2<E, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using matrix_expression<self_type>::operator ();
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
	typedef typename boost::mpl::if_<boost::is_same<typename E::orientation_category,
	row_major_tag>,
	column_major_tag,
	typename boost::mpl::if_<boost::is_same<typename E::orientation_category,
	column_major_tag>,
	row_major_tag,
	typename E::orientation_category>::type>::type orientation_category;
	typedef typename E::storage_category storage_category;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	// matrix_unary2 may be used as mutable expression -
	// this is the only non const expression constructor
	explicit matrix_unary2 (expression_type &e):
	  e_ (e) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size1 () const {
		return e_.size2 ();
	}
	BOOST_UBLAS_INLINE
	size_type size2 () const {
		return e_.size1 ();
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
	const_reference operator () (size_type i, size_type j) const {
		return functor_type::apply (e_ (j, i));
	}
	BOOST_UBLAS_INLINE
	reference operator () (size_type i, size_type j) {
		BOOST_STATIC_ASSERT ((boost::is_same<functor_type, scalar_identity<value_type > >::value));
		return e_ (j, i);
	}

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

	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_unary2 &mu2) const {
		return (*this).expression ().same_closure (mu2.expression ());
	}

	// Iterator types
private:
	typedef typename E::const_iterator1 const_subiterator2_type;
	typedef typename E::const_iterator2 const_subiterator1_type;
	typedef const value_type *const_pointer;

public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
	typedef indexed_const_iterator1<const_closure_type, typename const_subiterator1_type::iterator_category> const_iterator1;
	typedef const_iterator1 iterator1;
	typedef indexed_const_iterator2<const_closure_type, typename const_subiterator2_type::iterator_category> const_iterator2;
	typedef const_iterator2 iterator2;
#else
	class const_iterator1;
	typedef const_iterator1 iterator1;
	class const_iterator2;
	typedef const_iterator2 iterator2;
#endif
	typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
	typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator1 find1 (int rank, size_type i, size_type j) const {
		const_subiterator1_type it1 (e_.find2 (rank, j, i));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator1 (*this, it1.index2 (), it1.index1 ());
#else
		return const_iterator1 (*this, it1);
#endif
	}
	BOOST_UBLAS_INLINE
	const_iterator2 find2 (int rank, size_type i, size_type j) const {
		const_subiterator2_type it2 (e_.find1 (rank, j, i));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator2 (*this, it2.index2 (), it2.index1 ());
#else
		return const_iterator2 (*this, it2);
#endif
	}

	// Iterators enhance the iterators of the referenced expression
	// with the unary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator1:
	    public container_const_reference<matrix_unary2>,
	    public iterator_base_traits<typename E::const_iterator2::iterator_category>::template
	    iterator_base<const_iterator1, value_type>::type {
	public:
		typedef typename E::const_iterator2::iterator_category iterator_category;
		typedef typename matrix_unary2::difference_type difference_type;
		typedef typename matrix_unary2::value_type value_type;
		typedef typename matrix_unary2::const_reference reference;
		typedef typename matrix_unary2::const_pointer pointer;

		typedef const_iterator2 dual_iterator_type;
		typedef const_reverse_iterator2 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), it_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &mu, const const_subiterator1_type &it):
		  container_const_reference<self_type> (mu), it_ (it) {}

		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator1 &operator ++ () {
			++ it_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -- () {
			-- it_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator += (difference_type n) {
			it_ += n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -= (difference_type n) {
			it_ -= n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		difference_type operator - (const const_iterator1 &it) const {
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
			return it_.index2 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it_.index1 ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator1 &operator = (const const_iterator1 &it) {
			container_const_reference<self_type>::assign (&it ());
			it_ = it.it_;
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it_ == it.it_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it_ < it.it_;
		}

	private:
		const_subiterator1_type it_;
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
	class const_iterator2:
	    public container_const_reference<matrix_unary2>,
	    public iterator_base_traits<typename E::const_iterator1::iterator_category>::template
	    iterator_base<const_iterator2, value_type>::type {
	public:
		typedef typename E::const_iterator1::iterator_category iterator_category;
		typedef typename matrix_unary2::difference_type difference_type;
		typedef typename matrix_unary2::value_type value_type;
		typedef typename matrix_unary2::const_reference reference;
		typedef typename matrix_unary2::const_pointer pointer;

		typedef const_iterator1 dual_iterator_type;
		typedef const_reverse_iterator1 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), it_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &mu, const const_subiterator2_type &it):
		  container_const_reference<self_type> (mu), it_ (it) {}

		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator2 &operator ++ () {
			++ it_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator -- () {
			-- it_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator += (difference_type n) {
			it_ += n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator -= (difference_type n) {
			it_ -= n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		difference_type operator - (const const_iterator2 &it) const {
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
			return it_.index2 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it_.index1 ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator2 &operator = (const const_iterator2 &it) {
			container_const_reference<self_type>::assign (&it ());
			it_ = it.it_;
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it_ == it.it_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it_ < it.it_;
		}

	private:
		const_subiterator2_type it_;
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

private:
	expression_closure_type e_;
};

template<class E, class F>
struct matrix_unary2_traits {
	typedef matrix_unary2<E, F> expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename E::matrix_temporary_type result_type;
#endif
};

// (trans m) [i] [j] = m [j] [i]
template<class E>
BOOST_UBLAS_INLINE
typename matrix_unary2_traits<const E, scalar_identity<typename E::value_type> >::result_type
trans (const matrix_expression<E> &e) {
	typedef typename matrix_unary2_traits<const E, scalar_identity<typename E::value_type> >::expression_type expression_type;
	return expression_type (e ());
}
template<class E>
BOOST_UBLAS_INLINE
typename matrix_unary2_traits<E, scalar_identity<typename E::value_type> >::result_type
trans (matrix_expression<E> &e) {
	typedef typename matrix_unary2_traits<E, scalar_identity<typename E::value_type> >::expression_type expression_type;
	return expression_type (e ());
}

// (herm m) [i] [j] = conj (m [j] [i])
template<class E>
BOOST_UBLAS_INLINE
typename matrix_unary2_traits<E, scalar_conj<typename E::value_type> >::result_type
herm (const matrix_expression<E> &e) {
	typedef typename matrix_unary2_traits<E, scalar_conj<typename E::value_type> >::expression_type expression_type;
	return expression_type (e ());
}

template<class E1, class E2, class F>
class matrix_binary:
    public matrix_expression<matrix_binary<E1, E2, F> > {

	typedef E1 expression1_type;
	typedef E2 expression2_type;
	typedef F functor_type;
public:
	typedef typename E1::const_closure_type expression1_closure_type;
	typedef typename E2::const_closure_type expression2_closure_type;
private:
	typedef matrix_binary<E1, E2, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using matrix_expression<self_type>::operator ();
#endif
	typedef typename promote_traits<typename E1::size_type, typename E2::size_type>::promote_type size_type;
	typedef typename promote_traits<typename E1::difference_type, typename E2::difference_type>::promote_type difference_type;
	typedef typename F::result_type value_type;
	typedef value_type const_reference;
	typedef const_reference reference;
	typedef const self_type const_closure_type;
	typedef const_closure_type closure_type;
	typedef unknown_orientation_tag orientation_category;
	typedef unknown_storage_tag storage_category;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	matrix_binary (const E1 &e1, const E2 &e2):
	  e1_ (e1), e2_ (e2) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size1 () const {
		return BOOST_UBLAS_SAME (e1_.size1 (), e2_.size1 ());
	}
	BOOST_UBLAS_INLINE
	size_type size2 () const {
		return BOOST_UBLAS_SAME (e1_.size2 (), e2_.size2 ());
	}

public:
	// Expression accessors
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
	const_reference operator () (size_type i, size_type j) const {
		return functor_type::apply (e1_ (i, j), e2_ (i, j));
	}

	// Element access
	BOOST_UBLAS_INLINE
	const_reference operator () (size_type i) const {
		return functor_type::apply (e1_ (i), e2_ (i));
	}

	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_binary &mb) const {
		return (*this).expression1 ().same_closure (mb.expression1 ()) &&
		    (*this).expression2 ().same_closure (mb.expression2 ());
	}

	// Iterator types
private:
	typedef typename E1::const_iterator1 const_iterator11_type;
	typedef typename E1::const_iterator2 const_iterator12_type;
	typedef typename E2::const_iterator1 const_iterator21_type;
	typedef typename E2::const_iterator2 const_iterator22_type;
	typedef const value_type *const_pointer;

public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
	typedef typename iterator_restrict_traits<typename const_iterator11_type::iterator_category,
	typename const_iterator21_type::iterator_category>::iterator_category iterator_category1;
	typedef indexed_const_iterator1<const_closure_type, iterator_category1> const_iterator1;
	typedef const_iterator1 iterator1;
	typedef typename iterator_restrict_traits<typename const_iterator12_type::iterator_category,
	typename const_iterator22_type::iterator_category>::iterator_category iterator_category2;
	typedef indexed_const_iterator2<const_closure_type, iterator_category2> const_iterator2;
	typedef const_iterator2 iterator2;
#else
	class const_iterator1;
	typedef const_iterator1 iterator1;
	class const_iterator2;
	typedef const_iterator2 iterator2;
#endif
	typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
	typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator1 find1 (int rank, size_type i, size_type j) const {
		const_iterator11_type it11 (e1_.find1 (rank, i, j));
		const_iterator11_type it11_end (e1_.find1 (rank, size1 (), j));
		const_iterator21_type it21 (e2_.find1 (rank, i, j));
		const_iterator21_type it21_end (e2_.find1 (rank, size1 (), j));
		BOOST_UBLAS_CHECK (rank == 0 || it11 == it11_end || it11.index2 () == j, internal_logic ())
		    BOOST_UBLAS_CHECK (rank == 0 || it21 == it21_end || it21.index2 () == j, internal_logic ())
		    i = (std::min) (it11 != it11_end ? it11.index1 () : size1 (),
		                    it21 != it21_end ? it21.index1 () : size1 ());
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator1 (*this, i, j);
#else
		return const_iterator1 (*this, i, j, it11, it11_end, it21, it21_end);
#endif
	}
	BOOST_UBLAS_INLINE
	const_iterator2 find2 (int rank, size_type i, size_type j) const {
		const_iterator12_type it12 (e1_.find2 (rank, i, j));
		const_iterator12_type it12_end (e1_.find2 (rank, i, size2 ()));
		const_iterator22_type it22 (e2_.find2 (rank, i, j));
		const_iterator22_type it22_end (e2_.find2 (rank, i, size2 ()));
		BOOST_UBLAS_CHECK (rank == 0 || it12 == it12_end || it12.index1 () == i, internal_logic ())
		    BOOST_UBLAS_CHECK (rank == 0 || it22 == it22_end || it22.index1 () == i, internal_logic ())
		    j = (std::min) (it12 != it12_end ? it12.index2 () : size2 (),
		                    it22 != it22_end ? it22.index2 () : size2 ());
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator2 (*this, i, j);
#else
		return const_iterator2 (*this, i, j, it12, it12_end, it22, it22_end);
#endif
	}

	// Iterators enhance the iterators of the referenced expression
	// with the binary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator1:
	    public container_const_reference<matrix_binary>,
	    public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator1::iterator_category,
	    typename E2::const_iterator1::iterator_category>::iterator_category>::template
	    iterator_base<const_iterator1, value_type>::type {
	public:
		typedef typename iterator_restrict_traits<typename E1::const_iterator1::iterator_category,
		typename E2::const_iterator1::iterator_category>::iterator_category iterator_category;
		typedef typename matrix_binary::difference_type difference_type;
		typedef typename matrix_binary::value_type value_type;
		typedef typename matrix_binary::const_reference reference;
		typedef typename matrix_binary::const_pointer pointer;

		typedef const_iterator2 dual_iterator_type;
		typedef const_reverse_iterator2 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), i_ (), j_ (), it1_ (), it1_end_ (), it2_ (), it2_end_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &mb, size_type i, size_type j,
		                 const const_iterator11_type &it1, const const_iterator11_type &it1_end,
		                 const const_iterator21_type &it2, const const_iterator21_type &it2_end):
		  container_const_reference<self_type> (mb), i_ (i), j_ (j), it1_ (it1), it1_end_ (it1_end), it2_ (it2), it2_end_ (it2_end) {}

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
				if (it1_.index1 () <= i_)
					++ it1_;
			if (it2_ != it2_end_)
				if (it2_.index1 () <= i_)
					++ it2_;
			++ i_;
		}
		BOOST_UBLAS_INLINE
		void decrement (packed_random_access_iterator_tag) {
			if (it1_ != it1_end_)
				if (i_ <= it1_.index1 ())
					-- it1_;
			if (it2_ != it2_end_)
				if (i_ <= it2_.index1 ())
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
			if (it1_ != it1_end_) {
				BOOST_UBLAS_CHECK (it1_.index2 () == j_, internal_logic ());
				if (it1_.index1 () == i_)
					t1 = *it1_;
			}
			typename E2::value_type t2 = typename E2::value_type/*zero*/();
			if (it2_ != it2_end_) {
				BOOST_UBLAS_CHECK (it2_.index2 () == j_, internal_logic ());
				if (it2_.index1 () == i_)
					t2 = *it2_;
			}
			return functor_type::apply (t1, t2);
		}

		// Sparse specializations
		BOOST_UBLAS_INLINE
		void increment (sparse_bidirectional_iterator_tag) {
			size_type index1 = (*this) ().size1 ();
			if (it1_ != it1_end_) {
				if (it1_.index1 () <= i_)
					++ it1_;
				if (it1_ != it1_end_)
					index1 = it1_.index1 ();
			}
			size_type index2 = (*this) ().size1 ();
			if (it2_ != it2_end_)
				if (it2_.index1 () <= i_)
					++ it2_;
			if (it2_ != it2_end_) {
				index2 = it2_.index1 ();
			}
			i_ = (std::min) (index1, index2);
		}
		BOOST_UBLAS_INLINE
		void decrement (sparse_bidirectional_iterator_tag) {
			size_type index1 = (*this) ().size1 ();
			if (it1_ != it1_end_) {
				if (i_ <= it1_.index1 ())
					-- it1_;
				if (it1_ != it1_end_)
					index1 = it1_.index1 ();
			}
			size_type index2 = (*this) ().size1 ();
			if (it2_ != it2_end_) {
				if (i_ <= it2_.index1 ())
					-- it2_;
				if (it2_ != it2_end_)
					index2 = it2_.index1 ();
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
			if (it1_ != it1_end_) {
				BOOST_UBLAS_CHECK (it1_.index2 () == j_, internal_logic ());
				if (it1_.index1 () == i_)
					t1 = *it1_;
			}
			typename E2::value_type t2 = typename E2::value_type/*zero*/();
			if (it2_ != it2_end_) {
				BOOST_UBLAS_CHECK (it2_.index2 () == j_, internal_logic ());
				if (it2_.index1 () == i_)
					t2 = *it2_;
			}
			return functor_type::apply (t1, t2);
		}

	public:
		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator1 &operator ++ () {
			increment (iterator_category ());
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -- () {
			decrement (iterator_category ());
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator += (difference_type n) {
			increment (iterator_category (), n);
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -= (difference_type n) {
			decrement (iterator_category (), n);
			return *this;
		}
		BOOST_UBLAS_INLINE
		difference_type operator - (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (index2 () == it.index2 (), external_logic ());
			return index1 () - it.index1 ();
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
			return i_;
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			// if (it1_ != it1_end_ && it2_ != it2_end_)
			//    return BOOST_UBLAS_SAME (it1_.index2 (), it2_.index2 ());
			// else
			return j_;
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator1 &operator = (const const_iterator1 &it) {
			container_const_reference<self_type>::assign (&it ());
			i_ = it.i_;
			j_ = it.j_;
			it1_ = it.it1_;
			it1_end_ = it.it1_end_;
			it2_ = it.it2_;
			it2_end_ = it.it2_end_;
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (index2 () == it.index2 (), external_logic ());
			return index1 () == it.index1 ();
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (index2 () == it.index2 (), external_logic ());
			return index1 () < it.index1 ();
		}

	private:
		size_type i_;
		size_type j_;
		const_iterator11_type it1_;
		const_iterator11_type it1_end_;
		const_iterator21_type it2_;
		const_iterator21_type it2_end_;
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
	class const_iterator2:
	    public container_const_reference<matrix_binary>,
	    public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator2::iterator_category,
	    typename E2::const_iterator2::iterator_category>::iterator_category>::template
	    iterator_base<const_iterator2, value_type>::type {
	public:
		typedef typename iterator_restrict_traits<typename E1::const_iterator2::iterator_category,
		typename E2::const_iterator2::iterator_category>::iterator_category iterator_category;
		typedef typename matrix_binary::difference_type difference_type;
		typedef typename matrix_binary::value_type value_type;
		typedef typename matrix_binary::const_reference reference;
		typedef typename matrix_binary::const_pointer pointer;

		typedef const_iterator1 dual_iterator_type;
		typedef const_reverse_iterator1 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), i_ (), j_ (), it1_ (), it1_end_ (), it2_ (), it2_end_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &mb, size_type i, size_type j,
		                 const const_iterator12_type &it1, const const_iterator12_type &it1_end,
		                 const const_iterator22_type &it2, const const_iterator22_type &it2_end):
		  container_const_reference<self_type> (mb), i_ (i), j_ (j), it1_ (it1), it1_end_ (it1_end), it2_ (it2), it2_end_ (it2_end) {}

	private:
		// Dense access specializations
		BOOST_UBLAS_INLINE
		void increment (dense_random_access_iterator_tag) {
			++ j_; ++ it1_; ++ it2_;
		}
		BOOST_UBLAS_INLINE
		void decrement (dense_random_access_iterator_tag) {
			-- j_; -- it1_; -- it2_;
		}
		BOOST_UBLAS_INLINE
		void increment (dense_random_access_iterator_tag, difference_type n) {
			j_ += n; it1_ += n; it2_ += n;
		}
		BOOST_UBLAS_INLINE
		void decrement (dense_random_access_iterator_tag, difference_type n) {
			j_ -= n; it1_ -= n; it2_ -= n;
		}
		BOOST_UBLAS_INLINE
		value_type dereference (dense_random_access_iterator_tag) const {
			return functor_type::apply (*it1_, *it2_);
		}

		// Packed specializations
		BOOST_UBLAS_INLINE
		void increment (packed_random_access_iterator_tag) {
			if (it1_ != it1_end_)
				if (it1_.index2 () <= j_)
					++ it1_;
			if (it2_ != it2_end_)
				if (it2_.index2 () <= j_)
					++ it2_;
			++ j_;
		}
		BOOST_UBLAS_INLINE
		void decrement (packed_random_access_iterator_tag) {
			if (it1_ != it1_end_)
				if (j_ <= it1_.index2 ())
					-- it1_;
			if (it2_ != it2_end_)
				if (j_ <= it2_.index2 ())
					-- it2_;
			-- j_;
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
			if (it1_ != it1_end_) {
				BOOST_UBLAS_CHECK (it1_.index1 () == i_, internal_logic ());
				if (it1_.index2 () == j_)
					t1 = *it1_;
			}
			typename E2::value_type t2 = typename E2::value_type/*zero*/();
			if (it2_ != it2_end_) {
				BOOST_UBLAS_CHECK (it2_.index1 () == i_, internal_logic ());
				if (it2_.index2 () == j_)
					t2 = *it2_;
			}
			return functor_type::apply (t1, t2);
		}

		// Sparse specializations
		BOOST_UBLAS_INLINE
		void increment (sparse_bidirectional_iterator_tag) {
			size_type index1 = (*this) ().size2 ();
			if (it1_ != it1_end_) {
				if (it1_.index2 () <= j_)
					++ it1_;
				if (it1_ != it1_end_)
					index1 = it1_.index2 ();
			}
			size_type index2 = (*this) ().size2 ();
			if (it2_ != it2_end_) {
				if (it2_.index2 () <= j_)
					++ it2_;
				if (it2_ != it2_end_)
					index2 = it2_.index2 ();
			}
			j_ = (std::min) (index1, index2);
		}
		BOOST_UBLAS_INLINE
		void decrement (sparse_bidirectional_iterator_tag) {
			size_type index1 = (*this) ().size2 ();
			if (it1_ != it1_end_) {
				if (j_ <= it1_.index2 ())
					-- it1_;
				if (it1_ != it1_end_)
					index1 = it1_.index2 ();
			}
			size_type index2 = (*this) ().size2 ();
			if (it2_ != it2_end_) {
				if (j_ <= it2_.index2 ())
					-- it2_;
				if (it2_ != it2_end_)
					index2 = it2_.index2 ();
			}
			j_ = (std::max) (index1, index2);
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
			if (it1_ != it1_end_) {
				BOOST_UBLAS_CHECK (it1_.index1 () == i_, internal_logic ());
				if (it1_.index2 () == j_)
					t1 = *it1_;
			}
			typename E2::value_type t2 = typename E2::value_type/*zero*/();
			if (it2_ != it2_end_) {
				BOOST_UBLAS_CHECK (it2_.index1 () == i_, internal_logic ());
				if (it2_.index2 () == j_)
					t2 = *it2_;
			}
			return functor_type::apply (t1, t2);
		}

	public:
		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator2 &operator ++ () {
			increment (iterator_category ());
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator -- () {
			decrement (iterator_category ());
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator += (difference_type n) {
			increment (iterator_category (), n);
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator -= (difference_type n) {
			decrement (iterator_category (), n);
			return *this;
		}
		BOOST_UBLAS_INLINE
		difference_type operator - (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (index1 () == it.index1 (), external_logic ());
			return index2 () - it.index2 ();
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
			// if (it1_ != it1_end_ && it2_ != it2_end_)
			//    return BOOST_UBLAS_SAME (it1_.index1 (), it2_.index1 ());
			// else
			return i_;
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return j_;
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator2 &operator = (const const_iterator2 &it) {
			container_const_reference<self_type>::assign (&it ());
			i_ = it.i_;
			j_ = it.j_;
			it1_ = it.it1_;
			it1_end_ = it.it1_end_;
			it2_ = it.it2_;
			it2_end_ = it.it2_end_;
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (index1 () == it.index1 (), external_logic ());
			return index2 () == it.index2 ();
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (index1 () == it.index1 (), external_logic ());
			return index2 () < it.index2 ();
		}

	private:
		size_type i_;
		size_type j_;
		const_iterator12_type it1_;
		const_iterator12_type it1_end_;
		const_iterator22_type it2_;
		const_iterator22_type it2_end_;
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

private:
	expression1_closure_type e1_;
	expression2_closure_type e2_;
};

template<class E1, class E2, class F>
struct matrix_binary_traits {
	typedef matrix_binary<E1, E2, F> expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename E1::matrix_temporary_type result_type;
#endif
};

// (m1 + m2) [i] [j] = m1 [i] [j] + m2 [i] [j]
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_binary_traits<E1, E2, scalar_plus<typename E1::value_type,
typename E2::value_type> >::result_type
operator + (const matrix_expression<E1> &e1,
            const matrix_expression<E2> &e2) {
	typedef typename matrix_binary_traits<E1, E2, scalar_plus<typename E1::value_type,
	    typename E2::value_type> >::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// (m1 - m2) [i] [j] = m1 [i] [j] - m2 [i] [j]
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_binary_traits<E1, E2, scalar_minus<typename E1::value_type,
typename E2::value_type> >::result_type
operator - (const matrix_expression<E1> &e1,
            const matrix_expression<E2> &e2) {
	typedef typename matrix_binary_traits<E1, E2, scalar_minus<typename E1::value_type,
	    typename E2::value_type> >::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// (m1 * m2) [i] [j] = m1 [i] [j] * m2 [i] [j]
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_binary_traits<E1, E2, scalar_multiplies<typename E1::value_type,
typename E2::value_type> >::result_type
element_prod (const matrix_expression<E1> &e1,
              const matrix_expression<E2> &e2) {
	typedef typename matrix_binary_traits<E1, E2, scalar_multiplies<typename E1::value_type,
	    typename E2::value_type> >::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// (m1 / m2) [i] [j] = m1 [i] [j] / m2 [i] [j]
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_binary_traits<E1, E2, scalar_divides<typename E1::value_type,
typename E2::value_type> >::result_type
element_div (const matrix_expression<E1> &e1,
             const matrix_expression<E2> &e2) {
	typedef typename matrix_binary_traits<E1, E2, scalar_divides<typename E1::value_type,
	    typename E2::value_type> >::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

template<class E1, class E2, class F>
class matrix_binary_scalar1:
    public matrix_expression<matrix_binary_scalar1<E1, E2, F> > {

	typedef E1 expression1_type;
	typedef E2 expression2_type;
	typedef F functor_type;
	typedef const E1& expression1_closure_type;
	typedef typename E2::const_closure_type expression2_closure_type;
	typedef matrix_binary_scalar1<E1, E2, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using matrix_expression<self_type>::operator ();
#endif
	typedef typename E2::size_type size_type;
	typedef typename E2::difference_type difference_type;
	typedef typename F::result_type value_type;
	typedef value_type const_reference;
	typedef const_reference reference;
	typedef const self_type const_closure_type;
	typedef const_closure_type closure_type;
	typedef typename E2::orientation_category orientation_category;
	typedef unknown_storage_tag storage_category;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	matrix_binary_scalar1 (const expression1_type &e1, const expression2_type &e2):
	  e1_ (e1), e2_ (e2) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size1 () const {
		return e2_.size1 ();
	}
	BOOST_UBLAS_INLINE
	size_type size2 () const {
		return e2_.size2 ();
	}

public:
	// Element access
	BOOST_UBLAS_INLINE
	const_reference operator () (size_type i, size_type j) const {
		return functor_type::apply (expression1_type (e1_), e2_ (i, j));
	}

	// Element access
	BOOST_UBLAS_INLINE
	const_reference operator () (size_type i) const {
		return functor_type::apply (expression1_type (e1_), e2_ (i));
	}

	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_binary_scalar1 &mbs1) const {
		return &e1_ == &(mbs1.e1_) &&
		    (*this).e2_.same_closure (mbs1.e2_);
	}

	// Iterator types
private:
	typedef expression1_type const_subiterator1_type;
	typedef typename E2::const_iterator1 const_iterator21_type;
	typedef typename E2::const_iterator2 const_iterator22_type;
	typedef const value_type *const_pointer;

public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
	typedef indexed_const_iterator1<const_closure_type, typename const_iterator21_type::iterator_category> const_iterator1;
	typedef const_iterator1 iterator1;
	typedef indexed_const_iterator2<const_closure_type, typename const_iterator22_type::iterator_category> const_iterator2;
	typedef const_iterator2 iterator2;
#else
	class const_iterator1;
	typedef const_iterator1 iterator1;
	class const_iterator2;
	typedef const_iterator2 iterator2;
#endif
	typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
	typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator1 find1 (int rank, size_type i, size_type j) const {
		const_iterator21_type it21 (e2_.find1 (rank, i, j));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator1 (*this, it21.index1 (), it21.index2 ());
#else
		return const_iterator1 (*this, const_subiterator1_type (e1_), it21);
#endif
	}
	BOOST_UBLAS_INLINE
	const_iterator2 find2 (int rank, size_type i, size_type j) const {
		const_iterator22_type it22 (e2_.find2 (rank, i, j));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator2 (*this, it22.index1 (), it22.index2 ());
#else
		return const_iterator2 (*this, const_subiterator1_type (e1_), it22);
#endif
	}

	// Iterators enhance the iterators of the referenced expression
	// with the binary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator1:
	    public container_const_reference<matrix_binary_scalar1>,
	    public iterator_base_traits<typename E2::const_iterator1::iterator_category>::template
	    iterator_base<const_iterator1, value_type>::type {
	public:
		typedef typename E2::const_iterator1::iterator_category iterator_category;
		typedef typename matrix_binary_scalar1::difference_type difference_type;
		typedef typename matrix_binary_scalar1::value_type value_type;
		typedef typename matrix_binary_scalar1::const_reference reference;
		typedef typename matrix_binary_scalar1::const_pointer pointer;

		typedef const_iterator2 dual_iterator_type;
		typedef const_reverse_iterator2 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), it1_ (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &mbs, const const_subiterator1_type &it1, const const_iterator21_type &it2):
		  container_const_reference<self_type> (mbs), it1_ (it1), it2_ (it2) {}

		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator1 &operator ++ () {
			++ it2_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -- () {
			-- it2_ ;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator += (difference_type n) {
			it2_ += n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -= (difference_type n) {
			it2_ -= n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		difference_type operator - (const const_iterator1 &it) const {
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
			return it2_.index1 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it2_.index2 ();
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
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			// FIXME we shouldn't compare floats
			// BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ == it.it2_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			// FIXME we shouldn't compare floats
			// BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ < it.it2_;
		}

	private:
		const_subiterator1_type it1_;
		const_iterator21_type it2_;
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
	class const_iterator2:
	    public container_const_reference<matrix_binary_scalar1>,
	    public iterator_base_traits<typename E2::const_iterator2::iterator_category>::template
	    iterator_base<const_iterator2, value_type>::type {
	public:
		typedef typename E2::const_iterator2::iterator_category iterator_category;
		typedef typename matrix_binary_scalar1::difference_type difference_type;
		typedef typename matrix_binary_scalar1::value_type value_type;
		typedef typename matrix_binary_scalar1::const_reference reference;
		typedef typename matrix_binary_scalar1::const_pointer pointer;

		typedef const_iterator1 dual_iterator_type;
		typedef const_reverse_iterator1 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), it1_ (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &mbs, const const_subiterator1_type &it1, const const_iterator22_type &it2):
		  container_const_reference<self_type> (mbs), it1_ (it1), it2_ (it2) {}

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
			return it2_.index1 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it2_.index2 ();
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
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			// FIXME we shouldn't compare floats
			// BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ == it.it2_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			// FIXME we shouldn't compare floats
			// BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ < it.it2_;
		}

	private:
		const_subiterator1_type it1_;
		const_iterator22_type it2_;
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

private:
	expression1_closure_type e1_;
	expression2_closure_type e2_;
};

template<class E1, class E2, class F>
struct matrix_binary_scalar1_traits {
	typedef matrix_binary_scalar1<E1, E2, F> expression_type;   // allow E1 to be builtin type
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename E2::matrix_temporary_type result_type;
#endif
};

// (t * m) [i] [j] = t * m [i] [j]
template<class T1, class E2>
BOOST_UBLAS_INLINE
typename boost::enable_if< is_convertible<T1, typename E2::value_type >,
typename matrix_binary_scalar1_traits<const T1, E2, scalar_multiplies<T1, typename E2::value_type> >::result_type
>::type
operator * (const T1 &e1,
            const matrix_expression<E2> &e2) {
	typedef typename matrix_binary_scalar1_traits<const T1, E2, scalar_multiplies<T1, typename E2::value_type> >::expression_type expression_type;
	return expression_type (e1, e2 ());
}


template<class E1, class E2, class F>
class matrix_binary_scalar2:
    public matrix_expression<matrix_binary_scalar2<E1, E2, F> > {

	typedef E1 expression1_type;
	typedef E2 expression2_type;
	typedef F functor_type;
public:
	typedef typename E1::const_closure_type expression1_closure_type;
	typedef const E2& expression2_closure_type;
private:
	typedef matrix_binary_scalar2<E1, E2, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using matrix_expression<self_type>::operator ();
#endif
	typedef typename E1::size_type size_type;
	typedef typename E1::difference_type difference_type;
	typedef typename F::result_type value_type;
	typedef value_type const_reference;
	typedef const_reference reference;

	typedef const self_type const_closure_type;
	typedef const_closure_type closure_type;
	typedef typename E1::orientation_category orientation_category;
	typedef unknown_storage_tag storage_category;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	matrix_binary_scalar2 (const expression1_type &e1, const expression2_type &e2):
	  e1_ (e1), e2_ (e2) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size1 () const {
		return e1_.size1 ();
	}
	BOOST_UBLAS_INLINE
	size_type size2 () const {
		return e1_.size2 ();
	}

public:
	// Element access
	BOOST_UBLAS_INLINE
	const_reference operator () (size_type i, size_type j) const {
		return functor_type::apply (e1_ (i, j), expression2_type (e2_));
	}
	// Element access
	BOOST_UBLAS_INLINE
	const_reference operator () (size_type i) const {
		return functor_type::apply (e1_ (i), expression2_type (e2_));
	}

	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_binary_scalar2 &mbs2) const {
		return (*this).e1_.same_closure (mbs2.e1_) &&
		    &e2_ == &(mbs2.e2_);
	}

	// Iterator types
private:
	typedef typename E1::const_iterator1 const_iterator11_type;
	typedef typename E1::const_iterator2 const_iterator12_type;
	typedef expression2_type const_subiterator2_type;
	typedef const value_type *const_pointer;

public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
	typedef indexed_const_iterator1<const_closure_type, typename const_iterator11_type::iterator_category> const_iterator1;
	typedef const_iterator1 iterator1;
	typedef indexed_const_iterator2<const_closure_type, typename const_iterator12_type::iterator_category> const_iterator2;
	typedef const_iterator2 iterator2;
#else
	class const_iterator1;
	typedef const_iterator1 iterator1;
	class const_iterator2;
	typedef const_iterator2 iterator2;
#endif
	typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
	typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator1 find1 (int rank, size_type i, size_type j) const {
		const_iterator11_type it11 (e1_.find1 (rank, i, j));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator1 (*this, it11.index1 (), it11.index2 ());
#else
		return const_iterator1 (*this, it11, const_subiterator2_type (e2_));
#endif
	}
	BOOST_UBLAS_INLINE
	const_iterator2 find2 (int rank, size_type i, size_type j) const {
		const_iterator12_type it12 (e1_.find2 (rank, i, j));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator2 (*this, it12.index1 (), it12.index2 ());
#else
		return const_iterator2 (*this, it12, const_subiterator2_type (e2_));
#endif
	}

	// Iterators enhance the iterators of the referenced expression
	// with the binary functor.

#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator1:
	    public container_const_reference<matrix_binary_scalar2>,
	    public iterator_base_traits<typename E1::const_iterator1::iterator_category>::template
	    iterator_base<const_iterator1, value_type>::type {
	public:
		typedef typename E1::const_iterator1::iterator_category iterator_category;
		typedef typename matrix_binary_scalar2::difference_type difference_type;
		typedef typename matrix_binary_scalar2::value_type value_type;
		typedef typename matrix_binary_scalar2::const_reference reference;
		typedef typename matrix_binary_scalar2::const_pointer pointer;

		typedef const_iterator2 dual_iterator_type;
		typedef const_reverse_iterator2 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), it1_ (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &mbs, const const_iterator11_type &it1, const const_subiterator2_type &it2):
		  container_const_reference<self_type> (mbs), it1_ (it1), it2_ (it2) {}

		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator1 &operator ++ () {
			++ it1_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator1 &operator -- () {
			-- it1_ ;
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
			return it1_.index1 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it1_.index2 ();
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
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			// FIXME we shouldn't compare floats
			// BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ == it.it1_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			// FIXME we shouldn't compare floats
			// BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ < it.it1_;
		}

	private:
		const_iterator11_type it1_;
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
	class const_iterator2:
	    public container_const_reference<matrix_binary_scalar2>,
	    public iterator_base_traits<typename E1::const_iterator2::iterator_category>::template
	    iterator_base<const_iterator2, value_type>::type {
	public:
		typedef typename E1::const_iterator2::iterator_category iterator_category;
		typedef typename matrix_binary_scalar2::difference_type difference_type;
		typedef typename matrix_binary_scalar2::value_type value_type;
		typedef typename matrix_binary_scalar2::const_reference reference;
		typedef typename matrix_binary_scalar2::const_pointer pointer;

		typedef const_iterator1 dual_iterator_type;
		typedef const_reverse_iterator1 dual_reverse_iterator_type;

		// Construction and destruction
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), it1_ (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &mbs, const const_iterator12_type &it1, const const_subiterator2_type &it2):
		  container_const_reference<self_type> (mbs), it1_ (it1), it2_ (it2) {}

		// Arithmetic
		BOOST_UBLAS_INLINE
		const_iterator2 &operator ++ () {
			++ it1_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator -- () {
			-- it1_;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator += (difference_type n) {
			it1_ += n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		const_iterator2 &operator -= (difference_type n) {
			it1_ -= n;
			return *this;
		}
		BOOST_UBLAS_INLINE
		difference_type operator - (const const_iterator2 &it) const {
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
			return it1_.index1 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it1_.index2 ();
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
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			// FIXME we shouldn't compare floats
			// BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ == it.it1_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			// FIXME we shouldn't compare floats
			// BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ < it.it1_;
		}

	private:
		const_iterator12_type it1_;
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

private:
	expression1_closure_type e1_;
	expression2_closure_type e2_;
};

template<class E1, class E2, class F>
struct matrix_binary_scalar2_traits {
	typedef matrix_binary_scalar2<E1, E2, F> expression_type;   // allow E2 to be builtin type
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename E1::matrix_temporary_type result_type;
#endif
};

// (m * t) [i] [j] = m [i] [j] * t
template<class E1, class T2>
BOOST_UBLAS_INLINE
typename boost::enable_if< is_convertible<T2, typename E1::value_type>,
typename matrix_binary_scalar2_traits<E1, const T2, scalar_multiplies<typename E1::value_type, T2> >::result_type
>::type
operator * (const matrix_expression<E1> &e1,
            const T2 &e2) {
	typedef typename matrix_binary_scalar2_traits<E1, const T2, scalar_multiplies<typename E1::value_type, T2> >::expression_type expression_type;
	return expression_type (e1 (), e2);
}

// (m / t) [i] [j] = m [i] [j] / t
template<class E1, class T2>
BOOST_UBLAS_INLINE
typename boost::enable_if< is_convertible<T2, typename E1::value_type>,
typename matrix_binary_scalar2_traits<E1, const T2, scalar_divides<typename E1::value_type, T2> >::result_type
>::type
operator / (const matrix_expression<E1> &e1,
            const T2 &e2) {
	typedef typename matrix_binary_scalar2_traits<E1, const T2, scalar_divides<typename E1::value_type, T2> >::expression_type expression_type;
	return expression_type (e1 (), e2);
}


template<class E1, class E2, class F>
class matrix_vector_binary1:
    public vector_expression<matrix_vector_binary1<E1, E2, F> > {

public:
	typedef E1 expression1_type;
	typedef E2 expression2_type;
private:
	typedef F functor_type;
public:
	typedef typename E1::const_closure_type expression1_closure_type;
	typedef typename E2::const_closure_type expression2_closure_type;
private:
	typedef matrix_vector_binary1<E1, E2, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using vector_expression<self_type>::operator ();
#endif
	static const unsigned complexity = 1;
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
	matrix_vector_binary1 (const expression1_type &e1, const expression2_type &e2):
	  e1_ (e1), e2_ (e2) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size () const {
		return e1_.size1 ();
	}

public:
	// Expression accessors
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
		return functor_type::apply (e1_, e2_, i);
	}

	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_vector_binary1 &mvb1) const {
		return (*this).expression1 ().same_closure (mvb1.expression1 ()) &&
		    (*this).expression2 ().same_closure (mvb1.expression2 ());
	}

	// Iterator types
private:
	typedef typename E1::const_iterator1 const_subiterator1_type;
	typedef typename E2::const_iterator const_subiterator2_type;
	typedef const value_type *const_pointer;

public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
	typedef indexed_const_iterator<const_closure_type, typename const_subiterator1_type::iterator_category> const_iterator;
	typedef const_iterator iterator;
#else
	class const_iterator;
	typedef const_iterator iterator;
#endif

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator find (size_type i) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		const_subiterator1_type it1 (e1_.find1 (0, i, 0));
		return const_iterator (*this, it1.index1 ());
#else
		return const_iterator (*this, e1_.find1 (0, i, 0));
#endif
	}


#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator:
	    public container_const_reference<matrix_vector_binary1>,
	    public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator1::iterator_category,
	    typename E2::const_iterator::iterator_category>::iterator_category>::template
	    iterator_base<const_iterator, value_type>::type {
	public:
		typedef typename iterator_restrict_traits<typename E1::const_iterator1::iterator_category,
		typename E2::const_iterator::iterator_category>::iterator_category iterator_category;
		typedef typename matrix_vector_binary1::difference_type difference_type;
		typedef typename matrix_vector_binary1::value_type value_type;
		typedef typename matrix_vector_binary1::const_reference reference;
		typedef typename matrix_vector_binary1::const_pointer pointer;

		// Construction and destruction
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		BOOST_UBLAS_INLINE
		const_iterator ():
		  container_const_reference<self_type> (), it1_ (), e2_begin_ (), e2_end_ () {}
		BOOST_UBLAS_INLINE
		const_iterator (const self_type &mvb, const const_subiterator1_type &it1):
		  container_const_reference<self_type> (mvb), it1_ (it1), e2_begin_ (mvb.expression2 ().begin ()), e2_end_ (mvb.expression2 ().end ()) {}
#else
		BOOST_UBLAS_INLINE
		const_iterator ():
		  container_const_reference<self_type> (), it1_ () {}
		BOOST_UBLAS_INLINE
		const_iterator (const self_type &mvb, const const_subiterator1_type &it1):
		  container_const_reference<self_type> (mvb), it1_ (it1) {}
#endif

	private:
		// Dense random access specialization
		BOOST_UBLAS_INLINE
		value_type dereference (dense_random_access_iterator_tag) const {
			const self_type &mvb = (*this) ();
#ifdef BOOST_UBLAS_USE_INDEXING
			return mvb (index ());
#elif BOOST_UBLAS_USE_ITERATING
			difference_type size = BOOST_UBLAS_SAME (mvb.expression1 ().size2 (), mvb.expression2 ().size ());
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (size, it1_.begin (), e2_begin_);
#else
			return functor_type::apply (size, it1_.begin (), mvb.expression2 ().begin ());
#endif
#else
			difference_type size = BOOST_UBLAS_SAME (mvb.expression1 ().size2 (), mvb.expression2 ().size ());
			if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
				return functor_type::apply (size, it1_.begin (), e2_begin_);
#else
				return functor_type::apply (size, it1_.begin (), mvb.expression2 ().begin ());
#endif
			else
				return mvb (index ());
#endif
		}

		// Packed bidirectional specialization
		BOOST_UBLAS_INLINE
		value_type dereference (packed_random_access_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (it1_.begin (), it1_.end (), e2_begin_, e2_end_);
#else
			const self_type &mvb = (*this) ();
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
			return functor_type::apply (it1_.begin (), it1_.end (),
			                            mvb.expression2 ().begin (), mvb.expression2 ().end ());
#else
			return functor_type::apply (boost::numeric::ublas::begin (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::end (it1_, iterator1_tag ()),
			                            mvb.expression2 ().begin (), mvb.expression2 ().end ());
#endif
#endif
		}

		// Sparse bidirectional specialization
		BOOST_UBLAS_INLINE
		value_type dereference (sparse_bidirectional_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (it1_.begin (), it1_.end (), e2_begin_, e2_end_, sparse_bidirectional_iterator_tag ());
#else
			const self_type &mvb = (*this) ();
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
			return functor_type::apply (it1_.begin (), it1_.end (),
			                            mvb.expression2 ().begin (), mvb.expression2 ().end (), sparse_bidirectional_iterator_tag ());
#else
			return functor_type::apply (boost::numeric::ublas::begin (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::end (it1_, iterator1_tag ()),
			                            mvb.expression2 ().begin (), mvb.expression2 ().end (), sparse_bidirectional_iterator_tag ());
#endif
#endif
		}

	public:
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
			return it1_ - it.it1_;
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
			return it1_.index1 ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator &operator = (const const_iterator &it) {
			container_const_reference<self_type>::assign (&it ());
			it1_ = it.it1_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			e2_begin_ = it.e2_begin_;
			e2_end_ = it.e2_end_;
#endif
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it1_ == it.it1_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it1_ < it.it1_;
		}

	private:
		const_subiterator1_type it1_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		// Mutable due to assignment
		/* const */ const_subiterator2_type e2_begin_;
		/* const */ const_subiterator2_type e2_end_;
#endif
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

template<class T1, class E1, class T2, class E2>
struct matrix_vector_binary1_traits {
	typedef unknown_storage_tag storage_category;
	typedef row_major_tag orientation_category;
	typedef typename promote_traits<T1, T2>::promote_type promote_type;
	typedef matrix_vector_binary1<E1, E2, matrix_vector_prod1<E1, E2, promote_type> > expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename E1::vector_temporary_type result_type;
#endif
};

template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_vector_binary1_traits<typename E1::value_type, E1,
typename E2::value_type, E2>::result_type
prod (const matrix_expression<E1> &e1,
      const vector_expression<E2> &e2,
      unknown_storage_tag,
      row_major_tag) {
	typedef typename matrix_vector_binary1_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// Dispatcher
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_vector_binary1_traits<typename E1::value_type, E1,
typename E2::value_type, E2>::result_type
prod (const matrix_expression<E1> &e1,
      const vector_expression<E2> &e2) {
	BOOST_STATIC_ASSERT (E2::complexity == 0);
	typedef typename matrix_vector_binary1_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::storage_category storage_category;
	typedef typename matrix_vector_binary1_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::orientation_category orientation_category;
	return prod (e1, e2, storage_category (), orientation_category ());
}

template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_vector_binary1_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
prec_prod (const matrix_expression<E1> &e1,
           const vector_expression<E2> &e2,
           unknown_storage_tag,
           row_major_tag) {
	typedef typename matrix_vector_binary1_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// Dispatcher
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_vector_binary1_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
prec_prod (const matrix_expression<E1> &e1,
           const vector_expression<E2> &e2) {
	BOOST_STATIC_ASSERT (E2::complexity == 0);
	typedef typename matrix_vector_binary1_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::storage_category storage_category;
	typedef typename matrix_vector_binary1_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::orientation_category orientation_category;
	return prec_prod (e1, e2, storage_category (), orientation_category ());
}

template<class V, class E1, class E2>
BOOST_UBLAS_INLINE
V &
prod (const matrix_expression<E1> &e1,
      const vector_expression<E2> &e2,
      V &v) {
	return v.assign (prod (e1, e2));
}

template<class V, class E1, class E2>
BOOST_UBLAS_INLINE
V &
prec_prod (const matrix_expression<E1> &e1,
           const vector_expression<E2> &e2,
           V &v) {
	return v.assign (prec_prod (e1, e2));
}

template<class V, class E1, class E2>
BOOST_UBLAS_INLINE
V
prod (const matrix_expression<E1> &e1,
      const vector_expression<E2> &e2) {
	return V (prod (e1, e2));
}

template<class V, class E1, class E2>
BOOST_UBLAS_INLINE
V
prec_prod (const matrix_expression<E1> &e1,
           const vector_expression<E2> &e2) {
	return V (prec_prod (e1, e2));
}

template<class E1, class E2, class F>
class matrix_vector_binary2:
    public vector_expression<matrix_vector_binary2<E1, E2, F> > {

	typedef E1 expression1_type;
	typedef E2 expression2_type;
	typedef F functor_type;
public:
	typedef typename E1::const_closure_type expression1_closure_type;
	typedef typename E2::const_closure_type expression2_closure_type;
private:
	typedef matrix_vector_binary2<E1, E2, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using vector_expression<self_type>::operator ();
#endif
	static const unsigned complexity = 1;
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
	matrix_vector_binary2 (const expression1_type &e1, const expression2_type &e2):
	  e1_ (e1), e2_ (e2) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size () const {
		return e2_.size2 ();
	}

public:
	// Expression accessors
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
	const_reference operator () (size_type j) const {
		return functor_type::apply (e1_, e2_, j);
	}

	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_vector_binary2 &mvb2) const {
		return (*this).expression1 ().same_closure (mvb2.expression1 ()) &&
		    (*this).expression2 ().same_closure (mvb2.expression2 ());
	}

	// Iterator types
private:
	typedef typename E1::const_iterator const_subiterator1_type;
	typedef typename E2::const_iterator2 const_subiterator2_type;
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
	const_iterator find (size_type j) const {
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		const_subiterator2_type it2 (e2_.find2 (0, 0, j));
		return const_iterator (*this, it2.index2 ());
#else
		return const_iterator (*this, e2_.find2 (0, 0, j));
#endif
	}


#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator:
	    public container_const_reference<matrix_vector_binary2>,
	    public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
	    typename E2::const_iterator2::iterator_category>::iterator_category>::template
	    iterator_base<const_iterator, value_type>::type {
	public:
		typedef typename iterator_restrict_traits<typename E1::const_iterator::iterator_category,
		typename E2::const_iterator2::iterator_category>::iterator_category iterator_category;
		typedef typename matrix_vector_binary2::difference_type difference_type;
		typedef typename matrix_vector_binary2::value_type value_type;
		typedef typename matrix_vector_binary2::const_reference reference;
		typedef typename matrix_vector_binary2::const_pointer pointer;

		// Construction and destruction
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		BOOST_UBLAS_INLINE
		const_iterator ():
		  container_const_reference<self_type> (), it2_ (), e1_begin_ (), e1_end_ () {}
		BOOST_UBLAS_INLINE
		const_iterator (const self_type &mvb, const const_subiterator2_type &it2):
		  container_const_reference<self_type> (mvb), it2_ (it2), e1_begin_ (mvb.expression1 ().begin ()), e1_end_ (mvb.expression1 ().end ()) {}
#else
		BOOST_UBLAS_INLINE
		const_iterator ():
		  container_const_reference<self_type> (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator (const self_type &mvb, const const_subiterator2_type &it2):
		  container_const_reference<self_type> (mvb), it2_ (it2) {}
#endif

	private:
		// Dense random access specialization
		BOOST_UBLAS_INLINE
		value_type dereference (dense_random_access_iterator_tag) const {
			const self_type &mvb = (*this) ();
#ifdef BOOST_UBLAS_USE_INDEXING
			return mvb (index ());
#elif BOOST_UBLAS_USE_ITERATING
			difference_type size = BOOST_UBLAS_SAME (mvb.expression2 ().size1 (), mvb.expression1 ().size ());
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (size, e1_begin_, it2_.begin ());
#else
			return functor_type::apply (size, mvb.expression1 ().begin (), it2_.begin ());
#endif
#else
			difference_type size = BOOST_UBLAS_SAME (mvb.expression2 ().size1 (), mvb.expression1 ().size ());
			if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
				return functor_type::apply (size, e1_begin_, it2_.begin ());
#else
				return functor_type::apply (size, mvb.expression1 ().begin (), it2_.begin ());
#endif
			else
				return mvb (index ());
#endif
		}

		// Packed bidirectional specialization
		BOOST_UBLAS_INLINE
		value_type dereference (packed_random_access_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (e1_begin_, e1_end_, it2_.begin (), it2_.end ());
#else
			const self_type &mvb = (*this) ();
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
			return functor_type::apply (mvb.expression1 ().begin (), mvb.expression1 ().end (),
			                            it2_.begin (), it2_.end ());
#else
			return functor_type::apply (mvb.expression1 ().begin (), mvb.expression1 ().end (),
			                            boost::numeric::ublas::begin (it2_, iterator2_tag ()),
			                            boost::numeric::ublas::end (it2_, iterator2_tag ()));
#endif
#endif
		}

		// Sparse bidirectional specialization
		BOOST_UBLAS_INLINE
		value_type dereference (sparse_bidirectional_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (e1_begin_, e1_end_, it2_.begin (), it2_.end (), sparse_bidirectional_iterator_tag ());
#else
			const self_type &mvb = (*this) ();
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
			return functor_type::apply (mvb.expression1 ().begin (), mvb.expression1 ().end (),
			                            it2_.begin (), it2_.end (), sparse_bidirectional_iterator_tag ());
#else
			return functor_type::apply (mvb.expression1 ().begin (), mvb.expression1 ().end (),
			                            boost::numeric::ublas::begin (it2_, iterator2_tag ()),
			                            boost::numeric::ublas::end (it2_, iterator2_tag ()), sparse_bidirectional_iterator_tag ());
#endif
#endif
		}

	public:
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
			return it2_ - it.it2_;
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
			return it2_.index2 ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator &operator = (const const_iterator &it) {
			container_const_reference<self_type>::assign (&it ());
			it2_ = it.it2_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			e1_begin_ = it.e1_begin_;
			e1_end_ = it.e1_end_;
#endif
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it2_ == it.it2_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			return it2_ < it.it2_;
		}

	private:
		const_subiterator2_type it2_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		// Mutable due to assignment
		/* const */ const_subiterator1_type e1_begin_;
		/* const */ const_subiterator1_type e1_end_;
#endif
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

template<class T1, class E1, class T2, class E2>
struct matrix_vector_binary2_traits {
	typedef unknown_storage_tag storage_category;
	typedef column_major_tag orientation_category;
	typedef typename promote_traits<T1, T2>::promote_type promote_type;
	typedef matrix_vector_binary2<E1, E2, matrix_vector_prod2<E1, E2, promote_type> > expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename E2::vector_temporary_type result_type;
#endif
};

template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_vector_binary2_traits<typename E1::value_type, E1,
typename E2::value_type, E2>::result_type
prod (const vector_expression<E1> &e1,
      const matrix_expression<E2> &e2,
      unknown_storage_tag,
      column_major_tag) {
	typedef typename matrix_vector_binary2_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// Dispatcher
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_vector_binary2_traits<typename E1::value_type, E1,
typename E2::value_type, E2>::result_type
prod (const vector_expression<E1> &e1,
      const matrix_expression<E2> &e2) {
	BOOST_STATIC_ASSERT (E1::complexity == 0);
	typedef typename matrix_vector_binary2_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::storage_category storage_category;
	typedef typename matrix_vector_binary2_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::orientation_category orientation_category;
	return prod (e1, e2, storage_category (), orientation_category ());
}

template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_vector_binary2_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
prec_prod (const vector_expression<E1> &e1,
           const matrix_expression<E2> &e2,
           unknown_storage_tag,
           column_major_tag) {
	typedef typename matrix_vector_binary2_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// Dispatcher
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_vector_binary2_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
prec_prod (const vector_expression<E1> &e1,
           const matrix_expression<E2> &e2) {
	BOOST_STATIC_ASSERT (E1::complexity == 0);
	typedef typename matrix_vector_binary2_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::storage_category storage_category;
	typedef typename matrix_vector_binary2_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::orientation_category orientation_category;
	return prec_prod (e1, e2, storage_category (), orientation_category ());
}

template<class V, class E1, class E2>
BOOST_UBLAS_INLINE
V &
prod (const vector_expression<E1> &e1,
      const matrix_expression<E2> &e2,
      V &v) {
	return v.assign (prod (e1, e2));
}

template<class V, class E1, class E2>
BOOST_UBLAS_INLINE
V &
prec_prod (const vector_expression<E1> &e1,
           const matrix_expression<E2> &e2,
           V &v) {
	return v.assign (prec_prod (e1, e2));
}

template<class V, class E1, class E2>
BOOST_UBLAS_INLINE
V
prod (const vector_expression<E1> &e1,
      const matrix_expression<E2> &e2) {
	return V (prod (e1, e2));
}

template<class V, class E1, class E2>
BOOST_UBLAS_INLINE
V
prec_prod (const vector_expression<E1> &e1,
           const matrix_expression<E2> &e2) {
	return V (prec_prod (e1, e2));
}

template<class E1, class E2, class F>
class matrix_matrix_binary:
    public matrix_expression<matrix_matrix_binary<E1, E2, F> > {

public:
	typedef E1 expression1_type;
	typedef E2 expression2_type;
private:
	typedef F functor_type;
public:
	typedef typename E1::const_closure_type expression1_closure_type;
	typedef typename E2::const_closure_type expression2_closure_type;
private:
	typedef matrix_matrix_binary<E1, E2, F> self_type;
public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
	using matrix_expression<self_type>::operator ();
#endif
	static const unsigned complexity = 1;
	typedef typename promote_traits<typename E1::size_type, typename E2::size_type>::promote_type size_type;
	typedef typename promote_traits<typename E1::difference_type, typename E2::difference_type>::promote_type difference_type;
	typedef typename F::result_type value_type;
	typedef value_type const_reference;
	typedef const_reference reference;
	typedef const self_type const_closure_type;
	typedef const_closure_type closure_type;
	typedef unknown_orientation_tag orientation_category;
	typedef unknown_storage_tag storage_category;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	matrix_matrix_binary (const expression1_type &e1, const expression2_type &e2):
	  e1_ (e1), e2_ (e2) {}

	// Accessors
	BOOST_UBLAS_INLINE
	size_type size1 () const {
		return e1_.size1 ();
	}
	BOOST_UBLAS_INLINE
	size_type size2 () const {
		return e2_.size2 ();
	}

public:
	// Expression accessors
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
	const_reference operator () (size_type i, size_type j) const {
		return functor_type::apply (e1_, e2_, i, j);
	}

	// Element access
	BOOST_UBLAS_INLINE
	const_reference operator () (size_type i) const {
		return functor_type::apply (e1_, e2_, i);
	}

	// Closure comparison
	BOOST_UBLAS_INLINE
	bool same_closure (const matrix_matrix_binary &mmb) const {
		return (*this).expression1 ().same_closure (mmb.expression1 ()) &&
		    (*this).expression2 ().same_closure (mmb.expression2 ());
	}

	// Iterator types
private:
	typedef typename E1::const_iterator1 const_iterator11_type;
	typedef typename E1::const_iterator2 const_iterator12_type;
	typedef typename E2::const_iterator1 const_iterator21_type;
	typedef typename E2::const_iterator2 const_iterator22_type;
	typedef const value_type *const_pointer;

public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
	typedef typename iterator_restrict_traits<typename const_iterator11_type::iterator_category,
	typename const_iterator22_type::iterator_category>::iterator_category iterator_category;
	typedef indexed_const_iterator1<const_closure_type, iterator_category> const_iterator1;
	typedef const_iterator1 iterator1;
	typedef indexed_const_iterator2<const_closure_type, iterator_category> const_iterator2;
	typedef const_iterator2 iterator2;
#else
	class const_iterator1;
	typedef const_iterator1 iterator1;
	class const_iterator2;
	typedef const_iterator2 iterator2;
#endif
	typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
	typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

	// Element lookup
	BOOST_UBLAS_INLINE
	const_iterator1 find1 (int /* rank */, size_type i, size_type j) const {
		// FIXME sparse matrix tests fail!
		// const_iterator11_type it11 (e1_.find1 (rank, i, 0));
		const_iterator11_type it11 (e1_.find1 (0, i, 0));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator1 (*this, it11.index1 (), j);
#else
		// FIXME sparse matrix tests fail!
		// const_iterator22_type it22 (e2_.find2 (rank, 0, j));
		const_iterator22_type it22 (e2_.find2 (0, 0, j));
		return const_iterator1 (*this, it11, it22);
#endif
	}
	BOOST_UBLAS_INLINE
	const_iterator2 find2 (int /* rank */, size_type i, size_type j) const {
		// FIXME sparse matrix tests fail!
		// const_iterator22_type it22 (e2_.find2 (rank, 0, j));
		const_iterator22_type it22 (e2_.find2 (0, 0, j));
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
		return const_iterator2 (*this, i, it22.index2 ());
#else
		// FIXME sparse matrix tests fail!
		// const_iterator11_type it11 (e1_.find1 (rank, i, 0));
		const_iterator11_type it11 (e1_.find1 (0, i, 0));
		return const_iterator2 (*this, it11, it22);
#endif
	}


#ifndef BOOST_UBLAS_USE_INDEXED_ITERATOR
	class const_iterator1:
	    public container_const_reference<matrix_matrix_binary>,
	    public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator1::iterator_category,
	    typename E2::const_iterator2::iterator_category>::iterator_category>::template
	    iterator_base<const_iterator1, value_type>::type {
	public:
		typedef typename iterator_restrict_traits<typename E1::const_iterator1::iterator_category,
		typename E2::const_iterator2::iterator_category>::iterator_category iterator_category;
		typedef typename matrix_matrix_binary::difference_type difference_type;
		typedef typename matrix_matrix_binary::value_type value_type;
		typedef typename matrix_matrix_binary::const_reference reference;
		typedef typename matrix_matrix_binary::const_pointer pointer;

		typedef const_iterator2 dual_iterator_type;
		typedef const_reverse_iterator2 dual_reverse_iterator_type;

		// Construction and destruction
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), it1_ (), it2_ (), it2_begin_ (), it2_end_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &mmb, const const_iterator11_type &it1, const const_iterator22_type &it2):
		  container_const_reference<self_type> (mmb), it1_ (it1), it2_ (it2), it2_begin_ (it2.begin ()), it2_end_ (it2.end ()) {}
#else
		BOOST_UBLAS_INLINE
		const_iterator1 ():
		  container_const_reference<self_type> (), it1_ (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator1 (const self_type &mmb, const const_iterator11_type &it1, const const_iterator22_type &it2):
		  container_const_reference<self_type> (mmb), it1_ (it1), it2_ (it2) {}
#endif

	private:
		// Random access specialization
		BOOST_UBLAS_INLINE
		value_type dereference (dense_random_access_iterator_tag) const {
			const self_type &mmb = (*this) ();
#ifdef BOOST_UBLAS_USE_INDEXING
			return mmb (index1 (), index2 ());
#elif BOOST_UBLAS_USE_ITERATING
			difference_type size = BOOST_UBLAS_SAME (mmb.expression1 ().size2 (), mmb.expression2 ().size1 ());
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (size, it1_.begin (), it2_begin_);
#else
			return functor_type::apply (size, it1_.begin (), it2_.begin ());
#endif
#else
			difference_type size = BOOST_UBLAS_SAME (mmb.expression1 ().size2 (), mmb.expression2 ().size1 ());
			if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
				return functor_type::apply (size, it1_.begin (), it2_begin_);
#else
				return functor_type::apply (size, it1_.begin (), it2_.begin ());
#endif
			else
				return mmb (index1 (), index2 ());
#endif
		}

		// Packed bidirectional specialization
		BOOST_UBLAS_INLINE
		value_type dereference (packed_random_access_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (it1_.begin (), it1_.end (),
			                            it2_begin_, it2_end_, packed_random_access_iterator_tag ());
#else
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
			return functor_type::apply (it1_.begin (), it1_.end (),
			                            it2_.begin (), it2_.end (), packed_random_access_iterator_tag ());
#else
			return functor_type::apply (boost::numeric::ublas::begin (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::end (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::begin (it2_, iterator2_tag ()),
			                            boost::numeric::ublas::end (it2_, iterator2_tag ()), packed_random_access_iterator_tag ());
#endif
#endif
		}

		// Sparse bidirectional specialization
		BOOST_UBLAS_INLINE
		value_type dereference (sparse_bidirectional_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (it1_.begin (), it1_.end (),
			                            it2_begin_, it2_end_, sparse_bidirectional_iterator_tag ());
#else
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
			return functor_type::apply (it1_.begin (), it1_.end (),
			                            it2_.begin (), it2_.end (), sparse_bidirectional_iterator_tag ());
#else
			return functor_type::apply (boost::numeric::ublas::begin (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::end (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::begin (it2_, iterator2_tag ()),
			                            boost::numeric::ublas::end (it2_, iterator2_tag ()), sparse_bidirectional_iterator_tag ());
#endif
#endif
		}

	public:
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
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ - it.it1_;
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
			return it1_.index1 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it2_.index2 ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator1 &operator = (const const_iterator1 &it) {
			container_const_reference<self_type>::assign (&it ());
			it1_ = it.it1_;
			it2_ = it.it2_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			it2_begin_ = it.it2_begin_;
			it2_end_ = it.it2_end_;
#endif
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ == it.it1_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator1 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
			return it1_ < it.it1_;
		}

	private:
		const_iterator11_type it1_;
		// Mutable due to assignment
		/* const */ const_iterator22_type it2_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		/* const */ const_iterator21_type it2_begin_;
		/* const */ const_iterator21_type it2_end_;
#endif
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
	class const_iterator2:
	    public container_const_reference<matrix_matrix_binary>,
	    public iterator_base_traits<typename iterator_restrict_traits<typename E1::const_iterator1::iterator_category,
	    typename E2::const_iterator2::iterator_category>::iterator_category>::template
	    iterator_base<const_iterator2, value_type>::type {
	public:
		typedef typename iterator_restrict_traits<typename E1::const_iterator1::iterator_category,
		typename E2::const_iterator2::iterator_category>::iterator_category iterator_category;
		typedef typename matrix_matrix_binary::difference_type difference_type;
		typedef typename matrix_matrix_binary::value_type value_type;
		typedef typename matrix_matrix_binary::const_reference reference;
		typedef typename matrix_matrix_binary::const_pointer pointer;

		typedef const_iterator1 dual_iterator_type;
		typedef const_reverse_iterator1 dual_reverse_iterator_type;

		// Construction and destruction
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), it1_ (), it2_ (), it1_begin_ (), it1_end_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &mmb, const const_iterator11_type &it1, const const_iterator22_type &it2):
		  container_const_reference<self_type> (mmb), it1_ (it1), it2_ (it2), it1_begin_ (it1.begin ()), it1_end_ (it1.end ()) {}
#else
		BOOST_UBLAS_INLINE
		const_iterator2 ():
		  container_const_reference<self_type> (), it1_ (), it2_ () {}
		BOOST_UBLAS_INLINE
		const_iterator2 (const self_type &mmb, const const_iterator11_type &it1, const const_iterator22_type &it2):
		  container_const_reference<self_type> (mmb), it1_ (it1), it2_ (it2) {}
#endif

	private:
		// Random access specialization
		BOOST_UBLAS_INLINE
		value_type dereference (dense_random_access_iterator_tag) const {
			const self_type &mmb = (*this) ();
#ifdef BOOST_UBLAS_USE_INDEXING
			return mmb (index1 (), index2 ());
#elif BOOST_UBLAS_USE_ITERATING
			difference_type size = BOOST_UBLAS_SAME (mmb.expression1 ().size2 (), mmb.expression2 ().size1 ());
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (size, it1_begin_, it2_.begin ());
#else
			return functor_type::apply (size, it1_.begin (), it2_.begin ());
#endif
#else
			difference_type size = BOOST_UBLAS_SAME (mmb.expression1 ().size2 (), mmb.expression2 ().size1 ());
			if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
				return functor_type::apply (size, it1_begin_, it2_.begin ());
#else
				return functor_type::apply (size, it1_.begin (), it2_.begin ());
#endif
			else
				return mmb (index1 (), index2 ());
#endif
		}

		// Packed bidirectional specialization
		BOOST_UBLAS_INLINE
		value_type dereference (packed_random_access_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (it1_begin_, it1_end_,
			                            it2_.begin (), it2_.end (), packed_random_access_iterator_tag ());
#else
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
			return functor_type::apply (it1_.begin (), it1_.end (),
			                            it2_.begin (), it2_.end (), packed_random_access_iterator_tag ());
#else
			return functor_type::apply (boost::numeric::ublas::begin (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::end (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::begin (it2_, iterator2_tag ()),
			                            boost::numeric::ublas::end (it2_, iterator2_tag ()), packed_random_access_iterator_tag ());
#endif
#endif
		}

		// Sparse bidirectional specialization
		BOOST_UBLAS_INLINE
		value_type dereference (sparse_bidirectional_iterator_tag) const {
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			return functor_type::apply (it1_begin_, it1_end_,
			                            it2_.begin (), it2_.end (), sparse_bidirectional_iterator_tag ());
#else
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
			return functor_type::apply (it1_.begin (), it1_.end (),
			                            it2_.begin (), it2_.end (), sparse_bidirectional_iterator_tag ());
#else
			return functor_type::apply (boost::numeric::ublas::begin (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::end (it1_, iterator1_tag ()),
			                            boost::numeric::ublas::begin (it2_, iterator2_tag ()),
			                            boost::numeric::ublas::end (it2_, iterator2_tag ()), sparse_bidirectional_iterator_tag ());
#endif
#endif
		}

	public:
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
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ - it.it2_;
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
			return it1_.index1 ();
		}
		BOOST_UBLAS_INLINE
		size_type index2 () const {
			return it2_.index2 ();
		}

		// Assignment
		BOOST_UBLAS_INLINE
		const_iterator2 &operator = (const const_iterator2 &it) {
			container_const_reference<self_type>::assign (&it ());
			it1_ = it.it1_;
			it2_ = it.it2_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
			it1_begin_ = it.it1_begin_;
			it1_end_ = it.it1_end_;
#endif
			return *this;
		}

		// Comparison
		BOOST_UBLAS_INLINE
		bool operator == (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ == it.it2_;
		}
		BOOST_UBLAS_INLINE
		bool operator < (const const_iterator2 &it) const {
			BOOST_UBLAS_CHECK ((*this) ().same_closure (it ()), external_logic ());
			BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
			return it2_ < it.it2_;
		}

	private:
		// Mutable due to assignment
		/* const */ const_iterator11_type it1_;
		const_iterator22_type it2_;
#ifdef BOOST_UBLAS_USE_INVARIANT_HOISTING
		/* const */ const_iterator12_type it1_begin_;
		/* const */ const_iterator12_type it1_end_;
#endif
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

private:
	expression1_closure_type e1_;
	expression2_closure_type e2_;
};

template<class T1, class E1, class T2, class E2>
struct matrix_matrix_binary_traits {
	typedef unknown_storage_tag storage_category;
	typedef unknown_orientation_tag orientation_category;
	typedef typename promote_traits<T1, T2>::promote_type promote_type;
	typedef matrix_matrix_binary<E1, E2, matrix_matrix_prod<E1, E2, promote_type> > expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename E1::matrix_temporary_type result_type;
#endif
};

template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_matrix_binary_traits<typename E1::value_type, E1,
typename E2::value_type, E2>::result_type
prod (const matrix_expression<E1> &e1,
      const matrix_expression<E2> &e2,
      unknown_storage_tag,
      unknown_orientation_tag) {
	typedef typename matrix_matrix_binary_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// Dispatcher
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_matrix_binary_traits<typename E1::value_type, E1,
typename E2::value_type, E2>::result_type
prod (const matrix_expression<E1> &e1,
      const matrix_expression<E2> &e2) {
	BOOST_STATIC_ASSERT (E1::complexity == 0 && E2::complexity == 0);
	typedef typename matrix_matrix_binary_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::storage_category storage_category;
	typedef typename matrix_matrix_binary_traits<typename E1::value_type, E1,
	    typename E2::value_type, E2>::orientation_category orientation_category;
	return prod (e1, e2, storage_category (), orientation_category ());
}

template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_matrix_binary_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
prec_prod (const matrix_expression<E1> &e1,
           const matrix_expression<E2> &e2,
           unknown_storage_tag,
           unknown_orientation_tag) {
	typedef typename matrix_matrix_binary_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::expression_type expression_type;
	return expression_type (e1 (), e2 ());
}

// Dispatcher
template<class E1, class E2>
BOOST_UBLAS_INLINE
typename matrix_matrix_binary_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
typename type_traits<typename E2::value_type>::precision_type, E2>::result_type
prec_prod (const matrix_expression<E1> &e1,
           const matrix_expression<E2> &e2) {
	BOOST_STATIC_ASSERT (E1::complexity == 0 && E2::complexity == 0);
	typedef typename matrix_matrix_binary_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::storage_category storage_category;
	typedef typename matrix_matrix_binary_traits<typename type_traits<typename E1::value_type>::precision_type, E1,
	    typename type_traits<typename E2::value_type>::precision_type, E2>::orientation_category orientation_category;
	return prec_prod (e1, e2, storage_category (), orientation_category ());
}

template<class M, class E1, class E2>
BOOST_UBLAS_INLINE
M &
prod (const matrix_expression<E1> &e1,
      const matrix_expression<E2> &e2,
      M &m) {
	return m.assign (prod (e1, e2));
}

template<class M, class E1, class E2>
BOOST_UBLAS_INLINE
M &
prec_prod (const matrix_expression<E1> &e1,
           const matrix_expression<E2> &e2,
           M &m) {
	return m.assign (prec_prod (e1, e2));
}

template<class M, class E1, class E2>
BOOST_UBLAS_INLINE
M
prod (const matrix_expression<E1> &e1,
      const matrix_expression<E2> &e2) {
	return M (prod (e1, e2));
}

template<class M, class E1, class E2>
BOOST_UBLAS_INLINE
M
prec_prod (const matrix_expression<E1> &e1,
           const matrix_expression<E2> &e2) {
	return M (prec_prod (e1, e2));
}

template<class E, class F>
class matrix_scalar_unary:
    public scalar_expression<matrix_scalar_unary<E, F> > {
public:
	typedef E expression_type;
	typedef F functor_type;
	typedef typename F::result_type value_type;
	typedef typename E::const_closure_type expression_closure_type;

	// Construction and destruction
	BOOST_UBLAS_INLINE
	explicit matrix_scalar_unary (const expression_type &e):
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
		return functor_type::apply (e_);
	}

private:
	expression_closure_type e_;
};

template<class E, class F>
struct matrix_scalar_unary_traits {
	typedef matrix_scalar_unary<E, F> expression_type;
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
	typedef expression_type result_type;
#else
	typedef typename F::result_type result_type;
#endif
};

template<class E>
BOOST_UBLAS_INLINE
typename matrix_scalar_unary_traits<E, matrix_norm_1<E> >::result_type
norm_1 (const matrix_expression<E> &e) {
	typedef typename matrix_scalar_unary_traits<E, matrix_norm_1<E> >::expression_type expression_type;
	return expression_type (e ());
}

template<class E>
BOOST_UBLAS_INLINE
typename matrix_scalar_unary_traits<E, matrix_norm_frobenius<E> >::result_type
norm_frobenius (const matrix_expression<E> &e) {
	typedef typename matrix_scalar_unary_traits<E, matrix_norm_frobenius<E> >::expression_type expression_type;
	return expression_type (e ());
}

template<class E>
BOOST_UBLAS_INLINE
typename matrix_scalar_unary_traits<E, matrix_norm_inf<E> >::result_type
norm_inf (const matrix_expression<E> &e) {
	typedef typename matrix_scalar_unary_traits<E, matrix_norm_inf<E> >::expression_type expression_type;
	return expression_type (e ());
}

}}}

#endif

/* matrix_expression.hpp
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
*/