
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_EXCEPTIONS_H
#define BOOST_COROUTINES_EXCEPTIONS_H

#include <stdexcept>
#include <string>

#include <boost/config.hpp>
#include <boost/detail/scoped_enum_emulation.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <boost/coroutine/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct forced_unwind {};

}

BOOST_SCOPED_ENUM_DECLARE_BEGIN(coroutine_errc)
{
  no_data = 1
}
BOOST_SCOPED_ENUM_DECLARE_END(coroutine_errc)

BOOST_COROUTINES_DECL
system::error_category const& coroutine_category() BOOST_NOEXCEPT;

}

namespace system {

template<>
struct is_error_code_enum< coroutines::coroutine_errc > : public true_type
{};

#ifdef BOOST_NO_CXX11_SCOPED_ENUMS
template<>
struct is_error_code_enum< coroutines::coroutine_errc::enum_type > : public true_type
{};
#endif

inline
error_code make_error_code( coroutines::coroutine_errc e) //BOOST_NOEXCEPT
{
    return error_code( underlying_cast< int >( e), coroutines::coroutine_category() );
}

inline
error_condition make_error_condition( coroutines::coroutine_errc e) //BOOST_NOEXCEPT
{
    return error_condition( underlying_cast< int >( e), coroutines::coroutine_category() );
}

}

namespace coroutines {

class coroutine_error : public std::logic_error
{
private:
    system::error_code  ec_;

public:
    coroutine_error( system::error_code ec) :
        logic_error( ec.message() ),
        ec_( ec)
    {}

    system::error_code const& code() const BOOST_NOEXCEPT
    { return ec_; }
};

class invalid_result : public coroutine_error
{
public:
    invalid_result() :
        coroutine_error(
            system::make_error_code(
                coroutine_errc::no_data) )
    {}
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_EXCEPTIONS_H

/* exceptions.hpp
QvsLc7zPYb/FjEXf4+mO+D6H/R4mtZwonrrYACsWJioC3eVj5YqHepjJhSDwLTFvRFAXS7PKNj+MjIgC3Zl70rOp4bCPeuIqL5w6jLJ/z/4wxhu02JkrT2La9x1qsEKS9pMhncRKWOBcz5FaXZt1W20P9kxV14daG9gx0rfNvnhVdWvJNx4cYfJN7JhTfrQ7VWerY7C1cCesVDdefXaXxnj8+FTKY/8iGnsQ76A5rv+cNlGbrNLn+ZTTqvbCfGR756r6OJzSOm2iZCPbmIntL+Q8/Hneg8uD7rvhvA7VHw6lddKWvqFtgwMD20BHh2N4bkOpwZ4DTP66CHuVaZvGHnnsvIbDjoWw4yns8xS2EMK2Me9ICOtn3lMg7CTmPQfC9lLY9/enc1cQ9iLmHQBhL2V5mMZZzNsNYW/jsPUmbI59zAzNpU+hmdZYSfNP/E51zeH9q3gOvm1gYOuOQesSiwRgf3IZcdKXCC0GvukJo3HNhl30NvRQjt51HtrlrRN9PMZ56OPG0p+IOTKsx7Q+6fG2dA9vMTQ3Dvh0LCd6q7CPOFZFOdoyqu0Nx5OfidKQUad7Z1pkWHWZpSFZW/Kx6C7RkYQTaAfscL7jTwdwPeAIziicszpt9DUXLrSfmw/kuZgJxnf3NT1xIVFXRxNPDqVRoepNe0IyuQvMdvxTa58S5wuR/vy1g69EeHy25+uWkxQR948xb9+MODad7HwkpiB1+C22e7v4aKrKjXm/w5g77G/fI8rAa5MWlm/Z0wknwzRqn9PaEbfbRErcN14VfCf0dktxQYdaGTijUI5rVnnrb2kTF/z7MU4ywBf3KntXyHDC86c/Rmzj0LYUfzK0Ay5yC23B0JPGMIe2QNw5+qRN9G/0o44Xvql+Hx9YatLlsgXnB68D2xzq3TmwtbfH6xOvj/HID8DPV4F82CjCOr4h4BynvL36S+DA88WC/wrbgXHURL5HsW++KUpjMl9PP7h3zcYrF2cU3s0hD07tYNluCXipotBOfs2cFEvk8Xp9f3Nq1PhRWTIrt1acNis3lHgP5RNl/0blY17BPzfYgjjpm6NPK7Y9OiSl2d71qu21HSd5OzG0vd+tCjHKNL4FDnhgV65NhRzu+O0mjuPdFvCsRQ/u2LC1dxfW5e0B7zjjADW4//QX4Mgz3LwbLeevNA6UbdcTHA6HtMqlMXhXfFX4djQngvPxIB2sdplHAyer7d261HEepF2Yf5Sx3K2qXdyT5infnAnf3rk3xWj+Xg98XfyDsaQclsCXIWgfReXUioQKCdvCeFrmSqFeLY1xNmCOv8reLZQ+B7B/cxpgtyL3fsay+sL/+GUYrZv6oNsAmLeBpcgpVxobiuNmfycT7x43KxTuTKqXBs3qYF+5rQsxvZ/YDziavTzU4Fh+Mhf8Zo5xu39QtmR+TIOJ5n/3dWi+Nh/RlfEOO59Owb7yUZlcPqGCb4rHXPPigDUl6MceG/PMWF/kPF6XY1d9IG8Hzpa3hn/O6Akx19RUtGY/v8udbxzZNZhufLv3wy2uPFEP9xu19/lh/8qMsZ/UZeaUdq74ZJ4XHsphnRB2BIV9/WHU9+/nwhZx2FHzXNgzOOxACDuKw34A8o7lsNuNvFbmnubHzIYiG3v00drcc2kXfDf5REOTlntGoU9YRhyAcoitgPi8P69jU/lGAcb38dg/V5mEb0RnF54v93MmZ83IiQx87hJDwf7oXugrXFM33yJnA+cdzhw+aUAvreJpA3e2siuLZycuCzV5fC4k1ctCkBVyrBTXDnQOq4l4YXowPuAEMT2Fw/OtxfvkmARbGMMn9je2PJ5DPQXtT9Jd3YXzGztTmuTxIN6JXtsVzoP4Gjk=
*/