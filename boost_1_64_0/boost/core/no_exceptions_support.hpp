#ifndef BOOST_CORE_NO_EXCEPTIONS_SUPPORT_HPP
#define BOOST_CORE_NO_EXCEPTIONS_SUPPORT_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

//----------------------------------------------------------------------
// (C) Copyright 2004 Pavel Vozenilek.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
// This file contains helper macros used when exception support may be
// disabled (as indicated by macro BOOST_NO_EXCEPTIONS).
//
// Before picking up these macros you may consider using RAII techniques
// to deal with exceptions - their syntax can be always the same with 
// or without exception support enabled.
//----------------------------------------------------------------------

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if !(defined BOOST_NO_EXCEPTIONS)
#    define BOOST_TRY { try
#    define BOOST_CATCH(x) catch(x)
#    define BOOST_RETHROW throw;
#    define BOOST_CATCH_END }
#else
#    if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#        define BOOST_TRY { if ("")
#        define BOOST_CATCH(x) else if (!"")
#    elif !defined(BOOST_MSVC) || BOOST_MSVC >= 1900
#        define BOOST_TRY { if (true)
#        define BOOST_CATCH(x) else if (false)
#    else
         // warning C4127: conditional expression is constant
#        define BOOST_TRY { \
             __pragma(warning(push)) \
             __pragma(warning(disable: 4127)) \
             if (true) \
             __pragma(warning(pop))
#        define BOOST_CATCH(x) else \
             __pragma(warning(push)) \
             __pragma(warning(disable: 4127)) \
             if (false) \
             __pragma(warning(pop))
#    endif
#    define BOOST_RETHROW
#    define BOOST_CATCH_END }
#endif


#endif 

/* no_exceptions_support.hpp
Cvo2nqfXfkZgsVpw7iIfWoo4+2lh3np+al52kdaycPmnRiOrixemy1OLfCNrTSgrNwbrPXedYquHfuUXp+ZlFvE2zj3xJosRShPr8Tj2nVPyudXSNeE+CMePOJ1SllkvXwX1L/N9lnB+07qV5zZ1z+sIYcL8SQEzIcZEUA5muC1Ma+9wYxtgWm6IeO/5SirP5On6XtVa3me+mmiZe1HsEKBdQ7SriekGTWvU18AM0vjZvEbypV5L+WWPjJvYwLhHUdF3eQ9vbPHNxE+TsnDh1urore5YQewWe7uL9SH2TsS8+7fvRsz7xu57CVMTs7khDGPa+7yyEJux8w8gBmuXBL8ecbtmMXP6DYjrLWXsv50swMC4wF6CGwv3ErgvY9jGMr2R8uOWMvwnEI0ZTQWS8n+UsCoVmQH1NMuZMy5rZrzSxSy27oh1tTPs9FebL08GOMaHaQ2X1cfH1+uYOb0DQxfSF/uk7/SiLE8QlxV5KL5PdjpvGBL8k5zP7j7IA/Twl3VQF25kX4cMsA7x21aQN/izfgEy0TCwbp8i2UM0AFcKhI8VS1kIJ2PuD61AHansbb0/I+iPJiKzPr05xPUG/Ij5xrN9ExTwyt/F/aLMZ9Z6Sd5fTuHLl6wtbapVTtrm0QpLHzaA7S1ZlthEzhhuku9XXFm9+w6qoYq52AeymHm/rsaN3i7T1otBrl6VUIPBWPlNza9fPUAbfWuptQF6BeV8m/67lGb4wp6O7PaYbOrwFUwTZwb+lyTNgPutnK87aWbLVBvHJ/vDJN1+DSV5/Qjsn23E9NWfIMZ6p+vBNKxrrW8M+LDNy7N0v0st4mryJl8nIkanf/8MeH2bM31JzNuNZ/BLgYc1ZHhuDXl0azW+tlH7COleiZ1jwb5/DWuRheaJjQvxz4457Ins37i88TQwVSyoVSwt2gw/jkvMz3LhQV0KDz4aM+PAH1weP2OyBWmOlOvSzby/C3lTK3Qc+8pKvjI6kw/ubeahzVLnak6s19RqnfYHKus3aQ48VZ3DJe/ZmbYaaH9jWouiNX6WEJ+7hOdGl4hl/rtjCzotdybD8w/Qsctjx6Z/w365yDdveAyig0MXOzzq3gU80eAsmxfBuM+6G/FMHU72IkMDu/rdffjiEM+XRt1znlO9fJjD3L05I0WGQ+nb07Nrl9XNfXyZ7F3Ddc8q4iEj0Ay8Q0zKtCbI0401dVaAUw7kby1A3KaWDbhPyxfIz0madn3KawM54V73HKgLho4357+YD/uaV7p+Yf1IbbQyqfL2MbVprJY0bM6N/TxnZ4wGk3GjfeF2MbLuofUMG17Nh/PdMubJe7bRpumQPSVPPXemGQDWVJlQ/yaufhdhi4nr5epcvbG+XB1TXqdp6TuOT10jncNu3gB9OfQTmrnivIX4+Htlm2BME/zuvnDwbwb8AW9S3q22HJFU3k3gi2M+aB6PHe7QwTgM/FKprV3cTnmob8BQ9VXLG7t+ALatOoNpbN6vjvEyMmzD50MbWjt8oNM2nBjwByEu+M43ny7g7DpDX+MFVg5qyAhsXUj3hovWHzV1rnnrjulu9JYX7P4qdw6rURfa8BseuR7EoXRSsw59Fza4dqDy681fWIdXiu3+YKddOTH6mCRcanfEG2h3FrhwuzNXfe2ueY+j3aPRYL11bWPtTg6iGu1OHHW1+3BPw/29kJPX+W9pqA79vTVslzjqs93+3sZttzwpfz/4nWIdeoT5hNI7a7xtAg+PwWDDMk9ixhsX1hkKNfn2wRzj57ux9vyiWWGdsHUZxGw2niGaq2q2g5XXeHvwJiTwz14v+sX7Udfsv1wwbgHz1Boj+Ex5YbvUXHXYpeKr8+2l1YMwNnw=
*/