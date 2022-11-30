/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   dump.hpp
 * \author Andrey Semashev
 * \date   03.05.2013
 *
 * This header contains the \c dump output manipulator.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_DUMP_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_DUMP_HPP_INCLUDED_

#include <cstddef>
#include <iosfwd>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

typedef void dump_data_char_t(const void* data, std::size_t size, std::basic_ostream< char >& strm);
extern BOOST_LOG_API dump_data_char_t* dump_data_char;
BOOST_FORCEINLINE void dump_data(const void* data, std::size_t size, std::basic_ostream< char >& strm)
{
    (dump_data_char)(data, size, strm);
}

typedef void dump_data_wchar_t(const void* data, std::size_t size, std::basic_ostream< wchar_t >& strm);
extern BOOST_LOG_API dump_data_wchar_t* dump_data_wchar;
BOOST_FORCEINLINE void dump_data(const void* data, std::size_t size, std::basic_ostream< wchar_t >& strm)
{
    (dump_data_wchar)(data, size, strm);
}

#if !defined(BOOST_NO_CXX11_CHAR16_T)
typedef void dump_data_char16_t(const void* data, std::size_t size, std::basic_ostream< char16_t >& strm);
extern BOOST_LOG_API dump_data_char16_t* dump_data_char16;
BOOST_FORCEINLINE void dump_data(const void* data, std::size_t size, std::basic_ostream< char16_t >& strm)
{
    (dump_data_char16)(data, size, strm);
}
#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)
typedef void dump_data_char32_t(const void* data, std::size_t size, std::basic_ostream< char32_t >& strm);
extern BOOST_LOG_API dump_data_char32_t* dump_data_char32;
BOOST_FORCEINLINE void dump_data(const void* data, std::size_t size, std::basic_ostream< char32_t >& strm)
{
    (dump_data_char32)(data, size, strm);
}
#endif

template< std::size_t SizeV, typename R >
struct enable_dump_size_based
{
};

template< typename R >
struct enable_dump_size_based< 1u, R >
{
    typedef R type;
};

template< typename T, typename R >
struct enable_dump :
    public enable_dump_size_based< sizeof(T), R >
{
};

template< typename R >
struct enable_dump< void, R >
{
    typedef R type;
};

template< typename R >
struct enable_dump< const void, R >
{
    typedef R type;
};

template< typename R >
struct enable_dump< volatile void, R >
{
    typedef R type;
};

template< typename R >
struct enable_dump< const volatile void, R >
{
    typedef R type;
};

} // namespace aux

/*!
 * \brief Manipulator for printing binary representation of the data
 */
class dump_manip
{
private:
    //! Beginning of the data
    const void* m_data;
    //! Size of the data, in bytes
    std::size_t m_size;

public:
    dump_manip(const void* data, std::size_t size) BOOST_NOEXCEPT : m_data(data), m_size(size) {}
    dump_manip(dump_manip const& that) BOOST_NOEXCEPT : m_data(that.m_data), m_size(that.m_size) {}

    const void* get_data() const BOOST_NOEXCEPT { return m_data; }
    std::size_t get_size() const BOOST_NOEXCEPT { return m_size; }
};

//! The operator outputs binary data to a stream
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, dump_manip const& manip)
{
    if (BOOST_LIKELY(strm.good()))
        aux::dump_data(manip.get_data(), manip.get_size(), strm);

    return strm;
}

/*!
 * \brief Manipulator for printing binary representation of the data with a size limit
 */
class bounded_dump_manip :
    public dump_manip
{
private:
    //! Maximum size to output, in bytes
    std::size_t m_max_size;

public:
    bounded_dump_manip(const void* data, std::size_t size, std::size_t max_size) BOOST_NOEXCEPT : dump_manip(data, size), m_max_size(max_size) {}
    bounded_dump_manip(bounded_dump_manip const& that) BOOST_NOEXCEPT : dump_manip(static_cast< dump_manip const& >(that)), m_max_size(that.m_max_size) {}

    std::size_t get_max_size() const BOOST_NOEXCEPT { return m_max_size; }
};

