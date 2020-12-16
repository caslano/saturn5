//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_DSTREAM_HPP
#define BOOST_BEAST_UNIT_TEST_DSTREAM_HPP

#include <boost/config.hpp>
#include <ios>
#include <memory>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <string>

#ifdef BOOST_WINDOWS
#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/debugapi.hpp>
#endif

namespace boost {
namespace beast {
namespace unit_test {

#ifdef BOOST_WINDOWS

namespace detail {

template<class CharT, class Traits, class Allocator>
class dstream_buf
    : public std::basic_stringbuf<CharT, Traits, Allocator>
{
    using ostream = std::basic_ostream<CharT, Traits>;

    ostream& os_;
    bool dbg_;

    template<class T>
    void write(T const*) = delete;

    void write(char const* s)
    {
        if(dbg_)
            boost::winapi::OutputDebugStringA(s);
        os_ << s;
    }

    void write(wchar_t const* s)
    {
        if(dbg_)
            boost::winapi::OutputDebugStringW(s);
        os_ << s;
    }

public:
    explicit
    dstream_buf(ostream& os)
        : os_(os)
        , dbg_(boost::winapi::IsDebuggerPresent() != 0)
    {
    }

    ~dstream_buf()
    {
        sync();
    }

    int
    sync() override
    {
        write(this->str().c_str());
        this->str("");
        return 0;
    }
};

} // detail

/** std::ostream with Visual Studio IDE redirection.

    Instances of this stream wrap a specified `std::ostream`
    (such as `std::cout` or `std::cerr`). If the IDE debugger
    is attached when the stream is created, output will be
    additionally copied to the Visual Studio Output window.
*/
template<
    class CharT,
    class Traits = std::char_traits<CharT>,
    class Allocator = std::allocator<CharT>
>
class basic_dstream
    : public std::basic_ostream<CharT, Traits>
{
    detail::dstream_buf<
        CharT, Traits, Allocator> buf_;

public:
    /** Construct a stream.

        @param os The output stream to wrap.
    */
    explicit
    basic_dstream(std::ostream& os)
        : std::basic_ostream<CharT, Traits>(&buf_)
        , buf_(os)
    {
        if(os.flags() & std::ios::unitbuf)
            std::unitbuf(*this);
    }
};

using dstream = basic_dstream<char>;
using dwstream = basic_dstream<wchar_t>;

#else

using dstream = std::ostream&;
using dwstream = std::wostream&;

#endif

} // unit_test
} // beast
} // boost

#endif

/* dstream.hpp
jnZ82w7pg+Qii5FNyCEk/BzaOFKIrEC2IYeQGu1rOxKQUch8ZAOyBzmOhHegrJEMZC6yAtmGHEaC4vkWHpKK5COLkXVIKXIcCT+XbwMiQ5Hic89+0+Ds39m/s39n/87+/e/8/Xvs/7u/U//P+f7fqWiH7l8tX/tshtTT9efabrv9L8g+Rfte8fTCydgg0XelloY48M8qtNln0zDNbPtCp+k+ReNn9q/+FF31exaWfVbOxZqCnkv3sBI/x6Z52Mde49L9W0ikrgnVIy8ZVl7S2YCrufCTB9VtavavzhB3J195Ut3WZr/pXHF3MO8nsNd17FiNOxzOwt/aG5trwjcz++d/jnaXS/Xt1lZSLuY9VdKBW9LhYTNmv9qC78uJ28C2sC5lVVpWVtkF6fbi8lvnqt/DlFe9LbjZmeKjvFT3fLNXtY7ofuW8nZQtYzXLen9s5ovu40scV1K2vsoy18SVZPbfuySuevJOZ604sYkor5pZ+4V/FP06Lrc7z4Rv77D2DwdZ+/Vt74oskDinkq5Gjv7O1uj2ph7L/n6Q8JPQdR9Dmb9c9Em3s4Wjtk976hNQayg6v8h+6HbyjnrOmKLiycSttlXF/2OHixbnqzx8vBtg3lEI2aLvKPiwlz4U/7biv868J/u2xJvi8PWOwDRcv0oeI1xe7wiI7fYEOIh2G6Z21n9FHDGyV1/asQu2xDMA3hdSJuc3LGeNGI/9/Gb/cEoV7b7QR7uf5tXuZ3u2e/MuKe2CY9IuOEY4H3v9E3zs9e9o2XjSbxa01LEyyqELzZv03VK1+ugurzyOO9WugfYV1QvV/m7Zp696H7+VLuIkXRKnxzvnK2uVKY/TveajkIn8KHnGStcY3n/2tE9dR9No27uv+o1tfllmL/hr4tfP0ZXzan9W/SboeLS3dC5Epj2/IzopjgT+99bLstnp/ED0Ehm3w83ecspHpFY1bHnX9yijTB0PLXeWR3ltCVKb5VpeecgCfoSUl1dB4XRbgek1b5/svy8uwGnKJU7CDHfEGvusVjwRtnbgtpyoe/aNf3NvOzamzM4X/0G0FEqXsgjUsqgdQ70hdZHgapSJ1W5IN2Wg6fYoF0mXx/vT2XqLnqhtPF7beKlp4xPyioqYUngUj982r+FCzXX/lzO47nu39yRNYwkJk9GIThSpvBPd2M1WGt1h+Njv5HytN+90qS61lqTXrZQyt2sF53kK6eWs6biKq9gMZBm//4z8ld+1XHXs1yRzLeT0GmcT2zsXmZPHJZJfuWZZ/qmuoexa/8Ixi2+rxrKnsoXoB9RU/SSe42g76CH67Vxr+P9ZxG03cwyWbG9EHuL3C8in/G7gClTbyHoOD/uYRfKCuGWjZab4X2/zz8W/fI5yt/hfrG7ix23Z6b5MSj8znzyZcpxj+avdB43fQ588iX83X+fX9IWVpU/P9yD9so3fNHZ97szS2Ap9/OUc3Xycw55OtV9h1zHXud1Ny2yJrsURTZhT/I6Bv4vyfbxBDH0deY3joUpnTNXXufqOYECun9c9FbzL1q7sd+uBg5I6O/TYz8+ZY0nWsYPlxxKtYy+XH0uwjs03xxK7WMdObTbH0CMdHEs3x5L13RwdT7Rfqg0Z63pbWNGGjPQB875dQE09luQdVtuB9n3qhGPUiYbtZjvmO6wPvUQf8SV5zoNX6DcertfxbpqOdwlmvCvKwfpEXvF0ubj7HefQV9tD2maZ10kA/lqqbYZBonMFe9cDHTFIR6Qnkoa434/cQAJySU9gjIMWUM9znqDv9P/WsdPKb2u1cnhEr30HkX3NGVNf0vxm5zJbKOJLanL3Kfl14c93hPJs8370vd47E/dexwL+f1nfO/ukzJ4=
*/