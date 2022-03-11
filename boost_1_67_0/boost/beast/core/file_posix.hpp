//
// Copyright (c) 2015-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_FILE_POSIX_HPP
#define BOOST_BEAST_CORE_FILE_POSIX_HPP

#include <boost/beast/core/detail/config.hpp>

#if ! defined(BOOST_BEAST_NO_POSIX_FILE)
# if ! defined(__APPLE__) && ! defined(__linux__)
#  define BOOST_BEAST_NO_POSIX_FILE
# endif
#endif

#if ! defined(BOOST_BEAST_USE_POSIX_FILE)
# if ! defined(BOOST_BEAST_NO_POSIX_FILE)
#  define BOOST_BEAST_USE_POSIX_FILE 1
# else
#  define BOOST_BEAST_USE_POSIX_FILE 0
# endif
#endif

#if BOOST_BEAST_USE_POSIX_FILE

#include <boost/beast/core/error.hpp>
#include <boost/beast/core/file_base.hpp>
#include <cstdint>

namespace boost {
namespace beast {

/** An implementation of File for POSIX systems.

    This class implements a <em>File</em> using POSIX interfaces.
*/
class file_posix
{
    int fd_ = -1;

    BOOST_BEAST_DECL
    static
    int
    native_close(int& fd);

public:
    /** The type of the underlying file handle.

        This is platform-specific.
    */
    using native_handle_type = int;

    /** Destructor

        If the file is open it is first closed.
    */
    BOOST_BEAST_DECL
    ~file_posix();

    /** Constructor

        There is no open file initially.
    */
    file_posix() = default;

    /** Constructor

        The moved-from object behaves as if default constructed.
    */
    BOOST_BEAST_DECL
    file_posix(file_posix&& other);

    /** Assignment

        The moved-from object behaves as if default constructed.
    */
    BOOST_BEAST_DECL
    file_posix& operator=(file_posix&& other);

    /// Returns the native handle associated with the file.
    native_handle_type
    native_handle() const
    {
        return fd_;
    }

    /** Set the native handle associated with the file.

        If the file is open it is first closed.

        @param fd The native file handle to assign.
    */
    BOOST_BEAST_DECL
    void
    native_handle(native_handle_type fd);

    /// Returns `true` if the file is open
    bool
    is_open() const
    {
        return fd_ != -1;
    }

    /** Close the file if open

        @param ec Set to the error, if any occurred.
    */
    BOOST_BEAST_DECL
    void
    close(error_code& ec);

    /** Open a file at the given path with the specified mode

        @param path The utf-8 encoded path to the file

        @param mode The file mode to use

        @param ec Set to the error, if any occurred
    */
    BOOST_BEAST_DECL
    void
    open(char const* path, file_mode mode, error_code& ec);

    /** Return the size of the open file

        @param ec Set to the error, if any occurred

        @return The size in bytes
    */
    BOOST_BEAST_DECL
    std::uint64_t
    size(error_code& ec) const;

    /** Return the current position in the open file

        @param ec Set to the error, if any occurred

        @return The offset in bytes from the beginning of the file
    */
    BOOST_BEAST_DECL
    std::uint64_t
    pos(error_code& ec) const;

    /** Adjust the current position in the open file

        @param offset The offset in bytes from the beginning of the file

        @param ec Set to the error, if any occurred
    */
    BOOST_BEAST_DECL
    void
    seek(std::uint64_t offset, error_code& ec);

    /** Read from the open file

        @param buffer The buffer for storing the result of the read

        @param n The number of bytes to read

        @param ec Set to the error, if any occurred
    */
    BOOST_BEAST_DECL
    std::size_t
    read(void* buffer, std::size_t n, error_code& ec) const;

