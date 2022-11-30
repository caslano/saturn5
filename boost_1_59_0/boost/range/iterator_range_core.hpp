// Boost.Range library
//
//  Copyright Neil Groves & Thorsten Ottosen & Pavol Droba 2003-2004.
//  Use, modification and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
// Credits:
// 'michel' reported Trac 9072 which included a patch for allowing references
// to function types.
//
#ifndef BOOST_RANGE_ITERATOR_RANGE_CORE_HPP_INCLUDED
#define BOOST_RANGE_ITERATOR_RANGE_CORE_HPP_INCLUDED

#include <boost/config.hpp> // Define __STL_CONFIG_H, if appropriate.
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
    #pragma warning( push )
    #pragma warning( disable : 4996 )
#endif

#include <boost/assert.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/range/functions.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/has_range_iterator.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/detail/safe_bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/next_prior.hpp>
#include <iterator>
#include <algorithm>
#include <cstddef>

/*! \file
    Defines the \c iterator_class and related functions.
    \c iterator_range is a simple wrapper of iterator pair idiom. It provides
    a rich subset of Container interface.
*/


namespace boost
{
    namespace iterator_range_detail
    {
        //
        // The functions adl_begin and adl_end are implemented in a separate
        // class for gcc-2.9x
        //
        template<class IteratorT>
        struct iterator_range_impl {
            template< class ForwardRange >
            static IteratorT adl_begin( ForwardRange& r )
            {
                return IteratorT( boost::begin( r ) );
            }

            template< class ForwardRange >
            static IteratorT adl_end( ForwardRange& r )
            {
                return IteratorT( boost::end( r ) );
            }
        };

        template< class Left, class Right >
        inline bool less_than( const Left& l, const Right& r )
        {
            return std::lexicographical_compare( boost::begin(l),
                                                 boost::end(l),
                                                 boost::begin(r),
                                                 boost::end(r) );
        }
        
        template< class Left, class Right >
        inline bool greater_than( const Left& l, const Right& r )
        {
            return iterator_range_detail::less_than(r,l);
        }
        
        template< class Left, class Right >
        inline bool less_or_equal_than( const Left& l, const Right& r )
        {
            return !iterator_range_detail::less_than(r,l);
        }
        
        template< class Left, class Right >
        inline bool greater_or_equal_than( const Left& l, const Right& r )
        {
            return !iterator_range_detail::less_than(l,r);
        }

