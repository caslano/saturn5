/*
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

   Thanks to Nevin for his comments/help.
*/

/*
    General problem - turn a sequence of integral types into a sequence of hexadecimal characters.
    - and back.
*/

/// \file  hex.hpp
/// \brief Convert sequence of integral types into a sequence of hexadecimal
///     characters and back. Based on the MySQL functions HEX and UNHEX
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_HEXHPP
#define BOOST_ALGORITHM_HEXHPP

#include <iterator>     // for std::iterator_traits
#include <stdexcept>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/throw_exception.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>


namespace boost { namespace algorithm {

/*!
    \struct hex_decode_error
    \brief  Base exception class for all hex decoding errors
*/ /*!
    \struct non_hex_input
    \brief  Thrown when a non-hex value (0-9, A-F) encountered when decoding.
                Contains the offending character
*/ /*!
    \struct not_enough_input
    \brief  Thrown when the input sequence unexpectedly ends

*/
struct hex_decode_error : virtual boost::exception, virtual std::exception {};
struct not_enough_input : virtual hex_decode_error {};
struct non_hex_input    : virtual hex_decode_error {};
typedef boost::error_info<struct bad_char_,char> bad_char;

namespace detail {
/// \cond DOXYGEN_HIDE

    template <typename T, typename OutputIterator>
    OutputIterator encode_one ( T val, OutputIterator out, const char * hexDigits ) {
        const std::size_t num_hex_digits =  2 * sizeof ( T );
        char res [ num_hex_digits ];
        char  *p = res + num_hex_digits;
        for ( std::size_t i = 0; i < num_hex_digits; ++i, val >>= 4 )
            *--p = hexDigits [ val & 0x0F ];
        return std::copy ( res, res + num_hex_digits, out );
        }

    template <typename T>
    unsigned char hex_char_to_int ( T val ) {
        char c = static_cast<char> ( val );
        unsigned retval = 0;
        if      ( c >= '0' && c <= '9' ) retval = c - '0';
        else if ( c >= 'A' && c <= 'F' ) retval = c - 'A' + 10;
        else if ( c >= 'a' && c <= 'f' ) retval = c - 'a' + 10;
        else BOOST_THROW_EXCEPTION (non_hex_input() << bad_char (c));
        return static_cast<char>(retval);
        }

//  My own iterator_traits class.
//  It is here so that I can "reach inside" some kinds of output iterators
//      and get the type to write.
    template <typename Iterator>
    struct hex_iterator_traits {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
    };

    template<typename Container>
    struct hex_iterator_traits< std::back_insert_iterator<Container> > {
        typedef typename Container::value_type value_type;
    };

    template<typename Container>
    struct hex_iterator_traits< std::front_insert_iterator<Container> > {
        typedef typename Container::value_type value_type;
    };

    template<typename Container>
    struct hex_iterator_traits< std::insert_iterator<Container> > {
        typedef typename Container::value_type value_type;
    };

//  ostream_iterators have three template parameters.
//  The first one is the output type, the second one is the character type of
//  the underlying stream, the third is the character traits.
//      We only care about the first one.
    template<typename T, typename charType, typename traits>
    struct hex_iterator_traits< std::ostream_iterator<T, charType, traits> > {
        typedef T value_type;
    };

    template <typename Iterator>
    bool iter_end ( Iterator current, Iterator last ) { return current == last; }

