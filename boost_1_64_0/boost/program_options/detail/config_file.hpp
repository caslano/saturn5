// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_CONFIG_FILE_VP_2003_01_02
#define BOOST_CONFIG_FILE_VP_2003_01_02

#include <iosfwd>
#include <string>
#include <set>

#include <boost/noncopyable.hpp>
#include <boost/program_options/config.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/eof_iterator.hpp>

#include <boost/detail/workaround.hpp>
#include <boost/program_options/detail/convert.hpp>

#if BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
#include <istream> // std::getline
#endif

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/shared_ptr.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4251) // class XYZ needs to have dll-interface to be used by clients of class XYZ
#endif



namespace boost { namespace program_options { namespace detail {

    /** Standalone parser for config files in ini-line format.
        The parser is a model of single-pass lvalue iterator, and
        default constructor creates past-the-end-iterator. The typical usage is:
        config_file_iterator i(is, ... set of options ...), e;
        for(; i !=e; ++i) {
            *i;
        }
        
        Syntax conventions:

        - config file can not contain positional options
        - '#' is comment character: it is ignored together with
          the rest of the line.
        - variable assignments are in the form
          name '=' value.
          spaces around '=' are trimmed.
        - Section names are given in brackets. 

         The actual option name is constructed by combining current section
         name and specified option name, with dot between. If section_name 
         already contains dot at the end, new dot is not inserted. For example:
         @verbatim
         [gui.accessibility]
         visual_bell=yes
         @endverbatim
         will result in option "gui.accessibility.visual_bell" with value
         "yes" been returned.

         TODO: maybe, we should just accept a pointer to options_description
         class.
     */    
    class BOOST_PROGRAM_OPTIONS_DECL common_config_file_iterator
        : public eof_iterator<common_config_file_iterator, option>
    {
    public:
        common_config_file_iterator() { found_eof(); }
        common_config_file_iterator(
            const std::set<std::string>& allowed_options,
            bool allow_unregistered = false);

        virtual ~common_config_file_iterator() {}

    public: // Method required by eof_iterator
        
        void get();
        
#if BOOST_WORKAROUND(_MSC_VER, <= 1900)
        void decrement() {}
        void advance(difference_type) {}
#endif

    protected: // Stubs for derived classes

        // Obtains next line from the config file
        // Note: really, this design is a bit ugly
        // The most clean thing would be to pass 'line_iterator' to
        // constructor of this class, but to avoid templating this class
        // we'd need polymorphic iterator, which does not exist yet.
        virtual bool getline(std::string&) { return false; }
        
    private:
        /** Adds another allowed option. If the 'name' ends with
            '*', then all options with the same prefix are
            allowed. For example, if 'name' is 'foo*', then 'foo1' and
            'foo_bar' are allowed. */
        void add_option(const char* name);

        // Returns true if 's' is a registered option name.
        bool allowed_option(const std::string& s) const; 

        // That's probably too much data for iterator, since
        // it will be copied, but let's not bother for now.
        std::set<std::string> allowed_options;
        // Invariant: no element is prefix of other element.
        std::set<std::string> allowed_prefixes;
        std::string m_prefix;
        bool m_allow_unregistered;
    };

    template<class charT>
    class basic_config_file_iterator : public common_config_file_iterator {
    public:
        basic_config_file_iterator()
        {
            found_eof();
        }

        /** Creates a config file parser for the specified stream.            
        */
        basic_config_file_iterator(std::basic_istream<charT>& is, 
                                   const std::set<std::string>& allowed_options,
                                   bool allow_unregistered = false); 

    private: // base overrides

        bool getline(std::string&);

    private: // internal data
        shared_ptr<std::basic_istream<charT> > is;
    };
    
    typedef basic_config_file_iterator<char> config_file_iterator;
    typedef basic_config_file_iterator<wchar_t> wconfig_file_iterator;


    struct null_deleter
    {
        void operator()(void const *) const {}
    };


    template<class charT>
    basic_config_file_iterator<charT>::
    basic_config_file_iterator(std::basic_istream<charT>& is, 
                               const std::set<std::string>& allowed_options,
                               bool allow_unregistered)
    : common_config_file_iterator(allowed_options, allow_unregistered)
    {
        this->is.reset(&is, null_deleter());                 
        get();
    }

    // Specializing this function for wchar_t causes problems on
    // borland and vc7, as well as on metrowerks. On the first two
    // I don't know a workaround, so make use of 'to_internal' to
    // avoid specialization.
    template<class charT>
    bool
    basic_config_file_iterator<charT>::getline(std::string& s)
    {
        std::basic_string<charT> in;
        if (std::getline(*is, in)) {
            s = to_internal(in);
            return true;
        } else {
            return false;
        }
    }

