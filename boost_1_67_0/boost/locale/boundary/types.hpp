//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_BOUNDARY_TYPES_HPP_INCLUDED
#define BOOST_LOCALE_BOUNDARY_TYPES_HPP_INCLUDED

#include <boost/locale/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif


namespace boost {

    namespace locale {
        
        ///
        /// \brief This namespase contains all operations required for boundary analysis of text
        ///
        namespace boundary {
            ///
            /// \defgroup boundary Boundary Analysis
            ///
            /// This module contains all operations required for boundary analysis of text: character, word, like and sentence boundaries
            ///
            /// @{
            ///

            ///
            /// This type describes a possible boundary analysis alternatives.
            ///
            enum boundary_type {
                character,  ///< Analyse the text for character boundaries
                word,       ///< Analyse the text for word boundaries
                sentence,   ///< Analyse the text for Find sentence boundaries
                line        ///< Analyse the text for positions suitable for line breaks
            };

            ///
            /// \brief Flags used with word boundary analysis -- the type of the word, line or sentence boundary found.
            ///
            /// It is a bit-mask that represents various combinations of rules used to select this specific boundary.
            ///
            typedef uint32_t rule_type;

            ///
            /// \anchor bl_boundary_word_rules 
            /// \name Flags that describe a type of word selected
            /// @{
            static const rule_type
                word_none       =  0x0000F,   ///< Not a word, like white space or punctuation mark
                word_number     =  0x000F0,   ///< Word that appear to be a number
                word_letter     =  0x00F00,   ///< Word that contains letters, excluding kana and ideographic characters 
                word_kana       =  0x0F000,   ///< Word that contains kana characters
                word_ideo       =  0xF0000,   ///< Word that contains ideographic characters
                word_any        =  0xFFFF0,   ///< Any word including numbers, 0 is special flag, equivalent to 15
                word_letters    =  0xFFF00,   ///< Any word, excluding numbers but including letters, kana and ideograms.
                word_kana_ideo  =  0xFF000,   ///< Word that includes kana or ideographic characters
                word_mask       =  0xFFFFF;   ///< Full word mask - select all possible variants
            /// @}

            ///
            /// \anchor bl_boundary_line_rules 
            /// \name Flags that describe a type of line break
            /// @{
            static const rule_type 
                line_soft       =  0x0F,   ///< Soft line break: optional but not required
                line_hard       =  0xF0,   ///< Hard line break: like break is required (as per CR/LF)
                line_any        =  0xFF,   ///< Soft or Hard line break
                line_mask       =  0xFF;   ///< Select all types of line breaks
            
            /// @}
            
            ///
            /// \anchor bl_boundary_sentence_rules 
            /// \name Flags that describe a type of sentence break
            ///
            /// @{
            static const rule_type
                sentence_term   =  0x0F,    ///< \brief The sentence was terminated with a sentence terminator 
                                            ///  like ".", "!" possible followed by hard separator like CR, LF, PS
                sentence_sep    =  0xF0,    ///< \brief The sentence does not contain terminator like ".", "!" but ended with hard separator
                                            ///  like CR, LF, PS or end of input.
                sentence_any    =  0xFF,    ///< Either first or second sentence break type;.
                sentence_mask   =  0xFF;    ///< Select all sentence breaking points

            ///@}

            ///
            /// \name  Flags that describe a type of character break.
            ///
            /// At this point break iterator does not distinguish different
            /// kinds of characters so it is used for consistency.
            ///@{
            static const rule_type
                character_any   =  0xF,     ///< Not in use, just for consistency
                character_mask  =  0xF;     ///< Select all character breaking points

            ///@}

            ///
            /// This function returns the mask that covers all variants for specific boundary type
            ///
            inline rule_type boundary_rule(boundary_type t)
            {
                switch(t) {
                case character: return character_mask;
                case word:      return word_mask;
                case sentence:  return sentence_mask;
                case line:      return line_mask;
                default:        return 0;
                }
            }

            ///
            ///@}
            ///

        } // boundary
    } // locale
} // boost
            

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* types.hpp
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
*/