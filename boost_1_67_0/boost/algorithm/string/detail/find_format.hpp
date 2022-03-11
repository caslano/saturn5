//  Boost string_algo library find_format.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
// 
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_DETAIL_HPP
#define BOOST_STRING_FIND_FORMAT_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator.hpp>
#include <boost/algorithm/string/detail/find_format_store.hpp>
#include <boost/algorithm/string/detail/replace_storage.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

// find_format_copy (iterator variant) implementation -------------------------------//

           template< 
                typename OutputIteratorT,
                typename InputT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline OutputIteratorT find_format_copy_impl2(
                OutputIteratorT Output,
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult )
            {       
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Match not found - return original sequence
                    Output = std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                    return Output;
                }

                // Copy the beginning of the sequence
                Output = std::copy( ::boost::begin(Input), ::boost::begin(M), Output );
                // Format find result
                // Copy formatted result
                Output = std::copy( ::boost::begin(M.format_result()), ::boost::end(M.format_result()), Output );
                // Copy the rest of the sequence
                Output = std::copy( M.end(), ::boost::end(Input), Output );

                return Output;
            }

            template< 
                typename OutputIteratorT,
                typename InputT,
                typename FormatterT,
                typename FindResultT >
            inline OutputIteratorT find_format_copy_impl(
                OutputIteratorT Output,
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult )
            {   
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_copy_impl2( 
                        Output,
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                }
            }

 
