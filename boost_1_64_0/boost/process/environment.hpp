// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_ENVIRONMENT_HPP_
#define BOOST_PROCESS_ENVIRONMENT_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/filesystem/path.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/environment.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/environment.hpp>
#endif

namespace boost { namespace process {

namespace detail {

template<typename Char, typename Environment>
struct const_entry
{
    using value_type    = Char ;
    using pointer       = const value_type * ;
    using string_type   = std::basic_string<value_type> ;
    using range         = boost::iterator_range<pointer> ;
    using environment_t = Environment ;

    std::vector<string_type> to_vector() const
    {
        if (_data == nullptr)
            return std::vector<string_type>();
        std::vector<string_type> data;
        auto str = string_type(_data);
        struct splitter
        {
            bool operator()(wchar_t w) const {return w == api::env_seperator<wchar_t>();}
            bool operator()(char c)    const {return c == api::env_seperator<char>   ();}
        } s;
        boost::split(data, _data, s);
        return data;
    }
    string_type to_string()              const
    {
        if (_data != nullptr)
            return string_type(_data);
        else
            return string_type();
    }
    string_type get_name() const {return string_type(_name.begin(), _name.end());}
    explicit const_entry(string_type&& name, pointer data, environment_t & env_) :
        _name(std::move(name)), _data(data), _env(&env_) {}

    explicit const_entry(string_type &&name, environment_t & env) :
        _name(std::move(name)), _data(nullptr), _env(&env) {}
    const_entry(const const_entry&) = default;
    const_entry& operator=(const const_entry&) = default;

    void reload()
    {
        auto p = _env->find(_name);
        if (p == _env->end())
            _data = nullptr;
        else
            _data = p->_data;
        this->_env->reload();

    }
    bool empty() const
    {
        return _data == nullptr;
    }
protected:
    string_type _name;
    pointer _data;
    environment_t * _env;
};

template<typename Char, typename Environment>
struct entry : const_entry<Char, Environment>
{
    using father = const_entry<Char, Environment>;
    using value_type    = typename father::value_type;
    using string_type   = typename father::string_type;
    using pointer       = typename father::pointer;
    using environment_t = typename father::environment_t;

    explicit entry(string_type&& name, pointer data, environment_t & env) :
        father(std::move(name), data, env) {}

    explicit entry(string_type &&name, environment_t & env_) :
        father(std::move(name), env_) {}

    entry(const entry&) = default;
    entry& operator=(const entry&) = default;

    void assign(const string_type &value)
    {
        this->_env->set(this->_name, value);
        this->reload();
    }
    void assign(const std::vector<string_type> &value)
    {
        string_type data;
        for (auto &v : value)
        {
            if (&v != &value.front())
                data += api::env_seperator<value_type>();
            data += v;
        }
        this->_env->set(this->_name, data);
        this->reload();

    }
    void assign(const std::initializer_list<string_type> &value)
    {
        string_type data;
        for (auto &v : value)
        {
            if (&v != &*value.begin())
                data += api::env_seperator<value_type>();
            data += v;
        }
        this->_env->set(this->_name, data);
        this->reload();

    }
    void append(const string_type &value)
    {
        if (this->_data == nullptr)
            this->_env->set(this->_name, value);
        else
        {
            string_type st = this->_data;
            this->_env->set(this->_name, st + api::env_seperator<value_type>() + value);
        }


        this->reload();

    }
    void clear()
    {
        this->_env->reset(this->_name);
        this->_env->reload();
        this->_data = nullptr;
    }
    entry &operator=(const string_type & value)
    {
        assign(value);
        return *this;
    }
    entry &operator=(const std::vector<string_type> & value)
    {
        assign(value);
        return *this;
    }
    entry &operator=(const std::initializer_list<string_type> & value)
    {
        assign(value);
        return *this;
    }
    entry &operator+=(const string_type & value)
    {
        append(value);
        return *this;
    }

};



template<typename Char, typename Environment>
struct make_entry
{

    make_entry(const make_entry&) = default;
    make_entry& operator=(const make_entry&) = default;

    Environment *env;
    make_entry(Environment & env) : env(&env) {};
    entry<Char, Environment> operator()(const Char* data) const
    {
        auto p = data;
        while ((*p != equal_sign<Char>()) && (*p != null_char<Char>()))
                p++;
        auto name = std::basic_string<Char>(data, p);
        p++; //go behind equal sign

        return entry<Char, Environment>(std::move(name), p, *env);
    }
};

template<typename Char, typename Environment>
struct make_const_entry
{

