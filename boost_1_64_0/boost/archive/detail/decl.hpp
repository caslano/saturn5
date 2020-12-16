#ifndef BOOST_ARCHIVE_DETAIL_DECL_HPP
#define BOOST_ARCHIVE_DETAIL_DECL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2///////// 3/////////4/////////5/////////6/////////7/////////8
//  decl.hpp
//
//  (c) Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------//

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

#include <boost/config.hpp>

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK))
    #if defined(BOOST_ARCHIVE_SOURCE)
        #define BOOST_ARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_ARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

    #if defined(BOOST_WARCHIVE_SOURCE)
        #define BOOST_WARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_WARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

    #if defined(BOOST_WARCHIVE_SOURCE) || defined(BOOST_ARCHIVE_SOURCE)
        #define BOOST_ARCHIVE_OR_WARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_ARCHIVE_OR_WARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

#endif

#if ! defined(BOOST_ARCHIVE_DECL)
    #define BOOST_ARCHIVE_DECL
#endif
#if ! defined(BOOST_WARCHIVE_DECL)
    #define BOOST_WARCHIVE_DECL
#endif
#if ! defined(BOOST_ARCHIVE_OR_WARCHIVE_DECL)
    #define BOOST_ARCHIVE_OR_WARCHIVE_DECL
#endif

#endif // BOOST_ARCHIVE_DETAIL_DECL_HPP

/* decl.hpp
ddap1pnW+dbl1nXW9daN1s3WLdZt1h3Wndaj1hgbtg3PRtdGYCOykdo42Xja+NuE26yyWWeTZLPVZpdNuk2WTa5Nvk2xTalNpU21zWWbNpsumx6bPpthG5wt05Zly7Hl2wptxbYett62/rbBtqG2EbarbFNsD9kW2JbbXrZttu2w7bLtsR2wHbHFSeQl6hKuhCcxkthI3CQ+Ej9JoCRKskaSKNksyZLkSA5J8iVFknJJhaRW0iBpkrRIOiSdkkHJqARjR7eTt1O249gJ7CzsXOy87Hzs/O1C7MLtouyS7TbbZdjl25XZVdudt2uya7Nrt+u3e2mHk9KlqlJ1KUfKlRpJzaRWUgepizRSGi2Nla6SrpEmS3dJM6TZ0kJpsbRMWimtkdZLG6UDUoI9xZ5hL2/PtufZC+xF9mb2TvZz7YPtQ+zj7RPtU+xz7Svsq+yr7Wvt6+zr7VvsW+077Lvt++xH7WkOdAcrB4mD1MHJwc8h0CHEIdRhlcM6h60OuxyKHKodLjtcd2hzeOTQ49DvMOKg7sh11HUUOoodHRxdHN0cAxyDHEMdIxxTHHc55jkWOJY4ljtWObY6tjv2OL50HHKkONGc5J1YTlwnMycLJ4mTg5OfU4hTuFO80xqnNKdCp3KnKqdqpwanbqc+pwGnISeCM8lZ1ZnjzHMWOIucXZx9nH2d/Z2DnKOd1zknOSc7b3be5ZzhnO1c5lzn3OB83bnNudO535nkwnDhuOi68F3MXKxcbFy8XOa6hLlsddnukuZyyKXApdilzKXK5bxLo0uHS7dLj0uvS7/LkAvFleaq7MpzFbhKXB1c3Vw9XL1dfVz9XENcI12TXFNdc10PuRa6FrlWuVa71ru2uLa6DrkOuxLc5N2YbkI3sZuT2zQ3HzdftyC3eLd1bgluqW55bkVuxW6Vbufd6BPnaZlAGbABB+gCARACEbAAEiAFLsAdTANewAf4gSAQAkJBOIgAUSABJIHNE8+7TgcZIBvkgXxQAIpAKSgD1aAG1IHz4DpoA+2gE3SBR6AP9IOXYBhgMHB+B9ABA7CAKlAHXKALhMAMWAEbIAUuwAN4A38QAIJAKAgDkSAWrAJrQAJIBilgO9gF0kAmyAOHQDEoAWWgHFSCGlAPLoNGcB20gw7QDXpALxgAL8EI5t092miAAeQBC7ABD/CBERABM2ADJMAJeABP4A3mAj8QCIJBCAgD4SAWxINEkARSwHaQBtJBFsgFh0AhKAGloAJUgWpQB+pBI2gBraANdIJu0AcGwRAYBRgcnHMGNMAEqoANOEAAhEAMLIAVkAApcAfTgA/wBX7AHwSCUBABokA0iAfrQBJIBltBKsgAWSAXFIAiUAxKQRmoADXgPGgATaAFtIF20AV6QB/oB4NgGIwAHB76H6AAOmAAVaAOdAEfGAExsAI2wAG4ADcwDXgBXxAAgkAwCAPRYA1IAIkgGaSArSANZIM8cAgUgBJQDqpADagF58Fl0AiawS3QDjpAD+gFL8EQGAGjAEeA/QE0IA9YQBmoAy7gAwEQAQsgAQ7ADXgCb+AD5gI/EABCQDiIBPFgDUgESWAzSAVpIB1kghyQDwpBESgBpaAKVIN60AAaQRNoBq2gDXSDR6AXDIBhgCFC/wMkQAfyQBlwAA8IgBCIgBWQAifgDqYBT+ADfIE/CAIhIBxEgWiwCiSAJJAMUsEukAWyQS7IA/mgCBSDMlABKkEdaACXwXXQAm6BdtAJHoF+MAhegmEwAigk6HeACVSBOuAAXcAHZsAK2AApcAMewAt4A18wFwSBYBABokEsWAUSQCJIAVvBdrALZIBskAMOgQJQCMpAJagF9eAyaATXQSvoAF2gB/Q=
*/