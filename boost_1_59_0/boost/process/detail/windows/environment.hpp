// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_ENV_STORAGE_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_ENV_STORAGE_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include <boost/winapi/error_codes.hpp>
#include <boost/winapi/environment.hpp>
#include <boost/winapi/get_current_process.hpp>
#include <boost/winapi/get_current_process_id.hpp>
#include <boost/process/detail/config.hpp>
#include <algorithm>
#include <boost/process/locale.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<typename Char>
class native_environment_impl
{
    static void _deleter(Char* p) {boost::winapi::free_environment_strings(p);};
    std::unique_ptr<Char[], void(*)(Char*)> _buf{boost::winapi::get_environment_strings<Char>(), &native_environment_impl::_deleter};
    static inline std::vector<Char*> _load_var(Char* p);
    std::vector<Char*> _env_arr{_load_var(_buf.get())};
public:
    using char_type = Char;
    using pointer_type = const char_type*;
    using string_type = std::basic_string<char_type>;
    using native_handle_type = pointer_type;
    void reload()
    {
        _buf.reset(boost::winapi::get_environment_strings<Char>());
        _env_arr = _load_var(_buf.get());
        _env_impl = &*_env_arr.begin();
    }

    string_type get(const pointer_type id);
    void        set(const pointer_type id, const pointer_type value);
    void      reset(const pointer_type id);

    string_type get(const string_type & id) {return get(id.c_str());}
    void        set(const string_type & id, const string_type & value) {set(id.c_str(), value.c_str()); }
    void      reset(const string_type & id) {reset(id.c_str());}

    native_environment_impl() = default;
    native_environment_impl(const native_environment_impl& ) = delete;
    native_environment_impl(native_environment_impl && ) = default;
    native_environment_impl & operator=(const native_environment_impl& ) = delete;
    native_environment_impl & operator=(native_environment_impl && ) = default;
    Char ** _env_impl = &*_env_arr.begin();

    native_handle_type native_handle() const {return _buf.get();}
};

template<typename Char>
inline auto native_environment_impl<Char>::get(const pointer_type id) -> string_type
{
    Char buf[4096];
    auto size = boost::winapi::get_environment_variable(id, buf, sizeof(buf));
    if (size == 0) //failed
    {
        auto err =  ::boost::winapi::GetLastError();
        if (err == ::boost::winapi::ERROR_ENVVAR_NOT_FOUND_)//well, then we consider that an empty value
            return "";
        else
            throw process_error(std::error_code(err, std::system_category()),
                               "GetEnvironmentVariable() failed");
    }

    if (size == sizeof(buf)) //the return size gives the size without the null, so I know this went wrong
    {
        /*limit defined here https://msdn.microsoft.com/en-us/library/windows/desktop/ms683188(v=vs.85).aspx
         * but I used 32768 so it is a multiple of 4096.
         */
        constexpr static std::size_t max_size = 32768;
        //Handle variables longer then buf.
        std::size_t buf_size = sizeof(buf);
        while (buf_size <= max_size)
        {
            std::vector<Char> buf(buf_size);
            auto size = boost::winapi::get_environment_variable(id, buf.data(), buf.size());

            if (size == buf_size) //buffer to small
                buf_size *= 2;
            else if (size == 0)
                ::boost::process::detail::throw_last_error("GetEnvironmentVariable() failed");
            else
                return std::basic_string<Char>(
                        buf.data(), buf.data()+ size + 1);

        }

    }
    return std::basic_string<Char>(buf, buf+size+1);
}

template<typename Char>
inline void native_environment_impl<Char>::set(const pointer_type id, const pointer_type value)
{
    boost::winapi::set_environment_variable(id, value);
}

template<typename Char>
inline void  native_environment_impl<Char>::reset(const pointer_type id)
{
    boost::winapi::set_environment_variable(id, nullptr);
}

template<typename Char>
std::vector<Char*> native_environment_impl<Char>::_load_var(Char* p)
{
    std::vector<Char*> ret;
    if (*p != null_char<Char>())
    {
        ret.push_back(p);
        while ((*p != null_char<Char>()) || (*(p+1) !=  null_char<Char>()))
        {
            if (*p==null_char<Char>())
            {
                p++;
                ret.push_back(p);
            }
            else
                p++;
        }
    }
    p++;
    ret.push_back(nullptr);

    return ret;
}


template<typename Char>
struct basic_environment_impl
{
    std::vector<Char> _data = {null_char<Char>()};
    static std::vector<Char*> _load_var(Char* p);
    std::vector<Char*> _env_arr{_load_var(_data.data())};
public:
    using char_type = Char;
    using pointer_type = const char_type*;
    using string_type = std::basic_string<char_type>;
    using native_handle_type = pointer_type;

    std::size_t size() const { return _data.size();}

    void reload()
    {
        _env_arr = _load_var(_data.data());
        _env_impl = _env_arr.data();
    }

    string_type get(const pointer_type id) {return get(string_type(id));}
    void        set(const pointer_type id, const pointer_type value) {set(string_type(id), value);}
    void      reset(const pointer_type id)  {reset(string_type(id));}

    string_type get(const string_type & id);
    void        set(const string_type & id, const string_type & value);
    void      reset(const string_type & id);

