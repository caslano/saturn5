/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   settings.hpp
 * \author Andrey Semashev
 * \date   11.10.2009
 *
 * The header contains definition of the library settings container.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_SETTINGS_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_SETTINGS_HPP_INCLUDED_

#include <cstddef>
#include <string>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/move/core.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/optional/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/detail/native_typeof.hpp>
#if !defined(BOOST_LOG_TYPEOF)
#include <boost/core/enable_if.hpp>
#endif
#if defined(BOOST_LOG_TYPEOF) && defined(BOOST_NO_CXX11_TRAILING_RESULT_TYPES)
#include <boost/utility/declval.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// This workaround is needed for MSVC 10 to work around ICE caused by stack overflow
template< typename SectionT, bool IsConstV >
struct basic_settings_section_iterator_base;

template< typename SectionT >
struct basic_settings_section_iterator_base< SectionT, true >
{
    typedef typename SectionT::BOOST_NESTED_TEMPLATE iter< true > iterator_type;
    typedef typename SectionT::property_tree_type::const_iterator base_iterator_type;
    typedef iterator_adaptor<
        iterator_type,
        base_iterator_type,
        SectionT,
        use_default,
        const SectionT
    > type;
};

template< typename SectionT >
struct basic_settings_section_iterator_base< SectionT, false >
{
    typedef typename SectionT::BOOST_NESTED_TEMPLATE iter< false > iterator_type;
    typedef typename SectionT::property_tree_type::iterator base_iterator_type;
    typedef iterator_adaptor<
        iterator_type,
        base_iterator_type,
        SectionT,
        use_default,
        SectionT
    > type;
};

} // namespace aux

/*!
 * \brief The class represents a reference to the settings container section
 *
 * The section refers to a sub-tree of the library settings container. It does not
 * own the referred sub-tree but allows for convenient access to parameters within the subsection.
 */
template< typename CharT >
class basic_settings_section
{
    template< typename SectionT, bool IsConstV >
    friend struct aux::basic_settings_section_iterator_base;

public:
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Property tree type
    typedef property_tree::basic_ptree< std::string, string_type > property_tree_type;
    //! Property tree path type
    typedef typename property_tree_type::path_type path_type;

private:
#if !defined(BOOST_LOG_DOXYGEN_PASS)

    //! A reference proxy object
#ifndef BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
    template< bool IsConstV >
    class ref;
    template< bool IsConstV >
    friend class ref;
#endif
    template< bool IsConstV >
    class ref
    {
    private:
        typedef typename boost::conditional<
            IsConstV,
            basic_settings_section< char_type > const,
            basic_settings_section< char_type >
        >::type section_type;

    private:
        section_type& m_section;
        path_type m_path;

    public:
        ref(section_type& section, std::string const& section_name) :
            m_section(section),
            m_path(section_name)
        {
        }
        ref(section_type& section, const char* section_name) :
            m_section(section),
            m_path(section_name)
        {
        }

        ref& operator[] (std::string const& param_name)
        {
            m_path /= param_name;
            return *this;
        }

        ref& operator= (string_type const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            m_section.m_ptree->put(m_path, value);
            return *this;
        }

        template< bool V >
        ref& operator= (ref< V > const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            optional< string_type > val = value.get();
            if (!!val)
            {
                m_section.m_ptree->put(m_path, val);
            }
            else if (optional< property_tree_type& > node = m_section.m_ptree->get_child_optional(m_path))
            {
                node.put_value(string_type());
            }

            return *this;
        }

        template< typename T >
        ref& operator= (T const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            m_section.m_ptree->put(m_path, value);
            return *this;
        }

        BOOST_EXPLICIT_OPERATOR_BOOL()

        bool operator! () const
        {
            return !m_section.m_ptree || !m_section.m_ptree->get_child_optional(m_path);
        }

        std::string get_name() const
        {
            return m_path.dump();
        }

        operator optional< string_type > () const
        {
            return get();
        }

        optional< string_type > get() const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->template get_optional< string_type >(m_path);
            else
                return optional< string_type >();
        }

