// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_ERRORS_VP_2003_01_02
#define BOOST_ERRORS_VP_2003_01_02

#include <boost/program_options/config.hpp>

#include <string>
#include <stdexcept>
#include <vector>
#include <map>


#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4275) // non dll-interface class 'std::logic_error' used as base for dll-interface class 'boost::program_options::error'
#   pragma warning (disable:4251) // class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class 'boost::program_options::ambiguous_option'
#endif

namespace boost { namespace program_options {

    inline std::string strip_prefixes(const std::string& text)
    {
        // "--foo-bar" -> "foo-bar"
        std::string::size_type i = text.find_first_not_of("-/");
        if (i == std::string::npos) {
            return text;
        } else {
            return text.substr(i);
        }
    }

    /** Base class for all errors in the library. */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE error : public std::logic_error {
    public:
        error(const std::string& xwhat) : std::logic_error(xwhat) {}
    };


    /** Class thrown when there are too many positional options. 
        This is a programming error.
    */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE too_many_positional_options_error : public error {
    public:
        too_many_positional_options_error() 
         : error("too many positional options have been specified on the command line") 
        {}
    };

    /** Class thrown when there are programming error related to style */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE invalid_command_line_style : public error {
    public:
        invalid_command_line_style(const std::string& msg)
        : error(msg)
        {}
    };

    /** Class thrown if config file can not be read */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE reading_file : public error {
    public:
        reading_file(const char* filename)
         : error(std::string("can not read options configuration file '").append(filename).append("'"))
        {}
    };


    /** Base class for most exceptions in the library.
     *  
     *  Substitutes the values for the parameter name
     *      placeholders in the template to create the human
     *      readable error message
     *  
     *  Placeholders are surrounded by % signs: %example%
     *      Poor man's version of boost::format
     *  
     *  If a parameter name is absent, perform default substitutions
     *      instead so ugly placeholders are never left in-place.
     *  
     *  Options are displayed in "canonical" form
     *      This is the most unambiguous form of the
     *      *parsed* option name and would correspond to
     *      option_description::format_name()
     *      i.e. what is shown by print_usage()
     *  
     *  The "canonical" form depends on whether the option is
     *      specified in short or long form, using dashes or slashes
     *      or without a prefix (from a configuration file)
     *  
     *   */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE error_with_option_name : public error {

    protected:
        /** can be
         *      0 = no prefix (config file options)
         *      allow_long
         *      allow_dash_for_short
         *      allow_slash_for_short
         *      allow_long_disguise */
        int m_option_style;


        /** substitutions
         *  from placeholders to values */
        std::map<std::string, std::string> m_substitutions;
        typedef std::pair<std::string, std::string> string_pair;
        std::map<std::string, string_pair > m_substitution_defaults;

    public:
        /** template with placeholders */
        std::string m_error_template;

        error_with_option_name(const std::string& template_,
                               const std::string& option_name = "",
                               const std::string& original_token = "",
                               int option_style = 0);

        /** gcc says that throw specification on dtor is loosened 
         *  without this line                                     
         *  */ 
        ~error_with_option_name() throw() {}


        //void dump() const
        //{
        //  std::cerr << "m_substitution_defaults:\n";
        //  for (std::map<std::string, string_pair>::const_iterator iter = m_substitution_defaults.begin();
        //        iter != m_substitution_defaults.end(); ++iter)
        //      std::cerr << "\t" << iter->first << ":" << iter->second.first << "=" << iter->second.second << "\n";
        //  std::cerr << "m_substitutions:\n";
        //  for (std::map<std::string, std::string>::const_iterator iter = m_substitutions.begin();
        //        iter != m_substitutions.end(); ++iter)
        //      std::cerr << "\t" << iter->first << "=" << iter->second << "\n";
        //  std::cerr << "m_error_template:\n";
        //  std::cerr << "\t" << m_error_template << "\n";
        //  std::cerr << "canonical_option_prefix:[" << get_canonical_option_prefix() << "]\n";
        //  std::cerr << "canonical_option_name:[" << get_canonical_option_name() <<"]\n";
        //  std::cerr << "what:[" << what() << "]\n";
        //}

        /** Substitute
         *      parameter_name->value to create the error message from
         *      the error template */
        void set_substitute(const std::string& parameter_name,  const std::string& value)
        {           m_substitutions[parameter_name] = value;    }

        /** If the parameter is missing, then make the
         *      from->to substitution instead */
        void set_substitute_default(const std::string& parameter_name, 
                                    const std::string& from,  
                                    const std::string& to)
        {           
            m_substitution_defaults[parameter_name] = std::make_pair(from, to); 
        }


        /** Add context to an exception */
        void add_context(const std::string& option_name,
                         const std::string& original_token,
                         int option_style)
        {
            set_option_name(option_name);
            set_original_token(original_token);
            set_prefix(option_style);
        }

        void set_prefix(int option_style)
        {           m_option_style = option_style;}

        /** Overridden in error_with_no_option_name */
        virtual void set_option_name(const std::string& option_name)
        {           set_substitute("option", option_name);}

        std::string get_option_name() const
        {           return get_canonical_option_name();         }

        void set_original_token(const std::string& original_token)
        {           set_substitute("original_token", original_token);}


        /** Creates the error_message on the fly
         *      Currently a thin wrapper for substitute_placeholders() */
        virtual const char* what() const throw();

    protected:
        /** Used to hold the error text returned by what() */
        mutable std::string m_message;  // For on-demand formatting in 'what'

        /** Makes all substitutions using the template */
        virtual void substitute_placeholders(const std::string& error_template) const;

        // helper function for substitute_placeholders
        void replace_token(const std::string& from, const std::string& to) const;

        /** Construct option name in accordance with the appropriate
         *  prefix style: i.e. long dash or short slash etc */
        std::string get_canonical_option_name() const;
        std::string get_canonical_option_prefix() const;
    };


