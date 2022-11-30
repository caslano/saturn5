//
//  Copyright (c) 2015 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_GENERIC_CODECVT_HPP
#define BOOST_LOCALE_GENERIC_CODECVT_HPP

#include <boost/locale/utf.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <locale>

namespace boost {
namespace locale {

#ifndef BOOST_LOCALE_DOXYGEN
//
// Make sure that mbstate can keep 16 bit of UTF-16 sequence
//
BOOST_STATIC_ASSERT(sizeof(std::mbstate_t)>=2);
#endif

#if defined(_MSC_VER) && _MSC_VER < 1700
// up to MSVC 11 (2012) do_length is non-standard it counts wide characters instead of narrow and does not change mbstate
#define BOOST_LOCALE_DO_LENGTH_MBSTATE_CONST
#endif

///
/// \brief A base class that used to define constants for generic_codecvt
///
class generic_codecvt_base {
public:
    ///
    /// Initail state for converting to or from unicode code points, used by initial_state in derived classes
    ///
    enum initial_convertion_state {
        to_unicode_state, ///< The state would be used by to_unicode functions
        from_unicode_state ///< The state would be used by from_unicode functions
    };
};

///
/// \brief Geneneric generic codecvt facet, various stateless encodings to UTF-16 and UTF-32 using wchar_t, char32_t and char16_t
///
/// Implementations should dervide from this class defining itself as CodecvtImpl and provide following members
///
/// - `state_type` - a type of special object that allows to store intermediate cached data, for example `iconv_t` descriptor 
/// - `state_type initial_state(generic_codecvt_base::initial_convertion_state direction) const` - member function that creates initial state
/// - `int max_encoding_length() const` - a maximal length that one Unicode code point is represented, for UTF-8 for example it is 4 from ISO-8859-1 it is 1
/// - `utf::code_point to_unicode(state_type &state,char const *&begin,char const *end)` - extract first code point from the text in range [begin,end), in case of success begin would point to the next character sequence to be encoded to next code point, in case of incomplete sequence - utf::incomplete shell be returned, and in case of invalid input sequence utf::illegal shell be returned and begin would remain unmodified
/// - `utf::code_point from_unicode(state_type &state,utf::code_point u,char *begin,char const *end)` - convert a unicode code point `u` into a character seqnece at [begin,end). Return the length of the sequence in case of success, utf::incomplete in case of not enough room to encode the code point of utf::illegal in case conversion can not be performed
///
///
/// For example implementaion of codecvt for latin1/ISO-8859-1 character set
///
/// \code
///
/// template<typename CharType>
/// class latin1_codecvt :boost::locale::generic_codecvt<CharType,latin1_codecvt<CharType> > 
/// {
/// public:
///    
///     /* Standard codecvt constructor */ 
///     latin1_codecvt(size_t refs = 0) : boost::locale::generic_codecvt<CharType,latin1_codecvt<CharType> >(refs) 
///     {
///     }
///
///     /* State is unused but required by generic_codecvt */
///     struct state_type {};
///
///     state_type initial_state(generic_codecvt_base::initial_convertion_state /*unused*/) const
///     {
///         return state_type();
///     }
///     
///     int max_encoding_length() const
///     {
///         return 1;
///     }
///
///     boost::locale::utf::code_point to_unicode(state_type &,char const *&begin,char const *end) const
///     {
///        if(begin == end)
///           return boost::locale::utf::incomplete;
///        return *begin++; 
///     }
///
///     boost::locale::utf::code_point from_unicode(state_type &,boost::locale::utf::code_point u,char *begin,char const *end) const
///     {
///        if(u >= 256)
///           return boost::locale::utf::illegal;
///        if(begin == end)
///           return boost::locale::utf::incomplete;
///        *begin = u;
///        return 1; 
///     }
/// };
/// 
/// \endcode
/// 
/// When external tools used for encoding conversion, the `state_type` is useful to save objects used for conversions. For example,
/// icu::UConverter can be saved in such a state for an efficient use:
///
/// \code
/// template<typename CharType>
/// class icu_codecvt :boost::locale::generic_codecvt<CharType,icu_codecvt<CharType> > 
/// {
/// public:
///    
///     /* Standard codecvt constructor */ 
///     icu_codecvt(std::string const &name,refs = 0) : 
///         boost::locale::generic_codecvt<CharType,latin1_codecvt<CharType> >(refs)
///     { ... }
///
///     /* State is unused but required by generic_codecvt */
///     struct std::unique_ptr<UConverter,void (*)(UConverter*)> state_type;
///
///     state_type &&initial_state(generic_codecvt_base::initial_convertion_state /*unused*/) const
///     {
///         UErrorCode err = U_ZERO_ERROR;
///         state_type ptr(ucnv_safeClone(converter_,0,0,&err,ucnv_close);
///         return std::move(ptr);
///     }
///     
///     boost::locale::utf::code_point to_unicode(state_type &ptr,char const *&begin,char const *end) const
///     {
///         UErrorCode err = U_ZERO_ERROR;
///         boost::locale::utf::code_point cp = ucnv_getNextUChar(ptr.get(),&begin,end,&err);
///         ...
///     }
///     ...
/// };
/// \endcode
///
///
template<typename CharType,typename CodecvtImpl,int CharSize=sizeof(CharType)>
class generic_codecvt;

///
/// \brief UTF-16 to/from UTF-8 codecvt facet to use with char16_t or wchar_t on Windows
///
/// Note in order to fit the requirements of usability by std::wfstream it uses mbstate_t
/// to handle intermediate states in handling of variable length UTF-16 sequences
///
/// Its member functions implement standard virtual functions of basic codecvt
///
template<typename CharType,typename CodecvtImpl>
class generic_codecvt<CharType,CodecvtImpl,2> : public std::codecvt<CharType,char,std::mbstate_t>, public generic_codecvt_base
{
public:

