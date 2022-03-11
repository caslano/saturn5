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