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
sh/jhJJ5ZwxAsmukc/Io2cWczOMf1BshLDBZ0RgDwDYgOGyqov1Lr6r8j/iZ89GUt5jXoOESL0DD/QVBZuRfTBBGnv2WMPJ+wsiXbbYYed8mGyMv65GZYFnxZO7e3alipMw327dw7nqpZXrYkre2sX8y4I8CfG2SDlWvjhIJ/EID/t6dXcM/3oC/fCfhX9Qp/t4G/JuPs3JWEkPWJs0wErbOsm39N0v6+yV9ejipGEkNLGcIFjD6PvaCHFD/R/ChQ96SoUk49KGv85z3k79gLlNX4s+3YEvgQpXnIy+r2Dyn6z2fBAFsqU2adr5kySsT+pQPpJchMjIyKdbzTFy6Emp2eO6t0WoObU406r9J6k/yoHCS63yj7h33v8CDT04CrP43Ihtpol3juLydpK+w0vei9DOYjJ5FUkHyZGskbezfjPLOfKJr9JRkwJc+QRlVWug7tP9sEPhZG7qG/3cGvLqB8Gd1ir/CgJ/8adfw+w34/E8J/+NjO8Pf04BPbuwa/u1vCvxGnfBP7hT/swZ84M2u4V9owB+NJ2hkjA3/gfR/JRVZMWTuRBp9MUXIDe+nQkpxKlZZZ2A4TOzGt9zoM39Dn+sB/Y8xwjV3kOphrKIbs9I/EIoGxKgHcUGFlH/5Rin/7c8zvxvdWfvcZ8CPBXw46RXA1yb91Z6qQ/vg2qTfG3A19v438F0TH2g/taNr0/8G/FAeWJMAKokusifqkr1ybdL+UUZ52vTPk2/IKOYOGgnU+t43rA4abHTOixnSOZuXmJ1z4mjpnLI3ZFGW2cLUjte6ybVOZClr2ZTaEpfFxLvcb3Z7BHOOjb0u6/khdJ8GZs45G6xJtPF92yTqzpDd0Gs7Op8/7fgfaYX/uDj+sB3/4+mC//ou4K9Neu882yRW0/b7MnyX3n3JeKtpz/5NyoaCoV9+8EK+i0tyHmqqFz8ivveTpSwwEcjtusmbif9R1NWwdfNF1ONhtrgbtbTUfZOg7otANuI3c/zILOWF4ZSwaRV9uSeXCzQyVz/uMWopRfS3/5JuW86cbTck71zfx7R/Mwt2M+zfPgtMaZi/w4ntu7iZhqWZZ8E/Evil/BqyNutJ1mZt7G75eCTJwb632L+cKKlvpW5JQMnzfkrlL2rw3LWaCz4qlyy/nHdxraASfmT/1ATV8QgFG/9hpmaRqHE30pGwHaLG+XtaJuQfV1LB169EQ7wwVVxB/w7xbC69Rv9yMS0aSrNI7jAZhqnZTTf48XoNilZ+Bd5mjSS7CBOpF4mnMtKJhHQOI71IkI6OI10iSN18yxGQepuOUWW93sZAJDw4bpV4+Ow+uvoz/SMUrONu9TxHt+wMTXo2laqyqUIlSf3QpMcQrDgL74lDkx6k93y65eiap8WJAzybkIKz8gIRAt0/ij7kq8D0En23XNHFhs49P0pLS4B0yu7/eQSO0xIDseqSob7EWMWxgVBzUkVTmRZd6hJcnLpxUh1ZWESBIge5Hzi9u530sx8x08/7IK2T9C5Jn2RP/1atmd7XafqUdtJ/+7CZfpo7M6FL9U9uUX/kDwIbjsSAp3shYB/uBjwMvt0VO9vA3/Hw7u/pfrSD/VXxMHljDVNXkEQ+Y2C7mUbDCX4Vz80qwwt8xidA/pwb5DuSfLSdvZ2GdpDc51JEPt+WBKFuEH4Ic8VrfIE4D47bfU7EXaz8eLVTeyX2WaisMQ/A8k+yuTsUl/Xb+LmJ/OzoYiVCpXpGPBrSGSDFjKY31Ga1lKjpGTF4HkgIaOIgi43RPg0Voqv6pR6r6eMu8VFlVkVt5W/vRuy+YK6x5FAMmIptZ31VbMpz4WtmPdUT29QziwyAtG0oB1oaR/RhrudX8L+fuZQ=
*/