        template< typename T >
        optional< T > get() const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->template get_optional< T >(m_path);
            else
                return optional< T >();
        }

        operator section_type () const
        {
            return get_section();
        }

        section_type get_section() const
        {
            if (m_section.m_ptree)
                return section_type(m_section.m_ptree->get_child_optional(m_path).get_ptr());
            else
                return section_type();
        }

#if defined(BOOST_LOG_TYPEOF) && !(defined(__GNUC__) && !defined(__INTEL_COMPILER) && !defined(__clang__) && !defined(__PATHSCALE__) && !defined(__GXX_EXPERIMENTAL_CXX0X__) && (__GNUC__ == 4 && __GNUC_MINOR__ <= 5))
#if !defined(BOOST_NO_CXX11_TRAILING_RESULT_TYPES)
        template< typename T >
        auto or_default(T const& def_value) const -> BOOST_LOG_TYPEOF(property_tree_type().get(typename property_tree_type::path_type(), def_value))
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->get(m_path, def_value);
            else
                return def_value;
        }
#else
        // GCC up to 4.5 (inclusively) segfaults on the following code, if C++11 mode is not enabled
        template< typename T >
        BOOST_LOG_TYPEOF(property_tree_type().get(typename property_tree_type::path_type(), boost::declval< T >())) or_default(T const& def_value) const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->get(m_path, def_value);
            else
                return def_value;
        }
#endif
#else
        template< typename T >
        T or_default(T const& def_value) const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->get(m_path, def_value);
            else
                return def_value;
        }

        template< typename T >
        typename boost::enable_if_c< boost::property_tree::detail::is_character< T >::value, std::basic_string< T > >::type
        or_default(const T* def_value) const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->get(m_path, def_value);
            else
                return def_value;
        }
#endif
        string_type or_default(string_type const& def_value) const
        {
            return get().get_value_or(def_value);
        }
        string_type or_default(typename string_type::value_type const* def_value) const
        {
            if (optional< string_type > val = get())
                return val.get();
            else
                return def_value;
        }
    };

    //! An iterator over subsections and parameters
#ifndef BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
    template< bool IsConstV >
    class iter;
    template< bool IsConstV >
    friend class iter;
#endif
    template< bool IsConstV >
    class iter :
        public aux::basic_settings_section_iterator_base< basic_settings_section< char_type >, IsConstV >::type
    {
        friend class boost::iterator_core_access;

        typedef typename iter::iterator_adaptor_ iterator_adaptor_;
        // NOTE: This typedef must not come from iterator_adaptor_::base_type in order to work around MSVC 10 ICE
        typedef typename aux::basic_settings_section_iterator_base< basic_settings_section< char_type >, IsConstV >::base_iterator_type base_iterator_type;

    public:
        typedef typename iterator_adaptor_::reference reference;

    public:
        BOOST_DEFAULTED_FUNCTION(iter(), {})
        template< bool OtherIsConstV >
        iter(iter< OtherIsConstV > const& that) : iterator_adaptor_(that.base()) {}
        explicit iter(base_iterator_type const& it) : iterator_adaptor_(it) {}

        //! Returns the section name
        std::string const& get_name() const
        {
            return this->base()->first;
        }

    private:
        reference dereference() const
        {
            return reference(const_cast< property_tree_type* >(&this->base()->second));
        }
    };

public:
    typedef ref< true > const_reference;
    typedef ref< false > reference;
    typedef iter< true > const_iterator;
    typedef iter< false > iterator;
    typedef std::reverse_iterator< const_iterator > const_reverse_iterator;
    typedef std::reverse_iterator< iterator > reverse_iterator;

#else

public:
    /*!
     * Constant reference to the parameter value
     */
    typedef implementation_defined const_reference;
    /*!
     * Mutable reference to the parameter value
     */
    typedef implementation_defined reference;

    /*!
     * Constant iterator over nested parameters and subsections
     */
    typedef implementation_defined const_iterator;
    /*!
     * Mutable iterator over nested parameters and subsections
     */
    typedef implementation_defined iterator;

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

