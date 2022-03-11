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