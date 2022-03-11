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