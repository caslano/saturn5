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
L2EO89v3PNqxnhm4HvdMce/rvyVquc9OL7cMfVgOhLMFvdGid6rf1pFuipcaum8cOhHrUMz1f/cCeW/hm2Bttoo993tC6yQ+q5bnrGivVT9a9igkjD9IPPcmBMIa3TJin0ncj3XvniNxRFmt9Nq6V8JuERdvvRV1IKrC+jS6hTcxLlb1uRJFP0bK4W7CrZR44/174mcgk3Esv2FDyvOrZllaDp+jd5foPUf6REfX0+jecbh/Le5LEurhfiRibcv34nY5d/S53vD992STPpP2QaJ3hv9a2kEFY+5LfV/HXprglzaQaur5tNj21jOegYx3z/J+FGXXS0n+9Lm6bxVpWkqaFhIe//xDot7y3Rh3rWMtkNy1TLyNpE0+HhtjxXJfOuz7NGqz5Yt90KyleFfK9OXYJlZMdOfomd62hL+J8IPpORrf3vrY09Hb3BpO7mbHzbAOxPvDytK5/mUj/u6RdD2dcF30VOuxmHbWsfbP3BYo1wukXP3Jpl2QT8f4/duvnO/j8gsK8opL5qj/Pfj/mcT1TYLL/psmf7slfyOjzyLEiRZlit8a/C4Tv18mdIk64HNZzyNxrERvK2kkFL+tw3VUml+Cktnz9ZCU8UniZxd+PBL2Qv+x9uRcjY7tNi2/QPJs30NSL5T9K80akpiFAfsDtLGZXtl7FP8bJY69Cc69E0O1IXuPovOI6Dzm0CHtcnnrmit0nHmvyC8Ne8/RU/LVAd1GZn1MicjOiErhKWmwdVD2yVxMONdKXO/JNTRG6lKfw7UffG++7CHJ+5FEq7P2IQeljb0TX8/a7vm9Z4Dl914TtTmmyPpV7ALruXivtQ+TFtYPdo9tbnliusaUWg/HVEg+q4j7TxL3HY52QD8mjc3Oy91Sj6NjTrV8MaF3NlE1AdmvyOEiCetNwvqD6N3rD7v2ZLs3e6/I3hJfQpzf2u854vk6OhReTbXUSVS09WRUILzLCe8M0R3kaAuEx9jaWc5DROel2DWsoAn1ZW2175N9SAlnnei8kWBf53KlaPnwk3p5IfY934OWN3qzdWnscHULXePtSec3vhZRpdavo+bUOku2g4bzRaXkIT6alQNPeM6wYr1rojbFlFh3x37g2RMfTE8x6fmjpGdzQqr9vrymvKxCRrrONYTXStyp0X6ewM/jLdcIz+O+8HvFOqbCL5DyuoZwMyTcbH/kfquytzDuE8W9nd99T1S7jtZL2P0tL+003YqS/mkW/i8T/4cTukW96/tF3LXHPJt2LbqRe7vuRLZL/G9ztrXK8jzpEMx967C0q+a61zFPf/OlbkiJjzn8Y7jLJ0l4uwnvJWlvt/ntetWwcN+L+/PifqejPVbNK3P0F03gJ9I/+D2hd4r1xP4g/cV06S8WEU6WpLunhPNmiqQ7n5h4SWq/g325SvrEuPZWk5jdMW29oXv9nZKfJzy7eGYc6Uk0z80x0lbmJjzHPS3W911U/bjHvVLvP3C9FpCWlyUttyaE3sNYjvcwO3B39ml6txa/7+D2gPh9MsF+FqZPc/Sdd8l1cJA2FnlfjYuNWBNo2kRQ58/oPOrdHVPoXJNn3g1fMC+49vdM2nGq5rFQZF18fqSl1lqvY3xt9ldeKjofUw/PWm09MaxjbGeVeBO53nA36RtI3HN899CbVkWdZ70clekJlBlpcbyHqA4kWtJcE5bmByXN+kwh9VpVUm7a4lNSd4nivjtF+5+SAh1HOMP5jYSTrGWkY8oeluMZ4zwJK0vv9U6/2VGaBs3/XAZy9juNrKA/TzPLb/aVPjQfGSWSSMndbVXoc6551jTl3lX8zvB0t5I8IjN+b7Lwq+8s7H6VN/Uy/ltB+gYtCuj9xLPd+imy0Pc=
*/