    typedef CharType uchar;

    generic_codecvt(size_t refs = 0) : 
        std::codecvt<CharType,char,std::mbstate_t>(refs)
    {
    }
    CodecvtImpl const &implementation() const
    {
        return *static_cast<CodecvtImpl const *>(this);
    }

protected:


    virtual std::codecvt_base::result do_unshift(std::mbstate_t &s,char *from,char * /*to*/,char *&next) const
    {
        boost::uint16_t &state = *reinterpret_cast<boost::uint16_t *>(&s);
#ifdef DEBUG_CODECVT            
        std::cout << "Entering unshift " << std::hex << state << std::dec << std::endl;
#endif            
        if(state != 0)
            return std::codecvt_base::error;
        next=from;
        return std::codecvt_base::ok;
    }
    virtual int do_encoding() const throw()
    {
        return 0;
    }
    virtual int do_max_length() const throw()
    {
        return implementation().max_encoding_length();
    }
    virtual bool do_always_noconv() const throw()
    {
        return false;
    }

    virtual int
    do_length(  std::mbstate_t 
    #ifdef BOOST_LOCALE_DO_LENGTH_MBSTATE_CONST
            const   
    #endif
            &std_state,
            char const *from,
            char const *from_end,
            size_t max) const
    {
        #ifndef BOOST_LOCALE_DO_LENGTH_MBSTATE_CONST
        char const *save_from = from;
        boost::uint16_t &state = *reinterpret_cast<boost::uint16_t *>(&std_state);
        #else
        size_t save_max = max;
        boost::uint16_t state = *reinterpret_cast<boost::uint16_t const *>(&std_state);
        #endif

        typedef typename CodecvtImpl::state_type state_type;
        state_type cvt_state = implementation().initial_state(generic_codecvt_base::to_unicode_state);
        while(max > 0 && from < from_end){
            char const *prev_from = from;
            boost::uint32_t ch=implementation().to_unicode(cvt_state,from,from_end);
            if(ch==boost::locale::utf::incomplete || ch==boost::locale::utf::illegal) {
                from = prev_from;
                break;
            }
            max --;
            if(ch > 0xFFFF) {
                if(state == 0) {
                    from = prev_from;
                    state = 1;
                }
                else {
                    state = 0;
                }
            }        
        }
        #ifndef BOOST_LOCALE_DO_LENGTH_MBSTATE_CONST
        return from - save_from;
        #else
        return save_max - max;
        #endif
    }

    
    virtual std::codecvt_base::result 
    do_in(  std::mbstate_t &std_state,
            char const *from,
            char const *from_end,
            char const *&from_next,
            uchar *to,
            uchar *to_end,
            uchar *&to_next) const
    {
        std::codecvt_base::result r=std::codecvt_base::ok;
        
        // mbstate_t is POD type and should be initialized to 0 (i.a. state = stateT())
        // according to standard. We use it to keep a flag 0/1 for surrogate pair writing
        //
        // if 0 no code above >0xFFFF observed, of 1 a code above 0xFFFF observerd
        // and first pair is written, but no input consumed
        boost::uint16_t &state = *reinterpret_cast<boost::uint16_t *>(&std_state);
        typedef typename CodecvtImpl::state_type state_type;
        state_type cvt_state = implementation().initial_state(generic_codecvt_base::to_unicode_state);
        while(to < to_end && from < from_end)
        {
#ifdef DEBUG_CODECVT            
            std::cout << "Entering IN--------------" << std::endl;
            std::cout << "State " << std::hex << state <<std::endl;
            std::cout << "Left in " << std::dec << from_end - from << " out " << to_end -to << std::endl;
#endif           
            char const *from_saved = from;
            
            uint32_t ch=implementation().to_unicode(cvt_state,from,from_end);
            
            if(ch==boost::locale::utf::illegal) {
                from = from_saved;
                r=std::codecvt_base::error;
                break;
            }
            if(ch==boost::locale::utf::incomplete) {
                from = from_saved;
                r=std::codecvt_base::partial;
                break;
            }
            // Normal codepoints go direcly to stream
            if(ch <= 0xFFFF) {
                *to++=ch;
            }
            else {
                // for  other codepoints we do following
                //
                // 1. We can't consume our input as we may find ourselfs
                //    in state where all input consumed but not all output written,i.e. only
                //    1st pair is written
                // 2. We only write first pair and mark this in the state, we also revert back
                //    the from pointer in order to make sure this codepoint would be read
                //    once again and then we would consume our input together with writing
                //    second surrogate pair
                ch-=0x10000;
                boost::uint16_t vh = ch >> 10;
                boost::uint16_t vl = ch & 0x3FF;
                boost::uint16_t w1 = vh + 0xD800;
                boost::uint16_t w2 = vl + 0xDC00;
                if(state == 0) {
                    from = from_saved;
                    *to++ = w1;
                    state = 1;
                }
                else {
                    *to++ = w2;
                    state = 0;
                }
            }
        }
        from_next=from;
        to_next=to;
        if(r == std::codecvt_base::ok && (from!=from_end || state!=0))
            r = std::codecvt_base::partial;
#ifdef DEBUG_CODECVT            
        std::cout << "Returning ";
        switch(r) {
        case std::codecvt_base::ok:
            std::cout << "ok" << std::endl;
            break;
        case std::codecvt_base::partial:
            std::cout << "partial" << std::endl;
            break;
        case std::codecvt_base::error:
            std::cout << "error" << std::endl;
            break;
        default:
            std::cout << "other" << std::endl;
            break;
        }
        std::cout << "State " << std::hex << state <<std::endl;
        std::cout << "Left in " << std::dec << from_end - from << " out " << to_end -to << std::endl;
#endif            
        return r;
    }
    
