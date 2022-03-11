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