protected:
    //! Parameters
    property_tree_type* m_ptree;

public:
    /*!
     * Default constructor. Creates an empty settings container.
     */
    basic_settings_section() : m_ptree(NULL)
    {
    }

    /*!
     * Copy constructor.
     */
    basic_settings_section(basic_settings_section const& that) : m_ptree(that.m_ptree)
    {
    }

    /*!
     * Checks if the section refers to the container.
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * Checks if the section refers to the container.
     */
    bool operator! () const BOOST_NOEXCEPT { return !m_ptree; }

    /*!
     * Returns an iterator over the nested subsections and parameters.
     */
    iterator begin()
    {
        if (m_ptree)
            return iterator(m_ptree->begin());
        else
            return iterator();
    }

    /*!
     * Returns an iterator over the nested subsections and parameters.
     */
    iterator end()
    {
        if (m_ptree)
            return iterator(m_ptree->end());
        else
            return iterator();
    }

    /*!
     * Returns an iterator over the nested subsections and parameters.
     */
    const_iterator begin() const
    {
        if (m_ptree)
            return const_iterator(m_ptree->begin());
        else
            return const_iterator();
    }

    /*!
     * Returns an iterator over the nested subsections and parameters.
     */
    const_iterator end() const
    {
        if (m_ptree)
            return const_iterator(m_ptree->end());
        else
            return const_iterator();
    }

    /*!
     * Returns a reverse iterator over the nested subsections and parameters.
     */
    reverse_iterator rbegin() { return reverse_iterator(begin()); }

    /*!
     * Returns a reverse iterator over the nested subsections and parameters.
     */
    reverse_iterator rend() { return reverse_iterator(end()); }

    /*!
     * Returns a reverse iterator over the nested subsections and parameters.
     */
    const_reverse_iterator rbegin() const { return const_reverse_iterator(begin()); }

    /*!
     * Returns a reverse iterator over the nested subsections and parameters.
     */
    const_reverse_iterator rend() const { return const_reverse_iterator(end()); }

    /*!
     * Checks if the container is empty (i.e. contains no sections and parameters).
     */
    bool empty() const { return m_ptree == NULL || m_ptree->empty(); }

    /*!
     * Accessor to a single parameter. This operator should be used in conjunction
     * with the subsequent subscript operator that designates the parameter name.
     *
     * \param section_name The name of the section in which the parameter resides
     * \return An unspecified reference type that can be used for parameter name specifying
     */
    reference operator[] (std::string const& section_name) { return reference(*this, section_name); }
    /*!
     * Accessor to a single parameter. This operator should be used in conjunction
     * with the subsequent subscript operator that designates the parameter name.
     *
     * \param section_name The name of the section in which the parameter resides
     * \return An unspecified reference type that can be used for parameter name specifying
     */
    const_reference operator[] (std::string const& section_name) const { return const_reference(*this, section_name); }

    /*!
     * Accessor to a single parameter. This operator should be used in conjunction
     * with the subsequent subscript operator that designates the parameter name.
     *
     * \param section_name The name of the section in which the parameter resides
     * \return An unspecified reference type that can be used for parameter name specifying
     */
    reference operator[] (const char* section_name) { return reference(*this, section_name); }
    /*!
     * Accessor to a single parameter. This operator should be used in conjunction
     * with the subsequent subscript operator that designates the parameter name.
     *
     * \param section_name The name of the section in which the parameter resides
     * \return An unspecified reference type that can be used for parameter name specifying
     */
    const_reference operator[] (const char* section_name) const { return const_reference(*this, section_name); }

    /*!
     * Accessor for the embedded property tree
     */
    property_tree_type const& property_tree() const { return *m_ptree; }
    /*!
     * Accessor for the embedded property tree
     */
    property_tree_type& property_tree() { return *m_ptree; }

    /*!
     * Checks if the specified section is present in the container.
     *
     * \param section_name The name of the section
     */
    bool has_section(string_type const& section_name) const
    {
        return m_ptree != NULL && !!m_ptree->get_child_optional(section_name);
    }
    /*!
     * Checks if the specified parameter is present in the container.
     *
     * \param section_name The name of the section in which the parameter resides
     * \param param_name The name of the parameter
     */
    bool has_parameter(string_type const& section_name, string_type const& param_name) const
    {
        if (m_ptree)
        {
            optional< property_tree_type& > section = m_ptree->get_child_optional(section_name);
            if (!!section)
                return (section->find(param_name) != section->not_found());
        }

        return false;
    }

    /*!
     * Swaps two references to settings sections.
     */
    void swap(basic_settings_section& that)
    {
        property_tree_type* const p = m_ptree;
        m_ptree = that.m_ptree;
        that.m_ptree = p;
    }