    template <typename T>
    bool ptr_end ( const T* ptr, const T* /*end*/ ) { return *ptr == '\0'; }

//  What can we assume here about the inputs?
//      is std::iterator_traits<InputIterator>::value_type always 'char' ?
//  Could it be wchar_t, say? Does it matter?
//      We are assuming ASCII for the values - but what about the storage?
    template <typename InputIterator, typename OutputIterator, typename EndPred>
    typename boost::enable_if<boost::is_integral<typename hex_iterator_traits<OutputIterator>::value_type>, OutputIterator>::type
    decode_one ( InputIterator &first, InputIterator last, OutputIterator out, EndPred pred ) {
        typedef typename hex_iterator_traits<OutputIterator>::value_type T;
        T res (0);

    //  Need to make sure that we get can read that many chars here.
        for ( std::size_t i = 0; i < 2 * sizeof ( T ); ++i, ++first ) {
            if ( pred ( first, last ))
                BOOST_THROW_EXCEPTION (not_enough_input ());
            res = ( 16 * res ) + hex_char_to_int (*first);
            }

        *out = res;
        return ++out;
        }
/// \endcond
    }


/// \fn hex ( InputIterator first, InputIterator last, OutputIterator out )
/// \brief   Converts a sequence of integral types into a hexadecimal sequence of characters.
///
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename InputIterator, typename OutputIterator>
typename boost::enable_if<boost::is_integral<typename detail::hex_iterator_traits<InputIterator>::value_type>, OutputIterator>::type
hex ( InputIterator first, InputIterator last, OutputIterator out ) {
    for ( ; first != last; ++first )
        out = detail::encode_one ( *first, out, "0123456789ABCDEF" );
    return out;
    }


/// \fn hex_lower ( InputIterator first, InputIterator last, OutputIterator out )
/// \brief   Converts a sequence of integral types into a lower case hexadecimal sequence of characters.
///
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename InputIterator, typename OutputIterator>
typename boost::enable_if<boost::is_integral<typename detail::hex_iterator_traits<InputIterator>::value_type>, OutputIterator>::type
hex_lower ( InputIterator first, InputIterator last, OutputIterator out ) {
    for ( ; first != last; ++first )
        out = detail::encode_one ( *first, out, "0123456789abcdef" );
    return out;
    }


/// \fn hex ( const T *ptr, OutputIterator out )
/// \brief   Converts a sequence of integral types into a hexadecimal sequence of characters.
///
/// \param ptr      A pointer to a 0-terminated sequence of data.
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename T, typename OutputIterator>
typename boost::enable_if<boost::is_integral<T>, OutputIterator>::type
hex ( const T *ptr, OutputIterator out ) {
    while ( *ptr )
        out = detail::encode_one ( *ptr++, out, "0123456789ABCDEF" );
    return out;
    }


/// \fn hex_lower ( const T *ptr, OutputIterator out )
/// \brief   Converts a sequence of integral types into a lower case hexadecimal sequence of characters.
///
/// \param ptr      A pointer to a 0-terminated sequence of data.
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename T, typename OutputIterator>
typename boost::enable_if<boost::is_integral<T>, OutputIterator>::type
hex_lower ( const T *ptr, OutputIterator out ) {
    while ( *ptr )
        out = detail::encode_one ( *ptr++, out, "0123456789abcdef" );
    return out;
    }


/// \fn hex ( const Range &r, OutputIterator out )
/// \brief   Converts a sequence of integral types into a hexadecimal sequence of characters.
///
/// \param r        The input range
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename Range, typename OutputIterator>
typename boost::enable_if<boost::is_integral<typename detail::hex_iterator_traits<typename Range::iterator>::value_type>, OutputIterator>::type
hex ( const Range &r, OutputIterator out ) {
    return hex (boost::begin(r), boost::end(r), out);
}


/// \fn hex_lower ( const Range &r, OutputIterator out )
/// \brief   Converts a sequence of integral types into a lower case hexadecimal sequence of characters.
///
/// \param r        The input range
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename Range, typename OutputIterator>
typename boost::enable_if<boost::is_integral<typename detail::hex_iterator_traits<typename Range::iterator>::value_type>, OutputIterator>::type
hex_lower ( const Range &r, OutputIterator out ) {
    return hex_lower (boost::begin(r), boost::end(r), out);
}


/// \fn unhex ( InputIterator first, InputIterator last, OutputIterator out )
/// \brief   Converts a sequence of hexadecimal characters into a sequence of integers.
///
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename InputIterator, typename OutputIterator>
OutputIterator unhex ( InputIterator first, InputIterator last, OutputIterator out ) {
    while ( first != last )
        out = detail::decode_one ( first, last, out, detail::iter_end<InputIterator> );
    return out;
    }


/// \fn unhex ( const T *ptr, OutputIterator out )
/// \brief   Converts a sequence of hexadecimal characters into a sequence of integers.
///
/// \param ptr      A pointer to a null-terminated input sequence.
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename T, typename OutputIterator>
OutputIterator unhex ( const T *ptr, OutputIterator out ) {
//  If we run into the terminator while decoding, we will throw a
//      malformed input exception. It would be nicer to throw a 'Not enough input'
//      exception - but how much extra work would that require?
    while ( *ptr )
        out = detail::decode_one ( ptr, (const T *) NULL, out, detail::ptr_end<T> );
    return out;
    }


/// \fn OutputIterator unhex ( const Range &r, OutputIterator out )
/// \brief   Converts a sequence of hexadecimal characters into a sequence of integers.
///
/// \param r        The input range
/// \param out      An output iterator to the results into
/// \return         The updated output iterator
/// \note           Based on the MySQL function of the same name
template <typename Range, typename OutputIterator>
OutputIterator unhex ( const Range &r, OutputIterator out ) {
    return unhex (boost::begin(r), boost::end(r), out);
    }


/// \fn String hex ( const String &input )
/// \brief   Converts a sequence of integral types into a hexadecimal sequence of characters.
///
/// \param input    A container to be converted
/// \return         A container with the encoded text
template<typename String>
String hex ( const String &input ) {
    String output;
    output.reserve (input.size () * (2 * sizeof (typename String::value_type)));
    (void) hex (input, std::back_inserter (output));
    return output;
    }


/// \fn String hex_lower ( const String &input )
/// \brief   Converts a sequence of integral types into a lower case hexadecimal sequence of characters.
///
/// \param input    A container to be converted
/// \return         A container with the encoded text
template<typename String>
String hex_lower ( const String &input ) {
    String output;
    output.reserve (input.size () * (2 * sizeof (typename String::value_type)));
    (void) hex_lower (input, std::back_inserter (output));
    return output;
    }


/// \fn String unhex ( const String &input )
/// \brief   Converts a sequence of hexadecimal characters into a sequence of characters.
///
/// \param input    A container to be converted
/// \return         A container with the decoded text
template<typename String>
String unhex ( const String &input ) {
    String output;
    output.reserve (input.size () / (2 * sizeof (typename String::value_type)));
    (void) unhex (input, std::back_inserter (output));
    return output;
    }

}}