//! The operator outputs binary data to a stream
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, bounded_dump_manip const& manip)
{
    if (BOOST_LIKELY(strm.good()))
    {
        const std::size_t size = manip.get_size(), max_size = manip.get_max_size();
        if (max_size >= size)
        {
            aux::dump_data(manip.get_data(), size, strm);
        }
        else
        {
            aux::dump_data(manip.get_data(), max_size, strm);
            strm << " and " << (size - max_size) << " bytes more";
        }
    }

    return strm;
}

/*!
 * \brief Creates a stream manipulator that will output contents of a memory region in hexadecimal form
 * \param data The pointer to the beginning of the region
 * \param size The size of the region, in bytes
 * \return The manipulator that is to be put to a stream
 */
template< typename T >
inline typename aux::enable_dump< T, dump_manip >::type dump(T* data, std::size_t size) BOOST_NOEXCEPT
{
    return dump_manip((const void*)data, size);
}

/*!
 * \brief Creates a stream manipulator that will dump elements of an array in hexadecimal form
 * \param data The pointer to the beginning of the array
 * \param count The size of the region, in number of \c T elements
 * \return The manipulator that is to be put to a stream
 */
template< typename T >
inline dump_manip dump_elements(T* data, std::size_t count) BOOST_NOEXCEPT
{
    return dump_manip((const void*)data, count * sizeof(T));
}

/*!
 * \brief Creates a stream manipulator that will output contents of a memory region in hexadecimal form
 * \param data The pointer to the beginning of the region
 * \param size The size of the region, in bytes
 * \param max_size The maximum number of bytes of the region to output
 * \return The manipulator that is to be put to a stream
 */
template< typename T >
inline typename aux::enable_dump< T, bounded_dump_manip >::type dump(T* data, std::size_t size, std::size_t max_size) BOOST_NOEXCEPT
{
    return bounded_dump_manip((const void*)data, size, max_size);
}

/*!
 * \brief Creates a stream manipulator that will dump elements of an array in hexadecimal form
 * \param data The pointer to the beginning of the array
 * \param count The size of the region, in number of \c T elements
 * \param max_count The maximum number of elements to output
 * \return The manipulator that is to be put to a stream
 */
