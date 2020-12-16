// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_PTREE_FWD_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_PTREE_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/optional/optional_fwd.hpp>
#include <boost/throw_exception.hpp>
#include <functional>           // for std::less
#include <memory>               // for std::allocator
#include <string>

namespace boost { namespace property_tree
{
    namespace detail {
        template <typename T> struct less_nocase;
    }

    // Classes

    template < class Key, class Data, class KeyCompare = std::less<Key> >
    class basic_ptree;

    template <typename T>
    struct id_translator;

    template <typename String, typename Translator>
    class string_path;

    // Texas-style concepts for documentation only.
#if 0
    concept PropertyTreePath<class Path> {
        // The key type for which this path works.
        typename key_type;
        // Return the key that the first segment of the path names.
        // Split the head off the state.
        key_type Path::reduce();

        // Return true if the path is empty.
        bool Path::empty() const;

        // Return true if the path contains a single element.
        bool Path::single() const;

        // Dump as a std::string, for exception messages.
        std::string Path::dump() const;
    }
    concept PropertyTreeKey<class Key> {
        PropertyTreePath path;
        requires SameType<Key, PropertyTreePath<path>::key_type>;
    }
    concept PropertyTreeTranslator<class Tr> {
        typename internal_type;
        typename external_type;

        boost::optional<external_type> Tr::get_value(internal_type);
        boost::optional<internal_type> Tr::put_value(external_type);
    }
#endif
    /// If you want to use a custom key type, specialize this struct for it
    /// and give it a 'type' typedef that specifies your path type. The path
    /// type must conform to the Path concept described in the documentation.
    /// This is already specialized for std::basic_string.
    template <typename Key>
    struct path_of;

    /// Specialize this struct to specify a default translator between the data
    /// in a tree whose data_type is Internal, and the external data_type
    /// specified in a get_value, get, put_value or put operation.
    /// This is already specialized for Internal being std::basic_string.
    template <typename Internal, typename External>
    struct translator_between;

    class ptree_error;
    class ptree_bad_data;
    class ptree_bad_path;

    // Typedefs

    /** Implements a path using a std::string as the key. */
    typedef string_path<std::string, id_translator<std::string> > path;

    /**
     * A property tree with std::string for key and data, and default
     * comparison.
     */
    typedef basic_ptree<std::string, std::string> ptree;

    /**
     * A property tree with std::string for key and data, and case-insensitive
     * comparison.
     */
    typedef basic_ptree<std::string, std::string,
                        detail::less_nocase<std::string> >
        iptree;

#ifndef BOOST_NO_STD_WSTRING
    /** Implements a path using a std::wstring as the key. */
    typedef string_path<std::wstring, id_translator<std::wstring> > wpath;

    /**
     * A property tree with std::wstring for key and data, and default
     * comparison.
     * @note The type only exists if the platform supports @c wchar_t.
     */
    typedef basic_ptree<std::wstring, std::wstring> wptree;

    /**
     * A property tree with std::wstring for key and data, and case-insensitive
     * comparison.
     * @note The type only exists if the platform supports @c wchar_t.
     */
    typedef basic_ptree<std::wstring, std::wstring,
                        detail::less_nocase<std::wstring> >
        wiptree;
#endif

    // Free functions

    /**
     * Swap two property tree instances.
     */
    template<class K, class D, class C>
    void swap(basic_ptree<K, D, C> &pt1,
              basic_ptree<K, D, C> &pt2);

} }


#if !defined(BOOST_PROPERTY_TREE_DOXYGEN_INVOKED)
    // Throwing macro to avoid no return warnings portably
#   define BOOST_PROPERTY_TREE_THROW(e) BOOST_THROW_EXCEPTION(e)
#endif

#endif

