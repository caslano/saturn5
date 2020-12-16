// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2005 Dan Marsden.
// Copyright 2008 Hartmut Kaiser.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_QUERYING_HPP
#define BOOST_PHOENIX_ALGORITHM_QUERYING_HPP

#include <algorithm>

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_find.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_lower_bound.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_upper_bound.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_equal_range.hpp>

#include <boost/phoenix/stl/algorithm/detail/begin.hpp>
#include <boost/phoenix/stl/algorithm/detail/end.hpp>
#include <boost/phoenix/stl/algorithm/detail/decay_array.hpp>

#include <boost/phoenix/function/adapt_callable.hpp>

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/difference_type.hpp>

namespace boost { namespace phoenix {
    namespace impl
    {
        struct find
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& x, mpl::true_) const
            {
                return r.find(x);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& x, mpl::false_) const
            {
                return std::find(detail::begin_(r), detail::end_(r), x);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& x) const
            {
                return execute(r, x, has_find<R>());
            }
        };

        struct find_if
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::find_if(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct find_end
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template<typename This, class R, class R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::find_end(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::find_end(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }
        };

        struct find_first_of
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template<typename This, class R, class R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::find_first_of(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::find_first_of(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }
        };

        struct adjacent_find
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::adjacent_find(detail::begin_(r), detail::end_(r));
            }

            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::adjacent_find(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct count
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_difference<R>
            {};

            template<class R, class T>
            typename range_difference<R>::type
            operator()(R& r, T const& x) const
            {
                return std::count(detail::begin_(r), detail::end_(r), x);
            }
        };

        struct count_if
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_difference<R>
            {};

