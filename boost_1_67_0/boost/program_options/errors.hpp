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
    class BOOST_PROGRAM_OPTIONS_DECL error : public std::logic_error {
    public:
        error(const std::string& xwhat) : std::logic_error(xwhat) {}
    };


    /** Class thrown when there are too many positional options. 
        This is a programming error.
    */
    class BOOST_PROGRAM_OPTIONS_DECL too_many_positional_options_error : public error {
    public:
        too_many_positional_options_error() 
         : error("too many positional options have been specified on the command line") 
        {}
    };

    /** Class thrown when there are programming error related to style */
    class BOOST_PROGRAM_OPTIONS_DECL invalid_command_line_style : public error {
    public:
        invalid_command_line_style(const std::string& msg)
        : error(msg)
        {}
    };

    /** Class thrown if config file can not be read */
    class BOOST_PROGRAM_OPTIONS_DECL reading_file : public error {
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
    class BOOST_PROGRAM_OPTIONS_DECL error_with_option_name : public error {

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
    class BOOST_PROGRAM_OPTIONS_DECL multiple_values : public error_with_option_name {
    public:
        multiple_values() 
         : error_with_option_name("option '%canonical_option%' only takes a single argument"){}

        ~multiple_values() throw() {}
    };

    /** Class thrown when there are several occurrences of an
        option, but user called a method which cannot return 
        them all. */
    class BOOST_PROGRAM_OPTIONS_DECL multiple_occurrences : public error_with_option_name {
    public:
        multiple_occurrences() 
         : error_with_option_name("option '%canonical_option%' cannot be specified more than once"){}

        ~multiple_occurrences() throw() {}

    };

    /** Class thrown when a required/mandatory option is missing */
    class BOOST_PROGRAM_OPTIONS_DECL required_option : public error_with_option_name {
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
    class BOOST_PROGRAM_OPTIONS_DECL error_with_no_option_name : public error_with_option_name {
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
    class BOOST_PROGRAM_OPTIONS_DECL unknown_option : public error_with_no_option_name {
    public:
        unknown_option(const std::string& original_token = "")
        : error_with_no_option_name("unrecognised option '%canonical_option%'", original_token)
        {
        }

        ~unknown_option() throw() {}
    };



    /** Class thrown when there's ambiguity amoung several possible options. */
    class BOOST_PROGRAM_OPTIONS_DECL ambiguous_option : public error_with_no_option_name {
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
    class BOOST_PROGRAM_OPTIONS_DECL invalid_syntax : public error_with_option_name {
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

    class BOOST_PROGRAM_OPTIONS_DECL invalid_config_file_syntax : public invalid_syntax {
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
    class BOOST_PROGRAM_OPTIONS_DECL invalid_command_line_syntax : public invalid_syntax {
    public:
        invalid_command_line_syntax(kind_t kind,
                       const std::string& option_name = "",
                       const std::string& original_token = "",
                       int option_style              = 0):
            invalid_syntax(kind, option_name, original_token, option_style) {}
        ~invalid_command_line_syntax() throw() {}
    };


    /** Class thrown when value of option is incorrect. */
    class BOOST_PROGRAM_OPTIONS_DECL validation_error : public error_with_option_name {
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
    class BOOST_PROGRAM_OPTIONS_DECL invalid_option_value 
        : public validation_error
    {
    public:
        invalid_option_value(const std::string& value);
#ifndef BOOST_NO_STD_WSTRING
        invalid_option_value(const std::wstring& value);
#endif
    };

    /** Class thrown if there is an invalid bool value given */
    class BOOST_PROGRAM_OPTIONS_DECL invalid_bool_value 
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