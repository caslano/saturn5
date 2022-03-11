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