    /** Class thrown when there are several option values, but
        user called a method which cannot return them all. */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE multiple_values : public error_with_option_name {
    public:
        multiple_values() 
         : error_with_option_name("option '%canonical_option%' only takes a single argument"){}

        ~multiple_values() throw() {}
    };

    /** Class thrown when there are several occurrences of an
        option, but user called a method which cannot return 
        them all. */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE multiple_occurrences : public error_with_option_name {
    public:
        multiple_occurrences() 
         : error_with_option_name("option '%canonical_option%' cannot be specified more than once"){}

        ~multiple_occurrences() throw() {}

    };

    /** Class thrown when a required/mandatory option is missing */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE required_option : public error_with_option_name {
    public:
       // option name is constructed by the option_descriptor and never on the fly
       required_option(const std::string& option_name)
       : error_with_option_name("the option '%canonical_option%' is required but missing", "", option_name)
       {
       }

       ~required_option() throw() {}
    };

    /** Base class of unparsable options,
     *  when the desired option cannot be identified.
     *  
     *  
     *  It makes no sense to have an option name, when we can't match an option to the
     *      parameter
     *  
     *  Having this a part of the error_with_option_name hierachy makes error handling
     *      a lot easier, even if the name indicates some sort of conceptual dissonance!
     *  
     *   */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE error_with_no_option_name : public error_with_option_name {
    public:
        error_with_no_option_name(const std::string& template_,
                              const std::string& original_token = "")
        : error_with_option_name(template_, "", original_token)
        {
        }

        /** Does NOT set option name, because no option name makes sense */
        virtual void set_option_name(const std::string&) {}

        ~error_with_no_option_name() throw() {}
    };


    /** Class thrown when option name is not recognized. */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE unknown_option : public error_with_no_option_name {
    public:
        unknown_option(const std::string& original_token = "")
        : error_with_no_option_name("unrecognised option '%canonical_option%'", original_token)
        {
        }

        ~unknown_option() throw() {}
    };



