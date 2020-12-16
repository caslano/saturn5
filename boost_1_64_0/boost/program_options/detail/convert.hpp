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
NlLAS0mzYdp6FcjDIDg+RZhjQpuF+od2YL9ziqQloTyQ4YGY3yi5937wd3+ow4ED9uKe95Y9/20bAv/sENqC5NcuBysFnrfzaZeBlQBt/LvhehNk+vKFsNa6z+unv/H8r99d3N1ywe473jfrZFDXPEPOZzYbvs24R9VV18ybN2HRU/W1kOhu+/xBl4569KPjF3+74y+b3fLDyvP2C4Xevss+v/qKomHjWvZ+5+GdtnzriW3OLQFfFOT3ky9556zo6qG/XPyddn3lF4eUgj888vu2itfv+XzbHW94adODd3xqp2ugMA3k9yMnDblTrbqqc49nnzz45VPuh4qaTc4fOr24+91Pfzxq/k5d37wy5Pr+odAj5PwtVzbUdPX96r1Hb9r716vnzLwJ7MDJ+UvPrl3/8E6zZhc8oNywxeQjXw+Fdllkn99v3scLhnzY74dnq6e+PXW3ukwodDw5nxd56/qT967eKbn7U2OLiz6ZDH53SD089fYdCy++QAlP+eD6Y1dsyP8MfLGR38+sGrjg7IOOqMqvn7hNnwkTwbHyPeR8WVVs54/Hdx+4WWrXD888ZP3jsLbL9gdycr/QKogbIO5a1y80CuJ2ZbAOG46tEDshpkxoqxAL4Py8Y8GWHs59OBb+fwKsTauB38IzSEHsG4GHD0qyFSfBOoNxYP8+HnwUTAB/LhOhrk6GYx2sSYW4DGI3xFFpuAf8/lW433wF0kHsgjd4FcSRUSgPxOcgroS4Fn5zTAzW8apwDmK5BvVwSr/QgVC+1jRwdWDotlMvuD/cc/1kYMTBLj0Be+8kwW8A/DYIQQhCEIIQhCAEIQhBCIKcIF7+t8XqtBazeuT/PpLkf/v6OyCf+lxWThru6AdSIFePQP1AE7oyOADiRhD3t8sO93/rClteblNqIiVKBeRej8b1aRrsdwhy9urBpGaILmBH+N975LdDiFwdyi1Xw+8Py+uG39rI1wYTuZnlY12OfPS5sicfEah9PUlEbt989L/yz+dj9ytZPpj8/mGfXPJ4bnl2t/vs88sqpx/29RGHV31/3+D8pXmbzwcZj5x/7+gNs0Z3XHVmY/2yimGF4Xv/upz+1b32+RfO2KRxkxs6v5hw1aKOOxa9DLLpo+R814/fxloG90seE77r4C9e+2pDLv1Dbnm/heTziqX5a1Yv3WX2abtddsjIkV+uz60H8Jf3c+sHFpD7j9vjgpXqmd2Pnj6nYttV+b/8mFsP4K/3yK0H8Ner5NKTOHoD0BG49AK7ntovVASxEqIKsRWiV1cwB8659QV/U1dwam99weJT+/2hzoDqC56D3/rpC1bCeV5nsAb+7q8EeoMgBCEIQQhCEIIQhCAEAcI/LP+ntSa4FG8sshUARP7fmMzVM5t8X/l/TBT+2qM4ndYSMJdtOnvwh47MC8WmqnbGVJXlArIA/yc7MGRSdfUZPa7WJVTMHPgmM5NafHhhSMtqmJAkY8nDWvOwIrugddnhhSTHifhQ+8dpM/a7JLhepzXV6cNdhYymE5BVJtu3oWy/fQiPKNtfcTmRwRWltrRc0UC/YTQWoa8tlnYJpi0L4RHTVvNpAYtpmSw/COIqInt+Uv/IpqNm3npTy66f/7xK/ew2kKXsPIFsNDeQj4IQhCAEIQhBCEIQghCEIAThfx36QjxJqPzfYBnx4f9F2b9Ji6c0E+R/VkiU/XcObZk3FY5t4/qATK7U6o3J0bo1gsjoO8C1IbZ87lzLDju0rIycxzSLnPNj9GRZNWScnZ+P56NZ5/xQ1BGsRB3BViE8oo7g4gscHYFqZwx1AzTNlhv5p1l4npOmgUuTj/zTHD40g+GFEeNEcoTT7J6n4T33CeER7/k=
*/