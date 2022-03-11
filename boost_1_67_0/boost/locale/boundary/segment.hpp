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
hDAfssuqa1wfdEfnc/wqVMOQw+W3AiYjZwd4IDNYi9lcTAP7tEjM8bJHI43dyVIh91B59sHDG/MwYcPcZBu7esojAvTRuuGbE67jNzWT0LJocPmwlfQZEs2ePOTLrViXj9rHvIxi1tWqkI2FgdZ6ck0eyWrr4opYEzQuhrbrJlGexNlkbjw2lVgEa0ueR+7bqGmUvG99KxM8P0ZmLXvWEri4ISTv2w5kiDlA89siFm85LXcEscIsvFAkevbBDzdyTFN56DEJyMn3hJ4REqF2FxRP0Bss63wMSYo3b2jwDKZL2CcdakkGfQr8/gkQ7q/omztH+NJ3PqBlaDj8T2fEOMR+tTBIqvmsX9JCfPAWb9v2gHrmXsoGDQlQpGoy6blmtKNFJ4e5WDlTBxyh1pIeXfACH2tzMbR/AO1nPwFFpaf1OJuv7x9btEpoyo+Z8nL4ei/du384maxVgSNHoehIL40jt2CASihDYSNETL/cvVKSTJySjwzWo36QlghOPV8VjY3FP1GLC2x5fVU+FAIe/fkHWGI+v8edwXBEzLL+m2wDv3WrgEOX/ihU4NZLnjBfO4RbNJLNFCzVOC249SgVsn3X1jqqWsfiWC6dE6Cfzb8Ur2temeZYe3vTIpDtgG/LEY38IY1cHzBUUcOcY0CdVw8uGBkJ7ajNdDNtFGfb7sIJyNjcOfOxrNQ1JE946dzX27X+VpB4r82Y2Z8WM1TJVE9l1XiP/qO9uKYQ3eDxWZzMtbj8sUIGWw+2gWyw1dQ78KtiLpyYpSkPAWHL4mVWZp/g7oWSNc9BwOu6RIW+uK8T69AZgvoR1rMb0UMl2MLwj/2T2StAN7Xc8wTFz0actdh7ARDlTTZaq3wKL/u1A+8sBeBoxvKSRUyBoVFiylozdNe8UYvCoU2SZ+iVjlhT2d01aSq4VtnoPRzYvqQWhgoY4uqFvCj/2aFpPV9JljqiSGHS2DreKSduQdXBzWQlz9Kl5Bm3cIfQ5FRQTfRAtZj+oLGPwEg/3QWY7tp1MrDOKxjdB1UgsuMKfqIXnVvRVfJQZeo29RyWwAKtvRY8boLCt8+xKnybt5OrZgYWwiQjgK+4rdMvjke+1b1tQaFDZHT5CP5fl6VAOchRndMmRWNTODs6cXNUmC/GJrq5Aj5MHXWpTjuPA5m7ptOtD4JMUvP2fJ4ZWrJVggXqXkohU3HvxfOIML4FQPFcMV1i62ZbtDvtkXeFmDtd4yUvzBzIh+qeBrm1Td3mPXZCSwzb/HxshD7ez90kuysZvWv3vQsKMDmgcTwM2WCWzqKy8zpGKF0JrRkpa8k0NuZYPpk3TZSEJxdzyv0HdE1kwl1jO9i7PjSNPGGetCWXAcQ6SwgEPfHm0KmJEprmE+vtO4YIXMR383qaMJ4Dk5BuDfZ6BEblRxMSDTnQGFwJjKtdPv3k1HvZLVxCXa7hpXkgwD1Vo20H6ZxXV9DWeMNwK7nyZX/rG9fg50+fhwB1cM+yeRktKTEt6YEoaG4hc/p+9mf4hOJ54Xv1XJBfrDENpXyH7BEcg5+t4TR/uEKXTEUb2c29UiW460neYGgH4GXPA0YnTCfZN9O57lfONZdIBLDkGXCYH/e6gDGST6+w6dHDGXgzaCsO+xxO+NmvTCYisyn2BRPYTT8meoTXi25YvZl66sHzhmmjOGIDH4BzApkMcwoVsJTZpRX6lvuSYcS0Xbs7FDraF+jOHhJ7PjDLf6o+7Ve5QYcLyImlAbuI+xXEo+f/0L0qsDYpKas4japzn5JSIBG1VVXC6wNzl9/Vljxtmv/LsDT1tS9xWBixyNwhsaV9y7muHpuZ+7DuUKdJcnN6ye6hUT12Hg+niUKuCZsWcPhQ5M53cSjk776QnXQP6CLVchfwyQmG44d/ZcLJNAD0wEUtccEPtx792Y/7/fnpQwfwrBvYB/YsMJFf+JlLF2wPkj0ftpDvprkKL86v/sc6iJg7ZJHyxoKc1JOxgIOL0ZNee74q9mTpmwoIltUWwR5rBRdHoxKfGwCMhkZ75aFyAOvdrLvWOmKfqgg+cY73sJmkiMvzGKPWkYZ6j2J3Yt75U9kX2y3r4MR50af+mdZiJdkgiaW9vSZfx8rPrwuw2tJtfU/t86jC7az7nfPmbTCWSdnz33t9YEIJb0+e08vAc91+vsRkQhe6M9k9JcgBzuohZK1rxCGOPZnh5BOJ63Q3UH3Q0CxuIHjgOprAiTeeYED54fW3RYjErW+5ONdT2SxJxCcDHoThZSqefGoRbZNuAytppJ9z6Fyb4I/pni0nQim8zXnnQPChWj3Dnt6palOlsJMhMo0vZSmCsJi53uhtwGuwL8HIgSt+aS6BPkT/toxctdJsxYlJuYXuUizRoOZWanTpi56RUhfbGAOCnY80FBppz13a21RBm01oJk07E5JxEqVeAvFp+H/Tl8Ke54nczI4KZSAgP+63siVvSl7gFFSGLyci/0nxiTqQdscLg8bTz5okcN6OCXl9JDjGZCJe7qHd1aLKXajvS/FQIFUbTtRZx1e9ExgElzwR5i36IM4aurwnn8y4JjFcPpneu2DSsx59zaeEYmWoK9GX3hrHlh9cCcLZi03IODIK0zDfxL6bhbcY6xVKXKIGgbfwraobBVcgsIeLRRrFVM9TCa9EuSBLwzFU2TIZO+uxOfcIevwyqLJlkSWPYGkZY+V+ceWbUakFE+Q0lMovXaa3/6xqI2XTTNtbbEt5ThmCzqYeSCMVkfdaOynBBgkJCAfC02G613Or34ZIB8DBM8Qw4jZfEu/0fRpUBagomFr57LBT01m3fNhXii8l2JPLlpKurWO9ZTRyt5EVQ91L6gTcrfbnygIQMHIyXZ9yejCbPwhQGlGPKmodMu13XzkubIEbciI2/64vk8mQ/frSb+CDuwMvcyGABfgPaAAALP/TULU86g6X0yvvjw2OGt1P2FdyvqYxBRIEY44NdIm8nl25iCDFvH5qqB4RhA+u9B5Gf0wrBG0Dts7Jv3QeHnQ9dfkKuVHTYuWxCvQKzCizPTgjpm86t1dduiv6Ug7DttG8VYRniLLZOvDgvE2K7NgTKOL3BF4m1a3g8pKb24T3CH7YEnH1SIh4QLXvAhLeK5ls7EHw8ldw7p4gvllxBk7vJn+UlxqfKh9mfMfX11a5sUng6qQ5Cbp/NlgYtvuBo7odTKPqTtvrcaM7zFa6KGRxiCLjbXQveBkUemdvmHNcHg/z8SX8s+YIgNo+/ZitiIHFzE2QmEdr8t47jlQHyKAjQE/aq8JeiL3Ai6Q13ravySONDRdEk7DMf0ovLXD3pCDJRWGxeN55tcpa7aRXaf90b3ZKK4VqXjuLQMuabJKbzQaXb/NQ7tiNpN3cZHuUdsJ+1YbFz6EY1MS8yJKg5+NNjB/ytU/BBkITI3r1Mdcmz2uQFt/xL11jlUMW5TcYIg8mI0LkrMs02fApGFad+Ue5cU/1Jgj5YSwLiDHyhiymMnE0OmNQSoCqJn5S+Kb7OlSxQIpii5wF4BRnowrdAJ+X1tEyMvEJ4cwMoqTA4gCeDvKj/EUhFsgbNaR+KzmDLn+IKDPR3VDq3j1u0nrHTKACXThiqi+3CJWFsMmJuQ+pPTMXX9KwcGJ01Y/df5GOofvKQcuGc05xfAdPdZ891OacWIkmcPtvEQa+E17Jkr2pIeWd9jsJjRQKfnYo8ljOsplZDSLH6h+y1caSwjTZ3JycXCUKMpgmzhw1Q2ly+tS+NMla1CYzSGHIVbdULcutcYVPPHvq7tzNyltF/Gh30q4hgdcluuHoVjCJViWpkxKw7UD4dh7uvPsqd1UNFV6lT0lGEDAUwfDicWrDpuVEk5WC6MLYWcWkvdUENH1Ewi2hmtDOiI5J+Nk+t9tNdnIrvzUHxc519Xp+nBuilJpUOfWASp3rAkLzS06YnG2J99B3xG3WRJMv5WcP92ge0KAhBOu114k/hXOFSZJcPlPn25Qeu/FL/EpiJvZexV2qYP8IWjSrkGVAdc58abNUPkrOkgd9lhm/iYi1mRW9UXdP0LbMOJ4CH6xu2SuROSKEXc9XrR5K4tLBvSAXidSn6YS7rbGwRot41kp2qA5e+K+tIIkPBkYxKXmJ4arvknUXAiqPxlVYS5+Os+kiFBQLymjWwBufWX3fthLugNLkgVsYb9HJNOTuomCWJBzL4oGQIsCT+V44souxa6FtZOtrVMluLvmmKJI+mTsgwH+Zs7m7HFLWX/xitdOptbj28QflEvvJuuuSXDfuwl78egSjKj/hhJP3XWF+DPNh+LxbIuA2okGTP+lvNivwJAyF9WmMVwjfrsmGyrQHPjDdBZWpWhSfMR4s30EyfQkyMQadtkenfQQbKYMgh5oMn2oz8P790mobZtRrByyGoiGCfATAoyeNXeL+yaIHVxU32ZICnyRdR7b77Sp17k36Yw1YXITkVYOVmlM+9F1qxRZwyM8HlukgM08yxTTJSNwPSg8I3lxKFN2SvfOkdz9RARyN6aMj3eN1zFKBx+PLugVb97I1u0LIRGzjhlQXZF3f/gA+Kx2f0cx6WQlQNVHrc4XqMO+XZny1T3EnvGZwP4nixeJlA0ved/4bD5giyf1JTzSQIeyeNJ7cmvJbkV3FWXmERnbCL24Gsrjvc0PP8YKQdOraV1ceJRXznfcsOfngZwIHcUsXdAK0p+pmEJsXWj6SrapeCnO2fKKg2nWckGnI6u6m+tUo7Q6vw0Eh5vf1RFWk23WO5OyeJfMs5ys2qElrOsf9rHeCh0/twRShvlJx+iLSx3Ee4Gn7NRjMYhMJ07ZtzaqD8BL9JyHop5CqYVJx5VlUhiSHAhgUXnHXUswmndw8o3K4tQPmGetcoNa6OVvj4rfPxg/ldzDXcUTS9dv5n4R4TEgw9p4nvkx9Q4gnY7P8tZSTp1t+/r3IMcQUCzumyIz/bPnUhZmNnwWGc7XiawrxxpmAXQcQbZFq9zMgWOmVh/+LV3XuIuhYJPThFu/91ixjfmaQf7tliZv49IqBh9FUy2CmBdYmGpQdH5UjsC8ZxRreoFQWqtNARWgi1MPx0Zlbslzl0PaWexadQPbimiFaPx1ru1IkzCOqItzaALH93J0p31J5qp5EcMhcW62gQvXOvq4hQyJGl2IU+J58bLluPcAbmSyuNlHTAgwiOvouLJ/I88NS9pQYrR9LtdbtknOOGcphAmCY7XR/WxtmWbizTjE6XctBvced9Ydfjqd7BlRxwBfgnk0/C9y+Qbq8vcO1ubBQjbJdJmCNEwxUhajKTPJx29PrFUIAv4V4OIo+OTr+XhRU4xIuVu+j9m3wRmdLvy7oNrg3gVH1jyCmrG0SM1IPO9+KPjT+OGmRCTdtiUEyTUn2z22DrZV8UsU0ElsVRUfAwg1n7WbeRRkx6bG+dHbT9fN+Vi6xCxbLNbg9OjS4J1ddrriZvvASzkPxipkE25IuvIGmIdPYITHZbY33W1n6di2MRR99xU8OZo4AGnFxbPlmWLVcGUJ1rpai6lRSl1TVX/KPe6hyeBVcWT6Jud1GWIGDV5XSvE1BK1VtzB4zoBuYAnCIgCiJfzuO5v3undtpzOdqlOhG/XolR40OJrTujTBdv+WoXXb4F3XeE4twMh/uETqav+kJT/UUzZPSW4z0E/qfTLZ3ZL2IEe+v4uLnhhEaW4C/l7lpu/ua2GZj7fFJ26kFvwYpCUfzIWlWe/Yb8OELNiYNHHmvF9MWHoekcSM+HT9+Kyibe3tS9XFQ3eF+iDca10QLaOY+R7sbtTvU0IBsLEwle4DSDTBQG2iYFlHj1GgvEobOaWivTOgMXFkB8xY/fYw9Wg+d/grR69nJc5aUY0iSNIHCl/tZrQEOlRt+1XFMlSq3MH+xMikqYQV3yLvlhpxmJha2vY2Z9BppbxUi4lskwY9vBw2ur1zHejHzyTaj2VlBYpwhBAPRLORJMZxw/FlazvEtCUA5dqwU1zqGi6XilD8/lPb4TJGRp09pU1MlzxM3L89z31Fdwo1DD9t8FNUTH08KsK1+FyY6wkX8JfsodaLjpxyf5HhNwu+TEsAmVD1J/j0Smo1nsg9jWN3Zv0jEPgBw5yuHxaNJ4a54Cbo9d6pUGsnu5E3jUd9LPDxMiRjVBQWH5aNXxYkcif0FrVlaXP0Z/Xc/hzY7HYYs0ZnVQ1/7teX2I5r8lJJHvzO5bX619TySMs3S9wQfJRVaIzWeYL9Tn7nIvZsiZAH7L4qyn9tyMGI6reGXBoCz2nUZskmWq/OHV3rbSu1Tu7WOE4Lzf3k+t8WKSME7JmQ/yEYH9r20sUMIrNQxC2B6a3L/abOagbRSKLn/wK0wAlDqALSmHzPh7+RsbDkoHIbTqg3aJuvZEmW9qND8Rsm+1x8s/qJ5f0m3PeaMWhHy/n7KhrDjqoVvSWVioaPetIuCXDziF1mOwNmPsskRwE09w19yOLfVrHGWd7PT53e8wq3KAbo62k1soJZNpm+hYREA5A54XjmcUBZcE+W56Fhq0HNex9+9JUzKVtav5E/q8d4gtQweESmsw95jDjEJYMT3uJSlrqEsOS1Y29doJWNh2nVSbOdGUTsqQabaS5ZbMGPGsO1uVjSIqtH+ExxoBVCYetGp74Gx05yCBrgNEAjGWd+eQtIftK1y03O/1mxZuAt5AEehCvYiquqBiMcdfbRLuJUPghzuJKH8hhPu9+uh4+jah9mMAeOV5l0h1MGNnGaTdvAkeTNhKGHwlp5/ipeKEOYfmtHyxelE60MDd+qeEUQhVBJT22u1YvCgDS2m6Gv1Dd22ce5MGCtTaQJIaW5g6ux+quBX+gFjEPK+1nVDScfA6HrdSF53g7AuoaQrxMiMhGbx7e8x4ltR4SH6RJaH5epzKPQc+yoq/90+ggEfe1vW5ffUm1PUETCA0eoV+F0xf6fOLCnqKfjVUomQEzhCyuRShQIx5qu1L2fZ6gqXXObk3cDvCIPIZdkgDHMtj6RLBCNOyAuNweaEj7VqG4fkeyK/7voZQfwBtB+bL7A0zbd+Sj/EUjAUe4Ww4zzp2DJ4dlr1JuWNbJ3+CBJgs5MQ01jwQAI9qjwHf59oVMcRI40kPoltSYemnK5hXbM+qwnJwKt6mCdLI+fpHlH1rNsX9DqxCc2wVxrENaKDK991UFwm8otMlPeMT3jiP8yTMvCMIpxGtcroMQjElpSYXPu6gGB/mWzwXJkuVcSuiDo56ev9lhRMuq9dPZv0ZLyVb0sbUsnaWfKqzruZJoX3Fwdqr9k0ZnNluR2IMGe8vc1elV7+AreDnfG5fYWad7gmuageE1lONec0Egm3aVOWw4LQBKC4v5O+4Pc1MVKbHLGI8JjHgY07nhnqh4sHc5KXjoLVzu7NrHGiQKELqRU/0Kds9duwAoF5BP2tJ90BstYz0/qpPdc5Pf2qW6R30mwptvb+zGhmhmvMlwsjHxLRAW1n1Pmm9plMyL91d/DdRY7UOHen2futw7qFazVmdkxGdSELtXgxkSvB9/99nuXBoGXTr7dnhRjbHiPYEMn/dmio8EUIcbv+95/Ee58ertDOiQaPPV3xhCeAC8PcrSlhMm/7EdfkZPP4SY35SC8yIuxQ7/qSldRDvBbv4payOugFZ6+jitirPW5xpsIndZTfdq/IZeVd/yf4jnUMP9Nc7ncVCfQM4hAxtaU319NAIy6Aw8pNyTmZXDxKvbHEU9NhZ0OvEtqkG46FXJJQHCsA6sJk73kfodSD/Rj0/K96jZFOwdBE5fQnOtDxorr2TmxDYlCRaUuW/2XSLxh90urFA3En2QNhuUcPY+9RUDsVbzT4Q2Dr7kwCIzC1iPEu0EraoG/rhqnuaecsYfMvMHkcy4y5QcQmEZJSdP39hXhe5A6RNGQ+UAj92sOHKiidRbxGr6gi6AzR8Arg+xoRpqDF+o9pSExbsC15694OF3FS5+/+cnSw5uuGN17kkZJoD506jkFmGBWe4O2/ozcurezdJWtGsJZTPyLk4sw3yYFQSpbiZVM0X6TCNg++/hTbKmNWGisUiuvfZjFBQybnLErTc2bmyMzhJ6RAwzSuQTEEWNfVoHDGHU05LuEbyBFEoi9bD4sMvAp7u6mIGf8r5XtJZW0RMdjwPp5S/396Z0UURpWv/nZrOrgjU8MRtVGDwwtzIWNkigZLRw+rnuDb9cuPvsL09Toc6KYnIzjX2egalfjCMQjMliNOFV+46w7w7p9Mcc67oMyVP4EBG/NDN4ub95hFMw500nDTLF5I6iw0HYilDoYhSCenF2YF+JGmOGZtjlKGxCkWvdbk/HIT+sWumtoCx/dTXZwJQM5xX9D7/J1bTzEvUkbtntdpoqwOlXHHwnVOVbyzP2KaoZ36lw2mq0b8aj8eetpLMx/z0gEa7/yiKyPeZpAfyyA96v5fJQ5ioT+mM6YRVXY9xSFYPr+PRBMjL1M4zbhtdhXuFue2XcFiJiMlmXg0rCyDFOpncyxmK6E67LfrhGajrmbcVzl8dVtl/+3UAjVXgXDcgQraXuIfLiYI9O50+Bwrp472tpB6K2Yg8T4vLjD6pGb5z5xJErUBjdgxo4s+h2UWzmU4DPDod155Y3dechAtP9E2uAkxqg2vlRFSH52wMTaNrXy1LNb3CUnmO0ZxivwjKiT4DESGYCL0Ywu59cWiyOacBJKWcx4B3qyQQ4A8YBIZhrocUWB7td6NWjezahXxpSNrCjNXk5XaRG1nfSVMlKQSDvCuZW4d/p2VVfI/May3C0f67YIVPODRuMcKe0OMr61qGsuMjfj+Hm4rMgRaWT0EKCjKyEdMl02Eu8gCDB/S67SgwSejYcn5KFh7fQmBEAE0u/CXAdItAqY0IhTPHzlxNrdXi5aqvRzIQF2uH9xyDEMjSn0HPknGSCGUtp2JZRRqK8JrAizAXyIT59kFv76ryJMCeAYsDWmJe+Q+BtoChh1HOQAwiNu/8Jgl+46BJJEq2rpbI86a8dSph8S7BOXtZAo33mzcSWbbKkoKgSHC6gqKBr2v9tvehY6SWO5GrqmTkEbpwMUkMguAeQgPATftrZHpGc7OaWMCRgceeRyshQU5eNSCTmoWaTdUs5kzA6hjy7bTjwTGjUYwcAoShGAM7wHxxwQmEGnfGri6xdD2fzkPqefWNqUcKPxRE4GVn12CcqXgtNot6ntq1A6P+smDcJNzPYZStPJAiPU=
*/