        // This version is maintained since it is used in other boost libraries
        // such as Boost.Assign
        template< class Left, class Right >
        inline bool equal(const Left& l, const Right& r)
        {
            return boost::equal(l, r);
        }

struct range_tag
{
};

struct const_range_tag
{
};

struct iterator_range_tag
{
};

typedef char (&incrementable_t)[1];
typedef char (&bidirectional_t)[2];
typedef char (&random_access_t)[3];

incrementable_t test_traversal_tag(boost::incrementable_traversal_tag);
bidirectional_t test_traversal_tag(boost::bidirectional_traversal_tag);
random_access_t test_traversal_tag(boost::random_access_traversal_tag);

template<std::size_t S>
struct pure_iterator_traversal_impl
{
    typedef boost::incrementable_traversal_tag type;
};

template<>
struct pure_iterator_traversal_impl<sizeof(bidirectional_t)>
{
    typedef boost::bidirectional_traversal_tag type;
};

template<>
struct pure_iterator_traversal_impl<sizeof(random_access_t)>
{
    typedef boost::random_access_traversal_tag type;
};

template<typename IteratorT>
struct pure_iterator_traversal
{
    typedef
        BOOST_DEDUCED_TYPENAME iterator_traversal<IteratorT>::type
    traversal_t;
    BOOST_STATIC_CONSTANT(
        std::size_t,
        traversal_i = sizeof(iterator_range_detail::test_traversal_tag((traversal_t())))
    );
    typedef
        BOOST_DEDUCED_TYPENAME pure_iterator_traversal_impl<traversal_i>::type
    type;
};

template<class IteratorT, class TraversalTag>
class iterator_range_base
    : public iterator_range_tag
{
    typedef range_detail::safe_bool<
                IteratorT iterator_range_base<IteratorT, TraversalTag>::*
    > safe_bool_t;

    typedef iterator_range_base<IteratorT, TraversalTag> type;

protected:
    typedef iterator_range_impl<IteratorT> impl;

public:
    typedef BOOST_DEDUCED_TYPENAME
        safe_bool_t::unspecified_bool_type unspecified_bool_type;

    typedef BOOST_DEDUCED_TYPENAME
        iterator_value<IteratorT>::type value_type;

    typedef BOOST_DEDUCED_TYPENAME
        iterator_difference<IteratorT>::type difference_type;

    typedef std::size_t size_type; // note: must be unsigned

    // Needed because value-type is the same for
    // const and non-const iterators
    typedef BOOST_DEDUCED_TYPENAME
                iterator_reference<IteratorT>::type reference;

    //! const_iterator type
    /*!
        There is no distinction between const_iterator and iterator.
        These typedefs are provides to fulfill container interface
    */
    typedef IteratorT const_iterator;
    //! iterator type
    typedef IteratorT iterator;

protected:
    iterator_range_base()
        : m_Begin()
        , m_End()
    {
    }

    template<class Iterator>
    iterator_range_base(Iterator Begin, Iterator End)
        : m_Begin(Begin)
        , m_End(End)
    {
    }

public:
    IteratorT begin() const
    {
        return m_Begin;
    }

    IteratorT end() const
    {
        return m_End;
    }

    bool empty() const
    {
        return m_Begin == m_End;
    }

    operator unspecified_bool_type() const
    {
        return safe_bool_t::to_unspecified_bool(
                    m_Begin != m_End, &iterator_range_base::m_Begin);
    }

    bool operator!() const
    {
        return empty();
    }

    bool equal(const iterator_range_base& r) const
    {
        return m_Begin == r.m_Begin && m_End == r.m_End;
    }

   reference front() const
   {
       BOOST_ASSERT(!empty());
       return *m_Begin;
   }

   void drop_front()
   {
       BOOST_ASSERT(!empty());
       ++m_Begin;
   }

   void drop_front(difference_type n)
   {
       BOOST_ASSERT(n >= difference_type());
       std::advance(this->m_Begin, n);
   }
   
   // Deprecated
   void pop_front() { drop_front(); }

protected:
    template<class Iterator>
    void assign(Iterator first, Iterator last)
    {
        m_Begin = first;
        m_End = last;
    }

    template<class SinglePassRange>
    void assign(const SinglePassRange& r)
    {
        m_Begin = impl::adl_begin(r);
        m_End = impl::adl_end(r);
    }

    template<class SinglePassRange>
    void assign(SinglePassRange& r)
    {
        m_Begin = impl::adl_begin(r);
        m_End = impl::adl_end(r);
    }

    IteratorT m_Begin;
    IteratorT m_End;
};

template<class IteratorT>
class iterator_range_base<IteratorT, bidirectional_traversal_tag>
        : public iterator_range_base<IteratorT, incrementable_traversal_tag>
{
    typedef iterator_range_base<IteratorT, incrementable_traversal_tag> base_type;

protected:
    iterator_range_base()
    {
    }

    template<class Iterator>
    iterator_range_base(Iterator first, Iterator last)
        : base_type(first, last)
    {
    }

public:
    typedef BOOST_DEDUCED_TYPENAME base_type::difference_type difference_type;
    typedef BOOST_DEDUCED_TYPENAME base_type::reference reference;

    reference back() const
    {
        BOOST_ASSERT(!this->empty());
        return *boost::prior(this->m_End);
    }

    void drop_back()
    {
        BOOST_ASSERT(!this->empty());
        --this->m_End;
    }

    void drop_back(difference_type n)
    {
        BOOST_ASSERT(n >= difference_type());
        std::advance(this->m_End, -n);
    }
    
    // Deprecated
    void pop_back() { drop_back(); }
};

template<class IteratorT>
class iterator_range_base<IteratorT, random_access_traversal_tag>
        : public iterator_range_base<IteratorT, bidirectional_traversal_tag>
{
    typedef iterator_range_base<
                IteratorT, bidirectional_traversal_tag> base_type;

public:
    typedef BOOST_DEDUCED_TYPENAME
        boost::mpl::if_<
            boost::mpl::or_<
                boost::is_abstract<
                    BOOST_DEDUCED_TYPENAME base_type::value_type
                >,
                boost::is_array<
                    BOOST_DEDUCED_TYPENAME base_type::value_type
                >,
                boost::is_function<
                    BOOST_DEDUCED_TYPENAME base_type::value_type
                >
            >,
            BOOST_DEDUCED_TYPENAME base_type::reference,
            BOOST_DEDUCED_TYPENAME base_type::value_type
        >::type abstract_value_type;

    // Rationale:
    // typedef these here to reduce verbiage in the implementation of this
    // type.
    typedef BOOST_DEDUCED_TYPENAME base_type::difference_type difference_type;
    typedef BOOST_DEDUCED_TYPENAME base_type::size_type size_type;
    typedef BOOST_DEDUCED_TYPENAME base_type::reference reference;

protected:
    iterator_range_base()
    {
    }

    template<class Iterator>
    iterator_range_base(Iterator first, Iterator last)
        : base_type(first, last)
    {
    }

public:
    reference operator[](difference_type at) const
    {
        BOOST_ASSERT(at >= 0);
        BOOST_ASSERT(static_cast<typename base_type::size_type>(at) < size());
        return this->m_Begin[at];
    }

    //
    // When storing transform iterators, operator[]()
    // fails because it returns by reference. Therefore
    // operator()() is provided for these cases.
    //
    abstract_value_type operator()(difference_type at) const
    {
        BOOST_ASSERT(at >= 0);
        BOOST_ASSERT(static_cast<typename base_type::size_type>(at) < size());
        return this->m_Begin[at];
    }

    BOOST_DEDUCED_TYPENAME base_type::size_type size() const
    {
        return this->m_End - this->m_Begin;
    }
};

    }

//  iterator range template class -----------------------------------------//

