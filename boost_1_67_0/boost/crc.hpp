//  Boost CRC library crc.hpp header file  -----------------------------------//

//  Copyright 2001, 2004, 2011 Daryle Walker.
//  Distributed under the Boost Software License, Version 1.0.  (See the
//  accompanying file LICENSE_1_0.txt or a copy at
//  <http://www.boost.org/LICENSE_1_0.txt>.)

//  See <http://www.boost.org/libs/crc/> for the library's home page.

/** \file
    \brief  A collection of function templates and class templates that compute
      various forms of Cyclic Redundancy Codes (CRCs).

    \author  Daryle Walker

    \version  1.5

    \copyright  Boost Software License, version 1.0

    Contains the declarations (and definitions) of various kinds of CRC
    computation functions, function object types, and encapsulated policy types.

    \warning  The sample CRC-computer types were just checked against the
      <a href="http://regregex.bbcmicro.net/crc-catalogue.htm">Catalogue of
      parametrised CRC algorithms</a>.  New type aliases were added where I got
      a standard wrong.  However, the mistaken <code>typedef</code>s are still
      there for backwards compatibility.
    \note  There are references to the <i>Rocksoft&trade; Model CRC
      Algorithm</i>, as described within \"A Painless Guide to CRC Error
      Detection Algorithms,\" linked from \"<a
      href="http://www.ross.net/crc/crcpaper.html">CRC: A Paper On CRCs</a>\" by
      Ross Williams.  It will be abbreviated \"RMCA\" in other documentation
      blocks.
 */

#ifndef BOOST_CRC_HPP
#define BOOST_CRC_HPP

#include <boost/array.hpp>           // for boost::array
#include <boost/config.hpp>          // for BOOST_STATIC_CONSTANT, etc.
#include <boost/cstdint.hpp>         // for UINTMAX_C, boost::uintmax_t
#include <boost/integer.hpp>         // for boost::uint_t
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <climits>  // for CHAR_BIT, etc.
#include <cstddef>  // for std::size_t

#include <boost/limits.hpp>  // for std::numeric_limits


// The type of CRC parameters that can go in a template should be related
// on the CRC's bit count.  This macro expresses that type in a compact
// form, but also allows an alternate type for compilers that don't support
// dependent types (in template value-parameters).
#if !(defined(BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS))
#define BOOST_CRC_PARM_TYPE  typename ::boost::uint_t<Bits>::fast
#else
#define BOOST_CRC_PARM_TYPE  unsigned long
#endif

namespace boost
{


//  Forward declarations  ----------------------------------------------------//

//! Bit-wise CRC computer
template < std::size_t Bits >
    class crc_basic;

//! Table-driven CRC computer, usable as a function object
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly = 0u,
           BOOST_CRC_PARM_TYPE InitRem = 0u,
           BOOST_CRC_PARM_TYPE FinalXor = 0u, bool ReflectIn = false,
           bool ReflectRem = false >
    class crc_optimal;

//! Compute the (unaugmented) CRC of a memory block
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
    typename uint_t<Bits>::fast  crc( void const *buffer,
     std::size_t byte_count);

//! Compute the CRC of a memory block, with any augmentation provided by user
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly >
    typename uint_t<Bits>::fast  augmented_crc( void const *buffer,
     std::size_t byte_count,
     typename uint_t<Bits>::fast initial_remainder = 0u);

//! Computation type for ARC|CRC-16|CRC-IBM|CRC-16/ARC|CRC-16/LHA standard
typedef crc_optimal<16, 0x8005, 0, 0, true, true>         crc_16_type;
//! Computation type for CRC-16/CCITT-FALSE standard
typedef crc_optimal<16, 0x1021, 0xFFFF, 0, false, false>  crc_ccitt_false_t;
//! Computation type for the CRC mistakenly called the CCITT standard
typedef crc_ccitt_false_t                                 crc_ccitt_type;
//! Computation type for the actual
//! KERMIT|CRC-16/CCITT|CRC-16/CCITT-TRUE|CRC-CCITT standard
typedef crc_optimal<16, 0x1021, 0, 0, true, true>         crc_ccitt_true_t;
//! Computation type that I mistakenly called the XMODEM standard; it inverts
//! both reflection parameters and reflects the truncated divisor (Don't use?!)
typedef crc_optimal<16, 0x8408, 0, 0, true, true>         crc_xmodem_type;
//! Computation type for the actual XMODEM|ZMODEM|CRC-16/ACORN standard
typedef crc_optimal<16, 0x1021, 0, 0, false, false>       crc_xmodem_t;

//! Computation type for CRC-32|CRC-32/ADCCP|PKZIP standard
typedef crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>
  crc_32_type;


//  Forward declarations for implementation detail stuff  --------------------//
//  (Just for the stuff that will be needed for the next two sections)

//! \cond
namespace detail
{
    //! Mix-in class to add a possibly-reflecting member function
    template < int BitLength, bool DoIt, int Id = 0 >
        class possible_reflector;

    //! Mix-in class for byte-fed, table-driven CRC algorithms
    template < int Order, boost::uintmax_t TruncatedPolynomial, bool Reflect,
     int Id = 0 >
    class crc_driver;

}  // namespace detail
//! \endcond


//  Simple cyclic redundancy code (CRC) class declaration  -------------------//

/** Objects of this type compute the CRC checksum of submitted data, where said
    data can be entered piecemeal through several different kinds of groupings.
    Modulo-2 polynomial division steps are always performed bit-wise, without
    the use of pre-computation tables.  Said division uses the altered
    algorithm, so any data has to be unaugmented.

    \pre  0 \< \a Bits \<= \c std\::numeric_limits\<uintmax_t\>\::digits

    \tparam Bits  The order of the modulo-2 polynomial divisor.  (\e Width from
      the RMCA)
 */
template < std::size_t Bits >
class crc_basic
{
public:
    // Type
    /** \brief  The register type used for computations

        This type is used for CRC calculations and is the type for any returned
        checksums and returned or submitted remainders, (truncated) divisors, or
        XOR masks.  It is a built-in unsigned integer type.
     */
    typedef typename boost::uint_t<Bits>::fast  value_type;

    // Constant for the template parameter
    //! A copy of \a Bits provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( std::size_t, bit_count = Bits );

    // Constructor (use the automatic copy-ctr, move-ctr, and dtr)
    //! Create a computer, separately listing each needed parameter
    explicit  crc_basic( value_type truncated_polynomial,
               value_type initial_remainder = 0, value_type final_xor_value = 0,
               bool reflect_input = false, bool reflect_remainder = false );

    // Internal Operations
    //! Return the (truncated) polynomial divisor
    value_type  get_truncated_polynominal() const;
    //! Return what the polynomial remainder was set to during construction
    value_type  get_initial_remainder() const;
    //! Return the XOR-mask used during output processing
    value_type  get_final_xor_value() const;
    //! Check if input-bytes will be reflected before processing
    bool        get_reflect_input() const;
    //! Check if the remainder will be reflected during output processing
    bool        get_reflect_remainder() const;

    //! Return the remainder based from already-processed bits
    value_type  get_interim_remainder() const;
    //! Change the interim remainder to a new value
    void        reset( value_type new_rem );
    //! Change the interim remainder back to the initial value
    void        reset();

    // External Operations
    //! Submit a single bit for input processing
    void  process_bit( bool bit );
    //! Submit the lowest \a bit_length bits of a byte for input processing
    void  process_bits( unsigned char bits, std::size_t bit_length );
    //! Submit a single byte for input processing
    void  process_byte( unsigned char byte );
    //! Submit a memory block for input processing, iterator-pair style
    void  process_block( void const *bytes_begin, void const *bytes_end );
    //! Submit a memory block for input processing, pointer-and-size style
    void  process_bytes( void const *buffer, std::size_t byte_count );

    //! Return the checksum of the already-processed bits
    value_type  checksum() const;

private:
    // Member data
    value_type  rem_;
    value_type  poly_, init_, final_;  // non-const to allow assignability
    bool        rft_in_, rft_out_;     // non-const to allow assignability

};  // boost::crc_basic


//  Optimized cyclic redundancy code (CRC) class declaration  ----------------//

/** Objects of this type compute the CRC checksum of submitted data, where said
    data can be entered piecemeal through several different kinds of groupings.
    Modulo-2 polynomial division steps are performed byte-wise, aided by the use
    of pre-computation tables.  Said division uses the altered algorithm, so any
    data has to be unaugmented.

    \pre  0 \< \a Bits \<= \c std\::numeric_limits\<uintmax_t\>\::digits

    \tparam Bits  The order of the modulo-2 polynomial divisor.  (\e Width from
      the RMCA)
    \tparam TruncPoly  The lowest coefficients of the divisor polynomial.  The
      highest-order coefficient is omitted and always assumed to be 1.  Defaults
      to \c 0, i.e. the only non-zero term is the implicit one for
      x<sup><var>Bits</var></sup>.  (\e Poly from the RMCA)
    \tparam InitRem  The (unaugmented) initial state of the polynomial
      remainder.  Defaults to \c 0 if omitted.  (\e Init from the RMCA)
    \tparam FinalXor  The (XOR) bit-mask to be applied to the output remainder,
      after possible reflection but before returning.  Defaults to \c 0 (i.e. no
      bit changes) if omitted.  (\e XorOut from the RMCA)
    \tparam ReflectIn  If \c true, input bytes are read lowest-order bit first,
      otherwise highest-order bit first.  Defaults to \c false if omitted.
      (\e RefIn from the RMCA)
    \tparam ReflectRem  If \c true, the output remainder is reflected before the
      XOR-mask.  Defaults to \c false if omitted.  (\e RefOut from the RMCA)

    \todo  Get rid of the default value for \a TruncPoly.  Choosing a divisor is
      an important decision with many factors, so a default is never useful,
      especially a bad one.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
class crc_optimal
{
public:
    // Type
    //! \copydoc  boost::crc_basic::value_type
    typedef typename boost::uint_t<Bits>::fast  value_type;

    // Constants for the template parameters
    //! \copydoc  boost::crc_basic::bit_count
    BOOST_STATIC_CONSTANT( std::size_t, bit_count = Bits );
    //! A copy of \a TruncPoly provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( value_type, truncated_polynominal = TruncPoly );
    //! A copy of \a InitRem provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( value_type, initial_remainder = InitRem );
    //! A copy of \a FinalXor provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( value_type, final_xor_value = FinalXor );
    //! A copy of \a ReflectIn provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( bool, reflect_input = ReflectIn );
    //! A copy of \a ReflectRem provided for meta-programming purposes
    BOOST_STATIC_CONSTANT( bool, reflect_remainder = ReflectRem );

    // Constructor (use the automatic copy-ctr, move-ctr, and dtr)
    //! Create a computer, giving an initial remainder if desired
    explicit  crc_optimal( value_type init_rem = initial_remainder );

    // Internal Operations
    //! \copybrief  boost::crc_basic::get_truncated_polynominal
    value_type  get_truncated_polynominal() const;
    //! \copybrief  boost::crc_basic::get_initial_remainder
    value_type  get_initial_remainder() const;
    //! \copybrief  boost::crc_basic::get_final_xor_value
    value_type  get_final_xor_value() const;
    //! \copybrief  boost::crc_basic::get_reflect_input
    bool        get_reflect_input() const;
    //! \copybrief  boost::crc_basic::get_reflect_remainder
    bool        get_reflect_remainder() const;

    //! \copybrief  boost::crc_basic::get_interim_remainder
    value_type  get_interim_remainder() const;
    //! Change the interim remainder to either a given value or the initial one
    void        reset( value_type new_rem = initial_remainder );

    // External Operations
    //! \copybrief  boost::crc_basic::process_byte
    void  process_byte( unsigned char byte );
    //! \copybrief  boost::crc_basic::process_block
    void  process_block( void const *bytes_begin, void const *bytes_end );
    //! \copybrief  boost::crc_basic::process_bytes
    void  process_bytes( void const *buffer, std::size_t byte_count );

    //! \copybrief  boost::crc_basic::checksum
    value_type  checksum() const;

    // Operators
    //! Submit a single byte for input processing, suitable for the STL
    void        operator ()( unsigned char byte );
    //! Return the checksum of the already-processed bits, suitable for the STL
    value_type  operator ()() const;

private:
    // Implementation types
    // (Processing for reflected input gives reflected remainders, so you only
    // have to apply output-reflection if Reflect-Remainder doesn't match
    // Reflect-Input.)
    typedef detail::possible_reflector<Bits, ReflectIn>     reflect_i_type;
    typedef detail::crc_driver<Bits, TruncPoly, ReflectIn>  crc_table_type;
    typedef detail::possible_reflector<Bits, ReflectRem != ReflectIn>
      reflect_o_type;

    // Member data
    value_type  rem_;

};  // boost::crc_optimal


//  Implementation detail stuff  ---------------------------------------------//

//! \cond
namespace detail
{
    /** \brief  Meta-programming integral constant for a single-bit bit-mask

        Generates a compile-time constant for a bit-mask that affects a single
        bit.  The \c value will be 2<sup><var>BitIndex</var></sup>.  The \c type
        will be the smallest built-in unsigned integer type that can contain the
        value, unless there's a built-in type that the system can handle easier,
        then the \c type will be smallest fast-handled unsigned integer type.

        \pre  0 \<= BitIndex \< \c std\::numeric_limits\<uintmax_t\>\::digits

        \tparam BitIndex  The place of the sole set bit.
     */
    template < int BitIndex >
    struct high_bit_mask_c
        : boost::integral_constant<typename boost::uint_t< BitIndex + 1 >::fast,
           ( UINTMAX_C(1) << BitIndex )>
    {};

