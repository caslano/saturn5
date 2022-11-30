//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_BOUNDARY_FACETS_HPP_INCLUDED
#define BOOST_LOCALE_BOUNDARY_FACETS_HPP_INCLUDED

#include <boost/locale/config.hpp>
#include <boost/locale/boundary/types.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <locale>
#include <vector>




namespace boost {

    namespace locale {
        
        ///
        /// \brief This namespae contains all operations required for boundary analysis of text
        ///
        namespace boundary {
            ///
            /// \addtogroup boundary
            ///
            /// @{
            ///

            
            ///
            /// \brief This structure is used for representing boundary point
            /// that follows the offset.
            ///
            struct break_info {

                ///
                /// Create empty break point at beginning
                ///
                break_info() : 
                    offset(0),
                    rule(0)
                {
                }
                ///
                /// Create empty break point at offset v.
                /// it is useful for order comparison with other points.
                ///
                break_info(size_t v) :
                    offset(v),
                    rule(0)
                {
                }

                ///
                /// Offset from the beggining of the text where a break occurs.
                ///
                size_t offset;
                ///
                /// The identification of this break point according to 
                /// various break types
                ///
                rule_type rule;
               
                ///
                /// Compare two break points' offset. Allows to search with
                /// standard algorithms over the index.
                ///
                bool operator<(break_info const &other) const
                {
                    return offset < other.offset;
                }
            };
            
            ///
            /// This type holds the analysis of the text - all its break points
            /// with marks
            ///
            typedef std::vector<break_info> index_type;


            template<typename CharType>
            class boundary_indexing;

            #ifdef BOOST_LOCALE_DOXYGEN
            ///
            /// \brief This facet generates an index for boundary analysis
            /// for a given text.
            ///
            /// It is specialized for 4 types of characters \c char_t, \c wchar_t, \c char16_t and \c char32_t
            ///
            template<typename Char>
            class BOOST_LOCALE_DECL boundary_indexing : public std::locale::facet {
            public:
                ///
                /// Default constructor typical for facets
                ///
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                ///
                /// Create index for boundary type \a t for text in range [begin,end)
                ///
                /// The returned value is an index of type \ref index_type. Note that this
                /// index is never empty, even if the range [begin,end) is empty it consists
                /// of at least one boundary point with the offset 0.
                ///
                virtual index_type map(boundary_type t,Char const *begin,Char const *end) const = 0;
                ///
                /// Identification of this facet
                ///
                static std::locale::id id;
                
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };

            #else

            template<>
            class BOOST_LOCALE_DECL boundary_indexing<char> : public std::locale::facet {
            public:
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                virtual index_type map(boundary_type t,char const *begin,char const *end) const = 0;
                static std::locale::id id;
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };
            
            template<>
            class BOOST_LOCALE_DECL boundary_indexing<wchar_t> : public std::locale::facet {
            public:
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                virtual index_type map(boundary_type t,wchar_t const *begin,wchar_t const *end) const = 0;

                static std::locale::id id;
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };
            
            #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
            template<>
            class BOOST_LOCALE_DECL boundary_indexing<char16_t> : public std::locale::facet {
            public:
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                virtual index_type map(boundary_type t,char16_t const *begin,char16_t const *end) const = 0;
                static std::locale::id id;
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };
            #endif
            
            #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
            template<>
            class BOOST_LOCALE_DECL boundary_indexing<char32_t> : public std::locale::facet {
            public:
                boundary_indexing(size_t refs=0) : std::locale::facet(refs)
                {
                }
                virtual index_type map(boundary_type t,char32_t const *begin,char32_t const *end) const = 0;
                static std::locale::id id;
                #if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
                std::locale::id& __get_id (void) const { return id; }
                #endif
            };
            #endif

            #endif

            ///
            /// @}
            ///


        } // boundary

    } // locale
} // boost


#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* facets.hpp
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
*/