        //! iterator_range class
        /*!
            An \c iterator_range delimits a range in a sequence by beginning and ending iterators.
            An iterator_range can be passed to an algorithm which requires a sequence as an input.
            For example, the \c toupper() function may be used most frequently on strings,
            but can also be used on iterator_ranges:

            \code
                boost::tolower( find( s, "UPPERCASE STRING" ) );
            \endcode

            Many algorithms working with sequences take a pair of iterators,
            delimiting a working range, as an arguments. The \c iterator_range class is an
            encapsulation of a range identified by a pair of iterators.
            It provides a collection interface,
            so it is possible to pass an instance to an algorithm requiring a collection as an input.
        */
        template<class IteratorT>
        class iterator_range
            : public iterator_range_detail::iterator_range_base<
                    IteratorT,
                    BOOST_DEDUCED_TYPENAME iterator_range_detail::pure_iterator_traversal<IteratorT>::type
                >
        {
            typedef iterator_range_detail::iterator_range_base<
                    IteratorT,
                    BOOST_DEDUCED_TYPENAME iterator_range_detail::pure_iterator_traversal<IteratorT>::type
            > base_type;

            template<class Source>
            struct is_compatible_range_
              : is_convertible<
                    BOOST_DEDUCED_TYPENAME mpl::eval_if<
                        has_range_iterator<Source>,
                        range_iterator<Source>,
                        mpl::identity<void>
                    >::type,
                    BOOST_DEDUCED_TYPENAME base_type::iterator
                >
            {
            };

            template<class Source>
            struct is_compatible_range
                : mpl::and_<
                    mpl::not_<
                        is_convertible<
                            Source,
                            BOOST_DEDUCED_TYPENAME base_type::iterator
                        >
                    >,
                    is_compatible_range_<Source>
                >
            {
            };

        protected:
            typedef iterator_range_detail::iterator_range_impl<IteratorT> impl;

        public:
            typedef iterator_range<IteratorT> type;

            iterator_range()
            {
            }

            template<class Iterator>
            iterator_range(Iterator first, Iterator last)
                : base_type(first, last)
            {
            }

            template<class SinglePassRange>
            iterator_range(
                const SinglePassRange& r,
                BOOST_DEDUCED_TYPENAME ::boost::enable_if<
                    is_compatible_range<const SinglePassRange>
                >::type* = 0
            )
                : base_type(impl::adl_begin(r), impl::adl_end(r))
            {
            }

            template<class SinglePassRange>
            iterator_range(
                SinglePassRange& r,
                BOOST_DEDUCED_TYPENAME ::boost::enable_if<
                    is_compatible_range<SinglePassRange>
                >::type* = 0
            )
                : base_type(impl::adl_begin(r), impl::adl_end(r))
            {
            }

            template<class SinglePassRange>
            iterator_range(const SinglePassRange& r,
                           iterator_range_detail::const_range_tag)
                : base_type(impl::adl_begin(r), impl::adl_end(r))
            {
            }

            template<class SinglePassRange>
            iterator_range(SinglePassRange& r,
                           iterator_range_detail::range_tag)
                : base_type(impl::adl_begin(r), impl::adl_end(r))
            {
            }

            template<class Iterator>
            iterator_range& operator=(const iterator_range<Iterator>& other)
            {
                this->assign(other.begin(), other.end());
                return *this;
            }

            template<class Iterator>
            iterator_range& operator=(iterator_range<Iterator>& other)
            {
                this->assign(other.begin(), other.end());
                return *this;
            }

            template<class SinglePassRange>
            iterator_range& operator=(SinglePassRange& r)
            {
                this->assign(r);
                return *this;
            }

            template<class SinglePassRange>
            iterator_range& operator=(const SinglePassRange& r)
            {
                this->assign(r);
                return *this;
            }

            iterator_range& advance_begin(
                BOOST_DEDUCED_TYPENAME base_type::difference_type n)
            {
                std::advance(this->m_Begin, n);
                return *this;
            }

            iterator_range& advance_end(
                BOOST_DEDUCED_TYPENAME base_type::difference_type n)
            {
                std::advance(this->m_End, n);
                return *this;
            }

        protected:
            //
            // Allow subclasses an easy way to access the
            // base type
            //
            typedef iterator_range iterator_range_;
        };

//  iterator range free-standing operators ---------------------------//

