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
    static constexpr auto id = L"PATH";
#else
    const ::boost::process::native_environment ne{};
    typedef typename ::boost::process::native_environment::const_entry_type value_type;
    static constexpr auto id = "PATH";
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
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
*/