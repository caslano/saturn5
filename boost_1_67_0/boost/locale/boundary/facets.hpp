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
3kBODlK9wTlygQuheCzOmzyAZqG4AxR1UQie1xCNHnmMpKjlGjfLGoxyUvFYsRI2LpXWcYKS4HwkA+L2+pey3TuFjuhc91OLoTSuPaQgrwqt+VIWsiCOuO4cVK6w9XNzux33Lyb5H111IDxXP3gZwvUYHq/qDDDFaQF3dw7+A6/F8uT2rDv7TFy51jqdwdeN62/6huVN1sFZgbraZkWGpflPu5lUrtCFuUrohqGKu4/FCD9ey5rS3fD9IOTAjgTQig3BSutbgkKJw2lkzj7c2aKw6mBdx05YwsrCaZkw2jXETGhHx+Csijd45CxD4t3ZxB2NYJ2HslB8Ha4GHotC0rSw8ARY0G1AnSvIPE9N5z0/aJfLXCNIigmEldqZrnQnYrkoOfDJ4x3Avx4ti694aF9vzaq8nWV18tOpNfuIGTuF8YdqyBa4085WjCCoCbBo5YXMC5JcdY4Fnmmvfqmz6uQV0cuT3bNb5rB9nQX86zWEURwjg9/p8QyWwV676CucTnso7DeSWlMpThSLUfn3jKmPR4sm4cGmi6fo22OuPJ/esfD6zeLqp5Yr2i6j9byrTFe4MoCPSMmmkBXXF6HhG6J1k2MpVk+wmLNYIqV47O7iiJbKW/3IGa9p9wu9jdcdpgS6YhTZcbtMV/nziQiqj2sBUwt8Zv1ESQalt/nCBrz/5n4virT9dG62kSM7DpiTSrhho8cKI0/hJApdQUHeA0AaR5JdpFKB8id+5/Mkzc3GfmAXoLdsekoH+gF5UfkubHWOhQxTgT/W19xQ97qFjwHst+cAAA282X354ct8fvy22xOqqEtr5MjUUed4jgHZ0TP6R4h8ssTDrwpGqfdVfy07/TQRf3+V3g/P6fSgGMXjXth/nn+GVudd3mCc4rBIyN3V4MGdd73hF0l950DziPhzCtvl0tKLmqtS16Gc34RhrbUAXw13gfyLV/e1zr7wFwtiSylNi1rb0rNJ/p9h+FnQzkAlyWfaCk/O9eyHe1o7NGu+Tbd02es3nYEwjbsN2g8tZaauukBmeA0KsXsfHGL06E8RsGO07K79wQTYob8e6l4mxOnXU9RCjM4sPnKWChOwy0Y/HK6/JqADBbh7NPARF/kUKFVz1KNabX3q83E3hm8Qq+hc975fmdVYfRMaY3Bb9G829vF+P6cabaUE9fCl6oqesCDzm0Jv4NFvM2Aum3tCCIhXGvPVu5eRtjw13z/7HKZN33m44GN48dzqs4IfbHqUwD4vSzBCsf7RS847yxw7xbuP84NIXAf+JlmENurBKFzLDPnBNDmGb544iqn0d4bp/jIX2vcZuxUokoDKUHU4MgQKdWq/AdFYSmM75m6vhOMhEQEuCiG1/wrkKcKh47XjT+DxGE+AMQjnuBdFLlhiQ/rJOeK1oYG0c4jUbuIYl2Ny5wHzYtLAfnmPUAPCf6zghcvgKZtBhzEjoL8BE0wlPux7QLkvgfwvvBszeiZhlLuvp/6bzjzEWIyW47+SlbFlQgwyTYXZrNwaAUfYGqNeIiNVCyciZfoE9zUOvPVq6uu8yxLHuPL6zWfP/dHo+Ny9RBwA+jUiVgjbvDRu1cirkis1rn+j8B1+MfSNOy6MLIxuoDBpheykTFRgf+NPRAICh4VeF7kSmRiPnRIZyW1coNmnz3bBUtydj7kNbMEOLItFJAu02uWgQkgODcOj9/IqonHCA2+Q8c6LVLzSA+YX+dVb7iOXm6sFvNnLXN5n2t8WK3W9X9zr+c29U71dsHk7Azzx171jJZmhAy28wZa9vd62Ni/sJiStiUtozxk7JHmzeY7b9UeVnjvn7Kp8mq+1Y54/m6tllylDJHCaXnEMCDN22C4n12auGVQrxZMFwJV4r6xYweCqgOW1jJSURfkiCv6aDenrU2qtUXYehL5txXUM0QoVNNlJuiTZYPdAVoDaBQ8lqlbDreTYROGoW1PLePzhq0uSeYfNccJL3JS1Of3NquIjZCIQ821RthdQxWBN/iBkcghB2+qCYD+fzkuEGLH2RQoIvakXum12vg5AqUpJp3DZSV8WrBgFc94fBr2/uBFoCS1vTWmApVQ6WtggCHFRbUUjKLkfN+x+Ohq92yj/Ic4/d1uTTtKZbZCicagps2qfNKHGnzvYZ84pgrUIZoMPhbCIYEU1zupTYSJZUmGY5mqbfhiadka9RwQIAARMtD8W0getdhtNvM6Uz5lP5RQ1CTDkcd8033SuPpkyXzgRo71R1+Jn7cjGAUOSkpVCLzf4rWwC1W9pVNxGMsimDMEbpOfo6fqvXdHQ2XZV7xVj0EBXg71uBHCW9aIXkkvQTexBcqcKp3OUucPYO8GSvimCzcEoNDYFHwgIhuNYv6LboxlUF2VsQr+NB3NUm4oHulWHFI8mjqZHlE7ifWMFbl0p+NFGWNfs+T+4+NzBy0p4hISOsr0JhaNjA3O/MY5aV27oDz1fFVseHamueNdKKCijup9f4OpJ3R94l4O3KYdNnzfehf0G4lvn1BBw50dpOvLdfmnKkf186Hpwzrn44j0P5iBrynutJrF/fexpc98dd8F6EXsvBP/h2s6fLX/u3MxESJxAfPo3XOhTTniOtI9Ov57l2nFZ2Bh+GfEfqBO89ZveHT/5H/4i4D2Zi4Y9dle4noyM7LNXpAL88vGPjGzwhXw7b1a5X2oyK2kfN6/Wi3b+J1j8NtUbIM3AgW0HaSvG85sEO4HExODq6lF2qyrsvRixk1Mv+3xF+VReUb5TlMQepbeno2j6kRW8aKKs0aHdPM+jiC0SkjBA6cZ6EXo7KIfcYk5ll686pDgM5YF8CKATZpifD3joDZK4Ahy3Z7J2n4Imtevgv0H4HyqChguikS7bm4mrh+yFZk9PMpvFfWv6+f0jQ139GP9ZW/ALahI1PTEJvKAr9L5otLB55y43eP0DNxJEVy7dIG418+VXxQXkVNn47jmZt+aJ3PMWliKb1eIztUQYniYwrlv6MXWGL0Zs89hr9cJH5xD1EnrtD+VuUquXx6Kkc3NemxlxjpuGb9Aij6dvvpq8E3Fr1Hi+eilFpubrfJ9Wg3+J3wdxMsB8eu9QcW1EGCRDf56Tc8btDemmxqb7rlsxt7PPlT0AoPyIJEESkyoFygJ1NWMkkBbEP6qespInARfc5BlCA281Ynl5PqzuEV7JLB8FxRfsvQyxPiACqyBBictEsjVaL1zgNtohuLkmHFtCNQikfiPD3IE7OwqkBJ3Pg40+ekwNNwQ267b6l+ZWmX5nuECefyF43R7AvQUvv/ZcM3CQK+LdRwUBd8K/9Kb/fjWOpBJ8aWk+3anaeuUOd/JwzWk3I0k9VDH5dVnTnM/YblcNccz7Fulu+4KfBUrjHdATEQIqufhsARCtVkGFqOdg/iMWNBGabLUk2zQzzvpFC73hH/F4snp67wm1rxtt5xZe/tabRTQmP9jQy265bApX8Nqdf4bVIaHNXHeC3S5/K+vBoHuXRAz3TDqreAaq3W1UdidtxY/Y74xfDevTXlobIYcEWSXKkdPWp5hFWFHWFlaFGv2IIwzUf3c1tPOffacq7rTjvVd++DUB5i/4cTy1s96+Nj9JWaJufqf7Cfa/RZnDGPpm0iLCC/q8K15nq1wNKdTMv28HK738/YkeVXuDvv6abMKQx1nSngVGxvMgB5vMxTytuq7jEriorHIg/pz3Fbtd7z07W3J9/X1AXcprhPZU/bg1e1+rhIP52WNQw/4KXPllxWtar/bcJH5KPn+W/ZIFScHOSA3wn6EuK0YHbrfwl848RHyy/vJH/W5B/eI7cfiXwQGHsl7FZDA/DfiTKtkrx9Lm+9/oDwYHeZlXESTyL+mgzcOLMUyhMRxmSNo8GCJ9JNiBVwKhEGi9yvecukBvD4W2ofTFp5+oZ/pytz0ktHJLD3sgbcqLnwIKgR0dRvAyTlosbdV1iTJvcQmIkWQQDUrhtPHwtXwPZVyuV8EsNZAhSwRRVX4GLz+mT92iUwdmqXnfPGZ4GFFXKe4bnUxAWlFM5VsMCpEuTiQkICCuaqupPopA5AhqKnYEx3XwHRrVUuZmTCytzQEgVe+KrD3uw7KMxBhMCftAAujnN306TtyyZiwylO4yHi9wKmXIW/KkubFQZGg8YiA8QQgp5Q+Qx+6HUM4l4tj2YrV7dFyQUxJV9Pi/uI1tUqj6UKHy4YQkQZICwm8iQb7n/KSIL+fDoiH8sbkaaC/c8tu3sFC5Z8kgxzM4cJlmM98TKl9x8vr8Z+NmTsvF/8qOGmKWhZY6dFpjut0HZWbckYBFudJjeuHlgeE8ux2EHRK0bCoUoHGFNgVjsgxoXIAbeLUGH/+9AiamP7oJlZRJsauTOlI3spOn0I8ulrquNbJ1ORwvW+v8LCOF58kFDLRgH1eA3wS3TDsR4uFpFEAR/J3v7+eatdGEgmn4QTPAFsnZO1J/es54IhFg6TZPxxfMWfCXs6ENpXtuNVr3E4ASeCma1jnY6qF2ugGCsrBFf2x6dmXmKnw9qdgQvMLwCwCjE/4uNf+B17YgXkS9arKdML6IS1bWvj5Q8BAtAInUOZNf+vOn76toZg/cn/Kjj2Je8KuOXnNk2ry0N2yA0F1xONmTdKWBQGkedChhY3lYZpSOIWVXy8GNtbSpGkZG9KmRTy7RI/qSd2JXJDn+lkpg7VjBOq4usX/FFGksfMXx0Hbj1t45KytIbhs4Tb44a26TjV+JV/eFQZDN5IQH+x77qIHhoBOOXDpvS7B5+LboMhFOF7CQ3n0aMnzQ5WUoJQK1/609AX7ul0FvGMcUHWXxOoqOUdF3vTrET6kWiNcaDrYb4XvElx2Qmqo+aMGvrMOsleuC+7bBV0v5cfmLh8TeVFX1L9dNvN2SCputaTDvkcL5pDC7Q3YrYUgBElkMA+rbgwYUqZEBsZwkIVW2VXee8ik8QLFu/+A3EmwgPIYuSNwCiMEvtHA6eblRq2KnyiYXKulQoXYrSB92c/DSYlm86TK03RFO7qO0snvqI3bb9VR3oDRC1wYE99I0Q0oCpiS1lny+icGCPzlWyYLP7gJhUK9ZLQhcTzAY/rZC6A9RfrForn9RNciMZPwMm9UaplqAsJa3mcSwi734J0nu2ddDQZL2aqHJ0WmX0i/Lip84UXSv13IG05bRMmWs5YlDERLTuCtbzGEu31P3vVO50HdN9Q/Zl4VuHyS+5N5r03NvEG5O7IwHCf+ncvsbYrvXf/71U7KJ6Gnku3j4lY04zk4p/t1MusLfILXlij1eHAeWd0/jgcjVjekJ6lSgPcw5SDLe177Q5sDT04YMxxnf9I8r3rVzxvJMTrQ8cLmdxwfNvzD8R3MUnkNSf2TLUGlwQNAX0CCcguRHkIRrpan5WiW9TlNkq8gWcVon2kxQiCVfc7ZqFyIRMHRapO47+Pq/uWEUv7J2fS2xmVZN0Ii2fphDA4ke0mdems5XwHRRsEiVASKKzoe2SfurRg7FZeVmCg2LWd6eekGwe/ZBkaFnD4iY2xjg2ARovujUkSsythjCkF3pcH4gS5rNYAzDE6GlGCAix6HAdDB4qUHZ6OQSLt7JHo+uf92DAT94SFchlPD4B2ce0Cb+Rnrh3lb8+I72y47iD2fsnbIDW945vyhxJLxanB03H6q2c5JL7lZwRl9KL71882IjIqOmwtwR3k2KUlb//NGcGKyMTwfD0LbBucxGHziFEeaVdIK2WDLSOnKUJUKrvI6YGBpO4D9oJhb1suVbFropbEpJF4GwHIqPDnztHZoGCngwdNT3ZzJVG8GUM3k31bmxC1/PW1aU11GO1OKoQqzCwF+D39wRiC6SPsBq9K9hMHeYJhCuQLJLmtEMn3gwv5Y/Dfru7ZnWP1mnB1RLP4H1fedfcTP3oO8ghxqim3TGvvcCKuylId+cgSTdQqQNqxl+5T4rl0fuf7WU0VBcZrmUVMyWB/J5vLLTToz9+ANhqcDpPMgW7wpfzbVQNh0kjLTZp1U1QlvTTKfQavkYeO3k/rIS/TbrcOYBNiW+wjGsxHpjEUnzS14yQ0vAei8AEgyvsw8ODHuSpEWKtldpjc5qLf5sW/CKHiwxRKxBG2n7V56CELS3HZRX7W161Fb7QhB2c/j5OqsuOywUwhaGsvtVP1fnx3NDmrBuFB2iK6VjS8QLj9B8En1w/RLxmqluMS3yf37f/xEc+DOM+AnKyBaJGYBPYBVs86Mg4vXorwADLPzTA8tqnlDvCD2DmKedjudgJGK19cEsB0x5zxt3MThZgWXtW2pwUevxmklrd0B25+HHtb4CwEOgiQKBQGARBT9feSN8AQb5PelRqikRZe+jCRFIf5jfr4K+AxucK7lgC4OGzE46bIoa3yO/AqsOygIVp4EJBnXRAAJBZFeQ6tyi35XSLDMLgjdNZ/ujew5ceBYZKFCGNG7fHP3AeRpuGZyddsWrXPDzXwmP0DjlC3oHfjO/U84ITanLd85gYLDB0NN/0YdHfQUQh/SdlBfEr668gpCP7gA7LVhdJ7EeuEoZ/qQ7gNfdXfc7GlgPshYPUCcDdb+mdr0++sHXc7Ih5zTlCe2CQFJZsBqhdXapdxbtYn48XECkRQYZzM1OFYiV0OvUi5JfY0nlLOHZ55y4Oyv/1vwYlDTG1Kgj2CztC5UUJD9BlNdAYqyAvIXZKrApXKmsQSN3NTJh6WIfkA3ofvC8vmvGQw+QQxpcTWXf9dByFLG236O28Vg5rtihMOEvpaM7n9ScvnZBouKOU2v+R8bmFqfrTfoini0gYfBa/A463CrlO+nTUT8zhtz7sEl1lN8Ka8TB73728waRs5oETwaRetZFvr+HfkrsKIbVFIWTXoAU+JJtFbeNIDuoDQabsIL5Ji6lFsLKoOPNImQ9G37+EisqryTPuppMnmWaHDpTiHWzJULQmv8gVjc8Hb/v5TB2Y6zIqo1+lYJfKb0oPcqiJLWwLybDuMxMUKyu3gYq41ty8+HBAWAyaE8SglquIo8ghpQEvGSfJ+x1Q8vaNjqvU4NRvjUssJz3JRIKkSS4BoCwlubeiPnA3LmZj3D9yYzQvzOEbeQ2atedJv8OuC5WlasN2H7z661raa2JIdvyO52JIziiWfH46bDVI1tK2AslO/YEkuRnabBfzvF6/oYhLru/3pZgC98M0YK106Ei5fZit1puPwMealCgj52/f9EyT43Vssbz/ipBn/x+fz0dylQ3/hgCTeaN9YKPo8FUM5geFxJsBAjRJrYJ4oyirkjYq7XA3VNNZrZHZIsShbEgYI+HrhKF8IJwDRtyVaSFa4KtbYxybrKDUxX72YnQbE+dUgT4IgSIiNikKJbPcTmojX2OGrNuFkRc1nEn1+mA2sDoj4ruMPizvvDLyo5cDQ2nzAxZYi8j2sXoR8+71lDXQ7XfU4R0rUVGVEw/YgY+WYxbC1dD/VAcu/uexyVHv9cVffTKX92d0qspdoJOrf90s+1OH198ef4NZYJxKim55nG2rlUUKYyXDraGdToRLpwWe5m/Hp+jFLxF0Jc/ilm6k35YRnMFf1pvouUZYH1bNCaubM80wswVwyHGzwZSoE0kzAf2FfKdtPrs0OJ+8GMbR8ZjhT+birfjiMPJuy0zZTL87vuD6wn/uD3BPRvjxtKVZt+aoOPJNuhKpaDEQRjzpApJAJEuEaOZ4dzYTXvdkPjSYslTPenXdu5Vr+ueJzoSNrR6ntCbAmA1kv8mCfLF4UU8QGd6brvZpUElqIBUWRTjHVI92zVfijdn1BxHAbphTdyT4voet84Ga6IhecYEAHFOiwTBgYDJ+2X98lnQ5XYm8MppzuxQVP2FG+cyRW2BltE0JzSxhswGNG2zS0SnkYTyFe/PPnEWlQ5UcnIdyhtbDwncM3SOa5rKFeiopkgmHVwwMEvb9GuBd/mL1ia+Tb0VLJLt8RPzjXWuzIh7AV8OzVjwzUhy7LasX5qUj/p9f0P3o1A472mbh9/oxgGfN0HtmdD/OgfwPatcJfbDJ7+kgfDjT+3+UamTnVWXW+8I29411Ic+HNQ20t/HzLYnHc1D3dOsXHN8W1zO+v4jUmv9NF84b/WNf8Jt8BXYdDaL/wuty/OK1x/x9XPfU5lkjfvoRQyeOpKs2UxqyBin1E9SFShb65NJ5rCJY3PniEmnsTcOu/x5f7YRKkq+Aw8zqtRRJei0ZIR1pdjk2z/z0Ui6vNZkPp7rMKpRU4XnghHgHoD0z+B0RXq23tvaITYMw+/9y4h15ZPLZe8o/jWYPx3UVT3AFfSMurmokigmtECp3CqSHygyerLV+T+Je5tQP3d+8NjNK2PFojd4nNXGcEX1za89ehIPPeFoyjKql1L8UUR1CaDgi8h8onBACiI2g82ylpePZqMOJ3WezkktD5CTTF0VuBrAEXgiIasJ5ZR/PLVJU/X/XXEqxag7EXWIWK+x0b61ifNuRh36UZke0mW4q4vlZPTa0tHf0+KhPH6BBo4hC7NWq0xChFjWkn0ljzpsmdzOgaMp+Nk1bYvQ71Wf0EcRMwc+W0lfNGhFJAdPu/u9+20Jd3Hw18lzSHxoDT1QKLwUXmpqsxH8Hs+DIfyEX0o9Kl8hW5sieklBd+n1e5fDySbcreh3Xqv0euOB7RzT48NuNGrBTQGQBji9yNE9KzGE2bbRp25ioH8NHaUiG7p3IZCkemglR6Ipbu4umQNeuEIP8eF0WZ9hos12B3rznP4YfpoEibJThQIe3L/3jO4cCnciLMSPf2DQFi2eUswVjITRCMjjNnhN+ZFWCTWOZgLZOrUN25gxH+YuIStVpFTLyXFTT+by37A9/bx5NmAp/dO6AsRAkhjVMLf2a0xdRMTIRYT1+JJLYKN7k3BJzVtkd4C9nKfGw4KMwYrAq98VGk+uelCeVDOXyalMZgaY01dIpJCP6vWlHbRjrEqxx/wPzYqBp0E0yldzOtlGF8DKml7Uog2EewQbw2iPDfFJgguRShKdFfgC7tcFELFLFWqhztTNj8XZpyO7/p5ARdAJPt/01Z3yUeGqVk1viU8+7zVrpkWvniCNnGi7uICx7Nh3tz6DvZkebU4q6PEWUFWnEmpG7333ZUoFSEhaJ/YUEpooXKCtq3wIo01qqzJ/0QYAg7ncs4PAbruOKsEKP8vQqsKCD94hhqEdZ+qSBuXpIxbq7IhK4qC/A3W4VQQ62Vq98+73JYLEAxU=
*/