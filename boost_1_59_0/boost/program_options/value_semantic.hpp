// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_VALUE_SEMANTIC_HPP_VP_2004_02_24
#define BOOST_VALUE_SEMANTIC_HPP_VP_2004_02_24

#include <boost/program_options/config.hpp>
#include <boost/program_options/errors.hpp>

#include <boost/any.hpp>
#include <boost/function/function1.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>
#include <typeinfo>
#include <limits>

namespace boost { namespace program_options {

    /** Class which specifies how the option's value is to be parsed
        and converted into C++ types.
    */
    class BOOST_PROGRAM_OPTIONS_DECL value_semantic {
    public:
        /** Returns the name of the option. The name is only meaningful
            for automatic help message.
         */
        virtual std::string name() const = 0;

        /** The minimum number of tokens for this option that
            should be present on the command line. */
        virtual unsigned min_tokens() const = 0;

        /** The maximum number of tokens for this option that
            should be present on the command line. */
        virtual unsigned max_tokens() const = 0;

        /** Returns true if values from different sources should be composed.
            Otherwise, value from the first source is used and values from
            other sources are discarded.
        */
        virtual bool is_composing() const = 0;

        /** Returns true if value must be given. Non-optional value

        */
        virtual bool is_required() const = 0;
        
        /** Parses a group of tokens that specify a value of option.
            Stores the result in 'value_store', using whatever representation
            is desired. May be be called several times if value of the same
            option is specified more than once.
        */
        virtual void parse(boost::any& value_store, 
                           const std::vector<std::string>& new_tokens,
                           bool utf8) const 
            = 0;

        /** Called to assign default value to 'value_store'. Returns
            true if default value is assigned, and false if no default
            value exists. */
        virtual bool apply_default(boost::any& value_store) const = 0;
                                   
        /** Called when final value of an option is determined. 
        */
        virtual void notify(const boost::any& value_store) const = 0;
        
        virtual ~value_semantic() {}
    };

    /** Helper class which perform necessary character conversions in the 
        'parse' method and forwards the data further.
    */
    template<class charT>
    class value_semantic_codecvt_helper {
        // Nothing here. Specializations to follow.
    };

    /** Helper conversion class for values that accept ascii
        strings as input.
        Overrides the 'parse' method and defines new 'xparse'
        method taking std::string. Depending on whether input
        to parse is ascii or UTF8, will pass it to xparse unmodified,
        or with UTF8->ascii conversion.
    */
    template<>
    class BOOST_PROGRAM_OPTIONS_DECL 
    value_semantic_codecvt_helper<char> : public value_semantic {
    private: // base overrides
        void parse(boost::any& value_store, 
                   const std::vector<std::string>& new_tokens,
                   bool utf8) const;
    protected: // interface for derived classes.
        virtual void xparse(boost::any& value_store, 
                            const std::vector<std::string>& new_tokens) 
            const = 0;
    };

    /** Helper conversion class for values that accept ascii
        strings as input.
        Overrides the 'parse' method and defines new 'xparse'
        method taking std::wstring. Depending on whether input
        to parse is ascii or UTF8, will recode input to Unicode, or
        pass it unmodified.
    */
    template<>
    class BOOST_PROGRAM_OPTIONS_DECL
    value_semantic_codecvt_helper<wchar_t> : public value_semantic {
    private: // base overrides
        void parse(boost::any& value_store, 
                   const std::vector<std::string>& new_tokens,
                   bool utf8) const;
    protected: // interface for derived classes.
#if !defined(BOOST_NO_STD_WSTRING)
        virtual void xparse(boost::any& value_store, 
                            const std::vector<std::wstring>& new_tokens) 
            const = 0;
#endif
    };

