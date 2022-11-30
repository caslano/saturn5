// ----------------------------------------------------------------------------
// parsing.hpp :  implementation of the parsing member functions
//                      ( parse, parse_printf_directive)
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_PARSING_HPP
#define BOOST_FORMAT_PARSING_HPP


#include <boost/format/format_class.hpp>
#include <boost/format/exceptions.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/core/ignore_unused.hpp>

namespace boost {
namespace io {
namespace detail {

#if defined(BOOST_NO_STD_LOCALE)
    // streams will be used for narrow / widen. but these methods are not const
    template<class T>
    T& const_or_not(const T& x) {
        return const_cast<T&> (x);
    }
#else
    template<class T>
    const T& const_or_not(const T& x) {
        return x;
    }
#endif

    template<class Ch, class Facet> inline
    char wrap_narrow(const Facet& fac, Ch c, char deflt) {
        return const_or_not(fac).narrow(c, deflt);
    }

    template<class Ch, class Facet> inline
    bool wrap_isdigit(const Facet& fac, Ch c) {
#if ! defined( BOOST_NO_LOCALE_ISDIGIT )
        return fac.is(std::ctype<Ch>::digit, c);
# else
        ignore_unused(fac);
        using namespace std;
        return isdigit(c) != 0;
#endif
    }

    template<class Iter, class Facet>
    Iter wrap_scan_notdigit(const Facet & fac, Iter beg, Iter end) {
        using namespace std;
        for( ; beg!=end && wrap_isdigit(fac, *beg); ++beg) ;
        return beg;
    }


    // Input : [start, last) iterators range and a
    //          a Facet to use its widen/narrow member function
    // Effects : read sequence and convert digits into integral n, of type Res
    // Returns : n
    template<class Res, class Iter, class Facet>
    Iter str2int (const Iter & start, const Iter & last, Res & res,
                 const Facet& fac)
    {
        using namespace std;
        Iter it;
        res=0;
        for(it=start; it != last && wrap_isdigit(fac, *it); ++it ) {
            char cur_ch = wrap_narrow(fac, *it, 0); // cant fail.
            res *= 10;
            res += cur_ch - '0'; // 22.2.1.1.2.13 of the C++ standard
        }
        return it;
    }

    // auxiliary func called by parse_printf_directive
    // for centralising error handling
    // it either throws if user sets the corresponding flag, or does nothing.
    inline void maybe_throw_exception(unsigned char exceptions,
                                      std::size_t pos, std::size_t size)
    {
        if(exceptions & io::bad_format_string_bit)
            boost::throw_exception(io::bad_format_string(pos, size) );
    }