    inline basic_environment_impl(const native_environment_impl<Char> & nei);
    basic_environment_impl() = default;
    basic_environment_impl(const basic_environment_impl& rhs)
        : _data(rhs._data)
    {
    }
    basic_environment_impl(basic_environment_impl && rhs)
        :    _data(std::move(rhs._data)),
            _env_arr(std::move(rhs._env_arr)),
            _env_impl(_env_arr.data())
    {
    }
    basic_environment_impl &operator=(basic_environment_impl && rhs)
    {
        _data = std::move(rhs._data);
        //reload();
        _env_arr  = std::move(rhs._env_arr);
        _env_impl = _env_arr.data();

        return *this;
    }
    basic_environment_impl & operator=(const basic_environment_impl& rhs)
    {
        _data = rhs._data;
        reload();
        return *this;
    }

    template<typename CharR>
    explicit inline  basic_environment_impl(
                const basic_environment_impl<CharR>& rhs,
                const ::boost::process::codecvt_type & cv = ::boost::process::codecvt())
        : _data(::boost::process::detail::convert(rhs._data, cv))
    {
    }

    template<typename CharR>
    basic_environment_impl & operator=(const basic_environment_impl<CharR>& rhs)
    {
        _data = ::boost::process::detail::convert(rhs._data);
        _env_arr = _load_var(&*_data.begin());
        _env_impl = &*_env_arr.begin();
        return *this;
    }

    Char ** _env_impl = &*_env_arr.begin();

    native_handle_type native_handle() const {return &*_data.begin();}
};


template<typename Char>
basic_environment_impl<Char>::basic_environment_impl(const native_environment_impl<Char> & nei)
{
    auto beg = nei.native_handle();
    auto p   = beg;
    while ((*p != null_char<Char>()) || (*(p+1) !=  null_char<Char>()))
        p++;
    p++; //pointing to the second nullchar
    p++; //to get the pointer behing the second nullchar, so it's end.

    this->_data.assign(beg, p);
    this->reload();
}


template<typename Char>
inline auto basic_environment_impl<Char>::get(const string_type &id) -> string_type
{

    if (std::equal(id.begin(), id.end(), _data.begin()) && (_data[id.size()] == equal_sign<Char>()))
        return string_type(_data.data()); //null-char is handled by the string.

    std::vector<Char> seq = {'\0'}; //using a vector, because strings might cause problems with nullchars
    seq.insert(seq.end(), id.begin(), id.end());
    seq.push_back('=');

    auto itr = std::search(_data.begin(), _data.end(), seq.begin(), seq.end());

    if (itr == _data.end()) //not found
        return "";

    itr += seq.size(); //advance to the value behind the '='; the std::string will take care of finding the null-char.

    return string_type(&*itr);
}

template<typename Char>
inline void basic_environment_impl<Char>::set(const string_type &id, const string_type &value)
{
    reset(id);

    std::vector<Char> insertion;

    insertion.insert(insertion.end(), id.begin(),    id.end());
    insertion.push_back('=');
    insertion.insert(insertion.end(), value.begin(), value.end());
    insertion.push_back('\0');

    _data.insert(_data.end() -1, insertion.begin(), insertion.end());

    reload();
}

template<typename Char>
inline void  basic_environment_impl<Char>::reset(const string_type &id)
{
    //ok, we need to check the size of data first
    if (id.size() >= _data.size()) //ok, so it's impossible id is in there.
        return;

    //check if it's the first one, spares us the search.
    if (std::equal(id.begin(), id.end(), _data.begin()) && (_data[id.size()] == equal_sign<Char>()))
    {
        auto beg = _data.begin();
        auto end = beg;

        while (*end != '\0')
           end++;

        end++; //to point behind the last null-char

        _data.erase(beg, end); //and remove the thingy

    }

    std::vector<Char> seq = {'\0'}; //using a vector, because strings might cause problems with nullchars
    seq.insert(seq.end(), id.begin(), id.end());
    seq.push_back('=');

    auto itr = std::search(_data.begin(), _data.end(), seq.begin(), seq.end());

    if (itr == _data.end())
        return;//nothing to return if it's empty anyway...

    auto end = itr;

    while (*++end != '\0');


    _data.erase(itr, end);//and remove it
    reload();


}

template<typename Char>
std::vector<Char*> basic_environment_impl<Char>::_load_var(Char* p)
{
    std::vector<Char*> ret;
    if (*p != null_char<Char>())
    {
        ret.push_back(p);
        while ((*p != null_char<Char>()) || (*(p+1) !=  null_char<Char>()))
        {
            if (*p==null_char<Char>())
            {
                p++;
                ret.push_back(p);
            }
            else
                p++;
        }
    }
    p++;
    ret.push_back(nullptr);
    return ret;
}


template<typename T> constexpr T env_seperator();
template<> constexpr  char   env_seperator() {return  ';'; }
template<> constexpr wchar_t env_seperator() {return L';'; }

inline int   get_id()         {return boost::winapi::GetCurrentProcessId();}
inline void* native_handle()  {return boost::winapi::GetCurrentProcess(); }

typedef void* native_handle_t;

}

}
}
}




#endif /* BOOST_PROCESS_DETAIL_WINDOWS_ENV_STORAGE_HPP_ */

/* environment.hpp
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
*/