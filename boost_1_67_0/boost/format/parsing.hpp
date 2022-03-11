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