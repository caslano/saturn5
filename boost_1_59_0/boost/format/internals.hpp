// ----------------------------------------------------------------------------
// internals.hpp :  internal structs : stream_format_state, format_item. 
//                  included by format.hpp
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_INTERNALS_HPP
#define BOOST_FORMAT_INTERNALS_HPP


#include <string>
#include <boost/assert.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/optional.hpp>
#include <boost/limits.hpp>
#include <boost/format/detail/compat_workarounds.hpp>
#include <boost/format/alt_sstream.hpp> // used as a dummy stream

namespace boost {
namespace io {
namespace detail {


//---- stream_format_state --------------------------------------------------//

//   set of params that define the format state of a stream
    template<class Ch, class Tr> 
    struct stream_format_state 
    {
        typedef BOOST_IO_STD basic_ios<Ch, Tr>   basic_ios;

        stream_format_state(Ch fill)                 { reset(fill); }
//        stream_format_state(const basic_ios& os)     { set_by_stream(os); }

        void reset(Ch fill);                     //- sets to default state.
        void set_by_stream(const basic_ios& os); //- sets to os's state.
        void apply_on(basic_ios & os,            //- applies format_state to the stream
                      boost::io::detail::locale_t * loc_default = 0) const;
        template<class T> 
        void apply_manip(T manipulator)          //- modifies state by applying manipulator
            { apply_manip_body<Ch, Tr, T>( *this, manipulator) ; }

        // --- data ---
        std::streamsize width_;
        std::streamsize precision_;
        Ch fill_; 
        std::ios_base::fmtflags flags_;
        std::ios_base::iostate  rdstate_;
        std::ios_base::iostate  exceptions_;
        boost::optional<boost::io::detail::locale_t>  loc_;
    };  


//---- format_item  ---------------------------------------------------------//

//   stores all parameters that can be specified in format strings
    template<class Ch, class Tr, class Alloc>  
    struct format_item 
    {     
        enum pad_values { zeropad = 1, spacepad =2, centered=4, tabulation = 8 };
                         // 1. if zeropad is set, all other bits are not, 
                         // 2. if tabulation is set, all others are not.
                         // centered and spacepad can be mixed freely.
        enum arg_values { argN_no_posit   = -1, // non-positional directive. will set argN later
                          argN_tabulation = -2, // tabulation directive. (no argument read) 
                          argN_ignored    = -3  // ignored directive. (no argument read)
        };
        typedef BOOST_IO_STD basic_ios<Ch, Tr>                    basic_ios;
        typedef detail::stream_format_state<Ch, Tr>               stream_format_state;
        typedef ::std::basic_string<Ch, Tr, Alloc>                string_type;

        format_item(Ch fill) :argN_(argN_no_posit), fmtstate_(fill), 
                              truncate_(max_streamsize()), pad_scheme_(0)  {}
        void reset(Ch fill);
        void compute_states(); // sets states  according to truncate and pad_scheme.

        static std::streamsize max_streamsize() { 
            return (std::numeric_limits<std::streamsize>::max)();
        }

        // --- data ---
        int         argN_;  //- argument number (starts at 0,  eg : %1 => argN=0)
                            //  negative values for items that don't process an argument
        string_type  res_;      //- result of the formatting of this item
        string_type  appendix_; //- piece of string between this item and the next

        stream_format_state fmtstate_;// set by parsing, is only affected by modify_item

        std::streamsize truncate_;//- is set for directives like %.5s that ask truncation
        unsigned int pad_scheme_;//- several possible padding schemes can mix. see pad_values
    }; 



//--- Definitions  ------------------------------------------------------------

// -   stream_format_state:: -------------------------------------------------
    template<class Ch, class Tr>
    void stream_format_state<Ch,Tr>:: apply_on (basic_ios & os,
                      boost::io::detail::locale_t * loc_default) const {
    // If a locale is available, set it first. "os.fill(fill_);" may chrash otherwise. 
#if !defined(BOOST_NO_STD_LOCALE)
        if(loc_)
            os.imbue(loc_.get());
        else if(loc_default)
            os.imbue(*loc_default);
#else
        ignore_unused(loc_default);
#endif        
        // set the state of this stream according to our params
        if(width_ != -1)
            os.width(width_);
        if(precision_ != -1)
            os.precision(precision_);
        if(fill_ != 0)
            os.fill(fill_);
        os.flags(flags_);
        os.clear(rdstate_);
        os.exceptions(exceptions_);
    }

    template<class Ch, class Tr>
    void stream_format_state<Ch,Tr>:: set_by_stream(const basic_ios& os) {
        // set our params according to the state of this stream
        flags_ = os.flags();
        width_ = os.width();
        precision_ = os.precision();
        fill_ = os.fill();
        rdstate_ = os.rdstate();
        exceptions_ = os.exceptions();
    }


    template<class Ch, class Tr, class T>
    void apply_manip_body( stream_format_state<Ch, Tr>& self,
                           T manipulator) {
        // modify our params according to the manipulator
        basic_oaltstringstream<Ch, Tr>  ss;
        self.apply_on( ss );
        ss << manipulator;
        self.set_by_stream( ss );
    }

    template<class Ch, class Tr> inline
    void stream_format_state<Ch,Tr>:: reset(Ch fill) {
        // set our params to standard's default state.   cf 27.4.4.1 of the C++ norm
        width_=0; precision_=6; 
        fill_=fill; // default is widen(' '), but we cant compute it without the locale
        flags_ = std::ios_base::dec | std::ios_base::skipws; 
        // the adjust_field part is left equal to 0, which means right.
        exceptions_ = std::ios_base::goodbit;
        rdstate_ = std::ios_base::goodbit;
    }


// ---   format_item:: --------------------------------------------------------

    template<class Ch, class Tr, class Alloc> 
    void format_item<Ch, Tr, Alloc>:: 
    reset (Ch fill) { 
        argN_=argN_no_posit; truncate_ = max_streamsize(); pad_scheme_ =0; 
        res_.resize(0); appendix_.resize(0);
        fmtstate_.reset(fill);
    }

    template<class Ch, class Tr, class Alloc> 
    void format_item<Ch, Tr, Alloc>:: 
    compute_states() {
        // reflect pad_scheme_   on  fmt_state_
        //   because some pad_schemes has complex consequences on several state params.
        if(pad_scheme_ & zeropad) {
            // ignore zeropad in left alignment :
            if(fmtstate_.flags_ & std::ios_base::left) {
              BOOST_ASSERT(!(fmtstate_.flags_ &(std::ios_base::adjustfield ^std::ios_base::left)));
              // only left bit might be set. (not right, nor internal)
              pad_scheme_ = pad_scheme_ & (~zeropad); 
            }
            else { 
                pad_scheme_ &= ~spacepad; // printf ignores spacepad when zeropadding
                fmtstate_.fill_='0'; 
                fmtstate_.flags_ = (fmtstate_.flags_ & ~std::ios_base::adjustfield) 
                    | std::ios_base::internal;
                // removes all adjustfield bits, and adds internal.
            }
        }
        if(pad_scheme_ & spacepad) {
            if(fmtstate_.flags_ & std::ios_base::showpos)
                pad_scheme_ &= ~spacepad;
        }
    }


} } } // namespaces boost :: io :: detail


#endif // BOOST_FORMAT_INTERNALS_HPP

/* internals.hpp
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
*/