template< typename T >
inline bounded_dump_manip dump_elements(T* data, std::size_t count, std::size_t max_count) BOOST_NOEXCEPT
{
    return bounded_dump_manip((const void*)data, count * sizeof(T), max_count * sizeof(T));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_DUMP_HPP_INCLUDED_

/* dump.hpp
X14IQB8AMYT1Zd0cL3wEXm3A3HfYAe4svnhE82KxGRMzE0hySkpM1S1VW1LJmjrFtrObJrMmJjdcSX6vb1jb/9kyIpt+nomrDCp70VegD2niS6LvdR6yJnFsD0aeskL1Xn9Hnj//nR3SzDTA9Sde0uzkXqU+LdgBgK6+Vrf0totLdmVPQJ8L2RQzNZ7uFUveUSxs9kP+TDPHvmQYlt3hcuDuG2F0UYfV/LnY4VXXi3vzVbc6PxpsfeM0U4UpMC1IuC4kwikPoue9yLNKWDJQ9a6u37SHI2wJDo5HMLc8LVltihTeUCR0oej9HOWX0DP260U2Mmlfz/Uw6RVa3+d3u5Sz+iAK9VHgQ8/YWN96p8uQ82RhcQxK9YWBdzkD2dNzhMFn69UlafLAx/drjPcmO8P2iqRh5PcQB8vxq5owkoVdlPmtxtq3aCwbbMFZ3s0R3OneOUvtgEz9Isr9tCTP/QXhq/x5k1peA/g5wPAzjnj9ucDw20PyvX9bmGr4AaA3/DigL7tJIYMLYE/8rMe1z/4QWOktuNCbhwt0nF/Y8VGH04FeYdBp2A78hdvnyxootTQejtIZdu3LMuPWmE6/XwtAyWLqVPXUvd7mYrOpyRwsiRENtsNNgXs5apnObraPY63aa4H05BkefU3A4t7tgpr8diZC1VlhOAPlPWmF2nGeqPNHweHzAjsKwTAynq4z3sOX2WFs7J7JHnzT6YoAScE5sHbDJNVzArswiCHuRX0QfjSEzvYV3X+D2HWnXTXjcJiawMgKERtXpJBPmk6TzqDGihlo9ztYfBkQdVFj0Oe/2dZIsl/fdYbzVR+2ameLx+JFIvV58+NZkbBJ5fUDObWXP10/MNmxL+T5TKk6Uiqu1hOYH0z5JaUeV1+p4jZ5hkh6nsPhb6O2/kmhMxBL6bwXWEMr0t7q0gf0ABKOE3OCq++R1k5HZVjrNDjmeSw4jbS6QgFoXigTUWlTLk5RcSUm1mln+FfZMj4XDbZa+GrGVK3VLrKUUpb6IjjegagUexfT5ZJBYqc1Ozt9jD+5sTypwB108xg6kQcYGv4OY80f9pwlBN4u0z9IJVVD+brOYtuh2wTJ9N/JiNh+Wnol5HgjoeZO/V5Ld7gnLE0ox5FRAAs8SQg73n2jQEFqpQzQ6DRseAItOJs2f5Nopn98pUltaK46It9cbMPvXNjOkGkBdPd3CrkBlKMfJGWL7c5Jo0GnqdfF8Atx3a5gY2Q5Bbfxg3tglmKhewszpR6+9YQ0CM7ZJSLnhfFc7ai/LWR42xKNfm+gpVsBkBvGWKEhlcY25FjLQRGymfpo4MQp1pgdM9693zvaNYi8NH/kghoYewYQ1mh1DBcDUhI0tZgRlMBj757TWktf1RScgBJEzgo0vt2BNXTs54Oh6+1HBDObtBC+qTgxrmH5ULhWCBOB3IIq3PnD9+MoBERam+n1UUS2UW1EBUPeZW6FKBCNBofUc+bFJN+GQRREN1Qtvf/cf5Gp4vTampoeBKXjyhrkVK6JJWhYwtFytWFwkIwWxmgxN0POGAPt5N3Iu2Y8oLhAnk+idm0hPxyH6pAlM96mTI8myf8+lUAqqZJE424mpfDWQjgp0XA34muIw88dsR9CUjq9YbDXxHbG4oY/oq9LnOa7tr6BFBKL8FvfKALkey/MZdLK/KZ+y/XWQi/JGc8zRi/iokXEHvlnMFGRDgXXaFNKIrtzyHf6DbaXBFrahlSZdxquuaWMWU8vS6lIwz6U5ccUTJPX7rcgt9ou7Mk6b5pNd5T86KxfRrCYGp0C+xpnN96yQTcSkgvm6w8mJGxq1/uydepCuTHB3fGyBwa6807N+79NP+SHRpMfmvZjiIm09KJ2nLNO7Mc2+NuK8oDZBJZikvovbTmyW/P6Nv0hgWornrcjPS76M9T9c3LS5DBSnVNixHJrM1MRNEW+sr3ylX0FGuxkQg/yWzntEmoewBQuCok7d0AbnGLWgcWcsh3HoAyrI+hY9t1aOBy98vy+T0jBQ+4sN+uP5hwoHz5RtrqnrIQ9o0Ef6lxFR+GPnApwnhdVRU8Te3PG8rL1GbXObMxBUM1wwTdDQ5Jd8P3W4V1xUHX6kURBWUbBEyueOQz35kbZVelP1OJz0btinKsOO5d2d/8LJe3d/TfayMuELb/OItjz8vFxrOJ+gJ8c1PWkKuGqbJtlXu7/Q6k5KgOO8MVMW2OzIXFpVHg2IiRpYeXEid2hu0B2J3OOsxb7+w8UhDeBxb+KB3UbGB0I6ullYoUGnaKtqgd3A1QQX+JmoxHzaf+WzKAX0aLHldRuxZZaIcv7i6YsXqQfZDQe4u0+4nynu06Ci8OD2t873IQxGlmlmF3HCL3tX8aTLrJfhWy6eA/O+FQ5h6r1vG52M5+pc+c8GQMnYnttPdlWf7cJJVlEZZ9XwysJf2IcPnsnYxWDTuaHfFHWRa1qPqfSgqOJPOauvM9ccVOmP90xYLJ8BmV9Dmqx5ZKgcq14iTOpSvkyBWVw3r/wC3+wNgcaiRzeIBTW7u/4UNoaawUSi3EbT0XcsqG1OsVjVqlO3nzv7qetp1ruyKu4oqbD1Km4G8CkqQFFNN3FOdvKBbUamVR5gXkFvFILVc/lojHg9rhyS1Z1IxXjdXeFmW+glJqFKqgQYQfrcAVl3ibqGudh7Z57YYV7R6l+0VkAghtGykv+8HkyRDiVWURgzMobiaeKRpW9zAr/rFamWxWLAEWb8KtoVsHI/oatlypxuw6scAXTsQxmTE01EfeYqrOZeA2FLnlTSqdUpvEzKUo1b0br+WKZQmVhvbJQ23QWJJFoQLabmVLopqqelSRzFTtK8SrJbun4luoZURRN1ZJNm3JNHWJSeVemX/5IESQ3cH8AfyEpQAD/X786lc0EKMVq9JG7h2IYSwPAQ90YE6XJinaHdEKwlBUGbU4/gApxVYsv9nkTKtOzcLU4yaKJFB/2VhNn3uwgmJXI+bHjrmSJcTqJjnIuktpAPLNwNQROoRYB564gaVARx+EMsiQvPapraVoArweeqODW5Mrx/SYoE3MG81DRpAkQa/GWpMQQjZTYAVHy5iutKnlmlLQRG4tmxXUakHKuFTTsDVeS20AQUwvdsqGll249027/vNWLZCKkIpdG2Gksaf6q7JqB1V7WBVXqzOF/EodstgKmtNXTSsYeFgbRroayE/VQ1gImy1mG6OZ5xnwYMOXhaOkMzeHdKScf4vWC7CvxMprtGhXGvOX8hv+g2qtYiX9JL+Jh480vkxW7pU3HK4pHpHfjVcrIHr0zZQxuooaOIMuhHBpWaGACTc5uEX3okhmjM9hMkQpmpTOIyxKI756f2JTMeK8OHSnLuM2V+qQg88CecZnFokkLUqj/fSihUveGpNO4wGNJe4smOrIArlClDawq6Vvg7ay8kQg4hwMcR4cLJR30WSrz/EbTUFv7o+YoCZWpIhLpcIBptTXxA2upXCwoC5+HzU81xDdSuWLRDZQkh5gZuhszJwubpKVM2vsVZHWYIzWwm1Nqg1/ieTWz7IrPpshENFUZ56JEZJ3ztkgX1JjNePc0UZZOC17QjVgDYxbhJ04I0FGhbQWtg13mqJSrEepTnptW51cruDO0HxEVNWFbe5abr6f5z1D5Z1gqcFrZa5KIZNBLZYq0DKtQoGaIwzxFTWJQ3mG+TdVEL/FG6frYTE+oz7lhiwbySlfUCbsNuY0PKZMFfo/ECcR4b+aPGY0xYSuITKDC2JhOzpzeHPMsJiewhWrT0znt6jkrIAtOV0ik9mpW+itIPpOZSEIUXi0klMeEn5WaX8N413ROlXhXNMgCKfuDfL4/GGRiUcW4MMQ7trhyW3AZvRaBybkKxqz6d4Hir8TmmZeZnzWcsfE9MMrVqLeyO743+KkZpqj4/GvXTZxmPmB6KsqiK6Zah2BBdVyCPieKngdZ8iRNUgmzfgDJa6POx2CghkXuANXzo1WZXWW5LW+NWnjGY3zU1JFgTSpWaDV0CtqCI6WS9OEZZ5zuAKdJ8ZZYoBrOgbhnWHuoaJZ9GZAGV5E9GZtf9hWFW0/Bn+74lh3cpmXZUNT9SkmMio0uSuLirylLlvQAmKSybI1sl0kMgTCJkFc5h15umUApvqcxDj5lGheFuZ4GJbZh0sxv82FWoWSiRinQFUlrCdyrRQ5egSBaBQ+0As53CdjL6Bt69qe0AlS4BOhn9V8//DUa/ckV2PpFYfy9uv+5qv+5P/wqjbjPJevJxdqcRVqVCz8fvP9SGn5gHr3P5Qv123j7bqv/vHL4rDd80Th8lkOtxKeXzeUU/dv4Ojd6lENO9XNlfLe+f6Opf1Ma2mce2WMe2pXD9ppFc+O3meJV6vLJUvd64fgsN7zCPLzsjVnzHGnzHEn7OD88Tzc8L40s5DeB+V5F5+eXufKeavNISXtvjE3lL1R/Z45IjMUkxmfnU62/H2p7+y9tLTKsdHhA6WDvDMNd8MtKWPrQoRb/EexgG9NwG/NwC5LRlqOHl6jl+XBj3XBDngc7wqR0qJ4rNDpGj3y0RnSLi9GU9XCZsv5CweFiCIMVJTdmtMRVyO4uHhtBuGL8E7kqZRG35bbVItG+cL1Jc8A16JPlqmSL9cbmaxzj9Wate0OCLvIhhbT9kvhyy46AS5VkWbS20xJ5wNVdK6yVlaau0mx7PniKazkiecss3/ZIN8q5c9PSza3i60qPkv4aEWLgexm5+Tl/5XIeDJZRedfUBKleVCug4ls00RVwbTpg0fH5h6jz+sQrGs2saUr3MZTcaLVbxtxRLFhYvuuRvcDlP6fgni5ZbN8NGQGc75GIsletnRuyVPZQEDaXO7BvaTuGPNhrx1Y+0S0LEy5ZI4IAOkCAwD9Bf4L/hPwJ/RP2578/4X8i/kT+ifoT/SfmT+yfuD/xfxL+JP5J+pP8J+VP6p+0P+l/Mv5k/sn6k/0n50/un7w/+X8K/hT+KfpT/KfkT+mfsj/lfyr+VP6p+lP9p+ZP7Z+6P/V/Gv40/mn60/yn5U/rn7Y/7X86/nT+6frT/afnT++fvj/9fwb+DP4Z+jP8Z+TP6J+xP+N/Jv5M/pn6M/1n5s/sn7k/838W/iz+Wfqz/Gflz+qftT/rfzb+bP7Z+rP9Z+fP7p+9P/t/Dv4c/jn6c/zn5M/pn7M/538u/lz+ufpz/efmz+2fuz/3fx7+PP55+vP85+XP65+3P+9/Pv58/vn68/3n58/vH0B6QADLrmyJ2556C7dI286phU0LIA1lieEtMRUYJtq62wn++71o4mX2nmp47bVzWGDsv/mUfmF7qyD6XVM8/W+DgNhK9zFMS4GFcF2gNvea98KUizc1NMiXr3X7+VU2Wnm0W4e3ZpSvKJPPUP9uSTY3gEeUkP3G+b/GLiNFO8gLlWVdvGa/SdidndMfJC+VgPm8woasbhv4aW7efFeLdjB65eVtPGdXP5i1PZ0WAYxvqEveZ+gqqCbuLaXmkzVqBI1RXDjPz4en4LV/bDYZTDHkb9z4398xzd89xDRcGwawwznbr4qdsR20dLsw2ZF7TDvZcniW1/hJY2yhsITlEnkeeAUXMN2GCqekS+3QFk7eGWjZqITxUNn9Yy/KiIZM7NjR7au2nN2s5tLtjFukAHZ9TwB0rLJCbXJNTi/3c+cL8PyCZbxtx5Y7zHyDRykatqItMlgbSp3XQn2bh3FzcFXyiJWXcIRgBXDxqZRsa1VJ1c0CdnLP2hvXDGnHpHlz2ZQTlmI2FI+UcR1X8frwSUfX5tsduDVcS61lK5TJRYO0qO/mEqQ6/BbsH9edMz0zxSQbIMi8S3MVbmKl/yw7C7uv6a4KPWpIIYamks5dOo1lVEgj6uQolcFcJoQUSGAcMy4W1ykS8qZf7NkhVB8u4UmkwlMZySgQ7yIWzbv1xiYP1TKDXububyp2is4jvLqC5ncjtl3OOdbKFue/YGYWbSEGrPZ5Ps1bPt083alkIzdVSmSOHF+zAe1HAZGEoCQFTr1aExDn3vMVaWavIYRgNVLNZqJshfs1MGAOqdhzMwDQiAarUrzoYCuSWiE4+H0g1068rkN7LXwFU1Akd+UreefA/L1KSkHZiG0hFPGbjp047VLu2Q4Sp12kXitn9gw6yz0msAMmec1ppWX0k4hd4xvXxK6el4PwZ5hGOajUYu2HTF/uA2ALhaNMMcZxxv+jCwmjj0Lh1UdUwQxCndd0yhoQ5RHMDpI8rVT/5wBDC3kpmNQFLswt6U0+ZvYPJUiQnczaKBANpSEsemas3kYAdzy+dzCfDts6X5ZqBRw3PiRoflNhM6x8fICfkIocTS0b/tiISTbStEA1s6DOx0W/f8d2TKjlSLosKPtKlfD6mk30bnHH6a0LPI1N3sbVYuHGBUuoby/PgZeJ6Vye924NJBpPxkTH5Z/KWuxRq2OY+2SjI/VVqAOwlPXJ/T052H/Nrq3XNxNNV5kb0joXitoam8PmLXtV8iE/kBgqtbT7QLwJsAV0Lln5HuqihaEOc3pIWBlN6iQA+U4lM3mE5DqsoR6nhDyqHFyg/+kH8SpVDicIFFMOIsO87BFkdYfNnJyQwRtUr9qfO4t4sNC48ArPFBDKNWsiRGjOzgIGixjDiAIZBa7tePimewxiA2u/HHEIldpZRdVlUCXJh4opLeoLoN3hfhHrQhB+Z5b4VTSne9FgZYtF+7QuVT+f8Zilsswj0vIJCA9Qzf6Tt18Lcr64Ez4rxBiA3npW9RkgDt9xCu3sTjG/mH4GLmdi6mIPetFVu0ABz3p1WcJQBna5WV8EGjO3hLARtL75z6a+c93mPqTloRDYuSQYHE/3RxfYgxbLefYYXYgJLq9tVDWQFz8Ajw145LDH1Jp7T4Z9MAe/HHdKuGc16fP7dQmRlS+hcAVe2+BCUytaJYj4TFMOl1Xeel8Te7qk/Wv/bp3dTexJJnyXeTjbLm+YK/wWNzlkQbll3vIeoZ/26JC8LPby4E0WpjlSXHB3Z3O9CN+pdCj0i9ftlmDIB/U9MumywNwsFx3nC3B+r8qviSILMvfZ18uMBJWTyqt29+wmjFk/8vzOWDn858cfC2umAhaLFmJnT0CYsp16YPbf8OuGrdfmFQJtTHDkgI4L8aZsA9LEUhjzRnQ2nYy5DPrj2Yu5WSlimeRAnodz3yzqwg9zLJVs6b16Bi++DiWEk9Xajq3bhlCQWb6aIMrGtpc1Xp78qmpIRhwDSpw2X+Cl+CuOA8psjld0/gMWfrju7owPh6U8bGDMgSojH0hVTEsYMOXYQvYlYRN1E3c2G1CmbusxlG6IPnF/DtHnS0BQ5od06X0DKO/9/QYSZRajYJPrwIoGFhwmVtpjQy17VQOKgrsZpNP2if4ut+IFLgBsktmo5+a1izwuZ00cJ1/qlFMBD+B5rZ+EkSyDmqkEAOizM5fTXCJd0xLZjmTJUngsUaOD+KKHkVoiYgpPHyUu1q0/uZtINHvxsRZvGbKz2Iu4QBfrf/dOIsvxm2Ehs+wvXsRQaJ/ZPr/KiUlyzpXsBPWXZU43HdBLXBluxjNYwopsuMpZI/7aCJzbhEYwIPUXHc7myKGpu1L/wjSlnsr6iUtlZQRvCfSW931H7x/XpObsGAIAleJ5iqOAG3eqeWilrNguojE/nKmM
*/