    // Specialization is needed to workaround getline bug on Comeau.
#if BOOST_WORKAROUND(__COMO_VERSION__, BOOST_TESTED_AT(4303)) || \
        (defined(__sgi) && BOOST_WORKAROUND(_COMPILER_VERSION, BOOST_TESTED_AT(741)))
    template<>
    bool
    basic_config_file_iterator<wchar_t>::getline(std::string& s);
#endif

    

}}}

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif

/* config_file.hpp
mf9P5HVybdZZvIy9kWA/bbScdQ/inD/XJ8j4vjD9F/LWc32CrHEJ0/8vxrp1MeNGWiODauFcpv9H7iRuvOBI9eL3iaRlLXoI/RzwZS0Oh2vAbGRqyjBF6xPot3QRckf6cWEiy9TSwm0smP+rh3HvRi9bwpwS83+FzEIvU8LcDq3j7R5BPywzPMyKqjJHiWwJX7NH2bORfYwvO2UalhEzBK/rom26/xL0meTLTmpZwXo5ym1DbqUfV+Jz3oDcIn9uNKHHhfvcpuzso+jDw5cNL7KENTHM/yGymzoouwxU6OLXQlDe+MdQd97Dk2p/thx5SY7HrG4Fr9mmbTj8OK73oP5gimsnVJWAS5aoaSmTjHrR7YhylyC3y83V0zCcSUXrhetb2PdvKa7v8XDtvZmtJlMT7XuAff+QO9fFJa4dkpkUoCXo1tn+30/g+jU3e1xxRUTK3D/b/wG5C/25jnVFPK40qGLfJ1rnez2Ja9h786XZILDvP7LzLWQTq2cr2liYtkTLX/Q5D3gK7a15JirhQTSRpvufidzq6TxXt0A7nEmmxM9tMv0XcndocXELVQU0CIKZ7Pu3DP0/uOqYWUQmQVQRrg+n5V2L7AGu8qqFuoTy0nc4/jSuRXSV98RISaRiDNnZVdL+yMz/D/Jv9ONLGL9Tbt0z2Hf4cSWM7UYg90Pkvu/mVlWcVApbIVbWRmCgdaxiGTL2laPtLPKsk4eXO/g8RCZUl4r380SZzyFzoNWL2agJHr9T5qjn0Fd5byY8YLH2A7T/WIzMTabwTPfLJFqnzPwfPY9rOS0vW65v9puR+7CXK7E9DXoB/Zp4mRKeLdN/InNub6aqN4id5z+cyvwvOszVLiZ2E9zG2+AULw3zFemY4GfM5v8xH9d1+OVDvA6N6X+X4/q9VG8uOhYWyqXvcRtyu324ZEE0cUghp8zrkT3d75nHxI/zaJmtl9A3g4tbDdhI8ejKUntRvvDxNNN/IzvrYo8dfVxpSUTmHJX6Mo7jXf01rl60v8Ojq6RwVyG3PuvDlWB/T7mRV3Btaqo3V4a+lPm/Qu5x0/24jdLKG34VxwA+z1eGrvZwWl7kXuFqz2D9X1pTXFkxsTQseXzN9j99DW1sWn8nHxL83VP+cuQvzFUPksb5rPyvox4qF1/SeH8oHfcif7mLX1p14hjIQKQ0LOPbSdnhN9DHSA62DNscyl6K7PNzsGX06ZQ9agXKWEwvhP7cUdEqc8/KRcheydjy/bnv+ybug8ozwRWcLN93zP81clf3cKX729vuLdxXjGOiEt3FDUIQghCEIAQhCEEIwn8z9IU4EMeY42oLleGFZHgJ48UdXOPLrSEmTvEZWwpIH4QgBCEIQQhCEIIQhCAEIQhBCEIQ5IYc8v9fnl8ScQ/m/xt/HT4X56gUZVxtcVm4Il1L7RyE8IIQhCAEIQhBCEIQghCEIAQhCEH4v4S+ECeiLN1weF29noyaupauq0hampnQVD1qaXXNMcsw4um6RLo5ZlpDk1FLb9bAZ8kkZdiwguHDRxxWWFhn1E8y67IjR9TFUhlF1dOpoXAG7PlBJg/tEQptGtoWZPHLTgvh0SuTjwUT34Q+DSz59ygxEik9rpmwD0j/vNe2h3XTkWqlpLiycnRxyfFgAn1SRc3YKrJGMFSZN2ZHmzHAWb+3kVOm6/s49gbXwPH53cA3+iW2HqFdAe8JUSXaHNXjtgMFx0n5zqGj8iySKq5Fm7W0ks6kbDc/mmrfozjPvnH5pXb6beDv0Xndv/76axX5u6TPQEj78GA7bUn1iRVh2wE55Cmctwp+swNce4lcy8bMAiVt4X6/9j3WwvXSy+x7VEJdTMyzLXKroBwDaV4=
*/