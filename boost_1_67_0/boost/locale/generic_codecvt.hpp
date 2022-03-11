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