    /** Class thrown when there's ambiguity amoung several possible options. */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE ambiguous_option : public error_with_no_option_name {
    public:
        ambiguous_option(const std::vector<std::string>& xalternatives)
        : error_with_no_option_name("option '%canonical_option%' is ambiguous"),
            m_alternatives(xalternatives)
        {}

        ~ambiguous_option() throw() {}

        const std::vector<std::string>& alternatives() const throw() {return m_alternatives;}

    protected:
        /** Makes all substitutions using the template */
        virtual void substitute_placeholders(const std::string& error_template) const;
    private:
        // TODO: copy ctor might throw
        std::vector<std::string> m_alternatives;
    };


    /** Class thrown when there's syntax error either for command
     *  line or config file options. See derived children for
     *  concrete classes. */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE invalid_syntax : public error_with_option_name {
    public:
        enum kind_t {
            long_not_allowed = 30,
            long_adjacent_not_allowed,
            short_adjacent_not_allowed,
            empty_adjacent_parameter,
            missing_parameter,
            extra_parameter,
            unrecognized_line
        };

        invalid_syntax(kind_t kind, 
                       const std::string& option_name = "",
                       const std::string& original_token = "",
                       int option_style              = 0):
            error_with_option_name(get_template(kind), option_name, original_token, option_style),
            m_kind(kind)
        {
        }

        ~invalid_syntax() throw() {}

        kind_t kind() const {return m_kind;}

        /** Convenience functions for backwards compatibility */
        virtual std::string tokens() const {return get_option_name();   }
    protected:
        /** Used to convert kind_t to a related error text */
        std::string get_template(kind_t kind);
        kind_t m_kind;
    };

    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE invalid_config_file_syntax : public invalid_syntax {
    public:
        invalid_config_file_syntax(const std::string& invalid_line, kind_t kind):
            invalid_syntax(kind)
        {
            m_substitutions["invalid_line"] = invalid_line;
        }

        ~invalid_config_file_syntax() throw() {}

        /** Convenience functions for backwards compatibility */
        virtual std::string tokens() const {return m_substitutions.find("invalid_line")->second;    }
    };


    /** Class thrown when there are syntax errors in given command line */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE invalid_command_line_syntax : public invalid_syntax {
    public:
        invalid_command_line_syntax(kind_t kind,
                       const std::string& option_name = "",
                       const std::string& original_token = "",
                       int option_style              = 0):
            invalid_syntax(kind, option_name, original_token, option_style) {}
        ~invalid_command_line_syntax() throw() {}
    };


    /** Class thrown when value of option is incorrect. */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE validation_error : public error_with_option_name {
    public:
        enum kind_t {
            multiple_values_not_allowed = 30,
            at_least_one_value_required, 
            invalid_bool_value,
            invalid_option_value,
            invalid_option
        };
        
    public:
        validation_error(kind_t kind, 
                   const std::string& option_name = "",
                   const std::string& original_token = "",
                   int option_style              = 0):
        error_with_option_name(get_template(kind), option_name, original_token, option_style),
        m_kind(kind)
        {
        }

        ~validation_error() throw() {}

        kind_t kind() const { return m_kind; }

    protected:
        /** Used to convert kind_t to a related error text */
        std::string get_template(kind_t kind);
        kind_t m_kind;
    };

    /** Class thrown if there is an invalid option value given */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE invalid_option_value
        : public validation_error
    {
    public:
        invalid_option_value(const std::string& value);
#ifndef BOOST_NO_STD_WSTRING
        invalid_option_value(const std::wstring& value);
#endif
    };

    /** Class thrown if there is an invalid bool value given */
    class BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_VISIBLE invalid_bool_value
        : public validation_error
    {
    public:
        invalid_bool_value(const std::string& value);
    };





    

}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#endif

/* errors.hpp
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
*/