    // Input: the position of a printf-directive in the format-string
    //    a basic_ios& merely to use its widen/narrow member function
    //    a bitset'exceptions' telling whether to throw exceptions on errors.
    // Returns:
    //  true if parse succeeded (ignore some errors if exceptions disabled)
    //  false if it failed so bad that the directive should be printed verbatim
    // Effects:
    //  start is incremented so that *start is the first char after
    //     this directive
    //  *fpar is set with the parameters read in the directive
    template<class Ch, class Tr, class Alloc, class Iter, class Facet>
    bool parse_printf_directive(Iter & start, const Iter& last,
                                detail::format_item<Ch, Tr, Alloc> * fpar,
                                const Facet& fac,
                                std::size_t offset, unsigned char exceptions)
    {
        typedef typename basic_format<Ch, Tr, Alloc>::format_item_t format_item_t;

        fpar->argN_ = format_item_t::argN_no_posit;  // if no positional-directive
        bool precision_set = false;
        bool in_brackets=false;
        Iter start0 = start;
        std::size_t fstring_size = last-start0+offset;
        char mssiz = 0;

        if(start>= last) { // empty directive : this is a trailing %
                maybe_throw_exception(exceptions, start-start0 + offset, fstring_size);
                return false;
        }

        if(*start== const_or_not(fac).widen( '|')) {
            in_brackets=true;
            if( ++start >= last ) {
                maybe_throw_exception(exceptions, start-start0 + offset, fstring_size);
                return false;
            }
        }

        // the flag '0' would be picked as a digit for argument order, but here it's a flag :
        if(*start== const_or_not(fac).widen( '0'))
            goto parse_flags;

        // handle argument order (%2$d)  or possibly width specification: %2d
        if(wrap_isdigit(fac, *start)) {
            int n;
            start = str2int(start, last, n, fac);
            if( start >= last ) {
                maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
                return false;
            }

            // %N% case : this is already the end of the directive
            if( *start ==  const_or_not(fac).widen( '%') ) {
                fpar->argN_ = n-1;
                ++start;
                if( in_brackets)
                    maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
                return true;
            }

            if ( *start== const_or_not(fac).widen( '$') ) {
                fpar->argN_ = n-1;
                ++start;
            }
            else {
                // non-positional directive
                fpar->fmtstate_.width_ = n;
                fpar->argN_  = format_item_t::argN_no_posit;
                goto parse_precision;
            }
        }

      parse_flags:
        // handle flags
        while (start != last) { // as long as char is one of + - = _ # 0 or ' '
            switch ( wrap_narrow(fac, *start, 0)) {
                case '\'':
                    break; // no effect yet. (painful to implement)
                case '-':
                    fpar->fmtstate_.flags_ |= std::ios_base::left;
                    break;
                case '=':
                    fpar->pad_scheme_ |= format_item_t::centered;
                    break;
                case '_':
                    fpar->fmtstate_.flags_ |= std::ios_base::internal;
                    break;
                case ' ':
                    fpar->pad_scheme_ |= format_item_t::spacepad;
                    break;
                case '+':
                    fpar->fmtstate_.flags_ |= std::ios_base::showpos;
                    break;
                case '0':
                    fpar->pad_scheme_ |= format_item_t::zeropad;
                    // need to know alignment before really setting flags,
                    // so just add 'zeropad' flag for now, it will be processed later.
                    break;
                case '#':
                    fpar->fmtstate_.flags_ |= std::ios_base::showpoint | std::ios_base::showbase;
                    break;
                default:
                    goto parse_width;
            }
            ++start;
        } // loop on flag.

        if( start>=last) {
            maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
            return true;
        }

      // first skip 'asterisk fields' : * or num (length)
      parse_width:
        if(*start == const_or_not(fac).widen( '*') )
            ++start;
        else if(start!=last && wrap_isdigit(fac, *start))
            start = str2int(start, last, fpar->fmtstate_.width_, fac);

      parse_precision:
        if( start>= last) {
            maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
            return true;
        }
        // handle precision spec
        if (*start== const_or_not(fac).widen( '.')) {
            ++start;
            if(start != last && *start == const_or_not(fac).widen( '*') )
                ++start;
            else if(start != last && wrap_isdigit(fac, *start)) {
                start = str2int(start, last, fpar->fmtstate_.precision_, fac);
                precision_set = true;
            }
            else
                fpar->fmtstate_.precision_ =0;
        }

      // argument type modifiers
        while (start != last) {
            switch (wrap_narrow(fac, *start, 0)) {
                case 'h':
                case 'l':
                case 'j':
                case 'z':
                case 'L':
                    // boost::format ignores argument type modifiers as it relies on
                    // the type of the argument fed into it by operator %
                    break;

                // Note that the ptrdiff_t argument type 't' from C++11 is not honored
                // because it was already in use as the tabulation specifier in boost::format
                // case 't':

                // Microsoft extensions:
                // https://msdn.microsoft.com/en-us/library/tcxf1dw6.aspx

                case 'w':
                    break;
                case 'I':
                    mssiz = 'I';
                    break;
                case '3':
                    if (mssiz != 'I') {
                        maybe_throw_exception(exceptions, start - start0 + offset, fstring_size);
                        return true;
                    }
                    mssiz = '3';
                    break;
                case '2':
                    if (mssiz != '3') {
                        maybe_throw_exception(exceptions, start - start0 + offset, fstring_size);
                        return true;
                    }
                    mssiz = 0x00;
                    break;
                case '6':
                    if (mssiz != 'I') {
                        maybe_throw_exception(exceptions, start - start0 + offset, fstring_size);
                        return true;
                    }
                    mssiz = '6';
                    break;
                case '4':
                    if (mssiz != '6') {
                        maybe_throw_exception(exceptions, start - start0 + offset, fstring_size);
                        return true;
                    }
                    mssiz = 0x00;
                    break;
                default:
                    if (mssiz && mssiz == 'I') {
                        mssiz = 0;
                    }
                    goto parse_conversion_specification;
            }
            ++start;
        } // loop on argument type modifiers to pick up 'hh', 'll', and the more complex microsoft ones

      parse_conversion_specification:
        if (start >= last || mssiz) {
            maybe_throw_exception(exceptions, start - start0 + offset, fstring_size);
            return true;
        }

        if( in_brackets && *start== const_or_not(fac).widen( '|') ) {
            ++start;
            return true;
        }

        // The default flags are "dec" and "skipws"
        // so if changing the base, need to unset basefield first

        switch (wrap_narrow(fac, *start, 0))
        {
            // Boolean
            case 'b':
                fpar->fmtstate_.flags_ |= std::ios_base::boolalpha;
                break;

            // Decimal
            case 'u':
            case 'd':
            case 'i':
                // Defaults are sufficient
                break;

            // Hex
            case 'X':
                fpar->fmtstate_.flags_ |= std::ios_base::uppercase;
                BOOST_FALLTHROUGH;
            case 'x':
            case 'p': // pointer => set hex.
                fpar->fmtstate_.flags_ &= ~std::ios_base::basefield;
                fpar->fmtstate_.flags_ |= std::ios_base::hex;
                break;

            // Octal
            case 'o':
                fpar->fmtstate_.flags_ &= ~std::ios_base::basefield;
                fpar->fmtstate_.flags_ |= std::ios_base::oct;
                break;

            // Floating
            case 'A':
                fpar->fmtstate_.flags_ |= std::ios_base::uppercase;
                BOOST_FALLTHROUGH;
            case 'a':
                fpar->fmtstate_.flags_ &= ~std::ios_base::basefield;
                fpar->fmtstate_.flags_ |= std::ios_base::fixed;
                fpar->fmtstate_.flags_ |= std::ios_base::scientific;
                break;
            case 'E':
                fpar->fmtstate_.flags_ |= std::ios_base::uppercase;
                BOOST_FALLTHROUGH;
            case 'e':
                fpar->fmtstate_.flags_ |= std::ios_base::scientific;
                break;
            case 'F':
                fpar->fmtstate_.flags_ |= std::ios_base::uppercase;
                BOOST_FALLTHROUGH;
            case 'f':
                fpar->fmtstate_.flags_ |= std::ios_base::fixed;
                break;
            case 'G':
                fpar->fmtstate_.flags_ |= std::ios_base::uppercase;
                BOOST_FALLTHROUGH;
            case 'g':
                // default flags are correct here
                break;

            // Tabulation (a boost::format extension)
            case 'T':
                ++start;
                if( start >= last) {
                    maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
                    return false;
                } else {
                    fpar->fmtstate_.fill_ = *start;
                }
                fpar->pad_scheme_ |= format_item_t::tabulation;
                fpar->argN_ = format_item_t::argN_tabulation;
                break;
            case 't':
                fpar->fmtstate_.fill_ = const_or_not(fac).widen( ' ');
                fpar->pad_scheme_ |= format_item_t::tabulation;
                fpar->argN_ = format_item_t::argN_tabulation;
                break;

            // Character
            case 'C':
            case 'c':
                fpar->truncate_ = 1;
                break;

            // String
            case 'S':
            case 's':
                if(precision_set) // handle truncation manually, with own parameter.
                    fpar->truncate_ = fpar->fmtstate_.precision_;
                fpar->fmtstate_.precision_ = 6; // default stream precision.
                break;

            // %n is insecure and ignored by boost::format
            case 'n' :
                fpar->argN_ = format_item_t::argN_ignored;
                break;

            default:
                maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
        }
        ++start;

        if( in_brackets ) {
            if( start != last && *start== const_or_not(fac).widen( '|') ) {
                ++start;
                return true;
            }
            else  maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
        }
        return true;
    }
    // -end parse_printf_directive()