        /////////////////////////////////////////////////////////////////////
        // comparison operators
        /////////////////////////////////////////////////////////////////////

        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator==( const ForwardRange& l, const iterator_range<IteratorT>& r )
        {
            return boost::equal( l, r );
        }

        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator!=( const ForwardRange& l, const iterator_range<IteratorT>& r )
        {
            return !boost::equal( l, r );
        }

        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator<( const ForwardRange& l, const iterator_range<IteratorT>& r )
        {
            return iterator_range_detail::less_than( l, r );
        }
        
        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator<=( const ForwardRange& l, const iterator_range<IteratorT>& r )
        {
            return iterator_range_detail::less_or_equal_than( l, r );
        }
        
        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator>( const ForwardRange& l, const iterator_range<IteratorT>& r )
        {
            return iterator_range_detail::greater_than( l, r );
        }
        
        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator>=( const ForwardRange& l, const iterator_range<IteratorT>& r )
        {
            return iterator_range_detail::greater_or_equal_than( l, r );
        }

        template< class Iterator1T, class Iterator2T >
        inline bool
        operator==( const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
        {
            return boost::equal( l, r );
        }

        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator==( const iterator_range<IteratorT>& l, const ForwardRange& r )
        {
            return boost::equal( l, r );
        }


        template< class Iterator1T, class Iterator2T >
        inline bool
        operator!=( const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
        {
            return !boost::equal( l, r );
        }

        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator!=( const iterator_range<IteratorT>& l, const ForwardRange& r )
        {
            return !boost::equal( l, r );
        }


        template< class Iterator1T, class Iterator2T >
        inline bool
        operator<( const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
        {
            return iterator_range_detail::less_than( l, r );
        }

        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator<( const iterator_range<IteratorT>& l, const ForwardRange& r )
        {
            return iterator_range_detail::less_than( l, r );
        }
        
        template< class Iterator1T, class Iterator2T >
        inline bool
        operator<=( const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
        {
            return iterator_range_detail::less_or_equal_than( l, r );
        }
        
        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator<=( const iterator_range<IteratorT>& l, const ForwardRange& r )
        {
            return iterator_range_detail::less_or_equal_than( l, r );
        }
        
        template< class Iterator1T, class Iterator2T >
        inline bool
        operator>( const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
        {
            return iterator_range_detail::greater_than( l, r );
        }
        
        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator>( const iterator_range<IteratorT>& l, const ForwardRange& r )
        {
            return iterator_range_detail::greater_than( l, r );
        }
        
        template< class Iterator1T, class Iterator2T >
        inline bool
        operator>=( const iterator_range<Iterator1T>& l, const iterator_range<Iterator2T>& r )
        {
            return iterator_range_detail::greater_or_equal_than( l, r );
        }
        
        template< class IteratorT, class ForwardRange >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            mpl::not_<boost::is_base_and_derived<iterator_range_detail::iterator_range_tag, ForwardRange> >,
            bool
        >::type
        operator>=( const iterator_range<IteratorT>& l, const ForwardRange& r )
        {
            return iterator_range_detail::greater_or_equal_than( l, r );
        }

//  iterator range utilities -----------------------------------------//

        //! iterator_range construct helper
        /*!
            Construct an \c iterator_range from a pair of iterators

            \param Begin A begin iterator
            \param End An end iterator
            \return iterator_range object
        */
        template< typename IteratorT >
        inline iterator_range< IteratorT >
        make_iterator_range( IteratorT Begin, IteratorT End )
        {
            return iterator_range<IteratorT>( Begin, End );
        }

        template<typename IteratorT, typename IntegerT>
        inline iterator_range<IteratorT>
        make_iterator_range_n(IteratorT first, IntegerT n)
        {
            return iterator_range<IteratorT>(first, boost::next(first, n));
        }

        //! iterator_range construct helper
        /*!
            Construct an \c iterator_range from a \c Range containing the begin
            and end iterators.
        */
        template< class ForwardRange >
        inline iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type >
        make_iterator_range( ForwardRange& r )
        {
           return iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type >
                ( r, iterator_range_detail::range_tag() );
        }

        template< class ForwardRange >
        inline iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type >
        make_iterator_range( const ForwardRange& r )
        {
           return iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type >
                ( r, iterator_range_detail::const_range_tag() );
        }

        namespace iterator_range_detail
        {
            template< class Range >
            inline iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<Range>::type >
            make_range_impl( Range& r,
                             BOOST_DEDUCED_TYPENAME range_difference<Range>::type advance_begin,
                             BOOST_DEDUCED_TYPENAME range_difference<Range>::type advance_end )
            {
                //
                // Not worth the effort
                //
                //if( advance_begin == 0 && advance_end == 0 )
                //    return make_iterator_range( r );
                //

                BOOST_DEDUCED_TYPENAME range_iterator<Range>::type
                    new_begin = boost::begin( r ),
                    new_end   = boost::end( r );
                std::advance( new_begin, advance_begin );
                std::advance( new_end, advance_end );
                return make_iterator_range( new_begin, new_end );
            }
        }

        template< class Range >
        inline iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<Range>::type >
        make_iterator_range( Range& r,
                    BOOST_DEDUCED_TYPENAME range_difference<Range>::type advance_begin,
                    BOOST_DEDUCED_TYPENAME range_difference<Range>::type advance_end )
        {
            return iterator_range_detail::make_range_impl( r, advance_begin, advance_end );
        }

        template< class Range >
        inline iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<const Range>::type >
        make_iterator_range( const Range& r,
                    BOOST_DEDUCED_TYPENAME range_difference<Range>::type advance_begin,
                    BOOST_DEDUCED_TYPENAME range_difference<Range>::type advance_end )
        {
            return iterator_range_detail::make_range_impl( r, advance_begin, advance_end );
        }

        //! copy a range into a sequence
        /*!
            Construct a new sequence of the specified type from the elements
            in the given range

            \param Range An input range
            \return New sequence
        */
        template< typename SeqT, typename Range >
        inline SeqT copy_range( const Range& r )
        {
            return SeqT( boost::begin( r ), boost::end( r ) );
        }

} // namespace 'boost'

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
    #pragma warning( pop )
#endif

#endif


/* iterator_range_core.hpp
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
*/