    virtual std::codecvt_base::result 
    do_out( std::mbstate_t &std_state,
            uchar const *from,
            uchar const *from_end,
            uchar const *&from_next,
            char *to,
            char *to_end,
            char *&to_next) const
    {
        std::codecvt_base::result r=std::codecvt_base::ok;
        // mbstate_t is POD type and should be initialized to 0 (i.a. state = stateT())
        // according to standard. We assume that sizeof(mbstate_t) >=2 in order
        // to be able to store first observerd surrogate pair
        //
        // State: state!=0 - a first surrogate pair was observerd (state = first pair),
        // we expect the second one to come and then zero the state
        ///
        boost::uint16_t &state = *reinterpret_cast<boost::uint16_t *>(&std_state);
        typedef typename CodecvtImpl::state_type state_type;
        state_type cvt_state = implementation().initial_state(generic_codecvt_base::from_unicode_state);
        while(to < to_end && from < from_end)
        {
#ifdef DEBUG_CODECVT            
        std::cout << "Entering OUT --------------" << std::endl;
        std::cout << "State " << std::hex << state <<std::endl;
        std::cout << "Left in " << std::dec << from_end - from << " out " << to_end -to << std::endl;
#endif            
            boost::uint32_t ch=0;
            if(state != 0) {
                // if the state idecates that 1st surrogate pair was written
                // we should make sure that the second one that comes is actually
                // second surrogate
                boost::uint16_t w1 = state;
                boost::uint16_t w2 = *from; 
                // we don't forward from as writing may fail to incomplete or
                // partial conversion
                if(0xDC00 <= w2 && w2<=0xDFFF) {
                    boost::uint16_t vh = w1 - 0xD800;
                    boost::uint16_t vl = w2 - 0xDC00;
                    ch=((uint32_t(vh) << 10)  | vl) + 0x10000;
                }
                else {
                    // Invalid surrogate
                    r=std::codecvt_base::error;
                    break;
                }
            }
            else {
                ch = *from;
                if(0xD800 <= ch && ch<=0xDBFF) {
                    // if this is a first surrogate pair we put
                    // it into the state and consume it, note we don't
                    // go forward as it should be illegal so we increase
                    // the from pointer manually
                    state = ch;
                    from++;
                    continue;
                }
                else if(0xDC00 <= ch && ch<=0xDFFF) {
                    // if we observe second surrogate pair and 
                    // first only may be expected we should break from the loop with error
                    // as it is illegal input
                    r=std::codecvt_base::error;
                    break;
                }
            }
            if(!boost::locale::utf::is_valid_codepoint(ch)) {
                r=std::codecvt_base::error;
                break;
            }
            boost::uint32_t len = implementation().from_unicode(cvt_state,ch,to,to_end);
            if(len == boost::locale::utf::incomplete) {
                r=std::codecvt_base::partial;
                break;
            }
            else if(len == boost::locale::utf::illegal) {
                r=std::codecvt_base::error;
                break;
            }
            else
                    to+= len;
            state = 0;
            from++;
        }
        from_next=from;
        to_next=to;
        if(r==std::codecvt_base::ok && from!=from_end)
            r = std::codecvt_base::partial;
#ifdef DEBUG_CODECVT            
        std::cout << "Returning ";
        switch(r) {
        case std::codecvt_base::ok:
            std::cout << "ok" << std::endl;
            break;
        case std::codecvt_base::partial:
            std::cout << "partial" << std::endl;
            break;
        case std::codecvt_base::error:
            std::cout << "error" << std::endl;
            break;
        default:
            std::cout << "other" << std::endl;
            break;
        }
        std::cout << "State " << std::hex << state <<std::endl;
        std::cout << "Left in " << std::dec << from_end - from << " out " << to_end -to << std::endl;
#endif            
        return r;
    }
    
};

///
/// \brief UTF-32 to/from UTF-8 codecvt facet to use with char32_t or wchar_t on POSIX platforms
///
/// Its member functions implement standard virtual functions of basic codecvt.
/// mbstate_t is not used for UTF-32 handling due to fixed length encoding
///
template<typename CharType,typename CodecvtImpl>
class generic_codecvt<CharType,CodecvtImpl,4> : public std::codecvt<CharType,char,std::mbstate_t>, public generic_codecvt_base
{
public:
    typedef CharType uchar;