    /** \brief  Meta-programming integral constant for a lowest-bits bit-mask

        Generates a compile-time constant for a bit-mask that affects the lowest
        bits.  The \c value will be 2<sup><var>BitCount</var></sup> - 1.  The
        \c type will be the smallest built-in unsigned integer type that can
        contain the value, unless there's a built-in type that the system can
        handle easier, then the \c type will be smallest fast-handled unsigned
        integer type.

        \pre  0 \<= BitCount \<= \c std\::numeric_limits\<uintmax_t\>\::digits

        \tparam BitCount  The number of lowest-placed bits set.
     */
    template < int BitCount >
    struct low_bits_mask_c
        : boost::integral_constant<typename boost::uint_t< BitCount >::fast, (
           BitCount ? (( (( UINTMAX_C(1) << (BitCount - 1) ) - 1u) << 1 ) |
           UINTMAX_C( 1 )) : 0u )>
    {};

    /** \brief  Reflects the bits of a number

        Reverses the order of the given number of bits within a value.  For
        instance, if the given reflect count is 5, then the bit values for the
        16- and 1-place will switch and the 8- and 2-place will switch, leaving
        the other bits alone.  (The 4-place bit is in the middle, so it wouldn't
        change.)

        \pre  \a Unsigned is a built-in unsigned integer type
        \pre  0 \< word_length \<= \c std\::numeric_limits\<Unsigned\>\::digits

        \tparam Unsigned  The type of \a x.

        \param x  The value to be (partially) reflected.
        \param word_length  The number of low-order bits to reflect.  Defaults
          to the total number of value bits in \a Unsigned.

        \return  The (partially) reflected value.

        \todo  Check if this is the fastest way.
     */
    template < typename Unsigned >
    Unsigned  reflect_unsigned( Unsigned x, int word_length
     = std::numeric_limits<Unsigned>::digits )
    {
        for ( Unsigned  l = 1u, h = l << (word_length - 1) ; h > l ; h >>= 1, l
         <<= 1 )
        {
            Unsigned const  m = h | l, t = x & m;

            if ( (t == h) || (t == l) )
                x ^= m;
        }

        return x;
    }

    /** \brief  Make a byte-to-byte-reflection map

        Creates a mapping array so the results can be cached.  Uses
        #reflect_unsigned to generate the element values.

        \return  An array <var>a</var> such that, for a given byte value
          <var>i</var>, <code><var>a</var>[ <var>i</var> ]</code> resolves to
          the reflected value of <var>i</var>.
     */
    boost::array< unsigned char, (UINTMAX_C( 1 ) << CHAR_BIT) >
    inline make_byte_reflection_table()
    {
        boost::array<unsigned char, ( UINTMAX_C(1) << CHAR_BIT )>  result;
        unsigned char                                              i = 0u;

        do
            result[ i ] = reflect_unsigned( i );
        while ( ++i );
        return result;
    }

    /** \brief  Reflects the bits of a single byte

        Reverses the order of all the bits within a value.  For instance, the
        bit values for the 2<sup><code>CHAR_BIT</code> - 1</sup>- and 1-place
        will switch and the 2<sup><code>CHAR_BIT</code> - 2</sup>- and 2-place
        will switch, etc.

        \param x  The byte value to be reflected.

        \return  The reflected value.

        \note  Since this could be the most common type of reflection, and the
          number of states is relatively small, the implementation pre-computes
          and uses a table of all the results.
     */
    inline unsigned char  reflect_byte( unsigned char x )
    {
        static  boost::array<unsigned char, ( UINTMAX_C(1) << CHAR_BIT )> const
          table = make_byte_reflection_table();

        return table[ x ];
    }

    /** \brief  Reflects some bits within a single byte

        Like #reflect_unsigned, except it takes advantage of any (long-term)
        speed gains #reflect_byte may bring.

        \pre  0 \< \a word_length \<= \c CHAR_BIT

        \param x  The value to be (partially) reflected.
        \param word_length  The number of low-order bits to reflect.

        \return  The (partially) reflected value.
     */
    inline  unsigned char  reflect_sub_byte( unsigned char x, int word_length )
    { return reflect_byte(x) >> (CHAR_BIT - word_length); }

    /** \brief  Possibly reflects the bits of a number

        Reverses the order of the given number of bits within a value.  For
        instance, if the given reflect count is 5, then the bit values for the
        16- and 1-place will switch and the 8- and 2-place will switch, leaving
        the other bits alone.  (The 4-place bit is in the middle, so it wouldn't
        change.)  This variant function allows the reflection be controlled by
        an extra parameter, in case the decision to use reflection is made at
        run-time.

        \pre  \a Unsigned is a built-in unsigned integer type
        \pre  0 \< word_length \<= \c std\::numeric_limits\<Unsigned\>\::digits

        \tparam Unsigned  The type of \a x.

        \param x  The value to be (partially) reflected.
        \param reflect  Controls whether \a x is actually reflected (\c true) or
          left alone (\c false).
        \param word_length  The number of low-order bits to reflect.  Defaults
          to the total number of value bits in \a Unsigned.

        \return  The possibly (partially) reflected value.
     */
    template < typename Unsigned >
    inline
    Unsigned  reflect_optionally( Unsigned x, bool reflect, int word_length
     = std::numeric_limits<Unsigned>::digits )
    { return reflect ? reflect_unsigned(x, word_length) : x; }

    /** \brief  Possibly reflects the bits of a single byte

        Uses #reflect_byte (if \a reflect is \c true).

        \param x  The byte value to be (possibly) reflected.
        \param reflect  Whether (\c true) or not (\c false) \a x is reflected.

        \return  <code><var>reflect</var> ? reflect_byte(<var>x</var>) :
          <var>x</var></code>
     */
    inline
    unsigned char  reflect_byte_optionally( unsigned char x, bool reflect )
    { return reflect ? reflect_byte(x) : x; }

    /** \brief  Update a CRC remainder by several bits, assuming a non-augmented
          message

        Performs several steps of division required by the CRC algorithm, giving
        a new remainder polynomial based on the divisor polynomial and the
        synthesized dividend polynomial (from the old remainder and the
        newly-provided input).  The computations assume that the CRC is directly
        exposed from the remainder, without any zero-valued bits augmented to
        the message bits.

        \pre  \a Register and \a Word are both built-in unsigned integer types
        \pre  0 \< \a register_length \<= std\::numeric_limits\<\a Register\>
          \::digits
        \pre  0 \< \a word_length \<= std\::numeric_limits\<\a Word\>\::digits

        \tparam Register  The type used for representing the remainder and
          divisor modulo-2 polynomials.  The bit at <code>2<sup>i</sup></code>
          is used as the coefficient of <i>x<sup>i</sup></i>.
        \tparam Word  The type used for storing the incoming terms of the
          dividend modulo-2 polynomial.  The bit at <code>2<sup>i</sup></code>
          is used as the coefficient of <i>x<sup>i</sup></i> when \a reflect is
          \c false, and the coefficient of <i>x<sup><var>word_length</var> - 1 -
          i</sup></i> otherwise.

        \param[in]     register_length  The number of significant low-order bits
          to be used from \a Register values.  It is the order of the modulo-2
          polynomial remainder and one less than the divisor's order.
        \param[in,out] remainder  The upper part of the dividend polynomial
          before division, and the remainder polynomial after.
        \param[in]     new_dividend_bits  The coefficients for the next
          \a word_length lowest terms of the dividend polynomial.
        \param[in]     truncated_divisor  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
        \param[in]     word_length  The number of lowest-order bits to read from
          \a new_dividend_bits.
        \param[in]     reflect  If \c false, read from the highest-order marked
          bit from \a new_dividend_bits and go down, as normal.  Otherwise,
          proceed from the lowest-order bit and go up.

        \note  This routine performs a modulo-2 polynomial division variant.
          The exclusive-or operations are applied in a different order, since
          that kind of operation is commutative and associative.  It also
          assumes that the zero-valued augment string was applied before this
          step, which means that the updated remainder can be directly used as
          the final CRC.
     */
    template < typename Register, typename Word >
    void  crc_modulo_word_update( int register_length, Register &remainder, Word
     new_dividend_bits, Register truncated_divisor, int word_length, bool
     reflect )
    {
        // Create this masking constant outside the loop.
        Register const  high_bit_mask = UINTMAX_C(1) << (register_length - 1);

        // The natural reading order for division is highest digit/bit first.
        // The "reflect" parameter switches this.  However, building a bit mask
        // for the lowest bit is the easiest....
        new_dividend_bits = reflect_optionally( new_dividend_bits, !reflect,
         word_length );

        // Perform modulo-2 division for each new dividend input bit
        for ( int  i = word_length ; i ; --i, new_dividend_bits >>= 1 )
        {
            // compare the new bit with the remainder's highest
            remainder ^= ( new_dividend_bits & 1u ) ? high_bit_mask : 0u;

            // perform modulo-2 division
            bool const  quotient = remainder & high_bit_mask;

            remainder <<= 1;
            remainder ^= quotient ? truncated_divisor : 0u;

            // The quotient isn't used for anything, so don't keep it.
        }
    }

    /** \brief  Update a CRC remainder by a single bit, assuming a non-augmented
          message

        Performs the next step of division required by the CRC algorithm, giving
        a new remainder polynomial based on the divisor polynomial and the
        synthesized dividend polynomial (from the old remainder and the
        newly-provided input).  The computations assume that the CRC is directly
        exposed from the remainder, without any zero-valued bits augmented to
        the message bits.

        \pre  \a Register is a built-in unsigned integer type
        \pre  0 \< \a register_length \<= std\::numeric_limits\<\a Register\>
          \::digits

        \tparam Register  The type used for representing the remainder and
          divisor modulo-2 polynomials.  The bit at <code>2<sup>i</sup></code>
          is used as the coefficient of <i>x<sup>i</sup></i>.

        \param[in]     register_length  The number of significant low-order bits
          to be used from \a Register values.  It is the order of the modulo-2
          polynomial remainder and one less than the divisor's order.
        \param[in,out] remainder  The upper part of the dividend polynomial
          before division, and the remainder polynomial after.
        \param[in]     new_dividend_bit  The coefficient for the constant term
          of the dividend polynomial.
        \param[in]     truncated_divisor  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.

        \note  This routine performs a modulo-2 polynomial division variant.
          The exclusive-or operations are applied in a different order, since
          that kind of operation is commutative and associative.  It also
          assumes that the zero-valued augment string was applied before this
          step, which means that the updated remainder can be directly used as
          the final CRC.
     */
    template < typename Register >
    inline  void  crc_modulo_update( int register_length, Register &remainder,
     bool new_dividend_bit, Register truncated_divisor )
    {
        crc_modulo_word_update( register_length, remainder,
         static_cast<unsigned>(new_dividend_bit), truncated_divisor, 1, false );
    }

