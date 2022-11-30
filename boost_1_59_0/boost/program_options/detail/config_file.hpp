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
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
*/