    generic_codecvt(size_t refs = 0) : 
        std::codecvt<CharType,char,std::mbstate_t>(refs)
    {
    }
    
    CodecvtImpl const &implementation() const
    {
        return *static_cast<CodecvtImpl const *>(this);
    }
    
protected:

    virtual std::codecvt_base::result do_unshift(std::mbstate_t &/*s*/,char *from,char * /*to*/,char *&next) const
    {
        next=from;
        return std::codecvt_base::ok;
    }
    virtual int do_encoding() const throw()
    {
        return 0;
    }
    virtual int do_max_length() const throw()
    {
        return implementation().max_encoding_length();
    }
    virtual bool do_always_noconv() const throw()
    {
        return false;
    }

    virtual int
    do_length(  std::mbstate_t 
    #ifdef BOOST_LOCALE_DO_LENGTH_MBSTATE_CONST
            const   
    #endif    
            &/*state*/,
            char const *from,
            char const *from_end,
            size_t max) const
    {
        #ifndef BOOST_LOCALE_DO_LENGTH_MBSTATE_CONST 
        char const *start_from = from;
        #else
        size_t save_max = max;
        #endif
        typedef typename CodecvtImpl::state_type state_type;
        state_type cvt_state = implementation().initial_state(generic_codecvt_base::to_unicode_state);
        while(max > 0 && from < from_end){
            char const *save_from = from;
            boost::uint32_t ch=implementation().to_unicode(cvt_state,from,from_end);
            if(ch==boost::locale::utf::incomplete || ch==boost::locale::utf::illegal) {
                from = save_from;
                break;
            }
            max--;
        }
        #ifndef BOOST_LOCALE_DO_LENGTH_MBSTATE_CONST 
        return from - start_from;
        #else
        return save_max - max;
        #endif
    }

    
    virtual std::codecvt_base::result 
    do_in(  std::mbstate_t &/*state*/,
            char const *from,
            char const *from_end,
            char const *&from_next,
            uchar *to,
            uchar *to_end,
            uchar *&to_next) const
    {
        std::codecvt_base::result r=std::codecvt_base::ok;
        
        // mbstate_t is POD type and should be initialized to 0 (i.a. state = stateT())
        // according to standard. We use it to keep a flag 0/1 for surrogate pair writing
        //
        // if 0 no code above >0xFFFF observed, of 1 a code above 0xFFFF observerd
        // and first pair is written, but no input consumed
        typedef typename CodecvtImpl::state_type state_type;
        state_type cvt_state = implementation().initial_state(generic_codecvt_base::to_unicode_state);
        while(to < to_end && from < from_end)
        {
#ifdef DEBUG_CODECVT            
            std::cout << "Entering IN--------------" << std::endl;
            std::cout << "State " << std::hex << state <<std::endl;
            std::cout << "Left in " << std::dec << from_end - from << " out " << to_end -to << std::endl;
#endif           
            char const *from_saved = from;
            
            uint32_t ch=implementation().to_unicode(cvt_state,from,from_end);
            
            if(ch==boost::locale::utf::illegal) {
                r=std::codecvt_base::error;
                from = from_saved;
                break;
            }
            if(ch==boost::locale::utf::incomplete) {
                r=std::codecvt_base::partial;
                from=from_saved;
                break;
            }
            *to++=ch;
        }
        from_next=from;
        to_next=to;
        if(r == std::codecvt_base::ok && from!=from_end)
            r = std::codecvt_base::partial;
#ifdef DEBUG_CODECVT            
        std::cout << "Returning ";
        switch(r) {
        case std::codecvt_base::ok:
            std::cout << "ok" << std::endl;
            break;
        case std::codecvt_base::partial:
            std::cout << "partial" << std::endl;
            break;
        case std::codecvt_base::error:
            std::cout << "error" << std::endl;
            break;
        default:
            std::cout << "other" << std::endl;
            break;
        }
        std::cout << "State " << std::hex << state <<std::endl;
        std::cout << "Left in " << std::dec << from_end - from << " out " << to_end -to << std::endl;
#endif            
        return r;
    }
    
