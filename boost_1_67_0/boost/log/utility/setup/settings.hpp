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
wIuSHRLdmez9/3jEnnfVdLIMSBDxWuKrz4HyamRYMYbyMwvfNrEGa8dSu8fr3rpD7PMAytz86/b6RTwrGxdbqIh2jezNwaINxL4aMKCUpPCmBbfGNgsGCkSyEgeuJN27WKhcBfOX2Y1FMzcGENIVnYkVkpULqAtYVOGVCCXUfUJF4u5NHr7Due4h8ksGFUkA3HeP69Nb/KFGuXtCbhABJbIQ6s+xxrocR7fsH3nAfeEinGgK6VAJ+7ACzL8sH2PEAgYOB3VN5sxFBFTL1SCfcYizAWMwYxFY8Pd1zhjjHrUo/iunidnz7xDLSwhUl9gjabb4lYYS8ksFf2lMyINgSpE8LUf94jqEYdQ1gqhkFx3KEcJoh0MuESPvqLyt3IPwYKzm7OLHTKCHekvpZz0ood4OwekIWHCkoTFm1ypf0dfqqyZH86FnzkemSjg8B+UpYNeLKTAmcr57cLFrl5/62IjRdQGpNTk3TH9j4AQSCKa85RUliF4AjsfAIoCPQRFQwmbbo0ClWZzzQUiNpVVeGN2eiMqtRNRrTTFjtHGtVgxh6pMfVIh0UmHYiA0VwV9W5WwGmiOF6/2Qg9uN24aEVLnmYxzXbCdPaK1NQt2skPYor0pjxZdehn0mwKg/zhN2oxqjhABo5BEiTe8utyc30pz7bwM6GFsBnBrhESfe43ReCpZk+gKHng9dZCS/vW2k7UGXA7so6wvx5Jx/ZM/Uv0VtaXCFbTzFpirrP9n2O1XFbfCk+hYsG2TNNkPkxS9VHFNV9gd/kuGc7csVjc010AjUJC+25XE3aL7HoBE4eiDs8oHGWW6/AnHWe2HjHyJWFbX8HE7ys9fHc00PMVpjINF4hgKt4am4VNFhJguBaYEB63m9zOLiUfaXIh4mfyFX4CfRFdoBh6/Fj/+IHmFHyx1+TWAtDbqJpqpZTd2cksB/vgMRhmE5EDpPhYchmVFCMUcI5dpWjVqfVCNwSat6+GZHiTqgff/po0I78sMnr1MUUQa5A32c+gJ3ToMM3uQrI7PBWdiNzR7tcfF96Sg+UMtLvqZW2+lAF5NsSWKqfJhsiROLM0SmOAmm1BdNrtk0zpNPZZpPbrXW7Yle//c1pb6jYhA4JKbqrhj3HMy8mhtB61YLm3tNdXzsYIqngVrb91WCveo95UzsHLYAAHMsKQiZP0W+SvumUVxZrYj0nlJRpAiYAHoh2O/RVKi9lHi82sCxnqa+7T3vP6Ce+MmpukP+dCqMqcpkUCNDBcbqNXRW7D60xm2RaM2nt9lrH2bzSljGp0aCsZeAtm7L6AN7ciwbOTQ7peSzKJ7FjJ4r1tnoJigdabbnOpHzkmRpXEx1zbgmz5h3NyVTAJ/mwR/nql+Nqz6eyLlWimHb7G0Q/2PVhDCcLykztQvoOMHhJVoNdkKUCY2YjWBuO6LQHZW1Yz+PtfM2Ncvv0L+cjYfFwD0Fojy+aHT3gzwBk9I4h22eztvt5MfD1yuNRRKLvakNNVttTJFPDqCYT9O4t7JrhKtCkBaGeLEDHh82nI9rrXwbDISJ8naXmbMSN3qI/bJ1T/XWTjqkoz9OLAlCIa6QV+YaLw96kMZvgGBLygTI9orlzCxF6uynm8+YW2yio+BI90mkyYsfSFuT/bTyuamwUBHZuCI5IyYQZdiuh8zTeFIuqJeLGzeuaZ5tHxSDd+yVVZplV6Jyg5BPvuWEzJTDjwsYrRH6ottXykWLctzJqKwgNfaF7p16Q2Vo8PVfSwyPv4rtNsdwkU8C1okqXG7IYX02YMJMTckpaz80OvvBUaN4ppyxvJVd7uI+fTeakbE9v9EsuiHqfSqWaVMl10yzxCUKG2PebcONZrgKR/4JW/Pubp5xkA9WI4KXN8su99fwdora68wu47C2rDGlKDIjyTmjpUMnAfmw60cit0/xnAIFccqO5P05Rw/J7p0NJTfTe4LEVy+e8fuIZMOVSz8nfeU/2LpPah9rLTyCtsziacofhyOW6ku//1yaByJK9UEYrO0pooDQiOViBhr6P3g36awnOIIh7wUQdzGLb4bheMK8rPZEkfvEed1goccRQlewsI2TkzsNR/XTo9ZtpHYNVKC+1oCmbMNZk33H5O3hRsLgU/L8/+/dsIwfqJ8R/BT/RYGtd/VuGRzSimq75coPrwlEhehpNEHyBIeowhMAKhX21xAM6uRucbQp78hUMOAaZWwhMijVOFWikz7P0LFhe5Hznv3EV4tnGntczrvXv8djnq17bsynReH9rK7DYMVDtxG+rEOyzvtco6N9bj/C8ObIvCC7JoLr5WABJUHKUvqe/BjqZb+d+XwyCxWbxLvhPV8rkaoDesVKBfvNIH/jDorxasWKO4UhgijGvZYhmLIPXIFCZPHqLDvLiFqRL4sU7xjpoK8WQl5CWwQHalfkXnM4+fm98SCof5J8Fj3Q6/gUT6lR6XQMP/OfrDv/7JJ0dCaJkj+jfU+5RDO8Mxbk8vX27Ai0D1u9oeFl9HlGWNHKTdNfMMaNfTMZ1N/pEmZrB3oD5wcgFYqeLDVr8mAhOZKb2cbgW437m04i8DGz+6c0KqCnk5mLHPFXBqMLtk4VGsS+bMCBZ10kkdo7Wrh3D62NNKcmrp3lY+0qu9r143JkT5Q9ZA9RS+U3B5WtyCudxaW+uB3HVpJK2/+7dDtp+xwvYX3/9zNriHSftvOzeY+PRsMlqHP5XynOJiBropuwho5qdgX7GP1punx7fclnaO6oKGqcpO+432Z3u/83N81XeivCyc91OIIfKaZJ7wfXkLICTlymGLKGqNgbaYDA8n4t++Yvxgi435PdV/1g8HDvB1x24xkC0/Mz5xSdsbDtLtgz/GtvdIIxgn7HxarPJwzfkA9NZvcC8LbsJChjlcokIueXxCfcVBsWnIYQRhfxZP2ytrR5jWsJ3eLqEmDKNtp/BjGto/ARehPoFoX9EYDmtcV+Gds2uOuDPtywQvtXsQ341631fbjCVYyckBkC7hN3TQgJBRPEKCrSRFoKMvwL3cA2btdx3zpuB2pFEmR3ZhjQYOTgPSmVZ8TnENC2tCd4b8zxiZGzBZ4FuuTRKa4/9188v5bkHW8BiCYqns9BIDy2sBS7yJ9jP3GjDUd25Ob5Km3oMw/nqRf57G69ptnYz2CzqnctwDCuLzL/QfZU0Snw5d8EASQeCYMOlSSClqLHDYZMlNKgtkPoTmfTwnwjkRQpvNYcgI3AzyTUWXWCTSudyXHnh/W/yZDaj456Itn2+7fjgUEqWvTaL556ox19bwSKRAY4EV3pMWXYUg7iLY3juXbaSam/fektT7JTnN3TQwPXZCudzhV57xdqp3wxZmMixYDo7VK1ORgcyFcmEi7VZuh4sWkSi9VT6xN5cW3j8gsM+/YrrPp40n7bj9sqyAxfPeZQE/rVkRu/cVRQ2atvYPeFo0Z5+MDmnliBtZIl9Orz4/j//LwzfGkXstOOiN1GcUpDWSsSmZNo7xXzGP1b8nwNXPlsXXXSgYDOLIlXtpspAInCjGEFl7HZvkdrzC74dS+ZnvBiRdhGEsG2RruerqbzDla1KVI6ZYG8od8PDOaOB9hN4xcvcd+MTh82Cku/+QmlD+Y7YjquYDJ/PsFrjD//Sab7qemENjgTmv3P6D/eD+4kk0dm93qsR+warbuGwnkX1H3aJr67EOrRTvhjUuTdaDST65SUPJq6yf/adn5qwgqOTjrk7UfWob9BjIc34NVm8R0yLwPfJJBF1sLn89smqm821XQQm9Y3ro/blAQv6On6PY+lLBodjlNr5k27T18VttCb5leugtdQyarRst4+29per4l2lqRyvp7dKs4FYa/lxAkW4Y5VxMJ+A06piy+K/d74dG3YYYTNU1QLM13BpFXi5v9j7U5OhioCtEtsNKRKJ2Bu7g9+rGFhuCyVKXuuhizxfzYOCePJOveMzVH8NSKIOA2U9KPaukso/y9OMGc5YsB2SEfYlJh4HQEa6r8kM+qn3eHUvP5KVDtcwVDdGMTPtDUc1hY8vHYqy6QsqyZxe9yIjnRz07LsauKijlhDSyzX3sBHhjIlMxWFJDE38PKrl3j72eOJDfPvUep1NjeC+PEGAtcURmjjDsofRF+mGtfhTy0Xr0S9Iaq84EOen6ggoiXfqJkt5d08M6pHed1d3kaWWFILV7qDGEk/4t3l2larL/xIc3g8d/vGiOyEae2KCiSaRLAjQu14THHzxtjbXquDvEliiURrt2vGToTmPlfS+uEVwmDOFmi7kDRXAKMyO7Sx25I+CPzVCBYUqyoyLBq4pyJAK1GVyXgS9FHBcvVQx46Ioobu/N8Z4Gb5Tv4s/DLyd3xYXVvegtra/H6npQ7dIiDGbzhL8c9pmwaQmPFBieU8tN+AIbZI7XFejtyGXd0ZOnxV2Rh0eSVxMhfmH8kazS4VN1ldAkYF9iAIb9OGx357XBfmt7HugaEmSDSmfVRKwnoeJI2w1ux+3u2lWSSnWoUR9nkjLEBSNh8sOgROEaNcsluUzGgJiuq1KW3m+zZubrPimqU4xH9REbCG+iXbtXMxS+N8/C6FdEpOImmxQ3Ys6jscg0zFbwWlg+R28WODfvthd8NyIgVt7Jk2OW5tDJlMJkO2C8jHoBcRCTzQ7QOaGYvoe7tyuoOTWbe7Tfsc3EdSX0Z4lM0HXN9O3jeCreoYB3rBU4c0ePj/dIRdcE51X1Ka53bymbj6ZTVr7H/N7t1GE8vlqxDpOx9fzktwF9KHnCQMpBar3QHKaeKHQxSKryd2MYjwLpwG5HfYqBRKsXVvkDebB3ORZEiFds172rZPnKuyCnWF+yswM73zrpse3sWt9h1fxypNWt0UYw9/bwm8F42NpMT5L2ick0tWRUUvYlyGhvL5huJfWNsqYYBuWcy2I9al2KK/3ai2/Lzuh+I/JuwORmUwv2v4Lmzw3NgRjUyI19qSTDiDIZfILaei327aRjlX8h54HWPodL5jkEHYnjRdQwtJmsz249T9RjuFlxn874/fz22rLqO8MvO3rEYiIqfvmhqFMwi5wUTOdopdWl8qRIgmnfPokYuaMOWLQ9GWo5956CobbmroasMjbOSFzMrRwwl1ogJix3S+WaSdRQ7Dxr2WjhvsK6uT3z6RJcXfp/eWuKMTKzd1npVPfj4AKUD0AetZYwlmNGKLQ/hAY22chBpfGpBdemAz4xmEdkN2l4CWzyhKgxNFly5HUrcA3DghciZ+daoLZck6BcHsVo2dOD9NCtSqJTER8XJwE9ME5TN+hw4vQQG5nqdpqRhdM5H/RTRomqUkzJjeiB5uxO3/d7rOGnuHEzQkazzvuvV0lTwZDwpmOQWWo/tcSClaBQ0bMoEY+y1D9KN7qzJUn9V9MHmHdtSz2CL0+czNBDUgDiIwOGGWXVYgvli3QOTH1XT7MwkB0WERhS3rwnbkmsfxvYi3BUEl4W6nJh3bxZHHWIiml/d0RkhCVBq3WPomrlgd2jWvwVv+87c6bg7fblrCMe+2WcjdZGhauKiMr0DNwg0eH36L9mtpLXKPyJpnwenw5Ipy5Q/lQd+WOCsQk95dlQtGIvd1Eicazz790q2ugIqAAEB/gP+A/AH9A/YH/A/EH8g/UH/++wP9B+YP7B+4P/B/EP4g/kH6g/wH5Q/qH7Q/6H8w/mD+wfqD/QfnD+4fvD/4fwj+EP4h+kP8h+QP6R+yP+R/KP5Q/qH6Q/2H5g/tH7o/9H8Y/jD+YfrD/IflD+sftj/sfzj+cP7h+sP9h+cP7x++P/x/BP4I/hH6I/xH5I/oH7E/4n8k/kj+kfoj/Ufmj+wfuT/yfxT+KP5R+qP8R+WP6h+1P+p/NP5o/tH6o/1H54/uH70/+n8M/hj+Mfpj/Mfkj+kfsz/mfyz+WP6x+mP9x+aP7R+7P/Z/HP44/nH64/zH5Y/rH7c/7n88/nj+8frj/cfnj+8fvz8BfyaDPvzxpIYmjplqslWeVZRQyf+hcePS1/KSvc32PT/sPqlFSpJpNYyb9jXzf2wVkLxSSnNjTzpxvPtc4EKUH+03v6/112bEvxQfaL2LmLpVtcd48I9d/oeMe6OPl1Eksjrm5vXGmGu4dsMWd2PjjjLE1Ch3L17/NUnhufJubJMWLeG5tTLYY3O2rNnWwgvjV3MVoHYj4lQU3FlkhE/3oxB0MtDEUl1887jahXupYp1yfdDsxqAw2HqVMpzVEjybDkEsNNZ95UI3biMj+0NUn4mWu+aGqdeDhq90/FH1NFNxEOyRNHHQGeAo5WoYa8UUntC/Jnd6p1YERadDs3zuAKrSHR9lozukXbgmWLDjtVJEbroGX9Pb7cgJUDtirkbS2cyHN78+TD0JHmziU/b1XUmwm/8vP1HYbeRALMyQlWMBP6b85Y6ckxKaYQg+sgYS05MBczaC6JCMC9O+ZeGSWUYDfM1uh3/31PDt84HK79NO0n1sguw/3CheVbPa77tXLg2zD2mW6UDilDLuGCw7RPv+3xFrPWWBEHwz57IYjSBWL35flB6Z6PVDODdH/mLWI0fxUTlE7WMRdc4b46k7Wq67t0S5msnqy/X84YkT4TCIwIN7hWJ35Kh4GbvI8TTWwLRObO3xSAlrbKoDvP8YX+wvgwSKNwUneShYbILwTW31lyXHDFmZSAUzp67ibc+ntzIkkbyFDr7TEzyShJvR6UXzRxJ+WhMa+bcLLuwD+pl4bKriC8HuloCApRi4Tn+Ldu79oIQ2JrL9jurnAb+0eclyE2fP3JaopuelbanRUWXNWfHs9GGGyukdrpW19NmeMhoUbsh6U65TBTwgumorAv06gXuco59RPMFO+l3ilpKIqdX3MZcU5fWAA/smtC6WdhU6mbs9Qb8agASOH+B3kqVGi9z46pBhvtktDznchfZp2QUYgmSJA8Qi6SuPa0DfqIFxq/UHbdaoJ9x+J3Sr6HECPeeryP8prlKqiSI3TjpqJBynbidUjq2bepB4vVoAzSOHO4ZoZ9elgaSz4b0hBGaL0vLh4vBAGsnV3MxWW7r2WQrK6+aC83nXzKxF6mq00wAGKinbeU6VtGKJFawHn2gTsY1dMbYuD/o5BabxVTp/PP1M8wl2VoT8ROBomHYnqxKkAolmONNN3lBX0w4hLCPQR4GzmfYMtfbH7Fw0fimb11RqazUbefLYTVZ7wiycidHiXwN29oCpRn5nOEjkq5FDfr4qC4WMXWvtE+1p9QeyUz7P7DmlufdKwfdYTxjoyTAI24ouGQRickGORioG6G5Imy3ngrkhOiQc37Wubl0yjGQaJl1YPDQjPPBGVhMGTHUz64kec+m7x1aSr0u/x2P8vmXCXoC7eXzR9Uusr/qmJ3eYKHNKUntR/nzkPiT2AJWlxRU0yFX7mAdeAkTPCU5W6d+fwShDQzCDclQWxf9iyut31nMS+vPEKbb3Haw+R+cXiFRcQZFQyKeRvj+gJd9qhUChzz744AeQ1TaPmzArDyKBXQM0ZRnJZith9ovTy2B71EwI2g/l/6Aqx3DRC7uCyoRuxt3A27UWRdEXxxdrixJ6ne06rBEefKQK+IQ174H1Wx1pqIRSGaUExDAv9YLFdpMXYQjKjP6X0++Fc4Djq9BPMrVVgP0BdYPgJt4UgLJ3Sxexd+VVlv+ei8e6+eRV7AaaWDSg+MAX0UXYUrSP1AXkFR7Tnm6Q499gAbyIDyf72m16P2VMlOqfLAiIPNvH3YAzJr9Ise+mQdO5308O6J8h6+2dkQ3uD+AvJAUI4P/rJ1+93NCjpX1tSxc+c0scR2iDL9DjOW4jqnc38d9ol43apGX93Po1gLX9jAFCEpIsD7NmEQ/nOjpKcgG38nCnfjF03o0QC7rO6UECnKHzhCyOxL9bsV9YAs/vqSDorM90MdCSphvHMoGxOmWGMCPJbTiUIF2aImQbS3YQuzmVK+pRdbjCuUpFCcHXgyOUk/OecDHKMFJHAXioXuIQhrGsO3kxkc7YBwQZrd37JRUYg7iUKKXhnrG8R6RL5v8qnTQsrdhdnWiUpXBAJJ4Zf5GwfZn0smZTjMZeLIirFeycubDP8JVtldRw5xobtTcmQzkXkEV4MYTKieoow+xDoPpANpMfzXWDBxL7cTF+v/twRgpfCSZT1RkjGl2H4v5rV1f2e2nN76TZk5njLZVU3/EjfyC9//o93BxuU/lm6lZyfOHzk3nX6xEUAFzBFF5yVdJQq+KpB9XG+mnmxBKeKh5T3vDNMoNpnLzO3S1vHqZTlTQXnIDpKyy9wKSaRPyaBu0iScbkm5goCXm2lvFyDtYbqsk2lK7B8N2KAeenSNI1qcjiKtANbjYvo/0PUJijct6fH+/wnp1BQRgalRE8HTV7npZoJE/m8PaQ/omqure1rpL0cutlQrh0Rm57CMLG7BaNhc/3msP4veCHGCuqg3JiiztjmNjqvnfjtmEjYb9eQreg0IMNAvsBTZXyzmd9P/kzx0vB1KH6Ic4WVGp5itXPCg9AZEH3Q5mXpjd/OvWXsfdacxPb6Pxuxu25UT83f3zQNmTveaxDzrMCfW+m9vWcdRP6du1dWoHv/z+TzVV725UE8ANBOMyZnjHs6+h6uKJIKRxgpQQKEpY1UkQyLVNA8sPALpPYYVMwipbrmsCul6Kpwi3GJp9qSzLoZWUNbTex+/o25hucPrzr3OH/eNsmab0iyep9s4z0vHeB3yryYMuharFOq2L23VZfvqjqOfWBXxo8Q7TOHTpBgu+cg1damty9vrtO0Mwq6RGpeWjxtQu8tRunwcLZPJx9//Q9t6n8fPsC7dZphOaVMdMMCf/1LN7yvLnzAwdYcSPyofrC8Pg2GZZhq38FF/knEMGbF8NF26Of5rF9BSCSdBVUe7oDQRk3+pspvXnYDl57krztcQPniuFddaM0aKlrt9LtbKv+70hqe5sxDGg0JloKTqyjep7oB7aN41J1D1Umn62897vhh+yTmXQwzbz3WydKHmxUgzX50oVvc18p7+Mh/phTV4Nmu9hHIz13BTAsY3EDH87eb+zq1VXnzkv6x/HE3MPcmvHeBEc3WUgH8ukaDeEVh0LegpoYmaSnMUIEAFAUWtwCOhSB+4QP+VZH/yeo96chUj/CRLQBrWa4Hn3NE6d7jSkHaBQ5xpoWZjVjWDM1rj2nzq595oiD6V6VRcRnV1OuBTcwt3bUc+PE6bfrwQ8=
*/