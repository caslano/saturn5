// ----------------------------------------------------------------------------
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#ifndef BOOST_PROPERTY_TREE_ID_TRANSLATOR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_ID_TRANSLATOR_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>

#include <boost/optional.hpp>
#include <string>

namespace boost { namespace property_tree
{

    /// Simple implementation of the Translator concept. It does no translation.
    template <typename T>
    struct id_translator
    {
        typedef T internal_type;
        typedef T external_type;

        boost::optional<T> get_value(const T &v) { return v; }
        boost::optional<T> put_value(const T &v) { return v; }
    };

    // This is the default translator whenever you get two equal types.
    template <typename T>
    struct translator_between<T, T>
    {
        typedef id_translator<T> type;
    };

    // A more specific specialization for std::basic_string. Otherwise,
    // stream_translator's specialization wins.
    template <typename Ch, typename Traits, typename Alloc>
    struct translator_between< std::basic_string<Ch, Traits, Alloc>,
                               std::basic_string<Ch, Traits, Alloc> >
    {
        typedef id_translator< std::basic_string<Ch, Traits, Alloc> > type;
    };

}}

#endif

/* id_translator.hpp
43sU/ihbAnRVdPE+f128EwWGqeP401wdh2OEZpO7YBnh8Ap+PdsANiSkCupYdtKERbctBizithjVMUHuNBPVsR+bbB4nH52rSNgPm00S1lKRsACcqpOyJ05qUhZHUqYn1PtPaoTKAUz0n4J9F5+CfffJQAD+jb2y75r4NLni2dinfuJxU/4umv97ksN3/CSDL67y8K06yeFbfJLge+knP/hGBVUBvrYnTPBNzTfA91y+Eb44eXIuDUzG5vqymqlMgnAOUnZ4RbqUZz9E4UF9zp+DfmY6OdXUhhUS6PzjptqdyjPUbl8eThouLNmtyzSVdkWFfMYbSLFop5EUXUkFtpz2tOfxLdimlrkSQ42VeCDPyDZBeeWzDe6EOmxXOWyzGhIlH9yk3uTR+inQczYJ/od4qvHeCvh4lvpotxbNvc2Tc7XnufzmCzz5LE+O1F59hN/sw5Mp2vNO/GYbnozZzWLI8nz2kS1NPnsZ+eyi5rNf1/vsDukYqkQjOpdniqD2Itd0eqfE1MLh7ujS1jgrmK0XmzOJaIA5ZNR9+t1RQdd9uuYo4/p/HtAGfxjLrNW5/qLi+q8/wlz/dwO5/oMsbF/cx9OYzWxLRy6D8/8Oc/5PnVV9R0GiJSZjGqDvX7qR+/5OxflvRQyXwWyosteTsVfIc0ztFdI5/jr2e5Kel2ncdtLf59/Fff7ex1RugzZW6O0K0ttieKfkTZNq
*/