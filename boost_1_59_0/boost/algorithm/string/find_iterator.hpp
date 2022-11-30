//  Boost string_algo library find_iterator.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2004.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_ITERATOR_HPP
#define BOOST_STRING_FIND_ITERATOR_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/detail/find_iterator.hpp>

/*! \file
    Defines find iterator classes. Find iterator repeatedly applies a Finder
    to the specified input string to search for matches. Dereferencing
    the iterator yields the current match or a range between the last and the current
    match depending on the iterator used.
*/

namespace boost {
    namespace algorithm { 

//  find_iterator -----------------------------------------------//

        //! find_iterator
        /*!    
            Find iterator encapsulates a Finder and allows
            for incremental searching in a string.
            Each increment moves the iterator to the next match.

            Find iterator is a readable forward traversal iterator.

            Dereferencing the iterator yields an iterator_range delimiting
            the current match.
        */
        template<typename IteratorT>
        class find_iterator : 
            public iterator_facade<
                find_iterator<IteratorT>,
                const iterator_range<IteratorT>,
                forward_traversal_tag >,
            private detail::find_iterator_base<IteratorT>
        {
        private:
            // facade support
            friend class ::boost::iterator_core_access;

        private:
        // typedefs

            typedef detail::find_iterator_base<IteratorT> base_type;
            typedef BOOST_STRING_TYPENAME 
                base_type::input_iterator_type input_iterator_type;
            typedef BOOST_STRING_TYPENAME 
                base_type::match_type match_type;

        public:
            //! Default constructor
            /*!
                Construct null iterator. All null iterators are equal.

                \post eof()==true
            */
            find_iterator() {}

            //! Copy constructor
            /*!
                Construct a copy of the find_iterator
            */
            find_iterator( const find_iterator& Other ) :
                base_type(Other),
                m_Match(Other.m_Match),
                m_End(Other.m_End) {}

            //! Constructor
            /*!
                Construct new find_iterator for a given finder
                and a range.
            */
            template<typename FinderT>
            find_iterator(
                    IteratorT Begin,
                    IteratorT End,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_Match(Begin,Begin),
                m_End(End)
            {
                increment();
            }

            //! Constructor
            /*!
                Construct new find_iterator for a given finder
                and a range.
            */
            template<typename FinderT, typename RangeT>
            find_iterator(
                    RangeT& Col,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0)
            {
                iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_col(::boost::as_literal(Col));
                m_Match=::boost::make_iterator_range(::boost::begin(lit_col), ::boost::begin(lit_col));
                m_End=::boost::end(lit_col);

                increment();
            }

        private:
        // iterator operations

            // dereference
            const match_type& dereference() const
            {
                return m_Match;
            }

            // increment
            void increment()
            {
                m_Match=this->do_find(m_Match.end(),m_End);
            }

            // comparison
            bool equal( const find_iterator& Other ) const
            {
                bool bEof=eof();
                bool bOtherEof=Other.eof();

                return bEof || bOtherEof ? bEof==bOtherEof :
                    (
                        m_Match==Other.m_Match &&
                        m_End==Other.m_End 
                    );
            }

        public:
        // operations

            //! Eof check
            /*!
                Check the eof condition. Eof condition means that
                there is nothing more to be searched i.e. find_iterator
                is after the last match.
            */
            bool eof() const
            {
                return 
                    this->is_null() || 
                    ( 
                        m_Match.begin() == m_End &&
                        m_Match.end() == m_End
                    );
            }

        private:
        // Attributes
            match_type m_Match;
            input_iterator_type m_End;
        };

        //! find iterator construction helper
        /*!
         *    Construct a find iterator to iterate through the specified string
         */
        template<typename RangeT, typename FinderT>
        inline find_iterator< 
            BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
        make_find_iterator(
            RangeT& Collection,
            FinderT Finder)
        {
            return find_iterator<BOOST_STRING_TYPENAME range_iterator<RangeT>::type>(
                Collection, Finder);
        }

//  split iterator -----------------------------------------------//

        //! split_iterator
        /*!    
            Split iterator encapsulates a Finder and allows
            for incremental searching in a string.
            Unlike the find iterator, split iterator iterates
            through gaps between matches.

            Find iterator is a readable forward traversal iterator.

            Dereferencing the iterator yields an iterator_range delimiting
            the current match.
        */
        template<typename IteratorT>
        class split_iterator : 
            public iterator_facade<
                split_iterator<IteratorT>,
                const iterator_range<IteratorT>,
                forward_traversal_tag >,
            private detail::find_iterator_base<IteratorT>
        {
        private:
            // facade support
            friend class ::boost::iterator_core_access;

        private:
        // typedefs

            typedef detail::find_iterator_base<IteratorT> base_type;
            typedef BOOST_STRING_TYPENAME 
                base_type::input_iterator_type input_iterator_type;
            typedef BOOST_STRING_TYPENAME 
                base_type::match_type match_type;

        public:
            //! Default constructor
            /*!
                Construct null iterator. All null iterators are equal.
    
                \post eof()==true
            */
            split_iterator() :
                m_Next(),
                m_End(),
                m_bEof(true)
            {}

            //! Copy constructor
            /*!
                Construct a copy of the split_iterator
            */
            split_iterator( const split_iterator& Other ) :
                base_type(Other),
                m_Match(Other.m_Match),
                m_Next(Other.m_Next),
                m_End(Other.m_End),
                m_bEof(Other.m_bEof)
            {}

            //! Constructor
            /*!
                Construct new split_iterator for a given finder
                and a range.
            */
            template<typename FinderT>
            split_iterator(
                    IteratorT Begin,
                    IteratorT End,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_Match(Begin,Begin),
                m_Next(Begin),
                m_End(End),
                m_bEof(false)
            {
                // force the correct behavior for empty sequences and yield at least one token
                if(Begin!=End)
                {
                    increment();
                }
            }
            //! Constructor
            /*!
                Construct new split_iterator for a given finder
                and a collection.
            */
            template<typename FinderT, typename RangeT>
            split_iterator(
                    RangeT& Col,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_bEof(false)
            {
                iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_col(::boost::as_literal(Col));
                m_Match=make_iterator_range(::boost::begin(lit_col), ::boost::begin(lit_col));
                m_Next=::boost::begin(lit_col);
                m_End=::boost::end(lit_col);

                // force the correct behavior for empty sequences and yield at least one token
                if(m_Next!=m_End)
                {
                    increment();
                }
            }


        private:
        // iterator operations

            // dereference
            const match_type& dereference() const
            {
                return m_Match;
            }

            // increment
            void increment()
            {
                match_type FindMatch=this->do_find( m_Next, m_End );

                if(FindMatch.begin()==m_End && FindMatch.end()==m_End)
                {
                    if(m_Match.end()==m_End)
                    {
                        // Mark iterator as eof
                        m_bEof=true;
                    }
                }

                m_Match=match_type( m_Next, FindMatch.begin() );
                m_Next=FindMatch.end();
            }

            // comparison
            bool equal( const split_iterator& Other ) const
            {
                bool bEof=eof();
                bool bOtherEof=Other.eof();

                return bEof || bOtherEof ? bEof==bOtherEof :
                    (
                        m_Match==Other.m_Match &&
                        m_Next==Other.m_Next &&
                        m_End==Other.m_End
                    );
            }

        public:
        // operations

            //! Eof check
            /*!
                Check the eof condition. Eof condition means that
                there is nothing more to be searched i.e. find_iterator
                is after the last match.
            */
            bool eof() const
            {
                return this->is_null() || m_bEof;
            }

        private:
        // Attributes
            match_type m_Match;
            input_iterator_type m_Next;
            input_iterator_type m_End;
            bool m_bEof;
        };

        //! split iterator construction helper
        /*!
         *    Construct a split iterator to iterate through the specified collection
         */
        template<typename RangeT, typename FinderT>
        inline split_iterator< 
            BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
        make_split_iterator(
            RangeT& Collection,
            FinderT Finder)
        {
            return split_iterator<BOOST_STRING_TYPENAME range_iterator<RangeT>::type>(
                Collection, Finder);
        }


    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::find_iterator;
    using algorithm::make_find_iterator;
    using algorithm::split_iterator;
    using algorithm::make_split_iterator;

} // namespace boost


#endif  // BOOST_STRING_FIND_ITERATOR_HPP

/* find_iterator.hpp
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
*/