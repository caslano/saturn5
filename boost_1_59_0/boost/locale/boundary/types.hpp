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
z2pQip+GhQ2+RqynwQyovWoZ/phmVNU3N2xfxL9jEL/PbmZZrBfQJWpq3XIcTAakQSNpwWAWLjzdY3AoTdMw4CQnzolt27Zt27Zt27Zt27btE9v2l/t9qr6quWr/bs3udE9XzW4HULGUDtzjTskHs8MbpiGL78U3O7PCJjKnGjr82LVcMsO093TC+XSuj8QGL5cqTbCXc75XceCePgMVa9rsMpSdX8dr6nlbzs3yBJ8CnonuOCyrw9I2lldqNWAayZaW21G/fnJl5saTAaxzu+QS9a6lpZQL1HqSU9ZmfPSKN8Ul5y0iKzuMnZqj4vm4e9x4y6Q6395Bovs2QRpBxS8NF5w4IT/hlKQpJmmaF2/aabWIpFCWy3RYwVbqAlL/CFtA996XwjV69dUVXy0hhyEwvHt1piPwGvuwjoSoJTiJ6cupRvKGZeUJkLdPDANiuWQizNPbifoPA5XNnq+0bCZrOBtW+SxeUcHaoIpa4GSgUdzsX/tOD4SBmsbji8W7BV/my/HveT0Kp24Pp4Dg5ZkwF6rGy2K4F1G8JHaw43gsbFYmKp5g/53PKfoAACz/02DI08qVpBxK9vBUv4Kaz/Z/QotZbsvZRGAA35hp//CYFTKC3e//u9pp6P3cZkPgI4kTN8rIyvZXXuLl9L1iydzQbN8D59wI2BKLXmZIRBESumbAN/On6UnQ8zZUA1HNowt7sagMS2Zz+tF6vm2W4qy3ZRvEEDSQG3V/XrzNwiegJHIFqnYm0i6LJuI5zGTMT7VlTMLdiqVaYWSXxX3Xa0pfnQCXjcEQSg9ktdebANeYy7/ekDmRvt788qaeIin+jPS0bYqQK32hLXsyztULtD5s1CphfqFIjW3WlHbRN1VNpekz9dA/n8rUY/9Owbeuy8KQzlJfkAbxp2tOFaJIJhqZqgOqYQTeMaMGsFhnRAyM9STrpeXVAwT2gE/z+rtTTRYbooNlX8dW0IOY00yBZvPE/IYdbzv4lohsdIr++ccAnvNROIHspJkAZcOltFlNVEbyS/DjoGXrUekPn8T0vfKLPbaV+4EPJyJ+DdlraT6s5mHBehOBHtrd3Gq5Pd7ET/dldZUNYlmoHz6GUvZCtH5AnJ4YIpnosGR+zx+uyELkyOvq4IkkrF6A5ughPkUrPsP5bUbxQXmuaiB0KOC+AfImMQpiThfRMGOzSo2qKLnNo/I+Kb3OvoN9GyiSeyIQZyjW5QvoySgq6SQSYu7ldpHyUMVpGQhIGwMn86XDgXZF64A7d7rMLhri7tKsSjunnKM5lwvMJSvP5lXxG4WsCuDIFMIo27fe9R2yyrp+Guh1wCRwOki7GCwF1boMqkrKOrm0+Az9o0k6q9PYSuMp0gQqGO315V0B7wmTYNJFRlUXxy7OBp+fVFHRi9SVf/g5QyowBRJKCTeTOtwbm9QmYnUjo+Wra0utmDUw74ihKpZDKXOgpRDq+Z/IehD8itdQF4DXq/bQ3ctaVNrPzexybgkx/CRCy8w4cxwUN8HzS+GINoyYAOBjK7OZR61ugHRH9fLrQHpmPKfzzh1z6siWyWTsPoDQGWsvWAGVdVraMzV+O44q0of6qDR2pXlJOIQUa6no2QqgOcMUO6q7LbkdiMUP9dRR8+LNNQSwlmGYRcYVjVwE9Tz9dnw3yc+Pv4+ouSFhwK4+jwoeAXxinXAm3piFlqtyteWSBNCheugaDrhRCcbL/83bOfs4oRayE8RBQL28ic8lHl/v0g6Bbhw4ByLIqVRW5+0GdVFZxvuNo9H9Ir5xVrlg94Cs2NQb1EBZUZsk2ylcEVsxXST+JnmFAlZT4T4flD5ZYyw6sqOOzlMZiybqfP9l3WMTXw5FX/j2IuXyyc1FOzkhiQ8NbyvDeqL06KnGF5KsgHTGvaokm2nHwbrmguA0D8h9fm0/cWwqSk5Ab5Qk2hmCm1AIDvHCuwR1S6zRD6LjJcgAozjidm2R/OULc35IWa639wf1U9eGd/UNtvz7EeKfshykcXe+T25i3SlcGLAfStQoYNgAXkcysqdTu8q+KziQVsb0TzT3dtUycMBtJErAyavQBiIVKEmgeF3JZh/x+jZLhf6ivIPl/BMAAFD/b4pj/1+Ke8XE5UoVMAX9uODsAZE2kpU3YXXYGkQ1pw/L7jy7UgtMkVDhArou5uPWSr74yOVVf6bFtDhCTeYBgDNWqkaLFRnTfa+Tg3n4O2z6oVESulGBTqMnCaI0SFUpUjgCUhdRSdkCLzz/z0R00d9OHbVBDbQSTGj0jN5+w6hnz/vxCz7YiXN2lmkipgQGcuct/cdeSVNmgwTgFqAuSH6p9hvwkPk5snX7BlqnlDcrA7OfkDDCDKfift+rfH0TgGLO3FljHl4ePuVOeVRrZWoC40r5US4Pbmr4R044zFyB38FFrcpE0cbGyJx/V+V7SVR733aiIo0fdAawZKuineIV/lmo7fTfJPd+ZvQ8ZAoevzc4isaSJUVSboxadt48EDWdLbAFxgFF8gE63ojlgd8a9K1ZQtRnrVHkwqPYpIUIYGgDCnuEBCWpdwgNOGYJxBYW9sImVxrGFvKxWQ+IP2w78Np1L0tzXctKom/j8+pNlRyGKMmpEox1jXRXWerg89FBpzMB+x9d7VQMQd6Gn0oXTmVu9rVNgZuLwWHQCBTHuB+BHbCUTSQIgLsah85FC9k/cCgp08IIkqqk7ypvvOteJzLiGlSX3VnL19sQDVPjjasJbQisqSUbDulx/rD5K0tt0LWMQQyDkCUhYU9PswjyBgnELuVp0G4pKqB9TdjEQVM0fSw6t9FAt9HYJeEBBUBr2UlV0n+iaxgAuIyZtKDjQe5dZNzs8H42Y5dMKAWB1YZHMZ9cFBMs60/+MMiM1GLuxUrRZDTDi+ZMJiDZ45XZwKZLS1NCCIaN+pXoW6fBLZ3rsYJlmE1wdov67mbj06ciP+fZr9zWTQLTzU0DHXE7yHsJyZpEtY4KueiO6EfrYanCB3ERieAZFcF8/mNaqPqI99O2eaxvPDVtGyyeRwblBrx2UJh8P1429kOu+79QkDRg1w9Hh0IWDYQvh7HQlUweLW1NC0HhgBXmUvYzlkPlUyQEF3ZslJgXhUKPhdKUvf+Zm7kC35ZyWaafGICepWU8hAXZvXLj8FRoY3IDbNANnwb+KjFt9+pwSAnN6uXj2uhR/FMquHxuJ4Cez4rQDDHSXvOndCo4j0Ftj00ITjmVvEk6Mxarpju5bzJ5/raxbPQ5V0yAfusE23pgjOxwvrO8QGqRxDXqpCzBzIKfQxNFZZGhMWQhtLk1uUVDjCgeGdyc2LCelvZ1MG96/+h889b3T3UzbiIS12mJ4Dy1PwQcPzgAsB+AnAAL8vxeSXaTd9H5t1dGzZUjIyHflUJNkSnTeChBe+k3sxYAAMwrnMlwwwVibxJfmkODND8caPVAXd094LMPaF7S6qDzuJ3iK1yk/D9P00UOpdjHtpk6cbUxKoAFzv8mciRs2P837clBgALhA2hGXhhrpo9CEqhgZbzhjhf1dghUIwhJySVFtXM9RkBr7ws4l7uzshOKjRlMuAsF7iOmIpQKURLRUV1Hua66S/570OR6EI55eE9d3r/qrXrXnPF8bsGNuc5QEV+gWaMfmwG/40bD9wC+MlWRrNDpIE1b0C4raddSC3CnaS4tCJi/OUtmBNAokV6nplt5eHCvdJdYz6EZ6z88fYFe+yci01Gw+z0W8eFHQUjMDGpvYhwfQBcEl8aL7WnsOcrGkcWYTqEUoclMZChzQKPF/ul4tX43O1v5/GpxCbf45zZdSB19GO1kCuYWdBx60to2tdvZJKQkd6CH+KaG8bUOZG57QxiNMlcdQvEGtXQsxKtayY/YWEqYDEkADgCWAssMlDfwCzYFk4dQtB00H5/FDMtkpSxINhdCGAVk3To857d2aPsNrNz/C6wz2YtPuiUMR4euni6zlBjiGMXpOEepXKWnmJ2bG81VZ86qnzplrdmhM611lnY+/I6ob/QX/XnUw6WYP8QPTij5G6lzDmKhq8/idyY6yljbkDq7B0hrkB079s7ZnvPxZP+mOrUX6oFQITxeMe6tbR+n9+B+rFzgM0oLGxFFwvJiu7grgiAfl/c6Diu3mAnt21XCotYZbWAt+L3+eY7kr7B44TsGau7BwQRgceIr+eQkq9h7W0bxOX5uwrVOLOzDmoHJayDwCf87/qZSJy9KaeNHGiM/4PqL7yRrRMYwkW/pye+VasWLriRjQ0c7SoVQRHRJvhJRbBIkdgSinBtkNE0ZT5vr6c3VeD35NvuKrAZBjaAjiQuNaOn+iMQrn5LH5eVtLsrLOvoHo/qlzWelusU0wKfO0h/DIihrp9Rihn++KyET59N8MZO3zwvs8bH9fKkUV3XpVgphbvpPH2Jp7xwiYiIOEOsQ1vAyAL4wtVS3qaBcuxGnU1A3k8HL9aHJuuBQ+moAGPcQOax7fyu6AHgDkwC93my4wyVqehLgeCcf1J5hT6TJPSdVWjhujEX8FfwemJXBuKpiTLpekUhmGFaUWJpP8hJ8Jvj9KVBjr08Lw94ljg6ybLeIkoGp9eHC/ZmEbM+JQQV9Mi7n1188Tzxshh7jFQlWRco5YLKPgarL01LNBAMZsUtSKOMVmr9C0/JC4lXbR8wc7kkD0lSxVVYvfHi+PlyEIUSPyWYOle9olnUclQbjLGsZpNxoDGpUjmnla0sfxQK9Ktfca08ZyGwX4K++kgOYCwCH+gOCoHiCw6jHHGy4OKO0QdbHH+FXB9IKRmmhWg+Q02dHbeSUrtl8aIoxuEXyK+I5GmNlvUoJ2NbW4zEF8d+sFg7Vz7XnSPFsfYmU/6TBvkNkxu3rx5fyXRn8J2Mit2M2dYLyDmsSGi2zeFssrKAasiZXmVwKlKsNwaYo96tT6Luz8hbSHWySqKobSF3eri3k3RM/l+QYmHBZaI3rZ7ZnbwAG6WtrZejOY1rPSWCRGebU9Oc1oTxxfgzeFMq3pJxRUa9ErBqziGDTIlVImh5AvOa2sLWvgUwHb1imhwXyXTrqWPgkxHqz7P/pi7Nsppv7BR52V/ndpL62yMaDMLI+LyeNYIqp9v7owXlRjWcGFoQkFKI1MdacDYtkU20Fs3MQxmlPGQ7PHhaT7XVH2i4Ki4DdrblqPKgd7HG/jIfS6SuCtiKa7Y8rNU3iKNcwJX7EhzofyJ8S/4bB4p60oby8NAM+QGqzlZmi6vN4Ubq86zSaRmI/cQh4sjChA5Nwh08VcFpgIi+jb+ofP07Q6Aa3tXhgiRAEFSf/1fGhwFdfCB5IvlBbmaQ0c56rlMDpNG2xASOcbKfQJzWHLUlmzLCyfwzkHTnKd109i8WyWyvK2WI+hbvvRNGAzRGVaPc0K8pHtNOvL2X355rMI2xaB4xrXNoWpQDZB6wxTTspSB/NHsLXdT2Wy9Dlkklo6hva8S7zXX77KP/aSgdqoxnXubVfJyHzskjLqLJMp4KxdiAHqOJ7ShGP1VfGgQKCk36qpZHedRK5tRYbayuKppBNnEB76LIYRstIwS1JbYEUlDAsuUrcY10bNiRC+EHFTdggC0EVl51Wdi1VQp1KYPSwdG1JB1EwFpyaHSY7d+EkOeBJ/PwA/Oew1MCvpzkYrh0ffTftM3ZyagXjm2Cr0Dw/w3s/R7cAsN5GpdDfntWC3f/vFyrRIAZ9SmT8aED5Zc8gWkSKLoN+ce3PzuyoOFs2ShDoduDL+nDCRKwTT96z8UUaAhwxX61sezsEw/l1+jdWp5Bz0eFHreGj6QfHYsBorYMOiZiWiRXNwPDsukTHM0vTsELuxW0dtMIOnZa8NV+1D/U2z3odGuTGHRyc0ejLvn8EvdX7INmQ0rA60YVxgK9Ll1BldHayzJXToXhbvy8qNAlc1GUuElVN0pUHkKbqjRE8c62v12XZTZqHkPf/mU39i7lnBwDwZ73hxIQ5biGHzwUhXxufJzx5tquZDAOYBZFRdCaBBqAlbhN4ncreGUXmcQEuuMdh8EMjAAk6z7abaTOtUZRxdovDApoQ7irEQvoDC3Wg38SdW4sTBeX1gOmfR7lLZzBe9PJTwyk3YVlwPNkmDHUVm0NN+wQHDncIAACbxp8BKadHaP1zyAfWDXlBLHZEcdP0Z9SbE3lLz2Qd0WlcoqHrDQHrGhfx6/ynd8+tylgtQE7phoyqn+xfVg3LHT2pwoyfCyPAn/h9KFdVJOEcHzY32zIWYIJY00OJ1siVcO73TWLL524ghYknd11N8DYSDWOMciIyworxLoY6ZuLYcpklZ8D7Tzryuj7gIlDLj5vQdGWbmYUt9FXDbVISCd5+kmsv1f2o3aGT7MKSUcGOa7uuhecQ4n+OTymFOLZf4VxvKher7M4eusEjrsxbJicDaSF2XuBQaiNfFT3KkiGU6WCnteXf8k/mvzvsSWrEGG+qVRTo6B02NzhLaZEPmtg4Q0nuZOuMqg73pWLKYC9g3C47baDnl90wUlFyR/RZBWfejYfH0UXwm9w9Rv+WBPyZUb5SgPjnt21QafEaq14uwlGpknUkhGo9/RCwsAMBIaLocBw/4lbtP8YSsq1zLBDrOZUzarSYdR5T6I0ZgbLJFhQZCSM//dnMRfSjeioN9PKgpkDCGjGxda4dG+lzb49QIZbUR0jyCQjP7es9DjvkdoC6e1JG558Gx5NXW9JvRIaqzzrVZaWn25tr2TTZEfuWh2Wth/Lhi2LdSBbYo6+LLGrYVIEWiex+t4ThLgYl5SplRwteYqUU/FELKOLzrn5rG62HYQ3WZpmJSmYGK2iiwHPfzrl/ThvVNoi+vVN+uu0cIR455ZtXrkqAaxS3VMvIexrezm7y6TeobuEuMBNmFnhUNh/2OYvDbxbSSEkCFiRQuxYXbBq1LzoGDLMpBb5tPfrBzOxWdw5lnwjByEPUosnKJl6He99T7QFr6VE5T/VfWiuiU7c/Px2+P1IzL4Fu+vsSESvMXIExusncQcvnbu798RR0xYWJR5iv0XuDGEfaA/GQZE9kHwvGh+3bZy7VYfujK7J6kbdw7qEZ1YplOIBuYnT4S5k332fRUSeWGad0Pdkp79slL/SGikPxrnJDbgbkKtLZNzjEJPY3pgx4cgrW1u60Sw6Os+fEAppVVVvsisAqR8c0kc3bv97REM7A9wIn/wGBIIxteVENCS5XwBnO330pKVh0jWW+PpkBbqLtyIymn79s4pt3eHr16qDB0/S0LzzIEnDXjl/JAWqt0dgQcxvr84Uu6u2ClBYkCWFGLeLJ4AROGHHLxP2xRBWactTb3sj4e5AqqTGctU7V9z7dN6DqHKadSmGrNneHwgPf6NAZh4ROJLQfQuhquN/kXZ0qYpDVK46gL6t6RR9IuYPRaXiMSueUv2405Z3YbpTox2kryc8V8foZpNa5TTwy8zSnswDsJyz9mWII6gjHDUr9ToXEcFCt3KbynX9kr/nDWMc+zSCKo+TjPzUMZ9FWnv3D0lUyl9SjH+6Tker/IHj8Zw5747Fy5vaxlPzRNkwY5nSJKo/8S/52hMpxVbog9WcSNtoYH6wURF32gC3pj8pq5AHDTHdOWA5eFRmBNz3721T2S37bm0gaNY+DWlRqB3dr859uVI1z09MG1CZVa4JHgwi1
*/