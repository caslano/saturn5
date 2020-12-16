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
ZioelUM8yUcDFW+YK47rvVqL1dYi+ymNKL2y9ooeK/mltlQ4l3U/uPGaZU/h7ocN//aMH4epMDNVK84dMETun6PUk3Uf4L9b2v8KZKXnb3FfhaxG3kTWIGtlD8l8Mv1qjPs+SbK36dXRSKOc9ie191dVTf/N7xnc1PUY11hVrtFqf69E9osz5mzFCuuSdsZBr/uGZ302+TTvGa2llOVoFa7YNR6t3XTmFyGPIRuQs0iMy6WNRJ5AnkZs7hlJy2pbL3dSTpamNZV7ZKry/4eLdqBN1DaxP05VbSySp4/TIlw3aUNcDbQHXWHKPlukRx9X8pl2p+V+sktnwJghFvuL0Z8Y/hHm/pBffGyc1yHP4abdzitUmI5aM8IZ8eI4a6Lcytrea9Y0w1R/kJM7xpJmKxU3UZ1X5vysCl/f9r4SXX73R0u5Lycp/w9cw8lvBz1cu1Uvr82By/WyWgkMd4VrA5DZrihtnitC6aljlI20lUTJUzt13b3RUklLYoZaN/7y7IG4UPlFaXE03XKefZ2knOKVm67c8pXbIvYnnWvWSwfldoJaGWnuzX2jcjuoDVNu1uvqT0M/V05fqnKqK+dS5uTrT9ynFTTZw9UiyUJEnl/iLven3Z6d0d7PL9KKNqC1LiYty3kVOY/TysQeVfnX6nfpdllzTdw+/sTjlnq5x23aOTczXKTp1rylx+1T9Ilbqsdt3Tm3FGUPEbcvD3rcLlfnj5nnLTj36kOk/xB7fnJvSf8hbtwHlv7DaKdVpZ164tax9CnW5+7mmpo6XpF77GWx3xnj9dw1jXja7jMab8RR4Rfxs14Z+/2k8bex62k+kxop//uxGxxh8yy1iz/M65lQV/kv0BI03f8+lviB2v8krN19avYhlyj/PK0csWUPSnMv0bfgOqTxr7TLeqG2Qj37iC6u7U4o0cVzF4bL+9TUr73qNTd77PnfqV5WcY7qnnv5r+o80a6e0W/z/mR5535e+R/SW+vVtLV6Fbu6Rof9e1OitLW/Kf/P9X/RWirp12vvqXcO/HCdftTwK2fXBtBr895keY9erPyP6B15F3kHsWkb6LB/N7pIyibtG8M/jB67Pj3vI9o2etBiraZ5nzyu/LuR8yjfPPu1t3hp2ytVmnv15rwTvq5XCuidJ9nTd4qskPOVPu88a63vPT7vPAn/Ze88nj6rRT3+kz3+DH2doNG2i9/3tG01LuNkZ9y8j0tU+Kb6CC3Mri2jL/Bvv+L3A//2I6zj+3sCHPQPw3+1Xfsjrs23oKUf/Fn5N9Rv01x2tm1VncUo/d38/OPE/y/K/w3s417nqGOXCtNTs7a5JJ999h9DUoNw+8/ZznXYszcIN2t7jG6gqSNb6ne4jEeke7XH1ufdrzlDhe9r2xbTg2iL6UG0xfT3Ax+HkLCl7tf8hM1+zcNUvO6Wfbe963/+H7xPv1O9Hm5oX6+F26316qlW53ot2u5Yr+gKvF4Ltwder4XbA6/Xwu0XVq/7t5der7X+y/biNt95k8Weh1z/EqnXqUVmvfK9XEq9yvXPVeEftatXdAVer1OLAq/XqUWB16tX2ADrNQEuUvHu1hpTr1Fi+7yR5X3iccvfT/zB9+44p3u3sTtxI2wFJFvqeNk2s475jeL8dbxehW9kV8foCryOJazjvhNfK/8ouzonrvP7Qjzcpfw72rUBieuz74TU8zHld7Htu0Qc3Kf8r9aStXDzuX9AuXWw3auiCtyq/HtoFWk7Ls5rVqft/AHPdmOs+WcZa9YaeLeNpEvdCQ/B06X2H5bfD/aZbWNIaWPNdT2/H6jwPRnJKqO1QdNtjIfeQS4u1m2/gdFv014s39BN9hv+87SB9t/AxHf4LpI=
*/