    make_const_entry(const make_const_entry&) = default;
    make_const_entry& operator=(const make_const_entry&) = default;

    Environment *env;
    make_const_entry(Environment & env) : env(&env) {};
    const_entry<Char, Environment> operator()(const Char* data) const
    {
        auto p = data;
        while ((*p != equal_sign<Char>()) && (*p != null_char<Char>()))
                p++;
        auto name = std::basic_string<Char>(data, p);
        p++; //go behind equal sign

        return const_entry<Char, Environment>(std::move(name), p, *env);
    }
};

}

#if !defined (BOOST_PROCESS_DOXYGEN)

template<typename Char, template <class> class Implementation = detail::api::basic_environment_impl>
class basic_environment_impl : public Implementation<Char>
{
    Char** _get_end() const
    {
        auto p = this->_env_impl;
        while (*p != nullptr)
            p++;

        return p;
    }
public:
    using string_type = std::basic_string<Char>;
    using implementation_type = Implementation<Char>;
    using base_type = basic_environment_impl<Char, Implementation>;
    using       entry_maker = detail::make_entry<Char, base_type>;
    using entry_type        = detail::entry     <Char, base_type>;
    using const_entry_type  = detail::const_entry     <Char, const base_type>;
    using const_entry_maker = detail::make_const_entry<Char, const base_type>;

    friend       entry_type;
    friend const_entry_type;

    using iterator        = boost::transform_iterator<      entry_maker, Char**,       entry_type,       entry_type>;
    using const_iterator  = boost::transform_iterator<const_entry_maker, Char**, const_entry_type, const_entry_type>;
    using size_type       = std::size_t;

    iterator        begin()       {return       iterator(this->_env_impl,       entry_maker(*this));}
    const_iterator  begin() const {return const_iterator(this->_env_impl, const_entry_maker(*this));}
    const_iterator cbegin() const {return const_iterator(this->_env_impl, const_entry_maker(*this));}

    iterator        end()       {return       iterator(_get_end(),       entry_maker(*this));}
    const_iterator  end() const {return const_iterator(_get_end(), const_entry_maker(*this));}
    const_iterator cend() const {return const_iterator(_get_end(), const_entry_maker(*this));}

    iterator        find( const string_type& key )
    {
        auto p = this->_env_impl;
        auto st1 = key + ::boost::process::detail::equal_sign<Char>();
        while (*p != nullptr)
        {
            if (std::equal(st1.begin(), st1.end(), *p))
                break;
            p++;
        }
        return iterator(p, entry_maker(*this));
    }
    const_iterator  find( const string_type& key ) const
    {
        auto p = this->_env_impl;
        auto st1 = key + ::boost::process::detail::equal_sign<Char>();
        while (*p != nullptr)
        {
            if (std::equal(st1.begin(), st1.end(), *p))
                break;
            p++;
        }
        return const_iterator(p, const_entry_maker(*this));
    }

    std::size_t count(const string_type & st) const
    {
        auto p = this->_env_impl;
        auto st1 = st + ::boost::process::detail::equal_sign<Char>();
        while (*p != nullptr)
        {
            if (std::equal(st1.begin(), st1.end(), *p))
                return 1u;
            p++;
        }
        return 0u;
    }
    void erase(const string_type & id)
    {
        implementation_type::reset(id);
        this->reload();
    }
    std::pair<iterator,bool> emplace(const string_type & id, const string_type & value)
    {
        auto f = find(id);
        if (f == end())
        {
            implementation_type::set(id, value);
            this->reload();
            return std::pair<iterator, bool>(find(id), true);
        }
        else
            return std::pair<iterator, bool>(f, false);
    }
    using implementation_type::implementation_type;
    using implementation_type::operator=;
    using native_handle_type = typename implementation_type::native_handle_type;
    using implementation_type::native_handle;
    //copy ctor if impl is copy-constructible
    bool empty()
    {
        return *this->_env_impl == nullptr;
    }
    std::size_t size() const
    {
        return (_get_end() - this->_env_impl);
    }
    void clear()
    {
        std::vector<string_type> names;
        names.resize(size());
        std::transform(cbegin(), cend(), names.begin(), [](const const_entry_type & cet){return cet.get_name();});

        for (auto & nm : names)
            implementation_type::reset(nm);

        this->reload();
    }