    /** \brief  Update a CRC remainder by several bits, assuming an augmented
          message

        Performs several steps of division required by the CRC algorithm, giving
        a new remainder polynomial based on the divisor polynomial and the
        synthesized dividend polynomial (from the old remainder and the
        newly-provided input).  The computations assume that a zero-valued
        string of bits will be appended to the message before extracting the
        CRC.

        \pre  \a Register and \a Word are both built-in unsigned integer types
        \pre  0 \< \a register_length \<= std\::numeric_limits\<\a Register\>
          \::digits
        \pre  0 \< \a word_length \<= std\::numeric_limits\<\a Word\>\::digits

        \tparam Register  The type used for representing the remainder and
          divisor modulo-2 polynomials.  The bit at <code>2<sup>i</sup></code>
          is used as the coefficient of <i>x<sup>i</sup></i>.
        \tparam Word  The type used for storing the incoming terms of the
          dividend modulo-2 polynomial.  The bit at <code>2<sup>i</sup></code>
          is used as the coefficient of <i>x<sup>i</sup></i> when \a reflect is
          \c false, and the coefficient of <i>x<sup><var>word_length</var> - 1 -
          i</sup></i> otherwise.

        \param[in]     register_length  The number of significant low-order bits
          to be used from \a Register values.  It is the order of the modulo-2
          polynomial remainder and one less than the divisor's order.
        \param[in,out] remainder  The upper part of the dividend polynomial
          before division, and the remainder polynomial after.
        \param[in]     new_dividend_bits  The coefficients for the next
          \a word_length lowest terms of the dividend polynomial.
        \param[in]     truncated_divisor  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
        \param[in]     word_length  The number of lowest-order bits to read from
          \a new_dividend_bits.
        \param[in]     reflect  If \c false, read from the highest-order marked
          bit from \a new_dividend_bits and go down, as normal.  Otherwise,
          proceed from the lowest-order bit and go up.

        \note  This routine performs straight-forward modulo-2 polynomial
          division.  It assumes that an augment string will be processed at the
          end of the message bits before doing CRC analysis.
        \todo  Use this function somewhere so I can test it.
     */
    template < typename Register, typename Word >
    void  augmented_crc_modulo_word_update( int register_length, Register
     &remainder, Word new_dividend_bits, Register truncated_divisor, int
     word_length, bool reflect )
    {
        // Create this masking constant outside the loop.
        Register const  high_bit_mask = UINTMAX_C(1) << (register_length - 1);

        // The natural reading order for division is highest digit/bit first.
        // The "reflect" parameter switches this.  However, building a bit mask
        // for the lowest bit is the easiest....
        new_dividend_bits = reflect_optionally( new_dividend_bits, not reflect,
         word_length );

        // Perform modulo-2 division for each new dividend input bit
        for ( int  i = word_length ; i ; --i, new_dividend_bits >>= 1 )
        {
            bool const  quotient = remainder & high_bit_mask;

            remainder <<= 1;
            remainder |= new_dividend_bits & 1u;
            remainder ^= quotient ? truncated_divisor : 0u;

            // The quotient isn't used for anything, so don't keep it.
        }
    }

    /** \brief  Update a CRC remainder by a single bit, assuming an augmented
          message

        Performs the next step of division required by the CRC algorithm, giving
        a new remainder polynomial based on the divisor polynomial and the
        synthesized dividend polynomial (from the old remainder and the
        newly-provided input).  The computations assume that a zero-valued
        string of bits will be appended to the message before extracting the
        CRC.

        \pre  \a Register is a built-in unsigned integer type
        \pre  0 \< \a register_length \<= std\::numeric_limits\<\a Register\>
          \::digits

        \tparam Register  The type used for representing the remainder and
          divisor modulo-2 polynomials.  The bit at <code>2<sup>i</sup></code>
          is used as the coefficient of <i>x<sup>i</sup></i>.

        \param[in]     register_length  The number of significant low-order bits
          to be used from \a Register values.  It is the order of the modulo-2
          polynomial remainder and one less than the divisor's order.
        \param[in,out] remainder  The upper part of the dividend polynomial
          before division, and the remainder polynomial after.
        \param[in]     new_dividend_bit  The coefficient for the constant term
          of the dividend polynomial.
        \param[in]     truncated_divisor  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.

        \note  This routine performs straight-forward modulo-2 polynomial
          division.  It assumes that an augment string will be processed at the
          end of the message bits before doing CRC analysis.
        \todo  Use this function somewhere so I can test it.
     */
    template < typename Register >
    inline  void  augmented_crc_modulo_update( int register_length, Register
     &remainder, bool new_dividend_bit, Register truncated_divisor )
    {
        augmented_crc_modulo_word_update( register_length, remainder,
         static_cast<unsigned>(new_dividend_bit), truncated_divisor, 1, false );
    }

    /** \brief  A mix-in class that returns its argument

        This class template makes a function object that returns its argument
        as-is.  It's one case for #possible_reflector.

        \pre  0 \< \a BitLength \<= \c std\::numeric_limits\<uintmax_t\>
          \::digits

        \tparam BitLength  How many significant bits arguments have.
     */
    template < int BitLength >
    class non_reflector
    {
    public:
        /** \brief  The type to check for specialization

            This is a Boost integral constant indicating that this class
            does not reflect its input values.
         */
        typedef boost::false_type                 is_reflecting_type;
        /** \brief  The type to check for register bit length

            This is a Boost integral constant indicating how many
            significant bits won't actually be reflected.
         */
        typedef boost::integral_constant< int, BitLength >      width_c;
        /** \brief  The type of (not-)reflected values

            This type is the input and output type for the (possible-)
            reflection function, which does nothing here.
         */
        typedef typename boost::uint_t< BitLength >::fast  value_type;

        /** \brief  Does nothing

            Returns the given value, not reflecting any part of it.

            \param x  The value to not be reflected.

            \return  \a x
         */
        inline  static  value_type  reflect_q( value_type x )
        { return x; }
    };

    /** \brief  A mix-in class that reflects (the lower part of) its argument,
          generally for types larger than a byte

        This class template makes a function object that returns its argument
        after reflecting its lower-order bits.  It's one sub-case for
        #possible_reflector.

        \pre  \c CHAR_BIT \< \a BitLength \<= \c std\::numeric_limits\<uintmax_t
          \>\::digits

        \tparam BitLength  How many significant bits arguments have.
     */
    template < int BitLength >
    class super_byte_reflector
    {
    public:
        /** \brief  The type to check for specialization

            This is a Boost integral constant indicating that this class
            does reflect its input values.
         */
        typedef boost::true_type                  is_reflecting_type;
        /** \brief  The type to check for register bit length

            This is a Boost integral constant indicating how many
            significant bits will be reflected.
         */
        typedef boost::integral_constant< int, BitLength >      width_c;
        /** \brief  The type of reflected values

            This is both the input and output type for the reflection function.
         */
        typedef typename boost::uint_t< BitLength >::fast  value_type;

        /** \brief  Reflect (part of) the given value

            Reverses the order of the given number of bits within a value,
            using #reflect_unsigned.

            \param x  The value to be (partially) reflected.

            \return  ( <var>x</var> &amp;
              ~(2<sup><var>width_c</var>\::value</sup> - 1) ) | REFLECT(
              <var>x</var> &amp; (2<sup><var>width_c</var>\::value</sup> -
              1) )
         */
        inline  static  value_type  reflect_q( value_type x )
        { return reflect_unsigned(x, width_c::value); }
    };

    /** \brief  A mix-in class that reflects (the lower part of) its argument,
          generally for bytes

        This class template makes a function object that returns its argument
        after reflecting its lower-order bits.  It's one sub-case for
        #possible_reflector.

        \pre  0 \< \a BitLength \<= \c CHAR_BIT

        \tparam BitLength  How many significant bits arguments have.
     */
    template < int BitLength >
    class sub_type_reflector
    {
    public:
        /** \brief  The type to check for specialization

            This is a Boost integral constant indicating that this class
            does reflect its input values.
         */
        typedef boost::true_type              is_reflecting_type;
        /** \brief  The type to check for register bit length

            This is a Boost integral constant indicating how many
            significant bits will be reflected.
         */
        typedef boost::integral_constant< int, BitLength >  width_c;
        /** \brief  The type of reflected values

            This is both the input and output type for the reflection function.
         */
        typedef unsigned char                          value_type;

        /** \brief  Reflect (part of) the given value

            Reverses the order of the given number of bits within a value,
            using #reflect_sub_byte.

            \param x  The value to be (partially) reflected.

            \return  ( <var>x</var> &amp;
              ~(2<sup><var>width_c</var>\::value</sup> - 1) ) | REFLECT(
              <var>x</var> &amp; (2<sup><var>width_c</var>\::value</sup> -
              1) )
         */
        inline  static  value_type  reflect_q( value_type x )
        { return reflect_sub_byte(x, width_c::value); }
    };

    /** \brief  A mix-in class that reflects (the lower part of) its argument

        This class template makes a function object that returns its argument
        after reflecting its lower-order bits.  It's one case for
        #possible_reflector.

        \pre  0 \< \a BitLength \<= \c std\::numeric_limits\<uintmax_t\>
          \::digits

        \tparam BitLength  How many significant bits arguments have.
     */
    template < int BitLength >
    class reflector
        : public boost::conditional< (BitLength > CHAR_BIT),
          super_byte_reflector<BitLength>, sub_type_reflector<BitLength> >::type
    { };

    /** This class template adds a member function #reflect_q that will
        conditionally reflect its first argument, controlled by a compile-time
        parameter.

        \pre  0 \< \a BitLength \<= \c std\::numeric_limits\<uintmax_t\>
          \::digits

        \tparam BitLength  How many significant bits arguments have.
        \tparam DoIt  \c true if #reflect_q will reflect, \c false if it should
          return its argument unchanged.
        \tparam Id  An extra differentiator if multiple copies of this class
          template are mixed-in as base classes.  Defaults to 0 if omitted.
     */
    template < int BitLength, bool DoIt, int Id >
    class possible_reflector
        : public boost::conditional< DoIt, reflector<BitLength>,
          non_reflector<BitLength> >::type
    {
    public:
        /** \brief  The type to check for ID

            This is a Boost integral constant indicating what ID number this
            instantiation used.
         */
        typedef boost::integral_constant<int, Id>  id_type;
    };

    /** \brief  Find the composite remainder update effect from a fixed bit
          sequence, for each potential sequence combination.

        For each value between 0 and 2<sup><var>SubOrder</var></sup> - 1,
        computes the XOR mask corresponding to the composite effect they update
        the incoming remainder, which is the upper part of the dividend that
        gets (partially) pushed out of its register by the incoming value's
        bits.  The composite value merges the \"partial products\" from each bit
        of the value being updated individually.

        \pre  \a Register is a built-in unsigned integer type
        \pre  0 \< \a SubOrder \<= \a register_length \<=
          std\::numeric_limits\<\a Register\>\::digits

        \tparam SubOrder  The number of low-order significant bits of the trial
          new dividends.
        \tparam Register  The type used for representing the remainder and
          divisor modulo-2 polynomials.  The bit at <code>2<sup>i</sup></code>
          is used as the coefficient of <i>x<sup>i</sup></i>.

        \param[in] register_length  The number of significant low-order bits
          to be used from \a Register values.  It is the order of the modulo-2
          polynomial remainder and one less than the divisor's order.
        \param[in] truncated_divisor  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
        \param[in] reflect  If \c false, read from the highest-order marked
          bit from a new dividend's bits and go down, as normal.  Otherwise,
          proceed from the lowest-order bit and go up.

        \return  An array such that the element at index <var>i</var> is the
          composite effect XOR mask for value <var>i</var>.

        \note  This routine performs a modulo-2 polynomial division variant.
          The exclusive-or operations are applied in a different order, since
          that kind of operation is commutative and associative.  It also
          assumes that the zero-valued augment string was applied before this
          step, which means that the updated remainder can be directly used as
          the final CRC.
        \todo  Check that using the unaugmented-CRC division routines give the
          same composite mask table as using augmented-CRC routines.
     */
    template < int SubOrder, typename Register >
    boost::array< Register, (UINTMAX_C( 1 ) << SubOrder) >
    make_partial_xor_products_table( int register_length, Register
     truncated_divisor, bool reflect )
    {
        boost::array<Register, ( UINTMAX_C(1) << SubOrder )>  result;

        // Loop over every possible dividend value
        for ( typename boost::uint_t<SubOrder + 1>::fast  dividend = 0u;
         dividend < result.size() ; ++dividend )
        {
            Register  remainder = 0u;

            crc_modulo_word_update( register_length, remainder, dividend,
             truncated_divisor, SubOrder, false );
            result[ reflect_optionally(dividend, reflect, SubOrder) ] =
             reflect_optionally( remainder, reflect, register_length );
        }
        return result;
    }

