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
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
*/