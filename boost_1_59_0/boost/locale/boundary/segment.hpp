//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_BOUNDARY_SEGMENT_HPP_INCLUDED
#define BOOST_LOCALE_BOUNDARY_SEGMENT_HPP_INCLUDED
#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <locale>
#include <string>
#include <iosfwd>
#include <iterator>


namespace boost {
namespace locale {
namespace boundary {
    /// \cond INTERNAL
    namespace details {
        template<typename LeftIterator,typename RightIterator>
        int compare_text(LeftIterator l_begin,LeftIterator l_end,RightIterator r_begin,RightIterator r_end)
        {
            typedef LeftIterator left_iterator;
            typedef typename std::iterator_traits<left_iterator>::value_type char_type;
            typedef std::char_traits<char_type> traits;
            while(l_begin!=l_end && r_begin!=r_end) {
                char_type lchar = *l_begin++;
                char_type rchar = *r_begin++;
                if(traits::eq(lchar,rchar))
                    continue;
                if(traits::lt(lchar,rchar))
                    return -1;
                else
                    return 1;
            }
            if(l_begin==l_end && r_begin==r_end)
                return 0;
            if(l_begin==l_end)
                return -1;
            else
                return 1;
        }


        template<typename Left,typename Right>
        int compare_text(Left const &l,Right const &r)
        {
            return compare_text(l.begin(),l.end(),r.begin(),r.end());
        }
        
        template<typename Left,typename Char>
        int compare_string(Left const &l,Char const *begin)
        {
            Char const *end = begin;
            while(*end!=0)
                end++;
            return compare_text(l.begin(),l.end(),begin,end);
        }

        template<typename Right,typename Char>
        int compare_string(Char const *begin,Right const &r)
        {
            Char const *end = begin;
            while(*end!=0)
                end++;
            return compare_text(begin,end,r.begin(),r.end());
        }

    }
    /// \endcond

    ///
    /// \addtogroup boundary
    /// @{

    ///
    /// \brief a segment object that represents a pair of two iterators that define the range where
    /// this segment exits and a rule that defines it.
    ///
    /// This type of object is dereferenced by the iterators of segment_index. Using a rule() member function
    /// you can get a specific rule this segment was selected with. For example, when you use
    /// word boundary analysis, you can check if the specific word contains Kana letters by checking (rule() & \ref word_kana)!=0
    /// For a sentence analysis you can check if the sentence is selected because a sentence terminator is found (\ref sentence_term) or
    /// there is a line break (\ref sentence_sep).
    ///
    /// This object can be automatically converted to std::basic_string with the same type of character. It is also
    /// valid range that has begin() and end() member functions returning iterators on the location of the segment.
    ///
    /// \see
    ///
    /// - \ref segment_index
    /// - \ref boundary_point 
    /// - \ref boundary_point_index 
    ///
    template<typename IteratorType>
    class segment : public std::pair<IteratorType,IteratorType> {
    public:
        ///
        /// The type of the underlying character 
        ///
        typedef typename std::iterator_traits<IteratorType>::value_type char_type;
        ///
        /// The type of the string it is converted to
        ///
        typedef std::basic_string<char_type> string_type;
        ///
        /// The value that iterators return  - the character itself
        ///
        typedef char_type value_type;
        ///
        /// The iterator that allows to iterate the range
        ///
        typedef IteratorType iterator;
        ///
        /// The iterator that allows to iterate the range
        ///
        typedef IteratorType const_iterator;
        ///
        /// The type that represent a difference between two iterators
        ///
        typedef typename std::iterator_traits<IteratorType>::difference_type difference_type;

        ///
        /// Default constructor
        ///
        segment() {}
        ///
        /// Create a segment using two iterators and a rule that represents this point
        ///
        segment(iterator b,iterator e,rule_type r) :
            std::pair<IteratorType,IteratorType>(b,e),
            rule_(r)
        {
        }
        ///
        /// Set the start of the range
        ///
        void begin(iterator const &v)
        {
            this->first = v;
        }
        ///
        /// Set the end of the range
        ///
         void end(iterator const &v)
        {
            this->second = v;
        }