    /** \brief  A mix-in class for the table of table-driven CRC algorithms

        Encapsulates the parameters need to make a global (technically,
        class-static) table usuable in CRC algorithms, and generates said
        table.

        \pre  0 \< \a SubOrder \<= Order \<=
          std\::numeric_limits\<uintmax_t\>\::digits

        \tparam Order  The order of the modulo-2 polynomial remainder and one
          less than the divisor's order.
        \tparam SubOrder  The number of low-order significant bits of the trial
          new dividends.
        \tparam TruncatedPolynomial  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
        \tparam Reflect  If \c false, read from the highest-order marked
          bit from a new dividend's bits and go down, as normal.  Otherwise,
          proceed from the lowest-order bit and go up.
     */
    template < int Order, int SubOrder, boost::uintmax_t TruncatedPolynomial,
     bool Reflect >
    class crc_table_t
    {
    public:
        /** \brief  The type to check for register bit length

            This is a Boost integral constant indicating how many
            significant bits are in the remainder and (truncated) divisor.
         */
        typedef boost::integral_constant< int, Order >              width_c;
        /** \brief  The type to check for index-unit bit length

            This is a Boost integral constant indicating how many
            significant bits are in the trial new dividends.
         */
        typedef boost::integral_constant< int, SubOrder >      unit_width_c;
        /** \brief  The type of registers

            This is the output type for the partial-product map.
         */
        typedef typename boost::uint_t< Order >::fast          value_type;
        /** \brief  The type to check the divisor

            This is a Boost integral constant representing the (truncated)
            divisor.
         */
        typedef boost::integral_constant< value_type, TruncatedPolynomial >
          poly_c;
        /** \brief  The type to check for reflection

            This is a Boost integral constant representing whether input
            units should be read in reverse order.
         */
        typedef boost::integral_constant< bool, Reflect >           refin_c;
        /** \brief  The type to check for map size

            This is a Boost integral constant representing the number of
            elements in the partial-product map, based on the unit size.
         */
        typedef high_bit_mask_c< SubOrder >                  table_size_c;
        /** \brief  The type of the unit TO partial-product map

            This is the array type that takes units as the index and said unit's
            composite partial-product mask as the element.
         */
        typedef boost::array<value_type, table_size_c::value>  array_type;
        /** \brief  Create a global array for the mapping table

            Creates an instance of a partial-product array with this class's
            parameters.

            \return  A reference to a immutable array giving the partial-product
              update XOR map for each potential sub-unit value.
         */
        static  array_type const &  get_table()
        {
            static  array_type const  table =
             make_partial_xor_products_table<unit_width_c::value>(
             width_c::value, poly_c::value, refin_c::value );

            return table;
        }
    };

    /** \brief  A mix-in class that handles direct (i.e. non-reflected) byte-fed
          table-driven CRC algorithms

        This class template adds member functions #augmented_crc_update and
        #crc_update to update remainders from new input bytes.  The bytes aren't
        reflected before processing.

        \pre  \c CHAR_BIT \<= \a Order \<= \c std\::numeric_limits\<uintmax_t\>
          \::digits

        \tparam Order  The order of the modulo-2 polynomial remainder and one
          less than the divisor's order.
        \tparam TruncatedPolynomial  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
     */
    template < int Order, boost::uintmax_t TruncatedPolynomial >
    class direct_byte_table_driven_crcs
        : public crc_table_t<Order, CHAR_BIT, TruncatedPolynomial, false>
    {
        typedef crc_table_t<Order, CHAR_BIT, TruncatedPolynomial, false>
          base_type;

    public:
        typedef typename base_type::value_type  value_type;
        typedef typename base_type::array_type  array_type;

        /** \brief  Compute the updated remainder after reading some bytes

            The implementation reads from a table to speed-up applying
            augmented-CRC updates byte-wise.

            \param remainder  The pre-update remainder
            \param new_dividend_bytes  The address where the new bytes start
            \param new_dividend_byte_count  The number of new bytes to read

            \return  The updated remainder
         */
        static  value_type  augmented_crc_update( value_type remainder, unsigned
         char const *new_dividend_bytes, std::size_t new_dividend_byte_count)
        {
            static  array_type const &  table = base_type::get_table();

            while ( new_dividend_byte_count-- )
            {
                // Locates the merged partial product based on the leading byte
                unsigned char const  index = ( remainder >> (Order - CHAR_BIT) )
                 & UCHAR_MAX;

                // Complete the multi-bit modulo-2 polynomial division
                remainder <<= CHAR_BIT;
                remainder |= *new_dividend_bytes++;
                remainder ^= table.elems[ index ];
            }

            return remainder;
        }

        /** \brief  Compute the updated remainder after reading some bytes

            The implementation reads from a table to speed-up applying
            unaugmented-CRC updates byte-wise.

            \param remainder  The pre-update remainder
            \param new_dividend_bytes  The address where the new bytes start
            \param new_dividend_byte_count  The number of new bytes to read

            \return  The updated remainder
         */
        static  value_type  crc_update( value_type remainder, unsigned char
         const *new_dividend_bytes, std::size_t new_dividend_byte_count)
        {
            static  array_type const &  table = base_type::get_table();

            while ( new_dividend_byte_count-- )
            {
                // Locates the merged partial product based on comparing the
                // leading and incoming bytes
                unsigned char const  index = ( (remainder >> ( Order - CHAR_BIT
                 )) & UCHAR_MAX ) ^ *new_dividend_bytes++;

                // Complete the multi-bit altered modulo-2 polynomial division
                remainder <<= CHAR_BIT;
                remainder ^= table.elems[ index ];
            }

            return remainder;
        }
    };

    /** \brief  A mix-in class that handles reflected byte-fed, table-driven CRC
          algorithms

        This class template adds member functions #augmented_crc_update and
        #crc_update to update remainders from new input bytes.  The bytes are
        reflected before processing.

        \pre  \c CHAR_BIT \<= \a Order \<= \c std\::numeric_limits\<uintmax_t\>
          \::digits

        \tparam Order  The order of the modulo-2 polynomial remainder and one
          less than the divisor's order.
        \tparam TruncatedPolynomial  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
     */
    template < int Order, boost::uintmax_t TruncatedPolynomial >
    class reflected_byte_table_driven_crcs
        : public crc_table_t<Order, CHAR_BIT, TruncatedPolynomial, true>
    {
        typedef crc_table_t<Order, CHAR_BIT, TruncatedPolynomial, true>
          base_type;

    public:
        typedef typename base_type::value_type  value_type;
        typedef typename base_type::array_type  array_type;

        /** \brief  Compute the updated remainder after reading some bytes

            The implementation reads from a table to speed-up applying
            reflecting augmented-CRC updates byte-wise.

            \param remainder  The pre-update remainder; since the bytes are
              being reflected, this remainder also has to be reflected
            \param new_dividend_bytes  The address where the new bytes start
            \param new_dividend_byte_count  The number of new bytes to read

            \return  The updated, reflected remainder
         */
        static  value_type  augmented_crc_update( value_type remainder, unsigned
         char const *new_dividend_bytes, std::size_t new_dividend_byte_count)
        {
            static  array_type const &  table = base_type::get_table();

            while ( new_dividend_byte_count-- )
            {
                // Locates the merged partial product based on the leading byte
                // (which is at the low-order end for reflected remainders)
                unsigned char const  index = remainder & UCHAR_MAX;

                // Complete the multi-bit reflected modulo-2 polynomial division
                remainder >>= CHAR_BIT;
                remainder |= static_cast<value_type>( *new_dividend_bytes++ )
                 << ( Order - CHAR_BIT );
                remainder ^= table.elems[ index ];
            }

            return remainder;
        }

        /** \brief  Compute the updated remainder after reading some bytes

            The implementation reads from a table to speed-up applying
            reflected unaugmented-CRC updates byte-wise.

            \param remainder  The pre-update remainder; since the bytes are
              being reflected, this remainder also has to be reflected
            \param new_dividend_bytes  The address where the new bytes start
            \param new_dividend_byte_count  The number of new bytes to read

            \return  The updated, reflected remainder
         */
        static  value_type  crc_update( value_type remainder, unsigned char
         const *new_dividend_bytes, std::size_t new_dividend_byte_count)
        {
            static  array_type const &  table = base_type::get_table();

            while ( new_dividend_byte_count-- )
            {
                // Locates the merged partial product based on comparing the
                // leading and incoming bytes
                unsigned char const  index = ( remainder & UCHAR_MAX ) ^
                 *new_dividend_bytes++;

                // Complete the multi-bit reflected altered modulo-2 polynomial
                // division
                remainder >>= CHAR_BIT;
                remainder ^= table.elems[ index ];
            }

            return remainder;
        }
    };

    /** \brief  Mix-in class for byte-fed, table-driven CRC algorithms with
          parameter values at least a byte in width

        This class template adds member functions #augmented_crc_update and
        #crc_update to update remainders from new input bytes.  The bytes may be
        reflected before processing, controlled by a compile-time parameter.

        \pre  \c CHAR_BIT \<= \a Order \<= \c std\::numeric_limits\<uintmax_t\>
          \::digits

        \tparam Order  The order of the modulo-2 polynomial remainder and one
          less than the divisor's order.
        \tparam TruncatedPolynomial  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
        \tparam Reflect  If \c false, read from the highest-order bit from a new
          input byte and go down, as normal.  Otherwise, proceed from the
          lowest-order bit and go up.
     */
    template < int Order, boost::uintmax_t TruncatedPolynomial, bool Reflect >
    class byte_table_driven_crcs
        : public boost::conditional< Reflect,
          reflected_byte_table_driven_crcs<Order, TruncatedPolynomial>,
          direct_byte_table_driven_crcs<Order, TruncatedPolynomial> >::type
    { };

    /** \brief  A mix-in class that handles direct (i.e. non-reflected) byte-fed
          CRC algorithms for sub-byte parameters

        This class template adds member functions #augmented_crc_update and
        #crc_update to update remainders from new input bytes.  The bytes aren't
        reflected before processing.

        \pre  0 \< \a Order \< \c CHAR_BIT

        \tparam Order  The order of the modulo-2 polynomial remainder and one
          less than the divisor's order.
        \tparam TruncatedPolynomial  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
     */
    template < int Order, boost::uintmax_t TruncatedPolynomial >
    class direct_sub_byte_crcs
        : public crc_table_t<Order, Order, TruncatedPolynomial, false>
    {
        typedef crc_table_t<Order, Order, TruncatedPolynomial, false>
          base_type;

    public:
        typedef typename base_type::width_c     width_c;
        typedef typename base_type::value_type  value_type;
        typedef typename base_type::poly_c       poly_c;
        typedef typename base_type::array_type  array_type;

        /** \brief  Compute the updated remainder after reading some bytes

            The implementation reads from a table to speed-up applying
            augmented-CRC updates byte-wise.

            \param remainder  The pre-update remainder
            \param new_dividend_bytes  The address where the new bytes start
            \param new_dividend_byte_count  The number of new bytes to read

            \return  The updated remainder

            \todo  Use this function somewhere so I can test it.
         */
        static  value_type  augmented_crc_update( value_type remainder, unsigned
         char const *new_dividend_bytes, std::size_t new_dividend_byte_count)
        {
            //static  array_type const &  table = base_type::get_table();

            while ( new_dividend_byte_count-- )
            {
                // Without a table, process each byte explicitly
                augmented_crc_modulo_word_update( width_c::value, remainder,
                 *new_dividend_bytes++, poly_c::value, CHAR_BIT, false );
            }

            return remainder;
        }

        /** \brief  Compute the updated remainder after reading some bytes

            The implementation reads from a table to speed-up applying
            unaugmented-CRC updates byte-wise.

            \param remainder  The pre-update remainder
            \param new_dividend_bytes  The address where the new bytes start
            \param new_dividend_byte_count  The number of new bytes to read

            \return  The updated remainder
         */
        static  value_type  crc_update( value_type remainder, unsigned char
         const *new_dividend_bytes, std::size_t new_dividend_byte_count)
        {
            //static  array_type const &  table = base_type::get_table();

            while ( new_dividend_byte_count-- )
            {
                // Without a table, process each byte explicitly
                crc_modulo_word_update( width_c::value, remainder,
                 *new_dividend_bytes++, poly_c::value, CHAR_BIT, false );
            }

            return remainder;
        }
    };

