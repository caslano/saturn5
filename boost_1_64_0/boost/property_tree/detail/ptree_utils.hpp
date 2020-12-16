// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_PTREE_UTILS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_PTREE_UTILS_HPP_INCLUDED

#include <boost/limits.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/and.hpp>
#include <string>
#include <algorithm>
#include <locale>

namespace boost { namespace property_tree { namespace detail
{

    template<class T>
    struct less_nocase
    {
        typedef typename T::value_type Ch;
        std::locale m_locale;
        inline bool operator()(Ch c1, Ch c2) const
        {
            return std::toupper(c1, m_locale) < std::toupper(c2, m_locale);
        }
        inline bool operator()(const T &t1, const T &t2) const
        {
            return std::lexicographical_compare(t1.begin(), t1.end(),
                                                t2.begin(), t2.end(), *this);
        }
    };

    template <typename Ch>
    struct is_character : public boost::false_type {};
    template <>
    struct is_character<char> : public boost::true_type {};
    template <>
    struct is_character<wchar_t> : public boost::true_type {};


    BOOST_MPL_HAS_XXX_TRAIT_DEF(internal_type)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(external_type)
    template <typename T>
    struct is_translator : public boost::mpl::and_<
        has_internal_type<T>, has_external_type<T> > {};



    // Naively convert narrow string to another character type
    template<typename Str>
    Str widen(const char *text)
    {
        Str result;
        while (*text)
        {
            result += typename Str::value_type(*text);
            ++text;
        }
        return result;
    }

    // Naively convert string to narrow character type
    template<typename Str, typename char_type>
    Str narrow(const char_type *text)
    {
        Str result;
        while (*text)
        {
            if (*text < 0 || *text > (std::numeric_limits<char>::max)())
                result += '*';
            else
                result += typename Str::value_type(*text);
            ++text;
        }
        return result;
    }

    // Remove trailing and leading spaces
    template<class Str>
    Str trim(const Str &s, const std::locale &loc = std::locale())
    {
        typename Str::const_iterator first = s.begin();
        typename Str::const_iterator end = s.end();
        while (first != end && std::isspace(*first, loc))
            ++first;
        if (first == end)
            return Str();
        typename Str::const_iterator last = end;
        do --last; while (std::isspace(*last, loc));
        if (first != s.begin() || last + 1 != end)
            return Str(first, last + 1);
        else
            return s;
    }

} } }

#endif

/* ptree_utils.hpp
U8+SV9zgyB+VxzgrFPxJuxhlicXn2Wd/Vi8XWSN7W1lcYIngL8aZDkaYZY2cv+oz3czQGrF+scbJa1pHJ4wj0x5HrmUtZYRV8q5tLaCPObKzpDNDcB2POcsiede1DrzHvhPHWCPnel7jNDMsSc97rzEhK9v69D77Rhxji9j1rTtE3u91Rln1vPAG1gcmOTpt/1D9QX38kH32YePv9SM31E7PL4hL5ORYdxhnk6M3smYxT86N9Z1JNhj8+NX8bX1r4CfsF7o9nmCFwlznHwaZJ7Du1nOB3JvZhmkiN7e2c4FlCvKsscyxTfQWymCJjiX7+JbGhXEukXcr6zeDzLGZoC0l+fLR+nnzSlyh4Nb6xhDzZN1G+RxdNDZi4WccX0x7HNxWe7nIOocKlMXQlxwPbDPtefFnjcHttI0JNim+vTGbV6a0OSKfc3xwnhk6pE+wRuEdrP9kWyOPnzQ3b2ndFrNbzD/OU3ilNUHMs65EmSVyyjHPINPsUNTqeGqThyFmWb3K9qeVyxL11rAR5ggS6yGT1rPhM+q0Ts2zTbTL8c4sG5zuNl9YsV7Ge7SH3GdpIyu+B7UtHn22OcA69c/RLvIvaCPrFD7XtsxT5NhsZZjg+erg0KDnFL5AOYyS+0L7/EXK40SV41gsGPKcES6R/WJ1EHfeGqP1pcphlexh2zHGArkv02ZGmOPIy7Xl7dYIJtmhesJr77D/mCXyTmVzkXWOvsvxwiK5k7Zlki2Ovlsa25x23I5y0nE7RXRKe2l1/E5z6f3q+YB8TLLF9LQ2MPpBdVHyIXV/WN1comjG2DBL5CPGgRHmyfmo+csEW8Q+ZhxYpXDWvGOGwHF7nCXyPmEffVKbmGSdojl5mX+EcRPXKf6UfjDKCvmfNq6McVG+TdY9HnH8LJM1r37mKXIMLrBDyYL+MkXwBWPNRbYp/qL2M8QskS8ZMzoWjQuRL9ueC6xQ9BVjwQwb5H1VnXQzyTqFSx6zQvbXjCVDLJP/df1mktbHqIOsxyq3Ub/Y4EiTcSIaVy9TnH6wyCr1VxqHhxlnVil+uD4wyhpHT6iPFfKNUT3RSq+xTI45fYGlGu2r1T5GWCW/Tnvu6bggem/jf1/bkftAdfiOwkDUuDJcJm+5Y8Dfc7iEv+EQXGSO7J/4XJYLTLND0ZrPdBkj12e7UTp+5jnLxNYdzxT+QlkMMMEywS+9Z+YEF5jiEjm/Ug7djLFEsOF9PCcZZo5NCn6tXM4zxSVyfmN7uhljieC3tuckw8yxQf6mz4wZYJIVinwuvsjx32sX06yR+wf9oY9xlgm2fJeF04yyyA7Ff1QXw8yzRdGf9JUR5gn+rE10MMo8BdvawiSrZCV+hz7djNN6LXOLTYqvbf4wwTpFWZ4zTdZ1HJeMknNdc49pVsm+nue0MsU2h7LNAaZYp+D6ymKK4AbSGWCBvBvalmFWKM6xvjHOBtEbOY4Ibmw+M84GsZs4B7FIbq7ymWaH+E3NOZYpuJk05ug+Zz+LBTc337nIMkGeNtHBKEsEtzCXmWSb+C2lsUXsVtrLBiX5+sIqxbdWB/Pk3EZ5jLNOyW2lMUWkQP30Mco8M75PG/meY4KLrBBftc+Zxd9gCQaZI/eS+cQQlz4lz6dt+xlzjz5mWefQvHnDCtmf9ZzzTJGzID8jzLNN8Rdsy0nfwZxhgyNfsg3rlCzKzxr+DlJwlnmOf8Wco+ir5hYzbHNoSZtZJu9rymWUTY5+3fHACv6WUDDAEoXL5jBzZH/TGDBHybe8ziSXXutY8z6ymmFmKRr1lplB4q/XZjZ49BvUQdYbvcYU2xwdc5wxwQojb9KfN+snRW9RFwNPl1/cIjounUWK3qoepsk=
*/