    entry_type  at( const string_type& key )
    {
        auto f = find(key);
        if (f== end())
            throw std::out_of_range(key + " not found");
        return *f;
    }
    const_entry_type at( const string_type& key ) const
    {
        auto f = find(key);
        if (f== end())
            throw std::out_of_range(key + " not found");
        return *f;
    }
    entry_type operator[](const string_type & key)
    {
        auto p = find(key);
        if (p != end())
            return *p;

        return entry_type(string_type(key), *this);
    }
};
#endif

#if defined(BOOST_PROCESS_DOXYGEN)
/**Template representation of environments. It takes a character type (`char` or `wchar_t`)
 * as template parameter to implement the environment
 */
template<typename Char>
class basic_environment
{

public:
    typedef std::basic_string<Char> string_type;
    typedef boost::transform_iterator<      entry_maker, Char**> iterator       ;
    typedef boost::transform_iterator<const_entry_maker, Char**> const_iterator ;
    typedef std::size_t                                             size_type      ;

    iterator       begin()        ; ///<Returns an iterator to the beginning
    const_iterator begin()  const ; ///<Returns an iterator to the beginning
    const_iterator cbegin() const ; ///<Returns an iterator to the beginning

    iterator       end()       ; ///<Returns an iterator to the end
    const_iterator end()  const; ///<Returns an iterator to the end
    const_iterator cend() const; ///<Returns an iterator to the end

    iterator        find( const string_type& key );            ///<Find a variable by its name
    const_iterator  find( const string_type& key ) const;   ///<Find a variable by its name

    std::size_t count(const string_type & st) const; ///<Number of variables
    void erase(const string_type & id); ///<Erase variable by id.
    ///Emplace an environment variable.
    std::pair<iterator,bool> emplace(const string_type & id, const string_type & value);

    ///Default constructor
    basic_environment();
    ///Copy constructor.
    basic_environment(const basic_environment & );
    ///Move constructor.
    basic_environment(basic_environment && );

    ///Copy assignment.
    basic_environment& operator=(const basic_environment & );
    ///Move assignment.
    basic_environment& operator=(basic_environment && );

    typedef typename detail::implementation_type::native_handle_type native_handle;

    ///Check if environment has entries.
    bool empty();
    ///Get the number of variables.
    std::size_t size() const;
    ///Clear the environment. @attention Use with care, passed environment cannot be empty.
    void clear();
    ///Get the entry with the key. Throws if it does not exist.
    entry_type  at( const string_type& key );
    ///Get the entry with the key. Throws if it does not exist.
    const_entry_type at( const string_type& key ) const;
    ///Get the entry with the given key. It creates the entry if it doesn't exist.
    entry_type operator[](const string_type & key);

    /**Proxy class used for read access to members by [] or .at()
     * @attention Holds a reference to the environment it was created from.
     */
    template<typename Char, typename Environment>
    struct const_entry_type
    {
        typedef Char value_type;
        typedef const value_type * pointer;
        typedef std::basic_string<value_type> string_type;
        typedef boost::iterator_range<pointer> range;
        typedef Environment environment_t;

        ///Split the entry by ";" or ":" and return it as a vector. Used by PATH.
        std::vector<string_type> to_vector() const
        ///Get the value as string.
        string_type to_string()              const
        ///Get the name of this entry.
        string_type get_name() const {return string_type(_name.begin(), _name.end());}
        ///Copy Constructor
        const_entry(const const_entry&) = default;
        ///Move Constructor
        const_entry& operator=(const const_entry&) = default;
        ///Check if the entry is empty.
        bool empty() const;
    };

    /**Proxy class used for read and write access to members by [] or .at()
     * @attention Holds a reference to the environment it was created from.
     */
    template<typename Char, typename Environment>
    struct entry_type
    {

        typedef Char value_type;
        typedef const value_type * pointer;
        typedef std::basic_string<value_type> string_type;
        typedef boost::iterator_range<pointer> range;
        typedef Environment environment_t;