// find_format_copy implementation --------------------------------------------------//

           template< 
                typename InputT, 
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline InputT find_format_copy_impl2(
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Match not found - return original sequence
                    return InputT( Input );
                }

                InputT Output;
                // Copy the beginning of the sequence
                boost::algorithm::detail::insert( Output, ::boost::end(Output), ::boost::begin(Input), M.begin() );
                // Copy formatted result
                boost::algorithm::detail::insert( Output, ::boost::end(Output), M.format_result() );
                // Copy the rest of the sequence
                boost::algorithm::detail::insert( Output, ::boost::end(Output), M.end(), ::boost::end(Input) );

                return Output;
            }

            template< 
                typename InputT, 
                typename FormatterT,
                typename FindResultT >
            inline InputT find_format_copy_impl(
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_copy_impl2(
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return Input;
                }
            }

 // replace implementation ----------------------------------------------------//
        
            template<
                typename InputT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline void find_format_impl2( 
                InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Search not found - return original sequence
                    return;
                }

                // Replace match
                ::boost::algorithm::detail::replace( Input, M.begin(), M.end(), M.format_result() );
            }

            template<
                typename InputT,
                typename FormatterT,
                typename FindResultT >
            inline void find_format_impl( 
                InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    ::boost::algorithm::detail::find_format_impl2(
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                }
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FIND_FORMAT_DETAIL_HPP

/* find_format.hpp
T8jlf3XfV4LoIXiqHw1c02SqAvDmCFbjuvZR2HDLN3GTyyiJZB9ykY1wO7wTHYX+sjITMCo7O+KVKzsk86nc7ACoEZP2QOAU84UEGi1tq3n3U9byAT8EWGovguZW9uKjaVJ3DEWX9998ctFlxDCKZA9L+TkS4ZGkIvJiRU1wRVzAT0OCf8BHQ0RrwMmD+glMnRDvl2UsaFmfe7agvut1GTCYs4TcQAzn6lEebE9zrWOAtpQFF18Y38nbNwS/5qwcKN/YjBfPescipJeerxQ/ILALS0Bhm5yV9refKgI5ZRZgMYZ0BN0akwnyPWU58CRdW7/ieNvz96yu94AyY7i4vj3GsThJMZL0R9HRTDLhFeN9BvSlGKeMNMcGBYrVakKxaya8kqrQ5INCtqLGr3NAZhgBn/oAfeQsXLlTRBhAWYt2v2cea+VkgtM4Uj0RByPQbAx4xBk/oM1AuYsEmD5aUAy4zSJEOnjwWnnYWGPJYikhtIEpnXBdphe5OcR5ALDZPXXAkXm4Y8CauX3KpgPifVi1EhgRE/xH4LwxOE9NGGoQqerSHrdQZ146rk/L+48U++agNjnWZwsRDxx+oHtKNF7U+2vR11wSfsN25H9g6dpKNYJTopMyPNk/cdLuCA5K4PysOVKuNhpKPm0zYr4npHJDD3GMwDNytnZjN1z07edW1OAlN/7AKNw7/YKK5E3R9S2E+G4DSsgjQZq9ajvgjvPFPqioRZL+Xa/wht80VXrxUqspPZh8bA5B0OQEGEvzVm4F+YMwHulpBGHIhe7NrF1kV6hZ1BaRQvUcv62dpZwIz4TSTIbEg0TF9p1+/oalqyS8665Y0ArAx5MYjObSRogE9fzxt25lijjBv1SS66i49hKkG6w2kpUSNVsu/xUvyXYtMxcXyhKLbFjX29QHgCOhMAPz9e75R20oXBHxM9sPDSYNOD3B97xaIG6Z9PZ4ni2LVR3h9uuyotIVdw3q2xJaFC7YJQMzkM4wEASaV3SGhGc/NLJ0DxVkJ6jiMI/kpCGhgQFtmLHw6qVvwsVINsPQr8XXtZzUxXb/k5iT2oTDg/jdk0lpdqbfg/yyZdM9ZL8IFniitLc33ajoNr/VxCo48JQ85F1fNGy3BT4Th8ZS6yAz6V79tL1UH4X5GUy8Y7b1/elNRj8AS7BbGxcZk+YAVUttx/WNss9pESAoP9RZIzGptyNp2xi+k/uo8PWZPGTt6zw/VXxfLIpIeJo0BqRX3d67WhSF4iCwrEjGWg9zljh5s/0WzOwx1bWtYsDWe7hjV0YIK3Q3OZQu2S5dHuprStaXiEuh1cslKpOSYVoaFAxaFNKSdRoerBa2IhHNR2hgfqK+9DaMfaLvBee32X170qXYVTrfdbjjXoWA6OFTSY5qx4Rux4y6CYS+CYy60Voo+VdOlQ3w8zTdSue72jtTX3uHxVgirYCmLyW26aMZkFt00/LZMmQYJo09ZGv1C8f7NUL6uzdpe8U1tPLlv4v+BvdrcPO7d6hvxCG0fHWpj8wo1EyDQt/WmCadALy9qT3lw8a8D8a55PwDliuo3eh7x7MEg53xz5t9ieUt1JfhlsAqCa43YRqeVSGj4vWIRq8J148lKHpSLMnrgbVgBjeSBuI2EloZcAr3UiVlgnUAl2o8tVfVHPwTI0yXYgF3khYidjRWl2IY1/Jxl9xP97zX4x8zUbydL8+/Z7yRC0Dv3ztZo9/QeI9/93x7cAHiZnCIrd6kbmkyiGwQZCH5neGVG0iDD+AbrOBOGiZ+LRvAnDjYJBbytNpe5SdbSbFSWbuZdv4/4llkjjYZd1hfk7dX8QSGu+wimZvg1am4BdPPwSuZeGQxYNLUJ9nEMXzOL/Bf9GdKlJTy6aq7rMKZkzSWu23UlPauO1gzcZqeHX46/WOLRy7/LiGMedfZYIMnJcVGGKw/soq9l26P6nYeRvjBKZ9WCjNtnxi49Sbu3szin2aVrV+i2cMPz8KHB6OH7kn0IUzOv4dL6o+KxUHRKrAFdqt8bwqygoYMZ0XhDuPp1MDA4vQ7qJ3HlW72g8K/qQoezRxsct/vEQMqDDY/++24qYLXRBOCI7HWwCrDL3skG/DPXzMVzCJyictBc7edUdAtl1iofsRSRslP5nn8topYT3iRM57ik0enTualvewi24KCU9S/VdkBK8hRnmwBBVqjXDdOA4C/O5WL37dosxxJBppdCTNSlXrF7uO6+uD6MmIbi131ImEzIzw7ULYWSCpQib4LhOIMXWmXGx/NGax5HbqDXCPIi97ja4CxHz2FFXth8AZlHV/5z5g0HA7Om5rnHU1li/numiuzyosNBMmPxU1wtFeNFIyy3YQ5PxNS09BxRhxP+ejEUo9ukZFfcJOtT0GLG/u2Y2MOR013zzFevJls15/2IESZYnlzDM3k6K/L52v/SzilpCIZsHVMrbjQNakHGsVdi1U7VoRRkD54vCm2EdrlKorTsPovPceTaRHQXiRpI72spUmw7Pm1vvUhZ5DTAUeZJlvyGWtCOcdnFf47gfRXCzK3md7AuUHos7Z7/KBb66S115YzUS8IbMxJ836l8RnRZ5W0VwztqlL6g6lgyJtsU113U/Yde+vcTdQ303E1tvG/IA1/mojk1yHRfdzYmY9od8CF/xauesQT18t7KJHsF2bEYuvxw7MLuUXOueDRaaOddnnWeNa41zC7+6A64YYhhiEe1VdvfNptdrQxJC5+sxhGZ4075nhV4u5XYk9ePZPVwqR2BnK9E/r+gY1cExuohx8OU34GEpuPxPQNkuBV5y8Rj7L6iK+rKJ+mW/lCqJ/+qz1mHc1GLav6vbc9H8Yvzn6DyKO2IiA3I8PR8ESH3GpPLOc5p+6uCx2IobfhgmrYVzwD5s9ygeTbEYw/mKfsH4mpRzrcTRaGyoQEGrXRN6l/xd2njUV4ZV8VVBVcbaaKTYUbG7MCAhKZ2hEpstCkhgArX8JRygfMLcAmcw0y/89D0JDH4s69I1kKmsT+g4M7UWayx8gTyQnVMTA5BECJeTQCTHSifGGGVHiqWytFl4MVOh2wcyccLzi2TgLqLUSiMgAU6mTC5W00sMhlzt2/B5LIbAdH/ITJ/itC8l+w+6trzwl+ysm8nGsIpP10RG3owLZ30O+XK8rBGsr0Z6RUMeLwC8rVwWWERk6413QhY7Nn9uP5ZCH19OqEzest5cJ3I0SUYylVucQJG8hq/zWPJZxsU4X1YCneB55GbXox79RXhFQGVPS0GitoQO5Cc6IN+BICjP57s04OVktwMREAH7gXLjqvzfODvmWUaItP+2a754yHKiJplWN2La+Udh1ugufR+hxndBiEedcExPuGs+W1+qYeqiKC6wE6UCq0nkz8br+76BdgfG3ZGg5j+3l3oDPflsVTo8k8Wm6z4elYR787cn2e3VJX4kaz3RaOw/dgBaNe9befNInetHJ9qWEeKGIZ2iemPJIxijkIzB5kHqd+GZI1mjViNdKzS08II2gLNc27fW32NpnzuAtdbn4iNOzkf0ceP9qYNwAcVxy664fDjdFF0iOzDS4NjKKdfJGfCTV6KtVcpg9FZP0+gBCSumBjwfbdup4YK2nLAJ0TDNMOA2DeygmHO22+mHCzTsBmoKuFfMnCL7ZAfrc8MFbhnuDODoBVZoqiid6rJu7FXq0RC96cshYrerrqTLdDRimjjtIL39XRL6ctFFv+wT0/+Mjfh+uI8aNKJd89W+3Th07vuK5YFjf14P+NTd17kX695mP2bWc4MESN2DFzf3dKME+FG/0X3zpck5AWsu/N3/2ffcwzVQlp3zBOkWSwsOwa1W4qj5HhUl9Vdblry/bel/J/pUqORWH1MSypRIi3WVbigxnNrM767Iv8hOAL5bF6BNIpIiF+RYHgPzqtA7vZkXSAIBy0TUWNMGUJuZhIjBTyEqaPhyuoQ1PFasxe+6cN4gwYNXb4ST8ZpVWz3zTrDmvY5ZtxKaWr0cpQqM0KtTRSwN3MCj0Be3nUARidDwgSxOUVtZM5PfMywmbuaMo30Z8Irt4untoxdD2q0QnspaKCCB9kIP5MOJ2W5CUv0MB3RW8eKXpsHRS9JW96cL9ZeuK7VpT6qocv7mopARFHzL8OQarpxZEWMbjfT3n/UXBKFsjZ1qI/W3DIF2TZ2kIJr+XU5MFQMaYVWxxAS+RkslgjwkXKA9RINTMzeGD2RZARRNhhEb9z3LrlDzgY/QufQ37GhT92+2Sm7tYsdP7YdtD6l758AxjxlkJFna9pm728MGz1bvmv/auOaaF1eyJjOaSQVZpckFyYXBucMEk9UytTJVMjUx9UF10nbJXvla9X6KLwfh7TrCbvZG5EJtrm+YZt22NbZbtim3S7D/vmfioxKjEpOP4y3vLtmfyc/nzsuF1KTrWUMeA0GhWBERWjszp8icsVUqLPa9RI38eA17kHECvQuQ9VD6aOQg3PCkYFFMu/uf9Ez/kOqw43oFK0LjSZIV2IrKUoiOSCYnX2SHYWC5qvG5mKWAEk089fTzJID04XzjVWjl2SfVbcYQ+cqeu/dpeZoBbRxELpuQIzXWYEzLCTQg41PNj1lx1e/pwr57wjW5Qboj4Nf2bdRR4JRZOdDtTw7vF9HNnSBcCUklmzNhXWdOpH8VGsK5S38OO5M2/njTdncnvhQSm4Qv/5fjP9J1ZmVifWdR4OnnWe9n31fY79dddDdt9kuoTG0bWpYUS3Tac2SSzTpVeft/Smx/HSYzQWmdoO5IfedPps+gw3Jn1GfVKztH6uDJkkGY4C3oJG61bpFusumgaYDZ+O6sZvh81rLbvyjojrIFt/0/1jgSNjLpXlgp2wzZbEQ1U5oDLEJKgEYdEgCxBiTYLjWcV/9XkOcqRlKE/V/U3W+ufKbrcKjdLuyenAcN4eVgYhoLr2j095kZ6JZ4zdTlNHNdW56GeVPSGO9gNPt9pk6JEI8uXjtqz3mBUSAr8dq8nEIvV8Hyc/V3z3dPHz+lUyjJgf9SyuLbGXusSFNLYw1QtslL/9394uMV9sRja2v+s5mvajTrs1VBLEabzU9ZpEv1XvV5bfA9Nf00MU3iNQggSKBET5bAKkAibNIc21ltGW0tOUqD10X2plamVJX7TvggvvUbloaV7Ho15473ko7P9tZgvJ7y7sCuIl4UkOlD5+Ix8ni5kqZZbZSvFhZNuI8zdYCUs1iAxNmCAYIvz3j/JVpwM09p3uQMbDVjrFcPh6VNvaIYT6grGCfHs09VKjAn2bjL87IyUIDjPj81ipsPi3AseXrLLV5FH3O/t4F7OuE//cGCk/MCNwNRBSE1gzI9XtESJVRt/WmjGE3tBFTQnW7Ofn9wXpxT+09r8zo/w5XSTYmefiUFxA4ob0uXwIJiyyC85R757vCe9X73DJX8kDyW5Jf8lZSZHfmM2Mza/Nm82xzQGX5WZIu/F6ez3jsa3WXVBH0F6yU1JfqGmI75rsx5zLDdttuK3eHdU24ralrqMep56iHubOpC7oLuJu5jZki/HGA3M509dbCBXEwoXMyB3TbB8aEd4aGWKd+4PKTBsk4Wa1aJeZpMCdJ8tu9d57im3zyBK0nIuGxRUxNEeorIsBaP+5gjNtXLnGkGBv560vy1fGexAoNH8TRajXi9rHkpvjaSh8hrWuh/5Xa7K2YEfnga/MQMbfYD20d5NLwjGb5eOvakm1xi236vZgxHisDYHIse/gvlhJByqWxgtcCBJ174/bISbZzAapXsWOD6VekAXyBcoOUbbGjEujoyTOm3RLIyX43xj7a0uf+qrjdFJ9ft2v59e8SxWm/YYMU4t/pUHMeLrFDea6yaGmXUNY6sdbjGeuZuE7AYlQpw01piHnsU6rIybnx67LlWwX7ceHUHSZd9QS0pIgJ0+nvsyLypkqMwrLZNT2uJhgcy5H6t8V5pBaOl7txqj/tuL1WZQOqdVFe4tOCXb0bc797Qfc9HcM97YPRg1GB0YJRxFHa0/Oa85rDglnym4fYluy6Lzmz+Q2ck5LRNJPveRGQrQ0D+AERfwHVzKbn6fEI69cOfYFV02nJHdh22uFbnl3Y/2uPTFRlpeWllBa+zTVNCdeeHi7FWihCcu1bgexPFD7ARGiYOttFcefi1sf/EJTAtxVaOBcEJi5ZdlelLImeUJ//5E8tMJmjpbTLkn0KpJ4MT+u33JYcEyWdj8SO/Pa8AhaeeSod8J4d2ONNVVqH4EqPnOHSPvwiLcG4ZE440HrsAOJi+h0GZOMPN8wSD14E6Xx+9hgPQnfsCChmZec0H+2zLdLyhVkUSC9tkrd6D9YXz82OobmuXFMHHJvUsqHJ1zz+tbCFWRNzRQ11z6+M56L48CxZZAYbxrzgXJIk0iM+zzdfxN2vwfXN17Xah36Rp73ClNS3PZiozlfMWz3dKj+d1OZPDnVAnFTbvRRmfl+SfNWKaHz4CpMCE12ev7ao+MAkrn1sHO5c7GtsV2xk7EFlNrNI1RNgjAAzhAELgB0XxH8E3QT9BKU017jYr8f12O8b6iA8tm/oNjEjANmLkGthXy8CX/ezwADLPzTIM4GcY/Dap9nPMKVdlcemf8fZLLxAnj2SHACxQnW17bA4Q7ZaSQPf2mgNkxh6aUPwuj4o0BzupD15jDFmqoWdpeQNfFq8CpOmXm6IlzIf/E1+AEt5IgtUxiYVCz5Do0UPTydIW1edGhyz1w2BKXiH1u1QIHDgS+BmoFHgSWaG5pdqmsEFNrfKzLNziaSN7hPBHM1uuBgtx8rJP0pW4WvU9GgkcehBaoLrvL6QZP80LSaeLoUl4TFqqFGsomQ+NEWKNzsD1FAgboXUBKmYDkY+qdjPZJeMzVdcbIcGK2FXTbS6lin6nMEOkacaOLGqK/ui4DxuG3NqEKcz64tvraP68gJYhgpGOV6gZ5YIs5AcOHMzeng7XJnyH8D9cwGFCtkxF3rS+KJD9TrsXl4PvMqPWMMT8kr+0qZyh7LCJfqwboEO9hZCZhSVTS0UiR/l/5kEkC77SvnYwHxfrigRIr7DFAvY6Qmzrj4q0Ju5DdtYi4Ooc/8T/b/9gNjGKh2sgn8vXuZj/t5YoywQgM/bHt7GFop9mELaWi7texvz0PYwBBzqKYTTX861alQetJZLK9XOyWT/etu8Ol3HxkWZq8W9zyBQMfhQiaUnblX3JkdYDudfddYEs6OsmF9c+Idzyf9Zhcp25yNZyVehJxDRqckcbBcR4D1EnhcJmJ6fwOVOjpx5CDI2QeoJvL3+q1MAd87uXfF10fJR+XzXXkXiSAErMtC5jdyT/kop6u8Yr/Q8J92UPXROFJ0tEVVG0azwUYJHsPmE2NGxQICgy+eOxoH1E6KS/LmD2wf4L4ft+hbxNs7l6HyZzLT5zdmNo9Tgp1Rb28mqdaTn+ts80t9E/KmRCf1vxjyfmOzB6/cr8K07kuoVZZpmqqb/CjLWdfyYzQrNu82BrkgSp/Bb2wGxo5g37yRBM98WBaeUUt/fMy6AETJkyMEd6FUz06MBQ/qBiWPuKr7dVnVzBrNFd9WEfMzCUJg7HPg27HailNuG8A1vkysTgueZYeDWZdzUrIHG2Mnlxrp9hgJdeGYSNl3I/UMZXg/2wP+nZaLSbxFMOYOgbAE4cusE26oM+Qz/We4DaG5DHtDxBb546lmciKQEdA9/y8/sE+5rXOobNj+2o5bRP4dkPR2eF1BIe6gFRssaDqdQqCmTw8jnxyKbq+38NPqCiK2kuh9HLkDmzLx+NeLNRlHIfOhtfV2/0KtxF+8sDUWhBE4NrtQ7uiO1U2uQazeZe88a8nsrQKAzDipM9NAfAbo7sMR65tZfja2DbtgN04Z++0+PLWXNj/LMluZDrbk0xzX3xRABTZ22uQNyuNMarFAYth0HPvZKfjqycQDiQq6bQx+wttnPcFQRIbC+XM0s/WiGX80YEJetNYTPlrrAmjDscQSdKtFhRxuNNegFZO0Bgrcx+JDaE/V3npfRuidhi53+8qT/iMR5hTTU9U8Y2kGQNn2rud5k76+AY0R412Ci6nRk5BZHyr+Mvbt9f6/yDbEKRkOa/TQ0Nza3CA4wGHTDcgfuUFrdEcB11Sl7nSbY22OYLWr5HQygxPrMCqsHlS7VRGo/PqUJ2TI+tPicDaLTo2GJugCz6zCEd8f1t3HPpSnHMY17bU3l1rH7gL1rc4bE99ST8r09xL7f2pI90aW6ebm3fwMYeD3BnfNQI627+eSqbuEehpSa6l2PyfQlkD5z2U5Ez/2+qfKPV6Uw/uMcgkzWRjnFv+25+gq1/YHrtUURSLt0D4dP9NNW50PNKrqZwlPmDxXA0tWqJJb0ti7PkUq2OUlihjHxQHabN6HabGF46OgKz7n5089QhXZEKSsINuo0Nl22TUfuEfOW/SKyWDZ6hy5ncY2ypuLdS/YkSvOpzMlUrYSeutBGiGsWUIRN6Cx86iCywd/oXYJ1+5YcyiMy8hzFHdPSWbI//uYbbsGfPWrDaskdcUEDk4IJqQl6z03m/eRZcb0GsdB+VRzzSFeXGU01pyhnh5ZlPELb/F023mBqB1aSulhUej362RO+k90lsHO5fNO3TOCT/39rtu9TYo7ZBhvUst+AUq37F+8OpfLy5T/+QBvfVtBuAVknagnrPC8U42Yl6gidTI7WxCL2Wzml+qSJ0H2rHd4lTSpsOf3nIW0iRTJfia3ehOk98mDpaXIuXLLbogRZT8M9vPVFwde6oaHNUwNd+KHQJJySkIfjT/gepAI8bKpk/s2gxUiQqTP74RWb0mdUwigkBg7y6cObxYXw09bWNSuylNKFN1iU8xk7Pd31Je53/ymx5yTRk4JoIP+k018Hi3FlgUoLbiJjcddLxD9404jtEwrhKFsnRyZIP4MvEwnKDIKsulLhOGIF4bpz9isZCYCwCCTc5GmVYT37Wk0yadXZHZz1qLxwbiSQBaNpbTVLND69jPT99g5SUT/vxkSmHCEB2FaBOl6IM1fMoqVBQPxDg/wa8w9YEvOLNnJzhg95matZ0t8I0SdiCdIH/IsHJV0/YU0+CT5fTVuPUkObLZqIu2vtQa+L79TTHQiHzp3j+ji56gDTcpjqbBAbOuNzivlhGMWgx9BXzBaDS9eZFxGI8G3xAJWlyqRbj7s1ZNxcVGbAlxC7yo5Uq7WiGJ0m1hieVlSqmOR97E=
*/