/* ptree_fwd.hpp
Zi5Tfy/P8NyAVLSuN9PgOn5cD49vHI3D1KVy347+3q0vmsl+cl0viWdNwps6yy9GTBJvquDlUc6L4GnZ8sLZ9RLR+E/+Bxez8LWKM+HbCHXnkfhstXypL35ZDR+ecq4+C955X++31YM3e9+FcV/ReYxPEp7T7PoL5W0vwiv527ibxJ9J6pNp6gDN9VM3wu2f+enb7PA9+z/VOtZkOGcFF37jJ7PZ13D3GcTPxemVz/Mz/YBUT/o6KsWu+F9D+n+Ov9TC/66Qt39hnlOsz7m7tS/CkxL3h18r73JOtVRev50fVeORTeFpFvt13rboSXnh3mhsOkc+OCLuu8CltOj1TP647ln8mT7Xnmg+heJObfZ0jnrcAOcDYn5ysTpaRzxrJDybJf/vLM/GN4vw7HVn4imb8Sr5Wu9vMpzLc25iPfs/lX6bed+b8L2p7xPanxGD9VEK6Lszfu3cV85d4hz8SWZG46gycfNU+8xuBssP1r+Zrt8gL+Xfjc9x/QuS6jVwHM9r7vx4qTy++Bj23xKPietE5/ODeewuQx6Wss8PsYMj6VVcyB/IX0bqYyTUIY6RFzvHNAY+727Cfk/XXza/XPuSX+IcXjIap34oL7wIHzhRvvcr/v6x1/HdcfKTiunizX74AA9G7YcL8vnCT607Xzy9gH8vht/us7c9/9jI3+QzTSfwf/wsu5LdnomPXgrv2sLfmXjfRvY7Q/3/m/j70e53ckqdJ4Uf8kc8Z69z2fOyxYUEu7wF3j4OZ+ivcXN+cZ266GT7FD8XvYE6xR9xf5ufen9pjb9vxnsWxM+P5V8z6PWAz6fBa/Nfucx+x7hCX4WPqveuc70Z8o1HxOW1cHWiuPy++MlOCz5g39dGrycvwavUc/KW8Yvj8J9f2Pt5ePOZ9uszvFTfvOti6/rGvEbxi/h39dfwp9H2K84bnE9poF8weIR4aT9L/8bvrrRP79gXuFE2jv21SamX4GFd8N5S+PwOXjU8fu4Be0/IMz9n7/+Kf//LvE7iX7niw/fxc2a8/ot4dYF43UsdqLt63aN49zA4zx+3qjMN24GXwb/e/G7Cb2nRWCo+fqtf10JcWWdfFyTVPcTHk9gNva59y/wHmc9T9DSWHvbHz0PDh9LEi7PhwgrXaYHHd4vGigJ1+2nqpvLC3vfh72fG58LxidPwAbhbtA9vzxNvP7De5uzmOP51m3m+ZZ0D5NHj2H0reeUteCf8GiN/zPF6+Z30dTnc6AYH+8IlONtM/O76oLzzTvkYOyyDd0l+m9k5zXOlzPs08ZDfrb6CP7PLvL/xpwR8js9RJ+zLo/jvJDy2o/rzVfLkqdFYMdb+/N15TfbY2PwGt7ZPjeA0PClYwk8/xkftc+Xv+EVbfWf6L5KPpIrsT334vyUBh/lLJ/bbPalfq6+rT5n7YIbnkOAvw+zTCvHpU3hU33y9vrKVfO9Jdaxjo7H6Lq9/Eo1Vl8gHzSfnkjg/z1CPU8fB63v3k591xDOuEVf/jM/5ui7ca7BKPz3uS62W38fncfH0ZJyPTBOfm7GXHHG8nzrTnfbhMnyG/87kJ8O60N/IDHXPaCweAod+oqerxM34fNdA+ImH1WmP916O9/l7Oh45z/XyTuPP78nze6gT1I3GlH516QT3uwEfaKw+egK8vh//vl/+rz6Y2cx85I/T8dzi99iPc7Slv4jXp/n75TT1CXwxZV+ukkfnxvlmHBfTnHtJj8Yf+NfN9nEFO/vCfv0bTxwizi/EJ5dl4DV4ATudGP++5BDxZS9e/Ko4f5d4vsa+tsaL4Fy9/+Dnv8d5C5y4wXXPcd/a7NM6ux6AL8PF+dPgbCZ/hacjMsXHY+DcEPHp9bj+zR4=
*/