            template<class R, class P>
            typename range_difference<R>::type
            operator()(R& r, P p) const
            {
                return std::count_if(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct distance
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_difference<R>
            {};

            template<class R>
            typename range_difference<R>::type
            operator()(R& r) const
            {
                return std::distance(detail::begin_(r), detail::end_(r));
            }
        };

        struct equal
        {
            typedef bool result_type;

            template<class R, class I>
            bool operator()(R& r, I i) const
            {
                return std::equal(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class P>
            bool operator()(R& r, I i, P p) const
            {
                return std::equal(detail::begin_(r), detail::end_(r), i, p);
            }
        };

        struct search
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, typename R2>
            struct result<This(R&, R2&)>
                : range_iterator<R>
            {};

            template <typename This, class R, typename R2, class P>
            struct result<This(R&, R2&, P)>
                : range_iterator<R>
            {};

            template<class R, class R2>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2) const
            {
                return std::search(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    );
            }

            template<class R, class R2, class P>
            typename range_iterator<R>::type
            operator()(R& r, R2& r2, P p) const
            {
                return std::search(
                    detail::begin_(r)
                    , detail::end_(r)
                    , detail::begin_(r2)
                    , detail::end_(r2)
                    , p
                    );
            }
        };

        struct lower_bound 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.lower_bound(val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::lower_bound(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_lower_bound<R>());
            }

            template<class R, class T, class C>
            typename range_iterator<R>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::lower_bound(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        struct upper_bound 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : range_iterator<R>
            {};

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.upper_bound(val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::upper_bound(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename range_iterator<R>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_upper_bound<R>());
            }

            template<class R, class T, class C>
            typename range_iterator<R>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::upper_bound(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        namespace result_of
        {
            template <typename R, typename T, typename C = void>
            struct equal_range
            {
                typedef std::pair<
                    typename range_iterator<R>::type
                    , typename range_iterator<R>::type
                > type;
            };
        }

        struct equal_range 
        {
            template <typename Sig>
            struct result;

            template <typename This, class R, class T>
            struct result<This(R&, T&)>
                : result_of::equal_range<R,T>
            {};

            template <typename This, class R, class T, class C>
            struct result<This(R&, T&, C)>
                : result_of::equal_range<R,T, C>
            {};

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            execute(R& r, T const& val, mpl::true_) const
            {
                return r.equal_range(val);
            }

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            execute(R& r, T const& val, mpl::false_) const
            {
                return std::equal_range(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T>
            typename result_of::equal_range<R, T>::type
            operator()(R& r, T const& val) const
            {
                return execute(r, val, has_equal_range<R>());
            }

            template<class R, class T, class C>
            typename result_of::equal_range<R, T, C>::type
            operator()(R& r, T const& val, C c) const
            {
                return std::equal_range(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        namespace result_of
        {
            template <typename R, typename I, typename P = void>
            struct mismatch
            {
                typedef std::pair<
                    typename range_iterator<R>::type
                    , typename detail::decay_array<I>::type
                > type;
            };
        }

        struct mismatch
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class I>
            struct result<This(R&, I)>
                : result_of::mismatch<R, I>
            {};

            template<typename This, class R, class I, class P>
            struct result<This(R&, I, P)>
                : result_of::mismatch<R, I, P>
            {};

            template<class R, class I>
            typename result_of::mismatch<R, I>::type
            operator()(R& r, I i) const
            {
                return std::mismatch(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class P>
            typename result_of::mismatch<R, I, P>::type
            operator()(R& r, I i, P p) const
            {
                return std::mismatch(detail::begin_(r), detail::end_(r), i, p);
            }
        };

        struct binary_search 
        {
            typedef bool result_type;

            template<class R, class T>
            bool operator()(R& r, T const& val) const
            {
                return std::binary_search(detail::begin_(r), detail::end_(r), val);
            }

            template<class R, class T, class C>
            bool operator()(R& r, T const& val, C c) const
            {
                return std::binary_search(detail::begin_(r), detail::end_(r), val, c);
            }
        };

        struct includes 
        {
            typedef bool result_type;

            template<class R1, class R2>
            bool operator()(R1& r1, R2& r2) const
            {
                return std::includes(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    );
            }

            template<class R1, class R2, class C>
            bool operator()(R1& r1, R2& r2, C c) const
            {
                return std::includes(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    , c
                    );
            }
        };

        struct min_element
        {
            template <typename Sig>
            struct result;
            
            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::min_element(detail::begin_(r), detail::end_(r));
            }
        
            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::min_element(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct max_element
        {
            template <typename Sig>
            struct result;

            template <typename This, class R>
            struct result<This(R&)>
                : range_iterator<R>
            {};

            template <typename This, class R, class P>
            struct result<This(R&, P)>
                : range_iterator<R>
            {};

            template<class R>
            typename range_iterator<R>::type
            operator()(R& r) const
            {
                return std::max_element(detail::begin_(r), detail::end_(r));
            }
        
            template<class R, class P>
            typename range_iterator<R>::type
            operator()(R& r, P p) const
            {
                return std::max_element(detail::begin_(r), detail::end_(r), p);
            }
        };

        struct lexicographical_compare
        {
            typedef bool result_type;

            template<class R1, class R2>
            bool operator()(R1& r1, R2& r2) const
            {
                return std::lexicographical_compare(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    );
            }
        
            template<class R1, class R2, class P>
            bool operator()(R1& r1, R2& r2, P p) const
            {
                return std::lexicographical_compare(
                    detail::begin_(r1), detail::end_(r1)
                    , detail::begin_(r2), detail::end_(r2)
                    , p
                    );
            }
        };

    }

    BOOST_PHOENIX_ADAPT_CALLABLE(find, impl::find, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_if, impl::find_if, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_end, impl::find_end, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_end, impl::find_end, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_first_of, impl::find_first_of, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(find_first_of, impl::find_first_of, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(adjacent_find, impl::adjacent_find, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(adjacent_find, impl::adjacent_find, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(count, impl::count, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(count_if, impl::count_if, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(distance, impl::distance, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal, impl::equal, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal, impl::equal, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(search, impl::search, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(search, impl::search, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(lower_bound, impl::lower_bound, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(lower_bound, impl::lower_bound, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(upper_bound, impl::upper_bound, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(upper_bound, impl::upper_bound, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal_range, impl::equal_range, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(equal_range, impl::equal_range, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(mismatch, impl::mismatch, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(mismatch, impl::mismatch, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(binary_search, impl::binary_search, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(binary_search, impl::binary_search, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(includes, impl::includes, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(includes, impl::includes, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(min_element, impl::min_element, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(min_element, impl::min_element, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(max_element, impl::max_element, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(max_element, impl::max_element, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(lexicographical_compare, impl::lexicographical_compare, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(lexicographical_compare, impl::lexicographical_compare, 3)

}}

#endif

/* querying.hpp
LH7Ma/kJ7+WnfIif8XFu5tv8gu/zK37Dr/kDt/I3bmOxyPMVPJT/YG1+z/b8kcO4g2P5CyfyV87l75zHwsUcHxbh31mUq1mMG7gvv2Vx7uD+3Mf5cwCLMoHlWIrVWZoNWYbtWJZHM4nOQ89EZvYhlbZwH1nVv0uE6/nNcD2/xYP5NhvwHXbjuzyJG3g6P+AEbuQF/JAL+BEX82M+wU1cwa/4Gr/mx9zKrdzG7/ljuK5/5nHcwR78hQP4G89hodDOuw9nsgivZlEuZjE+xP25nAfyfZbg10zgdpbhDywb2vcWF8nsoxrtu6p8PEcfaRsPz6uF50dnMImXsTYvZyNewR68kn05l6m8iqM5jxN4Na/kNZzHG/kA5/NR3sS3eDM3cCE/5SL+zNtYWCJvZxXewcP4Nzbj3WzHe9iJ9zKF93Ekl/B8PsCb+CAX8SH+jSv4Pp/lJ3yO3/H50G71IkfwJY7iy5zJtbyM6ziHb/AdruchyvAd1uC77Mj32JkfsC838iRu5jB+zun8glfxS17HrbyT27iU2/kk/8GP+SO/40/8hTtYsajrj1VYyPXXlIXZmkXYjkU5gMU4hAcynSU4g6V5E8twEcvyGSbxeSbzTZbn56zArazE71mZkc/lg1mBNViPNdmdtTiGtZnOOpzDeryGDXgbG/NRNuFbbMr32Ywf81hGHljtxP14HGuwC+uyGxuzO9uwB7uwJ3uzF8exN9PZh5PYl/N4AhfwRN7Bk/gsT+ZqnsI1PJXvchC3cjATXFdDWIqprMLhrMkR7MCR7MgL2ZUzeRov5gjO4ihewu3RfiuhH7Lv7OF3rCP8e1Oo1yYUEy8nMYlnshKnsDHPZiuex3Sez6mcxhs4nQs5g3/jTC7hxXySs/gcL+GH/As/5eVMkIYr2JxX8lTO4VjO5WRexTmcx2t4HW/n9byfN3A1b+Ra3szPeQu3cwET5Hkhy/BWVuFtbMPbeTTv4ADeySG8m1N4D6fzXs7nfVzIxbyTD3AdH+TbfIg/8GH+wmUso9wfZSU+xpZ8nK35dx7HlTyVz3IKV/F8vshLuYbX8iXeypd5P9fycb7CJ/kWHXfPAWf2iXZNhePe0L+nhuP+TjjuG5nEz1iXm9mMn7MPv2B/buM4fsMzuZ1X8x+cz+/5IH/ko/yJz/BnbuQv/Iy/U/p8gKuvsQ+TpKkID2ZRtmYxHsN92Y3FeQr350AeyDNYis8xkWtZml+wDL9nWf7Kg7i/MijHRFbgYazIBqzEbqzMvqzCmazOK3go7+FhXMz6XMkG/JgN+QMbhe9PTVmBrRme7w99q+XBn5zP9yeH43Ewq/EQ1mUVdmZV9mIdDmFdjmY9XsL6vJyNeBMb8yk24etsyn+wOX9hC0YS05rFeBSj6Qx9qZm0T+50dgjp7MwB7MJh7MoZ7MZLeRLT7eQUTuWpvJan8UYO5P0cxGUczDc5hO9wGL/mcB4oDSOZyPFUB/zhfPFT/SAxZoW6giuFZbbdwsPul25hkDBFmCc8JLwubBFWvm0fQuI79i10F8YIlwn3COuELUKJd70nEj87CyOEWcIiYaUQ5qcPc9IL7xb6r5+XvuiG/4656ad1LNj89PM6/uvmqD9sw9556v9b56nf1Rz1izvGm6c+3hz1+Zuf/pgN9ifMEBYIy4UNwi9C7ffsQ5gozBMeEtYL3wpJ7zu+wmnCVGG+sFLYJBT9wL6FtkKKMEt4Qtgm1N5on8I04SFhs1D5Q9sKg4RpwiJhpbBJKPqR9widhRHCLGGRsFzYIpT/2DEXUoR5wjJho1B8kzITThOmCYuFDUKJT6wXBgmzhWXCZiHxU/sR0oTrhOXCJqH4Z8rys0L/l6+iwrA=
*/