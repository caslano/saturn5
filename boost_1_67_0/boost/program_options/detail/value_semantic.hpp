// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file defines template functions that are declared in
// ../value_semantic.hpp.

#include <boost/throw_exception.hpp>

// forward declaration
namespace boost { template<class T> class optional; }

namespace boost { namespace program_options { 

    extern BOOST_PROGRAM_OPTIONS_DECL std::string arg;
    
    template<class T, class charT>
    std::string
    typed_value<T, charT>::name() const
    {
        std::string const& var = (m_value_name.empty() ? arg : m_value_name);
        if (!m_implicit_value.empty() && !m_implicit_value_as_text.empty()) {
            std::string msg = "[=" + var + "(=" + m_implicit_value_as_text + ")]";
            if (!m_default_value.empty() && !m_default_value_as_text.empty())
                msg += " (=" + m_default_value_as_text + ")";
            return msg;
        }
        else if (!m_default_value.empty() && !m_default_value_as_text.empty()) {
            return var + " (=" + m_default_value_as_text + ")";
        } else {
            return var;
        }
    }

    template<class T, class charT>
    void 
    typed_value<T, charT>::notify(const boost::any& value_store) const
    {
        const T* value = boost::any_cast<T>(&value_store);
        if (m_store_to) {
            *m_store_to = *value;
        }
        if (m_notifier) {
            m_notifier(*value);
        }
    }

    namespace validators {
        /* If v.size() > 1, throw validation_error. 
           If v.size() == 1, return v.front()
           Otherwise, returns a reference to a statically allocated
           empty string if 'allow_empty' and throws validation_error
           otherwise. */
        template<class charT>
        const std::basic_string<charT>& get_single_string(
            const std::vector<std::basic_string<charT> >& v, 
            bool allow_empty = false)
        {
            static std::basic_string<charT> empty;
            if (v.size() > 1)
                boost::throw_exception(validation_error(validation_error::multiple_values_not_allowed));
            else if (v.size() == 1)
                return v.front();
            else if (!allow_empty)
                boost::throw_exception(validation_error(validation_error::at_least_one_value_required));
            return empty;
        }

        /* Throws multiple_occurrences if 'value' is not empty. */
        BOOST_PROGRAM_OPTIONS_DECL void 
        check_first_occurrence(const boost::any& value);
    }

    using namespace validators;

    /** Validates 's' and updates 'v'.
        @pre 'v' is either empty or in the state assigned by the previous
        invocation of 'validate'.
        The target type is specified via a parameter which has the type of 
        pointer to the desired type. This is workaround for compilers without
        partial template ordering, just like the last 'long/int' parameter.
    */
    template<class T, class charT>
    void validate(boost::any& v, 
                  const std::vector< std::basic_string<charT> >& xs, 
                  T*, long)
    {
        validators::check_first_occurrence(v);
        std::basic_string<charT> s(validators::get_single_string(xs));
        try {
            v = any(lexical_cast<T>(s));
        }
        catch(const bad_lexical_cast&) {
            boost::throw_exception(invalid_option_value(s));
        }
    }

    BOOST_PROGRAM_OPTIONS_DECL void validate(boost::any& v, 
                       const std::vector<std::string>& xs, 
                       bool*,
                       int);

#if !defined(BOOST_NO_STD_WSTRING)
    BOOST_PROGRAM_OPTIONS_DECL void validate(boost::any& v, 
                       const std::vector<std::wstring>& xs, 
                       bool*,
                       int);
#endif
    // For some reason, this declaration, which is require by the standard,
    // cause msvc 7.1 to not generate code to specialization defined in
    // value_semantic.cpp
#if ! ( BOOST_WORKAROUND(BOOST_MSVC, == 1310) )
    BOOST_PROGRAM_OPTIONS_DECL void validate(boost::any& v, 
                       const std::vector<std::string>& xs,
                       std::string*,
                       int);

#if !defined(BOOST_NO_STD_WSTRING)
    BOOST_PROGRAM_OPTIONS_DECL void validate(boost::any& v, 
                       const std::vector<std::wstring>& xs,
                       std::string*,
                       int);
#endif
#endif

    /** Validates sequences. Allows multiple values per option occurrence
       and multiple occurrences. */
    template<class T, class charT>
    void validate(boost::any& v, 
                  const std::vector<std::basic_string<charT> >& s, 
                  std::vector<T>*,
                  int)
    {
        if (v.empty()) {
            v = boost::any(std::vector<T>());
        }
        std::vector<T>* tv = boost::any_cast< std::vector<T> >(&v);
        assert(NULL != tv);
        for (unsigned i = 0; i < s.size(); ++i)
        {
            try {
                /* We call validate so that if user provided
                   a validator for class T, we use it even
                   when parsing vector<T>.  */
                boost::any a;
                std::vector<std::basic_string<charT> > cv;
                cv.push_back(s[i]);
                validate(a, cv, (T*)0, 0);                
                tv->push_back(boost::any_cast<T>(a));
            }
            catch(const bad_lexical_cast& /*e*/) {
                boost::throw_exception(invalid_option_value(s[i]));
            }
        }
    }

    /** Validates optional arguments. */
    template<class T, class charT>
    void validate(boost::any& v,
                  const std::vector<std::basic_string<charT> >& s,
                  boost::optional<T>*,
                  int)
    {
        validators::check_first_occurrence(v);
        validators::get_single_string(s);
        boost::any a;
        validate(a, s, (T*)0, 0);
        v = boost::any(boost::optional<T>(boost::any_cast<T>(a)));
    }

    template<class T, class charT>
    void 
    typed_value<T, charT>::
    xparse(boost::any& value_store, 
           const std::vector<std::basic_string<charT> >& new_tokens) const
    {
        // If no tokens were given, and the option accepts an implicit
        // value, then assign the implicit value as the stored value;
        // otherwise, validate the user-provided token(s).
        if (new_tokens.empty() && !m_implicit_value.empty())
            value_store = m_implicit_value;
        else
            validate(value_store, new_tokens, (T*)0, 0);
    }

    template<class T>
    typed_value<T>*
    value()
    {
        // Explicit qualification is vc6 workaround.
        return boost::program_options::value<T>(0);
    }

    template<class T>
    typed_value<T>*
    value(T* v)
    {
        typed_value<T>* r = new typed_value<T>(v);

        return r;        
    }

    template<class T>
    typed_value<T, wchar_t>*
    wvalue()
    {
        return wvalue<T>(0);
    }

    template<class T>
    typed_value<T, wchar_t>*
    wvalue(T* v)
    {
        typed_value<T, wchar_t>* r = new typed_value<T, wchar_t>(v);

        return r;        
    }



}}

/* value_semantic.hpp
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
*/