    /** \brief  A mix-in class that handles reflected byte-fed, CRC algorithms
          for sub-byte parameters

        This class template adds member functions #augmented_crc_update and
        #crc_update to update remainders from new input bytes.  The bytes are
        reflected before processing.

        \pre  0 \< \a Order \< \c CHAR_BIT

        \tparam Order  The order of the modulo-2 polynomial remainder and one
          less than the divisor's order.
        \tparam TruncatedPolynomial  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
     */
    template < int Order, boost::uintmax_t TruncatedPolynomial >
    class reflected_sub_byte_crcs
        : public crc_table_t<Order, Order, TruncatedPolynomial, true>
    {
        typedef crc_table_t<Order, Order, TruncatedPolynomial, true>
          base_type;

    public:
        typedef typename base_type::width_c     width_c;
        typedef typename base_type::value_type  value_type;
        typedef typename base_type::poly_c       poly_c;
        typedef typename base_type::array_type  array_type;

        /** \brief  Compute the updated remainder after reading some bytes

            The implementation reads from a table to speed-up applying
            reflecting augmented-CRC updates byte-wise.

            \param remainder  The pre-update remainder; since the bytes are
              being reflected, this remainder also has to be reflected
            \param new_dividend_bytes  The address where the new bytes start
            \param new_dividend_byte_count  The number of new bytes to read

            \return  The updated, reflected remainder

            \todo  Use this function somewhere so I can test it.
         */
        static  value_type  augmented_crc_update( value_type remainder, unsigned
         char const *new_dividend_bytes, std::size_t new_dividend_byte_count)
        {
            //static  array_type const &  table = base_type::get_table();

            remainder = reflect_sub_byte( remainder, width_c::value );
            while ( new_dividend_byte_count-- )
            {
                // Without a table, process each byte explicitly
                augmented_crc_modulo_word_update( width_c::value, remainder,
                 *new_dividend_bytes++, poly_c::value, CHAR_BIT, true );
            }
            remainder = reflect_sub_byte( remainder, width_c::value );

            return remainder;
        }

        /** \brief  Compute the updated remainder after reading some bytes

            The implementation reads from a table to speed-up applying
            reflected unaugmented-CRC updates byte-wise.

            \param remainder  The pre-update remainder; since the bytes are
              being reflected, this remainder also has to be reflected
            \param new_dividend_bytes  The address where the new bytes start
            \param new_dividend_byte_count  The number of new bytes to read

            \return  The updated, reflected remainder
         */
        static  value_type  crc_update( value_type remainder, unsigned char
         const *new_dividend_bytes, std::size_t new_dividend_byte_count)
        {
            //static  array_type const &  table = base_type::get_table();

            remainder = reflect_sub_byte( remainder, width_c::value );
            while ( new_dividend_byte_count-- )
            {
                // Without a table, process each byte explicitly
                crc_modulo_word_update( width_c::value, remainder,
                 *new_dividend_bytes++, poly_c::value, CHAR_BIT, true );
            }
            remainder = reflect_sub_byte( remainder, width_c::value );

            return remainder;
        }
    };

    /** \brief  Mix-in class for byte-fed, table-driven CRC algorithms with
          sub-byte parameters

        This class template adds member functions #augmented_crc_update and
        #crc_update to update remainders from new input bytes.  The bytes may be
        reflected before processing, controlled by a compile-time parameter.

        \pre  0 \< \a Order \< \c CHAR_BIT

        \tparam Order  The order of the modulo-2 polynomial remainder and one
          less than the divisor's order.
        \tparam TruncatedPolynomial  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
        \tparam Reflect  If \c false, read from the highest-order bit from a new
          input byte and go down, as normal.  Otherwise, proceed from the
          lowest-order bit and go up.
     */
    template < int Order, boost::uintmax_t TruncatedPolynomial, bool Reflect >
    class sub_byte_crcs
        : public boost::conditional< Reflect,
          reflected_sub_byte_crcs<Order, TruncatedPolynomial>,
          direct_sub_byte_crcs<Order, TruncatedPolynomial> >::type
    { };

    /** This class template adds member functions #augmented_crc_update and
        #crc_update to update remainders from new input bytes.  The bytes may be
        reflected before processing, controlled by a compile-time parameter.

        \pre  0 \< \a Order \<= \c std\::numeric_limits\<uintmax_t\>\::digits

        \tparam Order  The order of the modulo-2 polynomial remainder and one
          less than the divisor's order.
        \tparam TruncatedPolynomial  The lowest coefficients of the divisor
          polynomial.  The highest-order coefficient is omitted and always
          assumed to be 1.
        \tparam Reflect  If \c false, read from the highest-order bit from a new
          input byte and go down, as normal.  Otherwise, proceed from the
          lowest-order bit and go up.
        \tparam Id  An extra differentiator if multiple copies of this class
          template are mixed-in as base classes.  Defaults to 0 if omitted.
     */
    template < int Order, boost::uintmax_t TruncatedPolynomial, bool Reflect,
     int Id >
    class crc_driver
        : public boost::conditional< (Order < CHAR_BIT), sub_byte_crcs<Order,
          TruncatedPolynomial, Reflect>, byte_table_driven_crcs<Order,
          TruncatedPolynomial, Reflect> >::type
    {
    public:
        /** \brief  The type to check for ID

            This is a Boost integral constant indicating what ID number this
            instantiation used.
         */
        typedef boost::integral_constant<int, Id>  id_type;
    };


}  // namespace detail
//! \endcond


//  Simple CRC class function definitions  -----------------------------------//

/** Constructs a \c crc_basic object with at least the required parameters to a
    particular CRC formula to be processed upon receiving input.

    \param[in] truncated_polynomial  The lowest coefficients of the divisor
      polynomial.  The highest-order coefficient is omitted and always assumed
      to be 1.  (\e Poly from the RMCA)
    \param[in] initial_remainder  The (unaugmented) initial state of the
      polynomial remainder.  Defaults to \c 0 if omitted.  (\e Init from the
      RMCA)
    \param[in] final_xor_value  The (XOR) bit-mask to be applied to the output
      remainder, after possible reflection but before returning.  Defaults to
      \c 0 (i.e. no bit changes) if omitted.  (\e XorOut from the RMCA)
    \param[in] reflect_input  If \c true, input bytes are read lowest-order bit
      first, otherwise highest-order bit first.  Defaults to \c false if
      omitted.  (\e RefIn from the RMCA)
    \param[in] reflect_remainder  If \c true, the output remainder is reflected
      before the XOR-mask.  Defaults to \c false if omitted.  (\e RefOut from
      the RMCA)

    \post  <code><var>truncated_polynomial</var> ==
      this-&gt;get_truncated_polynominal()</code>
    \post  <code><var>initial_remainder</var> ==
      this-&gt;get_initial_remainder()</code>
    \post  <code><var>final_xor_value</var> ==
      this-&gt;get_final_xor_value()</code>
    \post  <code><var>reflect_input</var> ==
      this-&gt;get_reflect_input()</code>
    \post  <code><var>reflect_remainder</var> ==
      this-&gt;get_reflect_remainder()</code>
    \post  <code><var>initial_remainder</var> ==
      this-&gt;get_interim_remainder()</code>
    \post  <code>(<var>reflect_remainder</var> ?
      REFLECT(<var>initial_remainder</var>) : <var>initial_remainder</var>) ^
      <var>final_xor_value</var> == this-&gt;checksum()</code>
 */
template < std::size_t Bits >
inline
crc_basic<Bits>::crc_basic
(
    value_type  truncated_polynomial,
    value_type  initial_remainder,      // = 0
    value_type  final_xor_value,        // = 0
    bool        reflect_input,          // = false
    bool        reflect_remainder       // = false
)
    : rem_( initial_remainder ), poly_( truncated_polynomial )
    , init_( initial_remainder ), final_( final_xor_value )
    , rft_in_( reflect_input ), rft_out_( reflect_remainder )
{
}

/** Returns a representation of the polynomial divisor.  The value of the
    2<sup>i</sup> bit is the value of the coefficient of the polynomial's
    x<sup>i</sup> term.  The omitted bit for x<sup>(#bit_count)</sup> term is
    always 1.

    \return  The bit-packed list of coefficients.  If the bit-length of
      #value_type exceeds #bit_count, the values of higher-placed bits should be
      ignored (even any for x<sup>(#bit_count)</sup>) since they're unregulated.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_truncated_polynominal
(
) const
{
    return poly_;
}

/** Returns a representation of the polynomial remainder before any input has
    been submitted.  The value of the 2<sup>i</sup> bit is the value of the
    coefficient of the polynomial's x<sup>i</sup> term.

    \return  The bit-packed list of coefficients.  If the bit-length of
      #value_type exceeds #bit_count, the values of higher-placed bits should be
      ignored since they're unregulated.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_initial_remainder
(
) const
{
    return init_;
}

/** Returns the mask to be used during creation of a checksum.  The mask is used
    for an exclusive-or (XOR) operation applied bit-wise to the interim
    remainder representation (after any reflection, if #get_reflect_remainder()
    returns \c true).

    \return  The bit-mask.  If the bit-length of #value_type exceeds #bit_count,
      the values of higher-placed bits should be ignored since they're
      unregulated.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_final_xor_value
(
) const
{
    return final_;
}

/** Returns a whether or not a submitted byte will be \"reflected\" before it is
    used to update the interim remainder.  Only the byte-wise operations
    #process_byte, #process_block, and #process_bytes are affected.

    \retval true  Input bytes will be read starting from the lowest-order bit.
    \retval false  Input bytes will be read starting from the highest-order bit.
 */
template < std::size_t Bits >
inline
bool
crc_basic<Bits>::get_reflect_input
(
) const
{
    return rft_in_;
}

/** Indicates if the interim remainder will be \"reflected\" before it is passed
    to the XOR-mask stage when returning a checksum.

    \retval true  The interim remainder is reflected before further work.
    \retval false  The interim remainder is applied to the XOR-mask as-is.
 */
template < std::size_t Bits >
inline
bool
crc_basic<Bits>::get_reflect_remainder
(
) const
{
    return rft_out_;
}

/** Returns a representation of the polynomial remainder after all the input
    submissions since construction or the last #reset call.  The value of the
    2<sup>i</sup> bit is the value of the coefficient of the polynomial's
    x<sup>i</sup> term.  If CRC processing gets interrupted here, retain the
    value returned, and use it to start up the next CRC computer where you left
    off (with #reset(value_type) or construction).  The next computer has to
    have its other parameters compatible with this computer.

    \return  The bit-packed list of coefficients.  If the bit-length of
      #value_type exceeds #bit_count, the values of higher-placed bits should be
      ignored since they're unregulated.  No output processing (reflection or
      XOR mask) has been applied to the value.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_interim_remainder
(
) const
{
    return rem_ & detail::low_bits_mask_c<bit_count>::value;
}

/** Changes the interim polynomial remainder to \a new_rem, purging any
    influence previously submitted input has had.  The value of the
    2<sup>i</sup> bit is the value of the coefficient of the polynomial's
    x<sup>i</sup> term.

    \param[in] new_rem  The (unaugmented) state of the polynomial remainder
      starting from this point, with no output processing applied.

    \post  <code><var>new_rem</var> == this-&gt;get_interim_remainder()</code>
    \post  <code>((this-&gt;get_reflect_remainder() ?
      REFLECT(<var>new_rem</var>) : <var>new_rem</var>) ^
      this-&gt;get_final_xor_value()) == this-&gt;checksum()</code>
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::reset
(
    value_type  new_rem
)
{
    rem_ = new_rem;
}

/** Changes the interim polynomial remainder to the initial remainder given
    during construction, purging any influence previously submitted input has
    had.  The value of the 2<sup>i</sup> bit is the value of the coefficient of
    the polynomial's x<sup>i</sup> term.

    \post  <code>this-&gt;get_initial_remainder() ==
      this-&gt;get_interim_remainder()</code>
    \post  <code>((this-&gt;get_reflect_remainder() ?
      REFLECT(this-&gt;get_initial_remainder()) :
      this-&gt;get_initial_remainder()) ^ this-&gt;get_final_xor_value())
      == this-&gt;checksum()</code>
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::reset
(
)
{
    this->reset( this->get_initial_remainder() );
}

/** Updates the interim remainder with a single altered-CRC-division step.

    \param[in] bit  The new input bit.

    \post  The interim remainder is updated though a modulo-2 polynomial
      division, where the division steps are altered for unaugmented CRCs.
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_bit
(
    bool  bit
)
{
    detail::crc_modulo_update( bit_count, rem_, bit, poly_ );
}

/** Updates the interim remainder with several altered-CRC-division steps.  Each
    bit is processed separately, starting from the one at the
    2<sup><var>bit_length</var> - 1</sup> place, then proceeding down to the
    lowest-placed bit.  Any order imposed by
    <code>this-&gt;get_reflect_input()</code> is ignored.

    \pre  0 \< \a bit_length \<= \c CHAR_BIT

    \param[in] bits  The byte containing the new input bits.
    \param[in] bit_length  The number of bits in the byte to be read.

    \post  The interim remainder is updated though \a bit_length modulo-2
      polynomial divisions, where the division steps are altered for unaugmented
      CRCs.
 */
