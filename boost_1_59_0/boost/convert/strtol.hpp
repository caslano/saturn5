// Copyright (c) 2009-2020 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_STRTOL_CONVERTER_HPP
#define BOOST_CONVERT_STRTOL_CONVERTER_HPP

#include <boost/convert/base.hpp>
#include <boost/math/special_functions/round.hpp>
#include <limits>
#include <climits>
#include <cstdlib>

namespace boost { namespace cnv
{
    struct strtol;
}}

/// @brief std::strtol-based extended converter
/// @details The converter offers a fairly decent overall performance and moderate formatting facilities.

struct boost::cnv::strtol : public boost::cnv::cnvbase<boost::cnv::strtol>
{
    using this_type = boost::cnv::strtol;
    using base_type = boost::cnv::cnvbase<this_type>;

    using base_type::operator();

    private:

    friend struct boost::cnv::cnvbase<this_type>;

    template<typename string_type> void str_to(cnv::range<string_type> v, optional<   int_type>& r) const { str_to_i (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional<  sint_type>& r) const { str_to_i (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional<  lint_type>& r) const { str_to_i (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional< llint_type>& r) const { str_to_i (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional<  uint_type>& r) const { str_to_i (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional< usint_type>& r) const { str_to_i (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional< ulint_type>& r) const { str_to_i (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional<ullint_type>& r) const { str_to_i (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional<   flt_type>& r) const { str_to_d (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional<   dbl_type>& r) const { str_to_d (v, r); }
    template<typename string_type> void str_to(cnv::range<string_type> v, optional<  ldbl_type>& r) const { str_to_d (v, r); }

    template <typename char_type> cnv::range<char_type*> to_str (   int_type v, char_type* buf) const { return i_to_str(v, buf); }
    template <typename char_type> cnv::range<char_type*> to_str (  uint_type v, char_type* buf) const { return i_to_str(v, buf); }
    template <typename char_type> cnv::range<char_type*> to_str (  lint_type v, char_type* buf) const { return i_to_str(v, buf); }
    template <typename char_type> cnv::range<char_type*> to_str ( ulint_type v, char_type* buf) const { return i_to_str(v, buf); }
    template <typename char_type> cnv::range<char_type*> to_str ( llint_type v, char_type* buf) const { return i_to_str(v, buf); }
    template <typename char_type> cnv::range<char_type*> to_str (ullint_type v, char_type* buf) const { return i_to_str(v, buf); }
    template <typename char_type> cnv::range<char_type*> to_str ( dbl_type v, char_type* buf) const;

    template<typename char_type, typename in_type> cnv::range<char_type*> i_to_str (in_type, char_type*) const;
    template<typename string_type, typename out_type> void                str_to_i (cnv::range<string_type>, optional<out_type>&) const;
    template<typename string_type, typename out_type> void                str_to_d (cnv::range<string_type>, optional<out_type>&) const;

    static double adjust_fraction (double, int);
    static int           get_char (int v) { return (v < 10) ? (v += '0') : (v += 'A' - 10); }
};

template<typename char_type, typename Type>
boost::cnv::range<char_type*>
boost::cnv::strtol::i_to_str(Type in_value, char_type* buf) const
{
    // C1. Base=10 optimization improves performance 10%

    using unsigned_type = typename std::make_unsigned<Type>::type;

    char_type*      beg = buf + bufsize_ / 2;
    char_type*      end = beg;
    bool const   is_neg = std::is_signed<Type>::value && in_value < 0;
    unsigned_type value = static_cast<unsigned_type>(is_neg ? -in_value : in_value);
    int            base = int(base_);

    if (base == 10) for (; value; *(--beg) = int(value % 10) + '0', value /= 10); //C1
    else            for (; value; *(--beg) = get_char(value % base), value /= base);

    if (beg == end) *(--beg) = '0';
    if (is_neg)     *(--beg) = '-';

    return cnv::range<char_type*>(beg, end);
}

inline
double
boost::cnv::strtol::adjust_fraction(double fraction, int precision)
{
    // C1. Bring forward the fraction coming right after precision digits.
    //     That is, say, fraction=0.234567, precision=2. Then brought forward=23.4567
    // C3. INT_MAX(4bytes)=2,147,483,647. So, 10^8 seems appropriate. If not, drop it down to 4.
    // C4. ::round() returns the integral value that is nearest to x,
    //     with halfway cases rounded away from zero. Therefore,
    //          round( 0.4) =  0
    //          round( 0.5) =  1
    //          round( 0.6) =  1
    //          round(-0.4) =  0
    //          round(-0.5) = -1
    //          round(-0.6) = -1

    int const tens[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };

    for (int k = precision / 8; k; --k) fraction *= 100000000; //C3.

    fraction *= tens[precision % 8]; //C1

//  return ::rint(fraction); //C4
    return boost::math::round(fraction); //C4
}

template <typename char_type>
inline
boost::cnv::range<char_type*>
boost::cnv::strtol::to_str(double value, char_type* buf) const
{
    char_type*   beg = buf + bufsize_ / 2;
    char_type*   end = beg;
    char_type*  ipos = end - 1;
    bool is_negative = (value < 0) ? (value = -value, true) : false;
    double     ipart = std::floor(value);
    double     fpart = adjust_fraction(value - ipart, precision_);
    int    precision = precision_;
    int const   base = 10;

    for (; 1 <= ipart; ipart /= base)
        *(--beg) = get_char(int(ipart - std::floor(ipart / base) * base));

    if (beg == end) *(--beg) = '0';
    if (precision)  *(end++) = '.';

    for (char_type* fpos = end += precision; precision; --precision, fpart /= base)
        *(--fpos) = get_char(int(fpart - std::floor(fpart / base) * base));

    if (1 <= fpart)
    {
        for (; beg <= ipos; --ipos)
            if (*ipos == '9') *ipos = '0';
            else { ++*ipos; break; }

        if (ipos < beg)
            *(beg = ipos) = '1';
    }
    if (is_negative) *(--beg) = '-';

    return cnv::range<char_type*>(beg, end);
}

template<typename string_type, typename out_type>
void
boost::cnv::strtol::str_to_i(cnv::range<string_type> range, boost::optional<out_type>& result_out) const
{
    using     uint_type = unsigned int;
    using unsigned_type = typename std::make_unsigned<out_type>::type;
    using    range_type = cnv::range<string_type>;
    using      iterator = typename range_type::iterator;

    iterator             s = range.begin();
    uint_type           ch = *s;
    bool const is_negative = ch == '-' ? (ch = *++s, true) : ch == '+' ? (ch = *++s, false) : false;
    bool const is_unsigned = std::is_same<out_type, unsigned_type>::value;
    uint_type         base = uint_type(base_);

    /**/ if (is_negative && is_unsigned) return;
    else if ((base == 0 || base == 16) && ch == '0' && (*++s == 'x' || *s == 'X')) ++s, base = 16;
    else if (base == 0) base = ch == '0' ? (++s, 8) : 10;

    unsigned_type const    max = (std::numeric_limits<out_type>::max)();
    unsigned_type const   umax = max + (is_negative ? 1 : 0);
    unsigned_type const cutoff = umax / base;
    uint_type     const cutlim = umax % base;
    unsigned_type       result = 0;

    for (; s != range.sentry(); ++s)
    {
        ch = *s;

        /**/ if (std::isdigit(ch)) ch -= '0';
        else if (std::isalpha(ch)) ch -= (std::isupper(ch) ? 'A' : 'a') - 10;
        else return;

        if (base <= ch || cutoff < result || (result == cutoff && cutlim < ch))
            return;

        result *= base;
        result += ch;
    }
    result_out = is_negative ? -out_type(result) : out_type(result);
}

template<typename string_type, typename out_type>
void
boost::cnv::strtol::str_to_d(cnv::range<string_type> range, optional<out_type>& result_out) const
{
    // C1. Because of strtold() currently only works with 'char'
    // C2. strtold() does not work with ranges.
    //     Consequently, we have to copy the supplied range into a string for strtold().
    // C3. Check if the end-of-string was reached -- *cnv_end == 0.

    using range_type = cnv::range<string_type>;
    using    ch_type = typename range_type::value_type;

    size_t const  sz = 128;
    ch_type  str[sz] = {0}; std::strncpy(str, &*range.begin(), (std::min)(sz - 1, range.size()));
    char*    cnv_end = 0;
    ldbl_type result = strtold(str, &cnv_end);
    bool        good = result != -HUGE_VALL && result != HUGE_VALL && *cnv_end == 0; //C3
    out_type     max = (std::numeric_limits<out_type>::max)();

    if (good && -max <= result && result <= max)
        result_out = out_type(result);
}

#endif // BOOST_CONVERT_STRTOL_CONVERTER_HPP

/* strtol.hpp
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
*/