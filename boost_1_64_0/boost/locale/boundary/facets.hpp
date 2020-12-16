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
DhL6XDjOM5Jz81pzOJ6EC8wqV+ewXL3Dcg0OyzU6LLfJYTlju7NyiQHKnWyXAzksl++wXJHDcmMdlitxWK7KYbnqAOWmSeXcDsvVOixX57BcvcNyDQ7LNToo57bG9jieOdJnnSWUqY4Abua8NVuBGcBfOE/ZH5zfx4C+0SYAxwB/4/w+24HzWO5clruI5S7m/qXcv8IEe54kjkdxPG6kzzxJg1AuAbgvMA04GNgbOAS4D3Ao58MqAs7mvFfzOO+VeRwjgFcCDwTeYtYBbACOAn4DPBT4PbAYuB04GtgPx3EYEHUJfSOA43i8Y63xC2Al2zHGrIfHuyePN4/Hmw/sDuwPNNtpALAUuBfwZOBASW9iAL17UG9X6u1Gvd2ptyf15lJvL+otsb/b8I1KvXGg8dR7NOcrm0C9E6n3WLMdgJOAxwGnsB3L2Y4nAM3+PJH1TLC+CwDTWU+s2a6sJxrl2gHbANNNHrALMB6YD2wHHA5sDzwBmAisBCbZ9st3TuA9Cvt9j/b7Pu33Q2AfzoNnnsfHwNHAT4CHc92oI7juklnPF8C5XF/K1Pk18CKuJ+XmelJLgN8D76a81W9unvdURb91ZL+lsX0z2L6dgMXAzsCJwCxgCXA3YLY5fx3eaopBlaBFoBWgNaCNoIRkrHUDKgZVghaBVoDWgDaCElLABxWDKkGLQCtSYh3n4Mj5N+tAayDLvBvm2ujzbDaAzPyaRT55NNeA1k+LsXNoBku5M2VHgIc6fHNl+oKk/BiRGxPFPBj311HGfDn/xSf3xTfvhfkuyHWRclzU+S3MZ0G5APkrE0DrT4oRuSo7zGNPjTVGgCpBbtDDoHWgHaDsjuCBKkFu0MOgdaAdoOw08ECVIDfoYdA60A5Qdjp4oArQor/ZOxPwKIosAHdPAkkgQBIghBDkxoAIISLHihABFRXYcCkoSoCEM0AWwqUooChXlKiorKIbEDxRUXE5BAmIcghuuAQUNAoeKEhARNZF3b9r3jQ9M91hBnXd/Xaa7/Gn63hVXVVd3V1T9QpZhuxGTlULrXkJHaEjdISO0BE6Qkfo+H87wpHBv/f8/4GDjZn/v2ref7xnXv0+Y971wMFib890T9kv7mIrz+OeKe5q0pYl/HxxF/t3at52gWVfwEzdYa7td+acMMlEYHPlPHrXOOiNseiViwhKbxWXw9xai151sUHmN9tBb4pVL4UbqF6PXZ+2Dnb+io4rvei0zoZz/p3j8HFHO3+iy9k+1IfHHe38SVxn+1B7jjva+ZO4znb+PlH+YudPwtvY+cPd2c7fQsTr/A+295XuYOevoETq08vIn7ONvzcJ72DjD12B/24lYR1t/BXi72DjT+I62/hbUuJn4484tjb+xN3Zxt8r+J/Hxp/k1dnG36L/Uht/KQ42/jJOSJvwmuWgOdr4yyK8g40/dAXeJiSs4zyH6SccbfxJXGcbf+NPONr4I66zjb8pJ0q38TfmhLONv6f/gDpXzwap3wUMANvZZsv39OFB7peUfzzw+Qj5xwOfj5B/PPD5CIS1tcu2+A+yy+a5lw7TqdrZUywx7yXrrADnOUNRJx3tKYou5+dl+ElHe4oS1/l5+csJB3uKEtfZniI8abGnKOEd7CmKn7M9xdonz29P8e6TzvYUl9jYU1zyH58zHLw9xf81+34DOuu47/rx+GJt/Yptb7Q/GpcQ0++7kH2//3b7ftp3znbzaoo9uBqwjJx74sVcYLzaFxgv5QLjqXdyuMghni7xFlripcl7oK19PwkXJ/FmyPksOZ/rlb68S8Ch50l/iCVea3muOdnpqyPXW1fs9NWT3zzrW/cyk3R3OqTbUNItkvN82k9CAvt7IJ2RjIQ=
*/