template < std::size_t Bits >
void
crc_basic<Bits>::process_bits
(
    unsigned char  bits,
    std::size_t    bit_length
)
{
    // ignore the bits above the ones we want
    bits <<= CHAR_BIT - bit_length;

    // compute the CRC for each bit, starting with the upper ones
    unsigned char const  high_bit_mask = 1u << ( CHAR_BIT - 1u );
    for ( std::size_t i = bit_length ; i > 0u ; --i, bits <<= 1u )
    {
        process_bit( static_cast<bool>(bits & high_bit_mask) );
    }
}

/** Updates the interim remainder with a byte's worth of altered-CRC-division
    steps.  The bits within the byte are processed from the highest place down
    if <code>this-&gt;get_reflect_input()</code> is \c false, and lowest place
    up otherwise.

    \param[in] byte  The new input byte.

    \post  The interim remainder is updated though \c CHAR_BIT modulo-2
      polynomial divisions, where the division steps are altered for unaugmented
      CRCs.
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_byte
(
    unsigned char  byte
)
{
    process_bits( (rft_in_ ? detail::reflect_byte( byte ) : byte), CHAR_BIT );
}

/** Updates the interim remainder with several bytes' worth of
    altered-CRC-division steps.  The bits within each byte are processed from
    the highest place down if <code>this-&gt;get_reflect_input()</code> is
    \c false, and lowest place up otherwise.  The bytes themselves are processed
    starting from the one pointed by \a bytes_begin until \a bytes_end is
    reached through forward iteration, treating the two pointers as if they
    point to <code>unsigned char</code> objects.

    \pre  \a bytes_end has to equal \a bytes_begin if the latter is \c NULL or
      otherwise doesn't point to a valid buffer.
    \pre  \a bytes_end, if not equal to \a bytes_begin, has to point within or
      one-byte-past the same buffer \a bytes_begin points into.
    \pre  \a bytes_end has to be reachable from \a bytes_begin through a finite
      number of forward byte-pointer increments.

    \param[in] bytes_begin  The address where the memory block begins.
    \param[in] bytes_end  Points to one-byte past the address of the memory
      block's last byte, or \a bytes_begin if no bytes are to be read.

    \post  The interim remainder is updated though <code>CHAR_BIT * (((unsigned
      char const *) bytes_end) - ((unsigned char const *) bytes_begin))</code>
      modulo-2 polynomial divisions, where the division steps are altered for
      unaugmented CRCs.
 */
template < std::size_t Bits >
void
crc_basic<Bits>::process_block
(
    void const *  bytes_begin,
    void const *  bytes_end
)
{
    for ( unsigned char const * p
     = static_cast<unsigned char const *>(bytes_begin) ; p < bytes_end ; ++p )
    {
        process_byte( *p );
    }
}

/** Updates the interim remainder with several bytes' worth of
    altered-CRC-division steps.  The bits within each byte are processed from
    the highest place down if <code>this-&gt;get_reflect_input()</code> is
    \c false, and lowest place up otherwise.  The bytes themselves are processed
    starting from the one pointed by \a buffer, forward-iterated (as if the
    pointed-to objects were of <code>unsigned char</code>) until \a byte_count
    bytes are read.

    \pre  \a byte_count has to equal 0 if \a buffer is \c NULL or otherwise
      doesn't point to valid memory.
    \pre  If \a buffer points within valid memory, then that block has to have
      at least \a byte_count more valid bytes allocated from that point.

    \param[in] buffer  The address where the memory block begins.
    \param[in] byte_count  The number of bytes in the memory block.

    \post  The interim remainder is updated though <code>CHAR_BIT *
      <var>byte_count</var></code> modulo-2 polynomial divisions, where the
      division steps are altered for unaugmented CRCs.
 */
template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_bytes
(
    void const *  buffer,
    std::size_t   byte_count
)
{
    unsigned char const * const  b = static_cast<unsigned char const *>(
     buffer );

    process_block( b, b + byte_count );
}

/** Computes the checksum of all the submitted bits since construction or the
    last call to #reset.  The checksum will be the raw checksum, i.e. the
    (interim) remainder after all the modulo-2 polynomial division, plus any
    output processing.

    \return  <code>(this-&gt;get_reflect_remainder() ?
      REFLECT(this-&gt;get_interim_remainder()) :
      this-&gt;get_interim_remainder()) ^ this-&gt;get_final_xor_value()</code>

    \note  Since checksums are meant to be compared, any higher-placed bits
      (when the bit-length of #value_type exceeds #bit_count) will be set to 0.
 */
template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::checksum
(
) const
{
    return ( (rft_out_ ? detail::reflect_unsigned( rem_, bit_count ) :
     rem_) ^ final_ ) & detail::low_bits_mask_c<bit_count>::value;
}


//  Optimized CRC class function definitions  --------------------------------//

// Macro to compact code
#define BOOST_CRC_OPTIMAL_NAME  crc_optimal<Bits, TruncPoly, InitRem, \
 FinalXor, ReflectIn, ReflectRem>

/** Constructs a \c crc_optimal object with a particular CRC formula to be
    processed upon receiving input.  The initial remainder may be overridden.

    \param[in] init_rem  The (unaugmented) initial state of the polynomial
      remainder.  Defaults to #initial_remainder if omitted.

    \post  <code>#truncated_polynominal ==
      this-&gt;get_truncated_polynominal()</code>
    \post  <code>#initial_remainder == this-&gt;get_initial_remainder()</code>
    \post  <code>#final_xor_value == this-&gt;get_final_xor_value()</code>
    \post  <code>#reflect_input == this-&gt;get_reflect_input()</code>
    \post  <code>#reflect_remainder == this-&gt;get_reflect_remainder()</code>
    \post  <code><var>init_rem</var> == this-&gt;get_interim_remainder()</code>
    \post  <code>(#reflect_remainder ? REFLECT(<var>init_rem</var>) :
      <var>init_rem</var>) ^ #final_xor_value == this-&gt;checksum()</code>
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
BOOST_CRC_OPTIMAL_NAME::crc_optimal
(
    value_type  init_rem  // = initial_remainder
)
    : rem_( reflect_i_type::reflect_q(init_rem) )
{
}

//! \copydetails  boost::crc_basic::get_truncated_polynominal
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_truncated_polynominal
(
) const
{
    return truncated_polynominal;
}

//! \copydetails  boost::crc_basic::get_initial_remainder
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_initial_remainder
(
) const
{
    return initial_remainder;
}

//! \copydetails  boost::crc_basic::get_final_xor_value
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_final_xor_value
(
) const
{
    return final_xor_value;
}

//! \copydetails  boost::crc_basic::get_reflect_input
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
bool
BOOST_CRC_OPTIMAL_NAME::get_reflect_input
(
) const
{
    return reflect_input;
}

//! \copydetails  boost::crc_basic::get_reflect_remainder
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
bool
BOOST_CRC_OPTIMAL_NAME::get_reflect_remainder
(
) const
{
    return reflect_remainder;
}

//! \copydetails  boost::crc_basic::get_interim_remainder
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_interim_remainder
(
) const
{
    // Interim remainder should be _un_-reflected, so we have to undo it.
    return reflect_i_type::reflect_q( rem_ ) &
     detail::low_bits_mask_c<bit_count>::value;
}

/** Changes the interim polynomial remainder to \a new_rem, purging any
    influence previously submitted input has had.  The value of the
    2<sup>i</sup> bit is the value of the coefficient of the polynomial's
    x<sup>i</sup> term.

    \param[in] new_rem  The (unaugmented) state of the polynomial remainder
      starting from this point, with no output processing applied.  Defaults to
      <code>this-&gt;get_initial_remainder()</code> if omitted.

    \post  <code><var>new_rem</var> == this-&gt;get_interim_remainder()</code>
    \post  <code>((this-&gt;get_reflect_remainder() ?
      REFLECT(<var>new_rem</var>) : <var>new_rem</var>) ^
      this-&gt;get_final_xor_value()) == this-&gt;checksum()</code>
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::reset
(
    value_type  new_rem  // = initial_remainder
)
{
    rem_ = reflect_i_type::reflect_q( new_rem );
}

/** \copydetails  boost::crc_basic::process_byte

    \note  Any modulo-2 polynomial divisions may use a table of pre-computed
      remainder changes (as XOR masks) to speed computation when reading data
      byte-wise.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::process_byte
(
    unsigned char  byte
)
{
    process_bytes( &byte, sizeof(byte) );
}

/** \copydetails  boost::crc_basic::process_block

    \note  Any modulo-2 polynomial divisions may use a table of pre-computed
      remainder changes (as XOR masks) to speed computation when reading data
      byte-wise.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::process_block
(
    void const *  bytes_begin,
    void const *  bytes_end
)
{
    process_bytes( bytes_begin, static_cast<unsigned char const *>(bytes_end) -
     static_cast<unsigned char const *>(bytes_begin) );
}

/** \copydetails  boost::crc_basic::process_bytes

    \note  Any modulo-2 polynomial divisions may use a table of pre-computed
      remainder changes (as XOR masks) to speed computation when reading data
      byte-wise.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::process_bytes
(
    void const *   buffer,
    std::size_t  byte_count
)
{
    rem_ = crc_table_type::crc_update( rem_, static_cast<unsigned char const
     *>(buffer), byte_count );
}

//! \copydetails  boost::crc_basic::checksum
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::checksum
(
) const
{
    return ( reflect_o_type::reflect_q(rem_) ^ get_final_xor_value() )
     & detail::low_bits_mask_c<bit_count>::value;
}

/** Updates the interim remainder with a byte's worth of altered-CRC-division
    steps.  The bits within the byte are processed from the highest place down
    if <code>this-&gt;get_reflect_input()</code> is \c false, and lowest place
    up otherwise.  This function is meant to present a function-object interface
    to code that wants to process a stream of bytes with
    <code>std::for_each</code> or similar range-processing algorithms.  Since
    some of these algorithms takes their function object by value, make sure to
    copy back the result to this object so the updates can be remembered.

    \param[in] byte  The new input byte.

    \post  The interim remainder is updated though \c CHAR_BIT modulo-2
      polynomial divisions, where the division steps are altered for unaugmented
      CRCs.

    \note  Any modulo-2 polynomial divisions may use a table of pre-computed
      remainder changes (as XOR masks) to speed computation when reading data
      byte-wise.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::operator ()
(
    unsigned char  byte
)
{
    process_byte( byte );
}

/** Computes the checksum of all the submitted bits since construction or the
    last call to #reset.  The checksum will be the raw checksum, i.e. the
    (interim) remainder after all the modulo-2 polynomial division, plus any
    output processing.  This function is meant to present a function-object
    interface to code that wants to receive data like
    <code>std::generate_n</code> or similar data-processing algorithms.  Note
    that if this object is used as a generator multiple times without an
    intervening mutating operation, the same value will always be returned.

    \return  <code>(this-&gt;get_reflect_remainder() ?
      REFLECT(this-&gt;get_interim_remainder()) :
      this-&gt;get_interim_remainder()) ^ this-&gt;get_final_xor_value()</code>

    \note  Since checksums are meant to be compared, any higher-placed bits
      (when the bit-length of #value_type exceeds #bit_count) will be set to 0.
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::operator ()
(
) const
{
    return checksum();
}


//  CRC computation function definition  -------------------------------------//

/** Computes the polynomial remainder of a CRC run, assuming that \a buffer and
    \a byte_count describe a memory block representing the polynomial dividend.
    The division steps are altered so the result directly gives a checksum,
    without need to augment the memory block with scratch-space bytes.  The
    first byte is considered the highest order, going down for subsequent bytes.

    \pre  0 \< \a Bits \<= \c std\::numeric_limits\<uintmax_t\>\::digits

    \tparam Bits  The order of the modulo-2 polynomial divisor.  (\e Width from
      the RMCA)
    \tparam TruncPoly  The lowest coefficients of the divisor polynomial.  The
      highest-order coefficient is omitted and always assumed to be 1.
      (\e Poly from the RMCA)
    \tparam InitRem  The (unaugmented) initial state of the polynomial
      remainder.  (\e Init from the RMCA)
    \tparam FinalXor  The (XOR) bit-mask to be applied to the output remainder,
      after possible reflection but before returning.  (\e XorOut from the RMCA)
    \tparam ReflectIn  If \c True, input bytes are read lowest-order bit first,
      otherwise highest-order bit first.  (\e RefIn from the RMCA)
    \tparam ReflectRem  If \c True, the output remainder is reflected before the
      XOR-mask.  (\e RefOut from the RMCA)

    \param[in] buffer  The address where the memory block begins.
    \param[in] byte_count  The number of bytes in the memory block.

    \return  The checksum, which is the last (interim) remainder plus any output
      processing.

    \note  Unaugmented-style CRC runs perform modulo-2 polynomial division in
      an altered order.  The trailing \a Bits number of zero-valued bits needed
      to extracted an (unprocessed) checksum is virtually moved to near the
      beginning of the message.  This is OK since the XOR operation is
      commutative and associative.  It also means that you can get a checksum
      anytime.  Since data is being read byte-wise, a table of pre-computed
      remainder changes (as XOR masks) can be used to speed computation.

 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename uint_t<Bits>::fast
crc
(
    void const *  buffer,
    std::size_t   byte_count
)
{
    BOOST_CRC_OPTIMAL_NAME  computer;
    computer.process_bytes( buffer, byte_count );
    return computer.checksum();
}


//  Augmented-message CRC computation function definition  -------------------//

/** Computes the polynomial remainder of a CRC run, assuming that \a buffer and
    \a byte_count describe a memory block representing the polynomial dividend.
    The first byte is considered the highest order, going down for subsequent
    bytes.  Within a byte, the highest-order bit is read first (corresponding to
    \e RefIn = \c False in the RMCA).  Check the other parts of this function's
    documentation to see how a checksum can be gained and/or used.

    \pre  0 \< \a Bits \<= \c std\::numeric_limit\<uintmax_t\>\::digits

    \tparam Bits  The order of the modulo-2 polynomial divisor.  (\e Width from
      the RMCA)
    \tparam TruncPoly  The lowest coefficients of the divisor polynomial.  The
      highest-order coefficient is omitted and always assumed to be 1.
      (\e Poly from the RMCA)

    \param[in] buffer  The address where the memory block begins.
    \param[in] byte_count  The number of bytes in the memory block.
    \param[in] initial_remainder  The initial state of the polynomial
      remainder, defaulting to zero if omitted.  If you are reading a memory
      block in multiple runs, put the return value of the previous run here.
      (Note that initial-remainders given by RMCA parameter lists, as
      \e Init, assume that the initial remainder is in its \b unaugmented state,
      so you would need to convert the value to make it suitable for this
      function.  I currently don't provide a conversion routine.)

    \return  The interim remainder, if no augmentation is used.  A special value
      if augmentation is used (see the notes).  No output processing is done on
      the value.  (In RMCA terms, \e RefOut is \c False and \e XorOut is \c 0.)

    \note  Augmented-style CRC runs use straight-up modulo-2 polynomial
      division.  Since data is being read byte-wise, a table of pre-computed
      remainder changes (as XOR masks) can be used to speed computation.
    \note  Reading just a memory block will yield an interim remainder, and not
      the final checksum.  To get that checksum, allocate \a Bits / \c CHAR_BIT
      bytes directly after the block and fill them with zero values, then extend
      \a byte_count to include those extra bytes.  A data block is corrupt if
      the return value doesn't equal your separately given checksum.
    \note  Another way to perform a check is use the zero-byte extension method,
      but replace the zero values with your separately-given checksum.  The
      checksum must be loaded in big-endian order.  Here corruption, in either
      the data block or the given checksum, is confirmed if the return value is
      not zero.
    \note  The two checksum techniques assume the CRC-run is performed bit-wise,
      while this function works byte-wise.  That means that the techniques can
      be used only if \c CHAR_BIT divides \a Bits evenly!
 */