    template<class String, class Facet>
    int upper_bound_from_fstring(const String& buf,
                                 const typename String::value_type arg_mark,
                                 const Facet& fac,
                                 unsigned char exceptions)
    {
        // quick-parsing of the format-string to count arguments mark (arg_mark, '%')
        // returns : upper bound on the number of format items in the format strings
        using namespace boost::io;
        typename String::size_type i1=0;
        int num_items=0;
        while( (i1=buf.find(arg_mark,i1)) != String::npos ) {
            if( i1+1 >= buf.size() ) {
                if(exceptions & bad_format_string_bit)
                    boost::throw_exception(bad_format_string(i1, buf.size() )); // must not end in ".. %"
                else {
                  ++num_items;
                  break;
                }
            }
            if(buf[i1+1] == buf[i1] ) {// escaped "%%"
                i1+=2; continue;
            }

            ++i1;
            // in case of %N% directives, dont count it double (wastes allocations..) :
            i1 = detail::wrap_scan_notdigit(fac, buf.begin()+i1, buf.end()) - buf.begin();
            if( i1 < buf.size() && buf[i1] == arg_mark )
                ++i1;
            ++num_items;
        }
        return num_items;
    }
    template<class String> inline
    void append_string(String& dst, const String& src,
                       const typename String::size_type beg,
                       const typename String::size_type end) {
        dst.append(src.begin()+beg, src.begin()+end);
    }

} // detail namespace
} // io namespace



// -----------------------------------------------
//  format :: parse(..)