        ///
        /// Get the start of the range
        ///
        IteratorType begin() const 
        {
            return this->first;
        }
        ///
        /// Set the end of the range
        ///
        IteratorType end() const
        {
            return this->second;
        }

        ///
        /// Convert the range to a string automatically
        ///
        template <class T, class A>
        operator std::basic_string<char_type, T, A> ()const
        {
            return std::basic_string<char_type, T, A>(this->first, this->second);
        }
        
        ///
        /// Create a string from the range explicitly
        ///
        string_type str() const
        {
            return string_type(begin(),end());
        }

        ///
        /// Get the length of the text chunk
        ///

        size_t length() const
        {
            return std::distance(begin(),end());
        }

        ///
        /// Check if the segment is empty
        ///
        bool empty() const
        {
            return begin() == end();
        }

        ///
        /// Get the rule that is used for selection of this segment.
        ///
        rule_type rule() const
        {
            return rule_;
        }
        ///
        /// Set a rule that is used for segment selection
        ///
        void rule(rule_type r)
        {
            rule_ = r;
        }

        // make sure we override std::pair's operator==

        /// Compare two segments
        bool operator==(segment const &other)
        {
            return details::compare_text(*this,other) == 0;
        }

        /// Compare two segments
        bool operator!=(segment const &other)
        {
            return details::compare_text(*this,other) != 0;
        }

    private:
        rule_type rule_;
       
    };

   
    /// Compare two segments
    template<typename IteratorL,typename IteratorR>
    bool operator==(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) == 0; 
    }
    /// Compare two segments
    template<typename IteratorL,typename IteratorR>
    bool operator!=(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) != 0; 
    }