protected:
    explicit basic_settings_section(property_tree_type* tree) : m_ptree(tree)
    {
    }
};

template< typename CharT >
inline void swap(basic_settings_section< CharT >& left, basic_settings_section< CharT >& right)
{
    left.swap(right);
}


/*!
 * \brief The class represents settings container
 *
 * All settings are presented as a number of named parameters divided into named sections.
 * The parameters values are stored as strings. Individual parameters may be queried via subscript operators, like this:
 *
 * <code><pre>
 * optional< string > param = settings["Section1"]["Param1"]; // reads parameter "Param1" in section "Section1"
 *                                                            // returns an empty value if no such parameter exists
 * settings["Section2"]["Param2"] = 10; // sets the parameter "Param2" in section "Section2"
 *                                      // to value "10"
 * </pre></code>
 *
 * There are also other methods to work with parameters.
 */
template< typename CharT >
class basic_settings :
    public basic_settings_section< CharT >
{
    typedef basic_settings this_type;
    BOOST_COPYABLE_AND_MOVABLE(this_type)

public:
    //! Section type
    typedef basic_settings_section< CharT > section;
    //! Property tree type
    typedef typename section::property_tree_type property_tree_type;

public:
    /*!
     * Default constructor. Creates an empty settings container.
     */
    basic_settings() : section(new property_tree_type())
    {
    }

    /*!
     * Copy constructor.
     */
    basic_settings(basic_settings const& that) :
        section(that.m_ptree ? new property_tree_type(*that.m_ptree) : static_cast< property_tree_type* >(NULL))
    {
    }

    /*!
     * Move constructor.
     */
    basic_settings(BOOST_RV_REF(this_type) that)
    {
        this->swap(that);
    }
    /*!
     * Initializing constructor. Creates a settings container with the copy of the specified property tree.
     */
    explicit basic_settings(property_tree_type const& tree) : section(new property_tree_type(tree))
    {
    }

    /*!
     * Destructor
     */
    ~basic_settings()
    {
        delete this->m_ptree;
    }

    /*!
     * Copy assignment operator.
     */
    basic_settings& operator= (BOOST_COPY_ASSIGN_REF(basic_settings) that)
    {
        if (this != &that)
        {
            basic_settings tmp = that;
            this->swap(tmp);
        }
        return *this;
    }
    /*!
     * Move assignment operator.
     */
    basic_settings& operator= (BOOST_RV_REF(basic_settings) that)
    {
        this->swap(that);
        return *this;
    }
};

#ifdef BOOST_LOG_USE_CHAR
typedef basic_settings< char > settings;                        //!< Convenience typedef for narrow-character logging
typedef basic_settings_section< char > settings_section;        //!< Convenience typedef for narrow-character logging
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_settings< wchar_t > wsettings;                    //!< Convenience typedef for wide-character logging
typedef basic_settings_section< wchar_t > wsettings_section;    //!< Convenience typedef for wide-character logging
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_SETTINGS_HPP_INCLUDED_

