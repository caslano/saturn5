/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IN_05052005_0121)
#define FUSION_IN_05052005_0121

#include <boost/fusion/support/config.hpp>
#include <istream>
#include <boost/fusion/sequence/io/detail/manip.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Tag>
    struct delimiter_in
    {
        // read a delimiter
        template <typename IS>
        static void
        read(IS& is, char const* delim, mpl::false_ = mpl::false_())
        {
            detail::string_ios_manip<Tag, IS> manip(is);
            manip.read(delim);
        }

        template <typename IS>
        static void
        read(IS&, char const*, mpl::true_)
        {
        }
    };

    struct read_sequence_loop
    {
        template <typename IS, typename First, typename Last>
        static void
        call(IS&, First const&, Last const&, mpl::true_)
        {
        }

        template <typename IS, typename First, typename Last>
        static void
        call(IS& is, First const& first, Last const& last, mpl::false_)
        {
            result_of::equal_to<
                typename result_of::next<First>::type
              , Last
            >
            is_last;

            is >> *first;
            delimiter_in<tuple_delimiter_tag>::read(is, " ", is_last);
            call(is, fusion::next(first), last, is_last);
        }

        template <typename IS, typename First, typename Last>
        static void
        call(IS& is, First const& first, Last const& last)
        {
            result_of::equal_to<First, Last> eq;
            call(is, first, last, eq);
        }
    };

    template <typename IS, typename Sequence>
    inline void
    read_sequence(IS& is, Sequence& seq)
    {
        delimiter_in<tuple_open_tag>::read(is, "(");
        read_sequence_loop::call(is, fusion::begin(seq), fusion::end(seq));
        delimiter_in<tuple_close_tag>::read(is, ")");
    }
}}}

#endif

/* in.hpp
ZRzifh5nIvoM1BCmjQaM2PG5IXKGDNOQh76wzZc1MORumnIngyQq/Tir2Fpvbt3CPplgC8eJnMQL2dpcz8Y+g2DT0iuCJC/YNkzDiFW6+8kfjBm+jlXsuXWUsvV+vxWzg7Szw7wEcEHs1u0M6Nn+3PLmMtp76xzgLb4o5BnPnbDmg54CCxxYXGz223yfInwe84vAK6ElTb71rRO97XVql/x14CM+AXmUOXkg2OoBpWM7advvH1OeigdB6mYNj2jgLp4/mTwivXdYJmFeaB5I3taTRubijPvem3ePn/vCPuEvzT2+V0zP6mwGIiOXt7i2NI+6DNR33PKOiJ+unYcEVt/81zJvDxiUOb+0Lo6gQbOZ6S1kULoh9O6Av3MHHsUauOsG4FCNIfe+z4X3bVKUNHU+1llnUQld54cjZkA7YBGNzNkBMgGFMp/yn9tBwhv8U/9DHbA5ZHs8s0M+vpoh9+x/qIcp+I5GTrGfDDd7FJzKFjSdDwt63ZegU2EyFNwjfJnSRY2QdmaE0uBcjnK3xyyaOLgj/fM7CR33z+ijdT1Cxz001muc0IX2BXmPXx9peqTjvkfkgCV0seFA3nM3VDSy8cEz22d3ddBFRg/4m7m3+vmNBK6OejC7eWLrpLl3+vGZ1t41SuOouua0zHL5onunHw/YUwgX/tkDGvu84f+APahzcW2OIJbsdalkAz/6H/EHTZ3Fvh0CD85eYMyxKpN29R6n6W/soJ8yc7DvtOlL/UbTjXqLDsyy0c8mrmfTV/r/4uy6YutoqrCvneJQQw899CIETojB1MyWmW2zu0NiICDAOPENNjj2xdcG0yOKxANIeQAJEA880OtPD71DQCBCD70XIR7yABIPSHBmd/bMnJ1r+AM/uX/+Pd+ZeqadOXOOjcl3cQJ9DKYc55xYW3ec3QsDcrlt+/0i6XfBQv3aPFYlq6Gz4QBxcl63FFyLx8dOzkMzNh6KM32bcHKeb62dOzn/tE2mZczsl2767qGpQauT3G7OpuMpgbG/SV6SZVIb2MQ3vD+HtyDNufQ3r9bHBfjaHhSWNoGvWX1cv/Hw58+6/02Pm2phWy4MNF2ncXZ9baMREGi0F5B7qjtOe5g1A7FvMBEDFUecpb90xtDbUp6HyWG86o5NQqdzxzP2EZrWZ8L+wPb1lQOEbrzg4PyFuKuzE3HDjR7uX7eguB2ozjlMzuJ2bzUJh8mhjKW9fo8DGWRpcbN9ZJh+J7qmPw3a/iwTcWzKfW89DbQ95pI64MqdG/75P7DdwQfntH2Ip3MJcti0371/DyxNHfv4dbOA9+cdlMHZQx7dm1deSjD+vPE3j+7PGxdvQTF03sB3eAAkPhFUInkcBKyCy9BmnujiceE5rycDoXZyl5Q3fM67mxn7Csc+3L+2ox7b4Sr8+aNu+4bmjzU2cOg41oyeCmmY7uaKI/O3mib0PcfaNQ/njTXU8Vrc3mNttI/g9hxrV17R0+GUVZHK6oYXcle39wdvjOhjnxPvcoAYIusaRfQzvbIpnsehqG5Y7+HOA7/X+TbdpO+9Le3EgND0LhTL+3ZKgwl7bml5NGpUyM0eHPVUHs54KrB1v+RhwKYGp2jHrn/Gw6Fc4vsID2MC47q2kT5Gyy+msbKvT8e9JmKueRgsMIllQjGNDGvJtH4mJmO0VNp3MAc8DMhukwxibpqMgWRsve9/0MPoPbKNK+LTcZ+MbzpmCQaMN5x4NZQ23ksm5g71ccc8mbjqYSbLxMotPJwnE9c9jC8Tu7ekGCoTuuIe3ZOJ13kYXyaO3NrDeDLxbg/jy8TCbTyMJxNf9TC+TKjbehgiE9d8OsoE6mLJnFSwKg8ET6P8Ruck/Wb66w8=
*/