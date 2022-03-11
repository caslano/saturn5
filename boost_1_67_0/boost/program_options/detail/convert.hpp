// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONVERT_HPP_VP_2004_04_28
#define BOOST_CONVERT_HPP_VP_2004_04_28

#include <boost/program_options/config.hpp>

#if !defined(BOOST_NO_STD_WSTRING)

#include <boost/detail/workaround.hpp>

#include <string>
#include <vector>
#include <locale>
// for mbstate_t
#include <cwchar>
#include <stdexcept>

#if defined(BOOST_NO_STDC_NAMESPACE)
#include <wchar.h>
namespace std
{
    using ::mbstate_t;
}    
#endif

namespace boost {

    /** Converts from local 8 bit encoding into wchar_t string using
        the specified locale facet. */
    BOOST_PROGRAM_OPTIONS_DECL std::wstring 
    from_8_bit(const std::string& s, 
               const std::codecvt<wchar_t, char, std::mbstate_t>& cvt);

    /** Converts from wchar_t string into local 8 bit encoding into using
        the specified locale facet. */
    BOOST_PROGRAM_OPTIONS_DECL std::string 
    to_8_bit(const std::wstring& s, 
             const std::codecvt<wchar_t, char, std::mbstate_t>& cvt);


    /** Converts 's', which is assumed to be in UTF8 encoding, into wide
        string. */
    BOOST_PROGRAM_OPTIONS_DECL std::wstring
    from_utf8(const std::string& s);
    
    /** Converts wide string 's' into string in UTF8 encoding. */
    BOOST_PROGRAM_OPTIONS_DECL std::string
    to_utf8(const std::wstring& s);

    /** Converts wide string 's' into local 8 bit encoding determined by
        the current locale. */
    BOOST_PROGRAM_OPTIONS_DECL std::string
    to_local_8_bit(const std::wstring& s);

    /** Converts 's', which is assumed to be in local 8 bit encoding, into wide
        string. */
    BOOST_PROGRAM_OPTIONS_DECL std::wstring
    from_local_8_bit(const std::string& s);

    namespace program_options
    {
        /** Convert the input string into internal encoding used by
            program_options. Presence of this function allows to avoid
            specializing all methods which access input on wchar_t.
        */
        BOOST_PROGRAM_OPTIONS_DECL std::string to_internal(const std::string&);
        /** @overload */
        BOOST_PROGRAM_OPTIONS_DECL std::string to_internal(const std::wstring&);

        template<class T>
        std::vector<std::string> to_internal(const std::vector<T>& s)
        {
            std::vector<std::string> result;
            for (unsigned i = 0; i < s.size(); ++i)
                result.push_back(to_internal(s[i]));            
            return result;
        }

    }


  
}

#else
#include <vector>
#include <string>
namespace boost{
   namespace program_options{
        BOOST_PROGRAM_OPTIONS_DECL std::string to_internal(const std::string&);

        template<class T>
        std::vector<std::string> to_internal(const std::vector<T>& s)
        {
            std::vector<std::string> result;
            for (unsigned i = 0; i < s.size(); ++i)
                result.push_back(to_internal(s[i]));            
            return result;
        }
   }
}
#endif
#endif

/* convert.hpp
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
*/