/* settings.hpp
EI5rOUs5DbyA5wX6O7gnlv6hqZxmmufI3vlfloSJVJUN+AOrw6mKdvXdBXZZ3W3uOx6mtE2bOiG7QCSu7fPlerrufwl/HvIQol5XOUxrVXuhaxqp01tcOb0iQV2Unav5TvPiKtJcXM00G3PCxrTtyX4yiPVf6k1zfl6+db6g7ze9LGEG+LLFwTjs+576vsxb4t/JNM4GrtPZ/K1a18QT8DKOj51Bb7tl9Hd781JU4OxbFbvb+bcqdrfzb5UeNopnImh9xn1nbzlUfc/5XL834JN38ZzC0hZ2N9XkGcS2cC0oyj0WmMpvWuFkZVvIljD9tdrqtsA4Qnzu794v/on28rXz4skxznnEPpb4tzO1o6ptcKjLz3c/yW/mYX6VZbOO9ko2mMvGx9ppi4R5SbsJfxery4fx2PW469+i4+JfhLmoy15G5LfNZ1i234hfc60ey6vDHs+aPlkLN9ZCyeIW4XMee0riyIMcZmiVa6EY036wUz3s7m/U17sr7Qnvsc5Rh+A3/S11k84LoJtYNxtBTZHo0j163cgHQlk3L0uY9dok/H1MWTeMx3KOmTfNfH5zUPyL1Ota8qtspuh1u1f8Z6vXteT3Vbdf7LHWbeu9nrptaqrbpL3+17lHJY68Gl3nhvq3jyL1ecaoT65R9lrXuQP2qs9Gu7S0trNo0ArwlO7V69ty3bXKsd7DF2KUTwjLR1mXe519d5XlwrwkMn7L/vWF9jw94dZFoMgT96+rzJfwWvZj5BOgHj+qmS/Z12D85m/yIUW+DqIMykz5crr/DR67/T5fcgvnlJ8Ma/uV+K1tL6yVff98h1vngSk/ge6fl+91vn9ebisDeY9y3GBY47s4tgb32tmnWU6SBks57W9lq3eRR6qwlhOlkaqWR6rY61weqaLqur+26jmUxG9py6svVudJ2+fNk9MzBeGx1jnYlHWOsFXmx29bZr0hfmvfnNnanp/CyzDGW/Ij678q60d4LPM7YVPPl88pP5XmaBK/dQxNb6Oun2RTfs7lTED4LXueZPbRR5Md5s/v2YdmP/swvn9t1flMMeUzkLOFFFtbdLP6uJ/rMG9+26LEb81TZDt7npphctLHm6ei7EJ9wHCwh7TP+XjRp+o8WcaL9Q7Hi9PME0FryzOgVG+eIG4kcgOWOtLndiMkXBTP+HW+BuZ80i1EKRMwaZ9VB0m9hKrH/ypkNyz5m3eJbuOZSNmMYm/+plNXVpVtEDyWb1WJA30pldJqSdtcHrRuAIm8HehIA8TrTRvvh1u/PQ25LnhKwr0mexuZoGUg5fmrqZ01iLWfee2AP+fW9rZHfn9nXlvFfxrWfaH2bzz5fa0NPtpnXRsk7revDcL2q9cGclYBfEnieFYbgdJdUIPrgwaxVZ+D7d9nXR/E8f7xTq4POu1Xn1mcYd13ZkI68e59sYSfi4FWZKFzp+Vrhg30Uy3ce64gB3v95nFrZYptz0/6QJn3XSKfxAmhff+DdbNbwseo5737rX0j7RzncV6dAL7u2geuE8DXXfKBcsf/+x6PD2t+c6/yvx38Ku93S89eHfhdeLXuAt86AdR39v/9dtPUugV838FX6xzwrWNBrdPA991/tU6GwHUXfEO7WRrH5HTe0cZ5q/z/d03k5eX/+0Af030BSOzk8E4GZRnFz7CTQ/sxbr/JwNq0GxMD/DWwDu3GnA8sAPakXYvBtHORCpwFnMTwk2lf5k7gVOACuvOeOu8poM8xHcY9dd6n1nifug7wLvO9bPI1ED7rveJLaF+nPe2bdQDWB6YAmX/KsqvzP5D5H8z8D2H+05j/65j/UcArgOOY7/HAEcAbgTcz/C3AVOb/euYf7sw/5b+B8ar8hzA=
*/