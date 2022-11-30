// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_ENVIRONMENT_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_ENVIRONMENT_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include <boost/process/detail/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <boost/process/locale.hpp>


namespace boost { namespace process { namespace detail { namespace posix {

template<typename Char>
class native_environment_impl
{
    static std::vector<std::basic_string<Char>>  _load()
    {
        std::vector<std::basic_string<Char>> val;
        auto p = environ;
        while (*p != nullptr)
        {
            std::string str = *p;
            val.push_back(::boost::process::detail::convert(str));
            p++;
        }
        return val;
    }
    static std::vector<Char*> _load_var(std::vector<std::basic_string<Char>> & vec)
    {
        std::vector<Char*> val;
        val.resize(vec.size() + 1);
        std::transform(vec.begin(), vec.end(), val.begin(),
                [](std::basic_string<Char> & str)
                {
                    return &str.front();
                });
        val.back() = nullptr;
        return val;
    }
    std::vector<std::basic_string<Char>> _buffer = _load();
    std::vector<Char*> _impl = _load_var(_buffer);
public:
    using char_type = Char;
    using pointer_type = const char_type*;
    using string_type = std::basic_string<char_type>;
    using native_handle_type = char_type **;

    void reload()
    {
        _buffer = _load();
        _impl = _load_var(_buffer);
        _env_impl = _impl.data();
    }

    string_type get(const pointer_type id) { return get(string_type(id)); }
    void        set(const pointer_type id, const pointer_type value)
    {
        set(string_type(id), string_type(value));
    }
    void      reset(const pointer_type id) { reset(string_type(id)); }

    string_type get(const string_type & id)
    {
        std::string id_c = ::boost::process::detail::convert(id);
        std::string g = ::getenv(id_c.c_str());
        return ::boost::process::detail::convert(g.c_str());
    }
    void        set(const string_type & id, const string_type & value)
    {
        std::string id_c    = ::boost::process::detail::convert(id.c_str());
        std::string value_c = ::boost::process::detail::convert(value.c_str());
        auto res = ::setenv(id_c.c_str(), value_c.c_str(), true);
        if (res != 0)
            boost::process::detail::throw_last_error();
    }
    void      reset(const string_type & id)
    {
        std::string id_c = ::boost::process::detail::convert(id.c_str());
        auto res = ::unsetenv(id_c.c_str());
        if (res != 0)
            ::boost::process::detail::throw_last_error();
    }

    native_environment_impl() = default;
    native_environment_impl(const native_environment_impl& ) = delete;
    native_environment_impl(native_environment_impl && ) = default;
    native_environment_impl & operator=(const native_environment_impl& ) = delete;
    native_environment_impl & operator=(native_environment_impl && ) = default;
    native_handle_type _env_impl = _impl.data();

    native_handle_type native_handle() const {return _env_impl;}
};

template<>
class native_environment_impl<char>
{
public:
    using char_type = char;
    using pointer_type = const char_type*;
    using string_type = std::basic_string<char_type>;
    using native_handle_type = char_type **;

    void reload() {this->_env_impl = ::environ;}

    string_type get(const pointer_type id) { return getenv(id); }
    void        set(const pointer_type id, const pointer_type value)
    {
        auto res = ::setenv(id, value, 1);
        if (res != 0)
            boost::process::detail::throw_last_error();
        reload();
    }
    void      reset(const pointer_type id)
    {
        auto res = ::unsetenv(id);
        if (res != 0)
            boost::process::detail::throw_last_error();
        reload();
    }

    string_type get(const string_type & id) {return get(id.c_str());}
    void        set(const string_type & id, const string_type & value) {set(id.c_str(), value.c_str()); }
    void      reset(const string_type & id) {reset(id.c_str());}

    native_environment_impl() = default;
    native_environment_impl(const native_environment_impl& ) = delete;
    native_environment_impl(native_environment_impl && ) = default;
    native_environment_impl & operator=(const native_environment_impl& ) = delete;
    native_environment_impl & operator=(native_environment_impl && ) = default;
    native_handle_type _env_impl = environ;

    native_handle_type native_handle() const {return ::environ;}
};



template<typename Char>
struct basic_environment_impl
{
    std::vector<std::basic_string<Char>> _data {};
    static std::vector<Char*> _load_var(std::vector<std::basic_string<Char>> & data);
    std::vector<Char*> _env_arr{_load_var(_data)};
public:
    using char_type = Char;
    using pointer_type = const char_type*;
    using string_type = std::basic_string<char_type>;
    using native_handle_type = Char**;
    void reload()
    {
        _env_arr = _load_var(_data);
        _env_impl = _env_arr.data();
    }