#endif // BOOST_ALGORITHM_HEXHPP

/* hex.hpp
e24vbe9dnzx9/F67fLf4zrPu6Z/UXrBfM16/vm75nn98QuD7FnMWyP+eisEfOoAAKp4AOjwbKjUbOjiWkBkxFSpFkCmneVzQjLIOSRPaOrBBkCunfVxgj8Lp3SuZ1BnEgiA6odge1RaUuyBbTuu40B7lFnR74Kogfk6VPBBvLOXd+055iveB2QhI3YJ8OZ0MQG25/t0EOeKhEAo56qGQpII4XgWE3fL6GHdSxIFx3RT6dQyiGNSRyP3QyIFh3STrwvq1DCKfqdJJpJFl0WQRC6GZAhX1CxmkKJCHgxa6cfQr5Qm/Ie9AJ3W/y5EsRkODKoJiEayQJ5+Gjgjs6zbvRtIvsWuxC7YrtPtk11AtzS7GrsYux67XxN8kr05XjkCHpAqFDp0MkQyVDJkMrQahBqUGqQY9BzEHVRZ4GHgYhB2IHZQWmBakFTjTXdGNtc667rIOty67Trdus46nX2FXVS3bJNek58bvJu8mboYwC40dGNVNtq6v/+UstFrETXmeipuMm46bkJvSCjkTKRMtEzETNRM5E10XQRdFF0kXTRdRF1UXuQGaK3AuiC2QLagxsDHINTCju7Xbs/uxG7w7pJtOv/EsrlpsnvoImReNF5EXlReZF70DoQOlA6kDrQPxBnoNag1yDRo8ED8QPygrMCtIL1AvaC1wLYgvkC+oM/Dj//i0n1kopgFyTclnSlbktAja3k8G1DX186JW1A3ISxG4vdEG5DVfPpN69FrVRHwmdkF17OOuSZvXOSK8Qbns0zWwrYmZV6NBaM+lfBDuVKcA683GQOox4KvpZOfnFsChgEOK6A3FQI3o+6xO1N/3dQPBvphdGocuGkEsPK/35zMb5eyyOPSyCOThCb3IfUMbKPalbvHsMtwa3CLpdKMIUn0pGzQ10jTophGOvc0GQexy6fSq4dC9VDWa2hSZVLOh9QYZ6vR0SOgRRWFSvQUb+xuYGykbGhsLG4znOOfa59znXufvzgXtm5sE28S1KXVpdIl0qXTJdOl0CXUpdUl1aXWJdakrkaqQq9BtEWxRbJFs0WwR1SIawy17l3qX+rh6ufpae1v7PHvrN9o3OM95z33Ogc8FzglrBLTpbRDYwtN6Q/q+bxBvoJ0r2Jfdfb5rugu8y2+S8ZL00vQS9VL1+vkAioCXgpeEl4aXiJeKl8wy3QmCHvoawhrKGtIa2hqia/hp+GnYaQR+KH54a+/KhtgGnn1Vk9yT+pPwk/KT9JP2k+CT4pPkk+aT6DK9D7UPuQ89HoIvgi+KL5Ivmi+iL6ovsi/6K8IryisSfHhIb88GIoAQMUxSeiOeICyeZCieqCSebD+e0FhcJr9QsXBa2oKuPlZTsiJ/VhG7pGJa1oLeOZZTMiN/VPHTVlxtAZ1i9LTKcNJFvo2ia0nItNJwsodEewGvol4J/4Vk4VbCk2IOSmyAojiU1HP+yyTQ/nvzbGZxqngiRWWqTwaKYSjJYFJC+TmTDOZNzIJYlFHxolKG+TWT7OZtzAKpFDLxsolkUkr5JZMSk8z7Rvso5i3MQlRJJpJf8hlLtFNpv8ftSKJOcpt3KFPSxpbmW5jnOJUqE89IOiu214lr0mSQ0cZ9kiySMhU3lTSVMJUayXfMdyy4zL8sgM6HLtiehNonMi9wqnEKcypxSnFqdgpyKnBKcqp3inKqqJNskW3RbRFoUfgfH7GNm5W8lTzMf8x/LADPBy8IyQczb68TWKSwjsf7xCoVI66VL1ZQMWk4uTmJPJkwybpPuW++j7mvsc+x774Pui+yT7pvvI+6r7LPYt5aJ+Sh4yHkoeQh5aHlIbZI2U7dTt5O703gTXEc7yKFL+GZ3z7Ju2+4j7yvtM+077gPvS+1T71vuY9t3nlVcZVx1e7E/yDwoPAg8aDxIPKg8iDzoPMg9KD0IMVJgRsPJyWWHyhtRMWUMhJAMxxPMxJePpxaPhKcTsgWlzb8N0/cti8LnFC4xnONaNSKjX5qHfznx2dPSG8/PQ56b79boE6rlbsZCXLghxsm5KC5TXgcAdlC3vK/IGgWjx5UaFaPHiJ10MajgY8LGe7ZWr+AcM/nlsSjjYkbGN7cOr94757LLcGrkEkjF1c0TD40tZWwrbS1fwHTrJxJORY/suXg3sAtlkmtNni5de9Q0MZfGV+2HXRR4hClTT03dH1B5F7jldomrEuVRZdFmEWZRZpFS58wFjeWNJYwlkwfS5+YPEK9FbGVdNF3QXpRcGF8sX2BepF0oXIxc8FyUX9Bdc9573EPdi96T3Zvco/mXu9V1ibaIdOh0yHUodQh1aHVIaZLvUZdlXCacJqMH4ufiB+PvXV9Aeae1ybho75Kw0dkG4ef1DgcMxQzIjcoN7y0VbRVtG26Zbq9u7W7jb6Fvp28lbyttqW2Pbd1fAF373wPey9zT3tvfY/rXvRU+ZT51PHk/5TTJrVK60vyFscMP27FbMttyW2PbY1t02/Rb1dtVW3bbj1fNF64XtxeAN+D34vdk9+b3qPfq92z3bvew9/L3dPfZ3uJ89LgxyFDKRR3o1RChBeLh5dThJeahVdiSAZPCpuXGlF9T9yRhC4omJQ0r6hTWKQ6TryRBC/Im5TYLzeixCPV2s/dotBJ0iaV2y90UvOg4EnyKkie1NrPu1KBQqkyoOLtq0KhAiYtDkysnpTbr4KRl5UHo/qYSESaK/zHc8qMwpilMErB1MSJccMUxnWMophlkUr91MiJYcMk28LGtYwiKaXp+dJKsqqyCoXUTImKxoWMUpRKw0kLwzjGlYo535R2qJOG3xVIlqiiURVRsUhWKBZNU0ck9g2bDyMZlzi0OAQ7FDp8cmioleYQ41DjeNuEzfzN8hqV5fJ0iqpU6NTJFP/xyebEmeGKYaxt1m2Xbbht2W26bZttPOMKh6pa2Wa5Zj13fnd5d3Fz+Vlq7MSoYbJtfeMvF6G1Iu7KC6XchdyV3DncJVZKmYqZqpkKmSqZSplquvK6yrqKuqq6CroqukoN1FyJc0lsiWxJjYmNSa6JGcOtw57Dj8PgwyHDdMaNF3G1YgtlR0q8qrwKvCq8SrxqHfIdyh2KHaodCjfUa1RrlGvU4IlvWywpKzErSS9RL2ktcS2JL5EvqTPx4zDhdrWDsESxcAGVUjNVcS5VSW1pcWlpSYtFMaYFcn1JagmrUloZ7fQnC+r6+kVR67IGpaUy3OloC/L6L6kFHtNW9RGpeS4qjjPc9WmLOsc5N8qXM7oWtvUxi2q08u2lJQ/KnZrFYNPZWIo9Fnz1nZz8PAK4xXCKEdOhWCoRM581c/tnvh4gOBdzSuNWRsuLleZNTxxgOJdzyuJWycqTlyZMI88MHaA4l3rEc8rwaPCIZFSOykvNpBzQ1EvTqpmWOU43WwRxymVUqZZCT1PVa+oUZ5bOFtdbZGhW0SmilxWVSE0XHOwfYB6kHGgcLBwwXuNca19zX3tdv7sWdG5uEWwX1ynRLdfN1S3VLdSt1M3RLdEt0K3QzdMtq1SsUqpSs5W3VbZVtFW1VVArayy1nF6aXprhmuaaaZ1unfGcrj9oP+C85r32uQa+FrgmrBfQqbKRZytNmw6Z+X5AfIB2reBc9vD5oekh8CG/RcZb0lvTW9Rb1VvWW9dbwFvBW8Jbw1vEW8VbZqXyRF5PbU1+TXlNcU11TcG19LT0tOS0DL8Yv7R1euVA7ADPuapF7ln9WfhZ+Vn6WftZ8FnxWfJZ81l0pcqnzKfIpwpP3lfeV9lX0VfVV8FXxVfJV+1V/lX5VRG+NGS65wCRJQcxykJ6MzU7LDV/KDW3JLVwPzXH2EymrlCzcFbasrJ+XNOiom5WE7uiYlbWssp5nNMio25U89PORG09nWb0rMrIzEWdjaZrRcis0sich3l7Pa+mXgX/pUXhztSTZg7aeICmOLTlc93LItDxe+tsVnHqSSJNZepZA80wtDkwS6G6nEUG6yZWQeySqElRS8O6mkV26zZWgbRimUnZaTJLpbqSRYlF5mOjYxTrFlYh6hkTiy91jBXaaRXfJ3YsUBe5rTtUS2jHS+ssrHNcSlXzZiycNdsbxLXKMwppJz5ZFFmamplamJqbWo7UOdY51l/WXdZD10HXby9CHRNZF7jUuIS5lLikuDS7BLkUuCS51LtEuVQ0SLbKtuq2CrQqtEq0arSKaFWslFZM2EzZzJ2Mn0yfTJ7MnkzMWtxaHNY91j3Wg9eB14fUgVm3NwgsFVtP4s2yWsaYadWJ1VcsGi5uLiIvJiyyHlMemx9jHmsccxy7H4MeixyTHhsfox6rHLNYtzYIeep4CnkqeUp5anmKLZW0l7UXtVd5Z3sXH0+6WOKbe9a1L/IeGx4jHysdMx07HkMfSx1TH1seY1t33lTcZNy0u/A/CjwqPEo8ajyKPKo8yjzqPAo9Kj1KcRXjTsJZitUFyjqVMmUcBtAdxNMdhlcepFYeBmfmsE2kHaR4MLU3rwraljROah1aXzV4cLW3rwqcFrtOch1qtIiNzbbucXio8aiNTbXur1zjecjx6J0W3M4+7nlfv1spS2uRuz0M8uCHPyDkKb+dejwEuUK+8n8gaBeP2VNoV4/ZJ/XQxi+Hnwg56Llaf4DwzueVxK+ImRg42Lw6f3jvncsrwaeQVS43UXRAvj91lXCtdLX/ANOunFUyNjly5eDdwCuWVaa2d3l171HQwV81WXYd9FDiEaVbNrd//UDkXeOT2iGsV5pVmZWTVZJVkFVBPzU2MTYzNjU2Rz9OP518SH0VcZX00PdA+lDwYPyw/YD6kPTmosw8sDzUP1A9cz57PIM9iz6TPZs8o3nX+5R1iHbKdOp0CnUqdUp1anWK6ZWtlVVNnU6dzuGP40/jT2JfXT+Aeed1SPiqr5Xz5dpO/Muz4demV6bXu1e71+hX6NfJV8nXaldq13NXxw9wz87PsM8yz7TP1s+43kUvlS+ZLx0v/i85HVJrFb75pxO3B49XMddyV3LXY1dj1/RX9NdVV1XXtlfPD40Prg+3D8DP4M9iP/9O4Rn9We2Z7dn1Gf5Z7pn+OdtHnK8cfwIZDFD8FcYGIthMPNiKItjCLNgGQzR4otfMwgjre+SOKHRewcSwmXUdYBHrOPJGFDwvb2Joz8oIE494ac9gC0MnSpt4bM/Eic0DgyfKKy95YmnP8IoFCqZKH4u3xxYFC5jYLDCyemJszxaGQZYBDOtjJBGxgXCUAbFJIoa9YTWgF8MChikYmzgyrp/CsA7Qj2EZydSPjRwZ1k+yKWxYC+j7bJFuJM0kyyoLKMRmilQ0LASMUDANRy304xhWKuh/Y9rBTup/lzdczIqGVYTFIlqhYDqNHRHZ12/ej2RYYt9iH2xfaP/JvqHmG/sA+xz7GPtaU1fTuLpNOQMdoyoWOnYyRjJWMmYythqGGpYaphr2HMYcVlnkYeRhFHYkdlRaZFqUVuRMf0U/1ibrpssm3KbsJt2mzSaeYYV9Vc1o01jTmluX27jboBnDLDZ2ZFQ/2aa+4Zfz0Jo+t+l5C24TbhtufW5zK6ZMxkzWTEAmSyZTJpsugy6zLqMuqy5Al0WXqQGbK3Iuii2SLaoxsjHKNTKjv7Xfs/+xH7w/pJ/OsPE8rmZg3vKIiZeVF8DLwsvEy9bB0MHcwdjB2gG4wV7DWsNcwwaPxI/Ej8qKzIrSi9SLWotci+KL5IvqjPzYT7hZbd8rbhQLk/qV8ed/pJiIYzoEx+eYmGF6BMfFxU2Q5JmLmoh+idzBpGXUNKkbNsuYIMuzFm2NvMHEZeQ0cRreS49LWh8aHN2Lj0uYYCFmI6bP0xK9jcTD5GG6YPIwvhrdS5hgyyPoSdM3uWN8wgzC9I/8IEpBnD5Bn9c5X1TaURtPX3x7EYSqy+tx8q65o7SbGfqdpLuxcV/3YrhmTn5HoSa2pqqOGqelqrtKBqOPqruGiLFxiTJrWWFLnWzFm7OixFXWUqitKa8A1pc/+C31QmRbsSRqS/w6/aD04t7BHEmqRqOAZUblrDrKwAXXARKNakCQdKh1W4I510nVW6dZOUWYOD4liRVJFEgsZ9KAi8q9lSpMlFRKZYHC8Gr5oZSjgOUamkrq8JCxdIXSXPvCP5UEK9mrkiysn5zJ0tpI+rNK+wcBc0UY0QxqQhlxtKovcew1hbkW0eq2OkxkeH3NLxSjSgn19PVxrDOINQ3ThH1fC7pE0hka2yoTY1K0CD+p0qVrUX1KUptNGt4e50vqqmowGA1Q1FXTHEMfrRgUzySu5cy3MinQ9FksH54ERVNR0eqsbivMbRHVVNeFnikpYGGZiaAeMZ0bYlXplP9iH+XMTu0+xembkG+iOvddpUZdI2ldnslypP4gtaVZtTNJFeumJn3R4bE4RtfHwrsvd3L4olRje2P54GHxAkY+dPiAA/WLJHVZ6SFz2Vl66uRwSxAcx5fR2c7ugHe9ZBsbJDcGHXMx7IEYp2mfbQ0WQ8zxC6HP7wXpDco7x0MwRtDRiOAI4IhEfYL0exF7FXopeQG9pKGbEjj8L8Bb+P8jAnqBNlVVHUulF1pTV5cupDIlt5fBLTy02P30KSniRoUuzdbQmTXScjz1YKqORAWEh3JuRjlxtETvcy/LZ7oyyY3hhcny8FSNpG0LkZnclA9Sw4c0UJcW6Mp+PkmjVOB96lskbtbeScytXsDFwR90eheDurQ/q2jwKaVr6ULRDFNJoiurJe1DH1gqaAynNZmNm7A6YZR9LlJLoiuvrCgr0WWfq+VVuVGnzQKNWdw4QyPp27vOdSOmuIEIpw0woI62nIEeKYs/TiaGlvxKpTJUIFGOrmWr1PnBxfje/KFcVJPaBqf6C44i3deikQR1KgnNHgdsc9KosUSufN75Pv3oiJ4f/ZOOOJMYR6xCjtqQ3qFlmc1RdQxGJuZRDOh0k+Mt4cO1DiXdohfyVpagDc5mtRWoEiM8KFEOIkiHPdr1Y5b5UesnN9/4qABFhW1tpbV1peUGnwDd3kWTGRjbssrNSG35FnD0VanEMf3BqoZCYuTYmtbEhumP91iN/P2tqdqHSIPvpQicP/GTkYEqZqEMCm8pxXiRkd1Pk4MyIoIqxrzjmFB5NEDn6ROhN88XqZ5xtKgPZaEnkfEpERqOiyeho22s4W1pqEUBK5BRY5u0KGEBohqhlixA/vpBcAmNfCJsqNnIvnY6zBh1m2WbwbMsQimRmVTDLiyKUbYixKO88Z2jTuFs4ieNj9AkShoKSqWf5mb9Jbv4ldZ5RiruP1QqsKE/MErMHXyhRiswy0OjKpFcsYPkm8oM1cY00HFWcbYWLRVwkYxQv0yRwSId2v8mS0HqPKTtbMai2L8HOluytuVtmFtWzeohcJ9ulGOCKv9EAZf7XSC0O5KcGFy/lCXtHfjXUm0c3RY7fUp2TGiTT0m1cddWyjxp2oTEbKyFATFpWrTRjbvzkAXXjA47fY7Ud58XoQyLIwyV2lIkLQuiqtROfNovpg9V8nWrjJ8nYhZTuqUpKEZrvID0S2bMqDVMOUACrrPZ12w8jGv3Va6P6qAwiFxa3b8vWwy5wHTt6EeYCkT4o5TR2mPaSLDIGNootxrrnH5yrie2HHFBu4NuC5Xp5e316Q0KBQn9GCoU2hNKHJoXGoGYTBBNbj8JChTp1T44F/E/IWyh
*/