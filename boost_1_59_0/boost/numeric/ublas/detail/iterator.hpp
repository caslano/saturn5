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

#ifndef _BOOST_UBLAS_ITERATOR_
#define _BOOST_UBLAS_ITERATOR_

#include <boost/numeric/ublas/exception.hpp>
#include <iterator>


namespace boost { namespace numeric { namespace ublas {

  /** \brief Base class of all proxy classes that contain
   *       a (redirectable) reference to an immutable object.
   *
   *       \param C the type of the container referred to
   */
    template<class C>
    class container_const_reference:
        private nonassignable {
    public:
        typedef C container_type;

        BOOST_UBLAS_INLINE
        container_const_reference ():
            c_ (0) {}
        BOOST_UBLAS_INLINE
        container_const_reference (const container_type &c):
            c_ (&c) {}

        BOOST_UBLAS_INLINE
        const container_type &operator () () const {
            return *c_;
        }

        BOOST_UBLAS_INLINE
        container_const_reference &assign (const container_type *c) {
            c_ = c;
            return *this;
        }
        
        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const container_const_reference &cr) const {
            return c_ == cr.c_;
        }

    private:
        const container_type *c_;
    };

  /** \brief Base class of all proxy classes that contain
   *         a (redirectable) reference to a mutable object.
   *
   * \param C the type of the container referred to
   */
    template<class C>
    class container_reference:
        private nonassignable {
    public:
        typedef C container_type;

        BOOST_UBLAS_INLINE
        container_reference ():
            c_ (0) {}
        BOOST_UBLAS_INLINE
        container_reference (container_type &c):
            c_ (&c) {}

        BOOST_UBLAS_INLINE
        container_type &operator () () const {
           return *c_;
        }

        BOOST_UBLAS_INLINE
        container_reference &assign (container_type *c) {
            c_ = c;
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const container_reference &cr) const {
            return c_ == cr.c_;
        }

    private:
        container_type *c_;
    };

