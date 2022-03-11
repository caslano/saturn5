// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_STRTOL_CONVERTER_HPP
#define BOOST_CONVERT_STRTOL_CONVERTER_HPP

#include <boost/convert/base.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/math/special_functions/round.hpp>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <climits>

#if __GNUC__ == 4 && __GNUC_MINOR__ <= 2
namespace std
{
    using ::strtold; // Tests indicated that gcc-4.2.1 does not have 'std::strtold'
}
#endif

namespace boost { namespace cnv
{
    struct strtol;
}}

/// @brief std::strtol-based extended converter
/// @details The converter offers a fairly decent overall performance and moderate formatting facilities.

struct boost::cnv::strtol : public boost::cnv::cnvbase<boost::cnv::strtol>
{
    typedef boost::cnv::strtol             this_type;
    typedef boost::cnv::cnvbase<this_type> base_type;

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

    typedef typename boost::make_unsigned<Type>::type unsigned_type;

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
    char_type*         beg = buf + bufsize_ / 2;
    char_type*         end = beg;
    char_type*        ipos = end - 1;
    bool const is_negative = (value < 0) ? (value = -value, true) : false;
    double           ipart = std::floor(value);
    double           fpart = adjust_fraction(value - ipart, precision_);
    int          precision = precision_;
    int const         base = 10;

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
    using unsigned_type = typename boost::make_unsigned<out_type>::type;
    using    range_type = cnv::range<string_type>;
    using      iterator = typename range_type::iterator;

    iterator             s = range.begin();
    uint_type           ch = *s;
    bool const is_negative = ch == '-' ? (ch = *++s, true) : ch == '+' ? (ch = *++s, false) : false;
    bool const is_unsigned = boost::is_same<out_type, unsigned_type>::value;
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

    typedef cnv::range<string_type>      range_type;
    typedef typename range_type::value_type ch_type;

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