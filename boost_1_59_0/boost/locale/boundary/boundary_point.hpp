//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_BOUNDARY_BOUNDARY_POINT_HPP_INCLUDED
#define BOOST_LOCALE_BOUNDARY_BOUNDARY_POINT_HPP_INCLUDED

#include <boost/locale/boundary/types.hpp>

namespace boost {
namespace locale {
namespace boundary {

    ///
    /// \addtogroup boundary
    /// @{

    ///
    /// \brief This class represents a boundary point in the text. 
    ///
    /// It represents a pair - an iterator and a rule that defines this 
    /// point.
    ///
    /// This type of object is dereference by the iterators of boundary_point_index. Using a rule()
    /// member function you can get the reason why this specific boundary point was selected. 
    ///
    /// For example, When you use a sentence boundary analysis, the (rule() & \ref sentence_term) != 0 means
    /// that this boundary point was selected because a sentence terminator (like .?!) was spotted
    /// and the (rule() & \ref sentence_sep)!=0 means that a separator like line feed or carriage
    /// return was observed.
    ///
    /// \note
    ///
    /// -   The beginning of analyzed range is always considered a boundary point and its rule is always 0.
    /// -   when using a word boundary analysis the returned rule relates to a chunk of text preceding
    ///     this point.
    ///
    /// \see
    ///
    /// -   \ref boundary_point_index
    /// -   \ref segment
    /// -   \ref segment_index
    ///
    template<typename IteratorType>
    class boundary_point  {
    public:
        ///
        /// The type of the base iterator that iterates the original text
        ///
        typedef IteratorType iterator_type;

        ///
        /// Empty default constructor
        ///
        boundary_point() : rule_(0) {}
        
        ///
        /// Create a new boundary_point using iterator \p and a rule \a r
        ///
        boundary_point(iterator_type p,rule_type r) :
            iterator_(p),
            rule_(r)
        {
        }
        ///
        /// Set an new iterator value \a i
        ///
        void iterator(iterator_type i)
        {
            iterator_ = i;
        }
        ///
        /// Set an new rule value \a r
        ///
        void rule(rule_type r)
        {
            rule_ = r;
        }
        ///
        /// Fetch an iterator
        ///
        iterator_type iterator() const 
        {
            return iterator_;
        }
        ///
        /// Fetch a rule
        ///
        rule_type rule() const
        {
            return rule_;
        }
        ///
        /// Check if two boundary points are the same
        ///
        bool operator==(boundary_point const &other) const
        {
            return iterator_ == other.iterator_ && rule_ = other.rule_;
        }
        ///
        /// Check if two boundary points are different
        ///
        bool operator!=(boundary_point const &other) const
        {
            return !(*this==other);
        }
        ///
        /// Check if the boundary point points to same location as an iterator \a other
        ///
        bool operator==(iterator_type const &other) const
        {
            return iterator_ == other;
        }
        ///
        /// Check if the boundary point points to different location from an iterator \a other
        ///
        bool operator!=(iterator_type const &other) const
        {
            return iterator_ != other;
        }

        ///
        /// Automatic cast to the iterator it represents
        ///
        operator iterator_type ()const
        {
            return iterator_;
        }

    private:
        iterator_type iterator_;
        rule_type rule_;
       
    };
    ///
    /// Check if the boundary point \a r points to same location as an iterator \a l
    ///
    template<typename BaseIterator>
    bool operator==(BaseIterator const &l,boundary_point<BaseIterator> const &r)
    {
        return r==l;
    }
    ///
    /// Check if the boundary point \a r points to different location from an iterator \a l
    ///
    template<typename BaseIterator>
    bool operator!=(BaseIterator const &l,boundary_point<BaseIterator> const &r)
    {
        return r!=l;
    }

    /// @}
    
    typedef boundary_point<std::string::const_iterator> sboundary_point;      ///< convenience typedef
    typedef boundary_point<std::wstring::const_iterator> wsboundary_point;    ///< convenience typedef
    #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
    typedef boundary_point<std::u16string::const_iterator> u16sboundary_point;///< convenience typedef
    #endif
    #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
    typedef boundary_point<std::u32string::const_iterator> u32sboundary_point;///< convenience typedef
    #endif
   
    typedef boundary_point<char const *> cboundary_point;                     ///< convenience typedef
    typedef boundary_point<wchar_t const *> wcboundary_point;                 ///< convenience typedef
    #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
    typedef boundary_point<char16_t const *> u16cboundary_point;              ///< convenience typedef
    #endif
    #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
    typedef boundary_point<char32_t const *> u32cboundary_point;              ///< convenience typedef
    #endif
    

} // boundary
} // locale
} // boost


#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* boundary_point.hpp
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
*/