    /** Class which specifies a simple handling of a value: the value will
        have string type and only one token is allowed. */    
    class BOOST_PROGRAM_OPTIONS_DECL 
    untyped_value : public value_semantic_codecvt_helper<char>  {
    public:
        untyped_value(bool zero_tokens = false)
        : m_zero_tokens(zero_tokens)
        {}

        std::string name() const;

        unsigned min_tokens() const;
        unsigned max_tokens() const;

        bool is_composing() const { return false; }

        bool is_required() const { return false; }
        
        /** If 'value_store' is already initialized, or new_tokens
            has more than one elements, throws. Otherwise, assigns
            the first string from 'new_tokens' to 'value_store', without
            any modifications.
         */
        void xparse(boost::any& value_store,
                    const std::vector<std::string>& new_tokens) const;

        /** Does nothing. */
        bool apply_default(boost::any&) const { return false; }

        /** Does nothing. */
        void notify(const boost::any&) const {}        
    private:
        bool m_zero_tokens;
    };

#ifndef BOOST_NO_RTTI
    /** Base class for all option that have a fixed type, and are
        willing to announce this type to the outside world.
        Any 'value_semantics' for which you want to find out the
        type can be dynamic_cast-ed to typed_value_base. If conversion
        succeeds, the 'type' method can be called.
    */
    class typed_value_base 
    {
    public:
        // Returns the type of the value described by this
        // object.
        virtual const std::type_info& value_type() const = 0;
        // Not really needed, since deletion from this
        // class is silly, but just in case.
        virtual ~typed_value_base() {}
    };
#endif