        ///Split the entry by ";" or ":" and return it as a vector. Used by PATH.
        std::vector<string_type> to_vector() const
        ///Get the value as string.
        string_type to_string()              const
        ///Get the name of this entry.
        string_type get_name() const {return string_type(_name.begin(), _name.end());}
        ///Copy Constructor
        entry(const entry&) = default;
        ///Move Constructor
        entry& operator=(const entry&) = default;
        ///Check if the entry is empty.
        bool empty() const;

        ///Assign a string to the value
        void assign(const string_type &value);
        ///Assign a set of strings to the entry; they will be separated by ';' or ':'.
        void assign(const std::vector<string_type> &value);
        ///Append a string to the end of the entry, it will separated by ';' or ':'.
        void append(const string_type &value);
        ///Reset the value
        void clear();
        ///Assign a string to the entry.
        entry &operator=(const string_type & value);
        ///Assign a set of strings to the entry; they will be separated by ';' or ':'.
        entry &operator=(const std::vector<string_type> & value);
        ///Append a string to the end of the entry, it will separated by ';' or ':'.
        entry &operator+=(const string_type & value);
    };

};

/**Template representation of the environment of this process. It takes a template
 * as template parameter to implement the environment. All instances of this class
 * refer to the same environment, but might not get updated if another one makes changes.
 */
template<typename Char>
class basic_native_environment
{

public:
    typedef std::basic_string<Char> string_type;
    typedef boost::transform_iterator<      entry_maker, Char**> iterator       ;
    typedef boost::transform_iterator<const_entry_maker, Char**> const_iterator ;
    typedef std::size_t                                             size_type      ;

    iterator       begin()        ; ///<Returns an iterator to the beginning
    const_iterator begin()  const ; ///<Returns an iterator to the beginning
    const_iterator cbegin() const ; ///<Returns an iterator to the beginning

    iterator       end()       ; ///<Returns an iterator to the end
    const_iterator end()  const; ///<Returns an iterator to the end
    const_iterator cend() const; ///<Returns an iterator to the end

    iterator        find( const string_type& key );            ///<Find a variable by its name
    const_iterator  find( const string_type& key ) const;   ///<Find a variable by its name

    std::size_t count(const string_type & st) const; ///<Number of variables
    void erase(const string_type & id); ///<Erase variable by id.
    ///Emplace an environment variable.
    std::pair<iterator,bool> emplace(const string_type & id, const string_type & value);

    ///Default constructor
    basic_native_environment();
    ///Move constructor.
    basic_native_environment(basic_native_environment && );
    ///Move assignment.
    basic_native_environment& operator=(basic_native_environment && );

    typedef typename detail::implementation_type::native_handle_type native_handle;

    ///Check if environment has entries.
    bool empty();
    ///Get the number of variables.
    std::size_t size() const;
    ///Get the entry with the key. Throws if it does not exist.
    entry_type  at( const string_type& key );
    ///Get the entry with the key. Throws if it does not exist.
    const_entry_type at( const string_type& key ) const;
    ///Get the entry with the given key. It creates the entry if it doesn't exist.
    entry_type operator[](const string_type & key);

    /**Proxy class used for read access to members by [] or .at()
     * @attention Holds a reference to the environment it was created from.
     */
    template<typename Char, typename Environment>
    struct const_entry_type
    {
        typedef Char value_type;
        typedef const value_type * pointer;
        typedef std::basic_string<value_type> string_type;
        typedef boost::iterator_range<pointer> range;
        typedef Environment environment_t;

        ///Split the entry by ";" or ":" and return it as a vector. Used by PATH.
        std::vector<string_type> to_vector() const
        ///Get the value as string.
        string_type to_string()              const
        ///Get the name of this entry.
        string_type get_name() const {return string_type(_name.begin(), _name.end());}
        ///Copy Constructor
        const_entry(const const_entry&) = default;
        ///Move Constructor
        const_entry& operator=(const const_entry&) = default;
        ///Check if the entry is empty.
        bool empty() const;
    };

    /**Proxy class used for read and write access to members by [] or .at()
     * @attention Holds a reference to the environment it was created from.
     */
    template<typename Char, typename Environment>
    struct entry_type
    {

        typedef Char value_type;
        typedef const value_type * pointer;
        typedef std::basic_string<value_type> string_type;
        typedef boost::iterator_range<pointer> range;
        typedef Environment environment_t;