  /** \brief Base class of all forward iterators.
   * 
   *  \param IC the iterator category
   *  \param I the derived iterator type
   *  \param T the value type
   * 
   * The forward iterator can only proceed in one direction
   * via the post increment operator.
   */
    template<class IC, class I, class T>
    struct forward_iterator_base:
        public std::iterator<IC, T> {
        typedef I derived_iterator_type;
        typedef T derived_value_type;

        // Arithmetic
        BOOST_UBLAS_INLINE
        derived_iterator_type operator ++ (int) {
            derived_iterator_type &d (*static_cast<const derived_iterator_type *> (this));
            derived_iterator_type tmp (d);
            ++ d;
            return tmp;
        }
        BOOST_UBLAS_INLINE
        friend derived_iterator_type operator ++ (derived_iterator_type &d, int) {
            derived_iterator_type tmp (d);
            ++ d;
            return tmp;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator != (const derived_iterator_type &it) const {
            const derived_iterator_type *d = static_cast<const derived_iterator_type *> (this);
            return ! (*d == it);
        }
    };

  /** \brief Base class of all bidirectional iterators.
   *
   * \param IC the iterator category
   * \param I the derived iterator type
   * \param T the value type
   *
   * The bidirectional iterator can proceed in both directions
   * via the post increment and post decrement operator.
   */
    template<class IC, class I, class T>
    struct bidirectional_iterator_base:
        public std::iterator<IC, T> {
        typedef I derived_iterator_type;
        typedef T derived_value_type;

        // Arithmetic
        BOOST_UBLAS_INLINE
        derived_iterator_type operator ++ (int) {
            derived_iterator_type &d (*static_cast<const derived_iterator_type *> (this));
            derived_iterator_type tmp (d);
            ++ d;
            return tmp;
        }
        BOOST_UBLAS_INLINE
        friend derived_iterator_type operator ++ (derived_iterator_type &d, int) {
            derived_iterator_type tmp (d);
            ++ d;
            return tmp;
        }
        BOOST_UBLAS_INLINE
        derived_iterator_type operator -- (int) {
            derived_iterator_type &d (*static_cast<const derived_iterator_type *> (this));
            derived_iterator_type tmp (d);
            -- d;
            return tmp;
        }
        BOOST_UBLAS_INLINE
        friend derived_iterator_type operator -- (derived_iterator_type &d, int) {
            derived_iterator_type tmp (d);
            -- d;
            return tmp;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator != (const derived_iterator_type &it) const {
            const derived_iterator_type *d = static_cast<const derived_iterator_type *> (this);
            return ! (*d == it);
        }
    };

  /** \brief Base class of all random access iterators.
   *
   * \param IC the iterator category
   * \param I the derived iterator type
   * \param T the value type
   * \param D the difference type, default: std::ptrdiff_t
   *
   * The random access iterator can proceed in both directions
   * via the post increment/decrement operator or in larger steps
   * via the +, - and +=, -= operators. The random access iterator
   * is LessThan Comparable.
   */
    template<class IC, class I, class T, class D = std::ptrdiff_t>
    // ISSUE the default for D seems rather dangerous as it can easily be (silently) incorrect
    struct random_access_iterator_base:
        public std::iterator<IC, T> {
        typedef I derived_iterator_type;
        typedef T derived_value_type;
        typedef D derived_difference_type;

        /* FIXME Need to explicitly pass derived_reference_type as otherwise I undefined type or forward declared
        typedef typename derived_iterator_type::reference derived_reference_type;
        // Indexed element
        BOOST_UBLAS_INLINE
        derived_reference_type operator [] (derived_difference_type n) {
            return *(*this + n);
        }
        */

        // Arithmetic
        BOOST_UBLAS_INLINE
        derived_iterator_type operator ++ (int) {
            derived_iterator_type &d (*static_cast<derived_iterator_type *> (this));
            derived_iterator_type tmp (d);
            ++ d;
            return tmp;
        }
        BOOST_UBLAS_INLINE
        friend derived_iterator_type operator ++ (derived_iterator_type &d, int) {
            derived_iterator_type tmp (d);
            ++ d;
            return tmp;
        }
        BOOST_UBLAS_INLINE
        derived_iterator_type operator -- (int) {
            derived_iterator_type &d (*static_cast<derived_iterator_type *> (this));
            derived_iterator_type tmp (d);
            -- d;
            return tmp;
        }
        BOOST_UBLAS_INLINE
        friend derived_iterator_type operator -- (derived_iterator_type &d, int) {
            derived_iterator_type tmp (d);
            -- d;
            return tmp;
        }
        BOOST_UBLAS_INLINE
        derived_iterator_type operator + (derived_difference_type n) const {
            derived_iterator_type tmp (*static_cast<const derived_iterator_type *> (this));
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        friend derived_iterator_type operator + (const derived_iterator_type &d, derived_difference_type n) {
            derived_iterator_type tmp (d);
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        friend derived_iterator_type operator + (derived_difference_type n, const derived_iterator_type &d) {
            derived_iterator_type tmp (d);
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        derived_iterator_type operator - (derived_difference_type n) const {
            derived_iterator_type tmp (*static_cast<const derived_iterator_type *> (this));
            return tmp -= n;
        }
        BOOST_UBLAS_INLINE
        friend derived_iterator_type operator - (const derived_iterator_type &d, derived_difference_type n) {
            derived_iterator_type tmp (d);
            return tmp -= n;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator != (const derived_iterator_type &it) const {
            const derived_iterator_type *d = static_cast<const derived_iterator_type *> (this);
            return ! (*d == it);
        }
        BOOST_UBLAS_INLINE
        bool operator <= (const derived_iterator_type &it) const {
            const derived_iterator_type *d = static_cast<const derived_iterator_type *> (this);
            return ! (it < *d);
        }
        BOOST_UBLAS_INLINE
        bool operator >= (const derived_iterator_type &it) const {
            const derived_iterator_type *d = static_cast<const derived_iterator_type *> (this);
            return ! (*d < it);
        }
        BOOST_UBLAS_INLINE
        bool operator > (const derived_iterator_type &it) const {
            const derived_iterator_type *d = static_cast<const derived_iterator_type *> (this);
            return it < *d;
        }
    };

  /** \brief Base class of all reverse iterators. (non-MSVC version)
   *
   * \param I the derived iterator type
   * \param T the value type
   * \param R the reference type
   *
   * The reverse iterator implements a bidirectional iterator
   * reversing the elements of the underlying iterator. It
   * implements most operators of a random access iterator.
   *
   * uBLAS extension: it.index()
   */

    // Renamed this class from reverse_iterator to get
    // typedef reverse_iterator<...> reverse_iterator
    // working. Thanks to Gabriel Dos Reis for explaining this.
    template <class I>
    class reverse_iterator_base:
        public std::reverse_iterator<I> {
    public:
        typedef typename I::container_type container_type;
        typedef typename container_type::size_type size_type;
        typedef typename I::difference_type difference_type;
        typedef I iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        reverse_iterator_base ():
            std::reverse_iterator<iterator_type> () {}
        BOOST_UBLAS_INLINE
        reverse_iterator_base (const iterator_type &it):
            std::reverse_iterator<iterator_type> (it) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        reverse_iterator_base &operator ++ () {
            return *this = -- this->base ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base operator ++ (int) {
            reverse_iterator_base tmp (*this);
            *this = -- this->base ();
            return tmp;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base &operator -- () {
            return *this = ++ this->base ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base operator -- (int) {
            reverse_iterator_base tmp (*this);
            *this = ++ this->base ();
            return tmp;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base &operator += (difference_type n) {
            return *this = this->base () - n;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base &operator -= (difference_type n) {
            return *this = this->base () + n;
        }

        BOOST_UBLAS_INLINE
        friend reverse_iterator_base operator + (const reverse_iterator_base &it, difference_type n) {
            reverse_iterator_base tmp (it);
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        friend reverse_iterator_base operator + (difference_type n, const reverse_iterator_base &it) {
            reverse_iterator_base tmp (it);
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        friend reverse_iterator_base operator - (const reverse_iterator_base &it, difference_type n) {
            reverse_iterator_base tmp (it);
            return tmp -= n;
        }
        BOOST_UBLAS_INLINE
        friend difference_type operator - (const reverse_iterator_base &it1, const reverse_iterator_base &it2) {
            return it2.base () - it1.base ();
        }

        BOOST_UBLAS_INLINE
        const container_type &operator () () const {
            return this->base () ();
        }

        BOOST_UBLAS_INLINE
        size_type index () const {
            iterator_type tmp (this->base ());
            return (-- tmp).index ();
        }
    };

  /** \brief 1st base class of all matrix reverse iterators. (non-MSVC version)
   *
   * \param I the derived iterator type
   *
   * The reverse iterator implements a bidirectional iterator
   * reversing the elements of the underlying iterator. It
   * implements most operators of a random access iterator.
   *
   * uBLAS extension: it.index1(), it.index2() and access to
   * the dual iterator via begin(), end(), rbegin(), rend()
   */

    // Renamed this class from reverse_iterator1 to get
    // typedef reverse_iterator1<...> reverse_iterator1
    // working. Thanks to Gabriel Dos Reis for explaining this.
    template <class I>
    class reverse_iterator_base1:
        public std::reverse_iterator<I> {
    public:
        typedef typename I::container_type container_type;
        typedef typename container_type::size_type size_type;
        typedef typename I::difference_type difference_type;
        typedef I iterator_type;
        typedef typename I::dual_iterator_type dual_iterator_type;
        typedef typename I::dual_reverse_iterator_type dual_reverse_iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        reverse_iterator_base1 ():
            std::reverse_iterator<iterator_type> () {}
        BOOST_UBLAS_INLINE
        reverse_iterator_base1 (const iterator_type &it):
            std::reverse_iterator<iterator_type> (it) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        reverse_iterator_base1 &operator ++ () {
            return *this = -- this->base ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base1 operator ++ (int) {
            reverse_iterator_base1 tmp (*this);
            *this = -- this->base ();
            return tmp;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base1 &operator -- () {
            return *this = ++ this->base ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base1 operator -- (int) {
            reverse_iterator_base1 tmp (*this);
            *this = ++ this->base ();
            return tmp;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base1 &operator += (difference_type n) {
            return *this = this->base () - n;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base1 &operator -= (difference_type n) {
            return *this = this->base () + n;
        }

        BOOST_UBLAS_INLINE
        friend reverse_iterator_base1 operator + (const reverse_iterator_base1 &it, difference_type n) {
            reverse_iterator_base1 tmp (it);
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        friend reverse_iterator_base1 operator + (difference_type n, const reverse_iterator_base1 &it) {
            reverse_iterator_base1 tmp (it);
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        friend reverse_iterator_base1 operator - (const reverse_iterator_base1 &it, difference_type n) {
            reverse_iterator_base1 tmp (it);
            return tmp -= n;
        }
        BOOST_UBLAS_INLINE
        friend difference_type operator - (const reverse_iterator_base1 &it1, const reverse_iterator_base1 &it2) {
            return it2.base () - it1.base ();
        }

        BOOST_UBLAS_INLINE
        const container_type &operator () () const {
            return this->base () ();
        }

        BOOST_UBLAS_INLINE
        size_type index1 () const {
            iterator_type tmp (this->base ());
            return (-- tmp).index1 ();
        }
        BOOST_UBLAS_INLINE
        size_type index2 () const {
            iterator_type tmp (this->base ());
            return (-- tmp).index2 ();
        }

        BOOST_UBLAS_INLINE
        dual_iterator_type begin () const {
            iterator_type tmp (this->base ());
            return (-- tmp).begin ();
        }
        BOOST_UBLAS_INLINE
        dual_iterator_type end () const {
            iterator_type tmp (this->base ());
            return (-- tmp).end ();
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rbegin () const {
            return dual_reverse_iterator_type (end ());
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rend () const {
            return dual_reverse_iterator_type (begin ());
        }
    };

  /** \brief 2nd base class of all matrix reverse iterators. (non-MSVC version)
   *
   * \param I the derived iterator type
   *
   * The reverse iterator implements a bidirectional iterator
   * reversing the elements of the underlying iterator. It
   * implements most operators of a random access iterator.
   *
   * uBLAS extension: it.index1(), it.index2() and access to
   * the dual iterator via begin(), end(), rbegin(), rend()
   *
   * Note: this type is _identical_ to reverse_iterator_base1
   */

    // Renamed this class from reverse_iterator2 to get
    // typedef reverse_iterator2<...> reverse_iterator2
    // working. Thanks to Gabriel Dos Reis for explaining this.
    template <class I>
    class reverse_iterator_base2:
        public std::reverse_iterator<I> {
    public:
        typedef typename I::container_type container_type;
        typedef typename container_type::size_type size_type;
        typedef typename I::difference_type difference_type;
        typedef I iterator_type;
        typedef typename I::dual_iterator_type dual_iterator_type;
        typedef typename I::dual_reverse_iterator_type dual_reverse_iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        reverse_iterator_base2 ():
            std::reverse_iterator<iterator_type> () {}
        BOOST_UBLAS_INLINE
        reverse_iterator_base2 (const iterator_type &it):
            std::reverse_iterator<iterator_type> (it) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        reverse_iterator_base2 &operator ++ () {
            return *this = -- this->base ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base2 operator ++ (int) {
            reverse_iterator_base2 tmp (*this);
            *this = -- this->base ();
            return tmp;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base2 &operator -- () {
            return *this = ++ this->base ();
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base2 operator -- (int) {
            reverse_iterator_base2 tmp (*this);
            *this = ++ this->base ();
            return tmp;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base2 &operator += (difference_type n) {
            return *this = this->base () - n;
        }
        BOOST_UBLAS_INLINE
        reverse_iterator_base2 &operator -= (difference_type n) {
            return *this = this->base () + n;
        }

        BOOST_UBLAS_INLINE
        friend reverse_iterator_base2 operator + (const reverse_iterator_base2 &it, difference_type n) {
            reverse_iterator_base2 tmp (it);
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        friend reverse_iterator_base2 operator + (difference_type n, const reverse_iterator_base2 &it) {
            reverse_iterator_base2 tmp (it);
            return tmp += n;
        }
        BOOST_UBLAS_INLINE
        friend reverse_iterator_base2 operator - (const reverse_iterator_base2 &it, difference_type n) {
            reverse_iterator_base2 tmp (it);
            return tmp -= n;
        }
        BOOST_UBLAS_INLINE
        friend difference_type operator - (const reverse_iterator_base2 &it1, const reverse_iterator_base2 &it2) {
            return it2.base () - it1.base ();
        }

        BOOST_UBLAS_INLINE
        const container_type &operator () () const {
            return this->base () ();
        }

        BOOST_UBLAS_INLINE
        size_type index1 () const {
            iterator_type tmp (this->base ());
            return (-- tmp).index1 ();
        }
        BOOST_UBLAS_INLINE
        size_type index2 () const {
            iterator_type tmp (this->base ());
            return (-- tmp).index2 ();
        }

        BOOST_UBLAS_INLINE
        dual_iterator_type begin () const {
            iterator_type tmp (this->base ());
            return (-- tmp).begin ();
        }
        BOOST_UBLAS_INLINE
        dual_iterator_type end () const {
            iterator_type tmp (this->base ());
            return (-- tmp).end ();
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rbegin () const {
            return dual_reverse_iterator_type (end ());
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rend () const {
            return dual_reverse_iterator_type (begin ());
        }
    };

  /** \brief A class implementing an indexed random access iterator.
   *
   * \param C the (mutable) container type
   * \param IC the iterator category
   *
   * This class implements a random access iterator. The current 
   * position is stored as the unsigned integer it_ and the
   * values are accessed via operator()(it_) of the container.
   *
   * uBLAS extension: index()
   */

    template<class C, class IC>
    class indexed_iterator:
        public container_reference<C>,
        public random_access_iterator_base<IC,
                                           indexed_iterator<C, IC>,
                                           typename C::value_type,
                                           typename C::difference_type> {
    public:
        typedef C container_type;
        typedef IC iterator_category;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::difference_type difference_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::reference reference;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        indexed_iterator ():
            container_reference<container_type> (), it_ () {}
        BOOST_UBLAS_INLINE
        indexed_iterator (container_type &c, size_type it):
            container_reference<container_type> (c), it_ (it) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        indexed_iterator &operator ++ () {
            ++ it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator &operator -- () {
            -- it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator &operator += (difference_type n) {
            it_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator &operator -= (difference_type n) {
            it_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const indexed_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ - it.it_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
            return (*this) () (it_);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (difference_type n) const {
            return *((*this) + n);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index () const {
            return it_;
        }

        // Assignment
        BOOST_UBLAS_INLINE
        indexed_iterator &operator = (const indexed_iterator &it) {
            // FIX: ICC needs full qualification?!
            // assign (&it ());
            container_reference<C>::assign (&it ());
            it_ = it.it_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const indexed_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ == it.it_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const indexed_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ < it.it_;
        }

    private:
        size_type it_;
    };

  /** \brief A class implementing an indexed random access iterator.
   *
   * \param C the (immutable) container type
   * \param IC the iterator category
   *
   * This class implements a random access iterator. The current 
   * position is stored as the unsigned integer \c it_ and the
   * values are accessed via \c operator()(it_) of the container.
   *
   * uBLAS extension: \c index()
   *
   * Note: there is an automatic conversion from 
   * \c indexed_iterator to \c indexed_const_iterator
   */

    template<class C, class IC>
    class indexed_const_iterator:
        public container_const_reference<C>,
        public random_access_iterator_base<IC,
                                           indexed_const_iterator<C, IC>,
                                           typename C::value_type,
                                           typename C::difference_type> {
    public:
        typedef C container_type;
        typedef IC iterator_category;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::difference_type difference_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::const_reference reference;
        typedef indexed_iterator<container_type, iterator_category> iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        indexed_const_iterator ():
            container_const_reference<container_type> (), it_ () {}
        BOOST_UBLAS_INLINE
        indexed_const_iterator (const container_type &c, size_type it):
            container_const_reference<container_type> (c), it_ (it) {}
        BOOST_UBLAS_INLINE 
        indexed_const_iterator (const iterator_type &it):
            container_const_reference<container_type> (it ()), it_ (it.index ()) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        indexed_const_iterator &operator ++ () {
            ++ it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator &operator -- () {
            -- it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator &operator += (difference_type n) {
            it_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator &operator -= (difference_type n) {
            it_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const indexed_const_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ - it.it_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
            return (*this) () (it_);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (difference_type n) const {
            return *((*this) + n);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index () const {
            return it_;
        }

        // Assignment
        BOOST_UBLAS_INLINE
        indexed_const_iterator &operator = (const indexed_const_iterator &it) {
            // FIX: ICC needs full qualification?!
            // assign (&it ());
            container_const_reference<C>::assign (&it ());
            it_ = it.it_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const indexed_const_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ == it.it_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const indexed_const_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ < it.it_;
        }

    private:
        size_type it_;

        friend class indexed_iterator<container_type, iterator_category>;
    };

    template<class C, class IC>
    class indexed_iterator2;

  /** \brief A class implementing an indexed random access iterator 
   * of a matrix.
   *
   * \param C the (mutable) container type
   * \param IC the iterator category
   *
   * This class implements a random access iterator. The current
   * position is stored as two unsigned integers \c it1_ and \c it2_
   * and the values are accessed via \c operator()(it1_, it2_) of the
   * container. The iterator changes the first index.
   *
   * uBLAS extension: \c index1(), \c index2() and access to the
   * dual iterator via \c begin(), \c end(), \c rbegin() and \c rend()
   *
   * Note: The container has to support the \code find2(rank, i, j) \endcode 
   * method
   */

    template<class C, class IC>
    class indexed_iterator1:
        public container_reference<C>, 
        public random_access_iterator_base<IC,
                                           indexed_iterator1<C, IC>, 
                                           typename C::value_type,
                                           typename C::difference_type> {
    public:
        typedef C container_type;
        typedef IC iterator_category;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::difference_type difference_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::reference reference;

        typedef indexed_iterator2<container_type, iterator_category> dual_iterator_type;
        typedef reverse_iterator_base2<dual_iterator_type> dual_reverse_iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        indexed_iterator1 ():
            container_reference<container_type> (), it1_ (), it2_ () {}
        BOOST_UBLAS_INLINE 
        indexed_iterator1 (container_type &c, size_type it1, size_type it2):
            container_reference<container_type> (c), it1_ (it1), it2_ (it2) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        indexed_iterator1 &operator ++ () {
            ++ it1_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator1 &operator -- () {
            -- it1_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator1 &operator += (difference_type n) {
            it1_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator1 &operator -= (difference_type n) {
            it1_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const indexed_iterator1 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
            return it1_ - it.it1_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
            BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
            return (*this) () (it1_, it2_);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (difference_type n) const {
            return *((*this) + n);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index1 () const {
            return it1_;
        }
        BOOST_UBLAS_INLINE
        size_type index2 () const {
            return it2_;
        }

        BOOST_UBLAS_INLINE
        dual_iterator_type begin () const {
            return (*this) ().find2 (1, index1 (), 0); 
        }
        BOOST_UBLAS_INLINE
        dual_iterator_type end () const {
            return (*this) ().find2 (1, index1 (), (*this) ().size2 ());
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rbegin () const {
            return dual_reverse_iterator_type (end ());
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rend () const {
            return dual_reverse_iterator_type (begin ());
        }

        // Assignment
        BOOST_UBLAS_INLINE
        indexed_iterator1 &operator = (const indexed_iterator1 &it) {
            // FIX: ICC needs full qualification?!
            // assign (&it ());
            container_reference<C>::assign (&it ());
            it1_ = it.it1_;
            it2_ = it.it2_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const indexed_iterator1 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
            return it1_ == it.it1_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const indexed_iterator1 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
            return it1_ < it.it1_;
        }

    private:
        size_type it1_;
        size_type it2_;
    };

    template<class C, class IC>
    class indexed_const_iterator2;

  /** \brief A class implementing an indexed random access iterator 
   * of a matrix.
   *
   * \param C the (immutable) container type
   * \param IC the iterator category
   *
   * This class implements a random access iterator. The current
   * position is stored as two unsigned integers \c it1_ and \c it2_
   * and the values are accessed via \c operator()(it1_, it2_) of the
   * container. The iterator changes the first index.
   *
   * uBLAS extension: \c index1(), \c index2() and access to the
   * dual iterator via \c begin(), \c end(), \c rbegin() and \c rend()
   *
   * Note 1: The container has to support the find2(rank, i, j) method
   *
   * Note 2: there is an automatic conversion from 
   * \c indexed_iterator1 to \c indexed_const_iterator1
   */

    template<class C, class IC>
    class indexed_const_iterator1:
        public container_const_reference<C>, 
        public random_access_iterator_base<IC,
                                           indexed_const_iterator1<C, IC>, 
                                           typename C::value_type,
                                           typename C::difference_type> {
    public:
        typedef C container_type;
        typedef IC iterator_category;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::difference_type difference_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::const_reference reference;

        typedef indexed_iterator1<container_type, iterator_category> iterator_type;
        typedef indexed_const_iterator2<container_type, iterator_category> dual_iterator_type;
        typedef reverse_iterator_base2<dual_iterator_type> dual_reverse_iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        indexed_const_iterator1 ():
            container_const_reference<container_type> (), it1_ (), it2_ () {}
        BOOST_UBLAS_INLINE
        indexed_const_iterator1 (const container_type &c, size_type it1, size_type it2):
            container_const_reference<container_type> (c), it1_ (it1), it2_ (it2) {}
        BOOST_UBLAS_INLINE 
        indexed_const_iterator1 (const iterator_type &it):
            container_const_reference<container_type> (it ()), it1_ (it.index1 ()), it2_ (it.index2 ()) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        indexed_const_iterator1 &operator ++ () {
            ++ it1_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator1 &operator -- () {
            -- it1_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator1 &operator += (difference_type n) {
            it1_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator1 &operator -= (difference_type n) {
            it1_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const indexed_const_iterator1 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
            return it1_ - it.it1_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
            BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
            return (*this) () (it1_, it2_);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (difference_type n) const {
            return *((*this) + n);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index1 () const {
            return it1_;
        }
        BOOST_UBLAS_INLINE
        size_type index2 () const {
            return it2_;
        }

        BOOST_UBLAS_INLINE
        dual_iterator_type begin () const {
            return (*this) ().find2 (1, index1 (), 0); 
        }
        BOOST_UBLAS_INLINE
        dual_iterator_type end () const {
            return (*this) ().find2 (1, index1 (), (*this) ().size2 ()); 
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rbegin () const {
            return dual_reverse_iterator_type (end ()); 
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rend () const {
            return dual_reverse_iterator_type (begin ()); 
        }

        // Assignment
        BOOST_UBLAS_INLINE
        indexed_const_iterator1 &operator = (const indexed_const_iterator1 &it) {
            // FIX: ICC needs full qualification?!
            // assign (&it ());
            container_const_reference<C>::assign (&it ());
            it1_ = it.it1_;
            it2_ = it.it2_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const indexed_const_iterator1 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
            return it1_ == it.it1_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const indexed_const_iterator1 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it2_ == it.it2_, external_logic ());
            return it1_ < it.it1_;
        }

    private:
        size_type it1_;
        size_type it2_;

        friend class indexed_iterator1<container_type, iterator_category>;
    };

  /** \brief A class implementing an indexed random access iterator 
   * of a matrix.
   *
   * \param C the (mutable) container type
   * \param IC the iterator category
   *
   * This class implements a random access iterator. The current
   * position is stored as two unsigned integers \c it1_ and \c it2_
   * and the values are accessed via \c operator()(it1_, it2_) of the
   * container. The iterator changes the second index.
   *
   * uBLAS extension: \c index1(), \c index2() and access to the
   * dual iterator via \c begin(), \c end(), \c rbegin() and \c rend()
   *
   * Note: The container has to support the find1(rank, i, j) method
   */
    template<class C, class IC>
    class indexed_iterator2:
        public container_reference<C>, 
        public random_access_iterator_base<IC,
                                           indexed_iterator2<C, IC>, 
                                           typename C::value_type,
                                           typename C::difference_type> {
    public:
        typedef C container_type;
        typedef IC iterator_category;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::difference_type difference_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::reference reference;

        typedef indexed_iterator1<container_type, iterator_category> dual_iterator_type;
        typedef reverse_iterator_base1<dual_iterator_type> dual_reverse_iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        indexed_iterator2 ():
            container_reference<container_type> (), it1_ (), it2_ () {}
        BOOST_UBLAS_INLINE
        indexed_iterator2 (container_type &c, size_type it1, size_type it2):
            container_reference<container_type> (c), it1_ (it1), it2_ (it2) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        indexed_iterator2 &operator ++ () {
            ++ it2_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator2 &operator -- () {
            -- it2_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator2 &operator += (difference_type n) {
            it2_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_iterator2 &operator -= (difference_type n) {
            it2_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const indexed_iterator2 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
            return it2_ - it.it2_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
            BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
            return (*this) () (it1_, it2_);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (difference_type n) const {
            return *((*this) + n);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index1 () const {
            return it1_;
        }
        BOOST_UBLAS_INLINE
        size_type index2 () const {
            return it2_;
        }

        BOOST_UBLAS_INLINE
        dual_iterator_type begin () const {
            return (*this) ().find1 (1, 0, index2 ());
        }
        BOOST_UBLAS_INLINE
        dual_iterator_type end () const {
            return (*this) ().find1 (1, (*this) ().size1 (), index2 ());
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rbegin () const {
            return dual_reverse_iterator_type (end ());
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rend () const {
            return dual_reverse_iterator_type (begin ());
        }

        // Assignment
        BOOST_UBLAS_INLINE
        indexed_iterator2 &operator = (const indexed_iterator2 &it) {
            // FIX: ICC needs full qualification?!
            // assign (&it ());
            container_reference<C>::assign (&it ());
            it1_ = it.it1_;
            it2_ = it.it2_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const indexed_iterator2 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
            return it2_ == it.it2_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const indexed_iterator2 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
            return it2_ < it.it2_;
        }

    private:
        size_type it1_;
        size_type it2_;
    };

  /** \brief A class implementing an indexed random access iterator 
   * of a matrix.
   *
   * \param C the (immutable) container type
   * \param IC the iterator category
   *
   * This class implements a random access iterator. The current
   * position is stored as two unsigned integers \c it1_ and \c it2_
   * and the values are accessed via \c operator()(it1_, it2_) of the
   * container. The iterator changes the second index.
   *
   * uBLAS extension: \c index1(), \c index2() and access to the
   * dual iterator via \c begin(), \c end(), \c rbegin() and \c rend()
   *
   * Note 1: The container has to support the \c find2(rank, i, j) method
   *
   * Note 2: there is an automatic conversion from 
   * \c indexed_iterator2 to \c indexed_const_iterator2
   */

    template<class C, class IC>
    class indexed_const_iterator2:
        public container_const_reference<C>,
        public random_access_iterator_base<IC,
                                           indexed_const_iterator2<C, IC>,
                                           typename C::value_type,
                                           typename C::difference_type> {
    public:
        typedef C container_type;
        typedef IC iterator_category;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::difference_type difference_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::const_reference reference;

        typedef indexed_iterator2<container_type, iterator_category> iterator_type;
        typedef indexed_const_iterator1<container_type, iterator_category> dual_iterator_type;
        typedef reverse_iterator_base1<dual_iterator_type> dual_reverse_iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        indexed_const_iterator2 ():
            container_const_reference<container_type> (), it1_ (), it2_ () {}
        BOOST_UBLAS_INLINE
        indexed_const_iterator2 (const container_type &c, size_type it1, size_type it2):
            container_const_reference<container_type> (c), it1_ (it1), it2_ (it2) {}
        BOOST_UBLAS_INLINE
        indexed_const_iterator2 (const iterator_type &it):
            container_const_reference<container_type> (it ()), it1_ (it.index1 ()), it2_ (it.index2 ()) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        indexed_const_iterator2 &operator ++ () {
            ++ it2_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator2 &operator -- () {
            -- it2_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator2 &operator += (difference_type n) {
            it2_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        indexed_const_iterator2 &operator -= (difference_type n) {
            it2_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const indexed_const_iterator2 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
            return it2_ - it.it2_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
            BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
            return (*this) () (it1_, it2_);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (difference_type n) const {
            return *((*this) + n);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index1 () const {
            return it1_;
        }
        BOOST_UBLAS_INLINE
        size_type index2 () const {
            return it2_;
        }

        BOOST_UBLAS_INLINE
        dual_iterator_type begin () const {
            return (*this) ().find1 (1, 0, index2 ());
        }
        BOOST_UBLAS_INLINE
        dual_iterator_type end () const {
            return (*this) ().find1 (1, (*this) ().size1 (), index2 ());
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rbegin () const {
            return dual_reverse_iterator_type (end ());
        }
        BOOST_UBLAS_INLINE
        dual_reverse_iterator_type rend () const {
            return dual_reverse_iterator_type (begin ());
        }

        // Assignment
        BOOST_UBLAS_INLINE
        indexed_const_iterator2 &operator = (const indexed_const_iterator2 &it) {
            // FIX: ICC needs full qualification?!
            // assign (&it ());
            container_const_reference<C>::assign (&it ());
            it1_ = it.it1_;
            it2_ = it.it2_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const indexed_const_iterator2 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
            return it2_ == it.it2_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const indexed_const_iterator2 &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            BOOST_UBLAS_CHECK (it1_ == it.it1_, external_logic ());
            return it2_ < it.it2_;
        }

    private:
        size_type it1_;
        size_type it2_;

        friend class indexed_iterator2<container_type, iterator_category>;
    };

}}}

#endif

/* iterator.hpp
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
*/