    virtual std::codecvt_base::result 
    do_out( std::mbstate_t &/*std_state*/,
            uchar const *from,
            uchar const *from_end,
            uchar const *&from_next,
            char *to,
            char *to_end,
            char *&to_next) const
    {
        std::codecvt_base::result r=std::codecvt_base::ok;
        typedef typename CodecvtImpl::state_type state_type;
        state_type cvt_state = implementation().initial_state(generic_codecvt_base::from_unicode_state);
        while(to < to_end && from < from_end)
        {
#ifdef DEBUG_CODECVT            
        std::cout << "Entering OUT --------------" << std::endl;
        std::cout << "State " << std::hex << state <<std::endl;
        std::cout << "Left in " << std::dec << from_end - from << " out " << to_end -to << std::endl;
#endif            
            boost::uint32_t ch=0;
            ch = *from;
            if(!boost::locale::utf::is_valid_codepoint(ch)) {
                r=std::codecvt_base::error;
                break;
            }
            boost::uint32_t len = implementation().from_unicode(cvt_state,ch,to,to_end);
            if(len == boost::locale::utf::incomplete) {
                r=std::codecvt_base::partial;
                break;
            }
            else if(len == boost::locale::utf::illegal) {
                r=std::codecvt_base::error;
                break;
            }
            to+=len;
            from++;
        }
        from_next=from;
        to_next=to;
        if(r==std::codecvt_base::ok && from!=from_end)
            r = std::codecvt_base::partial;
#ifdef DEBUG_CODECVT            
        std::cout << "Returning ";
        switch(r) {
        case std::codecvt_base::ok:
            std::cout << "ok" << std::endl;
            break;
        case std::codecvt_base::partial:
            std::cout << "partial" << std::endl;
            break;
        case std::codecvt_base::error:
            std::cout << "error" << std::endl;
            break;
        default:
            std::cout << "other" << std::endl;
            break;
        }
        std::cout << "State " << std::hex << state <<std::endl;
        std::cout << "Left in " << std::dec << from_end - from << " out " << to_end -to << std::endl;
#endif            
        return r;
    }
};


template<typename CharType,typename CodecvtImpl>
class generic_codecvt<CharType,CodecvtImpl,1> : public std::codecvt<CharType,char,std::mbstate_t>, public generic_codecvt_base
{
public:
    typedef CharType uchar;

    CodecvtImpl const &implementation() const
    {
        return *static_cast<CodecvtImpl const *>(this);
    }

    generic_codecvt(size_t refs = 0) :  std::codecvt<char,char,std::mbstate_t>(refs)
    {
    }
};

} // locale
} // namespace boost

#endif
///
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* generic_codecvt.hpp
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
*/