        ///Split the entry by ";" or ":" and return it as a vector. Used by PATH.
        std::vector<string_type> to_vector() const
        ///Get the value as string.
        string_type to_string()              const
        ///Get the name of this entry.
        string_type get_name() const {return string_type(_name.begin(), _name.end());}
        ///Copy Constructor
        entry(const entry&) = default;
        ///Move Constructor
        entry& operator=(const entry&) = default;
        ///Check if the entry is empty.
        bool empty() const;

        ///Assign a string to the value
        void assign(const string_type &value);
        ///Assign a set of strings to the entry; they will be separated by ';' or ':'.
        void assign(const std::vector<string_type> &value);
        ///Append a string to the end of the entry, it will separated by ';'  or ':'.
        void append(const string_type &value);
        ///Reset the value
        void clear();
        ///Assign a string to the entry.
        entry &operator=(const string_type & value);
        ///Assign a set of strings to the entry; they will be separated by ';' or ':'.
        entry &operator=(const std::vector<string_type> & value);
        ///Append a string to the end of the entry, it will separated by ';' or ':'.
        entry &operator+=(const string_type & value);
    };

};

#endif

///Definition of the environment for the current process.
template<typename Char>
class basic_native_environment : public basic_environment_impl<Char, detail::api::native_environment_impl>
{
public:
    using base_type = basic_environment_impl<Char, detail::api::native_environment_impl>;
    using base_type::base_type;
    using base_type::operator=;
};

///Type definition to hold a seperate environment.
template<typename Char>
class basic_environment : public basic_environment_impl<Char, detail::api::basic_environment_impl>
{
public:
    using base_type = basic_environment_impl<Char, detail::api::basic_environment_impl>;
    using base_type::base_type;
    using base_type::operator=;
};


#if !defined(BOOST_NO_ANSI_APIS)
///Definition of the environment for the current process.
typedef basic_native_environment<char>     native_environment;
#endif
///Definition of the environment for the current process.
typedef basic_native_environment<wchar_t> wnative_environment;

#if !defined(BOOST_NO_ANSI_APIS)
///Type definition to hold a seperate environment.
typedef basic_environment<char>     environment;
#endif
///Type definition to hold a seperate environment.
typedef basic_environment<wchar_t> wenvironment;

}

///Namespace containing information of the calling process.
namespace this_process
{

///Definition of the native handle type.
typedef ::boost::process::detail::api::native_handle_t native_handle_type;

#if !defined(BOOST_NO_ANSI_APIS)
///Definition of the environment for this process.
using ::boost::process::native_environment;
#endif
///Definition of the environment for this process.
using ::boost::process::wnative_environment;

///Get the process id of the current process.
inline int get_id()                     { return ::boost::process::detail::api::get_id();}
///Get the native handle of the current process.
inline native_handle_type native_handle()  { return ::boost::process::detail::api::native_handle();}
#if !defined(BOOST_NO_ANSI_APIS)
///Get the enviroment of the current process.
inline native_environment   environment() { return ::boost::process:: native_environment(); }
#endif
///Get the enviroment of the current process.
inline wnative_environment wenvironment() { return ::boost::process::wnative_environment(); }
///Get the path environment variable of the current process runs.
inline std::vector<boost::filesystem::path> path()
{
#if defined(BOOST_WINDOWS_API)
    const ::boost::process::wnative_environment ne{};
    typedef typename ::boost::process::wnative_environment::const_entry_type value_type;
    const auto id = L"PATH";
#else
    const ::boost::process::native_environment ne{};
    typedef typename ::boost::process::native_environment::const_entry_type value_type;
    const auto id = "PATH";
#endif

    auto itr = std::find_if(ne.cbegin(), ne.cend(),
            [&](const value_type & e)
             {return id == ::boost::to_upper_copy(e.get_name(), ::boost::process::detail::process_locale());});

    if (itr == ne.cend())
        return {};

    auto vec = itr->to_vector();

    std::vector<boost::filesystem::path> val;
    val.resize(vec.size());

    std::copy(vec.begin(), vec.end(), val.begin());

    return val;
}
}
}
#endif /* INCLUDE_BOOST_PROCESS_DETAIL_ENVIRONMENT_HPP_ */

