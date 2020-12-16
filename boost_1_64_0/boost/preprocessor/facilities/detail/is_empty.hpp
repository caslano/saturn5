# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#ifndef BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP
#define BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP

#include <boost/preprocessor/punctuation/is_begin_parens.hpp>

#if BOOST_PP_VARIADICS_MSVC

# pragma warning(once:4002)

#define BOOST_PP_DETAIL_IS_EMPTY_IIF_0(t, b) b
#define BOOST_PP_DETAIL_IS_EMPTY_IIF_1(t, b) t

#else

#define BOOST_PP_DETAIL_IS_EMPTY_IIF_0(t, ...) __VA_ARGS__
#define BOOST_PP_DETAIL_IS_EMPTY_IIF_1(t, ...) t

#endif

#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BOOST_PP_DETAIL_IS_EMPTY_PROCESS(param) \
    BOOST_PP_IS_BEGIN_PARENS \
        ( \
        BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C param () \
        ) \
/**/

#else

#define BOOST_PP_DETAIL_IS_EMPTY_PROCESS(...) \
    BOOST_PP_IS_BEGIN_PARENS \
        ( \
        BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C __VA_ARGS__ () \
        ) \
/**/

#endif

#define BOOST_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(a, b) a ## b
#define BOOST_PP_DETAIL_IS_EMPTY_IIF(bit) BOOST_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(BOOST_PP_DETAIL_IS_EMPTY_IIF_,bit)
#define BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C(...) ()

#endif /* BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP */

/* is_empty.hpp
qteHZdJ/yuiCEIhZNT94UR+Kd7COjdbZxYXj0ng4Q7+ZEf/jkr3Z+1C/YsfIDxKXanpQ1mTGx/7Q9Knbe9sgrLaRc2cZFEpd1tcFh6FQLQFUM6BBHKPh2A4b3eVk0luajvf23vYaiRg2vQDf+D66YEIATV+xwuHqsqDpuMd720MIq57DaIorEreIw0l6MwEAY++YAdbt2I3wCNFG1qDuO9OCzqPgTi5kg4rb8FrAg/KEasyGnpcZ+kobPgBwws/oUZHgzAY1yfb61EX3l3CLOp7D8oLhKCpeGG+cWeFedenihZXbjv0blxSjIKz+eYYFfdAOe8iGfoOT5lvosNpjw1cDHv9z0ynfiqG4b/NxALx8ZweYQ4dxHK0+9a18K6i9G23vSo5PGuOwB0C9ddthmtFOby06BiFDdkgvQr78aewNKQX8amw/Fz//uJle2QYQJbw73/L7Pa1KLzIrTNNfnejZQu+UPc3P8406SR/mI/j7A63g2xCc3pt7OP7isbdffi/hnjVyX3QgtZK01G476K0UdNjFdxYfezvePnLXywpP6ypXIu85Gksj9wG2MzpAN2XCjlZHBUIxnqIiNT8PUvuUXVKaWinNVXbYM5wZzT7DhrsAn7z+U0X3O1/LBkUqrIbBt0ENwe+4V4jB6vnEjX021uYXtdTmlSUm5XzHf+wUhv+awyQ6l4UyeZ+sLR4GXsALyTJyT05xHRwXjUsvsc5joH1Mqx6bWOH2Pjm7ekx8J9aunckcc/mqOxHf1fSWd+d77p1vuU7b531yPcAcpaxpb1ZL3UmKkLUz6dr5lvu0XVasUwgotnRT2nvjFo5gpr3ADJZjhXK20TzeA2IlqI5otjLif2RMqbw9rMoKqNIjCnj1g2+N6M5DmAkSpiv/Rb2Lzj/wse/7a1183x+gEfQKbqOnwcLaWGvaSInzuDewUs2GqYde6Y/xnTYujd8KmCKYeTBlMLUwNTDV5iP2sJfAFMMUwpTzQy7wUIfeM9+nm6amHU6nqTcfcGTqZ4075PH/m8GkD05i0F0BUDve5lcR61PXmlmkrrHeTZlr6TKdCVsZ26bCVsC2ibD52DbOEnM411SJrK6VhKtTAyi32CLzmT1Tozbk47iUzfQkuNr+Pn7uh1hfZUHUwxHGxjtoNMdns2oXosOf3vxKrF/zDp0Ath0sXDTvsnZl7aSb87EkHZHJRFftERq7H8G53dXP/8GP1vATqlppYT29PUICrdGhEt/eEk/kSnwnQkoI/VJpQD10X4amYnpKziwrFJKc9qxHuDqKUmegyDkQrfMB6HBqYDZbSf9MYqrLaAQvSYA1XE3ZylSyuEKazUiTglzwzA6UBJkXx07DbwAUpclO3L/vCBhtVNAoNsKTDerOvqbAwJzWURSDdn94+uI5mGesjk9zuNfA1MME5MadFojF8kNAtZ6PYGVok150R/M0MXQzhfekyS+ONjF6UoPulvynqXMJdJqA+N0+uIPqYvxi3ONlN+a0Rzp6BnUOIo4QmjLtUC8RnwjKLrO5BxqCqijXfl1sQ6RnQ/r3Qt7rtQdja4y5fvDBCWWeEwiqf+bYMXyAzY70DJixfo/iEaxW6yQs/vw2aMis/0dcf36mBeOSNOIcF9HTkuRcADZvW+l3kNkN8/IKv+NdmA6YT2DcgBXA9IYZClMKcxGMvEcwAPVmQYcCpoTYP+pUP60Q5o6e8srPLfgGSD++Rf/IZr0V609tZcGnAqeQOYEc05RV2diW5KC8tZ+lOwtPMcEvfUH33DabuZ3Vk7XRCYsNa6tRUfErVdlUAnW8Byv1wVVnsocWlzu6wH7/2y1Ex1NTYut0aXZRRZv+zdmVgEdVXeGZyYQ=
*/