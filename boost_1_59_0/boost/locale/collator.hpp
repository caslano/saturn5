//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_COLLATOR_HPP_INCLUDED
#define BOOST_LOCALE_COLLATOR_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <locale>


namespace boost {
namespace locale {

    class info;

    ///
    /// \defgroup collation Collation 
    ///
    /// This module introduces collation related classes
    ///
    /// @{

    ///
    /// \brief a base class that includes collation level flags
    ///

    class collator_base {
    public:
        ///
        /// Unicode collation level types
        ///
        typedef enum {
            primary     = 0, ///< 1st collation level: base letters
            secondary   = 1, ///< 2nd collation level: letters and accents
            tertiary    = 2, ///< 3rd collation level: letters, accents and case
            quaternary  = 3, ///< 4th collation level: letters, accents, case and punctuation
            identical   = 4  ///< identical collation level: include code-point comparison
        } level_type;
    };
    
    ///
    /// \brief Collation facet. 
    ///
    /// It reimplements standard C++ std::collate,
    /// allowing usage of std::locale for direct string comparison
    ///
    template<typename CharType>
    class collator : 
        public std::collate<CharType>,
        public collator_base
    {
    public:
        ///
        /// Type of the underlying character
        ///
        typedef CharType char_type;
        ///
        /// Type of string used with this facet
        ///
        typedef std::basic_string<CharType> string_type;
        

        ///
        /// Compare two strings in rage [b1,e1),  [b2,e2) according using a collation level \a level. Calls do_compare
        ///
        /// Returns -1 if the first of the two strings sorts before the seconds, returns 1 if sorts after and 0 if
        /// they considered equal.
        ///
        int compare(level_type level,
                    char_type const *b1,char_type const *e1,
                    char_type const *b2,char_type const *e2) const
        {
            return do_compare(level,b1,e1,b2,e2);
        }
        ///
        /// Create a binary string that can be compared to other in order to get collation order. The string is created
        /// for text in range [b,e). It is useful for collation of multiple strings for text.
        ///
        /// The transformation follows these rules:
        /// \code
        ///   compare(level,b1,e1,b2,e2) == sign( transform(level,b1,e1).compare(transform(level,b2,e2)) );
        /// \endcode
        ///
        /// Calls do_transform
        ///
        string_type transform(level_type level,char_type const *b,char_type const *e) const
        {
            return do_transform(level,b,e);
        }

        ///
        /// Calculate a hash of a text in range [b,e). The value can be used for collation sensitive string comparison.
        ///
        /// If compare(level,b1,e1,b2,e2) == 0 then hash(level,b1,e1) == hash(level,b2,e2)
        ///
        /// Calls do_hash
        ///
        long hash(level_type level,char_type const *b,char_type const *e) const
        {
            return do_hash(level,b,e);
        }

        ///
        /// Compare two strings \a l and \a r using collation level \a level
        ///
        /// Returns -1 if the first of the two strings sorts before the seconds, returns 1 if sorts after and 0 if
        /// they considered equal.
        ///
        ///
        int compare(level_type level,string_type const &l,string_type const &r) const
        {
            return do_compare(level,l.data(),l.data()+l.size(),r.data(),r.data()+r.size());
        }

        ///
        /// Calculate a hash that can be used for collation sensitive string comparison of a string \a s
        ///
        /// If compare(level,s1,s2) == 0 then hash(level,s1) == hash(level,s2)
        ///

        long hash(level_type level,string_type const &s) const
        {
            return do_hash(level,s.data(),s.data()+s.size());
        }
        ///
        /// Create a binary string from string \a s, that can be compared to other, useful for collation of multiple
        /// strings.
        ///
        /// The transformation follows these rules:
        /// \code
        ///   compare(level,s1,s2) == sign( transform(level,s1).compare(transform(level,s2)) );
        /// \endcode
        ///
        string_type transform(level_type level,string_type const &s) const
        {
            return do_transform(level,s.data(),s.data()+s.size());
        }
        
    protected:

        ///
        /// constructor of the collator object
        ///
        collator(size_t refs = 0) : std::collate<CharType>(refs) 
        {
        }

        virtual ~collator()
        {
        }
        
        ///
        /// This function is used to override default collation function that does not take in account collation level.
        /// Uses primary level
        ///
        virtual int do_compare( char_type const *b1,char_type const *e1,
                                char_type const *b2,char_type const *e2) const
        {
            return do_compare(identical,b1,e1,b2,e2);
        }
        ///
        /// This function is used to override default collation function that does not take in account collation level.
        /// Uses primary level
        ///
        virtual string_type do_transform(char_type const *b,char_type const *e) const
        {
            return do_transform(identical,b,e);
        }
        ///
        /// This function is used to override default collation function that does not take in account collation level.
        /// Uses primary level
        ///
        virtual long do_hash(char_type const *b,char_type const *e) const
        {
            return do_hash(identical,b,e);
        }

        ///
        /// Actual function that performs comparison between the strings. For details see compare member function. Can be overridden. 
        ///
        virtual int do_compare( level_type level,
                                char_type const *b1,char_type const *e1,
                                char_type const *b2,char_type const *e2) const = 0;
        ///
        /// Actual function that performs transformation. For details see transform member function. Can be overridden. 
        ///
        virtual string_type do_transform(level_type level,char_type const *b,char_type const *e) const = 0;
        ///
        /// Actual function that calculates hash. For details see hash member function. Can be overridden. 
        ///
        virtual long do_hash(level_type level,char_type const *b,char_type const *e) const = 0;


    };

    ///
    /// \brief This class can be used in STL algorithms and containers for comparison of strings
    /// with a level other than primary
    ///
    /// For example:
    ///
    /// \code
    ///  std::map<std::string,std::string,comparator<char,collator_base::secondary> > data;
    /// \endcode
    /// 
    /// Would create a map the keys of which are sorted using secondary collation level
    ///
    template<typename CharType,collator_base::level_type default_level = collator_base::identical>
    struct comparator
    {
    public:
        ///
        /// Create a comparator class for locale \a l and with collation leval \a level
        ///
        /// \note throws std::bad_cast if l does not have \ref collator facet installed
        /// 
        comparator(std::locale const &l=std::locale(),collator_base::level_type level=default_level) : 
            locale_(l),
            level_(level)
        {
        }

        ///
        /// Compare two strings -- equivalent to return left < right according to collation rules
        ///
        bool operator()(std::basic_string<CharType> const &left,std::basic_string<CharType> const &right) const
        {
            return std::use_facet<collator<CharType> >(locale_).compare(level_,left,right) < 0;
        }
    private:
        std::locale locale_;
        collator_base::level_type level_;
    };


    ///
    ///@}
    ///

    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


#endif
///
/// \example collate.cpp
/// Example of using collation functions
///
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* collator.hpp
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
*/