    string_type get(const pointer_type id) {return get(string_type(id));}
    void        set(const pointer_type id, const pointer_type value) {set(string_type(id), value);}
    void      reset(const pointer_type id)  {reset(string_type(id));}

    string_type get(const string_type & id);
    void        set(const string_type & id, const string_type & value);
    void      reset(const string_type & id);

    basic_environment_impl(const native_environment_impl<Char> & nei);
    basic_environment_impl() = default;
    basic_environment_impl(const basic_environment_impl& rhs)
        : _data(rhs._data)
    {

    }
    basic_environment_impl(basic_environment_impl && ) = default;
    basic_environment_impl & operator=(const basic_environment_impl& rhs)
    {
        _data = rhs._data;
        _env_arr = _load_var(_data);
        _env_impl = &*_env_arr.begin();
        return *this;
    }
    basic_environment_impl & operator=(basic_environment_impl && ) = default;

    template<typename CharR>
    explicit inline  basic_environment_impl(
                const basic_environment_impl<CharR>& rhs,
                const ::boost::process::codecvt_type & cv = ::boost::process::codecvt())
        : _data(rhs._data.size())
    {
        std::transform(rhs._data.begin(), rhs._data.end(), _data.begin(),
                [&](const std::basic_string<CharR> & st)
                {
                    return ::boost::process::detail::convert(st, cv);
                }

            );
        reload();
    }

    template<typename CharR>
    basic_environment_impl & operator=(const basic_environment_impl<CharR>& rhs)
    {
        _data = ::boost::process::detail::convert(rhs._data);
        _env_arr = _load_var(&*_data.begin());
        _env_impl = &*_env_arr.begin();
        return *this;
    }

    Char ** _env_impl = &*_env_arr.data();

    native_handle_type native_handle() const {return &_data.front();}
};


template<typename Char>
basic_environment_impl<Char>::basic_environment_impl(const native_environment_impl<Char> & nei)
{
    auto beg = nei.native_handle();

    auto end = beg;
    while (*end != nullptr)
        end++;
    this->_data.assign(beg, end);
    reload();
}


template<typename Char>
inline auto basic_environment_impl<Char>::get(const string_type &id) -> string_type
{
    auto itr = std::find_if(_data.begin(), _data.end(), 
            [&](const string_type & st) -> bool
            {
                if (st.size() <= id.size())
                    return false;
                return std::equal(id.begin(), id.end(), st.begin()) && (st[id.size()] == equal_sign<Char>());
            }
        );

    if (itr == _data.end())
    {
        return "";
    }
    else return
        itr->data() + id.size(); //id=Thingy -> +2 points to T
}

template<typename Char>
inline void basic_environment_impl<Char>::set(const string_type &id, const string_type &value)
{
    auto itr = std::find_if(_data.begin(), _data.end(), 
        [&](const string_type & st) -> bool
        {
            if (st.size() <= id.size())
                return false;
            return std::equal(id.begin(), id.end(), st.begin()) && (st[id.size()] == equal_sign<Char>());
        }
    );

    if (itr != _data.end())
        *itr = id + equal_sign<Char>() + value;
    else 
        _data.push_back(id + equal_sign<Char>() + value);

    reload();
}

template<typename Char>
inline void  basic_environment_impl<Char>::reset(const string_type &id)
{
    auto itr = std::find_if(_data.begin(), _data.end(), 
        [&](const string_type & st) -> bool
        {
            if (st.size() <= id.size())
                return false;
            return std::equal(id.begin(), id.end(), st.begin()) && (st[id.size()] == equal_sign<Char>());
        }
    );
    if (itr != _data.end())
    {
        _data.erase(itr);//and remove it    
    }
    
    reload();


}

template<typename Char>
std::vector<Char*> basic_environment_impl<Char>::_load_var(std::vector<std::basic_string<Char>> & data)
{
    std::vector<Char*> ret;
    ret.reserve(data.size() +1);

    for (auto & val : data)
    {
        if (val.empty())
            val.push_back(0);
        ret.push_back(&val.front());
    }

    ret.push_back(nullptr);
    return ret;
}

template<typename T> constexpr T env_seperator();
template<> constexpr   char   env_seperator() {return  ':'; }
template<> constexpr  wchar_t env_seperator() {return L':'; }


typedef int native_handle_t;

inline int  get_id()        {return getpid(); }
inline int native_handle()  {return getpid(); }

}

}
}
}




#endif /* BOOST_PROCESS_DETAIL_WINDOWS_ENV_STORAGE_HPP_ */

/* environment.hpp
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
*/