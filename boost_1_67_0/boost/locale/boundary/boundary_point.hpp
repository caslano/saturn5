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