// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_VARIABLES_MAP_VP_2003_05_19
#define BOOST_VARIABLES_MAP_VP_2003_05_19

#include <boost/program_options/config.hpp>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <map>
#include <set>

#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4251) // 'boost::program_options::variable_value::v' : class 'boost::any' needs to have dll-interface to be used by clients of class 'boost::program_options::variable_value
#endif

namespace boost { namespace program_options {

    template<class charT>
    class basic_parsed_options;

    class value_semantic;
    class variables_map;

    // forward declaration

    /** Stores in 'm' all options that are defined in 'options'.
        If 'm' already has a non-defaulted value of an option, that value
        is not changed, even if 'options' specify some value.
    */
    BOOST_PROGRAM_OPTIONS_DECL
    void store(const basic_parsed_options<char>& options, variables_map& m,
                    bool utf8 = false);

    /** Stores in 'm' all options that are defined in 'options'.
        If 'm' already has a non-defaulted value of an option, that value
        is not changed, even if 'options' specify some value.
        This is wide character variant.
    */
    BOOST_PROGRAM_OPTIONS_DECL
    void store(const basic_parsed_options<wchar_t>& options,
                    variables_map& m);


    /** Runs all 'notify' function for options in 'm'. */
    BOOST_PROGRAM_OPTIONS_DECL void notify(variables_map& m);

    /** Class holding value of option. Contains details about how the
        value is set and allows to conveniently obtain the value.
    */
    class BOOST_PROGRAM_OPTIONS_DECL variable_value {
    public:
        variable_value() : m_defaulted(false) {}
        variable_value(const boost::any& xv, bool xdefaulted)
        : v(xv), m_defaulted(xdefaulted)
        {}

        /** If stored value if of type T, returns that value. Otherwise,
            throws boost::bad_any_cast exception. */
       template<class T>
       const T& as() const {
           return boost::any_cast<const T&>(v);
       }
       /** @overload */
       template<class T>
       T& as() {
           return boost::any_cast<T&>(v);
       }

        /// Returns true if no value is stored.
        bool empty() const;
        /** Returns true if the value was not explicitly
            given, but has default value. */
        bool defaulted() const;
        /** Returns the contained value. */
        const boost::any& value() const;

        /** Returns the contained value. */
        boost::any& value();
    private:
        boost::any v;
        bool m_defaulted;
        // Internal reference to value semantic. We need to run
        // notifications when *final* values of options are known, and
        // they are known only after all sources are stored. By that
        // time options_description for the first source might not
        // be easily accessible, so we need to store semantic here.
        shared_ptr<const value_semantic> m_value_semantic;

        friend BOOST_PROGRAM_OPTIONS_DECL
        void store(const basic_parsed_options<char>& options,
              variables_map& m, bool);

        friend class BOOST_PROGRAM_OPTIONS_DECL variables_map;
    };

    /** Implements string->string mapping with convenient value casting
        facilities. */
    class BOOST_PROGRAM_OPTIONS_DECL abstract_variables_map {
    public:
        abstract_variables_map();
        abstract_variables_map(const abstract_variables_map* next);

        virtual ~abstract_variables_map() {}

        /** Obtains the value of variable 'name', from *this and
            possibly from the chain of variable maps.

            - if there's no value in *this.
                - if there's next variable map, returns value from it
                - otherwise, returns empty value

            - if there's defaulted value
                - if there's next variable map, which has a non-defaulted
                  value, return that
                - otherwise, return value from *this

            - if there's a non-defaulted value, returns it.
        */
        const variable_value& operator[](const std::string& name) const;

        /** Sets next variable map, which will be used to find
           variables not found in *this. */
        void next(abstract_variables_map* next);

    private:
        /** Returns value of variable 'name' stored in *this, or
            empty value otherwise. */
        virtual const variable_value& get(const std::string& name) const = 0;

        const abstract_variables_map* m_next;
    };

    /** Concrete variables map which store variables in real map.

        This class is derived from std::map<std::string, variable_value>,
        so you can use all map operators to examine its content.
    */
    class BOOST_PROGRAM_OPTIONS_DECL variables_map : public abstract_variables_map,
                               public std::map<std::string, variable_value>
    {
    public:
        variables_map();
        variables_map(const abstract_variables_map* next);

        // Resolve conflict between inherited operators.
        const variable_value& operator[](const std::string& name) const
        { return abstract_variables_map::operator[](name); }

        // Override to clear some extra fields.
        void clear();

        void notify();

    private:
        /** Implementation of abstract_variables_map::get
            which does 'find' in *this. */
        const variable_value& get(const std::string& name) const;

        /** Names of option with 'final' values \-- which should not
            be changed by subsequence assignments. */
        std::set<std::string> m_final;

        friend BOOST_PROGRAM_OPTIONS_DECL
        void store(const basic_parsed_options<char>& options,
                          variables_map& xm,
                          bool utf8);

        /** Names of required options, filled by parser which has
            access to options_description.
            The map values are the "canonical" names for each corresponding option.
            This is useful in creating diagnostic messages when the option is absent. */
        std::map<std::string, std::string> m_required;
    };


    /*
     * Templates/inlines
     */

    inline bool
    variable_value::empty() const
    {
        return v.empty();
    }

    inline bool
    variable_value::defaulted() const
    {
        return m_defaulted;
    }

    inline
    const boost::any&
    variable_value::value() const
    {
        return v;
    }

    inline
    boost::any&
    variable_value::value()
    {
        return v;
    }

}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#endif

/* variables_map.hpp
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
*/