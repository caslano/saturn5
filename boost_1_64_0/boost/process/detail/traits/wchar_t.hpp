// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_WCHAR_T_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_WCHAR_T_HPP_

#include <boost/process/detail/traits/decl.hpp>
#include <boost/process/detail/traits/cmd_or_exe.hpp>
#include <boost/process/detail/traits/env.hpp>
#include <boost/process/locale.hpp>

namespace boost { namespace process { namespace detail {

//template

template<typename T> struct is_wchar_t : std::false_type {};

template<> struct is_wchar_t<boost::filesystem::path> : std::is_same<typename boost::filesystem::path::value_type, wchar_t>
{
};

template<> struct is_wchar_t<const wchar_t* > : std::true_type {};

template<> struct is_wchar_t<wchar_t* > : std::true_type {};

template<std::size_t Size> struct is_wchar_t<const wchar_t [Size]>    : std::true_type {};
template<std::size_t Size> struct is_wchar_t<const wchar_t (&)[Size]> : std::true_type {};

template<> struct is_wchar_t<std::wstring>               : std::true_type {};
template<> struct is_wchar_t<std::vector<std::wstring>>  : std::true_type {};
template<> struct is_wchar_t<std::initializer_list<std::wstring>> : std::true_type {};
template<> struct is_wchar_t<std::vector<wchar_t *>>           : std::true_type {};
template<> struct is_wchar_t<std::initializer_list<wchar_t *>> : std::true_type {};



template<typename Char, typename T>
struct char_converter
{
    static T&  conv(T & in)
    {
        return in;
    }
    static T&& conv(T&& in)
    {
        return std::move(in);
    }
    static const T&  conv(const T & in)
    {
        return in;
    }
};

template<typename Char, typename T>
using char_converter_t = char_converter<Char,
        typename std::remove_cv<typename std::remove_reference<T>::type>::type>;


template<>
struct char_converter<char, const wchar_t*>
{
    static std::string conv(const wchar_t* in)
    {
        std::size_t size = 0;
        while (in[size] != L'\0') size++;
        return ::boost::process::detail::convert(in, in + size);
    }
};

template<>
struct char_converter<char, wchar_t*>
{
    static std::string conv(wchar_t* in)
    {
        std::size_t size = 0;
        while (in[size] != L'\0') size++;
        return ::boost::process::detail::convert(in, in + size);
    }
};

template<std::size_t Size>
struct char_converter<char, wchar_t[Size]>
{
    static std::string conv(const wchar_t(&in)[Size])
    {
        return ::boost::process::detail::convert(in, in + Size -1);
    }
};

template<>
struct char_converter<wchar_t, const char*>
{
    static std::wstring conv(const char* in)
    {
        std::size_t size = 0;
        while (in[size] != '\0') size++;
        return ::boost::process::detail::convert(in, in + size);
    }
};

template<>
struct char_converter<wchar_t, char*>
{
    static std::wstring conv(char* in)
    {
        std::size_t size = 0;
        while (in[size] != '\0') size++;
        return ::boost::process::detail::convert(in, in + size);
    }
};


template<std::size_t Size>
struct char_converter<wchar_t, char[Size]>
{
    static std::wstring conv(const char(&in)[Size])
    {
        return ::boost::process::detail::convert(in, in + Size -1);
    }
};

//all the containers.
template<>
struct char_converter<wchar_t, std::string>
{
    static std::wstring conv(const std::string & in)
    {
        return ::boost::process::detail::convert(in);
    }
};

template<>
struct char_converter<char, std::wstring>
{
    static std::string conv(const std::wstring & in)
    {
        return ::boost::process::detail::convert(in);
    }
};

template<>
struct char_converter<wchar_t, std::vector<std::string>>
{
    static std::vector<std::wstring> conv(const std::vector<std::string> & in)
    {
        std::vector<std::wstring> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const std::string & st)
                {
                    return convert(st);
                });
        return ret;
    }
};

template<>
struct char_converter<wchar_t, std::initializer_list<std::string>>
{
    static std::vector<std::wstring> conv(const std::initializer_list<std::string> & in)
    {
        std::vector<std::wstring> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const std::string & st)
                {
                    return convert(st);
                });
        return ret;
    }
};

template<>
struct char_converter<wchar_t, std::vector<char* >>
{
    static std::vector<std::wstring> conv(const std::vector<char* > & in)
    {
        std::vector<std::wstring> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const char* st)
                {
                    std::size_t sz = 0;
                    while (st[sz] != '\0') sz++;
                    return convert(st, st + sz);
                });
        return ret;
    }
};

template<>
struct char_converter<wchar_t, std::initializer_list<char *>>
{
    static std::vector<std::wstring>  conv(const std::initializer_list<char * > & in)
    {
        std::vector<std::wstring> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const char* st)
                {
                    std::size_t sz = 0;
                    while (st[sz] != '\0') sz++;
                    return convert(st, st + sz);
                });
        return ret;
    }
};

template<>
struct char_converter<char, std::vector<std::wstring>>
{
    static std::vector<std::string> conv(const std::vector<std::wstring> & in)
    {
        std::vector<std::string> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const std::wstring & st)
                {
                    return convert(st);
                });
        return ret;
    }
};

template<>
struct char_converter<char, std::initializer_list<std::wstring>>
{
    static std::vector<std::string> conv(const std::initializer_list<std::wstring> & in)
    {
        std::vector<std::string> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const std::wstring & st)
                {
                    return convert(st);
                });
        return ret;
    }
};

