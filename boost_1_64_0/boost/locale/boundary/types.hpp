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
sq+l4kfpOcReRJ4O2o9pocfhO0iuq4XSk69m5fZDj127supY1EyVpiqcutKeP1b+ffRY/k9F/o58qUadda8xn0JkvTwzNiBvIxuRdyzfMG8nuvnur/ymvpB2ZG03R6Xd3Cj7ovdGkoz3vB3e7YZJ0KPG5WjW8Va79kA8mzK0jDP0U/71qXtd9n5RZaa+zxrDBdC3PMK9y8NvLMk6drwy1R3w+XDiCesadWK5Hrux4w7STjarcAvDJxH7PvQeZLwxmXHKCciTjOmXdZXVHnFV1mowILUWqRgervVE+oRH2pUH6dqPI7eTb+u9yv+h8ObalaxXj+DJey17bLfh95LO2mzGE5bpXbV6jGSvYky5TtiDrL3N07qFy7iyRz9XOSOsg5muuNuNK5v9YLnd+DMy1pTdi+rKvXbdTtxINZx8DOceeQH5J9JUtx1/Ig2ncWQZN1Zp1Df7gvv3uO/BGzSX/TubQ9vpIG2nSPn/NXwM37Z3ksdPYR09TMtBliC/0Ec96WI9cFiY1jssU4ugnLog3cMjzN9huqprdFn6eulbpVwmqTzGmH1/S3XeXM498ct6yl/O24ZFaN+54qz5lrHiONHziNIzi33PdV9dlH/X2JJLKYPmPJ8SKdsyd88oGxkWVf6q8leXDY9mmAs9Zv86aPS4UblZ1nK+VpVzI9We5V3XvJ4uUgf8EhI7nPututxvr9eQcRS55x5HpG/y4hYqbpP8DZ3Gs5VO0Yeu8/dpnnHr9A+8x7GTPzg3jj1rjzmObY5Zf7nbdEvxuOWYbqmtPG67d5lu5ph1x13+Y9undppul3nclu/0H9u+eqf32Pa3O36fsW1r35wnG2l8K+vvj8k4dsFea19mjmMHtBcVce3GrM1xuRXK/wPqi98stZvsntnosBm3tjxrlyn/j7imMO0eYtr0HegIfOyasHb9gjnGuUr579IqUHqzEfl28xq/3pCo2i/i3zajg3je/tox7Lat3Ak9SuOJgI/Ie1rtY5Y6LW0M21JXDVScfH0e+6gN15Ps6hu9Nu9nlt/VTiv/R8lLFXqJylqa1sXs+1YpvyvNZ3dzdT5FH4XFCU8fNvdbw62GXTshbZt3O8u48jvKv4Dyj+K3nBZaf2LfodW0ay/osn2/M/P2N+XPTkZakvT1kjf7dz302bYp81nVUvnfoY/V/X+zj5f8hyn9S0lhtvYctXwN7S7GMlZdBfmrzbvgu+b7oLwDWn+bD6jvLBP7kEpbyxoz5vd5P0z1jEu3cSe8X/qgfdIHFW71tFez/3EcK9qkwi6xa59KT6B74xlhA90br3Br4P2LhLXWc5bBeHm+1lJzkW7n7qiujUKD3RhDFVik9Dxl0TNydGbWue/hL5T/DOtcJrXvYXXppzZb+qupMX9MP+V59uy70p3QzWHusYYbw2SPy3fNeh9d2lhDotT9X1T4VmGJ3ONpWmVXnqu8XTtAr8N3JJd6im/0N5R/T1clVxvtIinvl5TbjfpINLyCfI3U0sPt2g767fuiVLnfFyr/smHGO/hKpIS3qQZ6Oe0B5F3ke/QmMkfhVlc5s10/uln93m/X/kjPvr9qKHFfVf6f60OI/TzyKeUTr0dpU5AViPs3ZFqTSmOAcc12bddMJ95scxPGDMvNzRrVn/QsczrmSV7rynvhkU3uZ3Q8td4OjX357eRF/Ddq5c1v77FKd8ewmmpOQzXXbOrO0+//pPRFmL+vTFRhO4Rt0Zaqa16s7o/RqjGkSvufosK0DKtAjTxOr3kAqaJHatchryFfI+1cEcx0i5R2oMZixg22PK/WudPRYyiN2ozjTNY2ih+loPL0FtfEVWr9yEkFtbdiCfnbouK1d5WlXv+lt8E=
*/