    /** Write to the open file

        @param buffer The buffer holding the data to write

        @param n The number of bytes to write

        @param ec Set to the error, if any occurred
    */
    BOOST_BEAST_DECL
    std::size_t
    write(void const* buffer, std::size_t n, error_code& ec);
};

} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/file_posix.ipp>
#endif

#endif

#endif

/* file_posix.hpp
nw11NMJD7JgCKzWikLuzTft+MnBYxTKCquEW062M0Qxv5Khu8CvhrIBNt/EzfROQS3joWo7Lh58vXQRVIkTDyt5TlRzHZ1bMfWzIwGmPjSOtY4ECkCmI1HFQEdxK5ruQGh5G56GBZEwT+KxOzL3h/BY38n8X3RQer2FKjfOUuN88mc58fL4GdgZ1IDIC2N6bPhyxPXdakscqjHtNko6oEnYPlGXupbcSKx7kx7PxXTtI8XP274C5stLlHgJgXLkyOEgtZh9LedI10LN6y24qU65Sot/ZkDyczh7nD21pfu1tFtpt7J46vvvvch34wNROKBnw9woRLAkzyi0DrOJKMXvXZvrfVCvgp+s4ruP/G0rHnUidABXBgp9XuuGLDNYUnDZ7nje/ry9XedI+tWoADXuZXdM4/iTuAdVwYlZgdlOwE6gNkZaOP9pMb4GhxtlWkyCcwGN1YvbL3i/HONcSF4McvQDWccT4zKCvOp+G/bhPoSwOg72acPWTDZGagbuxJWshK+TwHOZaDn7/Z3X1OPyIMhcCPrRhpkyO/e+3fupO12yhATU9O1J5bYSUDo8rMsfLn/GcLkw/vbfjSR1KDrJha8UhRlkXigNWOp6AHQeYBjj+j7mOXIyelgXCSHTYfp9Q37xoTuPhAOVAK7FpuKxgI2t22Dj/rJgg2ylU5q3n7BfYvc+MzcfhuzM+YsUjDof5KwRCm+2JW26moUdiI1wy7wlJAUucU8JTyfsFLreVygFqVH0S5AZKdX0tGfv+00gLMRJSxI+3JkW+hHrbFHyL6d8BKY+7KWW/JZpVKQq8vzMzAfOCugHGnS3O43Bcdi9kVo0zZH/41lsIz3H7fRO93wgV2PNzWxUPyFvDBBe6XLAmwaagfoa1bG6e5VcFaJ2JBQYXzpI0QwsJrAYeE5YaHCBGcB5mt9UL++V2Mc/4hDMHNWF8E3RDaOv4HrG6N0Vf8dSY5vDsN8rn+99UWC/vSXucncDWlQ3Ss2LkhhcUpxe4uFwXkro77Dm2A579Qw3h2Z/fug3pMxTTB+pDzlCdg93bcuqzpH1e2KKVm/GulLoPUuLdY2ZIZBukKfsXZ7heQYc4vcfnd+Bqs8lUdU197pkWOzGbOgmxwwujvb70z7BuxT8v7/3MwPYYRboWkyYN/P8ku9+lB1tVGlk/E4x4Qzf7vVxv+u8SObd5wYFkh7hX4csa4XUmb4dSHkNTwX4GVPXsuQolbzO53ku/C2MamIwRvPMoa9DQ8ZsLN07JliopYuXPMenx2P+eeBrj/dNSOSBAV/CkaR6hGV919zGwpIxrlXaXTd18ubrLLVjDEEytSqbyj7Ch26Kcwox32crdNanIe1bYZP1TaZQX5Pww3g6frjfsA1+Q+ISXGJwk1OlshmA4H/iyJEv2b13QK4iL4K7jkflT0AiDu7LxRPQrADfKQ2xW3hNwcA5OFtMBMl7a+iGWWgomGZuMxf6V7k6lFsMqyT5rfm6BIHBVdLaVr7nelVD43JeY8yB747uuJjKH96Qm5jM01HnopC0OKs1xy6Yb+M6vuvwPGnRABQZUCHxLN8KSh4n5fbwzX5rGCbl5Se16KyH+E1GupvQfrraWpJ6et0l/UmS2Ze+wHN9NfZbw9Se1H2C+Hb7cb7ibVfX+Gqoyze04pvHh9mcycWa6//vPwAcgshDxsBpjWkhxbz2zRXkHQNvQOTR8/2xPeEcvAlo8PvHcCJV4Bg3SF5D1LSHnCKb3s9X4lXsxUJGnqHHzFvzXvlHfiOUt58DpXJChkevQxZv9pCd2NuxIERl0IJx7eW3tlPDeG9QpQggcPdTJeqxLbetl+i7rsh0jG/96ZhAyOI0c7JDvKI1+76HJu7N3u2W7zU7LVoJuZJijiMYfPlzg0iinZ+EqVDImp3XjfDgzi+zyNsC6Vy+x0ag3uTs9shiKFXV833TbVw6EsKGUyil2j6//y4P1eedR7uS8z58i9vVPTm4u77318uIb1b+wzVZLxkq8j8sP99zMfEnIYkK4QFS/w6rShJyERyt94vQRyFf8xLwHCFektTE0iPw8LfzAMHm4B8MNiALPjcyCGkXB8TiuH3humfnkLrVMG1v27d+z7QqU3Fufuo6u+f8o70asQllCInxMsIu3ZGEB+54c3+/wW1WbTJ0nwoYhlvqoK3f752+ANYsin5VN095BytyLxZ3bCzTElpbz9DdAFaHOkTLragwRCP/vl6P/TxJH/+9fl5Mp+Szj99Gx9UKXKercj62IAFyo8ITNo3GoPSb/j6fkHoUlzHBpDvacfnzXMuxQW7LutsP8/BVsrb5OeF1DXNaFt+IQQAM6f6aO356ofGlWfKezWFzQnY3aX3gvdrhSzqOF9qcx0eYPadKp0GtHI7Ih0EyP4VmhCdaA9uKvNUhunqi8d43DTsav2uzfUdqNshR8d7fZHPbtDrvNJZB/Pc6bLeb+uytPm0Ja1PgW8eb3gsMWVV/npYkF5b6JKvHHm7ICJlsBH6beKgxoi9rVy4ms2cyhj6Rp5LLsQmgnYRAVTDHLVOfPKEU4UkEEuObbVKw4UHsfRwGhsrkmrJJpSTjSLKZXZ9sxLZFAjuWAQXyEeGBOqVGuydCAN2KdPSepTP7QO0f+Zh2twVz2U288HTzfX1KL48MlDcyaSi2LlzqtZhPSjCI/72P+xsDvK0KY7UovYrq4TAFFyHIptLEHghCLuTzuiP/7rTCoANN+kDYL9/fT8hTpqYGdEw7DC5dpWBEARyq5WzVhhiJob0zj7B8Ko92tszXmhAzqP5Jc/M9WKaBMv4bUAVuhq0YpkDxBqMYZYahXOfCNiB4ngi02MKJallBgncxg1wHl64PPKy9qM5eTLqH3LlmA/g9TkKaQpOT/xKXkFzZhhWnGhXxsAwoV8la2kAhAhygf2oA0EyRrlK206pbgOJIV/d9ArJsOzZ2GWf0n7Mg2jYenVdOnnWtGkgspZfUoVo2+9zDnWdKZmPyysSNMFGs/thQAgy1lwjrfJ6H2G7gCH1Oe/Q+La0/NXJNg/StQAoTUgQDp1oP+vni1OwX3ZOKC2fiIBpX1zION17JdWUvmDzMiOopSQ5KHgDHLmaxBxbc3RMak7F0+SwSONPiMB9hSLYsLkcAcE0mONdeB/i1zozfdxM5eeUn9A8nxdf3WY4fv/1cL8K6+/A6oMHimWxGdwTNfWF0sCz3/xMq4lNkNPb8OhsEY/iXMUD+RzWTID4/3mZym3cwidM7Kbq9VDiDOkLNAKDBfatRVo+lvpOJ7qryROskJ6nVnqdEKXxRwLuot1+v04w1UxzTsHmJuGUwMO+1EOCYWnDMfi1awaO3sPw6aQAxff3zQhkYIddicfc0WM22lc/SuUXe+5Z0tMfzqN4D1fW9S8OOA8k3OfGuGvBYXiOqd+EdWxBUe9WyNKGJyT0jGLKdLusplVe+GI0NyOn85H7DFxsaBs7uLFlmII0UYTRh3rNRVyP0dQuLgYZTa2GFNXfrDmWZSUubmOivZ4pE4Ar5h0MnxJeIAi0Y4VWg1cubz5myDJWrCKUIX/XmFYmtIY5DW/xO7DRIREQZZgo0D76Bkdn9BVDGq3JXJwBKt6zwDC1TY0v8UuZdbAcvIUZrI38f1TYTpoxuxvLb4ttmRH1WIqN+bu7lyYdJABgodhRfHJTiUNKD4CeiYvIHSDgm+DjgHbsXtx+NFhVfLYGnknyFTQxrt9As/iYbfR1Ts9XrswJUZOzJmzum1g40P/SQmWH456dzQjJVn5OyDkKyO/vfmr/uFw5CoGjkySCWO+Ubb41SDmVL0cI8Zas0HxbpMmT1SYR/CitOi739BObv0SYCxovJ7L8MXOAmDqNqFqR2lfXyxO5VhRkQmQhps7JflzOmbFgmxtH398JUpYLnBxBgWbSpvceuWsn2HZz5YKt0XmYzHuqs2q2tEs+CBLenk6umIdwYzxdTr33qx06mwy2ORE5F65uSvFxcM0Qza7xBLeIvHYjph2oAJFB/ZuhUxyx1lR96fMJS6YP9W3hTt6K2rEJBlJAgWyntkvqL/NXTrMCIItKMY+eb8kAIPFl4Zep7t8II1PNWc8cgqxQxq3fPokTrC6bbJdCHhZvGRNer8dc3JNIeRxz5VOcvcOv+bdFdl4kJT/nDttLTh82oofwRrK4dugdrlIjNYIoii64ETqhhEYbBrkSlTjuQfftBU3eMFGEr/dRjLf0gUT/SnZnxe0Ode3GqzRoU/ppsh0Sz0uaxGUjNerw1O4sIf8mQ+zg3ZKNKscmYqo117YPS7mQb8PcpAcTrbh6XXs7ytTHAFY+SiKJ7I4yhhoaGoNSFZTKBAsE4KQLSAbnXOlO7pHCVrH+JyUjcN9Fwp5YnyeK1Rt9h2/7WlOGjQYJbUXuTaQFzRv7xvt9/WIZ73LNp5jUm/WRXS2nCfUY57fOSvSzKID3sQaXh46c95Qk2cRlyLDV7Yz8BL0bdBp3mDidgOBmIZWuaLoUhTp2aJ5dCHD82ve5Cz/Tv5deOszWGssNl4gp0OuZzGTIje81ZfOxvWUajqhFF8Tc06lQ8wxbmLjXOBcKGbQGNHmpkn71oOfs75+Pig2UlJI1wzCy/3+qmCR/ysWyJyWYDrmQrRXLWm+mw+Q9yJigSoKLjRMPZ6b2cmdbhpF+DLOXpw5Mys6RfFtCkFun8XC6wOZR6Mp3j884jNrJ/q1IpSVF49fOzgo+C9nOO904toKqK1IeLRIfaDPeIDj9Kow8fAbOdrX3Ljd+rvcazDM8NA+P57sqZHfeh/RM3rXnOszP2SofFOkw9afMOP0Ifb/2ov6FSVV2Ks1rdiXrnnyEgxXQJxCOPS6kRTUQkW0NojzKuFHVWBPndv/oWH6XhZg5OTrSoH4ph4M44q2W6PlNPOmgZ9NGqGMRpfEet+WsucSOgr1eA3wnaEqqysbc1D41jx8JOCBWXmwWORHKJIL8uMFBBFy+xxrRWgUp43wv3vKm3eLe/Mtu2vQ8+uoXnmnC4XYXDOdC21H3vN7X6HNntUIiLH77Vksw/WpUVVh9eE/q1bjtkc3Yi9MOjB09GONZyx83OblEZVhjbdzs+2YS5zZ3B1/P4wAav5V+2SANV0MOAadpuzLxDKR/0vBJbUET1ntsOXhjlz/gofO863A24YJQ8B5UgIhIiZG5hgsQtfpuabinTvHI5NdM4aDLvcgfv8/04CGRvLDkXPUvZrp6fvkShfQJuCU4AioWkeqPy2jcbd+xm5YsXcM6zPn6AuOXaktSwOjqn20NmRiq6uiQX7iiEGlOqZGex+tv0r4BxhNKz9v1gme7KVMjXXBbe/QEl7awaNwtOYXrt5G97dlXvV9NX5JZpZfuJCjq7+42Um8GAY5Z2ULCF/tqDy6dlWZA6H8jvlKhoFoMu7uLZO4BUoDOINyr2J8Nig702hst3nczPGCem5YpU0Rb/N8abpPq0lTTPGmDWvhYkNj3nSx0JcTf326D61cXVIlp0TDM334iNDXY0WbSyi31uDaqo7VT5JZxLAWCy7gSNb1PYyMa6CVgtb/KvP0mNqTRnYey9OceX1g9ddqjv8tKT+ldNhH3YREFYuHFy5vzN4QBDjQE1cDzaSkRS4+qDrFOMkRPje9k2vHLpytTE4dy4VDDQWqkj+F++oExGeHvSClNe6I6eCgjrmkchlg8/pEVMtCOIAN7D8qADZvBQMDhQMFEumprF4dwIt2m3fhc/wvwQddxOOW/2D50kgwGX0owgGIzyB06cYiNZIbkumIUe9eEF0mE+tz+yRwfh+C1WptyydAv8c/mySpqxI7PKmaPJQ0nStxc7OSWJJlexMoX0lAniPztDNX7nTH8lmqZP3CPe0ep/wdBSbbCstmU1NVAR2TzC3Ru93/IqXiZ5JITFh7CWpc6yzlNhK7ShOYAYexuxbxWLssF4fsj2skfF9m9UlrAgMrPgOgTdO1VBNJvc+pre0QBNAp+b6EozkTravRs4T/etpfwGOzI+QnxB50TAPegf49FeVg42OO9eKdZUXPFwYWULPUQKvmyLJ18ksUcIVKdZQC4CBwgXC2Ny54SY5Us4+KX1gFeVvT8zw7q9R9uy2/MccpDxEY9N//WAAsuLkQOGzVsei/9YkepJW3SxX9QMhMXTm90deXv6GqglsNxCnagEOgKMydqFeEFxFPhZe/7pnehwMPZWyOULHRIUMfl1J7Hjd4DdV5qjlIBfn7OTUAoo2cnDoiy+SBqnXB1blgFem+0DHoCCJjoEVaXcpmYBXXSiTtM6T5nINFzKHSnZ965qhycPfnFIle7Npn2KrYUmIAFJsByMg1NtPeDdEpOLJZ8Tli+c0LArClvSCjpir7KVYllSKECmBgvc6dVx0cggXRtk27hx2tCUXSCPHeUaGc7ZFqG9sM5BVyCRxQAfLuHs3nyCR3H0T8CTxZen4ctaOON5efauMmFvgpwdXhFTIM3HlivxlR6RpmXeAGWHukqHFBsP1ngICM1GdrZOtIB8+hNDDXgVBgi63289IUVFoYKrCueM+wCVij0PxQFPl/FGOKY8Y4FqR1EeT9zE7SBihkkAYdBjGDIHr/rtszw1xuDXOmePVo1s/hhwhw4XjsY8c2Pmt+HaSvvUcgHIIabXkKWC29NpwDNmYNxEDiecFMYTZeCLEQF6kMzbYjc94Lf6stlyzbIzD07gOiahsPYYdZXaYPlKTBHUkQ8d4PO9TH4BAqDnHohVhCIcDVY6lwdadQuF+5JJq8MfgxJMIrwKliMGD/9PNOH+UIMynjmcOiYdxmo5NmgKag94BkQQi5DtyhkiGjC2mSi4llyOb5esQRUDIAV/AJgOrfh29dKNxxq2ia7WsoX/Z7KWthwX3nuYwx0ZK3jEgIB5LuLgicqwYQoQ/klduegR7go/koPUhAMLYmB2NHitCv7aAdVVkXWSUy2nUP9A5255Xfj7e03TudvwRHp+NKM6J4zrWbsgFB7K5L8lr9UCF8O86BgfSJat5tc8ski+SvsmsarA4fJiOPxLsoetD+ttCo5wwMfJ/Df9rWnHyTs9i8ui/6H+qqK+InOc0AN/Lhfl8Ssc5axJWHFVw/Gfy9lZsZ/bFuVHCChUoO/JnW9A47lbY7HXuH18cSbHkXxwJaBuergPwYVJG9+jmj2JC89d07ArOHjufn5DUmgMbPLQrYExa4JiKlNYJ2CvXF+yaVmdiiggXP80EDmYYSu0WSaXYRRknTrCrjstLmXx2qSjn5xisCP7cBy1CoJtGsMLgnqFMoIs/XBRfV73khWrvY76DWtZv5MgnoNlVr1bkYm1xEZskCoc0XoXIdZ7QsWT8Wz94wXJVO9IG3NpYv9m6q87w1Vd+PYtbW1vhJZ0RDjmlECSqsJZI7HB/2OZIyNDOfJxGswgtNcil94GNDQpH0fEqmp4+4ivOMnzfpEe8EFxxMlOjxvfOFqAUBbDbKKNuXV9elMNtiFYORBJCFTpFSm55QQ/MHvRWhO7d5s3elm1ssGz04Y7gyEIJO+av2/tJK+V6UiyTnsboKbwf/2kf3U+Nrp2QtXWJYtLwwsmqeNEjcZBTYYlFNiiDqrLqTpFr8AoIold21IXzzFFeFCe4PofRyYhQxFYFTzhAXDE5EhW7j6qvtJq3ypkbPH0JiVb3E4gxRCZP2/0zTvHjmUOWxDnWXeXNVFaL4QpyLlPBHEPXoFspT89YdlPIpnvHayKLoQlQUioBdkGapeTxI94iofFE5LgMt0CaSv6IX+f5Eghv9OrM0NaFyoUGxRoXYUPCEc1DfMBW5GTPbhFKgtazVoYo7RzmzrceMZflO2vCBZDQU6WYb2OKR1VAqsD0Lnrgq0LRn3fQaQK3iOGr0Dm0rzjFKS8vz75dtIvImh+zJkKUdd9yXMg9llHfCR9ogXgzimdqGWNpIicuDlESROvs4CBIyC7h3jKEEtpc/BzZU4Rm9gL0ihi7vMFZ6XQYN7vaPrKXeNjUWAyyS7GRw6zaGSu94PBTwBrpTKkh/2af8otbIilAFSc84ruv+zSDy1eJHVfCB5GxRulkRDhDpOy2Su4SqYFEQJSIPA8c4BYruxl61h7MQ0fF0sRb9gpJADftoRIV5gttMqvdTWYgLbIYa7khXcZX9vw4xxDSZ1oyIQiHHDjS4XUux3s9d2Vih73bkNV8UuHYEgEAPDxDgqDKR/s69HPlTcLrlkRpuXTNJSEJtFx4Rm9sNq+FTK7X1gnNF1kSI0EwnKWKE+GTaJMHjSFmSvC9nFKD88t2suQJ5MLxFp0AYq7Esum0AfPTAzTjAEIzaFuvjfzLgcQ0jSv2WrtRnv2qhL/Ccrr0jEr/vW3jlZhGI1hLWWsznMAK0s+1QYhvnuYESi3uPPfStmf3WJVei/00rlVond1KBiq5u9Bl9Afd7v7Y0EfpWsFNIRZ8AoeukkkQMVVi3HQaULb3e+j2i8nKpEoFrOwZTa94yqgHxMFznvUMUbf0mWU74IVoVyirGqKE2Fg5c1ASRs2DJBNmK0+kZGOYMt9vXzlVp5U4c91gsx2qa2rDN5dLZfEiqvxiV1YHjr6SDUwmpRdgO235PotBZcWmjaaZJQwlxiiZgqH8S6IKiIwsTkpnY1jKWH00VXtXcP+7QIaUL2xGMETRKwcbYSzgjaWsuCaUVTiQvOlUKKTiJ/OzgNrObWx5xr7g4TEJaoJAT9b5gm9nnBSg0GsnNuCMBJ+LyY5DTNyZDEJsPxkDRDJphz+RxCfJKMIRy/nGvHrQmcOmKAonwRM64UFqQ8TdCgFtIxzhzBDKbkBFGpuKGE3Li9YEF4Db89nua5om09V85SOPDueP6l9GdNk3D+UFU7LrZNKtIhRiC7uBTRGCtTSFIfSIV3B6huYqBJ2UnMr5lmL8B3uGCPx53Z58InpYmklNdJI5iQq5QpRwO6/qIKl0kIDdFJsaeGPZtNthhBf/y3wDTzNEuTOAwUQ7o2TcFb2zjSGVbaa6LzMsw1iKsngOD0z8Co3ua1JVwpwiJCkysiTE5sGXMyMJGGnZjEDfTIqABQBIqwxGLB6t+fIegb3o2BJJCG5qswgDZy+QzA+qsRnOZTD2jaz1d6MPRMoF6Ddg92KFe7Tc2WvSwfEpQJnxzUAdKff0yqd6EH+cJ3fWNZWiDR51zeDlCWDFpqmaSIEt7mSQiAKCUKtpMRsDqcknlQ4=
*/