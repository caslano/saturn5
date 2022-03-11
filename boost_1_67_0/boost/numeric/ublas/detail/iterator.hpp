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