/* environment.hpp
0eiPMzEQ52AQrsJgfB1D8W8YhnsxHA9hUzyLEaiMz6UxEKMwFFtgc4zHdtgSO2Br/BNegf2wPQ7BDpiFnXEMdsFC7IZl2B3nYg9cgT3xCeyL6/Fq3Iv98R94LZ7ARPwFB6Jycj2DgTgY4zEVU7EIb8cJuASLcSXOwh04G3fhbbgf5+IxvAOP4114Fueh00X/H0NwAUbhQozDezAe78WWuAjb6/xd8H7sikvxWnwQR+FDWIorsQZfxDtwAy7AjbgEN+FKfAnX4mu4GbfiNtyGb+N23I1v4iF8C4/g3/Bz3I1B3pxHsQnuxfZ4ALvhEUzEo5iHx7ASP8db8DguxS9xGZ7E9fg1voWn8Sh+i5fwBwz2Yf/GODyH7fEn7Ii/Yl/8DdOwsT/HNYbgOAzDSozAadgCH8ZYXI3x+Cy2xvXYDjdjB3wLO+FR7IxnsQtewAQM92X/w0jsgd3wShyIvTAPr8LbsD/Ow2vxYUzEZ3EAvoCDcBsm4z4cjIdwCB7B6/BbHIYcqyoPfXEV690MH8f2uBr74Rocik/hcFyGN+LDWI7L8SZ8BFfgCnwcH8U16EX5G9GJO9GF76MPHsCW+BG2woM4Ck/haDTup41HbyzApliILbAI2+JE7IXFmI4lmIWTcAJOxpuwTH/eHuKjf9uif+NzFrcpuf6Rf1cFsD9gCg7E6zADh+F4TMUqTMdbMAPvxutxOWbiGszCl/AG3Iej8QzeiD/hOPRiIXKxKRZgP5yIqViMOTgZ87AUS7Eca7ACZ2AVzsdqvB+n4wq8GTfiDNyNM/EA3o6f4Rx0etGuYBjOw2icj33xXrwOl+BEvA9vwvvxdlyKj+BDuBKX4av4CP4dV+D7uBYP4rMY4WS/Nz6Xw96YgX1wDF6N03Eg3ol3G+uDC/BxXIhP4ou4CzfgIdyIX+BLeBpfxov4Cnq76EegP76GLfF17IpvYE/cgX3wLRyFO7EG9+Ec/ADvxQ/xYfwI1+JBfAEP4Xb8BPfhYfwcT+JZfBsV7c87GIy7sAkew0j8HKPxCMbhZ9gST2BXNMrtjV9jNp7BXPwW78SfcQn+gg/jeVyuhx/Tw8/ir7gBf8PX8AJ+jL/jSbyEP+l8DuNYYDsEogNbohd2QCf2RB/MQF/MRj8sRn8swQCcgo1wGQbiCgzCJzAYX8QQfBPD8D0Mx48wAj/DSLyA0eik3YrBVtgCu2Is9sU4HILxmIkt8UZshfnYGkuxDVbjFTgD2+Ic7IhLsBM+iB1wrU7foNNfxkTcikn4Bl6Du3EwvodD8EPsjZ9hCv6AqfgLDkcn7VsaNsV0jMbrMQ6zsCVmYxfMwWtxBA7CUTgcR+MoHIPFOBbLMA9nYD7eiePxASzA5TgB1+NE3IrFuAtLcD9Owo+wDD/DcvwRK1HRjk7BYKzGr3AqnsXpeAlnId+ZUX/GCFyA8XgfXon341X4AObgMizG5TgJH8FSPV0lGuXdpctbgKvwEXwSn8WncD0+jdt0+l6d/j6+gJ/iRvwGN+HvuBnZl9XLGMj6neND/u1D2P8GEx/whGEikRhL1BCLiaeJ7cQB4hRxkQinUe1MDCLyiBpiIbGW2EocJi4SIR/yJnsigygl5hFriaFV9EGZ51b+PkgcpdN8DkeSNs9IJ84Q8SxbKrGKCPyIeRJDiZFEMTGbWEo8TWwnDhLnicB/sC5EIpFNVBLziFXEJmIPcZQ4R4QcpFxiKJFHTCcWE+uJPcQpwkXnPJ6oZLl7YipRSMwmlhLriV3EKcLvY55QTvQhMohCYi6xjthOHCBOEReJ8E/IR2QQhcRsYimxjthOHCDOEiGHWUZiEDGWqCHmESuI9cQu4ihxjgj8lPkTiUQeUUM=
*/