template<>
struct char_converter<char, std::vector<wchar_t* >>
{
    static std::vector<std::string> conv(const std::vector<wchar_t* > & in)
    {
        std::vector<std::string> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const wchar_t* st)
                {
                    std::size_t sz = 0;
                    while (st[sz] != L'\0') sz++;
                    return convert(st, st + sz);
                });
        return ret;
    }
};

template<>
struct char_converter<char, std::initializer_list<wchar_t * >>
{
    static std::vector<std::string> conv(const std::initializer_list<wchar_t *> & in)
    {
        std::vector<std::string> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const wchar_t* st)
                {
                    std::size_t sz = 0;
                    while (st[sz] != L'\0') sz++;
                    return convert(st, st + sz);
                });
        return ret;
    }
};


}}}
#endif /* BOOST_PROCESS_DETAIL_TRAITS_WCHAR_T_HPP_ */

/* wchar_t.hpp
74gOd0W760WzjEU56DvhhjhCUF3PkmaTL4139sFAvhuD8q1TJpDvnLq+fB21osOdfyPfrDKBfOe00vkG6RSis9mnE3Fzg4DOliCdJaZO9WCdgJ3YVPUNmP7xFpuxUMHGnmybTfwOwjNBtmXip0fxz5yrZiewRqj4A+E84VkVv5ewJ8iXz1B0k5LoT8JJsQMjXrE6stNib23KPmc7McmfZlS8lovOCuIOI+9F8LU9m/iX4DllS3ZG5fUFfJn+OUD4kfifCAE5lPyyEv1pVyn7MBeBv5GZdmKjf4WdWPSLpp1Y4t6AnVQzbYf1+R4t0zZhO7WsqbbresyUabuu9aZM57fclGm7rttMmbbrmmvKtH3ataZM12W8ljXR9mn9TZm2T6tsykzfQqZM19lhykzfQrsv9JH0ninTdX7NlOk6P2fKdJ2fRBZsU7fJlOk6r0UWbFN3/d4Lbeq+k/OpnKTFpi0WGfNzCRu3dnv+Phu3gG8i0TOv/0V+IoTPoiXIM+KRW66PYpGfR851DPIxovcg25yf2bZcXyj7uYEpIkfol23RuoVadtZG74yWqXOialOGtEmf/8T/UdZ+ZZ8T598u+0IJf0jap+PW8ob8bvLZISkOrsxcKMfODC4khxYi1s9DHHLNbt67/fASMs76meT5JsHmGY7Ky6Ftgh3q2vNidY14g8RPcvZF+27CdkJVh9vIIBQT9hL6ON2270PovHX9hhQaKu+ycLbEj3f25Py1lPAEoSK+0i4jjCXMcrQzXM4rbd9l0XnrZ2Dc65v3Zkxkck3JdbDXOETw5RFnySPOkkeCzoP7GX8Xin6SRT8pqEzGGX8xyJRuOYtuOdt+ZQyMGKvfXXhX4lMdl5L6asIuwvuERId/P1Wy5FfJtq76vl/0q1j0qwTpZ0jfW6/BlH8/6aNFXC3dIHnUsORRwzYPfX2m8xgkeSzmenG05FHHkkcdaz/oPOQmWnQbWHQbWHQt9/baF+FtEtfB0Yjr3r6E2YyCNdR8tzFR37t5pS4v82y8k+lvU46BKCl/YpCdeTy8X+ITfPWRZ6fmta2+75D54wsp/1H8C7U2QukMlLyWO0YajbGLu0r2c3Y8Ieh8/KVpfy3bXyWb8bvYpjP522JPLrQNcr4ND32+1fPtdTIPyeDW8y3jEhnHu5JFaz2OUyWL03O1Or6QJWmZebygK+3NiFfztZJV0uXI+Jf0VXR6PYZFXuPC+VLkdbTcMv6QNwjI1ZhCJvtwouQtGYvsvJ6b2V/2Mosdc2i7VXt75VD2rL/dLtne7jaUvXJoe9wlYsf86QNxT30z6JJGV6+fvrZf27VNfrtd7G+157a3iw1t92xvv/vvs4e2tzsPbSdtb48e2l7c3k76t9uR/1Y76d9q3/yN+JeTn9zL9Re/aNyjWf6+x/L3Zsvfayx/f0kID1PrNmotaxd8hnDeY8iPYSx20L1gOTgYboA5cCu8Bu6BQ+AJmAfPwHxlRzwOemAhjIRFMAFOgGXhRFgFToI14RR4MZwKm8LrYBt4PWwHp8PO8AbYDc6EveGNcCCcBXPhTXA4nANHw7lwPLwZXgtvgTfABXA1HA4fhSPgVngbfBneDg/BxfANuAS+De+E78Ol8CO4HH4GV8Az8C54Ft4Nz8HV0KH804XBe2AZuA4mwftgKlwPK8P7YXW4ETaAm2A3+CDsAR+CfeFmmAO3wPHwETgBPgb/AJ+Ay2EeXK/sjR+G2+DTcDvcC3fAN+Ez8DgcBT+Bo+FncAw8A3fDn+AeGK/826XAfbAufAG2gi/CDPgSHAwPwgJ4CBbC1+CN8AhcCd+ED8Gj8FF4DG6Hx+EL8H14CP4JHocfwp/gKRim7H3rwU8=
*/