    template<class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>& basic_format<Ch, Tr, Alloc>::
    parse (const string_type& buf) {
        // parse the format-string
        using namespace std;
#if !defined(BOOST_NO_STD_LOCALE)
        const std::ctype<Ch> & fac = BOOST_USE_FACET( std::ctype<Ch>, getloc());
#else
        io::basic_oaltstringstream<Ch, Tr, Alloc> fac;
        //has widen and narrow even on compilers without locale
#endif

        const Ch arg_mark = io::detail::const_or_not(fac).widen( '%');
        bool ordered_args=true;
        int max_argN=-1;

        // A: find upper_bound on num_items and allocates arrays
        int num_items = io::detail::upper_bound_from_fstring(buf, arg_mark, fac, exceptions());
        make_or_reuse_data(num_items);

        // B: Now the real parsing of the format string :
        num_items=0;
        typename string_type::size_type i0=0, i1=0;
        typename string_type::const_iterator it;
        bool special_things=false;
        int cur_item=0;
        while( (i1=buf.find(arg_mark,i1)) != string_type::npos ) {
            string_type & piece = (cur_item==0) ? prefix_ : items_[cur_item-1].appendix_;
            if( buf[i1+1] == buf[i1] ) { // escaped mark, '%%'
                io::detail::append_string(piece, buf, i0, i1+1);
                i1+=2; i0=i1;
                continue;
            }
            BOOST_ASSERT(  static_cast<unsigned int>(cur_item) < items_.size() || cur_item==0);

            if(i1!=i0) {
                io::detail::append_string(piece, buf, i0, i1);
                i0=i1;
            }
            ++i1;
            it = buf.begin()+i1;
            bool parse_ok = io::detail::parse_printf_directive(
                it, buf.end(), &items_[cur_item], fac, i1, exceptions());
            i1 = it - buf.begin();
            if( ! parse_ok ) // the directive will be printed verbatim
                continue;
            i0=i1;
            items_[cur_item].compute_states(); // process complex options, like zeropad, into params

            int argN=items_[cur_item].argN_;
            if(argN == format_item_t::argN_ignored)
                continue;
            if(argN ==format_item_t::argN_no_posit)
                ordered_args=false;
            else if(argN == format_item_t::argN_tabulation) special_things=true;
            else if(argN > max_argN) max_argN = argN;
            ++num_items;
            ++cur_item;
        } // loop on %'s
        BOOST_ASSERT(cur_item == num_items);

        // store the final piece of string
        {
            string_type & piece = (cur_item==0) ? prefix_ : items_[cur_item-1].appendix_;
            io::detail::append_string(piece, buf, i0, buf.size());
        }

        if( !ordered_args) {
            if(max_argN >= 0 ) {  // dont mix positional with non-positionnal directives
                if(exceptions() & io::bad_format_string_bit)
                    boost::throw_exception(
                        io::bad_format_string(static_cast<std::size_t>(max_argN), 0));
                // else do nothing. => positionnal arguments are processed as non-positionnal
            }
            // set things like it would have been with positional directives :
            int non_ordered_items = 0;
            for(int i=0; i< num_items; ++i)
                if(items_[i].argN_ == format_item_t::argN_no_posit) {
                    items_[i].argN_ = non_ordered_items;
                    ++non_ordered_items;
                }
            max_argN = non_ordered_items-1;
        }

        // C: set some member data :
        items_.resize(num_items, format_item_t(io::detail::const_or_not(fac).widen( ' ')) );

        if(special_things) style_ |= special_needs;
        num_args_ = max_argN + 1;
        if(ordered_args) style_ |=  ordered;
        else style_ &= ~ordered;
        return *this;
    }

} // namespace boost


#endif //  BOOST_FORMAT_PARSING_HPP

/* parsing.hpp
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
*/