template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly >
typename uint_t<Bits>::fast
augmented_crc
(
    void const *                 buffer,
    std::size_t                  byte_count,
    typename uint_t<Bits>::fast  initial_remainder  // = 0u
)
{
    return detail::low_bits_mask_c<Bits>::value &
     detail::byte_table_driven_crcs<Bits, TruncPoly, false>::
     augmented_crc_update( initial_remainder, static_cast<unsigned char const
     *>(buffer), byte_count );
}


}  // namespace boost


// Undo header-private macros
#undef BOOST_CRC_OPTIMAL_NAME
#undef BOOST_CRC_PARM_TYPE


#endif  // BOOST_CRC_HPP


/* crc.hpp
2Aph2m4onKohwhqi7YYGoLYb1GuhdgZN241X1XbzxGYWytRjoOfHaruh6C6p7UaDuLy2G10/FgVRt9DZNArJxbaSS/to1w9qu9lBt5IIdVltNygSKVNQpu3mLUo/nKEuoe0GqXZZbTca0P+Ithum7eTHabu5CmW5cDv5JCIIbieRCD9K201ecEc57zxtN7deRNuNNr79g5i2m0hDM3SBUwOV3eCA+veU3bRS9CdV9OHKbjA0oOwGqxvUSYPzEypwwZE8n/T/GTNHd1DZDULIHkpZTfsXVYZV9b2G9ILKbijiKRriF85DLO6hvO2iym5CGPJAZTeHUJDmQspuME+WI5n65/OU3dDcg8puWL1YZjTJ79mGE93hym6QYqjsJpxWx/50fpWQAdFdJzpI/V6c72hYnkyXmTIdDrAiCaq8iZJbffdTVUBMU85Q5oiyuLnvL7jeVZV1abvQk5txF7rl532w/zybyu0HM/5cKncfmEowe8C83KfuQUusxcvwM+9jL7BXpjtKdKT+EB695feVGJZK1e32ZFSkUr1IPk3VpSTFbucdsnF7T4pZ5C1OsuYa/GDbq/AGFDdXojdMomAAwVR/oPgTDVGmbifuPYCZaV2J3Z7uf3agVMDCF1AISEfGH1TChIDUh47NcmvtpwbbidozeiHlDyjezSfh88fyHQm9bqVmco7TRZo/g6ROkvwpdgizvUWwQLp6mJzF9h+kNLM/imr6PKgsxXd+i4ycFEnfPB5wuxk2GoNc5HYoVp7/JhepxBaFlonAT+fjUSVICuQd7SK5n+Hc+3k8wJ1uyxvbGKpIpCS6uBZJm/h8QCroJNTtWqybVN1n65GEdjvVUmPx4C0dShePcXtSIr9E5ih9XVCh8a/imsd2bKaU3aeRVs4w93hF/qakbJMw3EkcWDxsg6ugDfxjkqpNQjRqf4DmuV6NEgyDHCchV4LHjWn+epsiC+1au7jILTSTJq09RuDaqdqkgzbhDbLjJHllK2uYhw8EGgZ8VyoB3/lfoOXsGPpwjP3dmvGyI1p+a05iDG9KsR8UesQDirwvwZth31etS5EcMVJ+b1J+vDAEBS84fE/UES9Pw60/ngtMyspShBjLE414ymF8E1mZUxHi2btyXfZz9MrdQgjWnus8rT7XOSPwXOfv8GrbgOc6f/EmlD3suU7J0e03SPndSfnd/Es5itDNtBjho23xTOV8O3bTaSjcmZXFAOgZxHt4vbKJqah/BbN0Z1r562RHHAYin0py9Foe3coKHhua0IfvTcnVvfZzNTNDCn8rFt7urRxNOvErb5/9HF/cEoUlF1tM/iud5MP9AwsfeNN5hiL0QhZdIbmgLEBWVlJ+nGDMyvJHKkIclVjtzcnCmtH7MlCDHPKYpOCTid1kk4QHSb15nsKOwFOjjzRc4KlReqe8DqBh+vA4uhCdijyo/8lJ6EHo/viLHriEPRWLXYb2h9jQ/hAb7A9x2B+iaX+wBvtDLPYH6Ax452VjzfQ6pQv2I5VTQ3vBM/vP7wU/azqPkG3uE/yrHuMMZwmXRfrepWwEKYXVwb4QSwk6HCV+s5C8o7Yx+mWRrAaNbMEXWp2PXIxsdzYg2eIp2QYQ7At6ohV7UYIxDgWLNbxkt85IbsSXPteZyLXUNpOrqG0lo6kdTYZRO4ZEon0rUXahN46cpnY8+Ybak8iX1J5MPqH2FPI+taeSd6gdS1qonUjeoPZ0sgsPhPanKOtSyEs0aDZ5ntoZ5ClqzyWPU9tJNlN7Eamndi7ZQO3FhKf2MlJK7QJSQO1ispjapWQRtcvIXGrz9PhKWVdFplN7A5mqFmEnrrDJtRi6sx6dY6mzAZ1W6kTJRBJBnVvQeRafut2JV5fIN9SJnzdJB3U+hc4PqPMZdB6mzufR2USd29C5mzqpRoE/UWcjOp+jTlQmQH5BnXjoSDZTJ4pR0+MrWmRUJkAqaATqOCDF1IkP6JF86jyJzoXUiZyHpFNnBzqnUydB583U2UnrT51U28BY6kTVL8RKnfgiAomgTnyPhZzdgU76YOA31IkrSdJBnfi6F/mAOnGSJYd3qEVGzVukkUagyBTZQZ3R6Pwjdcag87fUGYvOx6kzDp0Sdcajs4Y6J6GzgjrxFWhSTJ1T0JlPnVPRuZA6E9GZTp3T0TmdOlPQeTN1zkbntdSZgc6xWpHnom8ojXCiU0+dKGxLTuMZ785cdHZS52J0fkqdy9D53suIJOYCutn5PDnSHkEVVkQ5yZ9fxh0nvp89WQ15ioWY7BFT1JBNLGSKPSJXDamiIeum2qctpiEuUoQhF8jNUo86WGAdY4+Yqia2M3RWe0SiGnIdC4m2R0xXQ65gITH2iBQ1JIKFxNojZqshp/5OQ+LsERlqyKcsJN4eMVcNeYeFJNojlqkhe1jIdHtEgRryIgtJsUcUqyG/ZCGz7RGlasgjLCTDHlGmhgg0ZN1c+zReJcEKDAlKvaDmA2NC69jG00cmtsr7r+GArdtbywfL3rzHZU4yxjfdgNtQN+f3BYkmZ6Lk0YGg5NH8ZzTJI99vFZQ8SpWzUXosolnH+T+Vv629A/ZQafOF026F70z4bpO+wTh6Zn1jUA5Jx5EhiEOVQ9odIocU/odNpj47AH9yttkzh9ukH4yy/Pt0lheN8f5voUVh/QPhole3KZJGNessW43xFV/LXnF/nCZxweqzKN6IwjGnUWUxJ0yX9bfrhBsh0bW3L9cJ1wzu4Md5ifX2VL0wBgKH377cIFhFr1HcZxzcIRyTFVtj05axjUfbxUZd0+l9OFfyMZv0UBZA8yUUABKdPL0PPxDzzxfJEIH4D0NoM+J/E/DvEb16f0NI/XLwk5ScaZWrTbJXPmpotvevM9l7LQ89A+jrztQCrvJYTTJmZI5L/NIifmGx9y9ZKkT4fnElbO1baF2ivT69+JlBPGMqv+7UC0r8E40jYG3b8ipGij5juVlsNxhalXj38eGwSI33HIHoLWAvQrsDwqzgmApm4tFNkQ1Rm9J0Dem6TWl6QNuQrhebDWILRX4ogBxoHoClUDqxWS+26BHqdwGoLQwGGgUL2KLD2IZQHLvAeh7MU2AeB7MZTD2YDWB4rMPsn3ZIsx/tAJuATcDuBLsT7C6wu8DuBrsb7F6we8HuA7vPY8TXSDlDl6FXo4aClW4D0wGmF0McpiVLYW+HJQx1s9qrIdjnQikC5NBgPfzNfZ4NSX1qG8QH22DoD6de6IN8F0djvqc/AEqbo2l9tTY5w9okAdtk2UjaJgi8pQzcj4N5HcymNMPEow3pBvFrSr1vKPX+FoIay6bCBNvqa4CkrdAQArklBA6Agm32tUH8BotsecgFnDoctxWsGDBxYCaBmQImEUwKmKxo2jaxQOtYsGPAjgE7GuxosK1gW8E2g20G2wS2CWwj2MbwtmE0KoVfHkw9mCejQ9omzQClDmkL6g9vh9CwsLb7T/ETWaGMxKwxkm89aUoIJ2GLbHofFlW84Br5QBPV+UI1vljxSqs8tBY4MH4c9Y/zOPqozIkJftny1t0oGK529KGCF8uuTPNEr4qZdL1Oj1dNJaPJaXDm9UQ8A2j0/PASXfEojkspMZDOJ+kSGlw99WEvVcuZ5mcRWs42Tcw2nz46sXXIW9JQDAn7lIuvoY0im38VvP8MTnr/OUxz5UtBlTslenK4PnxnSqVo+bFsj/Wt3WGusJAkipIpNMlvsvwl0+ySv4WNvy7N1ij2t1eOdJWYQnUJARFuEZNRjRDHx7qIH88yIOwYlWLlIwO6UYZS8WII0GHAeWpFhSH4/EgMrETzqA5dM2Q5FL84F7+koK4Nf2aOfwothiusgts1dUaaLqMUF1nJysCPg/KuO+giOegny34ZrBjOU2Q+BAR1eZ6FBsmTIv2fkdvCwj9j4XKL/63Q/pflyslGKbLi3CuoGglSE8Nx+ZpSgYHyn7dQ0dSMPpT/fIDKf1pl56SFsjN+IYlGLrLfdJ74Jwq1zo63ZjtL+ouXQSbhsqxOz+x4I9ONAFCTUJYVpVgV/nZxQ/xkhY+08/GT193gmbpONv9dmhtvRjHWDX83csIVTI519t9NZA6nOpaCw78Li61qO1AFWW2NBTL11603YhkEq7zALC80Jy0wCRG0ak1ZC17bDp3TP0R1yJjXXSZpllG6z5y9wJmbl593zz4jpxxhLV5k+aZxQRY+WWOBbrJR3id+ttFLovjbVN0IRZaNOjCpVvyJw58p+JOCP078WYY/ZR4Jp9QM4Yj7GH+bvM9LjLzFbwA+gOk9c6wZQo/4mYWPlffZTni/0vMmaYxnjvFOoRd4NR/ZMCY1Qzh7T26T3Hb6hNhkTXjX1rhQfheYPsTpUu8Uznr9mAYwGe8Seu/2ZSuaeqXByqiXoc9txZk8TNkdDCZ2snNwwz32oSjfUAHVRGHGb8UvxmviHVHeLyKZCMet4vQpCj9Fe6Z8XMJB3jqHN80RRmaVdPtNWSXf+w1ZJT3KqN3YxaNEcySsW/yjyJP/ERCZeAGcEj56PUDrmSp5EUPqAQBFTgoCaSiLCJM+XabCpATxfvCEovj/QaVPVTkMvGneDgU3QcHflo3ae08l5uJtVP51CwwZWPnge7P05dngo7Oqbh3biaQlJmFayWC6SaUKksA/5rz3XgWDlN+hpJm0M7cpkDYpHxZ0FLema5pi9sxOxHSo4whPSSdDGZpsJ6AYkEk3fjcOp8j5kiWe2TpEMFAN8wIxuRE6cr8QQSJHwIBDD54VMtmJA00lHIoRw1SQaVoAyV9nAk2foWxE2NTCHqGa+za0UeARqjHkg8cDTTHPHEdR+pJ16jNUr9PICTgaP92m46/Ao1h8hAqn2QGPUEEMfQGvRC+2f3PPkCYI1l6ien+rwhRG82ZykLoDL1GtOERZI75ENRidwZeo8KxVfYlKr75ElXBQmmd0K9pTVNxBOmXhU1Tz2FNUvmQFD9j/jaeoRmUh01xAmvYpSuAtqhsw33xTkRTjH4firH2YnXyOBuX3kYa3tHzxTaohAbL5o+Sma9Ax4FGq4AWxHLnaaj8lDLefWzeUXf3SSzEwiB5kHoNoUqh++Y3rRpLUx7Td0Imf090QzDMxeCK1W9Duj1nceEYC7Rz9CqoIK7J7191qP8VbAP2QnCwX+WcjLSjp+bl2q4v4EZd6uYudWFGdQpDqWvu5yjhy8Oe4f8JcC8GFcG71EpgPdWc0RKo31lqock16iWw60lyFoUpYM80LsnJc2B+jF2RJ+WZ6RQyPLyFhdFK+2eIuoc1ksh/k90g6/ytsahN7H7C4UVuO/ZSlHlXA2c9ZHr4PbKzKlawqvns0vhe4AxYiXf5TeiAXrY6dnlT6Fth6E8fHK3OMVUPk4Q16RYfaas2WvXhPYRlUMU89do9sUiLDLkldVkAHbxlKO7bhryqg8wz97aK/5wvoUIEeJqDzfYV6SWrxzwLrpe+34Ecjeg8VPxrh3VjtktSgIUEBHQ8e7f8PCOiEi+dQMaQdeJ0yKKRz9/lCOjeHC+kErmBRNTX04iu7hmUKXMNaIrkx2N5sqf8Gv2lH5aHgTusgehEr+Xp2EYveL5aosIRGRkZeRlhGcHpj/1G8iMVEd9SLWM18fEaGehHrfnqtCsF9RUExG9/dAbfON29QmODOjECU3mcbdFHBHfcJixQdxKgK7ujpvakLCu58SW8a0VvXvhOmi0ruIN7X6a0oSgLfdtNFJXeeoFjOl9ypNoWJg6xBsAtL7tA7U6rkTnrAHeezmy4vuXOF6XKSO9+rkjv/UiV3/qlK7nykSu78Q5XceVuV3HkzCimEfYMLiO7giGOiO3v+QaeNENEdHIeqYI6hD28Jh4juPEFFd0IgPj0HJVoRIrrzlQ5vVVRql7hOceitwzlRFd3J00R3Hrmk6I56k/4iEjwWjyNcdueZ/xnZnRfwY9eJS8vuVGgXsw6FyO5cqzDZHVTI8O/J7uSfpV/6mezO82oml5fduS5cdgeST2cXr6b9KNmdDnr1ivYWX9tA4Z0v/wZdxYdK0OjVq07a5G069erVX7SrV7eowjshV68eCwrvMIZ4ccGdd46yq1cTLi+4o1HFh2+8XUZw5zcAaPhYntUrZ/X53tL9lwR3Vu0MEdxBlv6fF9yhA/K/T3CHoruU4I4GcHnBnWF424qVh8oIqDet9qtCO49rN61wz9hCJ+6LCO3wVGgHAS4utOMMuWjl+v+K0M5u1MdzAaEdJMXlhXZWBK9Y5Z4ntJMyJ/he2AF8L0yT2qFM6qJSO1TzWpjUDg6h/yGpneDsgVI7z9B7P2FSOwhwIamdx7w/QmrHGYbv35fa+Rrf77qE1M4wL86Xl5Ta8cMK+0dK7TzXfV5pkY/Q+1PoILN/CQAv0LDzpXYsIfI6r9N601ke70+hI8ri/mf3BZfCA6R4nlrJHgi7asJMbmzcTC4TzB/AfA9Gd/VMLh3MeogLLuqpSijxHVx6R5NP3YGl9wPgHNLinw1rbJFPdJGbTiiKS+4lM43IL8fuxdljNc4P9P5wBGDwj5DTYqGLD3GSXDw4LYrl8sQiMxeiC67EXNyKRxHtsAZCrRewAqYfCdUnhu4NZn+unp6U+ofiGh/IgHgcHaQTEja5SO0T2C701aHbFCVMSyt9G+U4faTpfYRSM7YWE8x4JaRXVYKMJKfqQ1WBPMuFqQIZQY4HoslqcPo/vKgKkEiqAuRwFvnZ12q5UAVIpFHH35xFLBjmVEY1sqOTIar6FEcHPtrQwVHNwGPIxnpsxQ7JRPKDpbqAXhB/jaYX5MDXgdrlyM30pM7i9iLYUfHTjd6vovhCf6Tn1xDAFVnWRoKZZ4UfVxz8LMHjuigw8/EELwdP8JZC0NqiFPhZ44Sfdcvgp6YMIlbiqd5aPNWrxFO9jWUeemPBQ98XuFPYCqNqjnzU+xUqmrsiNL+NUZ51Vs9G653CN+KnFj5e9qLiuKHyaOkKzzqjZ6NxDrDcVlQ4Nwi/+aSlzxFO5y5Zmt/0Ks4yCUcS3log79MARjdcQQG8JAxFhnAqz4eabCgdqO4rA/wvBgQpxXMTUFXqBqD2VjweYrTSTop4M27/oqBhEq2aMuzggHCRXHw2CuGcz9KztX6dMKinFi9o6IQhYr9eiO1Jma3jR5foyQ0AWqKDsRGPafLsLXjGHtPJmh2xQ7MPZs3O7jq5yFo/Hl8M1F+X1zx7ipFzQ9lyyMMPYf4wAvQhX2yhG5vuh278zIZANx5LZj/EzgbjHwrtzljSMM0241SwH+oC3fo/6n6cZptX/SHdGo9FzVlUdA3Hnd9CXgxgvFCPTdqg9dgrOgM9NkBpOc28TeSv2mbir8RrQOMfhzVZkfn0ORSsy5Mi8RG0NOMFP1jT77lZcqZ1yAE+EzFVm3el/v3unXH4nenawR2bovifDG7kJ4rNOrFFd/uX5ZG3f16p139xewu4msDVfHs7tKRPJxy1Hbi9nR+EmwalXH/6A9l7zwW+Z9Gj/7nx1iGteHouDEJVh6c/3Wflsk5/qorRFcRHG5jrU8O792jibWF/yjWPAx9gCJEGHke0M1Qi8DrcMQeOa9Sjsgs94WgVYsgttQF+eXAj5Ze+X1CqU9k1exM/xn4K2OqQINjzDMxfHvZ+Y7IS9nxjhAGfs8GTNUc7O0tyki/q6GQq99pP8dPCn240e+jrjD+pxc4f8mqjGm6h4XLLgNcZ8XpiSL1HKKHHVPj3X/1e/yXsNi72vb7slgt/r6+/mX4brr2Ffa83ov04hDWC6bj5R36vR+SX/16PUBf/Xq/iWAnWIjBzwcwGMx3MVDCTwcRjHf5bvtdTaihY6QYwj4PZhiH/P/9eb54a+F7/uu2i3+utNtomCLwlDtyzwZTaLvO9HqF/3Pd6ivff+l6v4m6EMrSCOQKmDUw7GAKmC4xh6sz/pu/1jEax8BsPZiqYjKkhbfNf/l6vcRh8PypHYzHAXxxWYBzHHgwwjvseZIyjSs6kzAVm/TGwZBxF/hyESVdhsvCu5kZgIfbWSoOUGeQkKtOBUQ98xwmMhxh2qmzF3cPHIu8wAe9ohhXcUGQeJRw5+qDGPS7BPG4LYx4UIt83lVPfmVGm4fsIgZcP9MqRkjFkZyHO2ZDB5HZ2iN75Segher7vCY/qb9GVQkLfsIjQZ2tc8rctkRhOemA93OMw6fAGmBfXonLzElT+GwKLkuHfkkGAgKU5D0LstPrpd/SFv6FHePR1BrL9F8zzxYGmnojnoQq6N56E372IQpgsDqVBeNmhzym/A7Muj8UphPFTbF8Du8VpCEyW/haQ5OAnEgkKWhwPqweUoJeELvKcUa2RVuUybR0lKwtadA2I7h1juPI5qDf5GMC0Gr/Tf6Ea46dN76AFYuMgJ/n+A3wUIW9sY15KOBDpWkuPWaKcZNf9Ct7eNimjXrKqkyNuFapwqbOjAtYSs6Bo9FmGslzFuchJXlPw80qnbJIHQf9yLiAfFGI3wVcBFKGDZKwIu60Bm5c1gGT8GtyznF2NuQrX0x2CmQbduYYGDVVvE7BSKKOceDk60j8WX4ldsEhyLpIX5ErOXHmBcYHkNJLDUHzi0kjGcsrCj1m2E/guCnmiKjAwbqzC5Yy/ykV+B7kXR+vxySIy43m8wpCH71vNIcsBm1JW6iJXr8GqRYvzjIqUlis7YvPypJpF+M3V47A6YSi5ih234W0G9lxTBltexqrLyzYXObmJbmvxmbiZkG+erRFm3suvJ/BJ6M8qA0V+sJKtJ/BjWvBJaLaeeC0ItoiB+e8LDPleGPLVwaefA0M+Wh3yoe9AT7M3bbjAO88fVSrsExR759lC33luWHyHcqlnnq8NFuqNdQq7ZTPgmWdDAMR/c/gzz56roKd9Qr+U4TPPhuZIjj3yfGSd9q2XrGJYw1/q8ULnaOG24KAeJGUYm1NMXEAzt5yKjyxH7H4yIWx/gRdpcuQz/A3IF0jR04riKdO5yL7HsNJSOj6XMRxiXE5S9ixlTc3pJh1si4KDBwZhbY2J4wfhBfp/NeDavMjINaeZuNBnZGEQAiDGtERiATFemUKqcOicx6JwzyOfsffz46huRYreDOjld6haRH+knGaEstGtvJayRYdofaXaEAgyRgynT6ZpbGLb2QuxCcYYw0tISi9UPuiyWJ2cElPe3pcA0lPdfuoFqlPcvFRy9C0Bmpl7OBMf1eLo5lI=
*/