    /** Class which handles value of a specific type. */
    template<class T, class charT = char>
    class typed_value : public value_semantic_codecvt_helper<charT>
#ifndef BOOST_NO_RTTI
                      , public typed_value_base
#endif
    {
    public:
        /** Ctor. The 'store_to' parameter tells where to store
            the value when it's known. The parameter can be NULL. */
        typed_value(T* store_to) 
        : m_store_to(store_to), m_composing(false),
          m_implicit(false), m_multitoken(false),
          m_zero_tokens(false), m_required(false)
        {} 

        /** Specifies default value, which will be used
            if none is explicitly specified. The type 'T' should
            provide operator<< for ostream.
        */
        typed_value* default_value(const T& v)
        {
            m_default_value = boost::any(v);
            m_default_value_as_text = boost::lexical_cast<std::string>(v);
            return this;
        }

        /** Specifies default value, which will be used
            if none is explicitly specified. Unlike the above overload,
            the type 'T' need not provide operator<< for ostream,
            but textual representation of default value must be provided
            by the user.
        */
        typed_value* default_value(const T& v, const std::string& textual)
        {
            m_default_value = boost::any(v);
            m_default_value_as_text = textual;
            return this;
        }

        /** Specifies an implicit value, which will be used
            if the option is given, but without an adjacent value.
            Using this implies that an explicit value is optional,
        */
        typed_value* implicit_value(const T &v)
        {
            m_implicit_value = boost::any(v);
            m_implicit_value_as_text =
                boost::lexical_cast<std::string>(v);
            return this;
        }

        /** Specifies the name used to to the value in help message.  */
        typed_value* value_name(const std::string& name)
        {
            m_value_name = name;
            return this;
        }

        /** Specifies an implicit value, which will be used
            if the option is given, but without an adjacent value.
            Using this implies that an explicit value is optional, but if
            given, must be strictly adjacent to the option, i.e.: '-ovalue'
            or '--option=value'.  Giving '-o' or '--option' will cause the
            implicit value to be applied.
            Unlike the above overload, the type 'T' need not provide
            operator<< for ostream, but textual representation of default
            value must be provided by the user.
        */
        typed_value* implicit_value(const T &v, const std::string& textual)
        {
            m_implicit_value = boost::any(v);
            m_implicit_value_as_text = textual;
            return this;
        }

        /** Specifies a function to be called when the final value
            is determined. */
        typed_value* notifier(function1<void, const T&> f)
        {
            m_notifier = f;
            return this;
        }

        /** Specifies that the value is composing. See the 'is_composing' 
            method for explanation. 
        */
        typed_value* composing()
        {
            m_composing = true;
            return this;
        }

        /** Specifies that the value can span multiple tokens. 
        */
        typed_value* multitoken()
        {
            m_multitoken = true;
            return this;
        }

        /** Specifies that no tokens may be provided as the value of
            this option, which means that only presense of the option
            is significant. For such option to be useful, either the
            'validate' function should be specialized, or the 
            'implicit_value' method should be also used. In most
            cases, you can use the 'bool_switch' function instead of
            using this method. */
        typed_value* zero_tokens() 
        {
            m_zero_tokens = true;
            return this;
        }
            
        /** Specifies that the value must occur. */
        typed_value* required()
        {
            m_required = true;
            return this;
        }

    public: // value semantic overrides

        std::string name() const;

        bool is_composing() const { return m_composing; }

        unsigned min_tokens() const
        {
            if (m_zero_tokens || !m_implicit_value.empty()) {
                return 0;
            } else {
                return 1;
            }
        }

        unsigned max_tokens() const {
            if (m_multitoken) {
                return std::numeric_limits<unsigned>::max BOOST_PREVENT_MACRO_SUBSTITUTION();
            } else if (m_zero_tokens) {
                return 0;
            } else {
                return 1;
            }
        }

        bool is_required() const { return m_required; }

        /** Creates an instance of the 'validator' class and calls
            its operator() to perform the actual conversion. */
        void xparse(boost::any& value_store, 
                    const std::vector< std::basic_string<charT> >& new_tokens) 
            const;

        /** If default value was specified via previous call to 
            'default_value', stores that value into 'value_store'.
            Returns true if default value was stored.
        */
        virtual bool apply_default(boost::any& value_store) const
        {
            if (m_default_value.empty()) {
                return false;
            } else {
                value_store = m_default_value;
                return true;
            }
        }

        /** If an address of variable to store value was specified
            when creating *this, stores the value there. Otherwise,
            does nothing. */
        void notify(const boost::any& value_store) const;

    public: // typed_value_base overrides
        
#ifndef BOOST_NO_RTTI
        const std::type_info& value_type() const
        {
            return typeid(T);
        }
#endif
        

    private:
        T* m_store_to;
        
        // Default value is stored as boost::any and not
        // as boost::optional to avoid unnecessary instantiations.
        std::string m_value_name;
        boost::any m_default_value;
        std::string m_default_value_as_text;
        boost::any m_implicit_value;
        std::string m_implicit_value_as_text;
        bool m_composing, m_implicit, m_multitoken, m_zero_tokens, m_required;
        boost::function1<void, const T&> m_notifier;
    };


    /** Creates a typed_value<T> instance. This function is the primary
        method to create value_semantic instance for a specific type, which
        can later be passed to 'option_description' constructor.
        The second overload is used when it's additionally desired to store the 
        value of option into program variable.
    */
    template<class T>
    typed_value<T>*
    value();

    /** @overload 
    */
    template<class T>
    typed_value<T>*
    value(T* v);

    /** Creates a typed_value<T> instance. This function is the primary
        method to create value_semantic instance for a specific type, which
        can later be passed to 'option_description' constructor.
    */
    template<class T>
    typed_value<T, wchar_t>*
    wvalue();

    /** @overload   
    */
    template<class T>
    typed_value<T, wchar_t>*
    wvalue(T* v);

    /** Works the same way as the 'value<bool>' function, but the created
        value_semantic won't accept any explicit value. So, if the option 
        is present on the command line, the value will be 'true'.
    */
    BOOST_PROGRAM_OPTIONS_DECL typed_value<bool>*
    bool_switch();

    /** @overload
    */
    BOOST_PROGRAM_OPTIONS_DECL typed_value<bool>*    
    bool_switch(bool* v);

}}

#include "boost/program_options/detail/value_semantic.hpp"

#endif


/* value_semantic.hpp
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
*/