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
            [&](const string_type & st)
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
        [&](const string_type & st)
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
        [&](const string_type & st)
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