    /// Compare two segments
    template<typename IteratorL,typename IteratorR>
    bool operator<(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) < 0; 
    }
    /// Compare two segments
    template<typename IteratorL,typename IteratorR>
    bool operator<=(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) <= 0; 
    }
    /// Compare two segments
    template<typename IteratorL,typename IteratorR>
    bool operator>(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) > 0; 
    }
    /// Compare two segments
    template<typename IteratorL,typename IteratorR>
    bool operator>=(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) >= 0; 
    }

    /// Compare string and segment
    template<typename CharType,typename Traits,typename Alloc,typename IteratorR>
    bool operator==(std::basic_string<CharType,Traits,Alloc> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) == 0; 
    }
    /// Compare string and segment
    template<typename CharType,typename Traits,typename Alloc,typename IteratorR>
    bool operator!=(std::basic_string<CharType,Traits,Alloc> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) != 0; 
    }

    /// Compare string and segment
    template<typename CharType,typename Traits,typename Alloc,typename IteratorR>
    bool operator<(std::basic_string<CharType,Traits,Alloc> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) < 0; 
    }
    /// Compare string and segment
    template<typename CharType,typename Traits,typename Alloc,typename IteratorR>
    bool operator<=(std::basic_string<CharType,Traits,Alloc> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) <= 0; 
    }
    /// Compare string and segment
    template<typename CharType,typename Traits,typename Alloc,typename IteratorR>
    bool operator>(std::basic_string<CharType,Traits,Alloc> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) > 0; 
    }
    /// Compare string and segment
    template<typename CharType,typename Traits,typename Alloc,typename IteratorR>
    bool operator>=(std::basic_string<CharType,Traits,Alloc> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) >= 0; 
    }

    /// Compare string and segment
    template<typename Iterator,typename CharType,typename Traits,typename Alloc>
    bool operator==(segment<Iterator> const &l,std::basic_string<CharType,Traits,Alloc> const &r)
    {
        return details::compare_text(l,r) == 0; 
    }
    /// Compare string and segment
    template<typename Iterator,typename CharType,typename Traits,typename Alloc>
    bool operator!=(segment<Iterator> const &l,std::basic_string<CharType,Traits,Alloc> const &r)
    {
        return details::compare_text(l,r) != 0; 
    }

    /// Compare string and segment
    template<typename Iterator,typename CharType,typename Traits,typename Alloc>
    bool operator<(segment<Iterator> const &l,std::basic_string<CharType,Traits,Alloc> const &r)
    {
        return details::compare_text(l,r) < 0; 
    }
    /// Compare string and segment
    template<typename Iterator,typename CharType,typename Traits,typename Alloc>
    bool operator<=(segment<Iterator> const &l,std::basic_string<CharType,Traits,Alloc> const &r)
    {
        return details::compare_text(l,r) <= 0; 
    }
    /// Compare string and segment
    template<typename Iterator,typename CharType,typename Traits,typename Alloc>
    bool operator>(segment<Iterator> const &l,std::basic_string<CharType,Traits,Alloc> const &r)
    {
        return details::compare_text(l,r) > 0; 
    }
    /// Compare string and segment
    template<typename Iterator,typename CharType,typename Traits,typename Alloc>
    bool operator>=(segment<Iterator> const &l,std::basic_string<CharType,Traits,Alloc> const &r)
    {
        return details::compare_text(l,r) >= 0; 
    }


    /// Compare C string and segment
    template<typename CharType,typename IteratorR>
    bool operator==(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) == 0; 
    }
    /// Compare C string and segment
    template<typename CharType,typename IteratorR>
    bool operator!=(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) != 0; 
    }

    /// Compare C string and segment
    template<typename CharType,typename IteratorR>
    bool operator<(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) < 0; 
    }
    /// Compare C string and segment
    template<typename CharType,typename IteratorR>
    bool operator<=(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) <= 0; 
    }
    /// Compare C string and segment
    template<typename CharType,typename IteratorR>
    bool operator>(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) > 0; 
    }
    /// Compare C string and segment
    template<typename CharType,typename IteratorR>
    bool operator>=(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) >= 0; 
    }

    /// Compare C string and segment
    template<typename Iterator,typename CharType>
    bool operator==(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) == 0; 
    }
    /// Compare C string and segment
    template<typename Iterator,typename CharType>
    bool operator!=(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) != 0; 
    }

    /// Compare C string and segment
    template<typename Iterator,typename CharType>
    bool operator<(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) < 0; 
    }
    /// Compare C string and segment
    template<typename Iterator,typename CharType>
    bool operator<=(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) <= 0; 
    }
    /// Compare C string and segment
    template<typename Iterator,typename CharType>
    bool operator>(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) > 0; 
    }
    /// Compare C string and segment
    template<typename Iterator,typename CharType>
    bool operator>=(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) >= 0; 
    }






    typedef segment<std::string::const_iterator> ssegment;      ///< convenience typedef
    typedef segment<std::wstring::const_iterator> wssegment;    ///< convenience typedef
    #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
    typedef segment<std::u16string::const_iterator> u16ssegment;///< convenience typedef
    #endif
    #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
    typedef segment<std::u32string::const_iterator> u32ssegment;///< convenience typedef
    #endif
   
    typedef segment<char const *> csegment;                     ///< convenience typedef
    typedef segment<wchar_t const *> wcsegment;                 ///< convenience typedef
    #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
    typedef segment<char16_t const *> u16csegment;              ///< convenience typedef
    #endif
    #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
    typedef segment<char32_t const *> u32csegment;              ///< convenience typedef
    #endif



 
    
    ///
    /// Write the segment to the stream character by character
    ///
    template<typename CharType,typename TraitsType,typename Iterator>
    std::basic_ostream<CharType,TraitsType> &operator<<(
            std::basic_ostream<CharType,TraitsType> &out,
            segment<Iterator> const &tok)
    {
        for(Iterator p=tok.begin(),e=tok.end();p!=e;++p)
            out << *p;
        return out;
    }

    /// @}

} // boundary
} // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* segment.hpp
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
*/