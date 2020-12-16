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
/3843QjgY39+1k35WcX5WZ9ACYz9Uyy9S6j3VAcdhsrvWYWxq6ZW4sgM7KAR6twv0deycJKmr9MdPAjD7+IwX9iwNdQEgLJtHG1YNfZqmpn8EbVyAw3hZNl0UUAPApAeiS6/he1ZwVb7LtbcB0KVCGRe4xfDd5Nn1Pvg1L7Px25c1yuaLRZUztVEBQZ/gowDyICS7X73unRkqquvFgW0xpp21Z8t+mk1+XdWNRXNKuUUl7asY17RQpyU7GUnC2lJUNKLwyfW52zs/gwXnV73DuP1ljhR1lvzdqWUdYQNLt7RnVnp4J5xj7rmm+MDLx+81VnTEXhRB9ufzIhj3KiD8F8i+DfcKviL2lr4fZNZnQC4S57AAANLZpI60VBGG9rSAMMxOJTMYxr64kGX/dlf6xC2W/rz4diCAi83dfuHTCJMcJStW0YqJMvACAcWnjQbODvIg4Cl0cLT+dppviZU4kWZpLEA9V81SY73mQHyNw3ErgXkr1IO450XC0GcixRjP9LUJVP4AUY92UX6FT0k5LzkbS7nUpcN5a5vniAgs9xaz/IO5Idv4B/BCOJpxBfrNb4oqck8ANwtk+YhW0X3u5itovPglnuut/OEI64FPYiIN+sgiO8czGO6i8Z0BvqzcqEs/F288CfJsZioHvWyY+9dKQcD0+DryVqqG2QUblhoTuyvKsfL7qoD/exwBQLXxYJbo7wa7kLAgVXMIkdr9LKFIXuwHR+cA8SAPGYyL1rMqrpgIn3tK0oD1dWwGTyV52Ua1zlpWY/LoE4NZGXZ9iO0Pysehcx2PAovWA36h0PO/zvNBsWo1/tYfVx2go7RrIlw/V1MirL+rMPwD/N1E34wHa98yZgcXzG9thoTDuf7biq5Gd/dxsfqs7bc8qFYNBOXyDto+iS2BCJUOLIJlXpSEDVVbYFIvIg805a9iOwAWhNnw0zjY/qOJGpWwIFGgQLQd68/6580JPm+f2IxFJKqk/qad8ngI2w3mUXpHCoBSNhwQrW9WtZh4S9BgnMRECuan9OCMxY9jgxKVBkD2bEfTv278oic7MrP+MRdUI0IyjvNebns57U4SRfAbKgXRgr2a5CWbvg+waudrx5avx+jkvJz/rU3efJ9+xHmD18M336u5uMB1OWcS+kHDpjvr+HJvNAz6l0Qsrg8onDnagp3L2tp4037ZxpzxuQFGoyGCmB9EwaJyoIHRnScmTDYJXygLhsmzdqMp1Ihna8tIMQtNeLOg0nf6kL8ovs1sjy8ReGoXjUZrPdVlvHPkjjtDm8jjrWSGKLDRsY02jNj8CVoxOXtneOii4h6sz0PULWSLupEsiaLA9j5OxIzUpB3rQxeClqEqaLpoz1NgK15s2dUSzloB6wBQK1Z3Qu1ZyIgtvf42TPC/P/ff+wv7SrWIdjA/s+Gm7YMTV60bBmWMLGHtQEZujITSGzahYXzTJ/MvG5rfzm/VhQfQD1d6me+xgUmVUFO53GJNuAlAvzafDMA5HG1TYB7VZFAT89QQ1b1FfsH2ooAXwRwKn0/SgNV6KLkl7L03sxXknw20WVziQL+fIVV3cmc9DHCe2N/OtDS8yfWMj7IDcS7FvwcrZmguiY3tD2Kv+SMBUuUU59q3R1NfCbR7ACpsOiTPk7Vc9GPUpN/YGPY2P5sDOvKuwyF0jtPjHMtaIdvRIJnwoERwWYaPxG4N39cYqAu8ijNC+MD4W8mxVFQirxt1Fp3V75HWob2z0SbrpfXNRNeZuI8jGP/ESovA3zeTo0M2KGEOzmOWxtq3WTB7CQK+s8ujNni3l9BYslTJiwX/tTBXUXTZghj07yOvbtJ3N2G2eJK5Xzqas451M1lY+zdTKJu8qk=
*/